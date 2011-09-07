package exercise2.solution;

import exercise2.*;

/**
   A list of strings. At the beginning of exercise 2, StringList is
   singly linked and does no error checking.
   
   <b>Update this documentation</b> when you are done with the
   exercise.
*/
public class StringList
{
    /**
       The head is the first node of the list. In case of an empty
       list, the head is null.
    */
    private StringListNode head;
    
    // Add this field when changing StringList into a doubly-linked list
    //
    // private StringListNode tail;
    
    
    /**
       Insert a given value at the front of the list.
    */
    public void pushFront(String value)
    {
	StringListNode node = new StringListNode(value);
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
    public String front()
    {
	return head.value;
    }

    
    // Add this method when changing StringList into a doubly-linked list
    //
    // public void pushBack(String value)
    // {
    // }
    
    
    // Add this method when changing StringList into a doubly-linked list
    //
    // public void popBack()
    // {
    // }
    
    
    // Add this method when changing StringList into a doubly-linked list
    //
    // public String back()
    // {
    // }
    
    
    public void insert(String value, StringListIterator position)
    {
	StringListNode node = new StringListNode(value);
	node.next = position.node.next;
	position.node.next = node;
    }
    
    
    public void remove(StringListIterator position)
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
    public StringListIterator begin()
    {
	return new StringListIterator(head);
    }
    
    
    /**
       Prints all elements of the list on a separate line of
       System.out. Each line is prefixed with the given string to
       allow a basic form of custom formatting.
    */
    public void print(String prefix)
    {
	for (StringListNode current = head; null != current; current = current.next) {
	    System.out.println(prefix + current.value);
	}
    }
    
    
    public static void main(String [] args)
    {
	// The main method tries out the effects of the various
	// StringList methods. Run it to make sure your
	// implementations are correct.
	
	StringList sl = new StringList();
	
	System.out.println("pushing some things onto the list...");
	
	sl.pushFront("hello");
	for (int ii = 0; ii < 3; ++ii) {
	    sl.pushFront(" " + ii);
	}
	sl.pushFront("byebye!");
	
	System.out.println("result:");
	sl.print("  * ");
	
	if (sl.empty()) {
	    System.out.println("the StringList is empty");
	}
	else {
	    System.out.println("the StringList is not empty");
	}
	
	System.out.println("clearing the list...");

	sl.clear();

	System.out.println("result:");
	sl.print("  * ");
	
	if (sl.empty()) {
	    System.out.println("the StringList is empty");
	}
	else {
	    System.out.println("the StringList is not empty");
	}
	
	System.out.println("pushing some things onto the list...");
	
	sl.pushFront("one");
	sl.pushFront("two");
	sl.pushFront("three");

	System.out.print("using the iterator:");
	for (StringListIterator ii = sl.begin(); ii.valid(); ii.next()) {
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
