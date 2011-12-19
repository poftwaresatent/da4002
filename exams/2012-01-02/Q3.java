import java.util.LinkedList;

class Vertex {
  LinkedList neighbors
    = new LinkedList();
}

class Graph {
  Vertex A, B, C, D;
  
  public Graph() {
    A.neighbors.add(B);
    A.neighbors.add(C);
    B.neighbors.add(C);
    B.neighbors.add(D);
    D.neighbors.add(A);
  }
}
