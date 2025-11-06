#include <iostream>
using namespace std;

int main() {
    unsigned int X;
    cin >> X;
    if (X < 1000 || X > 9999) {
        cout << "Numarul nu este un numar natural de 4 cifre!" << endl;
        return 1;
    }

    int sum = X % 1000 + X % 100 + X % 10;

    cout << "Suma numerelor este: " << sum << endl;
    return 0;
}