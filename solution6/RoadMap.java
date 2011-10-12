import java.util.ArrayList;
import java.util.HashMap;
import java.util.StringTokenizer;
import java.util.NoSuchElementException;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.FileNotFoundException;
import java.io.IOException;


class FindCity
    implements IdVertexIterationCallback
{
    RoadMap roadmap;
    IdVertex city;
    boolean verbose;
    
    FindCity(RoadMap _roadmap, IdVertex _city, boolean _verbose)
    {
	roadmap = _roadmap;
	city = _city;
	verbose = _verbose;
    }
    
    public boolean processNodeIteration(IdVertex vertex, int counter)
    {
	if (verbose) {
	    System.out.println(counter + ": " + roadmap.city_names.get(vertex.id));
	}
	return vertex == city;
    }
}


public class RoadMap
{
    public IdGraph graph;
    public ArrayList<String> city_names;
    public HashMap<String, IdVertex> name_to_vertex_map;
    public ArrayList<Double> travel_costs;
    
    public RoadMap()
    {
	graph = new IdGraph();
	city_names = new ArrayList<String>();
	name_to_vertex_map = new HashMap<String, IdVertex>();
	travel_costs = new ArrayList<Double>();
    }
    
    public IdVertex getVertex(String city_name)
    {
	IdVertex vv = name_to_vertex_map.get(city_name);
	if (null == vv) {
	    vv = graph.addVertex();
	    city_names.add(city_name);
	    name_to_vertex_map.put(city_name, vv);
	}
	return vv;
    }
    
    public boolean load(String filename, boolean undirected_edges, boolean verbose)
    {
	try {
	    BufferedReader in = new BufferedReader(new FileReader(filename));
	    String line;
	    while (null != (line = in.readLine())) {
		StringTokenizer st = new StringTokenizer(line);
		String source_name = st.nextToken();
		String destination_name = st.nextToken();
		double cost = Double.parseDouble(st.nextToken());
		graph.addEdge(getVertex(source_name), getVertex(destination_name));
		travel_costs.add(cost);
		if (verbose) {
		    System.out.println("added edge " + source_name + " -> " + destination_name + " with cost " + cost);
		}
		if (undirected_edges) {
		    graph.addEdge(getVertex(destination_name), getVertex(source_name));
		    travel_costs.add(cost);
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
    
    public boolean findPathDFS(String source_name, String destination_name, boolean verbose)
    {
	IdVertex source = name_to_vertex_map.get(source_name);
	if (null == source) {
	    if (verbose) {
		System.out.println("source city not found: " + source_name);
		return false;
	    }
	}
	IdVertex destination = name_to_vertex_map.get(destination_name);
	if (null == destination) {
	    if (verbose) {
		System.out.println("destination city not found: " + destination_name);
		return false;
	    }
	}
	boolean found = graph.dfs(source, new FindCity(this, destination, verbose));
	if (verbose) {
	    if (found) {
		System.out.println("yes, there is a path from " + source_name + " to " + destination_name);
	    }
	    else {
		System.out.println("no, there is no path from " + source_name + " to " + destination_name);
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
	undirected_rm.findPathDFS("visby", "goteborg", true);
	System.out.println("\ntrying visby -> goteborg in directed road map");
	directed_rm.findPathDFS("visby", "goteborg", true);
	
	System.out.println("\ntrying new_york -> goteborg in undirected road map");
	undirected_rm.findPathDFS("new_york", "goteborg", true);
	System.out.println("\ntrying goteborg -> bangkok in directed road map");
	directed_rm.findPathDFS("goteborg", "bangkok", true);
	
	System.out.println("\ntrying ystad -> ostersund in undirected road map");
	undirected_rm.findPathDFS("ystad", "ostersund", true);
	System.out.println("\ntrying ystad -> ostersund in directed road map");
	directed_rm.findPathDFS("ystad", "ostersund", true);
    }
}
