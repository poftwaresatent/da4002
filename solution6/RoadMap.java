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
    public enum SearchMethod { DFS, BFS };
    public Graph graph;
    
    public RoadMap()
    {
	graph = new Graph();
    }
    
    public boolean load(String filename, boolean undirected_edges, boolean verbose)
    {
	try {
	    BufferedReader in = new BufferedReader(new FileReader(filename));
	    String line;
	    while (null != (line = in.readLine())) {
		StringTokenizer st = new StringTokenizer(line);
		String source = st.nextToken();
		String destination = st.nextToken();
		double cost = Double.parseDouble(st.nextToken());
		graph.addEdge(source, destination, cost);
		if (verbose) {
		    System.out.println("added edge " + source + " -> " + destination + " with cost " + cost);
		}
		if (undirected_edges) {
		    graph.addEdge(destination, source, cost);
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
    
    public boolean findPath(SearchMethod sm, String source, String destination, boolean verbose)
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
	boolean found = false;
	switch (sm) {
	case DFS:
	    found = graph.dfs(sv, new FindCity(dv, verbose));
	    break;
	case BFS:
	    found = graph.bfs(sv, new FindCity(dv, verbose));
	    break;
	default:
	    System.err.println("BUG: the search method " + sm + " is not handled in RoadMap.findPath");
	    return false;
	}
	if (verbose) {
	    if (found) {
		System.out.println("yes, " + sm + " found a path from " + source + " to " + destination);
	    }
	    else {
		System.out.println("no, " + sm + " did not find a path from " + source + " to " + destination);
	    }
	}
	return found;
    }
    
    public static void main(String[] args)
    {
	RoadMap undirected_rm = new RoadMap();
	if ( ! undirected_rm.load("city-connections-example.txt", true, false)) {
	    System.err.println("failed to load graph");
	    System.exit(42);
	}
	RoadMap directed_rm = new RoadMap();
	directed_rm.load("city-connections-example.txt", false, false);
	
	System.out.println("\ntrying visby -> goteborg in undirected road map");
	undirected_rm.findPath(SearchMethod.DFS, "visby", "goteborg", true);
	undirected_rm.findPath(SearchMethod.BFS, "visby", "goteborg", true);
	System.out.println("\ntrying visby -> goteborg in directed road map");
	directed_rm.findPath(SearchMethod.DFS, "visby", "goteborg", true);
	directed_rm.findPath(SearchMethod.BFS, "visby", "goteborg", true);
	
	System.out.println("\ntrying new_york -> goteborg in undirected road map");
	undirected_rm.findPath(SearchMethod.DFS, "new_york", "goteborg", true);
	undirected_rm.findPath(SearchMethod.BFS, "new_york", "goteborg", true);
	System.out.println("\ntrying goteborg -> bangkok in directed road map");
	directed_rm.findPath(SearchMethod.DFS, "goteborg", "bangkok", true);
	directed_rm.findPath(SearchMethod.BFS, "goteborg", "bangkok", true);
	
	System.out.println("\ntrying ystad -> ostersund in undirected road map");
	undirected_rm.findPath(SearchMethod.DFS, "ystad", "ostersund", true);
	undirected_rm.findPath(SearchMethod.BFS, "ystad", "ostersund", true);
	System.out.println("\ntrying ystad -> ostersund in directed road map");
	directed_rm.findPath(SearchMethod.DFS, "ystad", "ostersund", true);
	directed_rm.findPath(SearchMethod.BFS, "ystad", "ostersund", true);
    }
}
