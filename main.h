#include <iostream>
#include <stdexcept>

template<typename T>
class Stack{
    int top; // индекс верхнего элемента
    size_t memSize; 
    T* pMem; // ук-ль на масcив эл-ов

    // метод для расширения памяти\размера стека
    void resize() {
        memSize *= 2;
        T* pNewMem = new T[memSize];
        for (int i = 0;i <= top;i++) {
            pNewMem[i] = pMem[i];
        }
        delete[] pMem;
        pMem = pNewMem;
    }
public:
    Stack() : top(-1), memSize(1), pMem(new T[memSize]) {}
    ~Stack() { delete[] pMem; }

    size_t size() const { return top + 1; }
    bool IsEmpty() const { return top == -1; }

    T Pop() { 
        if (IsEmpty()) {
            throw std::underflow_error("Stack is empty! Cannot pop.");
        }
        return pMem[top--]; 
    }

    void Push(const T& val) {
        if (size() == memSize) {
            resize();
        }
        pMem[++top] = val;
    }

    // 1. Версия для неконстантных объектов (можно читать и изменять: st[i] = val)
    T& operator[](size_t index) {
        if (index > static_cast<size_t>(top)) {
            throw std::out_of_range("Index out of range!");
        }
        return pMem[index];
    }

    // 2. Версия для константных объектов (только для чтения: val = st[i])
    const T& operator[](size_t index) const {
        if (index > static_cast<size_t>(top)) {
            throw std::out_of_range("Index out of range!");
        }
        return pMem[index];
    }

};

template<typename T>
class Queue{
    int first; // Индекс начала очереди
    int last; // Индекс конца очереди
    size_t count; // Кол-во эл-ов в очереди
    size_t memSize;
    T* pMem;

    void resize() {
        size_t newSize = memSize * 2;
        T* pNewMem = new T[newSize];

        int curr = first;
        for (size_t i = 0;i < count;i++) {
            pNewMem[i] = pMem[curr];

            curr++; // двигаемся к след. эл-ту
            if (curr == memSize) {
                curr = 0; //Если дошли до конца старого массива, прыгаем в начало
            }
        }

        delete[] pMem;
        pMem = pNewMem;
        memSize = newSize;

        first = 0;
        last = count - 1;
    }
public:
    Queue() : first(0), last(-1), count(0), memSize(2), pMem(new T[memSize]) {}
    ~Queue() { delete[] pMem; }

    size_t size() const { return count; }
    bool IsEmpty() const { return count == 0; }

    void Push(const T& val){ // Добавление в конец очереди
        if (count == memSize) {
            resize();
        }

        last++;
        if (last == memSize) {
            last = 0;
        }
        pMem[last] = val;
        count++;
    }

    T Pop() { // Извлечение из начала очереди
        if (IsEmpty()) {
            throw std::underflow_error("Queue is empty! Cannot pop.");
        }
        T result = pMem[first];
        first++;
        if (first==memSize) {
            first = 0;
        }
        count--;
        return result;
    }

    // 1. Вариант для чтения и изменения элементов: q[i] = value;
    T& operator[](size_t index) {
        if (index >= count) {
            throw std::out_of_range("Index out of range!");
        }

        // Вычисляем реальный физический индекс в кольцевом массиве
        int realIndex = first + index;
        if (realIndex >= memSize) {
            realIndex -= memSize; // Если вышли за край массива, заворачиваем по кольцу
        }

        return pMem[realIndex];
    }

    // 2. Вариант для константных объектов (только для чтения)
    const T& operator[](size_t index) const {
        if (index >= count) {
            throw std::out_of_range("Index out of range!");
        }

        int realIndex = first + index;
        if (realIndex >= memSize) {
            realIndex -= memSize;
        }

        return pMem[realIndex];
    }
};


