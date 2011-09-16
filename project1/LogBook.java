import java.util.*;
import java.io.*;

/**
   Utility for collecting time measurements across various setups. The
   log is subdivided into series, which help to collect measurements
   of a given setup while varying one parameter. Each series consists
   of entries, each having one data point (for the X- and for the
   Y-axes).
*/
public class LogBook
{
    private String description;
    private String xLabel;
    private String yLabel;
    private LinkedList<LogSeries> series;

    public LogBook(String _description,
		   String _xLabel,
		   String _yLabel)
    {
	description = _description;
	xLabel = _xLabel;
	yLabel = _yLabel;
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
    public void writeData(Writer ww)
	throws IOException
    {
	LinkedList<Iterator<LogEntry>> iterators
	    = new LinkedList<Iterator<LogEntry>>();
	
	ww.write("##############################\n");
	ww.write("# log description:\n");
	ww.write("#   " + description + "\n");
	ww.write("#\n");
	ww.write("# series titles (two data columns per series):\n");
	for (LogSeries ser : series) {
	    ww.write("#   - " + ser.title + "\n");
	    iterators.add(ser.entries.iterator());
	}
	ww.write("#\n");
	
	outer:
	while (true) {
	    for (Iterator<LogEntry> it : iterators) {
		if ( ! it.hasNext()) {
		    ww.write("\n");
		    break outer;
		}
		LogEntry entry = it.next();
		ww.write(entry.xData + "  " + entry.yData + "    ");
	    }
	    ww.write("\n");
	}
    }
    
    public void writeDataFile(String baseName)
	throws IOException
    {
	FileWriter fw = new FileWriter(baseName + ".data");
	writeData(fw);
	fw.close();
    }
    
    public void printData()
    {
	try {
	    FileWriter fw = new FileWriter("/dev/stdout");
	    writeData(fw);
	    fw.close();
	}
	catch (IOException ee) {
	    System.err.println("exception in printData():\n  " + ee);
	}
    }
    
    public String createDataFile()
	throws IOException
    {
	String baseName = "log-" + System.currentTimeMillis();
	writeDataFile(baseName);
	return baseName;
    }
    
    public void writePlotScript(Writer ww,
				String baseName,
				boolean separatePlots)
	throws IOException
    {
	ww.write("set title '" + description + "'\n");
	ww.write("set xlabel '" + xLabel + "'\n");
	ww.write("set ylabel '" + yLabel + "'\n");
	if (separatePlots) {
	    int ii = 1;
	    for (LogSeries ser : series) {
		ww.write("plot '" + baseName + ".data' u "
			 + (ii++) + ":" + (ii++) + " w l t '"
			 + ser.title + "'\n");
	    }
	}
	else {
	    int ii = 1;
	    for (LogSeries ser : series) {
		if (1 == ii) {
		    ww.write("plot '" + baseName + ".data' u "
			     + (ii++) + ":" + (ii++) + " w l t '"
			     + ser.title + "'");
		}
		else {
		    ww.write(", '" + baseName + ".data' u "
			     + (ii++) + ":" + (ii++) + " w l t '"
			     + ser.title + "'");
		}
	    }
	    ww.write("\n");
	}
    }
    
    public void writePlotScriptFile(String baseName,
				    boolean separatePlots)
	throws IOException
    {
	FileWriter fw = new FileWriter(baseName + ".plot");
	writePlotScript(fw, baseName, separatePlots);
	fw.close();
    }
    
    public void printPlotScript(String baseName, boolean separatePlots)
    {
	try {
	    FileWriter fw = new FileWriter("/dev/stdout");
	    writePlotScript(fw, baseName, separatePlots);
	    fw.close();
	}
	catch (IOException ee) {
	    System.err.println("exception in printPlotScript():\n  " + ee);
	}
    }
    
    public String createFiles()
    {
	String baseName = "";
	try {
	    baseName = createDataFile();
	    writePlotScriptFile(baseName, false);
	}
	catch (IOException ee) {
	    System.err.println("failed to create files:\n  " + ee);
	    return "";
	}
	System.out.println("created data and plot files with base name `" + baseName + "'");
	System.out.println("  to see the plots, run `gnuplot -p " + baseName + ".plot'");
	return baseName;
    }
    
    /**
       Runs a little demo that measures the time it takes to run a for
       loop.
    */
    public static void main(String [] args)
    {
	LogBook log = new LogBook("delay of for-loops", "number of iterations", "elapsed time [ms]");
	
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
	
	log.printData();
	log.printPlotScript("none", true);
	
	log.createFiles(); 
    }
    
}
