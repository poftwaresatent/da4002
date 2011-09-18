public class BonusA
{
    private static int    nAvg    =      10;
    private static int    nMin    =    1000;
    private static int    nMax    =  200000;
    private static double nFactor = Math.sqrt(2.0);
    
    private static void parseOptions(String [] args)
    {
	try {
	    if (4 <= args.length) {
		nAvg = Integer.parseInt(args[0]);
		nMin = Integer.parseInt(args[1]);
		nMax = Integer.parseInt(args[2]);
		nFactor = Double.parseDouble(args[3]);
	    }
	    else if (3 <= args.length) {
		nAvg = Integer.parseInt(args[0]);
		nMin = Integer.parseInt(args[1]);
		nMax = Integer.parseInt(args[2]);
	    }
	    else if (1 <= args.length) {
		nAvg = Integer.parseInt(args[0]);
	    }
	}
	catch (NumberFormatException ee) {
	    System.err.println("failed to parse arguments:");
	    System.err.println("  expected [nAvg [nMin [nMax [nFactor]]]]");
	    System.exit(42);
	}
    }
    
    public static void main(String [] args)
    {
	parseOptions(args);
	
	LogBook insertionLog = new LogBook("container insertions",
					   "number of operations",
					   "average (N=" + nAvg + ") elapsed time [ms]");
	
	LogSeries listPushFrontSeries = insertionLog.addSeries("list push front");
	LogSeries vectorPushBackSeries = insertionLog.addSeries("vector push back");
	LogSeries bstreeInsertSeries = insertionLog.addSeries("binary search tree insert");
	
	LogBook removalLog = new LogBook("container removals",
					 "number of operations",
					 "average (N=" + nAvg + ") elapsed time [ms]");
	
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
		
		String[][] data = new String[nAvg][];
		for (int kk = 0; kk < nAvg; ++kk) {
		    data[kk] = Factory.createRandomStrings(ii);
		}
		
		listPushFrontSeries.initAverage();
		listPopFrontSeries.initAverage();
		for (int kk = 0; kk < nAvg; ++kk) {
		    StringList list = new StringList();
		    listPushFrontSeries.startAverage();
		    for (int jj = 0; jj < ii; ++jj) {
			list.pushFront(data[kk][jj]);
		    }
		    listPushFrontSeries.stopAverage();
		    listPopFrontSeries.startAverage();
		    for (int jj = 0; jj < ii; ++jj) {
			list.popFront();
		    }
		    listPopFrontSeries.stopAverage();
		}
		double dt = listPushFrontSeries.finalizeAverage("" + ii);
		System.out.print("\t" + dt);
		dt = listPopFrontSeries.finalizeAverage("" + ii);
		System.out.print("\t" + dt);
		
		vectorPushBackSeries.initAverage();
		vectorPopBackSeries.initAverage();
		for (int kk = 0; kk < nAvg; ++kk) {
		    StringVector vector = new StringVector(256);
		    vectorPushBackSeries.startAverage();
		    for (int jj = 0; jj < ii; ++jj) {
			vector.pushBack(data[kk][jj]);
		    }
		    vectorPushBackSeries.stopAverage();
		    vectorPopBackSeries.startAverage();
		    for (int jj = 0; jj < ii; ++jj) {
			vector.popBack();
		    }
		    vectorPopBackSeries.stopAverage();
		}
		dt = vectorPushBackSeries.finalizeAverage("" + ii);
		System.out.print("\t\t" + dt);
		dt = vectorPopBackSeries.finalizeAverage("" + ii);
		System.out.print("\t" + dt);
		
		bstreeInsertSeries.initAverage();
		bstreeRemoveMinSeries.initAverage();
		for (int kk = 0; kk < nAvg; ++kk) {
		    StringBSTree bstree = new StringBSTree();
		    bstreeInsertSeries.startAverage();
		    for (int jj = 0; jj < ii; ++jj) {
			bstree.insert(data[kk][jj]);
		    }
		    bstreeInsertSeries.stopAverage();
		    bstreeRemoveMinSeries.startAverage();
		    for (int jj = 0; jj < ii; ++jj) {
			bstree.removeMin();
		    }
		    bstreeRemoveMinSeries.stopAverage();
		}
		dt = bstreeInsertSeries.finalizeAverage("" + ii);
		System.out.print("\t\t" + dt);
		dt = bstreeRemoveMinSeries.finalizeAverage("" + ii);
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
