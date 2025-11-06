#include <iostream>
using namespace std;

int main() {
    int a, b;

    cout << "Introduceti doua numere intregi: ";
    cin >> a >> b;

    if (a + 1 == b)
        cout << "Primul numar este predecesorul celui de al doilea." << endl;
    else
        cout << "Primul numar nu este predecesorul celui de al doilea." << endl;

    return 0;
}
