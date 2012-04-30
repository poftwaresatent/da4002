import java.util.*;
import java.io.*;

/** Count the words given from standard input. The purpose is to
  * illustrate some aspects of the collections framework. If you want
  * to use this to count the words in an ascii file, just give the
  * contents of the file to the program: 
  *
  * <tt>java CountWords &lt filename</tt>
  */

public class CountWords
{
    static public void main(String[] args)
    {
	BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
	String line;
	int count = 0;
	
	// A tree set allows us to count unique words while storing
	// them in alphabetical order, solving two problems with one
	// container.
	java.util.TreeSet<String> ts = new java.util.TreeSet<String>();
	
	try {
	    while ((line = in.readLine()) != null) {
		StringTokenizer st = new StringTokenizer(line, " \t!=\"&().,*/+;:<>{}\\[]");
		while (st.hasMoreTokens()) {
		    count++; 
		    ts.add(st.nextToken());
		}
	    } 
	}
	catch (IOException e) {
	    // do nothing: the IOException simply signals the end of
	    // input
	}
	
	System.out.println("Total number of words: " + count);
	System.out.println("Number of unique words: " + ts.size());
	System.out.println("Alphabetical list of unique words:");
	for (String word : ts) {
	    System.out.println("  " + word);
	}
    }
}
