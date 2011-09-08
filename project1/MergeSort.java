public class MergeSort
{
    static private void dump(String title, int[] array, int ii)
    {
	System.out.print(title);
	for (int jj = 0; jj <= ii; ++jj) {
	    System.out.print("  " + array[jj]);
	}
	System.out.println();
    }
    
    static public void main(String[] args)
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
}
