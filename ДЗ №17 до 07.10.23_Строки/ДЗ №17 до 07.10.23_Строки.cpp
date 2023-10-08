// ДЗ #17 до 07.10.23_Строки
//
/*
Задание 1. Дана строка, содержащая пробелы. Найдите в ней самое длинное
слово, выведите это слово и его длину . Если таких слов несколько, выведите первое
из них.

Задание 2. Дана строка, содержащая пробелы. Найдите в ней количество
палиндромов

*/
/*
Самое длинное слово общего пользования:
Incomprehensibilities — непостижимость, необъятность. Это английское слово из 21 буквы установило рекорд в 1990-х годах как самое длинное слово «общего пользования». Если вы ещё не используете его – пора начинать!

Пример использования:
A careful examination of the particulars will show that there is no incomprehensibility or difficulty in them which has not a counterpart in nature.level hello mister kayak

*/


#include <iostream>
#include <string>
#include <vector>

using namespace std;

class LongestWordFinder 
{
public:
    // Конструктор класса, инициализирующий переменные
    LongestWordFinder(const string& inputString) : inputString(inputString) {}

    // Метод для нахождения самого длинного слова в строке
    void findLongestWord()
    {
        // Переменная для хранения самого длинного слова
        string longestWord;
        // Переменная для хранения длины самого длинного слова
        size_t maxLength = 0;
        // Индексы для отслеживания начала и конца текущего слова
        size_t start = 0;
        size_t end = 0;

        // Итерируемся по каждому символу в строке
        while (end <= inputString.length()) 
        {
            // Если встречаем пробел или достигаем конца строки
            if (inputString[end] == ' ' || end == inputString.length()) 
            {
                // Вычисляем текущую длину слова
                size_t currentLength = end - start;
                // Если текущее слово длиннее текущего самого длинного слова
                if (currentLength > maxLength) 
                {
                    // Обновляем переменные для самого длинного слова
                    maxLength = currentLength;
                    longestWord = inputString.substr(start, maxLength);
                }
                // Устанавливаем начало следующего слова
                start = end + 1;
            }
            // Переходим к следующему символу
            ++end;
        }
        // Выводим результаты на экран
        cout << "Самое длинное слово: " << longestWord << endl;
        cout << "Длина: " << maxLength << " символов." << endl;
    }

private:
    // переменная для хранения входной строки
    string inputString;
};

// Класс для подсчета палиндромов в строке
class PalindromeCounter 
{
public:
    // Конструктор, принимающий входную строку
    PalindromeCounter(const string& inputString) : inputString(inputString) {}

    // Метод для подсчета палиндромов в строке
    void countPalindromes() 
    {
        // Разбиваем строку на слова
        vector<string> words = splitString(inputString);

        // Переменная для хранения количества палиндромов
        size_t palindromeCount = 0;

        cout << "Палиндромы:" << endl;

        // Итерируемся по каждому слову
        for (const auto& word : words) 
        {
            // Если слово является палиндромом, увеличиваем счетчик
            if (isPalindrome(word)) 
            {
                ++palindromeCount;
                cout << word << endl;
            }
        }

        // Выводим количество найденных палиндромов
        cout << "Количество палиндромов: " << palindromeCount << endl;
    }

private:
    // переменная входной строки
    string inputString;

    // Метод для разбиения строки на слова
    vector<string> splitString(const string& str) 
    {
        vector<string> result;
        size_t start = 0;
        size_t end = 0;

        // Итерируемся по строке
        while (end <= str.length()) 
        {
            // Если встретили пробел или достигли конца строки, добавляем слово в результат
            if (str[end] == ' ' || end == str.length()) 
            {
                result.push_back(str.substr(start, end - start));
                start = end + 1;
            }
            ++end;
        }

        return result;
    }

    // Метод для проверки, является ли слово палиндромом
    bool isPalindrome(const string& str) 
    {
        if (str.length() == 1) 
        {
            // Исключаем слова из одной буквы
            return false;
        }
        // Инициализируем два указателя: один указывает на начало слова, другой - на конец
        size_t start = 0;
        size_t end = str.length() - 1;

        // Итерируемся с двух концов слова к его середине
        while (start < end) 
        {
            // Если символы на обоих концах не совпадают, слово не является палиндромом
            // Приводим символы к нижнему регистру перед сравнением с помощью функции tolower
            if (tolower(str[start]) != tolower(str[end]))
            {
                return false;
            }
            // Перемещаем указатели к центру слова
            ++start;
            --end;
        }

        // Если все пары символов совпали, слово является палиндромом
        return true;
    }
};

int main() 
{
    setlocale(LC_ALL, "Rus");

    // Устанавливаем русскую локаль для корректного отображения текста
    setlocale(LC_ALL, "Rus");

    // Задаем входную строку
    string inputString =
        "A careful examination of the particulars will show that there is no incomprehensibility "
        "or difficulty in them which has not a counterpart in nature."
        "Palindromes: Level hello AbBa mister kayak";

    cout << "Фраза: " << inputString << endl << endl;

    LongestWordFinder longestWordFinder(inputString);
    longestWordFinder.findLongestWord();
    cout << endl;

    // Создаем экземпляр класса PalindromeCounter, передавая входную строку
    PalindromeCounter palindromeCounter(inputString);
    // Вызываем метод для подсчета палиндромов
    palindromeCounter.countPalindromes();    
    
    return 0;
}

