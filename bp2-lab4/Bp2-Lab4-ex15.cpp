// Бинарное дерево поиска (BST) - подсчет узлов-листьев
// Лист = узел без детей (left == nullptr && right == nullptr)

#include <iostream>

// ============================================================================
// КЛАСС БИНАРНОГО ДЕРЕВА ПОИСКА
// ============================================================================

class BST {
private:
    struct Node {
        int data;       // Значение узла
        Node* left;     // Левый ребенок
        Node* right;    // Правый ребенок

        Node(int val) : data(val), left(nullptr), right(nullptr) {}
    };

    Node* root;  // Корень дерева

    // Вставка узла в BST (рекурсивно)
    Node* insertRec(Node* node, int val) {
        if (node == nullptr) {
            return new Node(val);
        }

        if (val < node->data) {
            node->left = insertRec(node->left, val);
        } else if (val > node->data) {
            node->right = insertRec(node->right, val);
        }

        return node;
    }

    // Подсчет узлов-листьев (без детей)
    int countLeavesRec(Node* node) {
        if (node == nullptr) {
            return 0;
        }

        // Если у узла нет детей → это лист
        if (node->left == nullptr && node->right == nullptr) {
            return 1;
        }

        // Иначе считаем листья в поддеревьях
        return countLeavesRec(node->left) + countLeavesRec(node->right);
    }

    // Подсчет внутренних узлов (с хотя бы одним ребенком)
    int countInternalRec(Node* node) {
        if (node == nullptr || (node->left == nullptr && node->right == nullptr)) {
            return 0;  // Пустой узел или лист
        }

        return 1 + countInternalRec(node->left) + countInternalRec(node->right);
    }

    // Обход inorder (отсортированный вывод)
    void inorderRec(Node* node) {
        if (node != nullptr) {
            inorderRec(node->left);
            std::cout << node->data << " ";
            inorderRec(node->right);
        }
    }

    // Вывод всех листьев
    void printLeavesRec(Node* node) {
        if (node == nullptr) {
            return;
        }

        if (node->left == nullptr && node->right == nullptr) {
            std::cout << node->data << " ";  // Это лист
        }

        printLeavesRec(node->left);
        printLeavesRec(node->right);
    }

    // Вычисление высоты дерева
    int heightRec(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + std::max(heightRec(node->left), heightRec(node->right));
    }

    // Освобождение памяти
    void destroyTree(Node* node) {
        if (node != nullptr) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

public:
    BST() : root(nullptr) {}

    ~BST() {
        destroyTree(root);
    }

    void insert(int val) {
        root = insertRec(root, val);
    }

    int countLeaves() {
        return countLeavesRec(root);
    }

    int countInternal() {
        return countInternalRec(root);
    }

    int height() {
        return heightRec(root);
    }

    void inorder() {
        inorderRec(root);
    }

    void printLeaves() {
        printLeavesRec(root);
    }

    bool isEmpty() {
        return root == nullptr;
    }
};

// ============================================================================
// ГЛАВНАЯ ФУНКЦИЯ
// ============================================================================

int main() {
    BST arbore;
    int n, valoare;

    std::cout << "=== NUMĂRARE NODURI FRUNZĂ ÎN ARBORE BINAR ===" << std::endl;
    std::cout << "\nIntroduceți numărul de valori: ";
    std::cin >> n;

    std::cout << "Introduceți " << n << " valori întregi:" << std::endl;
    for (int i = 0; i < n; i++) {
        std::cout << "Valoarea " << (i + 1) << ": ";
        std::cin >> valoare;
        arbore.insert(valoare);
    }

    std::cout << "\n=== REZULTATE ===" << std::endl;
    std::cout << "Arborele în ordine crescătoare: ";
    arbore.inorder();
    std::cout << std::endl;

    std::cout << "\nNoduri frunză (fără copii): ";
    arbore.printLeaves();
    std::cout << std::endl;

    std::cout << "\n=== STATISTICI ===" << std::endl;
    std::cout << "Număr total de noduri frunză: " << arbore.countLeaves() << std::endl;
    std::cout << "Număr de noduri interne: " << arbore.countInternal() << std::endl;
    std::cout << "Înălțimea arborelui: " << arbore.height() << std::endl;

    return 0;
}
