package exercise2;

import java.io.BufferedReader;
import java.io.InputStreamReader;

public class RPNCalculator
{
    static private StringVector stack = new StringVector(10);
    
    static private String process(String input)
    {
	try {
	    
	    if (input.equals("+")) {
		double bb = Double.parseDouble(stack.back());
		stack.popBack();
		double aa = Double.parseDouble(stack.back());
		stack.popBack();
		stack.pushBack("" + (aa + bb));
		return "OK";
	    }
	    
	    if (input.equals("-")) {
		double bb = Double.parseDouble(stack.back());
		stack.popBack();
		double aa = Double.parseDouble(stack.back());
		stack.popBack();
		stack.pushBack("" + (aa - bb));
		return "OK";
	    }
	    
	    stack.pushBack(input);
	}
	catch (Exception ee) {
	    return "ERROR: " + ee;
	}
	
	return "OK";
    }
    
    static public void main(String[] args)
    {
	BufferedReader in = new BufferedReader(new InputStreamReader(System.in));
	try {
	    String status = "OK";
	    while (true) {
		System.out.println();
		stack.print("    ");
		System.out.println(status);
		System.out.print("> ");
		String line = in.readLine();
		if (null == line) {
		    break;
		}
		status = process(line);
	    }
	}
	catch (Exception ee) {
	    System.out.println("oops: " + ee);
	}
    }
}
