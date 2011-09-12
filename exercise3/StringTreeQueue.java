public class StringTreeQueue
{
    static class Node {
	StringTree tree;
	Node next;
	
	Node(StringTree _tree, Node _next)
	{
	    tree = _tree;
	    next = _next;
	}
    }
    
    private Node head, tail;
    
    public void enqueue(StringTree tree)
    {
	if (null == head) {
	    head = new Node(tree, null);
	    tail = head;
	}
	else {
	    tail.next = new Node(tree, null);
	    tail = tail.next;
	}
    }
    
    public StringTree dequeue()
    {
	if (null == head) {
	    return null;
	}
	StringTree tree = head.tree;
	head = head.next;
	return tree;
    }
    
    public boolean empty()
    {
	return null == head;
    }
}
