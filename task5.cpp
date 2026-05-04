#include <iostream>
#include <vector>
#include <iomanip> 

using namespace std;

struct Point {
    double t;  
    double Tk; 
};

int main() {
    double Tk, Tsr, r, maxTime, dt;

    cout << "--- Параметры моделирования ---" << endl;
    cout << "Начальная температура кофе (Tk): "; cin >> Tk;
    cout << "Температура среды (Tsr): ";         cin >> Tsr;
    cout << "Коэффициент остывания (r): ";       cin >> r;
    cout << "Время наблюдения (мин): ";          cin >> maxTime;
    cout << "Шаг времени (dt): ";                cin >> dt;

    vector<Point> table;
    double currentTk = Tk;

    for (double t = 0; t <= maxTime; t += dt) {
        table.push_back({t, currentTk});
        
        currentTk = currentTk - r * (currentTk - Tsr) * dt;
    }

    cout << setw(10) << "Время (мин)" << " | " << setw(15) << "Температура (C)" << endl;
    cout << "-----------------------------" << endl;
    
    cout << fixed << setprecision(2);
    
    for (const auto& row : table) {
        cout << setw(11) << row.t << " | " << setw(15) << row.Tk << endl;
    }

    return 0;
}