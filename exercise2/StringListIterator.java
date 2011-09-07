package exercise2;

public class StringListIterator
{
    /**
       The node which the iterator is currently pointing at.
    */
    public StringListNode node;
    
    
    public StringListIterator(StringListNode _node)
    {
	node = _node;
    }
    
    
    public boolean valid()
    {
	return null != node;
    }
    
    
    public String get()
    {
	return node.value;
    }
    
    
    public void next()
    {
	node = node.next;
    }
}
