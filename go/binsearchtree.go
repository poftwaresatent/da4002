package main

import "fmt"
import "os"
import "strconv"

type item struct {
	data int
	left, right *item
}

func ins_r(root *item, data int) *item {
	if nil == root {
		return &item{data, nil, nil}
	}
	if data < root.data {
		root.left = ins_r(root.left, data)
	} else if data > root.data {
		root.right = ins_r(root.right, data)
	} // else ignore, no duplicates allowed
	return root
}

func rem_r(root *item, data int) *item {
	if nil == root {
		return nil
	}
	if data < root.data {
		root.left = rem_r(root.left, data)
		return root
	}
	if data > root.data {
		root.right = rem_r(root.right, data)
		return root
	}
	if nil == root.left {
		return root.right
	}
	if nil == root.right {
		return root.left
	}
	parent := root
	child := root.right
	for nil != child.left {
		parent = child
		child = child.left
	}
	root.data = child.data
	if parent == root {
		parent.right = child.right
	} else {
		parent.left = child.right
	}
	return root
}

func find_r(root *item, data int) *item {
	if nil == root {
		return nil
	}
	if data < root.data {
		return find_r(root.left, data)
	} else if data > root.data {
		return find_r(root.right, data)
	}
	return root
}

func find_i(root *item, data int) *item {
	for nil != root {
		if data < root.data {
			root = root.left
		} else if data > root.data {
			root = root.right
		} else {
			return root
		}
	}
	return nil
}
			
func pdot_r(root *item) {
	if nil != root.left {
		pdot_r(root.left)
		fmt.Printf("  \"%d\" -> \"%d\" [label=\"l\"];\n", root.data, root.left.data)
	}
	if nil != root.right {
		fmt.Printf("  \"%d\" -> \"%d\" [label=\"r\"];\n", root.data, root.right.data)
		pdot_r(root.right)
	}
}

func pdot(root *item) {
	fmt.Print("digraph \"bstree\" {\n  graph [label=\"")
	for _, arg := range(os.Args[1:]) {
		fmt.Print("  ", arg)
	}
	fmt.Println("\",overlap=scale];")
	pdot_r(root)
	fmt.Println("}");
}

func main() {
	var root *item
	
	op := ins_r
	for _, arg := range(os.Args[1:]) {
		if "i" == arg {
			op = ins_r
		} else if "r" == arg {
			op = rem_r
		} else {
			data, error := strconv.Atoi(arg)
			if nil != error {
				fmt.Println("ignoring", arg)
			} else {
				root = op(root, data)
			}
		}
	}
	
	pdot(root)

/*	
	find := []func(*item, int) *item { find_r, find_i }
	for ii := len(data)/4; ii < 3*len(data)/4; ii += 1 {
		fmt.Printf("%5d", data[ii])
		for _, ff := range(find) {
			if nil != ff(root, data[ii]) {
				fmt.Print("  yes")
			} else {
				fmt.Print("   no")
			}
		}
		fmt.Println()
	}
*/	
}
