// 17. Creati lista liniara simplu inlantuita Elev, fiecare nod continand
// informatii referitoare la elevii unei clase (nume, medie, adresa, varsta), si apoi:
// - sa se afiseze elevul de pe pozitia k din lista;
// - sa se caute informatii despre un elev dupa numele, citit de la tastatura.

#include <iostream>  // Biblioteca pentru operatii de intrare/iesire
#include <string>    // Biblioteca pentru tipul string
using namespace std; // Folosim spatiul de nume standard

struct nod {         // Definim structura unui nod al listei
    string nume;     // Campul pentru numele elevului
    float medie;     // Campul pentru media elevului
    string adresa;   // Campul pentru adresa elevului
    int varsta;      // Campul pentru varsta elevului
    nod *urm;        // Pointer catre urmatorul nod din lista
};

// Functia creaza primul nod al listei
void adauga_nod(nod *&prim, nod *&ultim, string nume, float medie, string adresa, int varsta) {
    prim = new nod;        // Alocam memorie pentru primul nod
    ultim = prim;          // Ultimul nod este acelasi cu primul
    prim->nume   = nume;   // Atribuim numele
    prim->medie  = medie;  // Atribuim media
    prim->adresa = adresa; // Atribuim adresa
    prim->varsta = varsta; // Atribuim varsta
    prim->urm    = NULL;   // Urmatorul nod este NULL (sfarsitul listei)
}

// Functia adauga un nod nou la sfarsitul listei
void adauga_ultim(nod *&ultim, string nume, float medie, string adresa, int varsta) {
    nod *p = new nod;      // Alocam memorie pentru noul nod
    p->nume   = nume;      // Atribuim numele
    p->medie  = medie;     // Atribuim media
    p->adresa = adresa;    // Atribuim adresa
    p->varsta = varsta;    // Atribuim varsta
    p->urm    = NULL;      // Noul nod nu are succesor
    ultim->urm = p;        // Legam noul nod dupa ultimul
    ultim = p;             // Actualizam pointerul la ultimul nod
}

// Functia afiseaza toti elevii din lista
void afisare(nod *prim) {
    cout << "\nNume\t\tMedie\tVarsta\tAdresa\n";              // Afisam antetul tabelului
    cout << "------------------------------------------------------\n"; // Linie separatoare
    for (nod *p = prim; p != NULL; p = p->urm)               // Parcurgem lista de la inceput pana la sfarsit
        cout << p->nume << "\t\t" << p->medie << "\t"        // Afisam numele si media
             << p->varsta << "\t" << p->adresa << "\n";      // Afisam varsta si adresa
}

// Functia afiseaza elevul de pe pozitia k din lista
void afisare_pozitia_k(nod *prim, int k) {
    nod *p = prim; // Pornim de la primul nod
    int i = 1;     // Contorul de pozitie incepe de la 1
    while (p != NULL && i < k) { // Parcurgem lista pana la pozitia k
        p = p->urm; // Trecem la urmatorul nod
        i++;        // Incrementam contorul
    }
    if (p == NULL) {                                         // Daca am depasit lista
        cout << "\nPozitia " << k << " nu exista in lista.\n"; // Afisam eroare
    } else {
        cout << "\nElevul de pe pozitia " << k << ":\n";       // Afisam titlul
        cout << "  Nume: " << p->nume << ", Medie: " << p->medie  // Afisam numele si media
             << ", Varsta: " << p->varsta << ", Adresa: " << p->adresa << "\n"; // Afisam varsta si adresa
    }
}

// Functia cauta un elev dupa nume in lista
void cauta_dupa_nume(nod *prim, string cautare) {
    bool gasit = false;                        // Initial elevul nu a fost gasit
    for (nod *p = prim; p != NULL; p = p->urm) { // Parcurgem toata lista
        if (p->nume == cautare) {              // Daca numele se potriveste
            cout << "\nElev gasit:\n";         // Afisam mesaj de succes
            cout << "  Nume: " << p->nume << ", Medie: " << p->medie  // Afisam numele si media
                 << ", Varsta: " << p->varsta << ", Adresa: " << p->adresa << "\n"; // Afisam varsta si adresa
            gasit = true;                      // Marcam ca elevul a fost gasit
        }
    }
    if (!gasit)                                // Daca elevul nu a fost gasit
        cout << "\nElevul cu numele \"" << cautare << "\" nu a fost gasit.\n"; // Afisam eroare
}

int main() {
    nod *prim, *ultim;   // Pointeri catre primul si ultimul nod al listei
    int n;               // Numarul de elevi
    string nume, adresa; // Variabile pentru nume si adresa
    float medie;         // Variabila pentru medie
    int varsta;          // Variabila pentru varsta

    cout << "Introduceti numarul de elevi: "; // Cerem numarul de elevi
    cin >> n;                                  // Citim numarul de elevi
    cin.ignore();                              // Ignoram caracterul newline ramas in buffer

    cout << "\nElevul 1:\n";                        // Afisam mesaj pentru primul elev
    cout << "  Nume: ";   getline(cin, nume);       // Citim numele
    cout << "  Medie: ";  cin >> medie;             // Citim media
    cin.ignore();                                    // Ignoram newline
    cout << "  Adresa: "; getline(cin, adresa);     // Citim adresa
    cout << "  Varsta: "; cin >> varsta;            // Citim varsta
    cin.ignore();                                    // Ignoram newline
    adauga_nod(prim, ultim, nume, medie, adresa, varsta); // Cream primul nod

    for (int i = 1; i < n; i++) {                         // Bucla pentru restul elevilor
        cout << "\nElevul " << i + 1 << ":\n";            // Afisam numarul elevului
        cout << "  Nume: ";   getline(cin, nume);         // Citim numele
        cout << "  Medie: ";  cin >> medie;               // Citim media
        cin.ignore();                                      // Ignoram newline
        cout << "  Adresa: "; getline(cin, adresa);       // Citim adresa
        cout << "  Varsta: "; cin >> varsta;              // Citim varsta
        cin.ignore();                                      // Ignoram newline
        adauga_ultim(ultim, nume, medie, adresa, varsta); // Adaugam nodul la sfarsitul listei
    }

    afisare(prim); // Afisam toti elevii din lista

    int k;
    cout << "\nIntroduceti pozitia k: "; // Cerem pozitia k
    cin >> k;                             // Citim pozitia
    afisare_pozitia_k(prim, k);          // Afisam elevul de pe pozitia k

    string cautare;
    cout << "\nIntroduceti numele elevului cautat: "; // Cerem numele de cautat
    cin.ignore();                                      // Ignoram newline
    getline(cin, cautare);                             // Citim numele
    cauta_dupa_nume(prim, cautare);                    // Cautam elevul dupa nume

    return 0; // Programul s-a terminat cu succes
}
