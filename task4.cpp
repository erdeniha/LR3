#include <iostream>
#include <vector>
#include <climits>
#include <cstdint>

using namespace std;

int main() {
    int number, limit;
    if (!(cin >> number >> limit)) return 0;

    vector<int> a(number);
    vector<int> pref(number + 1, 0);
    for (int i = 0; i < number; ++i) {
        cin >> a[i];
        pref[i + 1] = pref[i] + a[i]; 
    }

    int pavelScore = 0;
    int vikaScore = 0;
    int pos = 0; 
    
    int pavelLastLimit = -1;
    int vikaLastLimit = -1;
    
    bool isPavelTurn = true;

    while (pos < number) {
        int bestNum = -1;
        int maxTurnSum = INT_MIN;

        int forbiddenNum = isPavelTurn ? pavelLastLimit : vikaLastLimit;

        for (int k = 1; k <= limit && pos + k <= number; ++k) {
            if (k == forbiddenNum) continue;

            int currentSum = pref[pos + k] - pref[pos];

            if (currentSum > maxTurnSum) {
                maxTurnSum = currentSum;
                bestNum = k;
            } else if (currentSum == maxTurnSum) {
                if (bestNum == -1 || k < bestNum) {
                    bestNum = k;
                }
            }
        }

        if (bestNum == -1) break; 

        if (isPavelTurn) {
            pavelScore += maxTurnSum;
            pavelLastLimit = bestNum;
        } else {
            vikaScore += maxTurnSum;
            vikaLastLimit = bestNum;
        }

        pos += bestNum;
        isPavelTurn = !isPavelTurn; 
    }

    if (pavelScore > vikaScore) {
        cout << 1 << endl;
    } else {
        cout << 0 << endl;
    }

    return 0;
}