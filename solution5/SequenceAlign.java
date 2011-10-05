import java.util.HashSet;
import java.util.Stack;


/**
   Interface for determing the cost of deleting, inserting, or changing a character.
*/
interface CostFunction {
    public boolean valid(char aa);
    public int gapCost();
    public int matchCost(char aa, char bb);
}


/**
   Utility for storing the optimal value of a cell in the propagation
   table, along with the backpointers. As it is possible to have up to
   three backpointers per cell, but they always come from a
   predetermined set of neighbors, we simply store the backpointers as
   flags.
*/
class Cell
{
    public static final int MATCH =  0x1;
    public static final int INSERT = 0x2;
    public static final int DELETE = 0x4;
    
    public Cell(int _value) {
	bpflag = 0;
	value = _value;
    }
    
    public int bpflag, value;
}


class Pair<TT>
{
    public TT one, two;
    public Pair(TT _one, TT _two) {
	one = _one;
	two = _two;
    }
}


/**
   An CostFunction which implements the cost rules used during the lecture.
*/
class DefaultCostFunction
    implements CostFunction
{
    private HashSet<Character> vowels;
    private HashSet<Character> consonants;
    
    
    public DefaultCostFunction()
    {
	vowels = new HashSet<Character>();
	for (char aa : "AEIOUY".toCharArray()) {
	    vowels.add(aa);
	}
	consonants = new HashSet<Character>();
	for (char aa : "BCDFGHJKLMNPQRSTVWXZ".toCharArray()) {
	    consonants.add(aa);
	}
    }
    
    
    public boolean valid(char aa)
    {
	aa = Character.toUpperCase(aa);
	return vowels.contains(aa) || consonants.contains(aa);
    }
    
    
    public int gapCost() {
	return -5;
    }
    
    
    public int matchCost(char aa, char bb) {
	aa = Character.toUpperCase(aa);
	bb = Character.toUpperCase(bb);
	if (aa == bb) {
	    return 10;
	}
	if (vowels.contains(aa)) {
	    if (vowels.contains(bb)) {
		return -2;
	    }
	    return -10;
	}
	if (consonants.contains(bb)) {
	    return -4;
	}
	return -10;
    }
}


