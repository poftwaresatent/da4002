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
    
    private StringListNode tail;
    
    
    /**
       Insert a given value at the front of the list.
    */
    public void pushFront(String value)
    {
	StringListNode node = new StringListNode(value);
	node.next = head;
	if (null == head) {
	    // this is the first time we add something to the list
	    tail = node;
	}
	else {
	    head.prev = node;
	}
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
	if (null == head) {
	    // the list is now empty
	    tail = null;
	}
	else {
	    head.prev = null;
	}
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
    
    
    public void pushBack(String value)
    {
	StringListNode node = new StringListNode(value);
	if (null == tail) {
	    // this is the first time we add something to the list
	    head = node;
	    tail = node;
	    return;
	}
	tail.next = node;
	node.prev = tail;
	tail = node;
    }
    
    
    public void popBack()
    {
	tail = tail.prev;
	if (null == tail) {
	    // the list is now empty
	    head = null;
	    return;
	}
	tail.next = null;
    }
    
    
    public String back()
    {
	return tail.value;
    }
    
    
    public void insertAfter(String value, StringListIterator position)
    {
	StringListNode node = new StringListNode(value, position.node, position.node.next);
	position.node.next = node;
	if (tail == position.node) {
	    tail = node;
	}
	else {
	    node.next.prev = node;
	}
    }
    
    
    public void insertBefore(String value, StringListIterator position)
    {
	StringListNode node = new StringListNode(value, position.node.prev, position.node);
	position.node.prev = node;
	if (head == position.node) {
	    head = node;
	}
	else {
	    node.prev.next = node;
	}
    }
    
    
    public void remove(StringListIterator position)
    {
	if (head == position.node) {
	    popFront();
	    return;
	}
	if (tail == position.node) {
	    popBack();
	    return;
	}
	position.node.prev.next = position.node.next;
	position.node.next.prev = position.node.prev;
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
	tail = null;
    }
    
    
    /**
       Creates an iterator that starts at the beginning of the list.
    */
    public StringListIterator first()
    {
	return new StringListIterator(head);
    }
    
    
    /**
       Creates an iterator that starts at the end of the list.
    */
    public StringListIterator last()
    {
	return new StringListIterator(tail);
    }
    
    
    private static void pstring(String val, int width)
    {
	System.out.print(val);
	for (int rem = width - val.length(); rem > 0; --rem) {
	    System.out.print(" ");
	}
    }
    
    
    /**
       Prints all elements of the list on a separate line of
       System.out. Each line is prefixed with the given string to
       allow a basic form of custom formatting.
    */
    public void print(String title, String prefix, int colwidth)
    {
	if (0 < title.length()) {
	    System.out.println(title);
	}
	if (null == head) {
	    System.out.println(prefix + "(empty list)");
	    return;
	}
	System.out.println(prefix + "head: " + head.value);
	for (StringListNode current = head; null != current; current = current.next) {
	    System.out.print(prefix);
	    pstring(current.value, colwidth);
	    System.out.print("p: ");
	    if (null == current.prev) {
		pstring("(null)", colwidth);
	    }
	    else {
		pstring(current.prev.value, colwidth);
	    }
	    System.out.print("n: ");
	    if (null == current.next) {
		pstring("(null)", colwidth);
	    }
	    else {
		pstring(current.next.value, colwidth);
	    }
	    System.out.println();
	}
	System.out.println(prefix + "tail: " + tail.value);
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
	sl.print("after 5 pushFront", "  * ", 10);
	
	sl.clear();
	sl.print("after clear", "  * ", 10);
	
	sl.pushBack("one");
	sl.pushBack("two");
	sl.pushBack("three");
	sl.print("after 3 pushBack", "  * ", 10);

	System.out.print("using the iterator:");
	for (StringListIterator ii = sl.first(); ii.valid(); ii.next()) {
	    System.out.print(" " + ii.get());
	}
	System.out.println();
	
	while ( ! sl.empty()) {
	    System.out.println("pop front (" + sl.front() + ")");
	    sl.popFront();
	    System.out.println("result:");
	    sl.print("  result", "    - ", 10);
	}
	
	sl.pushBack("a1");
	sl.pushBack("a2");
	sl.print("after 3 pushBack", "  * ", 10);

	sl.insertAfter("b1", sl.first());
	sl.print("inserted after the head", "  * ", 10);
	
	sl.insertAfter("b2", sl.last());
	sl.print("inserted after the tail", "  * ", 10);

	sl.insertBefore("c1", sl.first());
	sl.print("inserted before the head", "  * ", 10);
	
	sl.insertBefore("c2", sl.last());
	sl.print("inserted before the tail", "  * ", 10);
	
	for (StringListIterator ii = sl.first(); ii.valid(); ii.next()) {
	    ii.next();
	    if (ii.valid()) {
		sl.remove(ii);
	    }
	}
	sl.print("after removing nodes number 2, 4, ...", "  * ", 10);
	
	sl.remove(sl.first());
	sl.print("after removing first node", "  * ", 10);
	
	sl.remove(sl.last());
	sl.print("after last node", "  * ", 10);
    }
    
}
