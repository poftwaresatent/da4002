import java.util.HashMap;
import java.util.HashSet;
import java.util.Stack;
import java.util.LinkedList;
import java.util.StringTokenizer;
import java.util.NoSuchElementException;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileNotFoundException;
import java.io.IOException;

public class Graph
{
    public HashMap<String, Vertex> vertices;
    
    public Graph()
    {
	vertices = new HashMap<String, Vertex>();
    }
    
    public Vertex findVertex(String name)
    {
	return vertices.get(name);
    }
    
    public Vertex getOrMakeVertex(String name)
    {
	Vertex vv = vertices.get(name);
	if (null == vv) {
	    vv = new Vertex(name);
	    vertices.put(name, vv);
	}
	return vv;
    }
    
    public Edge addEdge(Vertex source, Vertex destination, double cost)
    {
	Edge ee = new Edge(cost, destination);
	source.neighbors.add(ee);
	return ee;
    }
    
    public Edge addEdge(String source, String destination, double cost)
    {
	return addEdge(getOrMakeVertex(source), getOrMakeVertex(destination), cost);
    }
    
    public boolean load(String filename, boolean undirected)
    {
	try {
	    BufferedReader in = new BufferedReader(new FileReader(filename));
	    String line;
	    while (null != (line = in.readLine())) {
		StringTokenizer st = new StringTokenizer(line);
		String source = st.nextToken();
		String destination = st.nextToken();
		double cost = Double.parseDouble(st.nextToken());
		addEdge(source, destination, cost);
		if (undirected) {
		    addEdge(destination, source, cost);
		}
	    }
	}
	catch (NumberFormatException ee) {
	    System.err.println("format error in file " + filename
			       + "\n  (costs must be real numbers)");
	    return false;
	}
	catch (NoSuchElementException ee) {
	    System.err.println("syntax error in file " + filename
			       + "\n  (each line must have 3 entries: two strings and a double)");
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
    
}
