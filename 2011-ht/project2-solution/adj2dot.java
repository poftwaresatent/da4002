public class adj2dot {
    public static void main(String[] args) {
	if (0 == args.length) {
	    System.err.println("filename expected");
	    System.exit(42);
	}
	Graph gg = new Graph();
	if ( ! gg.load(args[0], false)) {
	    System.err.println("failed to load adjacency list from " + args[0]);
	}
	gg.dotPrint(args[0]);
    }
}
