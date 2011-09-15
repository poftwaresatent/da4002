/**
   A doubly-linked list of strings. It uses raw head and tail
   references, instead of the example in the course book which uses
   "dummy" head and tail nodes to reduce some of the special case
   handling required here.
*/
public class StringList
{
    /**
       The head is the first node of the list. In case of an empty
       list, the head is null.
    */
    private StringListNode head;
    
    /**
       The tail is the last node. Like the head, it is null when the list is empty.
    */
    private StringListNode tail;
    
    
    public StringList()
    {
	// Java initializes head and tail to null anyway, but we have
	// to have the default constructor because we also define
	// non-default ones.
    }
    
    
    public StringList(String[] original, int effectiveLength)
    {
	for (int ii = 0; ii < effectiveLength; ++ii) {
	    pushBack(original[ii]);
	}
    }
    
    
    public StringList(String[] original)
    {
	this(original, original.length);
    }
    
    
    public StringList(StringVector original)
    {
	this(original.raw(), original.size());
    }
    
    
    /**
       Prepend a value to the list.
    */
    public void pushFront(String value)
    {
	StringListNode node = new StringListNode(value);
	node.next = head;
	if (null == head) {	// the list was empty
	    tail = node;
	}
	else {
	    head.prev = node;
	}
	head = node;
    }
    
    
    /**
       Delete the first list item. <b>No error checking</b> is
       performed: calling popFront on an empty list is an error. Use
       the empty() method to check for emptyness.
    */
    public void popFront()
    {
	head = head.next;
	if (null == head) {	// the list is now empty
	    tail = null;
	}
	else {
	    head.prev = null;
	}
    }
    
    
    /**
       Retrieve the value which is stored in the first element of the
       list. <b>No error checking</b> is performed: it is an error to
       call this method on an empty list. Use the empty() method to
       check for emptyness.
    */
    public String front()
    {
	return head.value;
    }
    
    
    /**
       Append a value to the list.
    */
    public void pushBack(String value)
    {
	StringListNode node = new StringListNode(value);
	if (null == tail) {	// the list was empty
	    head = node;
	    tail = node;
	    return;
	}
	tail.next = node;
	node.prev = tail;
	tail = node;
    }
    
    
    /**
       Delete the last item from the list. <b>No error checking</b> is
       performed: calling popBack on an empty list is an error. Use
       the empty() method to check for emptyness.
    */
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
    
    
    /**
       Retrieve the value which is stored in the last element of the
       list. <b>No error checking</b> is performed: it is an error to
       call this method on an empty list. Use the empty() method to
       check for emptyness.
    */
    public String back()
    {
	return tail.value;
    }
    
    
    /**
       Insert a value into the list such that it comes after the
       specified position.
    */
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
    
    
    /**
       Insert a value into the list such that it comes before the
       specified position.
    */
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
    
    
    /**
       Remove an item (specified by its position) from the list.
    */
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
    
    
    /**
       Helper method which prints a string and then some empty space
       until the given width is reached.
    */
    public static void pstring(String val, int width)
    {
	System.out.print(val);
	for (int rem = width - val.length(); rem > 0; --rem) {
	    System.out.print(" ");
	}
    }
    
    
    /**
       Prints all elements of the list on a separate line of
       System.out. If a title is given, that is printed first. Then
       each list item, along with its prev and next items (for
       debugging). The colwidth is used to pad entries with spaces
       until they are at least that wide.
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
	    System.out.print(prefix + "  ");
	    pstring(current.value, colwidth);
	    System.out.print("  p: ");
	    if (null == current.prev) {
		pstring("(null)", colwidth);
	    }
	    else {
		pstring(current.prev.value, colwidth);
	    }
	    System.out.print("  n: ");
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
    
    
    /***
	The main method tries out the effects of the various
	StringList methods.
    */
    public static void main(String [] args)
    {
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
	    sl.print("  result", "    - ", 10);
	}
	
	sl.pushBack("a1");
	sl.pushBack("a2");
	sl.print("after 2 pushBack", "  * ", 10);

	sl.insertAfter("B1", sl.first());
	sl.print("inserted B1 after the head", "  * ", 10);
	
	sl.insertAfter("B2", sl.last());
	sl.print("inserted B2 after the tail", "  * ", 10);

	sl.insertBefore("C1", sl.first());
	sl.print("inserted C1 before the head", "  * ", 10);
	
	sl.insertBefore("C2", sl.last());
	sl.print("inserted C2 before the tail", "  * ", 10);
	
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
