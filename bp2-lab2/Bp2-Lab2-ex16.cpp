// 16. Creati lista liniara simplu inlantuita Elev, fiecare nod continand
// informatii referitoare la elevii unei clase (nume, medie, adresa, varsta), si apoi:
// - sa se afiseze elevul cu media cea mai mica si elevul cu media cea mai mare din lista;
// - sa se afiseze elevii ordonati descrescator dupa mediile obtinute.

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

// Functia gaseste si afiseaza elevul cu media minima si maxima
void afisare_extremi(nod *prim) {
    nod *min_p = prim;  // Initializam minimul cu primul nod
    nod *max_p = prim;  // Initializam maximul cu primul nod
    for (nod *p = prim->urm; p != NULL; p = p->urm) { // Parcurgem lista incepand cu al doilea nod
        if (p->medie < min_p->medie) min_p = p;        // Actualizam minimul daca gasim o medie mai mica
        if (p->medie > max_p->medie) max_p = p;        // Actualizam maximul daca gasim o medie mai mare
    }
    cout << "\nElevul cu media cea mai mica:\n";                          // Afisam titlul
    cout << "  Nume: " << min_p->nume << ", Medie: " << min_p->medie     // Afisam numele si media minima
         << ", Varsta: " << min_p->varsta << ", Adresa: " << min_p->adresa << "\n"; // Afisam varsta si adresa
    cout << "\nElevul cu media cea mai mare:\n";                          // Afisam titlul
    cout << "  Nume: " << max_p->nume << ", Medie: " << max_p->medie     // Afisam numele si media maxima
         << ", Varsta: " << max_p->varsta << ", Adresa: " << max_p->adresa << "\n"; // Afisam varsta si adresa
}

// Functia sorteaza lista descrescator dupa medie (bubble sort)
void sorteaza_descrescator(nod *prim) {
    bool schimbat;       // Variabila care indica daca s-a facut o interschimbare
    do {
        schimbat = false;          // La inceput nu s-a facut nicio interschimbare
        nod *p = prim;             // Pornim de la primul nod
        while (p->urm != NULL) {   // Cat timp exista un nod urmator
            if (p->medie < p->urm->medie) {             // Daca media curenta e mai mica decat cea urmatoare
                swap(p->nume,   p->urm->nume);          // Schimbam numele
                swap(p->medie,  p->urm->medie);         // Schimbam mediile
                swap(p->adresa, p->urm->adresa);        // Schimbam adresele
                swap(p->varsta, p->urm->varsta);        // Schimbam varstele
                schimbat = true;                        // Marcam ca s-a facut o interschimbare
            }
            p = p->urm; // Trecem la urmatorul nod
        }
    } while (schimbat); // Repetam cat timp se mai fac interschimbari
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

    afisare_extremi(prim);     // Afisam elevul cu media minima si maxima

    sorteaza_descrescator(prim);                             // Sortam lista descrescator
    cout << "\nElevii ordonati descrescator dupa medie:";   // Afisam titlul
    afisare(prim);             // Afisam lista sortata

    return 0; // Programul s-a terminat cu succes
}
