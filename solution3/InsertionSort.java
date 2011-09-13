public class InsertionSort
{
    static public void sort(String[] array)
    {
	for (int ii = 1; ii < array.length; ++ii) {
	    String ival = array[ii];
	    int jj = ii;
	    for ( ; jj > 0 && ival.compareTo(array[jj-1]) < 0; --jj) {
		array[jj] = array[jj-1];
	    }
	    array[jj] = ival;
	}
    }
    
    
    static public void main(String[] args)
    {
	String[] data = Factory.createRandomStrings(10);
	
	System.out.println("before");
	for (int jj = 0; jj < data.length; ++jj) {
	    System.out.println("  " + data[jj]);
	}
	
	sort(data);

	System.out.println("after");
	for (int jj = 0; jj < data.length; ++jj) {
	    System.out.println("  " + data[jj]);
	}	
    }   
}
