public class StringListNode
{
    public String value;
    public StringListNode prev;
    public StringListNode next;
    
    public StringListNode(String _value, StringListNode _prev, StringListNode _next)
    {
	value = _value;
	prev = _prev;
	next = _next;
    }
    
    public StringListNode(String value)
    {
	this(value, null, null);
    }
    
    public StringListNode()
    {
	this("", null, null);
    }
}
