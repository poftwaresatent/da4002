public class Fragment9
{
    static public void main(String[] args)
    {
	final long sizeMin = 10;
	final long sizeMax = 500;
	final double sizeFactor = 1.2;
	
	System.out.println();
	System.out.println("number of additions in fragment 9");
	System.out.println("---------------------------------");
	System.out.println("N\tcount\tcount/N^3\tcount/N^4\tcount/N^5");
	for (long nn = sizeMin; nn < sizeMax; nn = (long) Math.round(nn * sizeFactor)) {
	    System.out.print(nn);
	    
	    long count = 0;
	    for (long ii = 1; ii <= nn; ++ii) {
		for (long jj = 1; jj <= ii * ii; ++jj) {
		    if (0 == jj % ii) {
			for (long kk = 0; kk < jj; ++kk) {
			    ++count;
			}
		    }
		}
	    }
	    System.out.println("\t" + count
			       + "\t" + count/((double)nn*nn*nn)
			       + "\t" + count/((double)nn*nn*nn*nn)
			       + "\t" + count/((double)nn*nn*nn*nn*nn));
	}
    }
}
