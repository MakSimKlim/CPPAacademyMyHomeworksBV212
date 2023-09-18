// ДЗ 11 до 23.09.23 Бинарные деревья_задача
// 
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

// Класс для представления яблока
class Apple 
{
public:
    Apple(int weight) : weight_(weight) {}

    // Перегрузка оператора равенства для сравнения яблок по весу
    bool operator==(const Apple& other) const 
    {
        return weight_ == other.weight_;
    }

    // Перегрузка оператора сравнения для сортировки яблок по весу
    bool operator<(const Apple& other) const 
    {
        return weight_ < other.weight_;
    }

    int getWeight() const 
    {
        return weight_;
    }

private:
    int weight_;
};

// Класс для бинарного дерева
class Tree 
{
private:
    // Узел дерева
    struct TreeNode 
    {
        Apple data;
        TreeNode* left;
        TreeNode* right;
        TreeNode* parent;

        TreeNode(const Apple& apple) : data(apple), left(nullptr), right(nullptr), parent(nullptr) {}
    };

public:
    Tree() : root(nullptr) {}

    // Вставка элемента в дерево
    void insert(const Apple& apple) 
    {
        root = insertRecursive(root, apple);
    }

    // Поиск элемента в дереве
    TreeNode* search(const Apple& apple) 
    {
        return searchRecursive(root, apple);
    }

    // Удаление элемента из дерева
    void remove(const Apple& apple) 
    {
        root = removeRecursive(root, apple);
    }

    // Вывод элементов дерева в порядке возрастания
    void inorderTraversal() 
    {
        inorderRecursive(root);
    }

private:
    TreeNode* root;

    // Рекурсивная функция вставки элемента
    TreeNode* insertRecursive(TreeNode* node, const Apple& apple) 
    {
        if (node == nullptr) 
        {
            return new TreeNode(apple);
        }

        if (apple < node->data) 
        {
            node->left = insertRecursive(node->left, apple);
            node->left->parent = node;
        }
        else 
        {
            node->right = insertRecursive(node->right, apple);
            node->right->parent = node;
        }

        return node;
    }

    // Рекурсивная функция поиска элемента
    TreeNode* searchRecursive(TreeNode* node, const Apple& apple) 
    {
        if (node == nullptr || node->data == apple) 
        {
            return node;
        }

        if (apple < node->data) 
        {
            return searchRecursive(node->left, apple);
        }
        else 
        {
            return searchRecursive(node->right, apple);
        }
    }

    // Рекурсивная функция удаления элемента
    TreeNode* removeRecursive(TreeNode* node, const Apple& apple) 
    {
        if (node == nullptr) 
        {
            return node;
        }

        if (apple == node->data) 
        {
            if (node->left == nullptr) 
            {
                TreeNode* temp = node->right;
                delete node;
                return temp;
            }
            else if (node->right == nullptr) 
            {
                TreeNode* temp = node->left;
                delete node;
                return temp;
            }

            TreeNode* minRight = findMin(node->right);
            node->data = minRight->data;
            node->right = removeRecursive(node->right, minRight->data);
        }
        else if (apple < node->data) 
        {
            node->left = removeRecursive(node->left, apple);
        }
        else 
        {
            node->right = removeRecursive(node->right, apple);
        }

        return node;
    }

    // Рекурсивная функция поиска минимального элемента
    TreeNode* findMin(TreeNode* node) 
    {
        while (node->left != nullptr) 
        {
            node = node->left;
        }
        return node;
    }

    // Рекурсивная функция вывода элементов дерева в порядке возрастания
    void inorderRecursive(TreeNode* node) 
    {
        if (node != nullptr) 
        {
            inorderRecursive(node->left);
            cout << "Вес яблока: " << node->data.getWeight() << " грамм\n";
            inorderRecursive(node->right);
        }
    }
};

int main() 
{
    setlocale(LC_ALL, "Rus");

    srand(time(0));

    Tree tree;

    // Создаем 20 объектов типа Apple со случайным весом от 50 до 200 грамм
    for (int i = 0; i < 20; ++i) 
    {
        int weight = rand() % 151 + 50; // Генерируем случайный вес от 50 до 200 грамм
        Apple apple(weight);
        tree.insert(apple);
    }


    // Выводим элементы дерева в порядке возрастания
    cout << "Вес яблок по-возрастанию:\n";
    tree.inorderTraversal();

    return 0;
}
