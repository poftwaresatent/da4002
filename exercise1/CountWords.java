import java.util.*; 
import java.io.*; 

/** Count the words given from standard input. The purpose is to
  * illustrate some aspects of the collections framework. If you want
  * to use this to count the words in an ascii file, just give the
  * contents of the file to the program: 
  * <br><tt>java CountWords &lt filename</tt>
  * <p>
  * You will notice that we use an instance of the class
  * <tt>StringTokenizer</tt>. When creating an instance of this class
  * one provides a <tt>String s</tt> to be <i>tokenized</i> (split
  * into substrings) and a <tt>String separators</tt> to indicate at
  * what points <tt>s</tt> should be cut. In order to obtain the
  * different pieces of <tt>s</tt> we use the method <tt>String
  * nextToken()</tt>. There are more tokens as long as <tt>boolean
  * hasMoreTokens()</tt> returns <tt>true</tt>.
  */

public class CountWords
{
    
    static public void main(String[] args) {
	
	// an input stream with method <tt>String readLine()</tt>.
	BufferedReader in = new BufferedReader(new InputStreamReader(System.in)); 
	
	// characters that separaate words:
	String delim = " \t\n.,:;?!-/()[]\"\'";
	
	// we will read line by line:
	String line; 
	
	// to count words in the input:
	int count = 0; 
	
	try {
	    while ((line = in.readLine()) != null) {
		StringTokenizer st = new StringTokenizer(line, delim); 
		while (st.hasMoreTokens()) {
		    count++; 
		    st.nextToken();
		}
	    } 
	}
	catch (IOException e) {
	    // do nothing: the IOException simply signals the end of
	    // input
	}
	
	System.out.println("Total number of words: " + count); 
    }
}
