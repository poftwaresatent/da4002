public class StringListIterator
{
    /**
       The node which the iterator is currently pointing at.
    */
    public StringListNode current;
    
    
    public StringListIterator(StringListNode _current)
    {
	current = _current;
    }
    
    
    public boolean valid()
    {
	return null != current;
    }
    
    
    public String get()
    {
	return current.value;
    }
    
    
    public void next()
    {
	current = current.next;
    }
}
