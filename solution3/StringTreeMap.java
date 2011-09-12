public class StringTreeMap
{
    public StringTreeMapNode root;
    
    public StringTreeMap()
    {
	root = null;
    }
    
    static private StringTreeMapNode insert(String key, String value, StringTreeMapNode node)
    {
	if (null == node) {
	    return new StringTreeMapNode(key, value);
	}
	int comparison = key.compareTo(node.key);
	if (0 > comparison) {
	    // insert it into the smaller subtree
	    node.smaller = insert(key, value, node.smaller);
	}
	else if (0 < comparison) {
	    // insert it into the bigger subtree
	    node.bigger = insert(key, value, node.bigger);
	}
	else {
	    // same key, overwrite the value
	    node.value = value;
	}
	return node;
    }
    
    public void set(String key, String value)
    {
	root = insert(key, value, root);
    }
    
    static public StringTreeMapNode findMinNode(StringTreeMapNode node)
    {
	while (null != node.smaller) {
	    node = node.smaller;
	}
	return node;
    }
    
    public String findMinValue()
    {
	if (null == root) {
	    return null;
	}
	StringTreeMapNode node = findMinNode(root);
	return node.value;
    }
    
    static public StringTreeMapNode findMaxNode(StringTreeMapNode node)
    {
	while (null != node.bigger) {
	    node = node.bigger;
	}
	return node;
    }
    
    public String findMaxValue()
    {
	if (null == root) {
	    return null;
	}
	StringTreeMapNode node = findMaxNode(root);
	return node.value;
    }
    
    // This works becaue the caller will say something like
    // "node.bigger=removeMin(node.bigger)" which recurses down the
    // smaller subtrees until it ends up as
    // "someDescendent.bigger=someDescendent.bigger.bigger" which cuts
    // the original bigger child of the node out of the tree.
    //
    static private StringTreeMapNode removeMin(StringTreeMapNode node)
    {
	if (null != node.smaller) {
	    node.smaller = removeMin(node.smaller);
	    return node;
	}
	return node.bigger;
    }
    
    // Note: silently ignore non-existing entries.
    //
    static private StringTreeMapNode remove(String key, StringTreeMapNode node)
    {
	int comparison = key.compareTo(node.key);
	
	if (0 > comparison) {
	    // remove it from the smaller subtree, if it exists
	    if (null != node.smaller) {
		node.smaller = remove(key, node.smaller);
	    }
	    return node;
	}
	
	if (0 < comparison) {
	    // remove it from the bigger subtree, it it exists
	    if (null != node.bigger) {
		node.bigger = remove(key, node.bigger);
	    }
	    return node;
	}
	
	// The key is the same as node.key, so we have to remove
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
	// bigger subtree as a replacement. Use the replacement's key
	// and value to overwrite this node, then remove the
	// REPLACEMENT instead of this node. Because the replacement
	// is the smallest of a (sub)tree, it has at most one child,
	// so removing it is trivial (and implemented in a recursive
	// helper function called removeMin).
	
	StringTreeMapNode replacement = findMinNode(node.bigger);
	node.key = replacement.key;
	node.value = replacement.value;
	node.bigger = removeMin(node.bigger);
	
	return node;
    }
    
    public void unset(String key)
    {
	root = remove(key, root);
    }
    
    public String find(String key)
    {
	StringTreeMapNode node = root;
	while (null != node) {
	    int comparison = key.compareTo(node.key);
	    if (0 > comparison) {
		node = node.smaller;
	    }
	    else if (0 < comparison) {
		node = node.bigger;
	    }
	    else {
		return node.value;
	    }
	}
	return null;
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
            root.printPreOrder(prefix);
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
           root.printInOrder(prefix);
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
           root.printPostOrder(prefix);
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
    
    static private String paddedNumber(int number, int width)
    {
	String ns = "" + number;
	StringBuilder sb = new StringBuilder(width);
	width -= ns.length();
	for (int ii = 0; ii < width; ++ii) {
	    sb.append('0');
	}
	return sb.toString() + ns;
    }
    
    public static void main(String[] args)
    {
	StringTreeMap sm = new StringTreeMap();
	int nEntries = 100;
	int gap = 37;
	
        for (int ii = gap; 0 != ii; ii = (ii + gap) % nEntries) {
            sm.set("key_" + paddedNumber(ii, 3), "value_" + paddedNumber(ii, 3));
	}
	
        for (int ii = 1; ii < nEntries; ii += 2) {
            sm.unset("key_" + paddedNumber(ii, 3));
	}
	
	sm.printInOrder("after adding lots and removing half of it again", "  ");
	
	String mv = sm.findMinValue();
	String mvCheck = "value_" + paddedNumber(2, 3);
        if ( ! mvCheck.equals(mv)) {
	    System.out.println("FindMinValue returned " + mv + " instead of " + mvCheck);
	}
	
	mv = sm.findMaxValue();
	mvCheck = "value_" + paddedNumber(nEntries-2, 3);
        if ( ! mvCheck.equals(mv)) {
	    System.out.println("FindMaxValue returned " + mv + " instead of " + mvCheck);
	}
	
        for (int ii = 2; ii < nEntries; ii += 2) {
	    String pn = paddedNumber(ii, 3);
	    if ( ! ("value_" + pn).equals(sm.find("key_" + pn))) {
		System.out.println("Failed to find value " + pn);
	    }
	}
	
        for (int ii = 1; ii < nEntries; ii += 2) {
	    String pn = paddedNumber(ii, 3);
	    if (null != sm.find("key_" + pn)) {
		System.out.println("Found bogus entry for key " + pn);
	    }
	}
    }
}
