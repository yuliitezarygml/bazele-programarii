/*
Problema 10: Sistem de gestionare a mărfurilor (listă dublu înlănțuită)

Cerință:
Creați un sistem de evidență a mărfurilor în depozit, folosind o listă dublu înlănțuită cu noduri santinelă.
Fiecare marfă are: cod, denumire, cantitate în stoc, preț.

Operații necesare:
1. Adăugarea mărfii (cu sortare după cod)
2. Ștergerea mărfii după cod
3. Căutarea mărfii după cod
4. Modificarea datelor mărfii
5. Intrarea mărfii în depozit (creșterea cantității)
6. Ieșirea mărfii din depozit (scăderea cantității)
7. Afișarea tuturor mărfurilor (ordine directă și inversă)
8. Ștergerea automată a mărfii la atingerea stocului zero

Particularități de implementare:
- Listă dublu înlănțuită cu noduri santinelă (sant1, sant2)
- Mărfurile sunt sortate automat după cod la inserare
- Abordare orientată pe obiecte cu clasele Articol și Lista_articol
*/

#include <iostream>
#include <string>

// ============================================================================
// CLASA ARTICOL
// ============================================================================

class Articol {
private:
    int cod;
    std::string nume;
    int stoc;
    double pret;

public:
    Articol(int cod, const std::string& nume, int stoc, double pret)
        : cod(cod), nume(nume), stoc(stoc), pret(pret) {}

    // Getteri și setteri
    int getCod() const { return cod; }
    void setCod(int cod) { this->cod = cod; }

    std::string getNume() const { return nume; }
    void setNume(const std::string& nume) { this->nume = nume; }

    int getStoc() const { return stoc; }
    void setStoc(int stoc) { this->stoc = stoc; }

    double getPret() const { return pret; }
    void setPret(double pret) { this->pret = pret; }

    // Supraîncărcarea operatorului de afișare
    friend std::ostream& operator<<(std::ostream& os, const Articol& a) {
        os << "Cod: " << a.cod << " | Nume: " << a.nume
           << " | Stoc: " << a.stoc << " | Pret: " << a.pret << " lei";
        return os;
    }
};

// ============================================================================
// CLASA LISTĂ DUBLU ÎNLĂNȚUITĂ
// ============================================================================

class Lista_articol {
private:
    struct Node {
        Articol* inf;   // Pointer către articol
        Node* next;     // Nodul următor
        Node* prev;     // Nodul precedent

        Node() : inf(nullptr), next(nullptr), prev(nullptr) {}
        Node(Articol* articol) : inf(articol), next(nullptr), prev(nullptr) {}
    };

    Node* sant1;  // Nod santinelă (început)
    Node* sant2;  // Nod santinelă (sfârșit)

public:
    // Constructor: creează listă goală cu două noduri santinelă
    Lista_articol() {
        sant1 = new Node();
        sant2 = new Node();
        sant1->next = sant2;
        sant2->prev = sant1;
    }

    // Destructor: eliberează toată memoria
    ~Lista_articol() {
        Node* curent = sant1->next;
        while (curent != sant2) {
            Node* temp = curent;
            curent = curent->next;
            delete temp->inf;
            delete temp;
        }
        delete sant1;
        delete sant2;
    }

    // Verificare: este lista goală?
    bool esteGoala() const {
        return sant1->next == sant2;
    }

    // Afișarea listei de la început la sfârșit
    void afisare() const {
        if (esteGoala()) {
            std::cout << "Lista este vida." << std::endl;
            return;
        }
        std::cout << " Lista articole (ordonat dupa cod) " << std::endl;
        Node* curent = sant1->next;
        int index = 1;
        while (curent != sant2) {
            std::cout << index << ". " << *(curent->inf) << std::endl;
            curent = curent->next;
            index++;
        }
        std::cout << "---" << std::endl;
    }

