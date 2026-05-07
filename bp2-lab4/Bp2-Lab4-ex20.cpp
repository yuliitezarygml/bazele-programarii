/*
Problema 20: Sistem complet de gestionare a arborelui binar de căutare (BST)

Cerință:
Creați un program interactiv pentru lucrul cu arborele binar de căutare (BST).
Programul trebuie să suporte următoarele operații:

1. Inserarea nodului - adăugarea unei noi valori cu păstrarea proprietății BST
2. Ștergerea nodului - trei cazuri:
   - Nod frunză (fără copii) - ștergem direct
   - Nod cu un copil - înlocuim nodul cu copilul său
   - Nod cu doi copii - înlocuim cu inorder successor (minimul din subarborele drept)
3. Căutarea nodului - verificarea prezenței valorii în arbore
4. Parcurgerile arborelui:
   - Inordine (stânga-rădăcină-dreapta) - afișare sortată
   - Preordine (rădăcină-stânga-dreapta) - pentru copierea structurii
   - Postordine (stânga-dreapta-rădăcină) - pentru ștergerea arborelui
   - Pe niveluri (BFS) - parcurgere în lățime folosind coadă
5. Statistici:
   - Înălțimea arborelui
   - Numărul de noduri
   - Valoarea minimă și maximă
   - Verificarea echilibrului (diferența înălțimilor subarborilor ≤ 1)

Interfață:
- Meniu cu 12 opțiuni
- Introducere interactivă a comenzilor
- Verificarea corectitudinii operațiilor (ștergere din arbore gol etc.)
*/

#include <iostream>
#include <algorithm>
#include <queue>

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

    // Căutarea nodului după valoare
    Node* searchRec(Node* node, int val) {
        if (node == nullptr || node->data == val) {
            return node;
        }

        if (val < node->data) {
            return searchRec(node->left, val);
        }
        return searchRec(node->right, val);
    }

    // Găsirea nodului minim (cel mai din stânga)
    Node* findMin(Node* node) {
        while (node && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // Ștergerea nodului (3 cazuri: frunză, un copil, doi copii)
    Node* deleteRec(Node* node, int val) {
        if (node == nullptr) {
            return node;
        }

        // Căutarea nodului de șters
        if (val < node->data) {
            node->left = deleteRec(node->left, val);
        } else if (val > node->data) {
            node->right = deleteRec(node->right, val);
        } else {
            // Nodul găsit - efectuăm ștergerea

            // Cazul 1: Nod frunză (fără copii)
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }

            // Cazul 2: Nod cu un copil
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

            // Cazul 3: Nod cu doi copii
            // Găsim inorder successor (minimul din subarborele drept)
            Node* temp = findMin(node->right);
            node->data = temp->data;  // Copiem valoarea
            node->right = deleteRec(node->right, temp->data);  // Ștergem successor
        }

        return node;
    }

    // Parcurgerea inordine (stânga - rădăcină - dreapta) → afișare sortată
    void inorderRec(Node* node) {
        if (node != nullptr) {
            inorderRec(node->left);
            std::cout << node->data << " ";
            inorderRec(node->right);
        }
    }

    // Parcurgerea preordine (rădăcină - stânga - dreapta) → copierea structurii
    void preorderRec(Node* node) {
        if (node != nullptr) {
            std::cout << node->data << " ";
            preorderRec(node->left);
            preorderRec(node->right);
        }
    }

    // Parcurgerea postordine (stânga - dreapta - rădăcină) → ștergerea arborelui
    void postorderRec(Node* node) {
        if (node != nullptr) {
            postorderRec(node->left);
            postorderRec(node->right);
            std::cout << node->data << " ";
        }
    }

    // Calcularea înălțimii arborelui
    int heightRec(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + std::max(heightRec(node->left), heightRec(node->right));
    }

    // Numărarea tuturor nodurilor
    int countNodesRec(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        return 1 + countNodesRec(node->left) + countNodesRec(node->right);
    }

    // Verificarea echilibrului arborelui (diferența înălțimilor ≤ 1)
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

    // Parcurgerea pe niveluri (BFS - Breadth-First Search)
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
// MENIU ȘI FUNCȚIA PRINCIPALĂ
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
