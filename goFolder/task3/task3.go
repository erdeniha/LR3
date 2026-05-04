package main

import (
	"fmt"
	"math"
)

func NOD(a, b uint64) uint64 {
	for b != 0 {
		a %= b
		a, b = b, a
	}
	return a
}

func main() {
	fmt.Print("Введите a и b: ")
	var a, b int
	fmt.Scan(&a, &b)

	if b == 1 {
		fmt.Println("infinity")
		return
	}

	A := make([][]uint64, a+1)
	for i := range A {
		A[i] = make([]uint64, a+1)
	}

	for n := 1; n <= a; n++ {
		A[n][0] = 1
		for k := 1; k < n; k++ {
			A[n][k] = uint64(k+1)*A[n-1][k] + uint64(n-k)*A[n-1][k-1]
		}
	}

	var num uint64 = 0
	for k := 0; k < a; k++ {
		num += A[a][k] * uint64(math.Pow(float64(b), float64(a-k)))
	}

	den := uint64(math.Pow(float64(b-1), float64(a+1)))

	common := NOD(num, den)
	fmt.Printf("%d/%d\n", num/common, den/common)
}