    // Afișarea listei de la sfârșit la început
    void afisareInversa() const {
        if (esteGoala()) {
            std::cout << "Lista este vida." << std::endl;
            return;
        }
        std::cout << " Lista articole (invers) " << std::endl;
        Node* curent = sant2->prev;
        while (curent != sant1) {
            std::cout << *(curent->inf) << std::endl;
            curent = curent->prev;
        }
        std::cout << "---" << std::endl;
    }

    // Adăugarea articolului (cu sortare după cod)
    void adauga(Articol* a) {
        // Verificare pentru cod duplicat
        Node* curent = sant1->next;
        while (curent != sant2) {
            if (curent->inf->getCod() == a->getCod()) {
                std::cout << "Eroare: Exista deja un articol cu codul " << a->getCod() << "!" << std::endl;
                delete a;
                return;
            }
            curent = curent->next;
        }

        // Găsirea poziției pentru inserare (lista sortată după cod)
        curent = sant1->next;
        while (curent != sant2 && curent->inf->getCod() < a->getCod()) {
            curent = curent->next;
        }

        // Inserarea nodului nou înainte de poziția găsită
        Node* newNode = new Node(a);
        newNode->next = curent;
        newNode->prev = curent->prev;
        curent->prev->next = newNode;
        curent->prev = newNode;

        std::cout << "Articolul cu codul " << a->getCod() << " a fost adaugat." << std::endl;
    }

    // Ștergerea articolului după cod
    void sterge(int cod) {
        Node* curent = sant1->next;
        while (curent != sant2 && curent->inf->getCod() != cod) {
            curent = curent->next;
        }
        if (curent == sant2) {
            std::cout << "Articolul cu codul " << cod << " nu a fost gasit." << std::endl;
            return;
        }

        // Eliminarea nodului din listă
        curent->prev->next = curent->next;
        curent->next->prev = curent->prev;
        delete curent->inf;
        delete curent;
        std::cout << "Articolul cu codul " << cod << " a fost sters." << std::endl;
    }

    // Intrarea mărfii în depozit
    void intrareStoc(int cod, int cantitate) {
        Node* curent = sant1->next;
        while (curent != sant2 && curent->inf->getCod() != cod) {
            curent = curent->next;
        }
        if (curent == sant2) {
            std::cout << "Articolul cu codul " << cod << " nu a fost gasit." << std::endl;
            return;
        }
        curent->inf->setStoc(curent->inf->getStoc() + cantitate);
        std::cout << "Stoc actualizat: " << *(curent->inf) << std::endl;
    }

    // Ieșirea mărfii din depozit (ștergere automată la stoc zero)
    void iesireStoc(int cod, int cantitate) {
        Node* curent = sant1->next;
        while (curent != sant2 && curent->inf->getCod() != cod) {
            curent = curent->next;
        }
        if (curent == sant2) {
            std::cout << "Articolul cu codul " << cod << " nu a fost gasit." << std::endl;
            return;
        }
        if (curent->inf->getStoc() < cantitate) {
            std::cout << "Eroare: Stoc insuficient! Stoc disponibil: "
                      << curent->inf->getStoc() << std::endl;
            return;
        }

        curent->inf->setStoc(curent->inf->getStoc() - cantitate);

        // Ștergere automată la stoc zero
        if (curent->inf->getStoc() == 0) {
            curent->prev->next = curent->next;
            curent->next->prev = curent->prev;
            std::cout << "Stoc epuizat. Articolul cu codul " << cod << " a fost sters din lista." << std::endl;
            delete curent->inf;
            delete curent;
        } else {
            std::cout << "Stoc actualizat: " << *(curent->inf) << std::endl;
        }
    }

