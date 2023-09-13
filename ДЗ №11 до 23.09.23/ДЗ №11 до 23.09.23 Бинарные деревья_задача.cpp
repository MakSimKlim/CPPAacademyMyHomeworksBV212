// ДЗ 11 до 23.09.23 Бинарные деревья_задача
// Задание 1. Напишите класс Tree, который будет хранить узлы типа Apple.
// Каждый узел Apple хранит вес яблока в граммах, помимо информации нужной
// для дерева.Apple распределяются по дереву по их весу(для класса Apple
// нужно перегрузить операторы равенства и сравнения). Для проверки класса
// Tree, в main создайте 20 объектов типа Apple со случайным весом от 50 до 200
// грамм.

#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

class Apple {
public:
    Apple(int weight) : weight_(weight) {}

    // Перегрузка оператора равенства для сравнения яблок по весу
    bool operator==(const Apple& other) const {
        return weight_ == other.weight_;
    }

    // Перегрузка оператора сравнения для сортировки яблок по весу
    bool operator<(const Apple& other) const {
        return weight_ < other.weight_;
    }

    int getWeight() const {
        return weight_;
    }

private:
    int weight_;
};

class TreeNode {
public:
    Apple apple;
    TreeNode* left;
    TreeNode* right;

    TreeNode(const Apple& a) : apple(a), left(nullptr), right(nullptr) {}
};

class Tree {
public:
    Tree() : root(nullptr) {}

    // Вставка яблока в бинарное дерево
    void insert(const Apple& apple) {
        root = insertRecursive(root, apple);
    }

    // Рекурсивная функция для вставки яблока в дерево
    TreeNode* insertRecursive(TreeNode* node, const Apple& apple) {
        if (node == nullptr) {
            return new TreeNode(apple);
        }

        if (apple < node->apple) {
            node->left = insertRecursive(node->left, apple);
        }
        else if (apple == node->apple) {
            // Обработка ситуации, когда яблоко уже существует
            // (в данном случае можно игнорировать, ничего не делать)
        }
        else {
            node->right = insertRecursive(node->right, apple);
        }

        return node;
    }

    // Вывод содержимого дерева в порядке возрастания веса яблок
    void printApples() const {
        inorderTraversal(root);
    }

private:
    TreeNode* root;

    // Рекурсивный обход дерева в порядке возрастания
    void inorderTraversal(TreeNode* node) const {
        if (node != nullptr) {
            inorderTraversal(node->left);
            cout << "Apple weight: " << node->apple.getWeight() << " grams\n";
            inorderTraversal(node->right);
        }
    }
};

int main() {
    // Инициализируем генератор случайных чисел с использованием времени
    srand(time(0));

    Tree tree;

    // Создаем 20 объектов типа Apple со случайным весом и добавляем их в дерево
    for (int i = 0; i < 20; ++i) {
        int weight = rand() % 151 + 50; // Генерируем случайный вес от 50 до 200 грамм
        Apple apple(weight);
        tree.insert(apple);
    }

    // Выводим информацию о яблоках в дереве
    tree.printApples();

    return 0;
}