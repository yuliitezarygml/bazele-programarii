#include <iostream>
using namespace std;

int main() {
    int zi;
    cout << "Introduceti ziua lunii (1-31): ";
    cin >> zi;

    if (zi >= 1 && zi <= 10)
        cout << "Decada I" << endl;
    else if (zi >= 11 && zi < 20)
        cout << "Decada II" << endl;
    else if (zi >= 21 && zi <= 30)
        cout << "Decada III" << endl;
    else if (zi == 31)
        cout << "Decada IV" << endl;
    else
        cout << "Zi invalida!" << endl;

    return 0;
}
