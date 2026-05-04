#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    double xStart, xEnd, dx;
    
    cout << "Впиши: Xнач, Хкон, dx\n";
    cin >> xStart >> xEnd >> dx;

    cout << "--------------------------" << endl;
    cout << "|" << setw(10) << "X" << " | " << setw(10) << "Y" << " |" << endl;
    cout << "--------------------------" << endl;

    for (double x = xStart; x <= xEnd + dx / 2; x += dx) {
        double y;
        if (x <= -3) {
            y = x + 3;
        } else if (x <= 1) {
            y = pow(3, x);
        } else if (x <= 5) {
            y = 3 - sqrt(4 - pow(x - 3, 2));
        } else {
            y = -1.5 * x + 10.5;
        }

        cout << "|" << setw(10) << fixed << setprecision(2) << x << " | " << setw(10) << y << " |" << endl;
    }
    cout << "--------------------------" << endl;

    return 0;
}