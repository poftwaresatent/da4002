import java.util.LinkedList;

public class ExampleC
{
    private static int    nDataMin        =      50;
    private static int    nDataMax        =     800;
    private static double nDataFactor     =       4.0;
    private static int    nSearchesMin    =      10;
    private static int    nSearchesMax    =  102400;
    private static double nSearchesFactor = Math.sqrt(2.0);

    private static double[] pRandom = { 0.0, 0.1 };
    
    private static void parseOptions(String [] args)
    {
	try {
	    if (6 <= args.length) {
		nDataMin = Integer.parseInt(args[0]);
		nDataMax = Integer.parseInt(args[1]);
		nDataFactor = Double.parseDouble(args[2]);
		nSearchesMin = Integer.parseInt(args[3]);
		nSearchesMax = Integer.parseInt(args[4]);
		nSearchesFactor = Double.parseDouble(args[5]);
	    }
	    else if (3 <= args.length) {
		nDataMin = Integer.parseInt(args[0]);
		nDataMax = Integer.parseInt(args[1]);
		nDataFactor = Double.parseDouble(args[2]);
	    }
	    else if (2 <= args.length) {
		nDataMin = Integer.parseInt(args[0]);
		nDataMax = Integer.parseInt(args[1]);
	    }
	    else if (1 <= args.length) {
		nDataMax = Integer.parseInt(args[0]);
	    }
	}
	catch (NumberFormatException ee) {
	    System.err.println("failed to parse arguments: expected [int [int [double [int int double double* ]]]]");
	    System.exit(42);
	}
    }
    
    public static void main(String [] args)
    {
	parseOptions(args);
	LinkedList<LogBook> logs = new LinkedList<LogBook>();
	
	for (int iPrnd = 0; iPrnd < pRandom.length; ++iPrnd) {
	    double pRnd = pRandom[iPrnd];
	    
	    for (int iData = nDataMin; nDataMax >= iData; iData = (int) Math.round(iData * nDataFactor)) {
		LogBook log = new LogBook("read-once, search " + iData + " items, pRandom: " + pRnd,
					  "number of searches",
					  "elapsed time [ms]");
		logs.add(log);
		LogSeries unsortedListSeries = log.addSeries("unsorted list");
		LogSeries mergeSortVectorSeries = log.addSeries("vector / merge sort");
		
		System.out.println();
		System.out.println("time required to build/sort/search " + iData + " items (pRandom: " + pRnd + ")");
		System.out.println("------------------------------------------------------------------------------");
		System.out.println("N\tunsorted list\tvector / merge sort");
		
		for (int iSearches = nSearchesMin;
		     nSearchesMax >= iSearches;
		     iSearches = (int) Math.round(iSearches * nSearchesFactor))
		    {
			try {
			    System.out.print(iSearches);
			    long dt;
			    String[] data = Factory.createRandomStrings(iData);
			    String[] samples = Factory.createSamples(data, iSearches, pRnd);
			    
			    unsortedListSeries.start();
			    StringList list = new StringList(data);
			    for (int jj = 0; jj < iSearches; ++jj) {
				list.find(samples[jj]);
			    }
			    dt = unsortedListSeries.stop("" + iSearches);
			    System.out.print("\t\t" + dt);
			    
			    mergeSortVectorSeries.start();
			    StringVector vector = new StringVector(data);
			    MergeSort.sort(vector);
			    for (int jj = 0; jj < iSearches; ++jj) {
				BinarySearch.find(vector, samples[jj]);
			    }
			    dt = mergeSortVectorSeries.stop("" + iSearches);
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
	    }
	}
	
	System.out.println();
	System.out.println("==================================================");
	System.out.println("creating data and plot files");
	for (LogBook log : logs) {
	    System.out.println();
	    System.out.println("--------------------------------------------------");
	    System.out.println(log.description);
	    log.createFiles();
	}
    }
}
