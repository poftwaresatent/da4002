public class Permute {
    static public void print(String head, String tail) {
	if (tail.length() <= 1) {
	    System.out.println(head + tail);
	}
	else {
	    for (int ii = 0; ii < tail.length(); ++ii) {
		String rHead = head + tail.charAt(ii);
		StringBuilder rTail = new StringBuilder();
		for (int jj = 0; jj < tail.length(); ++jj) {
		    if (ii != jj) {
			rTail.append(tail.charAt(jj));
		    }
		}
		print(rHead, rTail.toString());
	    }
	}
    }
    
    static public void main(String[] args) {
	print("", args[0]);
    }
}
