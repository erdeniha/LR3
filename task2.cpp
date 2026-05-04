#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <iomanip>

using namespace std;


uint64_t power(uint64_t a, uint64_t b, uint64_t m) {
    uint64_t res = 1;
    a %= m;
    while (b > 0) {
        if (b % 2 == 1) res = (__uint128_t)res * a % m;
        a = (__uint128_t)a * a % m;
        b /= 2;
    }
    return res;
}

vector<int> Eratostenas(int limit) {
    vector<bool> isPrime(limit + 1, true);
    isPrime[0] = isPrime[1] = false;
    for (int p = 2; p * p <= limit; p++) {
        if (isPrime[p]) {
            for (int i = p * p; i <= limit; i += p)
                isPrime[i] = false;
        }
    }
    vector<int> primes;
    for (int p = 2; p <= limit; p++)
        if (isPrime[p]) primes.push_back(p);
    return primes;
}

bool miller_test(uint64_t n, const vector<int>& factors, int t) {
    if (n < 2) return false;
    if (n == 2) return true;
    
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<uint64_t> dist(2, n - 1);  // шаг 1.1 миллера

    for (int i = 0; i < t; i++) {
        uint64_t a = dist(gen); // шаг 1.1 миллера

        if (power(a, n - 1, n) != 1) return false; // шаг 1.2 миллера

        bool potentiallyPrime = true;
        for (int q : factors) { // шаг 1.3 миллера
            if (power(a, (n - 1) / q, n) == 1) {
                potentiallyPrime = false; 
                break;
            }
        }
        if (potentiallyPrime) return true; 
    }
    return false;
}

int main() {
    int bits;
    cout << "Введите разрядность числа: ";
    cin >> bits;

    vector<int> basePrimes = Eratostenas(500); // шаг 0.1 миллера  и этап 1
    random_device rd;
    mt19937 gen(rd());

    cout << "-------------------------------------------------------\n";
    cout << setw(5) << "№" << " | " << setw(15) << "Простое число " << " | " <<
    setw(10) << "Результат проверки" << " | " <<
    setw(10) << "rejected" << endl;
    cout << "-------------------------------------------------------\n";

    
    for (int i = 1; i <= 10; i++) { // этап 3
        uint64_t n;
        vector<int> currentFactors;
        
        
        int rejected = 0; // этап 4
        bool found = false;

        while (!found) { // этап 5
            uint64_t m = 1;
            currentFactors.clear();
            currentFactors.push_back(2); 
            
            while (log2(m) < bits - 2) {    // шаг 0.2 миллера
                int q = basePrimes[gen() % basePrimes.size()];
                if (m * q > (1ULL << (bits - 1))) break;
                m *= q;
                currentFactors.push_back(q);
            }
            n = 2 * m + 1; // шаг 0.3 миллера  

            if (log2(n) >= bits - 1 && miller_test(n, currentFactors, 5)) {    // шаг 0.4 миллера
                found = true; 
            } else {
                rejected++;
            }
        }

        // Этап 6
        bool finalRes = miller_test(n, currentFactors, 2);

        cout << setw(3) << i << " | " 
             << setw(14) << n << " | " 
             << setw(18) << (finalRes ? "true" : "false") << " | " 
             << setw(10) << rejected << endl;

    }
    cout << "-------------------------------------------------------\n";

    return 0;
}