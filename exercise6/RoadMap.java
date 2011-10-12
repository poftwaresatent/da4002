import java.util.StringTokenizer;
import java.util.NoSuchElementException;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileNotFoundException;
import java.io.IOException;


class FindCity
    implements ProcessVertex
{
    Vertex city;
    boolean verbose;
    
    FindCity(Vertex _city, boolean _verbose)
    {
	city = _city;
	verbose = _verbose;
    }
    
    public boolean visit(Vertex vertex, int counter)
    {
	if (verbose) {
	    System.out.println("  " + counter + ": " + vertex.name);
	}
	return vertex == city;
    }
}


public class RoadMap
{
    public Graph graph;
    public boolean verbose;
    
    public RoadMap(boolean _verbose)
    {
	graph = new Graph();
	verbose = _verbose;
    }
    
    public boolean load(String filename)
    {
	try {
	    BufferedReader in = new BufferedReader(new FileReader(filename));
	    String line;
	    while (null != (line = in.readLine())) {
		StringTokenizer st = new StringTokenizer(line);
		String source = st.nextToken();
		String destination = st.nextToken();
		graph.addEdge(source, destination);
		if (verbose) {
		    System.out.println("added edge " + source + " --> " + destination);
		}
	    }
	}
	catch (NoSuchElementException ee) {
	    System.err.println("syntax error in file " + filename
			       + "\n  (each line must contain 2 strings)");
	    return false;
	}
	catch (FileNotFoundException ee) {
	    System.err.println("no file called " + filename);
	    return false;
	}
	catch (IOException ee) {
	    System.err.println("input/output error in file " + filename);
	    return false;
	}
	return true;
    }
    
    public boolean findPathDFS(String source, String destination)
    {
	Vertex sv = graph.findVertex(source);
	if (null == sv) {
	    if (verbose) {
		System.out.println("source city not found: " + source);
		return false;
	    }
	}
	Vertex dv = graph.findVertex(destination);
	if (null == dv) {
	    if (verbose) {
		System.out.println("destination city not found: " + destination);
		return false;
	    }
	}
	boolean found = graph.dfs(sv, new FindCity(dv, verbose));
	if (verbose) {
	    if (found) {
		System.out.println("yes, there is a path from " + source + " to " + destination);
	    }
	    else {
		System.out.println("no, there is no path from " + source + " to " + destination);
	    }
	}
	return found;
    }
    
    public static void main(String[] args)
    {
	RoadMap rm = new RoadMap(true);
	if ( ! rm.load("city-connections-example.txt")) {
	    System.err.println("failed to load graph");
	    System.exit(42);
	}
	
	System.out.println("\ntrying visby -> goteborg");
	rm.findPathDFS("visby", "goteborg");
	
	System.out.println("\ntrying new_york -> goteborg");
	rm.findPathDFS("new_york", "goteborg");
	
	System.out.println("\ntrying ystad -> ostersund");
	rm.findPathDFS("ystad", "ostersund");
    }
}
