// ДЗ #18 до 12.10.23_Функторы, предикаты, алгоритмы, контейнеры
/*
Задание 1. Создайте приложение для работы автосалона. Необходимо хранить
информацию о продаваемых автомобилях (название, год выпуска, объем двигателя,
цену). Реализуйте интерфейс для добавления данных, удаления данных,
отображения данных, сортировке данных по различным параметрам, поиску
данных по различным параметрам. При реализации используйте контейнеры,
функторы и алгоритмы.
*/


#include <iostream>     // Включаем заголовочный файл для ввода-вывода
#include <vector>       // Включаем заголовочный файл для использования векторов
#include <algorithm>    // Включаем заголовочный файл для использования алгоритмов STL

using namespace std;    // Используем пространство имен std

class Car
{
private:
    string name;
    double engineVolume;
    int year;
    double price;

public:
    // Конструктор класса Car для инициализации полей объекта
    Car(const string& carName, double carEngineVolume, int carYear, double carPrice)
        : name(carName), engineVolume(carEngineVolume), year(carYear), price(carPrice) {}

    // Геттеры для получения значений полей
    const string& getName() const
    {
        return name;
    }

    double getEngineVolume() const
    {
        return engineVolume;
    }

    int getYear() const
    {
        return year;
    }

    double getPrice() const
    {
        return price;
    }

    // Метод для отображения информации об автомобиле
    void display() const
    {
        cout << "Название: " << name << "\tГод выпуска: " << year
            << "\tОбъем двигателя: " << engineVolume << "\tЦена в $: " << price << endl;
    }
};

// Функторы для сравнения объектов класса Car
class CompareByName
{
public:
    // Перегруженный оператор () для сравнения по имени
    bool operator()(const Car& a, const Car& b) const
    {
        return a.getName() < b.getName();
    }
};

class CompareByEngineVolume
{
public:
    // Перегруженный оператор () для сравнения по объему двигателя
    bool operator()(const Car& a, const Car& b) const
    {
        return a.getEngineVolume() < b.getEngineVolume();
    }
};

class CompareByYear
{
public:
    // Перегруженный оператор () для сравнения по году выпуска
    bool operator()(const Car& a, const Car& b) const
    {
        return a.getYear() < b.getYear();
    }
};

class CompareByPrice
{
public:
    // Перегруженный оператор () для сравнения по цене
    bool operator()(const Car& a, const Car& b) const
    {
        return a.getPrice() < b.getPrice();
    }
};

class CarDealer
{
private:
    vector<Car> cars;   // Вектор для хранения объектов класса Car

public:
    // Метод для добавления автомобиля в список
    void addCar(const Car& car)
    {
        cars.push_back(car);
    }

    // Метод для удаления автомобиля из списка по имени
    void removeCar(const string& carName)
    {
        // Используем remove_if и лямбда-выражение для поиска и удаления
        auto it = remove_if(cars.begin(), cars.end(), [&carName](const Car& car)
            {
                return car.getName() == carName;
            });

        // Если найден автомобиль, удаляем его
        if (it != cars.end())
        {
            cars.erase(it, cars.end());
            cout << "Автомобиль удален.\n";
        }
        else
        {
            cout << "Автомобиль не найден.\n";
        }
    }

    // Метод для отображения информации обо всех автомобилях в списке
    void displayAllCars() const
    {
        cout << "\nСписок автомобилей:\n";
        for (const auto& car : cars)
        {
            car.display();
        }
    }

    // Геттер для получения списка автомобилей
    vector<Car>& getCars()
    {
        return cars;
    }
};

class CarSortSearch
{
public:
    // Метод для сортировки списка по указанному параметру с использованием функтора
    template <typename Functor>
    static void sortByParameter(vector<Car>& cars, Functor comparator)
    {
        sort(cars.begin(), cars.end(), comparator);
    }

    // Метод для поиска по указанному параметру с использованием функтора
    template <typename Functor>
    static void searchByParameter(const vector<Car>& cars, const Functor& comparator, const typename vector<Car>::value_type& targetValue)
    {
        auto it = find_if(cars.begin(), cars.end(), [&comparator, &targetValue](const Car& car)
            {
                return comparator(car, targetValue);
            });

        if (it != cars.end())
        {
            cout << "Автомобиль найден:\n";

            for (const auto& car : cars)
            {
                if (comparator(car, targetValue))
                {
                    car.display();
                }
            }
        }
        else
        {
            cout << "Автомобиль не найден.\n";
        }
    }
};

