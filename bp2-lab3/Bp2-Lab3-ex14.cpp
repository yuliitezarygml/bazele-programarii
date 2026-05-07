// Игра "Красная гусыня" (Gâsca Roșie) - симуляция карточной игры с использованием очередей
// Правила: два игрока кладут карты на стол, при совпадении цвета игрок забирает все карты со стола

#include <iostream>
#include <string>
using namespace std;

// ============================================================================
// СТРУКТУРА УЗЛА ОЧЕРЕДИ (КАРТА)
// ============================================================================

struct nod {
    int valoare;      // Значение карты (1-8)
    string suit;      // Масть: Inima(червы), Romb(бубны), Trefla(трефы), Pica(пики)
    string culoare;   // Цвет: rosie(красная) или neagra(черная)
    nod *urm;         // Указатель на следующую карту
};

// ============================================================================
// ОПЕРАЦИИ С ОЧЕРЕДЬЮ
// ============================================================================

// Добавить карту в конец очереди
void adauga_sfarsit(nod *&prim, nod *&ultim, int val, string s, string c) {
    nod *p = new nod;
    p->valoare = val;
    p->suit = s;
    p->culoare = c;
    p->urm = nullptr;

    if (prim == nullptr) {
        prim = ultim = p;
    } else {
        ultim->urm = p;
        ultim = p;
    }
}

// Удалить первую карту из очереди
void scoate_primul(nod *&prim, nod *&ultim) {
    if (prim == nullptr) {
        return;
    }

    nod *temp = prim;
    prim = prim->urm;

    if (prim == nullptr) {
        ultim = nullptr;
    }

    delete temp;
}

// Переместить все карты со стола в пакет игрока
void muta_masa_la_pachet(nod *&prim_masa, nod *&ultim_masa, nod *&prim_pachet, nod *&ultim_pachet) {
    if (prim_masa == nullptr) {
        return;
    }

    if (prim_pachet == nullptr) {
        prim_pachet = prim_masa;
        ultim_pachet = ultim_masa;
    } else {
        ultim_pachet->urm = prim_masa;
        ultim_pachet = ultim_masa;
    }

    prim_masa = ultim_masa = nullptr;
}

// Вывести все карты в очереди
void afisare(nod *prim) {
    if (prim == nullptr) {
        cout << "Pachetul este gol." << endl;
        return;
    }

    nod *curent = prim;
    while (curent != nullptr) {
        cout << curent->valoare << " " << curent->suit << " (" << curent->culoare << ") ";
        curent = curent->urm;
    }
    cout << endl;
}

// Подсчитать количество карт в очереди
int numarare(nod *prim) {
    int count = 0;
    nod *curent = prim;
    while (curent != nullptr) {
        count++;
        curent = curent->urm;
    }
    return count;
}

// ============================================================================
// ГЛАВНАЯ ФУНКЦИЯ - ИГРОВОЙ ЦИКЛ
// ============================================================================

