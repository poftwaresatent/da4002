public class ExampleA
{
    private static int    nMin    =   1024;
    private static int    nMax    = 100000;
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
	
	LogBook log = new LogBook("container operations",
				  "number of operations",
				  "elapsed time [ms]");
	LogSeries listPushFrontSeries = log.addSeries("list push front");
	LogSeries vectorPushBackSeries = log.addSeries("vector push back");
	
	System.out.println();
	System.out.println("time required for container operations");
	System.out.println("--------------------------------------");
	System.out.println("N\tlist push front\tvector push back");
	
	for (int ii = nMin; nMax >= ii; ii = (int) Math.round(ii * nFactor)) {
	    try {
		System.out.print(ii);
		long dt;
		String[] data = Factory.createRandomStrings(ii);
		
		StringList list = new StringList();
		listPushFrontSeries.start();
		for (int jj = 0; jj < ii; ++jj) {
		    list.pushFront(data[jj]);
		}
		dt = listPushFrontSeries.stop("" + ii);
		System.out.print("\t\t" + dt);
		
		StringVector vector = new StringVector(256);
		vectorPushBackSeries.start();
		for (int jj = 0; jj < ii; ++jj) {
		    vector.pushBack(data[jj]);
		}
		dt = vectorPushBackSeries.stop("" + ii);
		System.out.print("\t\t" + dt);
		
		//////////////////////////////////////////////////
		//
		// Hint for extending this benchmark to measure how
		// long it takes to find strings:
		//
		// String[] samples = Factory.createSamples(data, 100, 0.1);
		//
		// This will create a sample array of 100 strings,
		// where each element is taken randomly from the data
		// array, and 10% of the samples will be freshly
		// created random strings. Thus, we can expect 90% of
		// the samples to exist in the data, but 10% will not
		// be found.
		//
		//////////////////////////////////////////////////
		
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
