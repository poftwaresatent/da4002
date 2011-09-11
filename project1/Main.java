public class Main
{
    public static void insert()
    {
	LogBook log = new LogBook("repeated insertion at the front");
	LogSeries listSeries = log.addSeries("list push front");
	LogSeries vectorSeries = log.addSeries("vector push back");
	
	String value = "whatever";
	
	for (int ii = 1024; 200000 >= ii; ii *= 2) {
	    System.out.println("inserting " + ii + " ...");
	    StringList list = new StringList();
	    StringVector vector = new StringVector(256);
	    try {
		
		listSeries.start();
		for (int jj = 0; jj < ii; ++jj) {
		    list.pushFront(value);
		}
		listSeries.stop("" + ii);
		
		vectorSeries.start();
		for (int jj = 0; jj < ii; ++jj) {
		    vector.pushBack(value);
		}
		vectorSeries.stop("" + ii);
		
	    }
	    catch (OutOfMemoryError ee) {
		System.out.println("OUT OF MEMORY: aborting experiment");
		break;
	    }
	}
	
	log.printGnuplotData();
	log.printGnuplotScript("foo.log",
			       "number of insertions",
			       "elapsed time [ms]",
			       true);
    }
    
    
    public static void sortRandom()
    {
	LogBook log = new LogBook("sorting algorithms");
	LogSeries insertionSortSeries = log.addSeries("insertion sort");
	LogSeries mergeSortSeries = log.addSeries("merge sort");
	
	for (int ii = 1; 200000 >= ii; ii *= 2) {
	    try {
		System.out.println("creating " + ii + " random strings...");
		String[] data = Factory.createRandomStrings(ii);
		String[] array = new String[data.length];
		
		System.out.println("running insertion sort...");
		for (int jj = 0; jj < data.length; ++jj) {
		    array[jj] = data[jj];
		}
		insertionSortSeries.start();
		InsertionSort.sort(array, array.length);
		insertionSortSeries.stop("" + ii);
		
		System.out.println("running merge sort...");
		for (int jj = 0; jj < data.length; ++jj) {
		    array[jj] = data[jj];
		}
		mergeSortSeries.start();
		MergeSort.sort(array, array.length);
		mergeSortSeries.stop("" + ii);
	    }
	    catch (OutOfMemoryError ee) {
		System.out.println("OUT OF MEMORY: aborting experiment");
		break;
	    }
	}
	
	log.printGnuplotData();
	log.printGnuplotScript("foo.log",
			       "number of items",
			       "elapsed time [ms]",
			       true);
    }
    
    
    public static void main(String [] args)
    {
	if (args.length < 1) {
	    System.out.println("please specify an experiment, such as \"sort\"");
	    System.exit(42);
	}
	if (args[0].equals("insert")) {
	    insert();
	}
	else if (args[0].equals("sort")) {
	    sortRandom();
	}
	else {
	    System.out.println("sorry, unknown experiment \"" + args[0] + "\"");
	    System.exit(42);
	}
    }
}
