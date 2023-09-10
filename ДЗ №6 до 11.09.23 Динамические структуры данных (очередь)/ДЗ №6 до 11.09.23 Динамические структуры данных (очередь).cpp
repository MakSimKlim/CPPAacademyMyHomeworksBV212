// ДЗ №6 до 11.09.23 Динамические структуры данных (очередь)
// 
 //Задание 1. Напишите реализацию класса QueuePriority , который будет
 //использовать приоритетное включение, то есть ставить объект в очередь
 //по его приоритету, а извлекать первый в очереди.
 //Задание 2. Создайте программу список дел на основе стэка. Пользователь
 //может либо записать текущее дело, либо получить на выполнение
 //последнее записанное дело в помощью текстового меню. В программе
 //должен быть класс Task, который хранит каждое отдельное дело
 //(например, в виде даты и строки с текстом дела), и TaskStack, который
 //хранит стэк дел.


#include <iostream>
#include <string>

using namespace std;

// Класс, представляющий отдельное дело
class Task {
public:
    Task() : date_(""), description_("") {} // Конструктор по умолчанию
    Task(const string& date, const string& description) : date_(date), description_(description) {}

    // Метод для получения описания дела
    string getDescription() const {
        return description_;
    }

    // Метод для вывода информации о деле
    void print() const {
        cout << "Дата: " << date_ << ", Дело: " << description_ << endl;
    }

private:
    string date_;
    string description_;
};

// Класс, представляющий стек дел
class TaskStack {
public:
    // Конструктор по умолчанию
    TaskStack() : capacity_(10), size_(0) {
        tasks_ = new Task[capacity_];
    }

    // Деструктор для освобождения памяти
    ~TaskStack() {
        delete[] tasks_;
    }

    // Метод для добавления дела в стек
    void push(const Task& task) {
        // Проверяем, нужно ли увеличить размер стека
        if (size_ == capacity_) {
            // Увеличиваем емкость стека вдвое
            capacity_ *= 2;
            Task* newTasks = new Task[capacity_];

            // Копируем существующие задачи в новый массив
            for (int i = 0; i < size_; ++i) {
                newTasks[i] = tasks_[i];
            }

            // Освобождаем старую память
            delete[] tasks_;

            // Обновляем указатель на новый массив
            tasks_ = newTasks;
        }

        // Добавляем задачу в стек
        tasks_[size_] = task;
        size_++;
    }

    // Метод для извлечения последнего дела из стека
    Task pop() {
        if (!isEmpty()) {
            size_--;
            return tasks_[size_];
        }
        else {
            // Возвращаем пустое дело, если стек пустой
            return Task("", "");
        }
    }

    // Метод для проверки, пуст ли стек
    bool isEmpty() const {
        return size_ == 0;
    }

private:
    Task* tasks_; // Указатель на массив задач
    int capacity_; // Емкость стека
    int size_; // Текущий размер стека
};

// Класс, представляющий очередь с приоритетами
class QueuePriority {
public:
    // Конструктор по умолчанию
    QueuePriority() {}

    // Метод для добавления дела в очередь с учетом приоритета
    void enqueue(const Task& task) {
        task_stack_.push(task);
    }

    // Метод для извлечения первого дела из очереди
    Task dequeue() {
        // Очередь с приоритетами извлекает последнее добавленное дело
        return task_stack_.pop();
    }

    // Метод для проверки, пуста ли очередь
    bool isEmpty() const {
        return task_stack_.isEmpty();
    }

private:
    TaskStack task_stack_;
};

int main() 
{
    setlocale(LC_ALL, "Rus");
    cout << "Программа Список Дел с очередью приоритетов" << endl;

    // Создаем объект класса QueuePriority
    QueuePriority todoList;

    // Добавляем дела в очередь
    todoList.enqueue(Task("2023-09-10", "Подготовить отчет"));
    todoList.enqueue(Task("2023-09-11", "Встреча с клиентом"));
    todoList.enqueue(Task("2023-09-12", "Подготовить презентацию"));

    // Извлекаем дела из очереди с приоритетами и выводим их на экран
    while (!todoList.isEmpty()) {
        Task nextTask = todoList.dequeue();
        nextTask.print();
    }

    return 0;
}