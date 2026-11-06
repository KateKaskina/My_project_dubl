#include <gtest/gtest.h>
#include "main.h" 

//Задача на сортировку на 2-х стеках(на вершине стека наименьшее значение, а на дне-наибольшее)
template <typename T>
void SortStack(Stack<T>& input) {
    Stack<T> tmpStack; // вспомогательный стек, который автоматич. удалится при выходе
    while (!input.IsEmpty()) {
        T current = input.Pop();
        while (!tmpStack.IsEmpty() && tmpStack[tmpStack.size() - 1] > current) {
            T trappedElement = tmpStack.Pop();
            input.Push(trappedElement);
        }
        tmpStack.Push(current);
    }
    while (!tmpStack.IsEmpty())
        input.Push(tmpStack.Pop());

}

// ТЕСТЫ ДЛЯ СОРТИРОВКИ НА ДВУХ СТЕКАХ

TEST(StackSortTest, EmptyAndSingleElement) {
    Stack<int> st;
    EXPECT_NO_THROW(SortStack(st));
    EXPECT_TRUE(st.IsEmpty());

    st.Push(42);
    SortStack(st);
    EXPECT_EQ(st.size(), 1);
    EXPECT_EQ(st.Pop(), 42);
}

TEST(StackSortTest, GeneralSorting) {
    Stack<int> st;
    st.Push(34);
    st.Push(3);
    st.Push(31);
    st.Push(98);
    st.Push(92);
    st.Push(23);

    SortStack(st);

    EXPECT_EQ(st.Pop(), 3);
    EXPECT_EQ(st.Pop(), 23);
    EXPECT_EQ(st.Pop(), 31);
    EXPECT_EQ(st.Pop(), 34);
    EXPECT_EQ(st.Pop(), 92);
    EXPECT_EQ(st.Pop(), 98);
    EXPECT_TRUE(st.IsEmpty());
}

TEST(StackSortTest, DuplicatesAndSorted) {
    Stack<int> st;
    st.Push(5);
    st.Push(10);
    st.Push(5);
    st.Push(1);

    SortStack(st);

    EXPECT_EQ(st.Pop(), 1);
    EXPECT_EQ(st.Pop(), 5);
    EXPECT_EQ(st.Pop(), 5);
    EXPECT_EQ(st.Pop(), 10);
}

// ТЕСТЫ ДЛЯ КЛАССА STACK

// Тест инициализации и начального состояния
TEST(StackTest, InitialState) {
    Stack<int> st;
    EXPECT_TRUE(st.IsEmpty());
    EXPECT_EQ(st.size(), 0);
    EXPECT_THROW(st.Pop(), std::underflow_error);
}

TEST(StackTest, PopPushOperations) {
    Stack<int> st;
    
    st.Push(10);
    st.Push(20);

    EXPECT_EQ(st.size(),2);
    EXPECT_FALSE(st.IsEmpty());

    EXPECT_EQ(st.Pop(), 20);
    EXPECT_EQ(st.Pop(), 10);
    EXPECT_TRUE(st.IsEmpty());
}

TEST(StackTest, AutoResize) {
    Stack<int> st; // memSize=1
    st.Push(1); 
    st.Push(2); // здесь должен вызываться resize()
    st.Push(3);

    EXPECT_EQ(st.size(), 3);
    EXPECT_EQ(st.Pop(), 3);
}

TEST(StackTest, OperatorIndex) {
    Stack<int> st;  
    st.Push(100);
    st.Push(200);  

    // Проверка чтения
    EXPECT_EQ(st[0], 100);
    EXPECT_EQ(st[1], 200);

    // Проверка записи
    st[0] = 500;
    EXPECT_EQ(st[0], 500);

    // Проверка генерации исключений при выходе за границы
    EXPECT_THROW(st[2], std::out_of_range);
    EXPECT_THROW(st[10], std::out_of_range);
}


// ТЕСТЫ ДЛЯ КЛАССА QUEUE

// Тест инициализации и начального состояния
TEST(QueueTest, InitialState) {
    Queue<int> q;
    EXPECT_TRUE(q.IsEmpty());
    EXPECT_EQ(q.size(), 0);
    EXPECT_THROW(q.Pop(), std::underflow_error);
}

TEST(QueueTest, PopPushOperations) {
    Queue<int> q;

    q.Push(10);
    q.Push(20);

    EXPECT_EQ(q.size(), 2);
    EXPECT_EQ(q.Pop(), 10);
    EXPECT_EQ(q.Pop(), 20);
    EXPECT_TRUE(q.IsEmpty());
}

// Тест логики кольцевого буфера (Wrap Around)
TEST(QueueTest, CircularBufferWrapAround) {
    Queue<int> q; // memSize = 2 
    q.Push(1);
    q.Push(2);    // Очередь заполнена [1, 2]

    q.Pop();      // Удалили 1. Теперь `first` указывает на индекс 1.

    // Добавляем элемент. Он должен зациклиться и встать на освободившийся индекс 0.
    EXPECT_NO_THROW(q.Push(3));
    EXPECT_EQ(q.size(), 2);

    // Проверяем, что элементы извлекаются в верном порядке (2, затем 3)
    EXPECT_EQ(q.Pop(), 2);
    EXPECT_EQ(q.Pop(), 3);
    EXPECT_TRUE(q.IsEmpty());
}

// Тест resize в момент, когда очередь "разорвана" по кольцу
TEST(QueueTest, ResizeWhenWrapped) {
    Queue<int> q; // memSize = 2
    q.Push(1);
    q.Push(2);
    q.Pop();      // Очередь: [_, 2], буфер сдвинут
    q.Push(3);    

    EXPECT_NO_THROW(q.Push(4));

    EXPECT_EQ(q.size(), 3);
    EXPECT_EQ(q.Pop(), 2);
    EXPECT_EQ(q.Pop(), 3);
    EXPECT_EQ(q.Pop(), 4);
}

TEST(QueueTest, OperatorIndex) {
    Queue<int> q; // memSize = 2
    q.Push(10);
    q.Push(20);
    q.Pop();
    q.Push(30);   // Элементы в памяти физически расположены как [30, 20]

    // Логически под индексом 0 идет элемент 20 (голова очереди), под индексом 1 - 30.
    EXPECT_EQ(q[0], 20);
    EXPECT_EQ(q[1], 30);

    // Изменение элемента по индексу
    q[0] = 99;
    EXPECT_EQ(q[0], 99);

    // Проверка исключений
    EXPECT_THROW(q[2], std::out_of_range);
}