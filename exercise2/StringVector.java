public class StringVector
{
    // As you implement each of the methods, add the required fields
    // here.
    
    
    public StringVector(int initialCapacity)
    {
	// Write a constructor which initializes the underlying string
	// array to the given capacity.
    }
    
    
    private void grow()
    {
	// Write a method which doubles the capacity of the
	// StringVector by creating a new array of the appropriate
	// size, copies the current data into the new array, and then
	// replacing the data reference with the newly created bigger
	// array.
    }
    
    
    public void pushBack(String value)
    {
	// Write a method which appends the given value to the data
	// array. Make sure to first check whether the internal data
	// array needs to be grown.
    }
    
    
    public void popBack()
    {
	// Write a method that removes the last element from the
	// StringVector.
    }
    
    
    public String get(int index)
    {
	// Write a method which returns the element stored at the
	// index given as argument.
	return "IMPLEMENT METHOD StringVector.get";
    }
    
    
    public String getBack()
    {
	// Write a method which returns the last element.
	return "IMPLEMENT METHOD StringVector.getBack";
    }
    
    
    public int size()
    {
	// Write a method which returns the number of items currently
	// stored in the StringVector.
	return 0;	      // this is just a placeholder for now...
    }
    
    
    public boolean empty()
    {
	// Write a method which determines whether the StringArray is
	// currently empty.
	return true;	      // this is just a placeholder for now...
    }
    
    
    public void clear()
    {
	// Write a method which removes all elements from the
	// StringArray.
    }
    
    
    public void print(String prefix)
    {
       // Write a method which prints all elements of the
       // StringVector, each on a separate line. Each line should
       // begin with the prefix given as argument.
    }
    
    
    public static void main(String [] args)
    {
	// The main method tries out the effects of the various
	// StringVector methods. Run it to make sure your
	// implementations are correct.
	//
	// Optional: can you think of good ways for automatically
	// testing the correctness of each method with the help of a
	// little example code?
	
	StringVector sv = new StringVector(64);
	
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
	
	if (sv.empty()) {
	    System.out.println("the StringVector is empty");
	}
	else {
	    System.out.println("the StringVector is not empty");
	}
	
	sv.pushBack("one");
	sv.pushBack("two");
	sv.pushBack("three");
	
	System.out.println("the StringVector contains " + sv.size() + " elements");
	sv.print("* ");
	while ( ! sv.empty()) {
	    System.out.println("  pop " + sv.getBack());
	    sv.popBack();
	    sv.print("  - ");
	}
    }
}
