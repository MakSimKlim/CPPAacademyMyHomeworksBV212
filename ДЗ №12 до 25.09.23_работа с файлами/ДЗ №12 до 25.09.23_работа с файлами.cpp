// ДЗ #12 до 25.09.23_работа с файлами
//
// Задание 1. Программа открывает указанный пользователем файл текстовым
// способом и считывает построчно.Каждая строчка шифруется шифром Цезаря
// со сдвигом, также указанным пользователем и записывается в другой файл
// бинарным способом
// 

#define _CRT_SECURE_NO_WARNINGS 0; // чтобы не было ошибки на fopen

#include <iostream>
#include <cstdio>
#include <string>

using namespace std;

// Функция для шифрования строки шифром Цезаря
string CesarCipher(const string& input, int shift) 
{
    // Создаем копию входной строки
    string result = input;

    // Проходим по каждому символу в строке
    for (char& c : result) 
    {
        // Проверяем, является ли символ буквой
        if (isalpha(c)) 
        {
            // Определяем базовую букву (верхний или нижний регистр)
            char base = isupper(c) ? 'A' : 'a';
            // Применяем шифр Цезаря с учетом сдвига
            c = ((c - base + shift) % 26) + base;
        }
    }

    // Возвращаем зашифрованную строку
    return result;
}
// функция копирования и шифрования файла
bool copyAndEncryptFile(const char* source, const char* dest, int shift) 
{
    FILE* src, * dst;

    // Открытие файла для чтения
    if (!(src = fopen(source, "rb"))) 
    {
        cerr << "Не удалось открыть входной файл." << endl;
        return false;
    }

    // Открытие файла для записи в бинарном режиме
    if (!(dst = fopen(dest, "wb"))) 
    {
        cerr << "Не удалось открыть выходной файл." << endl;
        fclose(src);
        return false;
    }

    char data;

    // Копируем данные и шифруем
    while (fread(&data, sizeof(char), 1, src) == 1) 
    {
        if (isalpha(data)) 
        {
            data = CesarCipher(string(1, data), shift)[0];
        }
        fwrite(&data, sizeof(char), 1, dst);
    }

    // Закрываем файлы
    fclose(src);
    fclose(dst);

    return true;
}

int main() 
{
    setlocale(LC_ALL, "Rus");
    string inputFileName, outputFileName;
    int shift;

    // Ввод имени входного файла, имени выходного файла и сдвига с клавиатуры
    cout << "Введите имя файла для чтения: ";
    cin >> inputFileName;

    cout << "Введите имя файла для записи (бинарный): ";
    cin >> outputFileName;

    cout << "Введите сдвиг для шифра Цезаря: ";
    cin >> shift;

    // Вызываем функцию копирования и шифрования файла
    if (copyAndEncryptFile(inputFileName.c_str(), outputFileName.c_str(), shift)) 
    {
        cout << "Шифрование и запись в бинарный файл завершены успешно." << endl;
    }
    else 
    {
        cerr << "Не удалось скопировать и зашифровать файл." << endl;
    }

    return 0; // Завершаем программу с кодом возврата 0
}
