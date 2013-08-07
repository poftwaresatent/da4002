package main

import "fmt"

func fibonacciRecursiveNaive(n int) int {
	if n < 2 {
		return 1
	}
	return fibonacciRecursiveNaive(n-2) + fibonacciRecursiveNaive(n-1)
}

func fibonacciImperativeNaive(n int) int {
	if n < 2 {
		return 1
	}
	f1 := 1
	f2 := 1
	var ff int
	for ; n >= 2; n -= 1 {
		ff = f1 + f2
		f2 = f1
		f1 = ff
	}
	return ff
}

func fibonacciRecursiveMemo() func(int) int {
	memo := []int { 1, 1 }
	var frm func(n int) int
	frm = func(n int) int {
		if n < len(memo) {
			return memo[n]
		}
		ff := frm(n-2) + frm(n-1)
		if n == len(memo) {
			memo = append(memo, ff)
		}
		return ff;
	}
	return frm
}

func fibonacciImperativeMemo() func(int) int {
	memo := []int { 1, 1 }
	return func(n int) int {
		for i := len(memo); i <= n; i += 1 {
			memo = append(memo, memo[i-2] + memo[i-1])
		}
		return memo[n]
	}
}

func main() {
	fib := []func(int) int {
		fibonacciRecursiveNaive,
		fibonacciImperativeNaive,
		fibonacciRecursiveMemo(),
		fibonacciImperativeMemo() }
	
	for n := 0; n <= 20; n += 1 {
		fmt.Printf("%3d", n)
		for _,f := range(fib) {
			fmt.Printf("  %5d", f(n))
		}
		fmt.Println()
	}
}
