public class InsertionSort
{
    /**
       Writes an array to the console, from index 0 up to (including)
       index ii. The title is printed out first on a separate line,
       and the arry output is indented by two spaces.
    */
    static private void dump(String title, int[] array, int ii)
    {
	System.out.print(title);
	for (int jj = 0; jj <= ii; ++jj) {
	    System.out.print("  " + array[jj]);
	}
	System.out.println();
    }
    
    
    /**
       A small demo of insetion sort, which writes progress
       information on the console. This can help to understand of
       insertion sort works.
    */
    static public void demo()
    {
	int[] array = { 17, 8, 99, 14, 1009, 71, 72, 99, 8, 70 };
	
	dump("init:", array, array.length - 1);
	
	for (int ii = 1; ii < array.length; ++ii) {
	    int ival = array[ii];

	    System.out.println();
	    System.out.println("ival[" + ii + "] = " + ival);
	    dump("  -->", array, ii);
	    
	    int jj = ii - 1;	    
	    for (; jj >= 0 && ival < array[jj]; --jj) {
		array[jj + 1] = array[jj];
		dump("  [" + jj + "]", array, ii);
	    }
	    array[++jj] = ival;
	    dump("  <--", array, ii);
	}
	
	System.out.println();
	dump("fini:", array, array.length - 1);
    }
    
    
    /**
       Sort an array of strings, using insertion sort. The
       effectiveLength parameter can be used to limit the sort to a
       sub-array, for example when the array is the underying storage
       for a vector. In that case, you will say "sort(sv.raw(),
       sv.size()" assuming sv is an instance of StringVector.
    */
    static public void sort(String[] array, int effectiveLength)
    {
	for (int ii = 1; ii < effectiveLength; ++ii) {
	    String ival = array[ii];
	    int jj = ii;
	    for ( ; jj > 0 && ival.compareTo(array[jj-1]) < 0; --jj) {
		array[jj] = array[jj-1];
	    }
	    array[jj] = ival;
	}
    }
    
    
    static public void sort(String[] array)
    {
	sort(array, array.length);
    }
    
    
    static private void print(String title, String prefix, String[] array)
    {
	System.out.println(title);
	for (int jj = 0; jj < array.length; ++jj) {
	    System.out.println(prefix + array[jj]);
	}
    }
    
    
    static public void main(String[] args)
    {
	String[] data = Factory.createRandomStrings(10);
	
	print("before:", "  ", data);
	sort(data);
	print("\nafter:", "  ", data);
    }
    
}
