// ДЗ №8 до 16.09.23 Виртульные методы (стэк на базе списка)

// Задание 1. Создать базовый класс список.Реализовать на базе списка стек
// и очередь с виртуальными функциями вставки и вытаскивания.

#include <iostream>
using namespace std;

// Определяем базовый класс "Список"
class List {
public:
    virtual void insert(int value) = 0;     // Виртуальная функция для вставки элемента
    virtual int remove() = 0;               // Виртуальная функция для вытаскивания элемента
    virtual bool isEmpty() const = 0;       // Виртуальная функция для проверки, пуст ли список
};

// Определяем производный класс "Стек" на основе базового класса "Список"
class Stack : public List 
{
private:
    int* data;          // Массив для хранения элементов стека
    int top;            // Индекс вершины стека
    int capacity;       // Вместимость стека

public:
    Stack(int size) : top(-1), capacity(size) 
    {
        data = new int[size];
    }

    ~Stack() 
    {
        delete[] data;
    }

    void insert(int value) override 
    {
        if (top < capacity - 1) {
            data[++top] = value;
        }
        else {
            cout << "Стек переполнен." << endl;
        }
    }

    int remove() override 
    {
        if (!isEmpty()) 
        {
            return data[top--];
        }
        else 
        {
            cout << "Стек пуст." << endl;
            return -1; // Возвращаем -1 как признак ошибки
        }
    }

    bool isEmpty() const override 
    {
        return top == -1;
    }
};

// Определяем производный класс "Очередь" на основе базового класса "Список"
class Queue : public List 
{
private:
    int* data;          // Массив для хранения элементов очереди
    int front;          // Индекс начала очереди
    int rear;           // Индекс конца очереди
    int capacity;       // Вместимость очереди

public:
    Queue(int size) : front(0), rear(-1), capacity(size) 
    {
        data = new int[size];
    }

    ~Queue() 
    {
        delete[] data;
    }

    void insert(int value) override 
    {
        if (rear < capacity - 1) 
        {
            data[++rear] = value;
        }
        else 
        {
            cout << "Очередь переполнена." << endl;
        }
    }

    int remove() override 
    {
        if (!isEmpty()) 
        {
            int removedValue = data[front];
            front++;
            return removedValue;
        }
        else 
        {
            cout << "Очередь пуста." << endl;
            return -1; // Возвращаем -1 как признак ошибки
        }
    }

    bool isEmpty() const override 
    {
        return front > rear;
    }
};

int main() 
{
    setlocale(LC_ALL,"Rus");

    Stack stack(5);
    Queue queue(5);

    // Добавляем элементы в стек
    for (int i = 1; i <= 5; i++) 
    {
        stack.insert(i);
    }

    cout << "Извлечение элементов из стека:" << endl;
    while (!stack.isEmpty()) 
    {
        cout << stack.remove() << " ";
    }
    cout << endl;

    // Добавляем элементы в очередь
    for (int i = 1; i <= 5; i++) 
    {
        queue.insert(i);
    }

    cout << "Извлечение элементов из очереди:" << endl;
    while (!queue.isEmpty()) 
    {
        cout << queue.remove() << " ";
    }
    cout << endl;

    return 0;
}