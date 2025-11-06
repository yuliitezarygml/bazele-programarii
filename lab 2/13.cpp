#include <iostream>
using namespace std;

int main() {
    int n;      // numărul de pungulițe
    int m;      // numărul de straturi
    int nr;     // numărul de metri per strat
    int S;      // grame de semințe necesare per metru

    cout << "Introduceti numarul de pungulite: ";
    cin >> n;
    cout << "Introduceti numarul de straturi: ";
    cin >> m;
    cout << "Introduceti lungimea fiecarui strat (in metri): ";
    cin >> nr;
    cout << "Introduceti cantitatea de seminte necesara pentru un metru (in grame): ";
    cin >> S;

    // Cantitatea totală de semințe pe care o are Alina
    int totalSeminte = n * 20;

    // Cantitatea totală de semințe necesară
    int necesar = m * nr * S;

    cout << "\nAlina are " << totalSeminte << " grame de seminte." << endl;
    cout << "Pentru intreaga gradinuta are nevoie de " << necesar << " grame." << endl;

    if (totalSeminte >= necesar)
        cout << "Alinei ii ajung semintele pentru intreaga gradinuta." << endl;
    else
        cout << "Alinei nu ii ajung semintele pentru intreaga gradinuta." << endl;

    return 0;
}
