public class StringBSTreeNode
{
    public String value;
    public StringBSTreeNode smaller;
    public StringBSTreeNode bigger;
    
    
    public StringBSTreeNode(String _value,
			    StringBSTreeNode _smaller,
			    StringBSTreeNode _bigger)
    {
	value = _value;
        smaller = _smaller;
        bigger = _bigger;
    }
    
    
    public StringBSTreeNode(String value)
    {
        this(value, null, null);
    }
    
    
    public int computeSize()
    {
	int size = 1;
	if (null != smaller) {
	    size += smaller.computeSize();
	}
	if (null != bigger) {
	    size += bigger.computeSize();
	}
	return size;
    }
    
    public int computeHeight()
    {
	if (null == smaller && null == bigger) {
	    return 0;
	}
	int lh = 0, rh = 0;
	if (null != smaller) {
	    lh = smaller.computeHeight();
	}
	if (null != bigger) {
	    rh = bigger.computeHeight();
	}
	return 1 + Math.max(lh, rh);
    }
    
    
    public void printPreOrder(String prefix, String indent)
    {
        System.out.println(prefix + value);
	if (null != smaller) {
            smaller.printPreOrder(prefix + indent, indent);
	}
	if (null != bigger) {
            bigger.printPreOrder(prefix + indent, indent);
	}
    }
    
    
    public void printPostOrder(String prefix, String indent)
    {
	if (null != smaller) {
            smaller.printPostOrder(prefix + indent, indent);
	}
	if (null != bigger) {
            bigger.printPostOrder(prefix + indent, indent);
	}
        System.out.println(prefix + value);
    }
    
    
    public void printInOrder(String prefix, String indent)
    {
	if (null != smaller) {
            smaller.printInOrder(prefix + indent, indent);
	}
        System.out.println(prefix + value);
	if (null != bigger) {
            bigger.printInOrder(prefix + indent, indent);
	}
    }
    
    
    public boolean check(String lowerBound, String upperBound)
    {
	if (null != lowerBound && value.compareTo(lowerBound) <= 0) {
	    return false;
	}
	if (null != upperBound && value.compareTo(upperBound) >= 0) {
	    return false;
	}
	if (null != smaller && ! smaller.check(lowerBound, value)) {
	    return false;
	}
	if (null != bigger && ! bigger.check(value, upperBound)) {
	    return false;
	}
	return true;
    }

}
