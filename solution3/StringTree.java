public class StringTree
{
    public String value;
    public StringTree sibling;
    public StringTree child;
    
    public int size;
    public int height;
    public int depth;
    
    
    public StringTree(String _value)
    {
	value = _value;
    }
    
    
    public StringTree addChild(StringTree node)
    {
	node.sibling = child;
	child = node;
	return node;
    }
    
    
    public StringTree addChild(String value)
    {
	return addChild(new StringTree(value));
    }
    
    
    public int computeSize()
    {
	size = 1;
	for (StringTree nn = child; null != nn; nn = nn.sibling) {
	    size += nn.computeSize();
	}
	return size;
    }
    
    public int computeHeight()
    {
	height = 0;
	if (null != child) {
	    for (StringTree nn = child; null != nn; nn = nn.sibling) {
		int hh = nn.computeHeight();
		if (hh > height) {
		    height = hh;
		}
	    }
	    height += 1;
	}
	return height;
    }
    
    public int computeDepth(int parentDepth)
    {
	depth = parentDepth + 1;
	for (StringTree nn = child; null != nn; nn = nn.sibling) {
	    nn.computeDepth(depth);
	}
	return depth;
    }
    
    
    public String info()
    {
	return value + "  (s: " + size + "  h: " + height + "  d: " + depth + ")";
    }
    
    
    public void printPreOrder(String prefix, String indent)
    {
        System.out.println(prefix + info());
	prefix += indent;
	for (StringTree nn = child; null != nn; nn = nn.sibling) {
	    nn.printPreOrder(prefix, indent);
	}
    }
    
    
    public void printPostOrder(String prefix, String indent)
    {
	String childPrefix = prefix + indent;
	for (StringTree nn = child; null != nn; nn = nn.sibling) {
	    nn.printPostOrder(childPrefix, indent);
	}
        System.out.println(prefix + info());
    }
    
    
    public void printLevelOrder(String prefix)
    {
	StringTreeQueue qq = new StringTreeQueue();
	qq.enqueue(this);
	while ( ! qq.empty()) {
	    StringTree node = qq.dequeue();
	    System.out.println(prefix + node.info());
	    for (StringTree nn = node.child; null != nn; nn = nn.sibling) {
		qq.enqueue(nn);
	    }
	}
    }
    
    
    static public void main(String[] args)
    {
	StringTree nA = new StringTree("A");
	StringTree nE = nA.addChild("E");
	StringTree nJ = nE.addChild("J");
	nJ.addChild("K");
	nE.addChild("I");
	StringTree nD = nA.addChild("D");
	nD.addChild("H");
	nA.addChild("C");
	StringTree nB = nA.addChild("B");
	nB.addChild("G");
	nB.addChild("F");
	
	nA.computeSize();
	nA.computeHeight();
	nA.computeDepth(-1);
	
	System.out.println("pre-order");
	nA.printPreOrder("  ", "");
	
	System.out.println("post-order");
	nA.printPostOrder("  ", "");
	
	System.out.println("level-order");
	nA.printLevelOrder("  ");
    }
}
