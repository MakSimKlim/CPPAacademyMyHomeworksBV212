// ДЗ№3 Шаблонный класс Матрица
//

#include <iostream>
#include <time.h>   // Для генерации случайных чисел на основе времени

using namespace std;

// Создаем шаблонный класс Matrix
template <typename T>
class Matrix {
private:
    int rows;     // Количество строк
    int columns;  // Количество столбцов
    T** data;     // Указатель на двумерный массив для хранения данных

public:
    // Конструктор класса Matrix
    Matrix(int rows, int columns) 
        : rows(rows), columns(columns) 
    {
        // Выделяем память для хранения данных
        data = new T * [rows];
        for (int i = 0; i < rows; ++i) 
        {
            data[i] = new T[columns];
        }
    }

    // Деструктор класса Matrix для освобождения памяти
    ~Matrix() 
    {
        delete[] data;
    }

    // Метод для заполнения матрицы с клавиатуры
    void fillFromKeyboard() 
    {
        cout << "Введите элементы матрицы:" << endl;
        for (int i = 0; i < rows; ++i) 
        {
            for (int j = 0; j < columns; ++j) 
            {
                cin >> data[i][j];
            }
        }
    }

    // Метод для заполнения матрицы случайными значениями
    void fillRandom() 
    {
        srand(time(0)); // Инициализация генератора случайных чисел текущим временем
        for (int i = 0; i < rows; ++i) 
        {
            for (int j = 0; j < columns; ++j) 
            {
                data[i][j] = rand() % 100; // Генерируем случайное число от 0 до 99
            }
        }
    }

    // Метод для отображения матрицы
    void display() 
    {
        for (int i = 0; i < rows; ++i) 
        {
            for (int j = 0; j < columns; ++j) 
            {
                cout << data[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Перегрузка оператора + для сложения матриц
    Matrix operator+(const Matrix& other) 
    {
        if (rows != other.rows || columns != other.columns) 
        {
            cout << "Невозможно сложить матрицы разных размеров." << endl; // сообщение при ошибке несоответствия размеров матриц
            exit(1); // Завершаем программу с ошибкой
        }

        Matrix result(rows, columns);
        for (int i = 0; i < rows; ++i) 
        {
            for (int j = 0; j < columns; ++j) 
            {
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }

    // Перегрузка оператора - для вычитания матриц
    Matrix operator-(const Matrix& other) 
    {
        if (rows != other.rows || columns != other.columns) 
        {
            cout << "Невозможно вычесть матрицы разных размеров." << endl;
            exit(1); // Завершаем программу с ошибкой
        }

        Matrix result(rows, columns);
        for (int i = 0; i < rows; ++i) 
        {
            for (int j = 0; j < columns; ++j) 
            {
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }

    // Перегрузка оператора * для умножения матриц
    Matrix operator*(const Matrix& other)
    {
        if (rows != other.rows || columns != other.columns)
        {
            cout << "Невозможно умножить матрицы заданых размеров." << endl;
            exit(1); // Завершаем программу с ошибкой
        }
       
        Matrix result(rows, columns);
        for (int i = 0; i < rows; ++i)
        {
            for (int j = 0; j < columns; ++j)
            {
                result.data[i][j] = data[i][j] * other.data[i][j];
            }
        }
        return result;
    }


    // Перегрузка оператора / для деления матриц
    Matrix operator/(const Matrix& other) 
    {
        if (rows != other.rows || columns != other.columns) 
        {
            cout << "Невозможно разделить матрицы разных размеров." << endl;
            exit(1); // Завершаем программу с ошибкой
        }

        Matrix result(rows, columns);
        for (int i = 0; i < rows; ++i) 
        {
            for (int j = 0; j < columns; ++j) 
            {
                if (other.data[i][j] == 0) {
                    cout << "Ошибка: деление на ноль." << endl;
                    exit(1); // Завершаем программу с ошибкой
                }
                result.data[i][j] = data[i][j] / other.data[i][j];
            }
        }
        return result;
    }

    // Метод для поиска минимального элемента в матрице
    T findMin() 
    {
        T min = data[0][0];
        for (int i = 0; i < rows; ++i) 
        {
            for (int j = 0; j < columns; ++j) 
            {
                if (data[i][j] < min) 
                {
                    min = data[i][j];
                }
            }
        }
        return min;
    }

    // Метод для поиска максимального элемента в матрице
    T findMax() 
    {
        T max = data[0][0];
        for (int i = 0; i < rows; ++i) 
        {
            for (int j = 0; j < columns; ++j) 
            {
                if (data[i][j] > max) 
                {
                    max = data[i][j];
                }
            }
        }
        return max;
    }
};

int main() 
{
    setlocale(LC_ALL, "Rus");
    
    int rows, columns;
    cout << "Введите количество строк и столбцов матрицы: " << endl;;
    cin >> rows >> columns;

    Matrix<double> matrix1(rows, columns); // Создаем матрицу с целыми числами
    matrix1.fillFromKeyboard();          // Заполняем матрицу с клавиатуры

    Matrix<double> matrix2(rows, columns);
    matrix2.fillRandom();                // Заполняем вторую матрицу случайными числами

    system("cls");// очистка экрана от предыдущих значений

    cout << "Первая матрица:" << endl;
    matrix1.display();

    cout << "Вторая матрица:" << endl;
    matrix2.display();

    Matrix<double> result1 = matrix1 + matrix2; // Складываем матрицы
    cout << "Сложение матриц:" << endl;
    result1.display();
    cout << endl;

    Matrix<double> result2 = matrix1 - matrix2; // Вычитаем матрицы
    cout << "Вычитание матриц:" << endl;
    result2.display();
    cout << endl;

    Matrix<double> result3 = matrix1 * matrix2; // Умножаем матрицы
    cout << "Произведение матриц:" << endl;
    result3.display();
    cout << endl;

    Matrix<double> result4 = matrix1 / matrix2; // Делим матрицы
    cout << "Деление матриц:" << endl;
    result4.display();
    cout << endl;

    cout << "Минимальный элемент в первой матрице: " << matrix1.findMin() << endl;
    cout << "Максимальный элемент во второй матрице: " << matrix2.findMax() << endl;

    return 0;
}