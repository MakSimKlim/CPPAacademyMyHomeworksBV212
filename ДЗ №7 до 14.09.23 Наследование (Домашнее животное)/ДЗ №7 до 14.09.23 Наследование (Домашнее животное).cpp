// ДЗ №7 до 14.09.23 Наследование (Домашнее животное)
//
//Задание 1. Создать базовый класс «Домашнее животное» и производные
//классы «Собака», «Кошка», «Попугай».С помощью конструктора
//установить имя каждого животного и его характеристики.

#include <iostream>
using namespace std;

class Animal // абстрактный класс, т.к. есть чисто виртуальная функция
{
public:
	string Name;
	Animal(string nameP) :Name{ nameP } {};
	virtual void Speak() = 0;//запрещено переопределние этой функции в дочерних классах, т.е int Speak выдаст ошибку
};

class Dog :public Animal
{
public:
	Dog(string nameP) : Animal{ nameP } {};
	virtual void Speak();
};

void Dog::Speak()
{
	cout << Name << "говорит гав - гав" << endl;
}

class Cat :public Animal
{
public:
	Cat(string nameP) : Animal{ nameP } {};
	virtual void Speak();
};
void Cat::Speak()
{
	cout << Name << "говорит мяу - мяу" << endl;
}

class Parrot :public Animal
{
public:
	Parrot(string nameP) : Animal{ nameP } {};
	virtual void Speak();
};

void Parrot::Speak()
{
	cout << Name << "говорит Кеша хороший" << endl;
}

int main()
{
	setlocale(LC_ALL, "Rus");
	Animal* animals[3] = {
		new Dog("Шарик "),
		new Cat("Муся "),
		new Parrot("Кеша "),
	};

	for (int i = 0; i < 3; i++)
		animals[i]->Speak();


	return 0;

}
