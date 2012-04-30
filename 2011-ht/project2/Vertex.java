import java.util.LinkedList;

public class Vertex
{
    public LinkedList<Edge> neighbors;
    
    public Vertex()
    {
	neighbors = new LinkedList<Edge>();
    }
}
