// Бинарное дерево поиска (BST) - вычисление суммы всех узлов
// BST свойство: левое поддерево < корень < правое поддерево

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
            return new Node(val);  // Создаем новый узел
        }

        if (val < node->data) {
            node->left = insertRec(node->left, val);   // Идем влево
        } else if (val > node->data) {
            node->right = insertRec(node->right, val); // Идем вправо
        }

        return node;
    }

    // Вычисление суммы всех узлов (рекурсивно)
    int sumRec(Node* node) {
        if (node == nullptr) {
            return 0;  // Пустое дерево = сумма 0
        }
        // Сумма = текущий узел + сумма левого + сумма правого
        return node->data + sumRec(node->left) + sumRec(node->right);
    }

    // Обход inorder (левый - корень - правый) → отсортированный вывод
    void inorderRec(Node* node) {
        if (node != nullptr) {
            inorderRec(node->left);
            std::cout << node->data << " ";
            inorderRec(node->right);
        }
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

    int sum() {
        return sumRec(root);
    }

    void inorder() {
        inorderRec(root);
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

    std::cout << "=== SUMA NODURILOR DIN ARBORE BINAR DE CĂUTARE ===" << std::endl;
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

    std::cout << "Suma tuturor nodurilor: " << arbore.sum() << std::endl;

    return 0;
}
