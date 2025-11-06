#include <iostream>
using namespace std;

int main() {
    int h1, m1, s1;
    int h2, m2, s2;
    int hs, ms, ss;

    cout << "Introduceti primul interval (h m s): ";
    cin >> h1 >> m1 >> s1;

    cout << "Introduceti al doilea interval (h m s): ";
    cin >> h2 >> m2 >> s2;

    ss = s1 + s2;
    ms = m1 + m2 + ss / 60;
    hs = h1 + h2 + ms / 60;

    ss = ss % 60;
    ms = ms % 60;

    cout << "Suma celor doua intervale este: "
         << hs << " ore, "
         << ms << " minute si "
         << ss << " secunde." << endl;

    return 0;
}
