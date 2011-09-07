package exercise2;

public class ListIterator<AnyType>
{
    /**
       The node which the iterator is currently pointing at.
    */
    public ListNode<AnyType> node;
    
    
    public ListIterator(ListNode<AnyType> _node)
    {
	node = _node;
    }
    
    
    public boolean valid()
    {
	return null != node;
    }
    
    
    public AnyType get()
    {
	return node.value;
    }
    
    
    public void next()
    {
	node = node.next;
    }
}
