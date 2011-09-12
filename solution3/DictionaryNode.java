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
    
    public void printPreOrder(String prefix)
    {
        System.out.println(prefix + key + " -> " + value);
	if (null != smaller) {
            smaller.printPreOrder(prefix + "  ");
	}
	if (null != bigger) {
            bigger.printPreOrder(prefix + "  ");
	}
    }
    
    
    public void printPostOrder(String prefix)
    {
	if (null != smaller) {
            smaller.printPostOrder(prefix + "  ");
	}
	if (null != bigger) {
            bigger.printPostOrder(prefix + "  ");
	}
        System.out.println(prefix + key + " -> " + value);
    }
    
    
    public void printInOrder(String prefix)
    {
	if (null != smaller) {
            smaller.printInOrder(prefix + "  ");
	}
        System.out.println(prefix + key + " -> " + value);
	if (null != bigger) {
            bigger.printInOrder(prefix + "  ");
	}
    }
}
