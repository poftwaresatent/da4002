public class MandatoryA
{
    private static int    nMin    =    5000;
    private static int    nMax    = 1000000;
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
		nMin = Integer.parseInt(args[0]);
	    }
	}
	catch (NumberFormatException ee) {
	    System.err.println("failed to parse arguments:");
	    System.err.println("  expected [nMin [nMax [nFactor]]]");
	    System.exit(42);
	}
    }
    
    public static void main(String [] args)
    {
	parseOptions(args);
	
	LogBook insertionLog = new LogBook("container insertions",
					   "number of operations",
					   "elapsed time [ms]");
	
	LogSeries listPushFrontSeries = insertionLog.addSeries("list push front");
	LogSeries vectorPushBackSeries = insertionLog.addSeries("vector push back");
	LogSeries bstreeInsertSeries = insertionLog.addSeries("binary search tree insert");
	
	LogBook removalLog = new LogBook("container removals",
					 "number of operations",
					 "elapsed time [ms]");
	
	LogSeries listPopFrontSeries = removalLog.addSeries("list pop front");
	LogSeries vectorPopBackSeries = removalLog.addSeries("vector pop back");
	LogSeries bstreeRemoveMinSeries = removalLog.addSeries("binary search tree remove-min");
	
	System.out.println();
	System.out.println("time required for container operations");
	System.out.println("--------------------------------------");
	System.out.println("N\tlist push/pop front\tvector push/pop back\tbs tree insert/rm-min");
	
	for (int ii = nMin; nMax >= ii; ii = (int) Math.round(ii * nFactor)) {
	    try {
		System.out.print(ii);
		long dt;
		String[] data = Factory.createRandomStrings(ii);
		
		StringList list = new StringList();
		listPushFrontSeries.startSingle();
		for (int jj = 0; jj < ii; ++jj) {
		    list.pushFront(data[jj]);
		}
		dt = listPushFrontSeries.stopSingle("" + ii);
		System.out.print("\t" + dt);
		
		listPopFrontSeries.startSingle();
		for (int jj = 0; jj < ii; ++jj) {
		    list.popFront();
		}
		dt = listPopFrontSeries.stopSingle("" + ii);
		System.out.print("\t" + dt);
		
		StringVector vector = new StringVector(256);
		vectorPushBackSeries.startSingle();
		for (int jj = 0; jj < ii; ++jj) {
		    vector.pushBack(data[jj]);
		}
		dt = vectorPushBackSeries.stopSingle("" + ii);
		System.out.print("\t\t" + dt);
		
		vectorPopBackSeries.startSingle();
		for (int jj = 0; jj < ii; ++jj) {
		    vector.popBack();
		}
		dt = vectorPopBackSeries.stopSingle("" + ii);
		System.out.print("\t" + dt);
		
		StringBSTree bstree = new StringBSTree();
		bstreeInsertSeries.startSingle();
		for (int jj = 0; jj < ii; ++jj) {
		    bstree.insert(data[jj]);
		}
		dt = bstreeInsertSeries.stopSingle("" + ii);
		System.out.print("\t\t" + dt);

		bstreeRemoveMinSeries.startSingle();
		for (int jj = 0; jj < ii; ++jj) {
		    bstree.removeMin();
		}
		dt = bstreeRemoveMinSeries.stopSingle("" + ii);
		System.out.print("\t" + dt);
		
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
	
	System.out.println();
	System.out.println("==================================================");
	System.out.println("Creating log and plot files for insertion benchmark");
	insertionLog.createFiles();
	
	System.out.println();
	System.out.println("--------------------------------------------------");
	System.out.println("Creating log and plot files for removal benchmark");
	removalLog.createFiles();
    }
}
