package project1;

import exercise2.solution.*;

public class SequenceComplexity
{
    public static void pushBenchmark()
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
		System.out.println("OUT OF MEMORY: aborting benchmark");
		break;
	    }
	}
	
	log.printGnuplotData();
	log.printGnuplotScript("foo.log",
			       "number of insertions",
			       "elapsed time [ms]",
			       true);
    }
    
    
    public static void main(String [] args)
    {
	pushBenchmark();
    }
}
