public class Edge
{
    public final Vertex source;
    public final Vertex destination;
    public final double cost;
    
    public Edge(Vertex _source, Vertex _destination, double _cost)
    {
	source = _source;
	destination = _destination;
	cost = _cost;
    }
}
