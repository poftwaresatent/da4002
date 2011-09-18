public class StringBSTree
{
    public StringBSTreeNode root;
    
    
    public StringBSTree()
    {
	root = null;
    }
    
    
    static private StringBSTreeNode insert(String value, StringBSTreeNode node)
    {
	if (null == node) {
	    return new StringBSTreeNode(value);
	}
	int comparison = value.compareTo(node.value);
	if (0 > comparison) {
	    // insert it into the smaller subtree
	    node.smaller = insert(value, node.smaller);
	}
	else if (0 < comparison) {
	    // insert it into the bigger subtree
	    node.bigger = insert(value, node.bigger);
	}
	else {
	    // value already in tree, nothing to do
	}
	return node;
    }
    
    
    public void insert(String value)
    {
	root = insert(value, root);
    }
    
    
    static public StringBSTreeNode findMinNode(StringBSTreeNode node)
    {
	while (null != node.smaller) {
	    node = node.smaller;
	}
	return node;
    }
    
    
    public StringBSTreeNode findMinNode()
    {
	return findMinNode(root);
    }
    
    
    public String findMin()
    {
	if (null == root) {
	    return null;
	}
	StringBSTreeNode node = findMinNode(root);
	return node.value;
    }
    
    
    static public StringBSTreeNode findMaxNode(StringBSTreeNode node)
    {
	while (null != node.bigger) {
	    node = node.bigger;
	}
	return node;
    }
    
    
    public String findMax()
    {
	if (null == root) {
	    return null;
	}
	StringBSTreeNode node = findMaxNode(root);
	return node.value;
    }
    
    
    // This works becaue the caller will say something like
    // "node.bigger=removeMin(node.bigger)" which recurses down the
    // smaller subtrees until it ends up as
    // "someDescendent.bigger=someDescendent.bigger.bigger" which cuts
    // the original bigger child of the node out of the tree.
    //
    static private StringBSTreeNode removeMin(StringBSTreeNode node)
    {
	if (null != node.smaller) {
	    node.smaller = removeMin(node.smaller);
	    return node;
	}
	return node.bigger;
    }
    
    
    public void removeMin()
    {
	if (null != root) {
	    root = removeMin(root);
	}
    }
    
    
    // Note: silently ignore non-existing entries.
    //
    static private StringBSTreeNode remove(String value, StringBSTreeNode node)
    {
	int comparison = value.compareTo(node.value);
	
	if (0 > comparison) {
	    // remove it from the smaller subtree, if it exists
	    if (null != node.smaller) {
		node.smaller = remove(value, node.smaller);
	    }
	    return node;
	}
	
	if (0 < comparison) {
	    // remove it from the bigger subtree, it it exists
	    if (null != node.bigger) {
		node.bigger = remove(value, node.bigger);
	    }
	    return node;
	}
	
	// The value is the same as node.value, so we have to remove
	// "this" node, which is easy UNLESS it has two
	// subtrees... (see below)
	
	if (null == node.smaller) {
	    if (null == node.bigger) {
		// easy: this node is a leaf, just remove it
		return null;
	    }
	    // easy: replace the node by its only child
	    return node.bigger;
	}
	else if (null == node.bigger) {
	    // easy: replace the node by its only child
	    return node.smaller;
	}
	
	// ...now for the tricky part: find the smallest node in the
	// bigger subtree as a replacement. Use the replacement's
	// value to overwrite this node, then remove the REPLACEMENT
	// instead of this node. Because the replacement is the
	// smallest of a (sub)tree, it has at most one child, so
	// removing it is trivial (and implemented in a recursive
	// helper function called removeMin).
	
	StringBSTreeNode replacement = findMinNode(node.bigger);
	node.value = replacement.value;
	node.bigger = removeMin(node.bigger);
	
	return node;
    }
    
    
    public void remove(String value)
    {
	root = remove(value, root);
    }
    
    
    public boolean contains(String value)
    {
	StringBSTreeNode node = root;
	while (null != node) {
	    int comparison = value.compareTo(node.value);
	    if (0 > comparison) {
		node = node.smaller;
	    }
	    else if (0 < comparison) {
		node = node.bigger;
	    }
	    else {
		return true;
	    }
	}
	return false;
    }
    
    
    public void printPreOrder(String title, String prefix)
    {
	if (0 != title.length()) {
	    System.out.println(title);
	}
        if (null == root) {
	    System.out.println(prefix + "(empty tree)");
	}
	else {
            root.printPreOrder(prefix, "  ");
	}
    }
    
    
    public void printInOrder(String title, String prefix)
    {
	if (0 != title.length()) {
	    System.out.println(title);
	}
        if (null == root) {
	    System.out.println(prefix + "(empty tree)");
	}
	else {
           root.printInOrder(prefix, "  ");
	}
    }
    
    
    public void printPostOrder(String title, String prefix)
    {
	if (0 != title.length()) {
	    System.out.println(title);
	}
        if (null == root) {
	    System.out.println(prefix + "(empty tree)");
	}
	else {
           root.printPostOrder(prefix, "  ");
	}
    }
    
    
    public void clear()
    {
        root = null;
    }
    
    
    public boolean empty()
    {
        return null == root;
    }
    
    
    public boolean check()
    {
	if (null != root) {
	    return root.check(null, null);
	}
	return true;
    }
    
    
    public static void main(String[] args)
    {
	StringBSTree dict = new StringBSTree();
	String[] data = Factory.createRandomStrings(15);
	for (int ii = 0; ii < data.length; ++ii) {
	    dict.insert(data[ii]);
	}
	dict.printInOrder("before repeated removing of min", "  ");
	while ( ! dict.empty()) {
	    String minValue = dict.findMin();
	    dict.removeMin();
	    dict.printInOrder("after removing min `" + minValue + "'", "  ");
	}
    }
}
