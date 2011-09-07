package exercise2;

public class StringListNode
{
    public String value;
    public StringListNode next;
    
    public StringListNode(String _value, StringListNode _next)
    {
	value = _value;
	next = _next;
    }
    
    public StringListNode(String value)
    {
	this(value, null);
    }
    
    public StringListNode()
    {
	this("", null);
    }
}
