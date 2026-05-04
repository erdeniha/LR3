package main

import (
	"fmt"
	"math"
)

func main() {
	var xStart, xEnd, dx float64
	fmt.Print("Впиши: Xнач, Хкон, dx\n")
	fmt.Scan(&xStart, &xEnd, &dx)

	fmt.Println("--------------------------")
	fmt.Printf("| %10s | %10s |\n", "X", "Y")
	fmt.Println("--------------------------")

	for x := xStart; x <= xEnd+dx/2; x += dx {
		var y float64
		if x <= -3 {
			y = x + 3
		} else if x <= 1 {
			y = math.Pow(3, x)
		} else if x <= 5 {
			y = 3 - math.Sqrt(4-math.Pow(x-3, 2))
		} else {
			y = -1.5*x + 10.5
		}
		fmt.Printf("| %10.2f | %10.2f |\n", x, y)
	}
	fmt.Println("--------------------------")
}
