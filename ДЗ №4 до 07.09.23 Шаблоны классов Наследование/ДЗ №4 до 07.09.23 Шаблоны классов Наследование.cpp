// ДЗ №4 до 07.09.23 Шаблоны классов Наследование.
//
//Задание 1. Создайте шаблонный класс DynArray , который будет хранить
//динамический массив данных, тип которых является шаблонным. Для
//него нужно перегрузить операторы() (перегрузка без параметров
//возвращает длину массива, если передаётся один параметр - добавляет
//этот элемент в конец массива), [], = (копирующее и перемещающее) и << .
//Также определите для него конструктор с использованием
//std::initalizer_list.
// 
//Задание 2. Создайте наследника от этого класса DynArrayNum, для
//которого перегружены операторы + (попарно складывает два массива с
//начала, элементы без пары просто добавляются в новый массив без
//изменений), -(такое же попарное вычитание) и * (попарное умножение).

#include <iostream>
#include <initializer_list>
#include <algorithm> // для max(). Эта функция возвращают максимальное из заданных значений.

// Включаем пространство имен std, чтобы не писать std:: перед элементами из стандартной библиотеки
using namespace std;

template <typename T>
class DynArray 
{
private:
    T* data; // Указатель на динамический массив
    size_t size; // Текущий размер массива
    size_t capacity; // Емкость массива (сколько элементов можно хранить без перевыделения памяти)

public:
    // Конструктор по умолчанию
    DynArray() : data(nullptr), size(0), capacity(0) {}

    // Конструктор с инициализацией через список инициализации
    DynArray(initializer_list<T> initList) : size(initList.size()), capacity(initList.size()) 
    {
        data = new T[capacity];
        copy(initList.begin(), initList.end(), data);
    }

    // Конструктор копирования
    DynArray(const DynArray& other) : size(other.size), capacity(other.capacity) 
    {
        data = new T[capacity];
        copy(other.data, other.data + size, data);
    }

    // Конструктор перемещения
    DynArray(DynArray&& other) noexcept : data(other.data), size(other.size), capacity(other.capacity) 
    {
        other.data = nullptr;
        other.size = 0;
        other.capacity = 0;
    }

    // Деструктор для освобождения памяти
    ~DynArray() 
    {
        delete[] data;
    }

    // Возвращает текущую длину массива
    size_t Length() const 
    {
        return size;
    }

    // Добавляет элемент в конец массива, автоматически увеличивая емкость массива 
    // и управляя выделением и освобождением памяти, если это необходимо.
    void Add(const T& element) 
        {
        //Это условие проверяет, достигла ли текущая длина массива(size) его емкости(capacity).
        //Если да, это означает, что массив заполнился, и требуется выделить больше памяти.
        if (size >= capacity) 
        {
            // Увеличиваем capacity при необходимости
            // Если массив пуст (емкость равна нулю), 
            // то устанавливаем емкость в 1 элемент, чтобы начать. 
            // В противном случае, мы удваиваем текущую емкость, чтобы увеличить место для добавления новых элементов.
            capacity = (capacity == 0) ? 1 : capacity * 2; 

            //Здесь создается новый динамический массив (new_data) с учетом увеличенной емкости. 
            //Мы выделяем память для массива, которая соответствует новой емкости.
            T* new_data = new T[capacity];

            //далее копируем существующие элементы из текущего массива data в новый массив new_data. 
            //Это гарантирует, что все существующие элементы сохраняются в новом массиве.
            copy(data, data + size, new_data);

            // Мы освобождаем память, ранее выделенную для текущего массива data, чтобы избежать утечки памяти. 
            // Теперь data больше не указывает на этот массив.
            delete[] data;

            // Мы обновляем указатель data, чтобы он указывал на новый массив new_data, 
            //который теперь содержит старые элементы и место для нового элемента.
            data = new_data;
        }
        // Мы добавляем новый элемент element в конец массива data и затем 
        // увеличиваем size на 1, чтобы указать, что массив теперь содержит один элемент больше.
        data[size++] = element;
    }

    // Перегрузка оператора [] для доступа к элементу по индексу
    T& operator[](size_t index) 
    {
        if (index < size) 
        {
            return data[index];
        }
        else 
        {
            throw out_of_range("Индекс за пределами массива");
        }
    }

    // Перегрузка оператора [] для доступа к элементу по индексу (константная версия)
    const T& operator[](size_t index) const 
    {
        if (index < size) 
        {
            return data[index];
        }
        else 
        {
            throw out_of_range("Индекс за пределами массива");
        }
    }

    // Перегрузка оператора присваивания для копирования
    DynArray& operator=(const DynArray& other) 
    {
        if (this != &other) 
        {
            delete[] data;
            size = other.size;
            capacity = other.capacity;
            data = new T[capacity];
            copy(other.data, other.data + size, data);
        }
        return *this;
    }