class MainMenu
{
public:
    // Метод для отображения главного меню и ввода выбора пользователя
    int displayMenu() const
    {
        int choice;

        do
        {
            cout << "***********   Автосалон 'У Макса'   ***********\n";
            cout << "\nМеню:\n";
            cout << "1. Добавить автомобиль\n";
            cout << "2. Удалить автомобиль\n";
            cout << "3. Отобразить все автомобили\n";
            cout << "4. Сортировать по названию\n";
            cout << "5. Сортировать по объему двигателя\n";
            cout << "6. Сортировать по году выпуска\n";
            cout << "7. Сортировать по цене\n";
            cout << "8. Поиск по названию\n";
            cout << "9. Поиск по объему двигателя\n";
            cout << "10. Поиск по году выпуска\n";
            cout << "11. Поиск по по цене\n";
            cout << "12. Выйти из программы\n";
            cout << "\nВыберите операцию: ";

            cin >> choice;

        } while (choice < 0 || choice > 12);

        return choice;
    }
};

int main()
{
    setlocale(LC_ALL, "Rus");    // Устанавливаем русскую локаль для корректного отображения текста
    int answer;                  // Переменная для хранения выбора пользователя
    MainMenu menu;               // Объект главного меню
    CarDealer carDealer;         // Объект автосалона

    do
    {
        system("cls");           // Очищаем консоль перед отображением меню
        answer = menu.displayMenu();  // Отображаем меню и получаем выбор пользователя

        // Обработка выбора пользователя
        if (answer == 1)
        {
            // Добавить автомобиль
            string name;
            double engineVolume;
            int year;
            double price;

            cout << "Введите название автомобиля (одно слово!): ";
            cin >> name;
            cout << "Введите объем двигателя: ";
            cin >> engineVolume;
            cout << "Введите год выпуска: ";
            cin >> year;
            cout << "Введите цену: ";
            cin >> price;

            Car car(name, engineVolume, year, price);
            carDealer.addCar(car);
        }
        else if (answer == 2)
        {
            // Удалить автомобиль
            string name;
            cout << "Введите название автомобиля для удаления: ";
            cin >> name;
            carDealer.removeCar(name);
        }
        else if (answer == 3)
        {
            // Отобразить все автомобили
            carDealer.displayAllCars();
        }
        else if (answer == 4)
        {
            // Сортировать по названию
            CarSortSearch::sortByParameter(carDealer.getCars(), CompareByName());
        }
        else if (answer == 5)
        {
            // Сортировать по объему двигателя
            CarSortSearch::sortByParameter(carDealer.getCars(), CompareByEngineVolume());
        }
        else if (answer == 6)
        {
            // Сортировать по году выпуска
            CarSortSearch::sortByParameter(carDealer.getCars(), CompareByYear());
        }
        else if (answer == 7)
        {
            // Сортировать по цене
            CarSortSearch::sortByParameter(carDealer.getCars(), CompareByPrice());
        }
        else if (answer == 8)
        {
            // Поиск по названию
            string name;
            cout << "Введите название для поиска: ";
            cin >> name;
            CarSortSearch::searchByParameter(carDealer.getCars(), CompareByName(), Car(name, 0.0, 0, 0.0));
        }
        else if (answer == 9)
        {
            // Поиск по объему двигателя
            double engineVolume;
            cout << "Введите объем двигателя для поиска: ";
            cin >> engineVolume;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера
            CarSortSearch::searchByParameter(carDealer.getCars(), CompareByEngineVolume(), Car("", engineVolume, 0, 0.0));
        }
        else if (answer == 10)
        {
            // Поиск по году выпуска
            int year;
            cout << "Введите год выпуска для поиска: ";
            cin >> year;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера
            CarSortSearch::searchByParameter(carDealer.getCars(), CompareByYear(), Car("", 0.0, year, 0.0));
        }
        else if (answer == 11)
        {
            // Поиск по цене
            double price;
            cout << "Введите цену для поиска: ";
            cin >> price;
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Очистка буфера
            CarSortSearch::searchByParameter(carDealer.getCars(), CompareByPrice(), Car("", 0.0, 0, price));
        }

        system("pause");   // Пауза, чтобы пользователь мог прочитать результаты операции

    } while (answer != 12);  // Выход из программы при выборе 12

    return 0;  
}