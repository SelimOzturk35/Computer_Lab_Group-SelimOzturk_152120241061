#include <iostream>

using namespace std;

int main() {
    char str[100];

    cout << "Stringi giriniz: ";
    cin >> str;

    cout << "Ilk: ";
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] >= 'A' && str[i] <= 'Z') {
            cout << char(str[i] + ('a' - 'A'));
        } else {
            cout << str[i];
        }
    }
    cout << endl;

    cout << "Ikinci: ";
    int u = 0;
    while (str[u] != '\0') {
        u++;
    }

    for (int i = u - 1; i >= 0; i--) {
        cout << str[i];
    }
    cout << endl;

    return 0;
}
