/*
Problema 15: Numărarea nodurilor frunză din arborele binar de căutare (BST)

Cerință:
Se dă un arbore binar de căutare (BST). Este necesar:
1. Construirea BST din numerele introduse de utilizator
2. Numărarea nodurilor frunză (noduri fără copii)
3. Numărarea nodurilor interne (noduri cu cel puțin un copil)
4. Calcularea înălțimii arborelui
5. Afișarea tuturor nodurilor frunză

Definiții:
- Frunză (frunză) - nod fără copii (left == nullptr && right == nullptr)
- Nod intern - nod cu cel puțin un copil
- Înălțimea arborelui - lungimea maximă a căii de la rădăcină la frunză

Algoritmul de numărare a frunzelor:
- Dacă nodul este gol → returnăm 0
- Dacă nodul nu are copii → este frunză, returnăm 1
- Altfel → numărăm recursiv frunzele în subarborii stâng și drept
*/

#include <iostream>

// ============================================================================
// CLASA ARBORE BINAR DE CĂUTARE
// ============================================================================

class BST {
private:
    struct Node {
        int data;       // Valoarea nodului
        Node* left;     // Copilul stâng
        Node* right;    // Copilul drept

        Node(int val) : data(val), left(nullptr), right(nullptr) {}
    };

    Node* root;  // Rădăcina arborelui

    // Inserarea nodului în BST (recursiv)
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

    // Numărarea nodurilor frunză (fără copii)
    int countLeavesRec(Node* node) {
        if (node == nullptr) {
            return 0;
        }

        // Dacă nodul nu are copii → este frunză
        if (node->left == nullptr && node->right == nullptr) {
            return 1;
        }

        // Altfel numărăm frunzele în subarbori
        return countLeavesRec(node->left) + countLeavesRec(node->right);
    }

    // Numărarea nodurilor interne (cu cel puțin un copil)
    int countInternalRec(Node* node) {
        if (node == nullptr || (node->left == nullptr && node->right == nullptr)) {
            return 0;  // Nod gol sau frunză
        }

        return 1 + countInternalRec(node->left) + countInternalRec(node->right);
    }

    // Parcurgerea inordine (afișare sortată)
    void inorderRec(Node* node) {
        if (node != nullptr) {
            inorderRec(node->left);
            std::cout << node->data << " ";
            inorderRec(node->right);
        }
    }

    // Afișarea tuturor frunzelor
    void printLeavesRec(Node* node) {
        if (node == nullptr) {
            return;
        }

        if (node->left == nullptr && node->right == nullptr) {
            std::cout << node->data << " ";  // Aceasta este frunză
        }

        printLeavesRec(node->left);
        printLeavesRec(node->right);
    }

    // Calcularea înălțimii arborelui
    int heightRec(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + std::max(heightRec(node->left), heightRec(node->right));
    }

    // Eliberarea memoriei
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
// FUNCȚIA PRINCIPALĂ
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
