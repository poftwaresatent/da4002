public class DictionaryNode
{
    public String key;
    public String value;
    public DictionaryNode smaller;
    public DictionaryNode bigger;
    
    
    public DictionaryNode(String _key,
			  String _value,
			  DictionaryNode _smaller,
			  DictionaryNode _bigger)
    {
	key = _key;
	value = _value;
        smaller = _smaller;
        bigger = _bigger;
    }
    
    
    public DictionaryNode(String key, String value)
    {
        this(key, value, null, null);
    }
    
    
    public String info()
    {
	return key + " -> " + value;
    }
    
    
    public void printPreOrder(String prefix, String indent)
    {
        System.out.println(prefix + info());
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
        System.out.println(prefix + info());
    }
    
    
    public void printInOrder(String prefix, String indent)
    {
	if (null != smaller) {
            smaller.printInOrder(prefix + indent, indent);
	}
        System.out.println(prefix + info());
	if (null != bigger) {
            bigger.printInOrder(prefix + indent, indent);
	}
    }
    
    
    public boolean check(String lowerBound, String upperBound)
    {
	if (null != lowerBound && key.compareTo(lowerBound) <= 0) {
	    return false;
	}
	if (null != upperBound && key.compareTo(upperBound) >= 0) {
	    return false;
	}
	if (null != smaller && ! smaller.check(lowerBound, key)) {
	    return false;
	}
	if (null != bigger && ! bigger.check(key, upperBound)) {
	    return false;
	}
	return true;
    }

}
