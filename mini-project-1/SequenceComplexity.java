class StringListNode
{
    public String data;
    public StringListNode next;
    
    public StringListNode(String _data)
    {
	data = _data;
    }
}


class StringList
{
    public StringListNode head;
    
    public void insertFront(String data)
    {
	StringListNode node = new StringListNode(data);
	node.next = head;
	head = node;
    }
    
    public void insertAfter(StringListNode position, String data)
    {
	StringListNode node = new StringListNode(data);
	node.next = position.next;
	position.next = node;
    }
    
    public String getFront()
    {
	// optional error checking:
	// if (null == head) { ... }
	return head.data;
    }
    
    public void removeFront()
    {
	// optional error checking:
	// if (null == head) { return false; }
	head = head.next;
    }
    
    public void removeAfter(StringListNode position)
    {
	// optional error checking:
	// if (null == position.next) { return false; }
	position.next = position.next.next;
    }
    
    public boolean isEmpty()
    {
	return null == head;
    }
    
    public void print(String prefix)
    {
	for (StringListNode current = head; null != current; current = current.next) {
	    System.out.println(prefix + current.data);
	}
    }
}


class StringListIterator
{
    public StringListNode current;
    
    public StringListIterator(StringList list)
    {
	current = list.head;
    }
    
    public boolean isFinished()
    {
	return null == current;
    }
    
    public void advance()
    {
	// optional error checking:
	// if (null != current) { ... }
	current = current.next;
    }
    
    public String getData()
    {
	// optional error checking:
	// if (null != current) { ... }
	return current.data;
    }
}


class StringVector
{
    public String [] data;
    public int size;
    
    public StringVector(int initialCapacity)
    {
	data = new String [initialCapacity];
	size = 0;
    }
    
    public void grow()
    {
	String [] bigger = new String [2 * data.length];
	for (int ii = 0; ii < size; ++ii) {
	    bigger[ii] = data[ii];
	}
	data = bigger;
    }
    
    public void insertFront(String value)
    {
	if (size >= data.length) {
	    grow();
	}
	for (int ii = 0, jj = 1; ii < size; ++ii, ++jj) {
	    data[jj] = data[ii];
	}
	data[0] = value;
	++size;
    }
    
    public void insertRear(String value)
    {
	if (size >= data.length) {
	    grow();
	}
	data[size++] = value;
    }
    
    public void print(String prefix)
    {
	for (int ii = 0; ii < size; ++ii) {
	    System.out.println(prefix + data[ii]);
	}
    }
    
}


class LogEntry
{
    public String xData, yData;
    
    public LogEntry(String _xData, String _yData)
    {
	xData = _xData;
	yData = _yData;
    }
}

    
class LogColumn
{
    public long tStart, tStop;
    public String title;
    public java.util.LinkedList<LogEntry> log;
    
    public LogColumn(String _title)
    {
	title = _title;
	log = new java.util.LinkedList<LogEntry>();
    }
    
    public void start()
    {
	tStart = System.currentTimeMillis();
    }
    
    public void stop(String xData)
    {
	tStop = System.currentTimeMillis();
	log.add(new LogEntry(xData, "" + (tStop - tStart)));
    }
}


class LogBook
{
    public String description;
    public java.util.LinkedList<LogColumn> columns;

    public LogBook(String _description)
    {
	description = _description;
	columns = new java.util.LinkedList<LogColumn>();
    }
    
    public LogColumn addColumn(String title)
    {
	LogColumn col = new LogColumn(title);
	columns.add(col);
	return col;
    }
    
    public void print()
    {
	java.util.LinkedList<java.util.Iterator<LogEntry>> iterators
	    = new java.util.LinkedList<java.util.Iterator<LogEntry>>();
	
	System.out.println("# log:");
	System.out.println("#   " + description);
	System.out.println("# columns:");
	for (LogColumn col : columns) {
	    System.out.println("#   " + col.title);
	    iterators.add(col.log.iterator());
	}
	
	outer:
	while (true) {
	    for (java.util.Iterator<LogEntry> it : iterators) {
		if ( ! it.hasNext()) {
		    break outer;
		}
		LogEntry entry = it.next();
		System.out.print(entry.xData + "  " + entry.yData + "    ");
	    }
	    System.out.println();
	}
    }
}


