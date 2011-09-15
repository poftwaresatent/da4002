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
    
    
    public boolean isLast()
    {
	return null == node.next;
    }
    
    
    public boolean isFirst()
    {
	return null == node.prev;
    }
    
    
    public String get()
    {
	return node.value;
    }
    
    
    public void next()
    {
	node = node.next;
    }
    
    
    public void prev()
    {
	node = node.prev;
    }
    
}
