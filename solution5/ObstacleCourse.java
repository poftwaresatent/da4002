import java.util.PriorityQueue;

class QueueElement
    implements Comparable<QueueElement>
{
    public QueueElement(int _value, int _ix, int _iy)
    {
	value = _value;
	ix = _ix;
	iy = _iy;
    }
    
    public int compareTo(QueueElement other)
    {
	return value - other.value;
    }
}


public class ObstacleCourse
{
    private int width, height;
    private int[][] cost;
    private int[][] value;
    
    public ObstacleCourse()
    {
	width = 30;
	height = 20;
	cost = new int[width][height];
	for (int xx = 0; xx < width; ++xx) {
	    for (int yy = 0; yy < height; ++yy) {
		cost[xx][yy] = 1;
	    }
	}
	// pool of water
	for (int xx = 5; xx < 25; ++xx) {
	    for (int yy = 0; yy < 5; ++yy) {
		cost[xx][yy] = 5;
	    }
	}
	// walls
	for (int yy = 6; yy < 15; ++yy) {
	    cost[10][yy] = -1;
	}
	for (int yy = 10; yy < 20; ++yy) {
	    cost[20][yy] = -1;
	}
    }
    
    public boolean propagate(int startx, int starty)
    {
	value = new int[width][height];
	for (int xx = 0; xx < width; ++xx) {
	    for (int yy = 0; yy < height; ++yy) {
		value[xx][yy] = -1;
	    }
	}
	
	PriorityQueue<QueueElement> pq = new PriorityQueue<QueueElement>();
	pq.add(new QueueElement(0, startx, starty));
	while (0 != pq.size()) {
	    QueueElement qe = pq.poll();
	    
	}
    }
    
}
