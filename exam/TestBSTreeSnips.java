public class TestBSTreeSnips {
    static void printInOrder(Node node) {
	if (null != node.foo) {
            printInOrder(node.foo);
	}
        System.out.println(node.value);
	if (null != node.bar) {
            printInOrder(node.bar);
	}
    }
    
    static void printDot(Node root) {
	System.out.println("digraph bstree {\n  graph [overlap=scale];");
	java.util.LinkedList<Node> queue = new java.util.LinkedList<Node>();
	queue.offer(root);
	while (0 < queue.size()) {
	    Node node = queue.pop();
	    if (null != node.foo) {
		System.out.println("  " + node.value + " -> " + node.foo.value + " [len=2];");
		queue.offer(node.foo);
	    }
	    if (null != node.bar) {
		System.out.println("  " + node.value + " -> " + node.bar.value + " [len=2];");
		queue.offer(node.bar);
	    }
	}
	System.out.println("}");
    }
    
    public static void main(String[] args) {
	long[] values = { 5, 3, 13, -7, 3, 7, 42, 4, 3 };
	boolean verbose = true;
	
	if (0 < args.length) {
	    verbose = false;
	    values = new long[args.length];
	    for (int ii = 0; ii < args.length; ++ii) {
		values[ii] = Integer.parseInt(args[ii]);
	    }
	}
	
	ContainerOne bstree = new ContainerOne();
	ContainerTwo dblist = new ContainerTwo();
	for (int ii = 0; ii < values.length; ++ii) {
	    bstree.insert(values[ii]);
	    dblist.insert(values[ii]);
	}
	
	if (verbose) {
	    System.out.println("binary search tree (in order):");
	    printInOrder(bstree.handle);
	}
	printDot(bstree.handle);
	
	if (verbose) {
	    System.out.println("\ndoubly linked list (forward):");
	    for (Node ii = dblist.alpha; ii != null; ii = ii.foo) {
		System.out.println(ii.value);
	    }
	    System.out.println("\ndoubly linked list (reverse):");
	    for (Node ii = dblist.beta; ii != null; ii = ii.bar) {
		System.out.println(ii.value);
	    }
	}
    }
}
