public class StringBinaryTreeNode
{
    public String value;
    public StringBinaryTreeNode left;
    public StringBinaryTreeNode right;
    
    public StringBinaryTreeNode(String _value,
				StringBinaryTreeNode _left,
				StringBinaryTreeNode _right)
    {
	value = _value;
        left    = _left;
        right   = _right;
    }
    
    public StringBinaryTreeNode()
    {
        this(null, null, null);
    }
    
    public int computeSize()
    {
	int size = 1;
	if (null != left) {
	    size += left.computeSize();
	}
	if (null != right) {
	    size += right.computeSize();
	}
	return size;
    }
    
    public int computeHeight()
    {
	if (null == left && null == right) {
	    return 0;
	}
	int lh = 0, rh = 0;
	if (null != left) {
	    lh = left.computeHeight();
	}
	if (null != right) {
	    rh = right.computeHeight();
	}
	return 1 + Math.max(lh, rh);
    }
    
    public void printPreOrder(String prefix)
    {
        System.out.println(prefix + value);
	if (null != left) {
            left.printPreOrder(prefix + "  ");
	}
	if (null != right) {
            right.printPreOrder(prefix + "  ");
	}
    }
    
    
    public void printPostOrder(String prefix)
    {
	if (null != left) {
            left.printPostOrder(prefix + "  ");
	}
	if (null != right) {
            right.printPostOrder(prefix + "  ");
	}
        System.out.println(prefix + value);
    }
    
    
    public void printInOrder(String prefix)
    {
	if (null != left) {
            left.printInOrder(prefix + "  ");
	}
        System.out.println(prefix + value);
	if (null != right) {
            right.printInOrder(prefix + "  ");
	}
    }
}
