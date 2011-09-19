public class BubbleSort
{
    static public void sort(String[] array)
    {
	int nRemain = array.length;
	while (nRemain > 0) {
	    int nextN = 0;
	    for (int ii = 1; ii < nRemain; ++ii) {
		if (array[ii-1].compareTo(array[ii]) > 0) {
		    String tmp = array[ii-1];
		    array[ii-1] = array[ii];
		    array[ii] = tmp;
		    nextN = ii;
		}
	    }
	    nRemain = nextN;
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
