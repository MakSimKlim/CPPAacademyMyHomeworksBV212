// ДЗ №9 до 18.09.23 Исключения и пространства имен
// 
// Задание 1. Возьмите код очередей из предыдущих домашних заданий и
// добавьте обработку исключений для случаев, когда происходит попытка
// достать объект из пустой очереди или добавить объект в полную очередь.


#include <iostream>
using namespace std;

// Определяем базовый класс "Список"
class List 
{
public:
    virtual void insert(int value) = 0;     // Виртуальная функция для вставки элемента
    virtual int remove() = 0;               // Виртуальная функция для вытаскивания элемента
    virtual bool isEmpty() const = 0;      // Виртуальная функция для проверки, пуст ли список
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
        try 
        {
            if (top < capacity - 1) 
            {
                data[++top] = value;
            }
            else 
            {
                throw "Стек переполнен.";  // Генерируем исключение с сообщением
            }
        }
        catch (const char* e) 
        {
            cout << "Произошла ошибка: " << e << endl;
            throw;  // Повторно генерируем исключение
        }
    }

    int remove() override 
    {
        try 
        {
            if (!isEmpty()) 
            {
                return data[top--];
            }
            else 
            {
                throw "Стек пуст.";  // Генерируем исключение с сообщением
            }
        }
        catch (const char* e) 
        {
            cout << "Произошла ошибка: " << e << endl;
            throw;  // Повторно генерируем исключение
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
        try 
        {
            if (rear < capacity - 1) 
            {
                data[++rear] = value;
            }
            else 
            {
                throw "Очередь переполнена.";  // Генерируем исключение с сообщением
            }
        }
        catch (const char* e) 
        {
            cout << "Произошла ошибка: " << e << endl;
            throw;  // Повторно генерируем исключение
        }
    }

    int remove() override 
    {
        try 
        {
            if (!isEmpty()) 
            {
                int removedValue = data[front];
                front++;
                return removedValue;
            }
            else 
            {
                throw "Очередь пуста.";  // Генерируем исключение с сообщением
            }
        }
        catch (const char* e) 
        {
            cout << "Произошла ошибка: " << e << endl;
            throw;  // Повторно генерируем исключение
        }
    }

    bool isEmpty() const override 
    {
        return front > rear;
    }
};

int main() 
{
    setlocale(LC_ALL, "Rus");
    Stack stack(7);
    Queue queue(7);

    try 
    {
        // Добавляем элементы в стек, для примера специально увеличим количество
        for (int i = 1; i <= 8; i++) 
        {  // Переполним стек
            stack.insert(i);
        }
        cout << "Извлечение элементов из стека:" << endl;
        while (!stack.isEmpty()) 
        {
            cout << stack.remove() << " ";
        }
        cout << endl;
    }
    catch (...) //универсальный catch
    {
        cout << "Обработка ошибки в основной функции." << endl;
    }

    try 
    {
        // Добавляем элементы в очередь
        for (int i = 1; i <= 7; i++) 
        {  // Переполним очередь
            queue.insert(i);
        }
        cout << "Извлечение элементов из очереди:" << endl;
        while (!queue.isEmpty()) 
        {
            cout << queue.remove() << " ";
        }
        cout << endl;
    }
    catch (...) //универсальный catch
    {
        cout << "Обработка ошибки в основной функции." << endl;
    }
    return 0;
}