public class StringList
{
    /**
       The head is the first node of the list. In case of an empty
       list, the head is null.
    */
    private StringListNode head;
    
    
    public void pushFront(String value)
    {
	// Write a method which adds the given value to the front of
	// the list.
    }
    
    
    public void popFront()
    {
	// Write a method which removes the first element from the
	// list.
    }
    
    
    public String front()
    {
	// Write a method which returns the string stored at the
	// beginning of the list.
	return "IMPLEMENT ME!";
    }
    
    
    public void insertAfter(String value, StringListIterator position)
    {
	// Write a method which inserts the given value such that it
	// ends up as the next element after the given position.
    }
    
    
    public boolean empty()
    {
	// Write a method which determines whether the StringList is
	// currently empty.
	return true;	      // this is just a placeholder for now...
    }
    
    
    public void clear()
    {
	// Write a method which removes all elements from the list.
    }
    
    
    public StringListIterator begin()
    {
	return new StringListIterator(head);
    }
    
    
    public void print(String prefix)
    {
       // Write a method which prints all elements of the list, each
       // on a separate line. Each line should begin with the prefix
       // given as argument.
    }
    
    
    public static void main(String [] args)
    {
	// The main method tries out the effects of the various
	// StringList methods. Run it to make sure your
	// implementations are correct.
	
	StringList sl = new StringList();
	
	sl.pushFront("hello");
	for (int ii = 0; ii < 3; ++ii) {
	    sl.pushFront(" " + ii);
	}
	sl.pushFront("byebye!");
	sl.print("* ");
	
	if (sl.empty()) {
	    System.out.println("the StringList is empty");
	}
	else {
	    System.out.println("the StringList is not empty");
	}
	
	sl.clear();
	sl.print("* ");
	
	if (sl.empty()) {
	    System.out.println("the StringList is empty");
	}
	else {
	    System.out.println("the StringList is not empty");
	}
	
	sl.pushFront("one");
	sl.pushFront("two");
	sl.pushFront("three");
	for (StringListIterator ii = sl.begin(); ii.valid(); ii.next()) {
	    System.out.print(" " + ii.get());
	}
	System.out.println();
	
	sl.print("* ");
	while ( ! sl.empty()) {
	    System.out.println("  pop " + sl.front());
	    sl.popFront();
	    sl.print("  - ");
	}
    }
}
