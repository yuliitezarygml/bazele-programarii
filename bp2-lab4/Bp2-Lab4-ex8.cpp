/*
Problema 8: Calcularea sumei tuturor nodurilor din arborele binar de căutare (BST)

Cerință:
Se dă un arbore binar de căutare (BST). Este necesar:
1. Construirea BST din numerele introduse de utilizator
2. Calcularea sumei tuturor nodurilor arborelui
3. Afișarea arborelui în ordine sortată (parcurgere inordine)

Proprietățile BST:
- Pentru fiecare nod: toate valorile din subarborele stâng < valoarea nodului < toate valorile din subarborele drept
- Parcurgerea inordine (stânga-rădăcină-dreapta) dă o secvență sortată

Algoritmul de calculare a sumei:
- Parcurgem recursiv arborele
- Suma = valoarea nodului curent + suma subarborelui stâng + suma subarborelui drept
- Cazul de bază: arborele gol are suma 0
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
            return new Node(val);  // Creăm un nod nou
        }

        if (val < node->data) {
            node->left = insertRec(node->left, val);   // Mergem la stânga
        } else if (val > node->data) {
            node->right = insertRec(node->right, val); // Mergem la dreapta
        }

        return node;
    }

    // Calcularea sumei tuturor nodurilor (recursiv)
    int sumRec(Node* node) {
        if (node == nullptr) {
            return 0;  // Arborele gol = suma 0
        }
        // Suma = nodul curent + suma stângă + suma dreaptă
        return node->data + sumRec(node->left) + sumRec(node->right);
    }

    // Parcurgerea inordine (stânga - rădăcină - dreapta) → afișare sortată
    void inorderRec(Node* node) {
        if (node != nullptr) {
            inorderRec(node->left);
            std::cout << node->data << " ";
            inorderRec(node->right);
        }
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
// FUNCȚIA PRINCIPALĂ
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
