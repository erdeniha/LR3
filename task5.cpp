#include <iostream>
#include <vector>
#include <iomanip> 
#include <cmath>    

using namespace std;

struct Point {
    double t;  
    double Tk; 
};

void aprox(const vector<Point>& table, double& a, double& b) {
    int n = table.size();
    double sumX = 0, sumY = 0, sumXY = 0, sumX2 = 0;

    for (const auto& p : table) {
        sumX += p.t;
        sumY += p.Tk;
        sumXY += p.t * p.Tk;
        sumX2 += p.t * p.t;
    }

    a = (n * sumXY - sumX * sumY) / (n * sumX2 - sumX * sumX);
    
    b = (sumY - a * sumX) / n;
}

double korrel(const vector<Point>& table) {
    int n = table.size();
    double sumX = 0, sumY = 0;
    for (const auto& p : table) {
        sumX += p.t;
        sumY += p.Tk;
    }
    double averageX = sumX / n;
    double averageY = sumY / n;

    double num = 0, denX = 0, denY = 0;
    for (const auto& p : table) {
        num += (p.t - averageX) * (p.Tk - averageY);
        denX += pow(p.t - averageX, 2);
        denY += pow(p.Tk - averageY, 2);
    }

    return num / sqrt(denX * denY);
}

int main() {
    double Tk, Tsr, rCoeff, maxTime, dt;

    cout << "--- Параметры моделирования ---" << endl;
    cout << "Начальная температура кофе (Tk): "; cin >> Tk;
    cout << "Температура среды (Tsr): ";         cin >> Tsr;
    cout << "Коэффициент остывания (r): ";       cin >> rCoeff;
    cout << "Время наблюдения (мин): ";          cin >> maxTime;
    cout << "Шаг времени (dt): ";                cin >> dt;

    vector<Point> table;
    double currentTk = Tk;

    for (double t = 0; t <= maxTime; t += dt) {
        table.push_back({t, currentTk});
        currentTk = currentTk - rCoeff * (currentTk - Tsr) * dt;
    }

    cout << "\n" << setw(10) << "Время (мин)" << " | " << setw(15) << "Температура (C)" << endl;
    cout << "-----------------------------" << endl;
    cout << fixed << setprecision(2);
    for (const auto& row : table) {
        cout << setw(11) << row.t << " | " << setw(15) << row.Tk << endl;
    }

    double a, b;
    aprox(table, a, b);
    double r_corr = korrel(table);

    cout << "Уравнение линейной модели: y = " << a << "x + " << b << endl;
    cout << "Коэффициент корреляции(r): " << r_corr << endl;

    return 0;
}