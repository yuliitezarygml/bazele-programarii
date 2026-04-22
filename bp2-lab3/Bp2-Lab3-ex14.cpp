// 14. Sa se simuleze, folosind structuri dinamice de date, jocul "Gasca Rosie"
// jucat de doi jucatori. Un pachet de 32 de carti este impartit in mod egal
// celor doi jucatori. Cartile se tin cu fata in jos, jucatorii pun alternativ
// pe masa cu fata in sus cartea din varful pachetului lor.
// Daca s-a pus o carte rosie, celalalt jucator ia intregul pachet de carti
// de pe masa si-l pune sub pachetul sau.
// Jocul continua pana cand unul din jucatori ramane fara carti. Acesta castiga.

#include <iostream>  // Biblioteca pentru operatii de intrare/iesire
#include <string>    // Biblioteca pentru tipul string
using namespace std; // Folosim spatiul de nume standard

struct nod {              // Definim structura unui nod (o carte de joc)
    int valoare;          // Valoarea cartii (1-8)
    string suit;          // Culoarea cartii: "Inima", "Romb", "Trefla", "Pica"
    string culoare;       // Culoarea pentru joc: "rosie" sau "neagra"
    nod *urm;             // Pointer catre urmatoarea carte din pachet
};

// Functia adauga o carte la sfarsitul cozii (pachetului)
void adauga_sfarsit(nod *&prim, nod *&ultim, int val, string suit, string culoare) {
    nod *p = new nod;       // Alocam memorie pentru noua carte
    p->valoare  = val;      // Atribuim valoarea cartii
    p->suit     = suit;     // Atribuim culoarea cartii
    p->culoare  = culoare;  // Atribuim culoarea pentru joc
    p->urm      = NULL;     // Noua carte nu are succesor
    if (prim == NULL) {     // Daca pachetul este gol
        prim = ultim = p;   // Prima si ultima carte sunt aceeasi
    } else {                // Altfel
        ultim->urm = p;     // Legam noua carte dupa ultima
        ultim = p;          // Actualizam pointerul la ultima carte
    }
}

// Functia scoate si returneaza prima carte din pachet (din fata cozii)
nod* scoate_primul(nod *&prim, nod *&ultim) {
    if (prim == NULL) return NULL; // Daca pachetul e gol, returnam NULL
    nod *p = prim;                 // Retinem pointerul la prima carte
    prim = prim->urm;              // Mutam inceputul pachetului la urmatoarea carte
    if (prim == NULL) ultim = NULL; // Daca pachetul a ramas gol, actualizam si ultimul
    p->urm = NULL;                 // Decuplam carta scoasa de la lista
    return p;                      // Returnam carta scoasa
}

// Functia muta toate cartile de pe masa la sfarsitul pachetului unui jucator
void muta_masa_la_pachet(nod *&masa_prim, nod *&masa_ultim,
                          nod *&pac_prim,  nod *&pac_ultim) {
    if (masa_prim == NULL) return;     // Daca masa e goala, nu facem nimic
    if (pac_prim == NULL) {            // Daca pachetul jucatorului e gol
        pac_prim  = masa_prim;         // Pachetul devine cartile de pe masa
        pac_ultim = masa_ultim;        // Actualizam si ultimul element
    } else {                           // Altfel
        pac_ultim->urm = masa_prim;    // Legam cartile de pe masa dupa ultimul din pachet
        pac_ultim = masa_ultim;        // Actualizam pointerul la ultima carte
    }
    masa_prim = masa_ultim = NULL;     // Golim masa
}

// Functia numara cartile dintr-un pachet
int numar_carti(nod *prim) {
    int n = 0;                                      // Contorul incepe de la 0
    for (nod *p = prim; p != NULL; p = p->urm) n++; // Parcurgem lista si numaram
    return n;                                       // Returnam numarul de carti
}

