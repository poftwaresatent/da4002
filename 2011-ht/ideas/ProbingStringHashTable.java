import java.io.*;
import java.util.*;

public class ProbingStringHashTable
{
    int[] dataHash;		// -2 means unused, -1 means deleted
    String[] dataValue;
    int size;
    int maxOffset;
    
    public ProbingStringHashTable(int capacity)
    {
	if (capacity < 1) {
	    capacity = 1;
	}
	dataValue = new String[capacity];
	dataHash = new int[capacity];
	for (int ii = 0; ii < capacity; ++ii) {
	    dataHash[ii] = -2;
	}
	size = 0;
	maxOffset = 1;
    }
    
    private int computeHash(String value)
    {
	int hash = 0;
	for (int ii = 0; ii < value.length(); ++ii) {
	    hash = 31 * hash + value.charAt(ii);
	}
	return Math.abs(hash % dataHash.length);
    }
    
    public boolean insert(String value)
    {
	if (size == dataValue.length) {
	    return false;
	}
	int hash = computeHash(value);
	int probe = hash;
	int offset = 1;
	while (0 <= dataHash[probe]) { // find first deleted or unused entry
	    if (dataHash[probe] == hash && dataValue[probe].equals(value)) {
		return true;	// value is already in the table
	    }
	    probe = (probe + offset) % dataHash.length;
	    offset += 2;
	}
	dataHash[probe] = hash;
	dataValue[probe] = value;
	++size;
	maxOffset += 2;
	return true;
    }
    
    public int find(String value)
    {
	if (0 == size) {
	    return -1;
	}
	int hash = computeHash(value);
	int probe = hash;
	int offset = 1;
	while (offset <= maxOffset && -1 <= dataHash[probe]) {
	    // keep looking beyond deleted entries
	    if (dataHash[probe] == hash && dataValue[probe].equals(value)) {
		return probe;
	    }
	    probe = (probe + offset) % dataHash.length;
	    offset += 2;
	}
	return -1;
    }
    
    public boolean remove(String value)
    {
	int index = find(value);
	if (0 > index) {
	    return false;
	}
	dataHash[index] = -1;
	dataValue[index] = null;
	--size;
	maxOffset -= 2;
	return true;
    }
    
    public int size()
    {
	return size;
    }

    public int capacity()
    {
	return dataHash.length;
    }
    
    public void print(String title, String prefix)
    {
	if (0 != title.length()) {
	    System.out.println(title);
	}
	for (int ii = 0; ii < dataHash.length; ++ii) {
	    System.out.print(prefix + "[" + ii + "]");
	    if (-2 == dataHash[ii]) {
		System.out.println(" unused");
	    }
	    else if (-1 == dataHash[ii]) {
		System.out.println(" deleted");
	    }
	    else {
		System.out.println(" " + dataHash[ii] + ": " + dataValue[ii]);
	    }
	}
    }
    
    public void printCompact(String title, String prefix)
    {
	if (0 != title.length()) {
	    System.out.println(title);
	}
	for (int ii = 0; ii < dataHash.length; ++ii) {
	    if (0 <= dataHash[ii]) {
		System.out.println(prefix + dataValue[ii]);
	    }
	}
    }
    
    static public void demo()
    {
	ProbingStringHashTable ht = new ProbingStringHashTable(5);
	ht.print("freshly baked", "  ");

	System.out.println();
	ht.insert("hello");
	ht.insert("world");
	ht.print("after hello world", "  ");
	System.out.println("find hello: " + ht.find("hello"));
	System.out.println("find world: " + ht.find("world"));
	System.out.println("find byebye: " + ht.find("byebye"));
	
	System.out.println();
	ht.remove("world");
	ht.print("after world removal", "  ");
	System.out.println("find world: " + ht.find("world"));
	
	System.out.println();
	ht.insert("byebye");
	ht.insert("jupiter");
	ht.print("after byebye jupiter", "  ");
	System.out.println("find hello: " + ht.find("hello"));
	System.out.println("find world: " + ht.find("world"));
	System.out.println("find byebye: " + ht.find("byebye"));
	System.out.println("find jupiter: " + ht.find("jupiter"));
	
	System.out.println();
	ht.insert("duplicate");
	ht.insert("duplicate");
	ht.insert("duplicate");
	ht.insert("duplicate");
	ht.print("after 4 duplicates", "  ");
    }
    
    static public void main(String[] args)
    {
	// Yes, it's wasteful to to create two new objects at the risk
	// of just throwing them away again. But Java is not able to
	// figure out that the "in" variable is always initialized by
	// the time we try to read from it... and flags it as an
	// error. Really annoying.
	//
	BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
	
	if (0 < args.length) {
	    try{
		in = new BufferedReader(new FileReader(args[0]));
	    }
	    catch (FileNotFoundException ee) {
		System.out.println(args[0] + ": no such file");
		System.exit(42);
	    }
	}
	
	ProbingStringHashTable ht = new ProbingStringHashTable(100);
	String line;
	outer:
	try {
	    while (null != (line = in.readLine())) {
		StringTokenizer st = new StringTokenizer(line);
		while (st.hasMoreTokens()) {
		    if ( ! ht.insert(st.nextToken())) {
			System.out.println("OOPS: more input than capacity, aborting");
			break outer;
		    }
		}
	    }
	}
	catch (IOException ee) {
	}
	ht.printCompact("", "");
    }
}
