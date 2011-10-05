import java.util.HashSet;


class Cell
{
    public static final int MERGE =  0x1;
    public static final int INSERT = 0x2;
    public static final int DELETE = 0x4;
    
    public Cell(int _value) {
	bpflag = 0;
	value = _value;
    }
    
    public int bpflag, value;
}


class CostFunction
{
    private HashSet<Character> vowels;
    private HashSet<Character> consonants;
    
    
    public CostFunction()
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
    
    
    public int mergeCost(char aa, char bb) {
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
	    }
	}
	for (int ii = 1; ii < bb.length(); ++ii) {
	    table[ii][0] = new Cell(ii * cf.gapCost());
	}
	maxValue = Integer.MIN_VALUE;
	minValue = Integer.MAX_VALUE;
    }
    
    
    public void propagate()
    {
	for (int ii = 1; ii < bb.length(); ++ii) {
	    for (int jj = 1; jj < aa.length(); ++jj) {
		
		final int mergeVal
		    = table[ii-1][jj-1].value + cf.mergeCost(bb.charAt(ii), aa.charAt(jj));
		final int deleteVal
		    = table[ii-1][jj].value + cf.gapCost();
		final int insertVal
		    = table[ii][jj-1].value + cf.gapCost();
		
		int optVal = mergeVal;
		if (deleteVal > optVal) {
		    optVal = deleteVal;
		}
		if (insertVal > optVal) {
		    optVal = insertVal;
		}
		
		table[ii][jj] = new Cell(optVal);
		if (mergeVal == optVal) {
		    table[ii][jj].bpflag |= Cell.MERGE;
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
	String numfmt = " %+" + width + "d";
	String charfmt = " %" + width + "c";
	
	System.out.print(" ");
	for (int ii = 0; ii < aa.length(); ++ii) {
	    System.out.format(charfmt, aa.charAt(ii));
	}
	System.out.println();

	for (int ii = 0; ii < bb.length(); ++ii) {
	    System.out.print(bb.charAt(ii));
	    for (int jj = 0; jj < aa.length(); ++jj) {
		System.out.format(numfmt, table[ii][jj].value);
	    }
	    System.out.println();
	}
    }
    
    
    public static void main (String[] args)
    {
	if (args.length < 2) {
	    System.err.println("provide two strings on the command line please");
	    System.exit(42);
	}
	
	SequenceAlign sa = new SequenceAlign(new CostFunction());
	if ( ! sa.valid(args[0]) || ! sa.valid(args[1])) {
	    System.exit(17);
	}
	sa.init(args[0], args[1]);
	sa.propagate();
	sa.print();
    }
}
