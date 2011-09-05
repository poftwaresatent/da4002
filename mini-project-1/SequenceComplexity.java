public class SequenceComplexity
{
    public static void insertFrontBenchmark()
    {
	LogBook insertFrontLog = new LogBook("repeated insertion at the front");
	LogSeries stringListSeries = insertFrontLog.addSeries("SimpleStringList");
	LogSeries stringVectorSeries = insertFrontLog.addSeries("StringVector");
	
	String value = "whatever";
	
	for (int ii = 1024; 200000 >= ii; ii *= 2) {
	    System.out.println("inserting " + ii + " ...");
	    SimpleStringList list = new SimpleStringList();
	    StringVector vector = new StringVector(256);
	    try {
		
		stringListSeries.start();
		for (int jj = 0; jj < ii; ++jj) {
		    list.insertFront(value);
		}
		stringListSeries.stop("" + ii);
		
		stringVectorSeries.start();
		for (int jj = 0; jj < ii; ++jj) {
		    vector.insertFront(value);
		}
		stringVectorSeries.stop("" + ii);
		
	    }
	    catch (OutOfMemoryError ee) {
		System.out.println("OUT OF MEMORY: aborting benchmark");
		break;
	    }
	}
	
	insertFrontLog.printGnuplotData();
	insertFrontLog.printGnuplotScript("foo.log",
					  "number of insertions",
					  "elapsed time [ms]",
					  true);
    }
    
    
    public static void main(String [] args)
    {
	insertFrontBenchmark();
    }
}
