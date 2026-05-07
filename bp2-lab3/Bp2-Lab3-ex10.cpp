// Система управления товарами с двусвязным списком
// Товары хранятся отсортированными по коду, автоматически удаляются при нулевом остатке

#include <iostream>
#include <string>

// ============================================================================
// КЛАСС ТОВАРА
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

    // Геттеры и сеттеры
    int getCod() const { return cod; }
    void setCod(int cod) { this->cod = cod; }

    std::string getNume() const { return nume; }
    void setNume(const std::string& nume) { this->nume = nume; }

    int getStoc() const { return stoc; }
    void setStoc(int stoc) { this->stoc = stoc; }

    double getPret() const { return pret; }
    void setPret(double pret) { this->pret = pret; }

    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Articol& a) {
        os << "Cod: " << a.cod << " | Nume: " << a.nume
           << " | Stoc: " << a.stoc << " | Pret: " << a.pret << " lei";
        return os;
    }
};

// ============================================================================
// КЛАСС ДВУСВЯЗНОГО СПИСКА
// ============================================================================

class Lista_articol {
private:
    struct Node {
        Articol* inf;   // Указатель на товар
        Node* next;     // Следующий узел
        Node* prev;     // Предыдущий узел

        Node() : inf(nullptr), next(nullptr), prev(nullptr) {}
        Node(Articol* articol) : inf(articol), next(nullptr), prev(nullptr) {}
    };

    Node* sant1;  // Сторожевой узел (начало)
    Node* sant2;  // Сторожевой узел (конец)

public:
    // Конструктор: создает пустой список с двумя сторожевыми узлами
    Lista_articol() {
        sant1 = new Node();
        sant2 = new Node();
        sant1->next = sant2;
        sant2->prev = sant1;
    }

    // Деструктор: освобождает всю память
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

    // Проверка: пуст ли список?
    bool esteGoala() const {
        return sant1->next == sant2;
    }

    // Вывод списка от начала к концу
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

    // Вывод списка от конца к началу
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

    // Добавить товар (с сортировкой по коду)
    void adauga(Articol* a) {
        // Проверка на дубликат кода
        Node* curent = sant1->next;
        while (curent != sant2) {
            if (curent->inf->getCod() == a->getCod()) {
                std::cout << "Eroare: Exista deja un articol cu codul " << a->getCod() << "!" << std::endl;
                delete a;
                return;
            }
            curent = curent->next;
        }

        // Найти позицию для вставки (список отсортирован по коду)
        curent = sant1->next;
        while (curent != sant2 && curent->inf->getCod() < a->getCod()) {
            curent = curent->next;
        }

        // Вставить новый узел перед найденной позицией
        Node* newNode = new Node(a);
        newNode->next = curent;
        newNode->prev = curent->prev;
        curent->prev->next = newNode;
        curent->prev = newNode;

        std::cout << "Articolul cu codul " << a->getCod() << " a fost adaugat." << std::endl;
    }

    // Удалить товар по коду
    void sterge(int cod) {
        Node* curent = sant1->next;
        while (curent != sant2 && curent->inf->getCod() != cod) {
            curent = curent->next;
        }
        if (curent == sant2) {
            std::cout << "Articolul cu codul " << cod << " nu a fost gasit." << std::endl;
            return;
        }

        // Удалить узел из списка
        curent->prev->next = curent->next;
        curent->next->prev = curent->prev;
        delete curent->inf;
        delete curent;
        std::cout << "Articolul cu codul " << cod << " a fost sters." << std::endl;
    }

    // Поступление товара на склад
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

    // Продажа/расход товара (автоматическое удаление при нулевом остатке)
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

        // Автоматическое удаление при нулевом остатке
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

    // Изменить название и/или цену товара
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

    // Найти товар по коду
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
// ГЛАВНАЯ ФУНКЦИЯ
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
