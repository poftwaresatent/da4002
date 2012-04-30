class TypeConversion{
    public static void main(String[] commandLine){
        double quotient;
        int x = 6;
        int y = 10;
	
	System.out.println("quotient = x / y");
        quotient = x / y;
        System.out.println("  result: quotient = " + quotient);
	
	System.out.println("quotient = (double) x / y");
        quotient = (double) x / y;
        System.out.println("  result: quotient = " + quotient);
    }
}
