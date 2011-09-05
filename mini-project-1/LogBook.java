import java.util.LinkedList;
import java.util.Iterator;

/**
   Utility for collecting time measurements across various setups. The
   log is subdivided into series, which help to collect measurements
   of a given setup while varying one parameter. Each series consists
   of entries, each having one data point (for the X- and for the
   Y-axes).
*/
public class LogBook
{
    public String description;
    public LinkedList<LogSeries> series;

    public LogBook(String _description)
    {
	description = _description;
	series = new LinkedList<LogSeries>();
    }
    
    /**
       Create and register a measurement series, by giving it a title.
       The idea is to run various benchmarks with differing parameter,
       (that end up on the X-axis). Each time call LogSeries.start
       before the benchmark and LogSeries.stop afterward.
    */
    public LogSeries addSeries(String title)
    {
	LogSeries ser = new LogSeries(title);
	series.add(ser);
	return ser;
    }
    
    /**
       Print the accumulated measurement series, along with their
       descriptions, in a format usable by gnuplot.
    */
    public void printGnuplotData()
    {
	LinkedList<Iterator<LogEntry>> iterators
	    = new LinkedList<Iterator<LogEntry>>();
	
	System.out.println("##############################");
	System.out.println("# log description:");
	System.out.println("#   " + description);
	System.out.println("#");
	System.out.println("# series titles (two data columns per series):");
	for (LogSeries ser : series) {
	    System.out.println("#   - " + ser.title);
	    iterators.add(ser.entries.iterator());
	}
	System.out.println("#");
	
	outer:
	while (true) {
	    for (Iterator<LogEntry> it : iterators) {
		if ( ! it.hasNext()) {
		    System.out.println();
		    break outer;
		}
		LogEntry entry = it.next();
		System.out.print(entry.xData + "  " + entry.yData + "    ");
	    }
	    System.out.println();
	}
    }
    
    public void printGnuplotScript(String dataFilename,
				   String xLabel,
				   String yLabel,
				   boolean separatePlots)
    {
	System.out.println("set title '" + description + "'");
	System.out.println("set xlabel '" + xLabel + "'");
	System.out.println("set ylabel '" + yLabel + "'");
	if (separatePlots) {
	    int ii = 1;
	    for (LogSeries ser : series) {
		System.out.println("plot '" + dataFilename + "' u "
				   + (ii++) + ":" + (ii++) + " w l t '"
				   + ser.title + "'");
	    }
	}
	else {
	    int ii = 1;
	    for (LogSeries ser : series) {
		if (1 == ii) {
		    System.out.print("plot '" + dataFilename + "' u "
				     + (ii++) + ":" + (ii++) + " w l t '"
				     + ser.title + "'");
		}
		else {
		    System.out.print(", '" + dataFilename + "' u "
				     + (ii++) + ":" + (ii++) + " w l t '"
				     + ser.title + "'");
		}
	    }
	    System.out.println();
	}
    }
    
    /**
       Runs a little demo that measures the time it takes to run a for
       loop.
    */
    public static void main(String [] args)
    {
	LogBook log = new LogBook("delay of for-loops");
	
	LogSeries ser = log.addSeries("empty");
	for (int ii = 1024; 1000000 >= ii; ii *= 2) {
	    ser.start();
	    for (int jj = 0; ii > jj; ++jj) {
		/* nop */
	    }
	    ser.stop("" + ii);
	}
	
	ser = log.addSeries("simple string operations");
	for (int ii = 1024; 1000000 >= ii; ii *= 2) {
	    ser.start();
	    for (int jj = 0; ii > jj; ++jj) {
		String blah = "blah" + jj;
	    }
	    ser.stop("" + ii);
	}
	
	log.printGnuplotData();
    }
    
}