int main() {
    nod *juc1_prim = NULL, *juc1_ultim = NULL; // Pachetul Jucatorului 1
    nod *juc2_prim = NULL, *juc2_ultim = NULL; // Pachetul Jucatorului 2
    nod *masa_prim = NULL, *masa_ultim = NULL; // Cartile de pe masa

    // Definim cele 4 tipuri si culorile lor de joc
    string suit_name[] = {"Inima", "Romb",   "Trefla", "Pica"  }; // Tipurile cartilor
    string suit_col[]  = {"rosie", "rosie",  "neagra", "neagra"}; // Culoarea fiecarui tip

    // Cream pachetul temporar de 32 de carti (4 tipuri x 8 valori)
    nod *pac_prim = NULL, *pac_ultim = NULL; // Pachetul temporar initial
    for (int s = 0; s < 4; s++)              // Parcurgem cele 4 tipuri
        for (int v = 1; v <= 8; v++)         // Parcurgem valorile 1-8
            adauga_sfarsit(pac_prim, pac_ultim, v, suit_name[s], suit_col[s]); // Adaugam carta

    // Distribuim cartile alternand: carta 1 la J1, carta 2 la J2, etc.
    for (int i = 0; i < 32; i++) {                          // Distribuim toate 32 de carti
        nod *p = scoate_primul(pac_prim, pac_ultim);        // Scoatem prima carta din pachet
        if (i % 2 == 0)                                     // Daca e pozitie para
            adauga_sfarsit(juc1_prim, juc1_ultim, p->valoare, p->suit, p->culoare); // Merge la J1
        else                                                // Altfel
            adauga_sfarsit(juc2_prim, juc2_ultim, p->valoare, p->suit, p->culoare); // Merge la J2
        delete p;                                           // Eliberam nodul temporar
    }

    cout << "=== Jocul 'Gasca Rosie' ===\n";
    cout << "Jucatorul 1: " << numar_carti(juc1_prim) << " carti\n"; // Afisam nr. carti J1
    cout << "Jucatorul 2: " << numar_carti(juc2_prim) << " carti\n\n"; // Afisam nr. carti J2

    int tura = 1;              // Jucatorul 1 incepe primul
    int runda = 0;             // Contorul de runde
    const int MAX_RUNDE = 500; // Limita maxima de runde pentru evitarea buclei infinite

    // Jocul continua cat timp ambii jucatori au carti si nu s-a depasit limita
    while (juc1_prim != NULL && juc2_prim != NULL && runda < MAX_RUNDE) {
        runda++;   // Incrementam numarul rundei
        nod *carte; // Pointerul la carta jucata in aceasta runda

        if (tura == 1) {                                              // Daca e randul lui J1
            carte = scoate_primul(juc1_prim, juc1_ultim);            // J1 scoate prima sa carte
            cout << "Runda " << runda << " | J1 pune: "
                 << carte->valoare << " " << carte->suit
                 << " (" << carte->culoare << ")";                    // Afisam carta jucata
        } else {                                                      // Altfel e randul lui J2
            carte = scoate_primul(juc2_prim, juc2_ultim);            // J2 scoate prima sa carte
            cout << "Runda " << runda << " | J2 pune: "
                 << carte->valoare << " " << carte->suit
                 << " (" << carte->culoare << ")";                    // Afisam carta jucata
        }

        bool este_rosie = (carte->culoare == "rosie"); // Verificam daca e carte rosie

        // Punem carta pe masa
        adauga_sfarsit(masa_prim, masa_ultim, carte->valoare, carte->suit, carte->culoare);
        delete carte; // Eliberam memoria nodului temporar

        if (este_rosie) {                                  // Daca carta pusa e rosie
            int nr_masa = numar_carti(masa_prim);          // Numaram cartile de pe masa
            if (tura == 1) {                               // Daca a jucat J1
                cout << " -> ROSIE! J2 ia " << nr_masa << " carti de pe masa\n"; // Afisam mesaj
                muta_masa_la_pachet(masa_prim, masa_ultim, juc2_prim, juc2_ultim); // J2 ia masa
            } else {                                       // Daca a jucat J2
                cout << " -> ROSIE! J1 ia " << nr_masa << " carti de pe masa\n"; // Afisam mesaj
                muta_masa_la_pachet(masa_prim, masa_ultim, juc1_prim, juc1_ultim); // J1 ia masa
            }
        } else {         // Daca carta nu e rosie
            cout << "\n"; // Trecem la linie noua
        }

        // Afisam starea curenta a jocului
        cout << "   [J1: " << numar_carti(juc1_prim)
             << " | Masa: " << numar_carti(masa_prim)
             << " | J2: " << numar_carti(juc2_prim) << "]\n";

        tura = (tura == 1) ? 2 : 1; // Schimbam tura: daca era J1 devine J2 si invers
    }

    cout << "\n=== REZULTAT ===\n"; // Afisam sectiunea rezultat
    if (juc1_prim == NULL)          // Daca J1 a ramas fara carti
        cout << "Jucatorul 1 a ramas fara carti -> JUCATORUL 2 CASTIGA!\n"; // J2 castiga
    else if (juc2_prim == NULL)     // Daca J2 a ramas fara carti
        cout << "Jucatorul 2 a ramas fara carti -> JUCATORUL 1 CASTIGA!\n"; // J1 castiga
    else                            // Daca s-a atins limita de runde
        cout << "Jocul a atins limita de " << MAX_RUNDE << " runde. Egalitate!\n"; // Egalitate

    return 0; // Programul s-a terminat cu succes
}
