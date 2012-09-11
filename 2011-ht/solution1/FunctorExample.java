interface Functor {
    public int call(int lhs, int rhs);
}

class Plus implements Functor {
    public int call(int lhs, int rhs) {
	return lhs + rhs;
    }
}

class Minus implements Functor {
    public int call(int lhs, int rhs) {
	return lhs - rhs;
    }
}

public class FunctorExample {
    static private int apply(int lhs, int rhs, Functor ff) {
	return ff.call(lhs, rhs);
    }
    
    static public void main(String[] args) {
	Functor[] funcs = { new Plus(), new Minus() };
	System.out.println("Plus:  " + apply(42, 17, funcs[0]));
	System.out.println("Minus: " + apply(42, 17, funcs[1]));
    }
}
