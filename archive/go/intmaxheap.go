package main

import "fmt"
import "os"
import "strconv"


func bubble_up(heap []int, index int) {
	parent := index / 2
	for parent > 0 && heap[index] > heap[parent] {
		heap[index], heap[parent] = heap[parent], heap[index]
		index = parent
		parent = index / 2
	}
}


func insert(heap []int, num int) []int {
	if nil == heap || 1 >= len(heap) {
		heap = make([]int, 2) // heap[0] is skipped
		heap[1] = num
		return heap
	}
	
	heap = append(heap, num)
	bubble_up(heap, len(heap)-1)
	return heap
}


func bubble_down(heap []int, index int) {
	target := index
	for {
		left  := 2 * index
		right := left + 1
		if left < len(heap) && heap[left] > heap[target] {
			target = left
		}
		if right < len(heap) && heap[right] > heap[target] {
			target = right
		}
		if target == index {
			return
		}
		
		heap[index], heap[target] = heap[target], heap[index]
		
		index = target
	}
}

// the value is returned as heap[0] unless the function returns nil in
// which case the heap was empty to begin with
func extract(heap []int) []int {
	if nil == heap || 1 >= len(heap) {
		return nil
	}
	
	if 2 == len(heap) {
		heap := []int{ heap[1] }
		return heap
	}
	
	heap[0] = heap[1]		// remember that heap[0] is skipped
	heap[1] = heap[len(heap)-1]
	heap = heap[:len(heap)-1]
	bubble_down(heap, 1)
	return heap
}


func dump(heap []int) {
	for ii, vv := range (heap) {
		if 0 < ii {
			fmt.Print("  ", vv)
		}
	}
	fmt.Println()
}


func main() {
	heap := make([]int, 0)
	
	for _, arg := range(os.Args[1:]) {
		data, error := strconv.Atoi(arg)
		if nil != error {
			fmt.Println("ignoring", arg)
		} else {
			heap = insert(heap, data)
			fmt.Println("inserted ", data)
			dump(heap)
		}
	}
	
	for nil != heap {
		heap = extract(heap)
		if nil != heap {
			fmt.Println("extracted ", heap[0])
			dump(heap)
		}
	}
}
