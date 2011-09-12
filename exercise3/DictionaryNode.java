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
}
