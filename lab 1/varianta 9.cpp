#include <iostream>
#include <cmath>
using namespace std;

int main() {
    int num;
    cout << "Introduceti aria patratului: ";
    cin >> num;

    if (num < 0) {
        cout << "Eroare: Nu se poate calcula aria" << endl;
    } else {
        int l = sqrt(num);
        cout << "Lungimea laturii este: " << l << endl;
        cout << "Perimetrul patratului este: " << 4*l << endl;
    }
}