/**
   Implementation of the Needleman-Wunsch algorithm. It also contains
   supporting data structures and some utility methods, e.g. for
   printing the table on the console.
*/
public class SequenceAlign
{
    private CostFunction cf;
    private String aa, bb;
    public Cell[][] table;
    public int maxValue, minValue;
    
    
    public SequenceAlign(CostFunction _cf)
    {
	cf = _cf;
    }
    
    
    public boolean valid(String aa)
    {
	if (0 == aa.length()) {
	    System.err.println("invalid: empty string");
	    return false;
	}
	for (int ii = 0; ii < aa.length(); ++ii) {
	    if ( ! cf.valid(aa.charAt(ii))) {
		System.err.println("invalid character '" + aa.charAt(ii) + "' at position " + ii);
		return false;
	    }
	}
	return true;
    }
    
    
    public void init(String _aa, String _bb)
    {
	aa = "_" + _aa;
	bb = "_" + _bb;
	table = new Cell[bb.length()][];
	for (int ii = 0; ii < bb.length(); ++ii) {
	    table[ii] = new Cell[aa.length()];
	    for (int jj = 0; jj < aa.length(); ++jj) {
		table[0][jj] = new Cell(jj * cf.gapCost());
		if (0 != jj) {
		    table[0][jj].bpflag = Cell.INSERT;
		}
	    }
	}
	for (int ii = 1; ii < bb.length(); ++ii) {
	    table[ii][0] = new Cell(ii * cf.gapCost());
	    table[ii][0].bpflag = Cell.DELETE;
	}
	maxValue = Integer.MIN_VALUE;
	minValue = Integer.MAX_VALUE;
    }
    
    
    public void propagate()
    {
	for (int ii = 1; ii < bb.length(); ++ii) {
	    for (int jj = 1; jj < aa.length(); ++jj) {
		
		final int matchVal
		    = table[ii-1][jj-1].value + cf.matchCost(bb.charAt(ii), aa.charAt(jj));
		final int deleteVal
		    = table[ii-1][jj].value + cf.gapCost();
		final int insertVal
		    = table[ii][jj-1].value + cf.gapCost();
		
		int optVal = matchVal;
		if (deleteVal > optVal) {
		    optVal = deleteVal;
		}
		if (insertVal > optVal) {
		    optVal = insertVal;
		}
		
		table[ii][jj] = new Cell(optVal);
		if (matchVal == optVal) {
		    table[ii][jj].bpflag |= Cell.MATCH;
		}
		if (deleteVal == optVal) {
		    table[ii][jj].bpflag |= Cell.DELETE;
		}
		if (insertVal == optVal) {
		    table[ii][jj].bpflag |= Cell.INSERT;
		}
		
		if (optVal > maxValue) {
		    maxValue = optVal;
		}
		if (optVal < minValue) {
		    minValue = optVal;
		}
	    }
	}
    }
    
    
    public void print()
    {
	int fwmax = 1;
	if (0 != maxValue) {
	    fwmax = (int) Math.ceil(Math.log10(Math.abs(maxValue)));
	}
	int fwmin = 1;
	if (0 != minValue) {
	    fwmin = (int) Math.ceil(Math.log10(Math.abs(minValue)));
	}
	final int width = Math.max(fwmin, fwmax) + 1;
	String numfmt = "%c%+" + width + "d";
	String chrfmt = "%c%" + width + "c";
	
	System.out.print(" ");
	for (int ii = 0; ii < aa.length(); ++ii) {
	    System.out.format(chrfmt, ' ', aa.charAt(ii));
	}
	System.out.println();
	
	for (int ii = 0; ii < bb.length(); ++ii) {
	    System.out.print(' ');
	    for (int jj = 0; jj < aa.length(); ++jj) {
		System.out.format(chrfmt,
				  0 != (table[ii][jj].bpflag & Cell.MATCH) ? '\\' : ' ',
				  0 != (table[ii][jj].bpflag & Cell.DELETE) ? '|' : ' ');
	    }
	    System.out.println();
	    System.out.print(bb.charAt(ii));
	    for (int jj = 0; jj < aa.length(); ++jj) {
		System.out.format(numfmt,
				  0 != (table[ii][jj].bpflag & Cell.INSERT) ? '_' : ' ',
				  table[ii][jj].value);
	    }
	    System.out.println();
	}
    }
    
    
    public Pair<String> backtrace(boolean debug)
	throws RuntimeException
    {
	if (debug) {
	    System.out.println("backtrace:");
	}
	int jj = aa.length() - 1;
	int ii = bb.length() - 1;
	StringBuilder sa = new StringBuilder();
	StringBuilder sb = new StringBuilder();
	do {
	    if (debug) {
		System.out.print("  [" + ii + "][" + jj + "]");
	    }
	    
	    if (ii < 0 || jj < 0) {
		throw new RuntimeException("BUG: invalid index [" + ii + "][" + jj + "]");
	    }
	    if (0 != (table[ii][jj].bpflag & Cell.MATCH)) {
		if (debug) {
		    System.out.println(" " + aa.charAt(jj) + " " + bb.charAt(ii));
		}
		sa.append(aa.charAt(jj--));
		sb.append(bb.charAt(ii--));
	    }
	    else if (0 != (table[ii][jj].bpflag & Cell.INSERT)) {
		if (debug) {
		    System.out.println(" " + aa.charAt(jj) + " _");
		}
		sa.append(aa.charAt(jj--));
		sb.append('_');
	    }
	    else if (0 != (table[ii][jj].bpflag & Cell.DELETE)) {
		if (debug) {
		    System.out.println(" _ " + bb.charAt(ii));
		}
		sa.append('_');
		sb.append(bb.charAt(ii--));
	    }
	    else {
		throw new RuntimeException("BUG: invalid bpflag at table[" + ii + "][" + jj + "]");
	    }
	} while ((ii >= 1 && jj >= 0) || (ii >= 0 && jj >= 1));
	
	return new Pair<String>(sa.reverse().toString(),
				sb.reverse().toString());
    }
    
    
    public static void main (String[] args)
    {
	if (args.length < 2) {
	    System.err.println("provide two strings on the command line please");
	    System.exit(42);
	}
	
	SequenceAlign sa = new SequenceAlign(new DefaultCostFunction());
	if ( ! sa.valid(args[0]) || ! sa.valid(args[1])) {
	    System.exit(17);
	}
	sa.init(args[0], args[1]);
	sa.propagate();
	sa.print();
	
	try {
	    Pair<String> match = sa.backtrace(true);
	    System.out.println();
	    System.out.println(match.one);
	    System.out.println(match.two);
	}
	catch (RuntimeException ee) {
	    System.err.println(ee);
	    System.exit(42);
	}
    }
}
