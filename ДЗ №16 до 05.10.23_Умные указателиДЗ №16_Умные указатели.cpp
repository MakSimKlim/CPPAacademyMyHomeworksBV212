// ДЗ #16_Умные указатели
//
//Тема: У мные указатели
//Задание 1. Создайте пользовательские классы умных указателей.Один из
//классов должен повторять функциональность стандартного класса unique_ptr,
//а другой shar ed_ptr.Напишите к од по тестированию ваших классов.


#include <iostream>

using namespace std;

// Простой класс для демонстрации
class MyClass {
public:
    MyClass(int val) : value(val) {}

    void print() {
        cout << "Value: " << value << endl;
    }

private:
    int value;
};

// Реализация умного указателя, аналогичного std::unique_ptr
template <typename T>
class MyUniquePtr {
public:
    // Конструктор
    MyUniquePtr(T* ptr) : data(ptr) {}

    // Деструктор, освобождает память
    ~MyUniquePtr() {
        delete data;
    }

    // Оператор разыменования
    T& operator*() const {
        return *data;
    }

    // Оператор доступа к члену
    T* operator->() const {
        return data;
    }

private:
    T* data;
};

// Реализация умного указателя, аналогичного std::shared_ptr
template <typename T>
class MySharedPtr {
public:
    // Конструктор
    MySharedPtr(T* ptr) : data(ptr), count(new size_t(1)) {}

    // Конструктор копирования
    MySharedPtr(const MySharedPtr& other) : data(other.data), count(other.count) {
        (*count)++;
    }

    // Деструктор, уменьшает счетчик и освобождает память, если необходимо
    ~MySharedPtr() {
        (*count)--;
        if (*count == 0) {
            delete data;
            delete count;
        }
    }

    // Оператор разыменования
    T& operator*() const {
        return *data;
    }

    // Оператор доступа к члену
    T* operator->() const {
        return data;
    }

private:
    T* data;
    size_t* count;
};

int main() {
    // Пример использования MyUniquePtr
    MyUniquePtr<MyClass> uniquePtr(new MyClass(42));
    uniquePtr->print();

    // Пример использования MySharedPtr
    MySharedPtr<MyClass> sharedPtr1(new MyClass(24));
    MySharedPtr<MyClass> sharedPtr2 = sharedPtr1;  // теперь у них общий указатель

    sharedPtr1->print();
    sharedPtr2->print();

    return 0;
}
