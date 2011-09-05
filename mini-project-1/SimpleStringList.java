/**
   Simple list of strings. Supports a limited number of operations,
   and performs no error checking. Useful as an example and to build
   more complete things from it.
*/
public class SimpleStringList
{
    /**
       Node for the simple string list. Just some public fields and a
       convenient constructor.
    */
    public class Node
    {
	public String data;
	public Node next;
	
	public Node(String _data)
	{
	    data = _data;
	}
    }
    
    
    /**
       The first node of the list. It is null when the list is empty.
    */
    private Node head;
    
    /**
       Insert a given value at the front of the list.
    */
    public void insertFront(String value)
    {
	Node node = new Node(value);
	node.next = head;
	head = node;
    }
    
    /**
       Insert a given value after the specified position.
    */
    public void insertAfter(Node position, String value)
    {
	Node node = new Node(value);
	node.next = position.next;
	position.next = node;
    }
    
    /**
       Retrieve the value which is stored in the first element of the
       list. <b>No error checking</b> is performed, the caller can
       call isEmpty in order to find out whether there is anything to
       retrieve.
    */
    public String getFront()
    {
	return head.data;
    }
    
    /**
       Delete the first list item. This will result in the second item
       becoming the new head, unless of course there are no more
       elements. <b>No error checking</b> is performed, calling
       removeFront on an empty list will result in a null pointer
       exception. Use isEmpty to check for emptyness.
    */
    public void removeFront()
    {
	head = head.next;
    }
    
    /**
       Delete the list node immediately following the given
       position. <b>No error checking</b> is performed, so make sure
       that removeAfter is not called on the last node by verifying
       that position.next is not null.
    */
    public void removeAfter(Node position)
    {
	position.next = position.next.next;
    }
    
    /**
       Determines whether the list is empty.
    */
    public boolean isEmpty()
    {
	return null == head;
    }
    
    /**
       Prints all elements of the list on a separate line of
       System.out. Each line is prefixed with the given string to
       allow a basic form of custom formatting.
    */
    public void print(String prefix)
    {
	for (Node current = head; null != current; current = current.next) {
	    System.out.println(prefix + current.data);
	}
    }
    
    /**
       A static function that demonstrates some of the list
       operations. When verbose is true it prints messages to
       System.out.
    */
    public static void demo(boolean verbose)
    {
	SimpleStringList list = new SimpleStringList();
	
	if (verbose) {
	    System.out.println("Inserting three items at the front.");
	}
	
	list.insertFront("blah one");
	list.insertFront("blah two");
	list.insertFront("blah three");
	
	if (verbose) {
	    System.out.println("  Result:");
	    list.print("  - ");
	    System.out.println();
	    System.out.println("Inserting three items after the head.");
	}
	
	list.insertAfter(list.head, "more blah one");
	list.insertAfter(list.head, "more blah two");
	list.insertAfter(list.head, "more blah three");

	if (verbose) {
	    System.out.println("  Result:");
	    list.print("  - ");
	    System.out.println();
	    System.out.println("Removing front '" + list.getFront() + "'");
	}
	
	list.removeFront();
	if (verbose) {
	    System.out.println("Removing front '" + list.getFront() + "'");
	}
	list.removeFront();
	if (verbose) {
	    System.out.println("Removing front '" + list.getFront() + "'");
	}
	list.removeFront();
	
	if (verbose) {
	    System.out.println("  Result:");
	    list.print("  - ");
	    System.out.println();
	    System.out.println("Removing twice after the head.");
	}
	
	list.removeAfter(list.head);
	list.removeAfter(list.head);
	if (verbose) {
	    System.out.println("  Result:");
	    list.print("  - ");
	}
    }
    
    /**
       The main function simply runs the demo in verbose mode.
    */
    public static void main(String [] args)
    {
	demo(true);
    }
}