    // Перегрузка оператора присваивания для перемещения
    DynArray& operator=(DynArray&& other) noexcept 
    {
        if (this != &other) 
        {
            delete[] data;
            data = other.data;
            size = other.size;
            capacity = other.capacity;
            other.data = nullptr;
            other.size = 0;
            other.capacity = 0;
        }
        return *this;
    }

    // Перегрузка оператора вывода для вывода элементов массива
    friend ostream& operator<<(ostream& os, const DynArray& arr) 
    {
        for (size_t i = 0; i < arr.size; ++i) 
        {
            os << arr.data[i] << ' ';
        }
        return os;
    }
};

// Класс DynArrayNum наследует от DynArray и добавляет перегрузку операторов +, -, и *
template <typename T>
class DynArrayNum : public DynArray<T> 
{
public:
    // Конструктор для попарных операций и добавления элементов без пары
    DynArrayNum(const DynArray<T>& arr1, const DynArray<T>& arr2, char operation) 
    {
        size_t size1 = arr1.Length();
        size_t size2 = arr2.Length();
        size_t maxSize = max(size1, size2);

        for (size_t i = 0; i < maxSize; ++i) 
        {
            T element1 = (i < size1) ? arr1[i] : T();
            T element2 = (i < size2) ? arr2[i] : T();

            if (element1 != T() && element2 != T()) 
            {
                T result;
                if (operation == '+') 
                {
                    result = element1 + element2;
                }
                else if (operation == '-') 
                {
                    result = element1 - element2;
                }
                else if (operation == '*') 
                {
                    result = element1 * element2;
                }
                else 
                {
                    throw invalid_argument("Недопустимая операция");
                }
                // Добавляем результат в DynArrayNum только если оба элемента пары не равны T()
                this->Add(result);
            }
            else if (element1 != T()) 
            {
                this->Add(element1);
            }
            else if (element2 != T()) 
            {
                this->Add(element2);
            }
        }
    }

    // Конструктор для добавления элементов без пары
    DynArrayNum(const DynArray<T>& arr, char operation) 
    {
        size_t size = arr.Length();
        for (size_t i = 0; i < size; ++i) 
        {
            this->Add(arr[i]);
        }
    }

    // Перегрузка оператора + для DynArrayNum
    DynArrayNum<T> operator+(const DynArrayNum<T>& other) const 
    {
        const DynArray<T>& arr1 = *this;
        const DynArray<T>& arr2 = other;
        return DynArrayNum<T>(arr1, arr2, '+');
    }

    // Перегрузка оператора - для DynArrayNum
    DynArrayNum<T> operator-(const DynArrayNum<T>& other) const 
    {
        const DynArray<T>& arr1 = *this;
        const DynArray<T>& arr2 = other;
        return DynArrayNum<T>(arr1, arr2, '-');
    }

    // Перегрузка оператора * для DynArrayNum
    DynArrayNum<T> operator*(const DynArrayNum<T>& other) const 
    {
        const DynArray<T>& arr1 = *this;
        const DynArray<T>& arr2 = other;
        return DynArrayNum<T>(arr1, arr2, '*');
    }
};

int main() 
{
    // Устанавливаем локаль для корректного вывода на русском языке
    setlocale(LC_ALL, "Rus");

    // Создаем объект DynArray и инициализируем его с помощью списка инициализации
    DynArray<int> arr = { 1, 2, 3, 4 };

    // Выводим начальный массив
    cout << "1) Исходный массив: " << arr << endl;

    // Выводим длину массива
    cout << "2) Длина массива: " << arr.Length() << endl;

    // Добавляем элемент в конец массива и выводим его
    arr.Add(5);
    cout << "3) Массив после добавления 5: " << arr << endl;

    // Изменяем элемент массива и выводим его
    arr[2] = 42;
    cout << "4) Массив после замены arr[2] на 42: " << arr << endl;

    // Создаем копию массива и выводим ее
    DynArray<int> arr2;
    arr2 = arr;
    cout << "5) Копия массива: " << arr2 << endl;

    // Создаем перемещенную версию массива и выводим ее
    DynArray<int> arr3 = move(arr2);
    cout << "6) Перемещенный массив: " << arr3 << endl;

    // массивы для реализации наследника класса DynArrayNum
    DynArray<int> arr4 = { 1, 2, 1};
    DynArray<int> arr5 = { 2, 1, 2, 3, 4 };

    cout << "массивы для реализации наследника класса DynArrayNum:" << endl;
    cout << "7) Массив №1: " << arr4 << endl;
    cout << "8) Массив №2: " << arr5 << endl;
    cout << endl;

    // Создаем объекты DynArrayNum, который выполнит операции попарно
    DynArrayNum<int> addition(arr4, arr5, '+');
    DynArrayNum<int> subtraction(arr4, arr5, '-');
    DynArrayNum<int> multiplication(arr4, arr5, '*');

    cout << "Результаты попарного " << endl;
    cout << "- сложения: " << addition << endl;
    cout << "- вычитания: " << subtraction << endl;
    cout << "- умножения: " << multiplication << endl;
    cout << "c добавлением элементов без пары в новый массив без изменений" << endl;

    return 0;
}
