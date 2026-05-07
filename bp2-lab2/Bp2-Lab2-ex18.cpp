// 18. Creati lista Student care contine: Numele studentului, Grupa, 3 note.
// Sa se creeze lista studentilor in ordinea descresterii notei medii.

#include <iostream>
#include <string>
using namespace std;

struct nod {
    string nume;
    string grupa;
    float nota1, nota2, nota3;
    nod *urm;
};

float medie(nod *p) {
    return (p->nota1 + p->nota2 + p->nota3) / 3.0;
}

void adauga_nod(nod *&prim, nod *&ultim, string nume, string grupa, float n1, float n2, float n3) {
    prim = new nod;
    ultim = prim;
    prim->nume  = nume;
    prim->grupa = grupa;
    prim->nota1 = n1;
    prim->nota2 = n2;
    prim->nota3 = n3;
    prim->urm   = NULL;
}

void adauga_ultim(nod *&ultim, string nume, string grupa, float n1, float n2, float n3) {
    nod *p = new nod;
    p->nume  = nume;
    p->grupa = grupa;
    p->nota1 = n1;
    p->nota2 = n2;
    p->nota3 = n3;
    p->urm   = NULL;
    ultim->urm = p;
    ultim = p;
}

void sorteaza(nod *prim) {
    bool schimbat;
    do {
        schimbat = false;
        nod *p = prim;
        while (p->urm != NULL) {
            if (medie(p) < medie(p->urm)) {
                swap(p->nume,  p->urm->nume);
                swap(p->grupa, p->urm->grupa);
                swap(p->nota1, p->urm->nota1);
                swap(p->nota2, p->urm->nota2);
                swap(p->nota3, p->urm->nota3);
                schimbat = true;
            }
            p = p->urm;
        }
    } while (schimbat);
}

void afisare(nod *prim) {
    cout << "\nNume\t\tGrupa\tNota1\tNota2\tNota3\tMedie\n";
    cout << "------------------------------------------------------\n";
    for (nod *p = prim; p != NULL; p = p->urm)
        cout << p->nume << "\t\t" << p->grupa << "\t"
             << p->nota1 << "\t" << p->nota2 << "\t" << p->nota3 << "\t"
             << medie(p) << "\n";
}

int main() {
    nod *prim, *ultim;
    int n;
    string nume, grupa;
    float n1, n2, n3;

    cout << "Introduceti numarul de studenti: ";
    cin >> n;
    cin.ignore();

    cout << "\nStudentul 1:\n";
    cout << "  Nume: ";   getline(cin, nume);
    cout << "  Grupa: ";  getline(cin, grupa);
    cout << "  Nota 1: "; cin >> n1;
    cout << "  Nota 2: "; cin >> n2;
    cout << "  Nota 3: "; cin >> n3;
    cin.ignore();
    adauga_nod(prim, ultim, nume, grupa, n1, n2, n3);

    for (int i = 1; i < n; i++) {
        cout << "\nStudentul " << i + 1 << ":\n";
        cout << "  Nume: ";   getline(cin, nume);
        cout << "  Grupa: ";  getline(cin, grupa);
        cout << "  Nota 1: "; cin >> n1;
        cout << "  Nota 2: "; cin >> n2;
        cout << "  Nota 3: "; cin >> n3;
        cin.ignore();
        adauga_ultim(ultim, nume, grupa, n1, n2, n3);
    }

    sorteaza(prim);
    afisare(prim);

    return 0;
}
