// ДЗ№2 перегрузка операторов вводв и вывода
//
// Задание 1. В ранее реализованный класс String добавьте перегрузку
// операторов >> и << для ввода и вывода строки в поток.
// 
// Задание 2. В класс String добавьте преобразование строки в тип int.
// Результирующее число должно быть равно длине строки без учёта
// символа окончания строки.
//
//

#include <iostream>
#include <cstring>
#include <string>
#include <windows.h> // для setconsoleCP

using namespace std;

class String
{
private:
    char* data;                               // Указатель на массив символов (строку)
    size_t length;                            // Длина строки

public:
    // Конструктор по умолчанию
    String() : data(nullptr), length(0) {}

    // Конструктор класса
    String(const char* str)     
    {
        length = strlen(str);                 // Вычисляем длину строки
        data = new char[length + 1];          // Выделяем память для копии строки (+1 для нулевого символа)
        strcpy_s(data, length + 1, str);      // Копируем переданную строку в выделенную память
    }

    // Деструктор класса
    ~String()
    {
        //delete[] data;                        // Освобождаем память при удалении объекта
    }

    // Перегрузка оператора ()
    int operator()(char target) const
    {
        for (size_t i = 0; i < length; ++i)   // Проходим по каждому символу строки
        {
            if (data[i] == target)            // Если символ совпадает с целевым символом
            {
                //return int(i);                // Возвращаем индекс символа (приведение к int)
                return static_cast<int>(i);
            }
        }
        return -1;                            // Если символ не найден, возвращаем -1
    }

    // Перегрузка оператора преобразования в int, возвращает длину строки
    operator int() const
    {
        return static_cast<int>(length);
    }

    // Дружественная функция - перегрузка оператора вывода (<<)
    friend ostream& operator<<(ostream& os, const String& str);

    // Дружественная функция - перегрузка оператора ввода (>>)
    friend istream& operator>>(istream& is, String& str);
};

// Перегрузка оператора вывода (<<) для объекта String
ostream& operator<<(ostream& os, const String& str)
{
    os << str.data;// Выводим строку на поток
    return os;
}

// Перегрузка оператора ввода (>>) для объекта String
istream& operator>>(istream& is, String& str)
{
    char buffer[4096]; // Буфер для ввода строки
    is.getline(buffer, sizeof(buffer)); // Считываем строку до символа новой строки
    //is >> buffer;// Чтение строки из потока
    str = String(buffer);// Присваиваем объекту String значение из буфера
    return is;
}

int main()
{
    //setlocale(LC_ALL, "Rus");
    SetConsoleCP(1251);                                   // установка кодовой страницы win-cp 1251 в поток ввода
    SetConsoleOutputCP(1251);                             // установка кодовой страницы win-cp 1251 в поток вывода


    String myString("Привет, мир!");
    cout << "Длина строки: " << myString << " = " << int(myString) << endl << endl;
    
    String inputString;
    cout << "Введите предложение, слово или символ: ";
    cin >> inputString;// Здесь мы считываем слово, а не всю строку
    cout << "Вы ввели: " << inputString << endl;


    return 0;
}