    // Modificarea denumirii și/sau prețului articolului
    void modifica(int cod, const std::string& numeNou, double pretNou) {
        Node* curent = sant1->next;
        while (curent != sant2 && curent->inf->getCod() != cod) {
            curent = curent->next;
        }
        if (curent == sant2) {
            std::cout << "Articolul cu codul " << cod << " nu a fost gasit." << std::endl;
            return;
        }
        if (!numeNou.empty()) {
            curent->inf->setNume(numeNou);
        }
        if (pretNou > 0) {
            curent->inf->setPret(pretNou);
        }
        std::cout << "Articol modificat: " << *(curent->inf) << std::endl;
    }

    // Căutarea articolului după cod
    void cauta(int cod) const {
        Node* curent = sant1->next;
        while (curent != sant2 && curent->inf->getCod() != cod) {
            curent = curent->next;
        }
        if (curent == sant2) {
            std::cout << "Articolul cu codul " << cod << " nu a fost gasit." << std::endl;
        } else {
            std::cout << "Articol gasit: " << *(curent->inf) << std::endl;
        }
    }
};

// ============================================================================
// FUNCȚIA PRINCIPALĂ
// ============================================================================

int main() {
    Lista_articol lista;
    int optiune;
    std::cout << "=== Sistem de gestiune stocuri ===" << std::endl << std::endl;

    do {
        std::cout << "\n--- MENIU ---" << std::endl;
        std::cout << "1. Adauga articol" << std::endl;
        std::cout << "2. Sterge articol (dupa cod)" << std::endl;
        std::cout << "3. Intrare stoc (receptie marfa)" << std::endl;
        std::cout << "4. Iesire stoc (vanzare/consum)" << std::endl;
        std::cout << "5. Modifica articol (nume / pret)" << std::endl;
        std::cout << "6. Cauta articol dupa cod" << std::endl;
        std::cout << "7. Afiseaza toate articolele" << std::endl;
        std::cout << "8. Afiseaza invers" << std::endl;
        std::cout << "0. Iesire" << std::endl;
        std::cout << "Optiunea dvs: ";
        std::cin >> optiune;

        switch (optiune) {
            case 1: {
                int cod, stoc;
                std::string nume;
                double pret;
                std::cout << "Cod articol: ";
                std::cin >> cod;
                std::cout << "Nume articol: ";
                std::cin >> nume;
                std::cout << "Stoc initial: ";
                std::cin >> stoc;
                std::cout << "Pret unitar: ";
                std::cin >> pret;
                lista.adauga(new Articol(cod, nume, stoc, pret));
                break;
            }

            case 2: {
                int cod;
                std::cout << "Codul articolului de sters: ";
                std::cin >> cod;
                lista.sterge(cod);
                break;
            }

            case 3: {
                int codI, cantI;
                std::cout << "Codul articolului: ";
                std::cin >> codI;
                std::cout << "Cantitate intrata: ";
                std::cin >> cantI;
                lista.intrareStoc(codI, cantI);
                break;
            }

            case 4: {
                int codE, cantE;
                std::cout << "Codul articolului: ";
                std::cin >> codE;
                std::cout << "Cantitate iesita: ";
                std::cin >> cantE;
                lista.iesireStoc(codE, cantE);
                break;
            }

            case 5: {
                int codM;
                std::string numeNou;
                double pretNou;
                std::cout << "Codul articolului de modificat: ";
                std::cin >> codM;
                std::cout << "Nume nou (- pentru a pastra): ";
                std::cin >> numeNou;
                if (numeNou == "-") numeNou = "";
                std::cout << "Pret nou (0 pentru a pastra): ";
                std::cin >> pretNou;
                lista.modifica(codM, numeNou, pretNou);
                break;
            }

            case 6: {
                int cod;
                std::cout << "Codul articolului cautat: ";
                std::cin >> cod;
                lista.cauta(cod);
                break;
            }

            case 7:
                lista.afisare();
                break;

            case 8:
                lista.afisareInversa();
                break;

            case 0:
                std::cout << "La revedere." << std::endl;
                break;

            default:
                std::cout << "Optiune invalida." << std::endl;
        }

    } while (optiune != 0);

    return 0;
}
