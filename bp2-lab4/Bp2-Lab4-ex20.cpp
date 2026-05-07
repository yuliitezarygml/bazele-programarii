// Полная система управления бинарным деревом поиска (BST)
// Включает: вставку, удаление (3 случая), поиск, все виды обхода, статистику, проверку баланса

#include <iostream>
#include <algorithm>
#include <queue>

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

    // Поиск узла по значению
    Node* searchRec(Node* node, int val) {
        if (node == nullptr || node->data == val) {
            return node;
        }

        if (val < node->data) {
            return searchRec(node->left, val);
        }
        return searchRec(node->right, val);
    }

    // Найти минимальный узел (самый левый)
    Node* findMin(Node* node) {
        while (node && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // Удаление узла (3 случая: лист, один ребенок, два ребенка)
    Node* deleteRec(Node* node, int val) {
        if (node == nullptr) {
            return node;
        }

        // Поиск узла для удаления
        if (val < node->data) {
            node->left = deleteRec(node->left, val);
        } else if (val > node->data) {
            node->right = deleteRec(node->right, val);
        } else {
            // Узел найден - выполняем удаление

            // Случай 1: Узел-лист (без детей)
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }

            // Случай 2: Узел с одним ребенком
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Случай 3: Узел с двумя детьми
            // Находим inorder successor (минимум в правом поддереве)
            Node* temp = findMin(node->right);
            node->data = temp->data;  // Копируем значение
            node->right = deleteRec(node->right, temp->data);  // Удаляем successor
        }

        return node;
    }

    // Обход inorder (левый - корень - правый) → отсортированный вывод
    void inorderRec(Node* node) {
        if (node != nullptr) {
            inorderRec(node->left);
            std::cout << node->data << " ";
            inorderRec(node->right);
        }
    }

    // Обход preorder (корень - левый - правый) → копирование структуры
    void preorderRec(Node* node) {
        if (node != nullptr) {
            std::cout << node->data << " ";
            preorderRec(node->left);
            preorderRec(node->right);
        }
    }

    // Обход postorder (левый - правый - корень) → удаление дерева
    void postorderRec(Node* node) {
        if (node != nullptr) {
            postorderRec(node->left);
            postorderRec(node->right);
            std::cout << node->data << " ";
        }
    }

    // Вычисление высоты дерева
    int heightRec(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + std::max(heightRec(node->left), heightRec(node->right));
    }

    // Подсчет всех узлов
    int countNodesRec(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + countNodesRec(node->left) + countNodesRec(node->right);
    }

    // Проверка баланса дерева (разница высот ≤ 1)
    bool isBalancedRec(Node* node) {
        if (node == nullptr) {
            return true;
        }

        int leftHeight = heightRec(node->left);
        int rightHeight = heightRec(node->right);

        if (std::abs(leftHeight - rightHeight) > 1) {
            return false;
        }

        return isBalancedRec(node->left) && isBalancedRec(node->right);
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

    bool search(int val) {
        return searchRec(root, val) != nullptr;
    }

    void remove(int val) {
        root = deleteRec(root, val);
    }

    void inorder() {
        std::cout << "Inordine (crescător): ";
        inorderRec(root);
        std::cout << std::endl;
    }

    void preorder() {
        std::cout << "Preordine: ";
        preorderRec(root);
        std::cout << std::endl;
    }

    void postorder() {
        std::cout << "Postordine: ";
        postorderRec(root);
        std::cout << std::endl;
    }

    int height() {
        return heightRec(root);
    }

    int countNodes() {
        return countNodesRec(root);
    }

    int findMinValue() {
        if (root == nullptr) {
            std::cout << "Arborele este gol!" << std::endl;
            return -1;
        }
        Node* minNode = findMin(root);
        return minNode->data;
    }

    int findMaxValue() {
        if (root == nullptr) {
            std::cout << "Arborele este gol!" << std::endl;
            return -1;
        }
        Node* current = root;
        while (current->right != nullptr) {
            current = current->right;
        }
        return current->data;
    }

    bool isBalanced() {
        return isBalancedRec(root);
    }

    // Обход по уровням (BFS - Breadth-First Search)
    void levelOrder() {
        if (root == nullptr) {
            std::cout << "Arborele este gol!" << std::endl;
            return;
        }

        std::queue<Node*> q;
        q.push(root);

        std::cout << "Afișare pe niveluri: ";
        while (!q.empty()) {
            Node* current = q.front();
            q.pop();

            std::cout << current->data << " ";

            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
        std::cout << std::endl;
    }

    bool isEmpty() {
        return root == nullptr;
    }
};

// ============================================================================
// МЕНЮ И ГЛАВНАЯ ФУНКЦИЯ
// ============================================================================

void afiseazaMeniu() {
    std::cout << "\n=== MENIU ARBORE BINAR DE CĂUTARE ===" << std::endl;
    std::cout << "1.  Inserare nod" << std::endl;
    std::cout << "2.  Ștergere nod" << std::endl;
    std::cout << "3.  Căutare nod" << std::endl;
    std::cout << "4.  Afișare inordine (crescător)" << std::endl;
    std::cout << "5.  Afișare preordine" << std::endl;
    std::cout << "6.  Afișare postordine" << std::endl;
    std::cout << "7.  Afișare pe niveluri" << std::endl;
    std::cout << "8.  Înălțimea arborelui" << std::endl;
    std::cout << "9.  Numărul de noduri" << std::endl;
    std::cout << "10. Valoarea minimă" << std::endl;
    std::cout << "11. Valoarea maximă" << std::endl;
    std::cout << "12. Verificare echilibrat" << std::endl;
    std::cout << "0.  Ieșire" << std::endl;
    std::cout << "Alegeți opțiunea: ";
}

int main() {
    BST arbore;
    int optiune, valoare;

    std::cout << "=== ARBORE BINAR DE CĂUTARE ===" << std::endl;
    std::cout << "Program demonstrativ pentru gestionarea unui BST\n" << std::endl;

    do {
        afiseazaMeniu();
        std::cin >> optiune;

        switch (optiune) {
            case 1:
                std::cout << "Introduceți valoarea de inserat: ";
                std::cin >> valoare;
                arbore.insert(valoare);
                std::cout << "Valoarea " << valoare << " a fost inserată." << std::endl;
                break;

            case 2:
                if (arbore.isEmpty()) {
                    std::cout << "Arborele este gol!" << std::endl;
                } else {
                    std::cout << "Introduceți valoarea de șters: ";
                    std::cin >> valoare;
                    if (arbore.search(valoare)) {
                        arbore.remove(valoare);
                        std::cout << "Valoarea " << valoare << " a fost ștearsă." << std::endl;
                    } else {
                        std::cout << "Valoarea " << valoare << " nu există în arbore." << std::endl;
                    }
                }
                break;

            case 3:
                std::cout << "Introduceți valoarea de căutat: ";
                std::cin >> valoare;
                if (arbore.search(valoare)) {
                    std::cout << "Valoarea " << valoare << " EXISTĂ în arbore." << std::endl;
                } else {
                    std::cout << "Valoarea " << valoare << " NU EXISTĂ în arbore." << std::endl;
                }
                break;

            case 4:
                if (arbore.isEmpty()) {
                    std::cout << "Arborele este gol!" << std::endl;
                } else {
                    arbore.inorder();
                }
                break;

            case 5:
                if (arbore.isEmpty()) {
                    std::cout << "Arborele este gol!" << std::endl;
                } else {
                    arbore.preorder();
                }
                break;

            case 6:
                if (arbore.isEmpty()) {
                    std::cout << "Arborele este gol!" << std::endl;
                } else {
                    arbore.postorder();
                }
                break;

            case 7:
                if (arbore.isEmpty()) {
                    std::cout << "Arborele este gol!" << std::endl;
                } else {
                    arbore.levelOrder();
                }
                break;

            case 8:
                std::cout << "Înălțimea arborelui: " << arbore.height() << std::endl;
                break;

            case 9:
                std::cout << "Numărul de noduri: " << arbore.countNodes() << std::endl;
                break;

            case 10:
                if (!arbore.isEmpty()) {
                    std::cout << "Valoarea minimă: " << arbore.findMinValue() << std::endl;
                }
                break;

            case 11:
                if (!arbore.isEmpty()) {
                    std::cout << "Valoarea maximă: " << arbore.findMaxValue() << std::endl;
                }
                break;

            case 12:
                if (arbore.isEmpty()) {
                    std::cout << "Arborele este gol!" << std::endl;
                } else {
                    if (arbore.isBalanced()) {
                        std::cout << "Arborele ESTE echilibrat." << std::endl;
                    } else {
                        std::cout << "Arborele NU ESTE echilibrat." << std::endl;
                    }
                }
                break;

            case 0:
                std::cout << "Ieșire din program..." << std::endl;
                break;

            default:
                std::cout << "Opțiune invalidă! Încercați din nou." << std::endl;
        }

    } while (optiune != 0);

    return 0;
}
