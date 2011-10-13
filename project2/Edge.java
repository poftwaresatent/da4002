public class Edge
{
    public final double cost;
    public final Vertex destination;
    
    public Edge(double _cost, Vertex _destination)
    {
	cost = _cost;
	destination = _destination;
    }
}