public class SequenceComplexity
{
    public static void listDemo(boolean verbose)
    {
	StringList list = new StringList();
	
	if (verbose) {
	    System.out.println("Inserting three items at the front.");
	}
	
	list.insertFront("blah one");
	list.insertFront("blah two");
	list.insertFront("blah three");
	
	if (verbose) {
	    System.out.println("  Result:");
	    list.print("  - ");
	    System.out.println();
	    System.out.println("Inserting three items after the head.");
	}
	
	list.insertAfter(list.head, "more blah one");
	list.insertAfter(list.head, "more blah two");
	list.insertAfter(list.head, "more blah three");

	if (verbose) {
	    System.out.println("  Result:");
	    list.print("  - ");
	    System.out.println();
	    System.out.println("Removing front '" + list.getFront() + "'");
	}
	
	list.removeFront();
	if (verbose) {
	    System.out.println("Removing front '" + list.getFront() + "'");
	}
	list.removeFront();
	if (verbose) {
	    System.out.println("Removing front '" + list.getFront() + "'");
	}
	list.removeFront();
	
	if (verbose) {
	    System.out.println("  Result:");
	    list.print("  - ");
	    System.out.println();
	    System.out.println("Removing twice after the head.");
	}
	
	list.removeAfter(list.head);
	list.removeAfter(list.head);
	if (verbose) {
	    System.out.println("  Result:");
	    list.print("  - ");
	}
    }
    
    
    public static void vectorDemo(boolean verbose)
    {
	StringVector vector = new StringVector(256);
	
	if (verbose) {
	    System.out.println("Inserting three items at the front.");
	}
	
	vector.insertFront("blah one");
	vector.insertFront("blah two");
	vector.insertFront("blah three");
	
	if (verbose) {
	    System.out.println("  Result:");
	    vector.print("  - ");
	    System.out.println();
	    ////	    System.out.println("Inserting three items after the head.");
	}
    }
    
    
    public static void demoBenchmark()
    {
	LogBook demoLog = new LogBook("running demo with or without printing");
	
	LogColumn col = demoLog.addColumn("verbose");
	for (int ii = 1; 3 >= ii; ++ii) {
	    col.start();
	    for (int jj = 0; ii > jj; ++jj) {
		listDemo(true);
	    }
	    col.stop("" + ii);
	}
	
	col = demoLog.addColumn("silent");
	for (int ii = 1; 3 >= ii; ++ii) {
	    col.start();
	    for (int jj = 0; ii > jj; ++jj) {
		listDemo(false);
	    }
	    col.stop("" + ii);
	}
	
	demoLog.print();
    }
    
    
    public static void insertFrontBenchmark()
    {
	LogBook insertFrontLog = new LogBook("repeated insertion at the front");
	LogColumn stringListColumn = insertFrontLog.addColumn("StringList");
	LogColumn stringVectorColumn = insertFrontLog.addColumn("StringVector");
	
	String value = "whatever";
	
	for (int ii = 1024; 200000 >= ii; ii *= 2) {
	    System.out.println("inserting " + ii + " ...");
	    StringList list = new StringList();
	    StringVector vector = new StringVector(256);
	    try {
		
		stringListColumn.start();
		for (int jj = 0; jj < ii; ++jj) {
		    list.insertFront(value);
		}
		stringListColumn.stop("" + ii);
		
		stringVectorColumn.start();
		for (int jj = 0; jj < ii; ++jj) {
		    vector.insertFront(value);
		}
		stringVectorColumn.stop("" + ii);
		
	    }
	    catch (OutOfMemoryError ee) {
		System.out.println("OUT OF MEMORY: aborting benchmark");
		break;
	    }
	}
	
	insertFrontLog.print();
    }
    
    
    public static void main(String [] args)
    {
	vectorDemo(true);
	insertFrontBenchmark();
    }
}
