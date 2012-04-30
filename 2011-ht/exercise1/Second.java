class Second
{
    
    public static void main(String[] commandLine){
        primitiveTypes();
        System.out.println();
        referenceTypes();        
    }
    
    private static final void primitiveTypes()
    {
        // The meaning of ==.
        System.out.println("Primitive type Float:");
        // PI is a constant defined in the class Complex.
        // the output of this statement seems reasonable!
        System.out.println("Math.PI == Math.PI is " + (Math.PI == Math.PI));
	
        // when we want to consider a float as an integer we might use round
        // a method in class Math.
        // the output of this statement seems reasonable!
        System.out.println("Math.round(3.5) == Math.round(3.5) is " + 
                           (Math.round(3.5) == Math.round(3.5)));
    }
    
    private static final void referenceTypes()
    {
        // The meaning of ==.
        System.out.println("Reference type Complex:");
        // i is a constant defined in the class Complex.
        // the output of this statement seems reasonable!
        System.out.println("Complex.i == Complex.i is " + (Complex.i == Complex.i));
	
        // when we want to consider a double as a complex we use fromDouble
        // a method in class Complex.
        // Can you explain the output of this statement?
        System.out.println("Complex.fromDouble(3.5) == Complex.fromDouble(3.5) is " + 
			   (Complex.fromDouble(3.5)==Complex.fromDouble(3.5)));
	
        // Can you explain the output of these statements?
        Complex x = Complex.fromDouble(3.5);
        Complex y = x;
        System.out.println("x == y is "+(x==y));
        
        /*
          The current implementation of Complex requires that the method 
	         public boolean equals(Object x)
          is implemented so that 
                 complex1.equals(complex2)
          is true when complex1 and complex2 have the same real and imaginary parts.
	  
          Do so! Add the method equals to the class Complex, comment
          it and run javadoc to get a new version of the documentation
          of the class Complex.

          Notice that the method cannot be static! it is a so-called
          "instance method".
	  
          Check the output of
            System.out.println("fromDouble(3).equals(fromDouble(3)) is " + 
                                Complex.fromDouble(3).equals(Complex.fromDouble(3)));
         */
    }

}
