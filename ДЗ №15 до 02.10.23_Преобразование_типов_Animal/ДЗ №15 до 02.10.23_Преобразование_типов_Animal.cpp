// ДЗ #15 до 02.10.23_Преобразование_типов_Animal
//
//Преобразование типов в С++.
//Напишите следующее приложение.В нём есть класс Animal,
//который может хранить имя животного, от которого унаследованы классы
//Lion, Mouse, Hippo, Elephant, Monkey и Crocodile.Пусть каждый класс
//выводит своё сообщение на экран унаследованным виртуальным методов,
//которое содержит имя животного и что оно делает, вроде <Name> toots its
//trunk, <Name> swings on the branch, <Name> hides in the river, и т.п.
//Создайте динамический массив указателей на Animal не менее, чем из 6
//указателей на животных, и поместите в него минимум по одному разному
//животному с помощью dynamic_cast.Затем, выведите от каждого животного
//его сообщение.Обратите внимание, что выводится на экран.
//

#include <iostream>
#include <string>

using namespace std;

// Базовый класс Animal
class Animal 
{
public:
    // Конструктор с параметром для установки имени животного
    Animal(const string& name) : name(name) {}

    // Виртуальная функция для вывода сообщения о действии животного
    virtual void action() const 
    {
        cout << "Animal action" << endl;
    }

protected:
    string name;  // Имя животного
};

// Класс Lion, наследующийся от Animal
class Lion : public Animal 
{
public:
    // Конструктор с параметром для установки имени льва
    Lion(const string& name) : Animal(name) {}

    // Реализация виртуальной функции action для льва
    void action() const override 
    {
        cout << name << " рычит в саванне" << endl;
    }
};

// Класс Mouse, наследующийся от Animal
class Mouse : public Animal 
{
public:
    // Конструктор с параметром для установки имени мыши
    Mouse(const string& name) : Animal(name) {}

    // Реализация виртуальной функции action для мыши
    void action() const override 
    {
        cout << name << " пищит в норке в поле" << endl;
    }
};

// Класс Hippo, наследующийся от Animal
class Hippo : public Animal 
{
public:
    // Конструктор с параметром для установки имени мыши
    Hippo(const string& name) : Animal(name) {}

    // Реализация виртуальной функции action для мыши
    void action() const override 
    {
        cout << name << " плавает в озере" << endl;
    }
};

// Класс Elephant, наследующийся от Animal
class Elephant : public Animal 
{
public:
    // Конструктор с параметром для установки имени мыши
    Elephant(const string& name) : Animal(name) {}

    // Реализация виртуальной функции action для мыши
    void action() const override 
    {
        cout << name << " шевелит ушами и хоботом" << endl;
    }
};

// Класс Monkey, наследующийся от Animal
class Monkey : public Animal 
{
public:
    // Конструктор с параметром для установки имени мыши
    Monkey(const string& name) : Animal(name) {}

    // Реализация виртуальной функции action для мыши
    void action() const override 
    {
        cout << name << " раскачивается на ветке" << endl;
    }
};

// Класс Crocodile, наследующийся от Animal
class Crocodile : public Animal 
{
public:
    // Конструктор с параметром для установки имени мыши
    Crocodile(const string& name) : Animal(name) {}

    // Реализация виртуальной функции action для мыши
    void action() const override 
    {
        cout << name << " поджидает жертву в реке" << endl;
    }
};


int main() 
{
    setlocale(LC_ALL, "Rus");
    // Создаем динамический массив указателей на Animal
    Animal* animals[6];

    // Создаем объекты различных классов с использованием dynamic_cast
    animals[0] = new Lion("лев Лёва");
    animals[1] = new Mouse("мышка Нарушка");
    animals[2] = new Hippo("гиппопотам Савелий");
    animals[3] = new Elephant("слон Валера");
    animals[4] = new Monkey("обезьянка Чича");
    animals[5] = new Crocodile("крокодил Гена");

    // Применяем dynamic_cast для безопасного приведения типов
    for (int i = 0; i < 6; ++i) {
        Lion* lion = dynamic_cast<Lion*>(animals[i]);
        Mouse* mouse = dynamic_cast<Mouse*>(animals[i]);
        Hippo* hippo = dynamic_cast<Hippo*>(animals[i]);
        Elephant* elephant = dynamic_cast<Elephant*>(animals[i]);
        Monkey* monkey = dynamic_cast<Monkey*>(animals[i]);
        Crocodile* crocodile = dynamic_cast<Crocodile*>(animals[i]);

        if (lion != nullptr) {
            lion->action();
        }
        else if (mouse != nullptr) {
            mouse->action();
        }
        else if (hippo != nullptr) {
            hippo->action();
        }
        else if (elephant != nullptr) {
            elephant->action();
        }
        else if (monkey != nullptr) {
            monkey->action();
        }
        else if (crocodile != nullptr) {
            crocodile->action();
        }
    }

    // Освобождаем память, выделенную под объекты
    for (int i = 0; i < 6; ++i) {
        delete animals[i];
    }

    return 0;
}