import java.io.*;

public class ex43
{
    static public void main(String[] args)
    {
	final int sizeMin = 50;
	final int sizeMax = 3000;
	final double sizeFactor = 1.5;
	final String separator = "\t";
	final String filename = "log.data";
	try {
	    FileWriter logFile = new FileWriter(filename);
	
	    System.out.println();
	    System.out.println("----------------------------------------------");
	    System.out.println("N\ttime");
	    for (int nn = sizeMin; nn < sizeMax; nn = (int) Math.round(nn * sizeFactor)) {
		System.out.print(nn);
		logFile.write("" + nn);
		
		long tStart = System.currentTimeMillis();
		// fragment 9
		//   note: ii and jj start at 1, and the kk loop is not always executed
		for (int ii = 1; ii <= nn; ++ii) {
		    for (int jj = 1; jj <= ii * ii; ++jj) {
			if (0 == jj % ii) {
			    for (int kk = 0; kk < jj; ++kk) {
				int blah = 10;
				blah *= 10;
			    }
			}
		    }
		}
		long tEnd = System.currentTimeMillis();
		long dt = tEnd - tStart;
		System.out.print("\t\t" + dt);
		logFile.write(separator + dt);
		
		System.out.println();
		logFile.write("\n");
	    }
	    
	    logFile.close();
	    
	    System.out.println();
	    System.out.println("wrote data to file `" + filename + "'");
	    System.out.println();
	    System.out.println("suggestions for plotting it in gnuplot:");
	    System.out.println("  set key top left");
	    System.out.println("  plot 'log.data' u 1:2            w lp t 'fragment 9'");
	    System.out.println("  plot 'log.data' u 1:($2/log($1)) w lp t 'fragment 9 / log N'");
	    System.out.println("  plot 'log.data' u 1:($2/$1)      w lp t 'fragment 9 / N'");
	    System.out.println("  plot 'log.data' u 1:($2/($1**2)) w lp t 'fragment 9 / N squared'");
	    
	}
	catch (IOException ee) {
	    System.err.println("Failure due to some input-output problem:\n  " + ee);
	    System.exit(42);
	}
    }
}
