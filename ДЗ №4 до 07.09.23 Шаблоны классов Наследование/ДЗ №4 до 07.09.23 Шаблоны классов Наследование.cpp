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

#include <iostream>           // Для работы с вводом и выводом
#include <initializer_list>   // Для использования списков инициализации
#include <algorithm>          // Для использования функций работы с последовательностями
#include <stdexcept>          // Для работы с исключениями

// Используем пространство имен std (стандартная библиотека C++)
using namespace std;

// Объявляем шаблонный класс DynArray
template <typename T>
class DynArray 
{
private:
    T* data;      // Указатель на массив данных
    size_t size;  // Размер массива

public:
    // Конструктор по умолчанию
    DynArray() 
        : size(0), data(nullptr) 
    {}

    // Конструктор с инициализацией из списка
    DynArray(initializer_list<T> initList) 
        : size(initList.size()), data(new T[size]) 
    {
        copy(initList.begin(), initList.end(), data);  // Копируем элементы из списка в массив
    }

    // Конструктор копирования
    DynArray(const DynArray& other) 
        : size(other.size), data(new T[size]) 
    {
        copy(other.data, other.data + size, data);  // Копируем данные из другого объекта
    }

    // Конструктор перемещения (быстрое копирование данных)
    DynArray(DynArray&& other) noexcept 
        : size(other.size), data(other.data) 
    {
        other.size = 0;         // Обнуляем размер и указатель другого объекта
        other.data = nullptr;
    }

    // Деструктор (освобождение памяти)
    ~DynArray() 
    {
        delete[] data;  // Освобождаем выделенную память
    }

    // Перегрузка оператора () для получения размера массива
    size_t operator()() const 
    {
        return size;  // Возвращаем размер массива
    }

    // Перегрузка оператора () для добавления элемента в конец массива
    void operator()(const T& value) 
    {
        T* newData = new T[size + 1];     // Создаем новый массив на 1 элемент больше
        copy(data, data + size, newData); // Копируем данные из старого массива
        newData[size] = value;            // Добавляем новый элемент в конец
        delete[] data;                    // Освобождаем старый массив
        data = newData;                   // Переключаем указатель на новый массив
        size++;                           // Увеличиваем размер
    }

    // Перегрузка оператора [] для доступа к элементам массива
    T& operator[](size_t index) 
    {
        if (index >= size) 
        {
            throw out_of_range("Индекс вне допустимого диапазона");  // Генерируем исключение, если индекс недопустим
        }
        return data[index];  // Возвращаем элемент по индексу
    }

    // Перегрузка оператора присваивания для копирования
    DynArray& operator=(const DynArray& other) 
    {
        if (this == &other) 
        {
            return *this;  // Проверка на самоприсваивание
        }
        delete[] data;    // Освобождаем текущие данные
        size = other.size;      // Копируем размер
        data = new T[size];     // Выделяем память под новые данные
        copy(other.data, other.data + size, data);  // Копируем данные из другого объекта
        return *this;    // Возвращаем ссылку на текущий объект
    }

    // Перегрузка оператора присваивания для перемещения
    DynArray& operator=(DynArray&& other) noexcept 
    {
        if (this == &other) 
        {
            return *this;  // Проверка на самоприсваивание
        }
        delete[] data;    // Освобождаем текущие данные
        size = other.size;      // Копируем размер
        data = other.data;      // Копируем указатель на данные
        other.size = 0;         // Обнуляем размер и указатель другого объекта
        other.data = nullptr;
        return *this;    // Возвращаем ссылку на текущий объект
    }

    // Дружественная функция для вывода данных в поток
    friend ostream& operator<<(ostream& os, const DynArray& arr) 
    {
        os << '[';
        for (size_t i = 0; i < arr.size; i++) 
        {
            os << arr.data[i];             // Выводим элементы массива
            if (i < arr.size - 1) 
            {
                os << ", ";                // Разделяем элементы запятой
            }
        }
        os << ']';
        return os;
    }
};

// Объявляем шаблонный класс DynArrayNum, который наследуется от DynArray
template <typename T>
class DynArrayNum : public DynArray<T> 
{
public:
    // Конструктор с инициализацией из списка
    DynArrayNum(initializer_list<T> initList) 
        : DynArray<T>(initList) 
    {}

    // Перегрузка оператора + для попарного сложения
    DynArrayNum operator+(const DynArrayNum& other) const 
    {
        if (this->() != other()) 
        {
            throw invalid_argument("Массивы должны иметь одинаковый размер для сложения.");  // Генерируем исключение при неравных размерах
        }

        DynArrayNum result;                // Создаем новый объект DynArrayNum для результата
        for (size_t i = 0; i < this->(); i++) 
        {
            result(this->operator[](i) + other[i]);  // Складываем элементы попарно и добавляем в результат
        }
        return result;                    // Возвращаем результат
    }

    // Перегрузка оператора - для попарного вычитания
    DynArrayNum operator-(const DynArrayNum& other) const 
    {
        if (this->() != other()) 
        {
            throw invalid_argument("Массивы должны иметь одинаковый размер для вычитания.");  // Генерируем исключение при неравных размерах
        }

        DynArrayNum result;                // Создаем новый объект DynArrayNum для результата
        for (size_t i = 0; i < this->(); i++) 
        {
            result(this->operator[](i) - other[i]);  // Вычитаем элементы попарно и добавляем в результат
        }
        return result;                    // Возвращаем результат
    }

    // Перегрузка оператора * для попарного умножения
    DynArrayNum operator*(const DynArrayNum& other) const 
    {
        if (this->() != other()) 
        {
            throw invalid_argument("Массивы должны иметь одинаковый размер для умножения.");  // Генерируем исключение при неравных размерах
        }

        DynArrayNum result;                // Создаем новый объект DynArrayNum для результата
        for (size_t i = 0; i < this->(); i++) 
        {
            result(this->operator[](i) * other[i]);  // Умножаем элементы попарно и добавляем в результат
        }
        return result;                    // Возвращаем результат
    }

    // Используем оператор () из базового класса для добавления элемента в конец массива
    using DynArray<T>::operator();
};

int main() 
{
    DynArrayNum<int> arr1 = { 1, 2, 3 };      // Создаем объект DynArrayNum<int> с инициализацией
    DynArrayNum<int> arr2 = { 4, 5, 6 };      // Создаем еще один объект

    DynArrayNum<int> sum = arr1 + arr2;     // Складываем элементы попарно и сохраняем результат
    cout << "Сумма : " << sum << endl;         // Выводим результат

    DynArrayNum<int> diff = arr1 - arr2;    // Вычитаем элементы попарно и сохраняем результат
    cout << "Разность: " << diff << endl; // Выводим результат

    DynArrayNum<int> product = arr1 * arr2; // Умножаем элементы попарно и сохраняем результат
    cout << "Произведение: " << product << endl; // Выводим результат

    return 0;  // Завершаем программу
}