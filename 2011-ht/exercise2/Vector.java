public class Vector<AnyType>
{
    /**
       The array field contains the underlying data storage.
    */
    private AnyType[] array;
    
    /**
       The size field tracks the current size of the Vector,
       independently from array.length (which is the current
       capacity).
    */
    private int size;
    
    
    public Vector(int initialCapacity)
    {
	array = (AnyType[]) new Object [initialCapacity];
	size = 0;
    }
    
    
    private void grow()
    {
	AnyType [] bigger = (AnyType[]) new Object [2 * array.length];
	for (int ii = 0; ii < size; ++ii) {
	    bigger[ii] = array[ii];
	}
	array = bigger;
    }
    
    
    public void pushBack(AnyType value)
    {
	if (size >= array.length) {
	    grow();
	}
	array[size++] = value;
    }
    
    
    public void popBack()
    {
	--size;
    }
    
    
    public AnyType at(int index)
    {
	return array[index];
    }
    
    
    public AnyType back()
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
	// Vector methods. Run it to make sure your
	// implementations are correct.
	
	Vector<Double> dv = new Vector<Double>(1);
	
	dv.pushBack(42.0);
	for (int ii = 0; ii < 3; ++ii) {
	    dv.pushBack(ii + 0.5);
	}
	dv.pushBack(17.0);
	dv.print("* ");
	
	if (dv.empty()) {
	    System.out.println("the Vector is empty");
	}
	else {
	    System.out.println("the Vector is not empty");
	}
	
	dv.clear();
	dv.print("* ");
	
	if (dv.empty()) {
	    System.out.println("the Vector is empty");
	}
	else {
	    System.out.println("the Vector is not empty");
	}
	
	dv.pushBack(11.1);
	dv.pushBack(22.2);
	dv.pushBack(33.3);
	for (int ii = 0; ii < dv.size(); ++ii) {
	    System.out.print(" " + dv.at(ii));
	}
	System.out.println();
	
	System.out.println("the Vector contains " + dv.size() + " elements");
	dv.print("* ");
	while ( ! dv.empty()) {
	    System.out.println("  pop " + dv.back());
	    dv.popBack();
	    dv.print("  - ");
	}
    }
}
