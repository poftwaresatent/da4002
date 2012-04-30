public class List<AnyType>
{
    /**
       The head is the first node of the list. In case of an empty
       list, the head is null.
    */
    private ListNode<AnyType> head;
    
    // Add this field when changing List into a doubly-linked list
    //
    // private ListNode<AnyType> tail;
    
    
    /**
       Insert a given value at the front of the list.
    */
    public void pushFront(AnyType value)
    {
	ListNode<AnyType> node = new ListNode<AnyType>(value);
	node.next = head;
	head = node;
    }
    
    
    /**
       Delete the first list item. This will result in the second item
       becoming the new head, unless of course there are no more
       elements. <b>No error checking</b> is performed, calling
       popFront on an empty list will result in a null pointer
       exception. Use the empty() to check for emptyness.
    */
    public void popFront()
    {
	head = head.next;
    }
    
    
    /**
       Retrieve the value which is stored in the first element of the
       list. <b>No error checking</b> is performed: use the empty()
       method to find out whether there is anything to retrieve.
    */
    public AnyType front()
    {
	return head.value;
    }

    
    // Add this method when changing List into a doubly-linked list
    //
    // public void pushBack(AnyType value)
    // {
    // }
    
    
    // Add this method when changing List into a doubly-linked list
    //
    // public void popBack()
    // {
    // }
    
    
    // Add this method when changing List into a doubly-linked list
    //
    // public AnyType back()
    // {
    // }
    
    
    public void insert(AnyType value, ListIterator position)
    {
	ListNode<AnyType> node = new ListNode<AnyType>(value);
	node.next = position.node.next;
	position.node.next = node;
    }
    
    
    public void remove(ListIterator position)
    {
	position.node.next = position.node.next.next;
    }
    
    
    /**
       Determines whether the list is empty.
    */
    public boolean empty()
    {
	return null == head;
    }
    
    
    /**
       Removes all elements from the list.
    */
    public void clear()
    {
	head = null;
    }
    
    
    /**
       Creates an iterator that starts at the beginning of the list.
    */
    public ListIterator begin()
    {
	return new ListIterator(head);
    }
    
    
    /**
       Prints all elements of the list on a separate line of
       System.out. Each line is prefixed with the given string to
       allow a basic form of custom formatting.
    */
    public void print(String prefix)
    {
	for (ListNode<AnyType> current = head; null != current; current = current.next) {
	    System.out.println(prefix + current.value);
	}
    }
    
    
    public static void main(String [] args)
    {
	// The main method tries out the effects of the various
	// List methods. Run it to make sure your
	// implementations are correct.
	
	List<String> sl = new List<String>();
	
	System.out.println("pushing some things onto the list...");
	
	sl.pushFront("hello");
	for (int ii = 0; ii < 3; ++ii) {
	    sl.pushFront(" " + ii);
	}
	sl.pushFront("byebye!");
	
	System.out.println("result:");
	sl.print("  * ");
	
	if (sl.empty()) {
	    System.out.println("the List is empty");
	}
	else {
	    System.out.println("the List is not empty");
	}
	
	System.out.println("clearing the list...");

	sl.clear();

	System.out.println("result:");
	sl.print("  * ");
	
	if (sl.empty()) {
	    System.out.println("the List is empty");
	}
	else {
	    System.out.println("the List is not empty");
	}
	
	System.out.println("pushing some things onto the list...");
	
	sl.pushFront("one");
	sl.pushFront("two");
	sl.pushFront("three");

	System.out.print("using the iterator:");
	for (ListIterator ii = sl.begin(); ii.valid(); ii.next()) {
	    System.out.print(" " + ii.get());
	}
	System.out.println();
	
	while ( ! sl.empty()) {
	    System.out.println("popping " + sl.front());
	    sl.popFront();
	    System.out.println("result:");
	    sl.print("  * ");
	}
    }
}
