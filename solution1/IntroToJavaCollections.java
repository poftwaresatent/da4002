public class IntroToJavaCollections
{
    public static void main(String[] args)
    {
	java.util.HashSet<String> hash = new java.util.HashSet<String>();
	java.util.TreeSet<String> tree = new java.util.TreeSet<String>();
	for (int ii = 0; ii < args.length; ++ii) {
	    hash.add(args[ii]);
	    tree.add(args[ii]);
	}
	System.out.println("Hash set storage order:");
	for (String entry : hash) {
	    System.out.println("  " + entry);
	}
	System.out.println("Tree set storage order:");
	for (String entry : tree) {
	    System.out.println("  " + entry);
	}
    }
}
