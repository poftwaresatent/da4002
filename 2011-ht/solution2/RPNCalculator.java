import java.io.BufferedReader;
import java.io.InputStreamReader;

public class RPNCalculator
{
    static private StringVector stack = new StringVector(10);
    
    static private String process(String input)
    {
	try {
	    
	    if (input.equals("h")) {
		System.out.println("RPNCalculator HELP");
		System.out.println("  enter numbers, followed by return, to push them onto the stack");
		System.out.println("  enter operator symbols to perform them on the two top items on the stack");
		System.out.println("  available commands:");
		System.out.println("    h   print this help message");
		System.out.println("    c   clear the stack");
		System.out.println("    s   sum up all the numbers on the stack");
		System.out.println("    q   quit the application");
		System.out.println("  available operators:");
		System.out.println("    +   adds two numbers");
		System.out.println("    -   removes the bottom-most item from the one above");
		System.out.println("    *   multiplies two numbers");
		System.out.println("    /   divides the number above the bottom-most by the bottom-most");
		return "OK";
	    }
	    
	    if (input.equals("c")) {
		stack.clear();
		return "OK";
	    }
	    
	    if (input.equals("s")) {
		double sum = 0;
		while ( ! stack.empty()) {
		    sum += Double.parseDouble(stack.back());
		    stack.popBack();
		}
		stack.pushBack("" + sum);
		return "OK";
	    }
	    
	    if (input.equals("q")) {
		System.out.println("Byebye!");
		System.exit(0);
	    }
	    
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
	    
	    if (input.equals("*")) {
		double bb = Double.parseDouble(stack.back());
		stack.popBack();
		double aa = Double.parseDouble(stack.back());
		stack.popBack();
		stack.pushBack("" + (aa * bb));
		return "OK";
	    }
	    
	    if (input.equals("/")) {
		double bb = Double.parseDouble(stack.back());
		stack.popBack();
		double aa = Double.parseDouble(stack.back());
		stack.popBack();
		stack.pushBack("" + (aa / bb));
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
