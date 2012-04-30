import java.util.LinkedList;

public class IdVertex
{
    public final int id;
    public LinkedList<IdEdge> neighbors;
    
    /**
       If you want to use the id as index into various external data
       stores, you have to make sure to generate consistent ids. The
       getVertex method of the IdGraph class does this for
       you. Similarly, any edges added to the neighbors of this vertex
       need to have consistent ids. The IdGraph.addEdge method does
       this.
     */
    public IdVertex(int _id)
    {
	id = _id;
	neighbors = new LinkedList<IdEdge>();
    }
}
