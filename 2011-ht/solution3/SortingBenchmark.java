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
	final int sizeMin = 100;
	final int sizeMax = 10000;
	final double sizeFactor = 1.5;
	
	System.out.println();
	System.out.println("time required to sort arrays of random strings");
	System.out.println("----------------------------------------------");
	System.out.println("array size\tinsertion sort\tmerge sort\tbubble sort");
	for (int ii = sizeMin; ii < sizeMax; ii = (int) Math.round(ii * sizeFactor)) {
	    System.out.print(ii);
	    String[] data = Factory.createRandomStrings(ii);

	    String[] clone = Factory.duplicate(data);
	    long tStart = System.currentTimeMillis();
	    InsertionSort.sort(clone);
	    long tEnd = System.currentTimeMillis();
	    System.out.print("\t\t" + (tEnd - tStart));
	    
	    // Make sure to create a new duplicate of the original
	    // UNSORTED data before running each algorithm.
	    
	    clone = Factory.duplicate(data);
	    tStart = System.currentTimeMillis();
	    MergeSort.sort(clone);
	    tEnd = System.currentTimeMillis();
	    System.out.print("\t\t" + (tEnd - tStart));
	    
	    // Make sure to create a new duplicate of the original
	    // UNSORTED data before running each algorithm.
	    
	    clone = Factory.duplicate(data);
	    tStart = System.currentTimeMillis();
	    BubbleSort.sort(clone);
	    tEnd = System.currentTimeMillis();
	    System.out.println("\t\t" + (tEnd - tStart));
	}
	
	System.out.println();
	System.out.println("time required to sort arrays of already sorted strings");
	System.out.println("------------------------------------------------------");
	System.out.println("array size\tinsertion sort\tmerge sort\tbubble sort");
	for (int ii = sizeMin; ii < sizeMax; ii = (int) Math.round(ii * sizeFactor)) {
	    System.out.print(ii);
	    String[] data = Factory.createRandomStrings(ii);
	    MergeSort.sort(data);
	    
	    long tStart = System.currentTimeMillis();
	    InsertionSort.sort(data);
	    long tEnd = System.currentTimeMillis();
	    System.out.print("\t\t" + (tEnd - tStart));
	    
	    tStart = System.currentTimeMillis();
	    MergeSort.sort(data);
	    tEnd = System.currentTimeMillis();
	    System.out.print("\t\t" + (tEnd - tStart));
	    
	    tStart = System.currentTimeMillis();
	    BubbleSort.sort(data);
	    tEnd = System.currentTimeMillis();
	    System.out.println("\t\t" + (tEnd - tStart));
	}
	
	System.out.println();
	System.out.println("time required to sort arrays of inverted-order sorted strings");
	System.out.println("-------------------------------------------------------------");
	System.out.println("array size\tinsertion sort\tmerge sort\tbubble sort");
	for (int ii = sizeMin; ii < sizeMax; ii = (int) Math.round(ii * sizeFactor)) {
	    System.out.print(ii);
	    String[] sorted = Factory.createRandomStrings(ii);
	    MergeSort.sort(sorted);
	    String[] data = new String[sorted.length];
	    for (int kk = 0, jj = sorted.length-1; kk < sorted.length; ++kk, --jj) {
		data[kk] = sorted[jj];
	    }
	    
	    String[] clone = Factory.duplicate(data);
	    long tStart = System.currentTimeMillis();
	    InsertionSort.sort(clone);
	    long tEnd = System.currentTimeMillis();
	    System.out.print("\t\t" + (tEnd - tStart));
	    
	    clone = Factory.duplicate(data);
	    tStart = System.currentTimeMillis();
	    MergeSort.sort(clone);
	    tEnd = System.currentTimeMillis();
	    System.out.print("\t\t" + (tEnd - tStart));
	    
	    clone = Factory.duplicate(data);
	    tStart = System.currentTimeMillis();
	    BubbleSort.sort(clone);
	    tEnd = System.currentTimeMillis();
	    System.out.println("\t\t" + (tEnd - tStart));
	}
    }
}
