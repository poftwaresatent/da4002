public class BonusAOrderDependence
{
    private static int    nMin    =   200;
    private static int    nMax    = 15000;
    private static double nFactor = Math.sqrt(2.0);
    static private java.util.Random rnd = new java.util.Random();
    
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
	
	LogBook timeLog
	    = new LogBook("BS tree order dependency (random/sorted/reverse/duplicates)",
			  "number of operations",
			  "elapsed time for insertion [ms]");
	LogSeries timeRandom = timeLog.addSeries("random");
	LogSeries timeSorted = timeLog.addSeries("sorted");
	LogSeries timeReverse = timeLog.addSeries("reverse");
	LogSeries timeDuplicates = timeLog.addSeries("duplicates");
	
	LogBook extraLog
	    = new LogBook("BS tree order dependency (random/sorted/reverse/duplicates)",
			  "number of operations",
			  "number of nodes / path length");
	
	LogSeries sizeRandom = extraLog.addSeries("size (random)");
	LogSeries heightRandom = extraLog.addSeries("height (random)");
	LogSeries sizeSorted = extraLog.addSeries("size (sorted)");
	LogSeries heightSorted = extraLog.addSeries("height (sorted)");
	LogSeries sizeReverse = extraLog.addSeries("size (reverse)");
	LogSeries heightReverse = extraLog.addSeries("height (reverse)");
	LogSeries sizeDuplicates = extraLog.addSeries("size (duplicates)");
	LogSeries heightDuplicates = extraLog.addSeries("height (duplicates)");
	
	System.out.println();
	System.out.println("BS tree order dependency (random/sorted/reverse/duplicates)");
	System.out.println("--------------------------------------");
	//                  123456   12345 12345 12345 12345   123456 123456 123456 123456   123456 123456 123456 123456
	System.out.println("     N               insert time                          size                        height");
	
	for (int ii = nMin; nMax >= ii; ii = (int) Math.round(ii * nFactor)) {
	    try {
		System.out.printf("%6d", ii);
		long dt;
		String[] randomData = Factory.createRandomStrings(ii);
		String[] sortedData = Factory.duplicate(randomData);
		java.util.Arrays.sort(sortedData);
		String[] reverseData = new String[ii];
		for (int jj = 0; jj < ii; ++jj) {
		    reverseData[jj] = sortedData[ii - jj - 1];
		}
		String[] duplicatesData = new String[ii];
		outer:
		for (int jj = 0; jj < ii; /**/) {
		    int len = rnd.nextInt(10) + 1;
		    for (int kk = 0; kk < len; ++kk) {
			if (jj+kk >= ii) {
			    break outer;
			}
			duplicatesData[jj + kk] = randomData[jj];
		    }
		    jj += len;
		}
		
		StringBSTree bstree = new StringBSTree();
		timeRandom.startSingle();
		for (int jj = 0; jj < ii; ++jj) {
		    bstree.insert(randomData[jj]);
		}
		dt = timeRandom.stopSingle("" + ii);
		System.out.printf("   %5d", dt);
		int bstreeSizeRandom = bstree.root.computeSize();
		sizeRandom.addCustom("" + ii, "" + bstreeSizeRandom);
		int bstreeHeightRandom = bstree.root.computeHeight();
		heightRandom.addCustom("" + ii, "" + bstreeHeightRandom);
		
		bstree = new StringBSTree();
		timeSorted.startSingle();
		for (int jj = 0; jj < ii; ++jj) {
		    bstree.insert(sortedData[jj]);
		}
		dt = timeSorted.stopSingle("" + ii);
		System.out.printf(" %5d", dt);
		int bstreeSizeSorted = bstree.root.computeSize();
		sizeSorted.addCustom("" + ii, "" + bstreeSizeSorted);
		int bstreeHeightSorted = bstree.root.computeHeight();
		heightSorted.addCustom("" + ii, "" + bstreeHeightSorted);
		
		bstree = new StringBSTree();
		timeReverse.startSingle();
		for (int jj = 0; jj < ii; ++jj) {
		    bstree.insert(reverseData[jj]);
		}
		dt = timeReverse.stopSingle("" + ii);
		System.out.printf(" %5d", dt);
		int bstreeSizeReverse = bstree.root.computeSize();
		sizeReverse.addCustom("" + ii, "" + bstreeSizeReverse);
		int bstreeHeightReverse = bstree.root.computeHeight();
		heightReverse.addCustom("" + ii, "" + bstreeHeightReverse);
		
		bstree = new StringBSTree();
		timeDuplicates.startSingle();
		for (int jj = 0; jj < ii; ++jj) {
		    bstree.insert(duplicatesData[jj]);
		}
		dt = timeDuplicates.stopSingle("" + ii);
		System.out.printf(" %5d", dt);
		int bstreeSizeDuplicates = bstree.root.computeSize();
		sizeDuplicates.addCustom("" + ii, "" + bstreeSizeDuplicates);
		int bstreeHeightDuplicates = bstree.root.computeHeight();
		heightDuplicates.addCustom("" + ii, "" + bstreeHeightDuplicates);
		
		System.out.printf("   %6d %6d %6d %6d   %6d %6d %6d %6d\n",
				  bstreeSizeRandom,
				  bstreeSizeSorted,
				  bstreeSizeReverse,
				  bstreeSizeDuplicates,
				  bstreeHeightRandom,
				  bstreeHeightSorted,
				  bstreeHeightReverse,
				  bstreeHeightDuplicates);
	    }
	    catch (OutOfMemoryError ee) {
		System.out.println();
		System.out.println("OUT OF MEMORY: aborting experiment");
		System.out.println();
		break;
	    }
	    catch (StackOverflowError ee) {
		System.out.println();
		System.out.println("STACK OVERFLOW: aborting experiment");
		System.out.println();
		break;
	    }
	}
	
	System.out.println();
	System.out.println("==================================================");
	System.out.println("Creating log and plot files for runtimes");
	timeLog.createFiles();
	
	System.out.println();
	System.out.println("==================================================");
	System.out.println("Creating log and plot files for extra data");
	extraLog.createFiles();
    }
}
