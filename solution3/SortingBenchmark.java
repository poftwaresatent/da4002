public class SortingBenchmark
{
    static private void print(String title, String[] array)
    {
	System.out.println(title);
	for (int jj = 0; jj < array.length; ++jj) {
	    System.out.println("  " + array[jj]);
	}
    }
    
    
    static public void main(String[] args)
    {
	System.out.println("array size\tinsertion sort\tmerge sort");
	for (int ii = 500; ii < 40000; ii = (int) Math.round(ii * 1.5)) {
	    System.out.print(ii);
	    String[] data = Factory.createRandomStrings(ii);

	    String[] clone = Factory.duplicate(data);
	    long tStart = System.currentTimeMillis();
	    InsertionSort.sort(clone);
	    long tEnd = System.currentTimeMillis();
	    System.out.print("\t\t" + (tEnd - tStart));
	    
	    clone = Factory.duplicate(data);
	    tStart = System.currentTimeMillis();
	    MergeSort.sort(clone);
	    tEnd = System.currentTimeMillis();
	    System.out.println("\t\t" + (tEnd - tStart));
	}
    }
}
