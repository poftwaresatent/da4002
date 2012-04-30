public class SpellCheck
{
    static private String[] dictionary = {
	"alpha",
	"bravo",
	"charlie",
	"delta",
	"echo",
	"foxtrot",
	"golf",
	"hotel",
	"india",
	"juliet",
	"kilo",
	"lima",
	"mike",
	"november",
	"oscar",
	"papa",
	"quebec",
	"romeo",
	"sierra",
	"tango",
	"uniform",
	"victor",
	"whiskey",
	"xray",
	"yankee",
	"zulu" };
    
    public static void main(String[] args)
    {
	SequenceAlign sa = new SequenceAlign(new DefaultCostFunction());
	for (int ii = 0; ii < args.length; ++ii) {
	    System.out.print(args[ii] + ": ");
	    if ( ! sa.valid(args[ii])) {
		System.out.println("INVALID INPUT");
		continue;
	    }
	    int maxscore = Integer.MIN_VALUE;
	    int maxindex = -1;
	    Pair<String> match = new Pair<String>("", "");
	    for (int jj = 0; jj < dictionary.length; ++jj) {
		sa.init(args[ii], dictionary[jj]);
		int score = sa.propagate();
		if (score > maxscore) {
		    maxscore = score;
		    maxindex = jj;
		    match = sa.backtrace(false);
		}
	    }
	    System.out.println(dictionary[maxindex] + " (score: " + maxscore + ")");
	    System.out.println("  " + match.one);
	    System.out.println("  " + match.two);
	}
    }
}
