// Сортировка чисел с помощью двух стеков
// Алгоритм: вставка каждого нового числа в правильную позицию, используя вторую стеку как буфер

#include <iostream>
#include <climits>

// ============================================================================
// КЛАСС СТЕКА (LIFO - Last In, First Out)
// ============================================================================

class Stiva {
private:
    struct Node {
        int value;
        Node* next;
        Node(int val) : value(val), next(nullptr) {}
    };

    Node* top;  // Вершина стека

public:
    Stiva() : top(nullptr) {}

    ~Stiva() {
        while (!isEmpty()) {
            eliminare();
        }
    }

    // Добавить элемент на вершину стека
    void adaugare(int val) {
        Node* newNode = new Node(val);
        newNode->next = top;
        top = newNode;
    }

    // Удалить и вернуть элемент с вершины
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

    // Посмотреть значение на вершине (без удаления)
    int varf() const {
        if (isEmpty())
            return INT_MAX;
        return top->value;
    }

    // Проверить, пуст ли стек
    bool isEmpty() const {
        return top == nullptr;
    }

    // Вывести все элементы стека
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
    Stiva stiva1;  // Основной стек (будет содержать отсортированные числа)
    Stiva stiva2;  // Вспомогательный стек (буфер для перестановки)

    int numar, raspuns;

    // Ввод первого числа
    std::cout << "Introduceti primul numar: ";
    std::cin >> numar;
    stiva1.adaugare(numar);

    std::cout << "Mai adaugati un numar? (1 - Da, 0 - Nu): ";
    std::cin >> raspuns;

    // Цикл ввода и сортировки
    while (raspuns == 1) {
        std::cout << "Introduceti numarul: ";
        std::cin >> numar;

        // Случай 1: Новое число больше вершины → просто добавляем
        if (stiva1.varf() > numar) {
            stiva1.adaugare(numar);
        }
        // Случай 2: Нужно найти правильную позицию
        else {
            // Переносим все меньшие элементы в stiva2
            while (!stiva1.isEmpty() && stiva1.varf() < numar) {
                stiva2.adaugare(stiva1.eliminare());
            }

            // Вставляем новое число
            stiva1.adaugare(numar);

            // Возвращаем элементы обратно
            while (!stiva2.isEmpty()) {
                stiva1.adaugare(stiva2.eliminare());
            }
        }

        std::cout << "Mai adaugati un numar? (1 - Da, 0 - Nu): ";
        std::cin >> raspuns;
    }

    // Вывод отсортированного результата
    std::cout << "\nSirul ordonat crescator:" << std::endl;
    stiva1.afisare();

    return 0;
}
