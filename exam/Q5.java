class Q5 {
    public static void main(String[] args) {
	System.out.println("naive recursion:\n  " + GRec.gRec(Integer.parseInt(args[0])));
	System.out.println("memoization:\n  " + GRec.gRecMemo(Integer.parseInt(args[0])));
	System.out.println("iterative:\n  " + GRec.gRecIter(Integer.parseInt(args[0])));
    }
}
