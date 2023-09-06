// ДЗ №4 до 07.09.23 Шаблоны классов Наследование.
//
//Задание 1. Создайте шаблонный класс DynArray , к оторый будет хранить
//динамический массив данных, тип которых является шаблонным. Для
//него нужно перегрузить операторы() (перегрузка без параметров
//возвращает длину массива, если передаётся один параметр - добавляет
//этот элемент в к онец массива), [], = (к опирующее и перемещающее) и << .
//Также определите для него конструктор с использованием
//std::initalizer_list.
// 
//Задание 2. Создайте наследника от этого класса DynArrayNum, для
//которого перегружены операторы + (попарно складывает два массива с
//начала, элементы без пары просто добавляются в новый массив без
//изменений), -(такое же попарное вычитание) и * (попарное умножение).


#include <iostream>
#include <stdexcept>
#include <utility>

using namespace std;

template <typename T>
class DynArray
{
private:
    T* data;       // Указатель на динамический массив
    size_t size;   // Размер массива

public:
    // Конструктор по умолчанию, создающий пустой массив
    DynArray() : size(0), data(nullptr) {}

    // Конструктор копирования
    DynArray(const DynArray& other) : size(other.size), data(new T[size])
    {
        for (size_t i = 0; i < size; ++i)
        {
            data[i] = other.data[i];
        }
    }

    // Конструктор перемещения
    DynArray(DynArray&& other) noexcept : size(other.size), data(other.data)
    {
        other.size = 0;
        other.data = nullptr;
    }

    // Деструктор для освобождения памяти
    ~DynArray()
    {
        delete[] data;
    }

    // Перегрузка оператора () для получения длины массива
    size_t operator()() const
    {
        return size;
    }

    // Перегрузка оператора () для добавления элемента в конец массива
    void operator()(const T& element)
    {
        T* newData = new T[size + 1];
        for (size_t i = 0; i < size; ++i)
        {
            newData[i] = data[i];
        }
        newData[size] = element;
        delete[] data;
        data = newData;
        ++size;
    }

    // Перегрузка оператора [] для доступа к элементам массива
    T& operator[](size_t index)
    {
        if (index >= size)
        {
            cout << "Индекс вне диапазона" << endl;
            // Выбираем значение по умолчанию для типа T
            static T defaultValue = T();
            return defaultValue;
        }
        return data[index];
    }

    // Перегрузка оператора присваивания для копирования
    DynArray& operator=(const DynArray& other)
    {
        if (this != &other)
        {
            delete[] data;
            size = other.size;
            data = new T[size];
            for (size_t i = 0; i < size; ++i)
            {
                data[i] = other.data[i];
            }
        }
        return *this;
    }

    // Перегрузка оператора присваивания для перемещения
    DynArray& operator=(DynArray&& other) noexcept
    {
        if (this != &other)
        {
            delete[] data;
            size = other.size;
            data = other.data;
            other.size = 0;
            other.data = nullptr;
        }
        return *this;
    }

    // Перегрузка оператора вывода для удобного вывода массива
    friend ostream& operator<<(ostream& os, const DynArray& arr)
    {
        os << "[";
        for (size_t i = 0; i < arr.size; ++i)
        {
            os << arr.data[i];
            if (i < arr.size - 1)
            {
                os << ", ";
            }
        }
        os << "]";
        return os;
    }
};

int main()
{
    // Пример использования DynArray
    DynArray<int> arr;

    // Добавление элементов
    arr(1);
    arr(2);
    arr(3);

    // Получение размера массива
    cout << "Размер массива: " << arr() << endl;

    // Доступ к элементам массива
    cout << "Элемент с индексом 1: " << arr[1] << endl;

    // Копирование и перемещение объектов
    DynArray<int> copyArr = arr;         // Копирование
    DynArray<int> moveArr = std::move(arr); // Перемещение

    return 0;
}
