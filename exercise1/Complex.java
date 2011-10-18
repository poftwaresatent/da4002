public class Complex
{
    
    private double re, im;
    
    /**
       to create a Complex with value 0 + i0
    */
    public Complex()
    {
        re = 0;
        im = 0;
    }
    
    /**
       to create a Complex with value rp + i ip  
    */
    public Complex(double rp, double ip)
    {
        re = rp;
	im = ip;
    }
    
    /**
       For a  Complex z, 
       
       z.real() is its real part
    */
    public double real()
    {
	return re;
    }
    
    /**
       For a Complex z,
       
       z.imag() is its imaginary part
    */
    public double imag()
    {
	return im;
    }
    
    /**
       For a Complex z,
       
       z.toString() is its string representation.
    */
    public String toString()
    {
        if (im == 0) {
	    return "" + re;
	}
        if (re == 0) {
	    return "" + im + "i";
	}
        return "" + re + " + i" + im;
    }
    
    private static double sq(double aa)
    {
        return aa * aa;
    }
    
    /**
       Complex.plus(z1,z2) is the Complex that results from adding z1 and z2.
    */
    public static final Complex plus(Complex aa, Complex bb)
    {
        return new Complex(aa.real() + bb.real(),
			   aa.imag() + bb.imag());
    }
    
    /**
       Complex.fromDouble(x) is a Complex with value x + i0.
    */
    public static final Complex fromDouble(double aa)
    {
        return new Complex(aa, 0.0);
    }
    
    /**
       Complex.i is the Complex with value 0 + i.
    */
    public static final Complex i = new Complex(0.0, 1.0);
    
    /**
       Complex.minus(z1,z2) is the Complex that results from substracting z2 from z1.       
    */
    public static final Complex minus(Complex aa, Complex bb)
    {
        return new Complex(aa.real() - bb.real(),
			   aa.imag() - bb.imag());
    }
    
    /**
       Complex.times(z1,z2) is the Complex that results from multiplying z1 and z2.
    */
    public static final Complex times(Complex aa, Complex bb)
    {
        return new Complex(aa.real() * bb.real() - aa.imag() * bb.imag(),
                           aa.real() * bb.imag() + aa.imag() * bb.real());
    }
    
    private static final Complex distribute(Complex aa, double xx)
    {
        return new Complex(aa.real() / xx, aa.imag() / xx);
    }
    
    /**
       Complex.conjugate(z) is, for z = a + ib, the Complex with value a - ib.
    */
    public static final Complex conjugate(Complex aa)
    {
        return new Complex(aa.real(), -aa.imag());
    }
    
    /**
       Complex.divide(z1,z2) is the Complex that results from dividing z1 by z2.
    */
    public static final Complex divide(Complex aa, Complex bb)
    {
        // remember: it throws an exception in case the double we distribute is 0.
        return distribute(times(aa, conjugate(bb)),
                          sq(bb.real()) + sq(bb.imag()));
    }
    
    /**
       Complex.invert(z) is the Complex 1/z.
    */
    public static final Complex invert(Complex aa)
    {
        return divide(fromDouble(1), aa);
    }
    
    public static final double modulus(Complex aa)
    {
        return Math.sqrt(sq(aa.real()) + sq(aa.imag()));
    }
    
    public static final double argument(Complex aa)
    {
        return Math.atan(aa.imag() / aa.real());
    }
    
    /**
       A method with which to test your operations.
    */
    public static void main(String [] args)
    {
        Complex aa = new Complex(1.0, 1.0);
        Complex bb = new Complex(5.0, 2.0);
        Complex cc = divide(aa, bb);
        System.out.println(i);
        System.out.println(times(i, i));
        System.out.println(cc);
    }
}
