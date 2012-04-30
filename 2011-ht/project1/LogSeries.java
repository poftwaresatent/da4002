import java.util.LinkedList;

/**
   A series of log entries, with utilities for measuring time.
*/
public class LogSeries
{
    private long tStart, tStop, mCount;
    private double mSum;
    public String title;
    public LinkedList<LogEntry> entries;
    
    public LogSeries(String _title)
    {
	title = _title;
	entries = new LinkedList<LogEntry>();
    }
    
    /**
       Starts a single time measurement.
    */
    public void startSingle()
    {
	tStart = System.currentTimeMillis();
    }
    
    /**
       Stops a single time measurement, and then creates an entry with
       the given xData paired with the time elapsed since startSingle
       was called (in milliseconds).
    */
    public long stopSingle(String xData)
    {
	tStop = System.currentTimeMillis();
	long dt = tStop - tStart;
	entries.add(new LogEntry(xData, "" + dt));
	return dt;
    }
    
    /**
       Initialize the counters for taking several measurements and
       storing the average.
    */
    public void initAverage()
    {
	mCount = 0;
	mSum = 0;
    }
    
    /**
       Start a time measurement which is part of a series to determine
       an average.
    */
    public void startAverage()
    {
	tStart = System.currentTimeMillis();
    }
    
    /**
       Stop a time measurement which is part of a series to determine
       an average. Returns the time delay since the most recent call
       to startAverage (in milliseconds).
    */
    public long stopAverage()
    {
	tStop = System.currentTimeMillis();
	long dt = tStop - tStart;
	++mCount;
	mSum += dt;
	return dt;
    }
    
    /**
       Finalize the average measurement, by storing the end result as
       a log entry. The average time delay (in milliseconds) is
       returned.
    */
    public double finalizeAverage(String xData)
    {
	double dt = mSum / mCount;
	entries.add(new LogEntry(xData, "" + dt));
	return dt;
    }
    
}
