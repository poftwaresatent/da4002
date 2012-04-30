public class BonusASearch
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
	
	LogBook searchLog = new LogBook("finding items",
					"number of searches",
					"elapsed time [ms]");
	
	LogSeries listFindSeries = searchLog.addSeries("linear find on list");
	LogSeries bstreeFindSeries = searchLog.addSeries("find in binary search tree");
	
	System.out.println();
	System.out.println("time required for container operations");
	System.out.println("--------------------------------------");
	System.out.println("N\tlist push/find/pop\tvector push/pop\tbs tree insert/find/rm-min");
	
	for (int ii = nMin; nMax >= ii; ii = (int) Math.round(ii * nFactor)) {
	    try {
		System.out.print(ii);
		long dt;
		String[] data = Factory.createRandomStrings(ii);
		String[] samples = Factory.createSamples(data, 1000, 0.1);
		
		StringList list = new StringList();
		listPushFrontSeries.startSingle();
		for (int jj = 0; jj < ii; ++jj) {
		    list.pushFront(data[jj]);
		}
		dt = listPushFrontSeries.stopSingle("" + ii);
		System.out.print("\t" + dt);
		
		listFindSeries.startSingle();
		for (int kk = 0; kk < samples.length; ++kk) {
		    list.find(samples[kk]);
		}
		dt = listFindSeries.stopSingle("" + ii);
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
		
		bstreeFindSeries.startSingle();
		for (int kk = 0; kk < samples.length; ++kk) {
		    bstree.find(samples[kk]);
		}
		dt = bstreeFindSeries.stopSingle("" + ii);
                System.out.print("\t" + dt);
		
		bstreeRemoveMinSeries.startSingle();
		for (int jj = 0; jj < ii; ++jj) {
		    bstree.removeMin();
		}
		dt = bstreeRemoveMinSeries.stopSingle("" + ii);
		System.out.print("\t" + dt);
		
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
	
	System.out.println();
	System.out.println("--------------------------------------------------");
	System.out.println("Creating log and plot files for search benchmark");
	searchLog.createFiles();
    }
}
