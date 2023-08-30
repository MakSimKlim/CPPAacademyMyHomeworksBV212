// ДЗ№3 срок до 03.09.23 (полиморфизм - матрица)
//
 //Задание 1. Создайте шаблонный класс матрица. 
 //Необходимо реализовать:
 //- динамическое выделение памяти, 
 //- очистку памяти, 
 //- заполнение матрицы с клавиатуры, 
 //- заполнение случайными значениями, 
 //- отображение матрицы,
 //- арифметиче ские операции с помощью перегруженных операторов(+, –, *, / ) 
 //- поиск минимального и максимального элемента
// 
// https://www.bestprog.net/ru/2019/08/23/c-an-example-of-creating-a-template-class-matrix-dynamic-memory-allocation-ru/

#include <iostream>
#include <list> // Подключаем заголовок для работы с контейнером list
#include <cstdlib>
#include <ctime>

using namespace std;

template <typename T>
class Matrix 
{
private:
    int rows; // Количество строк в матрице
    int cols; // Количество столбцов в матрице
    list<list<T>> data; // Контейнер для хранения данных матрицы

public:
    Matrix(int rows, int cols) : rows(rows), cols(cols), data(rows, list<T>(cols)) {}
    // Конструктор класса. Создаем матрицу с заданным числом строк и столбцов, 
    // инициализируем контейнер data с указанными размерами

    void fillFromKeyboard() 
    {
        cout << "Введите элементы матрицы:\n";
        for (auto& row : data) / Перебираем строки матрицы
        { /
            for (int j = 0; j < cols; ++j) // Перебираем столбцы в текущей строке
            { 
                T element;
                cin >> element; // Считываем элемент с клавиатуры
                row.push_back(element); // Добавляем элемент в текущую строку
            }
        }
    }

    void fillRandom() 
    {
        srand(time(nullptr));
        for (auto& row : data) // Перебираем строки матрицы
        { 
            for (int j = 0; j < cols; ++j) // Перебираем столбцы в текущей строке
            { 
                row.push_back(static_cast<T>(rand() % 100)); // Генерируем случайное значение и добавляем его в текущую строку
            }
        }
    }

    void display() const 
    {
        for (const auto& row : data) { // Перебираем строки матрицы
            for (const T& element : row) { // Перебираем элементы в текущей строке
                cout << element << " "; // Выводим элемент на экран с пробелом
            }
            cout << "\n"; // Переходим на новую строку после вывода строки матрицы
        }
    }

    // сложение элементов
    Matrix<T> operator+(const Matrix<T>& other) const 
    {
        if (rows != other.rows || cols != other.cols) 
        {
            throw std::invalid_argument("Матрицы должны иметь одинаковые размеры для сложения.");
        }

        Matrix<T> result(rows, cols); // Создаем новую матрицу для хранения результата
        auto it1 = data.begin();
        auto it2 = other.data.begin();
        auto itResult = result.data.begin();

        while (it1 != data.end() && it2 != other.data.end()) 
        {
            auto& row1 = *it1;
            auto& row2 = *it2;
            auto& resultRow = *itResult;

            auto elementIt1 = row1.begin();
            auto elementIt2 = row2.begin();
            auto elementItResult = resultRow.begin();

            while (elementIt1 != row1.end() && elementIt2 != row2.end()) 
            {
                *elementItResult = *elementIt1 + *elementIt2;
                ++elementIt1;
                ++elementIt2;
                ++elementItResult;
            }

            ++it1;
            ++it2;
            ++itResult;
        }

        return result;
    }

    // Аналогично, вы можете реализовать другие арифметические операции (-, *, /)

    T findMin() const 
    {
        T minVal = data.front().front(); // Инициализируем минимальное значение значением первого элемента
        for (const auto& row : data) // Перебираем строки матрицы
        { 
            for (const T& element : row) // Перебираем элементы в текущей строке
            { 
                if (element < minVal) { // Если текущий элемент меньше текущего минимального значения
                    minVal = element; // Обновляем минимальное значение
                }
            }
        }
        return minVal; // Возвращаем найденное минимальное значение
    }

    T findMax() const 
    {
        T maxVal = data.front().front(); // Инициализируем максимальное значение значением первого элемента
        for (const auto& row : data) // Перебираем строки матрицы
        { 
            for (const T& element : row) // Перебираем элементы в текущей строке
            { 
                if (element > maxVal) // Если текущий элемент больше текущего максимального значения
                { 
                    maxVal = element; // Обновляем максимальное значение
                }
            }
        }
        return maxVal; // Возвращаем найденное максимальное значение
    }
};

int main() 
{
    setlocale(LC_ALL, "Rus");

    int rows, cols;
    std::cout << "Введите количество строк: ";
    std::cin >> rows;
    std::cout << "Введите количество столбцов: ";
    std::cin >> cols;

    Matrix<int> matrix1(rows, cols);
    matrix1.fillRandom();

    Matrix<int> matrix2(rows, cols);
    matrix2.fillRandom();

    std::cout << "Матрица 1:\n";
    matrix1.display();

    std::cout << "\nМатрица 2:\n";
    matrix2.display();

    Matrix<int> sum = matrix1 + matrix2;
    std::cout << "\nСумма матриц:\n";
    sum.display();

    std::cout << "\nМинимальный элемент в матрице 1: " << matrix1.findMin() << "\n";
    std::cout << "Максимальный элемент в матрице 2: " << matrix2.findMax() << "\n";

    return 0;
}