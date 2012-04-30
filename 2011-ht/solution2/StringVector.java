public class StringVector
{
    /**
       The array field contains the underlying data storage.
    */
    private String[] array;
    
    /**
       The size field tracks the current size of the StringVector,
       independently from array.length (which is the current
       capacity).
    */
    private int size;
    
    
    public StringVector(int initialCapacity)
    {
	array = new String [initialCapacity];
	size = 0;
    }
    
    
    private void grow()
    {
	String [] bigger = new String [2 * array.length];
	for (int ii = 0; ii < size; ++ii) {
	    bigger[ii] = array[ii];
	}
	array = bigger;
    }
    
    
    public void pushBack(String value)
    {
	if (size >= array.length) {
	    grow();
	}
	array[size++] = value;
    }
    
    
    //// This was not part of the exercise, but illustrates what needs
    //// to be done in order to insert elements into the middle of the
    //// vector.
    public void insertAt(String value, int index)
    {
	if (size >= array.length) {
	    grow();
	}
	for (int ii = size; ii > index; --ii) {
	    array[ii] = array[ii-1];
	}
	array[index] = value;
	++size;
    }


    public void popBack()
    {
	--size;
    }
    
    
    public String at(int index)
    {
	return array[index];
    }
    
    
    public String back()
    {
	return array[size-1];
    }
    
    
    public int size()
    {
	return size;
    }
    
    
    public boolean empty()
    {
	return 0 == size;
    }
    
    
    public void clear()
    {
	size = 0;
    }
    
    
    public void print(String prefix)
    {
	for (int ii = 0; ii < size; ++ii) {
	    System.out.println(prefix + array[ii]);
	}
    }
    
    
    public static void main(String [] args)
    {
	// The main method tries out the effects of the various
	// StringVector methods. Run it to make sure your
	// implementations are correct.
	
	StringVector sv = new StringVector(1);
	
	sv.pushBack("hello");
	for (int ii = 0; ii < 3; ++ii) {
	    sv.pushBack(" " + ii);
	}
	sv.pushBack("byebye!");
	sv.print("* ");
	
	if (sv.empty()) {
	    System.out.println("the StringVector is empty");
	}
	else {
	    System.out.println("the StringVector is not empty");
	}
	
	sv.clear();
	sv.print("* ");
	
	if (sv.empty()) {
	    System.out.println("the StringVector is empty");
	}
	else {
	    System.out.println("the StringVector is not empty");
	}
	
	sv.pushBack("one");
	sv.pushBack("two");
	sv.pushBack("three");
	for (int ii = 0; ii < sv.size(); ++ii) {
	    System.out.print(" " + sv.at(ii));
	}
	System.out.println();
	
	System.out.println("the StringVector contains " + sv.size() + " elements");
	sv.print("* ");
	while ( ! sv.empty()) {
	    System.out.println("  pop " + sv.back());
	    sv.popBack();
	    sv.print("  - ");
	}
	
	sv.clear();
	sv.pushBack("one");
	sv.pushBack("two");
	sv.pushBack("three");
	sv.print(" before  ");
	sv.insertAt("HELLO", 1);
	sv.print(" after  ");
	
    }
}
