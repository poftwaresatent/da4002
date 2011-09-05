/**
   A vector of strings which grows on demand. Each time the size hits
   the current capacity, the capacity is doubled.
*/
public class StringVector
{
    private String [] data;
    private int size;
    
    /**
       Initialize the StringVector with a given initial
       capacity. <b>Do not</b> set initialCapacity to zero, it must be
       strictly positive.
    */
    public StringVector(int initialCapacity)
    {
	data = new String [initialCapacity];
	size = 0;
    }
    
    /**
       Double the capacity of the underlying array by creating a
       bigger array twice the size, then copying all the old data
       over.
    */
    private void grow()
    {
	String [] bigger = new String [2 * data.length];
	for (int ii = 0; ii < size; ++ii) {
	    bigger[ii] = data[ii];
	}
	data = bigger;
    }
    
    /**
       Insert a value at the front of the string vector. All
       previously stored items must be moved out of the way first, so
       this can be a bit expensive.
    */
    public void insertFront(String value)
    {
	if (size >= data.length) {
	    grow();
	}
	for (int ii = 0, jj = 1; ii < size; ++ii, ++jj) {
	    data[jj] = data[ii];
	}
	data[0] = value;
	++size;
    }
    
    /**
       Insert a value at the end of the string vector.
    */
    public void insertRear(String value)
    {
	if (size >= data.length) {
	    grow();
	}
	data[size++] = value;
    }
    
    /**
       Prints all elements of the string vector on a separate line of
       System.out. Each line is prefixed with the given string to
       allow a basic form of custom formatting.
    */
    public void print(String prefix)
    {
	for (int ii = 0; ii < size; ++ii) {
	    System.out.println(prefix + data[ii]);
	}
    }
    
    /**
       A static function that demonstrates some of the vector
       operations. When verbose is true it prints messages to
       System.out.
    */
    public static void demo(boolean verbose)
    {
	StringVector vector = new StringVector(256);
	
	if (verbose) {
	    System.out.println("Inserting three items at the front.");
	}
	
	vector.insertFront("blah one");
	vector.insertFront("blah two");
	vector.insertFront("blah three");
	
	if (verbose) {
	    System.out.println("  Result:");
	    vector.print("  - ");
	    System.out.println();
	    System.out.println("Inserting three items at the rear.");
	}
	
	vector.insertRear("blih one");
	vector.insertRear("blih two");
	vector.insertRear("blih three");

	if (verbose) {
	    System.out.println("  Result:");
	    vector.print("  - ");
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
