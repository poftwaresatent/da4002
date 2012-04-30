public class ListNode<AnyType>
{
    public AnyType value;
    public ListNode next;
    
    public ListNode(AnyType _value, ListNode _next)
    {
	value = _value;
	next = _next;
    }
    
    public ListNode(AnyType value)
    {
	this(value, null);
    }
    
    public ListNode()
    {
	this(null, null);
    }
}
