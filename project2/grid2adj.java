public class grid2adj {
    public static void main(String[] args) {
	if (0 == args.length) {
	    System.err.println("filename expected");
	    System.exit(42);
	}
	Graph gg = new Graph();
	if ( ! gg.loadGrid(args[0])) {
	    System.err.println("failed to load grid from " + args[0]);
	}
	gg.print();
    }
}
