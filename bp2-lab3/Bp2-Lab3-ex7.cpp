/*
Problema 7: Sortarea numerelor folosind două stive

Cerință:
Se dă o secvență de numere întregi. Folosind două stive (structuri LIFO),
sortați numerele în ordine crescătoare. Prima stivă conține numerele inițiale,
a doua este folosită ca auxiliară pentru rearanjarea elementelor.

Algoritm:
1. Citim primul număr și îl punem în prima stivă
2. Pentru fiecare număr următor:
   - Dacă numărul este mai mare decât vârful primei stive → îl adăugăm direct
   - Altfel: mutăm toate elementele mai mici în a doua stivă,
     inserăm noul număr, returnăm elementele înapoi
3. În rezultat, prima stivă conține secvența sortată (descrescător de la vârf)
*/

#include <iostream>
#include <climits>


class Stiva {
private:
    struct Node {
        int value;
        Node* next;
        Node(int val) : value(val), next(nullptr) {}
    };

    Node* top;  // Vârful stivei

public:
    Stiva() : top(nullptr) {}

    ~Stiva() {
        while (!isEmpty()) {
            eliminare();
        }
    }

    // Adaugă element pe vârful stivei
    void adaugare(int val) {
        Node* newNode = new Node(val);
        newNode->next = top;
        top = newNode;
    }

    // Elimină și returnează elementul de pe vârf
    int eliminare() {
        if (isEmpty()) {
            std::cout << "Eroare: Stiva este goala!" << std::endl;
            return -1;
        }
        int val = top->value;
        Node* temp = top;
        top = top->next;
        delete temp;
        return val;
    }

    // Vizualizează valoarea de pe vârf (fără eliminare)
    int varf() const {
        if (isEmpty())
            return INT_MAX;
        return top->value;
    }

    // Verifică dacă stiva este goală
    bool isEmpty() const {
        return top == nullptr;
    }

    // Afișează toate elementele stivei
    void afisare() const {
        if (isEmpty()) {
            std::cout << "Stiva este vida." << std::endl;
            return;
        }
        Node* curent = top;
        while (curent != nullptr) {
            std::cout << curent->value << " ";
            curent = curent->next;
        }
        std::cout << std::endl;
    }
};



int main() {
    Stiva stiva1;  // Stiva principală (va conține numerele sortate)
    Stiva stiva2;  // Stiva auxiliară (buffer pentru rearanjare)

    int numar, raspuns;

    // Introducerea primului număr
    std::cout << "Introduceti primul numar: ";
    std::cin >> numar;
    stiva1.adaugare(numar);

    std::cout << "Mai adaugati un numar? (1 - Da, 0 - Nu): ";
    std::cin >> raspuns;

    // Ciclul de introducere și sortare
    while (raspuns == 1) {
        std::cout << "Introduceti numarul: ";
        std::cin >> numar;

        // Cazul 1: Numărul nou este mai mare decât vârful → adăugăm direct
        if (stiva1.varf() > numar) {
            stiva1.adaugare(numar);
        }
        // Cazul 2: Trebuie să găsim poziția corectă
        else {
            // Mutăm toate elementele mai mici în stiva2
            while (!stiva1.isEmpty() && stiva1.varf() < numar) {
                stiva2.adaugare(stiva1.eliminare());
            }

            // Inserăm noul număr
            stiva1.adaugare(numar);

            // Returnăm elementele înapoi
            while (!stiva2.isEmpty()) {
                stiva1.adaugare(stiva2.eliminare());
            }
        }

        std::cout << "Mai adaugati un numar? (1 - Da, 0 - Nu): ";
        std::cin >> raspuns;
    }

    // Afișarea rezultatului sortat
    std::cout << "\nSirul ordonat crescator:" << std::endl;
    stiva1.afisare();

    return 0;
}
