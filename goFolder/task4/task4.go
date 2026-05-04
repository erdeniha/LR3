package main

import (
	"fmt"
	"math"
)

func main() {
	var n, m int
	if _, err := fmt.Scan(&n, &m); err != nil {
		return
	}

	a := make([]int, n)
	pref := make([]int, n+1)
	for i := 0; i < n; i++ {
		fmt.Scan(&a[i])
		pref[i+1] = pref[i] + a[i]
	}

	var pScore, vScore int
	pLast, vLast := -1, -1
	pos := 0
	isPavelTurn := true

	for pos < n {
		bestK := -1
		maxTurnSum := int(math.MinInt)

		forbiddenK := -1
		if isPavelTurn {
			forbiddenK = pLast
		} else {
			forbiddenK = vLast
		}

		for k := 1; k <= m && pos+k <= n; k++ {

			if k == forbiddenK {
				continue
			}

			currentSum := pref[pos+k] - pref[pos]

			if currentSum > maxTurnSum {
				maxTurnSum = currentSum
				bestK = k
			} else if currentSum == maxTurnSum {
				if bestK == -1 || k < bestK {
					bestK = k
				}
			}
		}

		if bestK == -1 {
			break
		}

		if isPavelTurn {
			pScore += maxTurnSum
			pLast = bestK
		} else {
			vScore += maxTurnSum
			vLast = bestK
		}

		pos += bestK
		isPavelTurn = !isPavelTurn
	}

	if pScore > vScore {
		fmt.Println(1)
	} else {
		fmt.Println(0)
	}
}
