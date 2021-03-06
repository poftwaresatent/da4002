import java.util.HashMap;
import java.util.HashSet;
import java.util.Stack;
import java.util.LinkedList;
import java.util.ArrayList;
import java.util.StringTokenizer;
import java.util.NoSuchElementException;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileNotFoundException;
import java.io.IOException;

public class Graph
{
    private static final double sq2 = Math.sqrt(2.0);
    private static final int[][] nbor
	= { {-1, -1}, {-1, 0}, {-1, 1}, {0, -1}, {0, 1}, {1, -1}, {1, 0}, {1, 1} };
    private static final double[] nscale
	= {      sq2,     1.0,     sq2,     1.0,    1.0,     sq2,    1.0,    sq2 };
    
    public HashMap<String, Vertex> vertices;
    
    public Graph()
    {
	vertices = new HashMap<String, Vertex>();
    }
    
    public Vertex findVertex(String name)
    {
	return vertices.get(name);
    }
    
    public Vertex addVertex(String name, double value)
    {
	Vertex vv = new Vertex(name, value);
	vertices.put(name, vv);
	return vv;
    }
    
    public Vertex getOrMakeVertex(String name)
    {
	Vertex vv = vertices.get(name);
	if (null == vv) {
	    vv = new Vertex(name, 0);
	    vertices.put(name, vv);
	}
	return vv;
    }
    
    public Edge addEdge(Vertex source, Vertex destination, double cost)
    {
	Edge ee = new Edge(source, destination, cost);
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
    
    public boolean loadGrid(String filename)
    {
	try {
	    BufferedReader in = new BufferedReader(new FileReader(filename));
	    String line;
	    ArrayList<ArrayList<Vertex>> grid = new ArrayList<ArrayList<Vertex>>();
	    
	    while (null != (line = in.readLine())) {
		ArrayList<Vertex> row = new ArrayList<Vertex>();
		grid.add(row);
		StringTokenizer st = new StringTokenizer(line);
		while (st.hasMoreTokens()) {
		    String cell = st.nextToken();
		    if (cell.equals("#")) {
			row.add(null);
		    }
		    else {
			row.add(addVertex("(" + grid.size() + "," + row.size() + ")",
					  Double.parseDouble(cell)));
		    }
		}
	    }
	    
	    for (int ii = 0; ii < grid.size(); ++ii) {
		ArrayList<Vertex> row = grid.get(ii);
		for (int jj = 0; jj < row.size(); ++jj) {
		    Vertex vv = row.get(jj);
		    if (null == vv) {
			continue;
		    }
		    for (int kk = 0; kk < nbor.length; ++kk) {
			int ni = ii + nbor[kk][0];
			if (ni < 0 || ni >= grid.size()) {
			    continue;
			}
			ArrayList<Vertex> nrow = grid.get(ni);
			int nj = jj + nbor[kk][1];
			if (nj < 0 || nj >= nrow.size()) {
			    continue;
			}
			Vertex nv = nrow.get(nj);
			if (null != nv) {
			    addEdge(vv, nv, vv.value * nscale[kk]);
			}
		    }
		}
	    }
	    
	}
	catch (NumberFormatException ee) {
	    System.err.println("format error in file " + filename
			       + "\n  (costs must be real numbers)");
	    return false;
	}
	catch (NoSuchElementException ee) {
	    System.err.println("oops, you hit a bug (NoSuchElementException)");
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

    public LinkedList<Vertex> dfs(Vertex start, Vertex goal)
    {
	for (Vertex vv : vertices.values()) {
	    vv.value = -1;
	    vv.backpointer = null;
	}
	
	Stack<Edge> open = new Stack<Edge>();
	open.push(new Edge(null, start, 0));
	for (int counter = 0; 0 < open.size(); ++counter) {
	    Edge current = open.pop();
	    if (0 > current.destination.value) {
		current.destination.value = counter;
		current.destination.backpointer = current.source;
		if (goal == current.destination) {
		    LinkedList<Vertex> path = new LinkedList<Vertex>();
		    for (Vertex vv = current.destination; null != vv; vv = vv.backpointer) {
			path.addFirst(vv);
		    }
		    return path;
		}
		for (Edge ee : current.destination.neighbors) {
		    if (0 > ee.destination.value) {
			open.push(ee);
		    }
		}
	    }
	}
	return null;
    }

    public LinkedList<Vertex> dfs(String start, String goal)
    {
	Vertex ss = findVertex(start);
	Vertex gg = findVertex(goal);
	if (null == ss || null == gg) {
	    return null;
	}
	return dfs(ss, gg);
    }
    
    public void print()
    {
	for (Vertex vv : vertices.values()) {
	    for (Edge ee : vv.neighbors) {
		System.out.println(vv.name + "\t" + ee.destination.name + "\t" + ee.cost);
	    }
	}
    }
    
    public void compactPrint()
    {
	for (Vertex vv : vertices.values()) {
	    System.out.print(vv.name + " [v: " + vv.value + "] -->");
	    for (Edge ee : vv.neighbors) {
		System.out.print(" " + ee.destination.name + " [c: " + ee.cost + "]  ");
	    }
	    System.out.println();
	}
    }
    
    public void prettyPrint()
    {
	for (Vertex vv : vertices.values()) {
	    System.out.println(vv.name + " [v: " + vv.value + "]");
	    for (Edge ee : vv.neighbors) {
		System.out.println("    --> " + ee.destination.name + " [c: " + ee.cost + "]");
	    }
	}
    }
    
    public void dotPrint(String name)
    {
	System.out.println("digraph \"" + name + "\" {\n  graph [overlap=scale];");
	for (Vertex vv : vertices.values()) {
	    for (Edge ee : vv.neighbors) {
		System.out.println("  \"" + vv.name + "\" -> \"" + ee.destination.name
				   + "\" [label=" + ee.cost + ",len=2];");
	    }
	    System.out.println();
	}
	System.out.println("}");
    }
    
    public static void main(String[] args)
    {
	if (0 == args.length) {
	    System.err.println("filename expected");
	    System.exit(42);
	}
	Graph gg = new Graph();
	if ( ! gg.load(args[0], false)) {
	    System.err.println("failed to load graph from " + args[0]);
	}
	gg.dotPrint(args[0]);
	if (2 < args.length) {
	    LinkedList<Vertex> path = gg.dfs(args[1], args[2]);
	    if (null == path) {
		System.out.println("\nno path from " + args[1] + " to " + args[2]);
	    }
	    else {
		System.out.println("\npath from " + args[1] + " to " + args[2] + ":");
		for (Vertex vv : path) {
		    System.out.println("  " + vv.name);
		}
	    }
	}
    }
    
}
