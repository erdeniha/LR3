#include <iostream>
#include <numeric>
#include <cmath>
#include <cstdint>

using namespace std;

uint64_t NOD(uint64_t a, uint64_t b) {
    while (b) { a %= b; swap(a, b); }
    return a;
}

void amount() {
    cout << "Введите а и b: ";
    int a, b;
    if (!(cin >> a >> b)) return;

    if (b == 1) {
        cout << "infinity" << endl;
        return;
    }

    uint64_t A[11][11] = {0};
    for (int n = 1; n <= a; n++) {
        A[n][0] = 1;
        for (int k = 1; k < n; k++) {
            A[n][k] = (k + 1) * A[n - 1][k] + (n - k) * A[n - 1][k - 1];
        }
    }

    uint64_t num = 0;
    for (int k = 0; k < a; k++) {
        num += A[a][k] * (uint64_t)pow(b, a - k);
    }

    uint64_t den = pow(b - 1, a + 1);

    uint64_t common = NOD(num, den);
    cout << num / common << "/" << den / common << endl;
}

int main() {
    amount();
    return 0;
}