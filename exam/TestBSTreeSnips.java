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
    
    public static void main(String[] args) {
	long[] values = { 5, 3, 13, -7, 3, 7, 42, 3, 5 };
	
	ContainerOne bstree = new ContainerOne();
	ContainerTwo dblist = new ContainerTwo();
	for (int ii = 0; ii < values.length; ++ii) {
	    bstree.insert(values[ii]);
	    dblist.insert(values[ii]);
	}
	
	System.out.println("binary search tree (in order):");
	printInOrder(bstree.handle);
	
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
