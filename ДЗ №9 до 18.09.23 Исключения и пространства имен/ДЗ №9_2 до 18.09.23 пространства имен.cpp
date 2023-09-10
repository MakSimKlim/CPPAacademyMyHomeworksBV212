// ДЗ №9_2 до 18.09.23 пространства имен
//

//Задание 2. Создайте пространство имён для вычислений на координатной
//плоскости, создайте там классы для точки и многоугольника. Создайте
//другое пространство имён для классов - хранилищ и создайте там классы
//для динамических массива и матрицы. В функции main() основного
//файла, матрицу, которая хранила бы точки, и функцию, которая
//превращала бы эту матрицу в многоугольник.

#include <iostream>
#include <cmath> // Для использования функции sqrt

// Используем пространство имён std
using namespace std;

// Создаем пространство имён для вычислений на координатной плоскости
namespace Coordinates 
{
    // Класс для представления точки на плоскости
    class Point 
    {
    public:
        double x, y; // Координаты точки

        // Конструктор для инициализации координат точки
        Point(double xCoord, double yCoord) : x(xCoord), y(yCoord) {}
    };

    // Класс для представления многоугольника на плоскости
    class Polygon 
    {
    public:
        // Конструктор для создания многоугольника с заданными вершинами
        Polygon(const Point* vertices, int numVertices) : vertices(vertices), numVertices(numVertices)  { }

        // Метод для вывода координат точек многоугольника
        void printVertices() 
        {
            cout << "Вершины многоугольника:" << endl;
            for (int i = 0; i < numVertices; i++) 
            {
                cout << "x: " << vertices[i].x << ", y: " << vertices[i].y << endl;
            }
        }

    private:
        const Point* vertices; // Массив вершин многоугольника
        int numVertices;       // Количество вершин
    };
}

// Создаем пространство имён для классов - хранилищ
namespace Storage 
{
    // Класс для динамического массива
    class DynamicArray 
    {
    public:
        // Конструктор для создания динамического массива с заданным размером
        DynamicArray(int size) { }
    };

    // Класс для матрицы
    class Matrix 
    {
    public:
        // Конструктор для создания матрицы с заданными размерами
        Matrix(int rows, int cols) { }
    };
}

int main() 
{
    setlocale(LC_ALL, "Rus");
    // Создаем матрицу для хранения точек
    Storage::Matrix pointMatrix(3, 2); // Например, 3 строки и 2 столбца для координат x и y

    // Создаем многоугольник из точек в матрице
    Coordinates::Point vertices[] = { Coordinates::Point(1.0, 2.0), Coordinates::Point(3.0, 4.0), Coordinates::Point(5.0, 6.0) };
    Coordinates::Polygon polygon(vertices, 3);

    // Выводим координаты точек многоугольника
    polygon.printVertices();

    return 0;
}



