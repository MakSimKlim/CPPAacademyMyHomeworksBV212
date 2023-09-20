// ДЗ #12 до 25.09.23_работа с файлами
//
// Задание 1. Программа открывает указанный пользователем файл текстовым
// способом и считывает построчно.Каждая строчка шифруется шифром Цезаря
// со сдвигом, также указанным пользователем и записывается в другой файл
// бинарным способом
// 

#define _CRT_SECURE_NO_WARNINGS 0; // чтобы не было ошибки на fopen

#include <iostream>
#include <fstream>
#include <string>
#include <io.h>

using namespace std;

// Функция для шифрования строки шифром Цезаря
string encryptCesarCipher(const string& input, int shift) 
{
    string result = input;                         // Создаем копию входной строки для шифрования
    for (char& c : result)                         // Итерируемся по каждому символу в строке
    { 
        if (isalpha(c)) 
        { 
            char base = isupper(c) ? 'A' : 'a';   // Определяем базовую букву ('A' для заглавных, 'a' для строчных)
            c = ((c - base + shift) % 26) + base; // Применяем шифр Цезаря с заданным сдвигом
        }
    }
    return result;                                // Возвращаем зашифрованную строку
}

int main() 
{
    setlocale(LC_ALL, "Rus");

    string inputFileName, outputFileName;
    int shift;

    cout << "Введите имя файла для чтения: ";
    cin >> inputFileName;

    //проверка существует ли этот файл
    // src_path.c_str() - конвертация в char (метод c_str)
    if (_access(inputFileName.c_str(), 00) == -1)
    {
        cout << "\nУказан неверный путь к файлу\n";
    }

    cout << "Введите имя файла для записи (бинарный): ";
    cin >> outputFileName;

    //если файл существкет, провери мего наперезапись
    if (_access(outputFileName.c_str(), 00) == 0)
    {
        cout << "Такой файл существует. Перезаписать? Y/N >";
        string answer;
        cin >> answer;
        if (answer.find_first_of("yYдД"))//если хотим перезаписать
        {
            if (_access(outputFileName.c_str(), 02) == -1) //проверка права на запись
            {
                cout << "\nНет прав записи файла.\n";
            }
        }
        else {
            cout << "\nОперация отменена!\n";

            return 0;
        }

    }

    cout << "Введите сдвиг для шифра Цезаря: ";
    cin >> shift;

    ifstream inputFile(inputFileName);                      // Создаем объект для чтения файла
    if (!inputFile) 
    {
        cerr << "Не удалось открыть входной файл." << endl; // Выводим сообщение об ошибке, если файл не удалось открыть
        return 1;                                           // Возвращаем код ошибки
    }

    ofstream outputFile(outputFileName, ios::binary);       // Создаем объект для записи в бинарный файл
    if (!outputFile) 
    {
        cerr << "Не удалось открыть выходной файл." << endl;// Выводим сообщение об ошибке, если файл не удалось открыть
        return 1;                                           // Возвращаем код ошибки
    }

    string line;

    while (getline(inputFile, line))                        // Считываем строки из входного файла по одной
    {
        // Шифруем строку и записываем в бинарный файл
        string encryptedLine = encryptCesarCipher(line, shift); // Вызываем функцию для шифрования
        outputFile.write(encryptedLine.c_str(), encryptedLine.size()); // Записываем зашифрованную строку в бинарный файл
        //outputFile.put(' ');  // Добавляем пробел между зашифрованными строками
    
    }

    // Закрываем файлы
    inputFile.close();
    outputFile.close();

    cout << "Шифрование завершено успешно." << endl;

    return 0;
}