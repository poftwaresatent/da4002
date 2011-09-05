import java.util.LinkedList;

/**
   A series of log entries, with utilities for measuring time.
*/
public class LogSeries
{
    private long tStart, tStop;
    public String title;
    public LinkedList<LogEntry> entries;
    
    public LogSeries(String _title)
    {
	title = _title;
	entries = new LinkedList<LogEntry>();
    }
    
    /**
       Starts the time measurement.
    */
    public void start()
    {
	tStart = System.currentTimeMillis();
    }
    
    /**
       Stops the time measurement, and then creates an entry with the
       given xData paired with the time elapsed since start was called
       (in milliseconds).
    */
    public void stop(String xData)
    {
	tStop = System.currentTimeMillis();
	entries.add(new LogEntry(xData, "" + (tStop - tStart)));
    }
}
