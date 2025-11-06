#include <iostream>
using namespace std;

int main() {
    int X, Z;

    cout << "Introduceti varsta lui Nicolae (X): ";
    cin >> X;
    cout << "Introduceti varsta lui Mihai (Z): ";
    cin >> Z;


    double varsta_medie = (X + Z) / 2.0;
    int diferenta_varsta = X - Z;
    if (diferenta_varsta<0) {
        diferenta_varsta = diferenta_varsta * (-1);
    }
    cout << "Vârsta medie este: " << varsta_medie << endl;
    cout << "Diferența de vârstă este: " << diferenta_varsta << " ani" << endl;

    return 0;
}