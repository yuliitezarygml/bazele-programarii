/*
Problema 14: Jocul "Gâsca Roșie"

Cerință:
Doi jucători joacă un joc de cărți, folosind un pachet de 16 cărți (câte 8 cărți fiecare).
Cărțile au valori de la 1 la 8 și aparțin la patru culori:
- Inima (roșu)
- Romb (roșu)
- Trefla (negru)
- Pica (negru)

Regulile jocului:
1. Jucătorii pun pe rând câte o carte pe masă
2. Dacă culorile cărților coincid (ambele roșii sau ambele negre):
   - Jucătorul care a pus a doua carte ia toate cărțile de pe masă
   - Cărțile luate se adaugă la sfârșitul pachetului său
3. Dacă culorile nu coincid - cărțile rămân pe masă
4. Jocul continuă până când unul dintre jucători rămâne fără cărți
5. Câștigă jucătorul care mai are cărți

Implementare:
- Se folosesc trei cozi (FIFO): pachetul jucătorului 1, pachetul jucătorului 2, cărțile de pe masă
- Operații: adăugare la sfârșitul cozii, eliminare de la început, mutarea întregii cozi
*/

#include <iostream>
#include <string>
using namespace std;

// ============================================================================
// STRUCTURA NODULUI COZII (CARTE)
// ============================================================================

struct nod {
    int valoare;      // Valoarea cărții (1-8)
    string suit;      // Culoarea: Inima, Romb, Trefla, Pica
    string culoare;   // Culoare: rosie (roșu) sau neagra (negru)
    nod *urm;         // Pointer către următoarea carte
};

// ============================================================================
// OPERAȚII CU COADA
// ============================================================================

// Adăugarea cărții la sfârșitul cozii
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

// Eliminarea primei cărți din coadă
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

// Mutarea tuturor cărților de pe masă în pachetul jucătorului
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

// Afișarea tuturor cărților din coadă
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

// Numărarea cărților din coadă
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
// FUNCȚIA PRINCIPALĂ - CICLUL DE JOC
// ============================================================================

int main() {
    // Cozile pentru cei doi jucători
    nod *prim1 = nullptr, *ultim1 = nullptr;  // Pachetul jucătorului 1
    nod *prim2 = nullptr, *ultim2 = nullptr;  // Pachetul jucătorului 2
    nod *prim_masa = nullptr, *ultim_masa = nullptr;  // Cărțile de pe masă

    cout << "=== JOCUL GÂSCA ROȘIE ===" << endl;
    cout << "Regulile: Doi jucători pun câte o carte pe masă." << endl;
    cout << "Dacă culorile coincid, jucătorul ia toate cărțile de pe masă.\n" << endl;

    // Inițializarea pachetelor jucătorilor (exemplu din PDF)
    // Jucătorul 1: 8 cărți
    adauga_sfarsit(prim1, ultim1, 1, "Inima", "rosie");
    adauga_sfarsit(prim1, ultim1, 2, "Romb", "rosie");
    adauga_sfarsit(prim1, ultim1, 3, "Trefla", "neagra");
    adauga_sfarsit(prim1, ultim1, 4, "Pica", "neagra");
    adauga_sfarsit(prim1, ultim1, 5, "Inima", "rosie");
    adauga_sfarsit(prim1, ultim1, 6, "Romb", "rosie");
    adauga_sfarsit(prim1, ultim1, 7, "Trefla", "neagra");
    adauga_sfarsit(prim1, ultim1, 8, "Pica", "neagra");

    // Jucătorul 2: 8 cărți
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

    // Ciclul de joc
    int runda = 1;
    while (prim1 != nullptr && prim2 != nullptr) {
        cout << "\n--- Runda " << runda << " ---" << endl;

        // Jucătorul 1 pune o carte pe masă
        cout << "Jucătorul 1 pune: " << prim1->valoare << " " << prim1->suit << " (" << prim1->culoare << ")" << endl;
        adauga_sfarsit(prim_masa, ultim_masa, prim1->valoare, prim1->suit, prim1->culoare);
        string culoare1 = prim1->culoare;
        scoate_primul(prim1, ultim1);

        // Jucătorul 2 pune o carte pe masă
        cout << "Jucătorul 2 pune: " << prim2->valoare << " " << prim2->suit << " (" << prim2->culoare << ")" << endl;
        adauga_sfarsit(prim_masa, ultim_masa, prim2->valoare, prim2->suit, prim2->culoare);
        string culoare2 = prim2->culoare;
        scoate_primul(prim2, ultim2);

        // Verificarea coinciderii culorilor
        if (culoare1 == culoare2) {
            cout << ">>> Culorile coincid! ";

            // Determinăm câștigătorul rundei (ultimul care a pus cartea de aceeași culoare)
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

        // Limită de runde pentru prevenirea buclei infinite
        if (runda > 50) {
            cout << "\nJocul s-a terminat după 50 de runde (limită de siguranță)." << endl;
            break;
        }
    }

    // Determinarea câștigătorului
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

    // Eliberarea memoriei
    while (prim1 != nullptr) scoate_primul(prim1, ultim1);
    while (prim2 != nullptr) scoate_primul(prim2, ultim2);
    while (prim_masa != nullptr) scoate_primul(prim_masa, ultim_masa);

    return 0;
}
