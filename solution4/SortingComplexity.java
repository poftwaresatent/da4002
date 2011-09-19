import java.io.*;

public class SortingComplexity
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
	final String separator = "\t";
	final String filename = "log.data";
	try {
	    FileWriter logFile = new FileWriter(filename);
	
	    System.out.println();
	    System.out.println("time required to sort arrays of random strings");
	    System.out.println("----------------------------------------------");
	    System.out.println("array size\tinsertion sort\tmerge sort\tbubble sort");
	    for (int ii = sizeMin; ii < sizeMax; ii = (int) Math.round(ii * sizeFactor)) {
		System.out.print(ii);
		logFile.write("" + ii);
		String[] data = Factory.createRandomStrings(ii);

		String[] clone = Factory.duplicate(data);
		long tStart = System.currentTimeMillis();
		InsertionSort.sort(clone);
		long tEnd = System.currentTimeMillis();
		long dt = tEnd - tStart;
		System.out.print("\t\t" + dt);
		logFile.write(separator + dt);
		
		// Make sure to create a new duplicate of the original
		// UNSORTED data before running each algorithm.
	    
		clone = Factory.duplicate(data);
		tStart = System.currentTimeMillis();
		MergeSort.sort(clone);
		tEnd = System.currentTimeMillis();
		dt = tEnd - tStart;
		System.out.print("\t\t" + dt);
		logFile.write(separator + dt);
		
		// Make sure to create a new duplicate of the original
		// UNSORTED data before running each algorithm.
	    
		clone = Factory.duplicate(data);
		tStart = System.currentTimeMillis();
		BubbleSort.sort(clone);
		tEnd = System.currentTimeMillis();
		dt = tEnd - tStart;
		System.out.print("\t\t" + dt);
		logFile.write(separator + dt);
		
		System.out.println();
		logFile.write("\n");
	    }
	    
	    logFile.close();
	    System.out.println("wrote data to file `" + filename + "'");
	    
	}
	catch (IOException ee) {
	    System.err.println("Failure due to some input-output problem:\n  " + ee);
	    System.exit(42);
	}
    }
}
