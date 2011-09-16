public class ExampleB
{
    private static int    nMin    =   256;
    private static int    nMax    = 40000;
    private static double nFactor = Math.sqrt(2.0);

    private static void parseOptions(String [] args)
    {
	try {
	    if (3 <= args.length) {
		nMin = Integer.parseInt(args[0]);
		nMax = Integer.parseInt(args[1]);
		nFactor = Double.parseDouble(args[2]);
	    }
	    else if (2 <= args.length) {
		nMin = Integer.parseInt(args[0]);
		nMax = Integer.parseInt(args[1]);
	    }
	    else if (1 <= args.length) {
		nMax = Integer.parseInt(args[0]);
	    }
	}
	catch (NumberFormatException ee) {
	    System.err.println("failed to parse arguments: expected [int [int [double]]]");
	    System.exit(42);
	}
    }
    
    public static void main(String [] args)
    {
	parseOptions(args);
	
	LogBook log = new LogBook("sorting algorithms",
				  "input length",
				  "elapsed time [ms]");
	LogSeries insertionSortSeries = log.addSeries("insertion sort");
	LogSeries mergeSortSeries = log.addSeries("merge sort");
	
	String value = "whatever";
	
	System.out.println();
	System.out.println("time required to sort data");
	System.out.println("--------------------------");
	System.out.println("N\tinsertion sort\tmerge sort");
	
	for (int ii = nMin; nMax >= ii; ii = (int) Math.round(ii * nFactor)) {
	    try {
		System.out.print(ii);
		long dt;
		String[] data = Factory.createRandomStrings(ii);
		
		String[] clone = Factory.duplicate(data);
		insertionSortSeries.start();
		InsertionSort.sort(clone, clone.length);
		dt = insertionSortSeries.stop("" + ii);
		System.out.print("\t\t" + dt);
		
		clone = Factory.duplicate(data);
		mergeSortSeries.start();
		MergeSort.sort(clone, clone.length);
		dt = mergeSortSeries.stop("" + ii);
		System.out.print("\t\t" + dt);
		
		System.out.println();
	    }
	    catch (OutOfMemoryError ee) {
		System.out.println();
		System.out.println("OUT OF MEMORY: aborting experiment");
		System.out.println();
		break;
	    }
	}
	
	log.createFiles();
    }
}
