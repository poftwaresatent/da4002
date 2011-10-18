import java.awt.*;

class Ball
{
    private int centerX, centerY, radius;
    private Color color;
    
    public Ball(int xx, int yy, int rr, Color cc)
    {
        centerX = xx;
        centerY = yy;
        radius = rr;
        color = cc;
    }
    
    public void move()
    {
        centerX = centerX + 10;
        centerY = centerY + 10;
    }
    
    public void report()
    {
        System.out.println("Ball with radius " + radius
			   + " and coordinates (" + centerX + "," + centerY+ ")"
			   + " and color " + color);
    }
    
    public void report(Graphics pen)
    {
        pen.setColor(color);
        pen.fillOval(centerX - radius, centerY - radius, 2 * radius, 2 * radius);
    }
}