int main() {
    // Очереди для двух игроков
    nod *prim1 = nullptr, *ultim1 = nullptr;  // Пакет игрока 1
    nod *prim2 = nullptr, *ultim2 = nullptr;  // Пакет игрока 2
    nod *prim_masa = nullptr, *ultim_masa = nullptr;  // Карты на столе

    cout << "=== JOCUL GÂSCA ROȘIE ===" << endl;
    cout << "Regulile: Doi jucători pun câte o carte pe masă." << endl;
    cout << "Dacă culorile coincid, jucătorul ia toate cărțile de pe masă.\n" << endl;

    // Инициализация пакетов игроков (пример из PDF)
    // Игрок 1: 8 карт
    adauga_sfarsit(prim1, ultim1, 1, "Inima", "rosie");
    adauga_sfarsit(prim1, ultim1, 2, "Romb", "rosie");
    adauga_sfarsit(prim1, ultim1, 3, "Trefla", "neagra");
    adauga_sfarsit(prim1, ultim1, 4, "Pica", "neagra");
    adauga_sfarsit(prim1, ultim1, 5, "Inima", "rosie");
    adauga_sfarsit(prim1, ultim1, 6, "Romb", "rosie");
    adauga_sfarsit(prim1, ultim1, 7, "Trefla", "neagra");
    adauga_sfarsit(prim1, ultim1, 8, "Pica", "neagra");

    // Игрок 2: 8 карт
    adauga_sfarsit(prim2, ultim2, 1, "Trefla", "neagra");
    adauga_sfarsit(prim2, ultim2, 2, "Pica", "neagra");
    adauga_sfarsit(prim2, ultim2, 3, "Inima", "rosie");
    adauga_sfarsit(prim2, ultim2, 4, "Romb", "rosie");
    adauga_sfarsit(prim2, ultim2, 5, "Trefla", "neagra");
    adauga_sfarsit(prim2, ultim2, 6, "Pica", "neagra");
    adauga_sfarsit(prim2, ultim2, 7, "Inima", "rosie");
    adauga_sfarsit(prim2, ultim2, 8, "Romb", "rosie");

    cout << "Pachetul inițial al jucătorului 1 (" << numarare(prim1) << " cărți):" << endl;
    afisare(prim1);

    cout << "\nPachetul inițial al jucătorului 2 (" << numarare(prim2) << " cărți):" << endl;
    afisare(prim2);

    // Игровой цикл
    int runda = 1;
    while (prim1 != nullptr && prim2 != nullptr) {
        cout << "\n--- Runda " << runda << " ---" << endl;

        // Игрок 1 кладет карту на стол
        cout << "Jucătorul 1 pune: " << prim1->valoare << " " << prim1->suit << " (" << prim1->culoare << ")" << endl;
        adauga_sfarsit(prim_masa, ultim_masa, prim1->valoare, prim1->suit, prim1->culoare);
        string culoare1 = prim1->culoare;
        scoate_primul(prim1, ultim1);

        // Игрок 2 кладет карту на стол
        cout << "Jucătorul 2 pune: " << prim2->valoare << " " << prim2->suit << " (" << prim2->culoare << ")" << endl;
        adauga_sfarsit(prim_masa, ultim_masa, prim2->valoare, prim2->suit, prim2->culoare);
        string culoare2 = prim2->culoare;
        scoate_primul(prim2, ultim2);

        // Проверка совпадения цветов
        if (culoare1 == culoare2) {
            cout << ">>> Culorile coincid! ";

            // Определяем победителя раунда (последний положивший карту того же цвета)
            if (culoare2 == "rosie") {
                cout << "Jucătorul 2 ia toate cărțile de pe masă!" << endl;
                muta_masa_la_pachet(prim_masa, ultim_masa, prim2, ultim2);
            } else {
                cout << "Jucătorul 2 ia toate cărțile de pe masă!" << endl;
                muta_masa_la_pachet(prim_masa, ultim_masa, prim2, ultim2);
            }
        } else {
            cout << "Culorile nu coincid. Cărțile rămân pe masă." << endl;
        }

        cout << "Cărți pe masă: " << numarare(prim_masa) << endl;
        cout << "Jucătorul 1: " << numarare(prim1) << " cărți" << endl;
        cout << "Jucătorul 2: " << numarare(prim2) << " cărți" << endl;

        runda++;

        // Ограничение на количество раундов для предотвращения бесконечного цикла
        if (runda > 50) {
            cout << "\nJocul s-a terminat după 50 de runde (limită de siguranță)." << endl;
            break;
        }
    }

    // Определение победителя
    cout << "\n=== REZULTATUL FINAL ===" << endl;
    if (prim1 == nullptr && prim2 == nullptr) {
        cout << "Remiză! Ambii jucători au rămas fără cărți." << endl;
    } else if (prim1 == nullptr) {
        cout << "Jucătorul 2 a câștigat! Jucătorul 1 a rămas fără cărți." << endl;
        cout << "Cărți rămase jucătorului 2: " << numarare(prim2) << endl;
    } else {
        cout << "Jucătorul 1 a câștigat! Jucătorul 2 a rămas fără cărți." << endl;
        cout << "Cărți rămase jucătorului 1: " << numarare(prim1) << endl;
    }

    // Освобождение памяти
    while (prim1 != nullptr) scoate_primul(prim1, ultim1);
    while (prim2 != nullptr) scoate_primul(prim2, ultim2);
    while (prim_masa != nullptr) scoate_primul(prim_masa, ultim_masa);

    return 0;
}
