import java.awt.Color;

class Reports
{
    public static void main(String [] cmd)
    {
        Ball redBall = new Ball(100, 50, 20, Color.red);
        Ball blueBall = new Ball(100, 50, 20, Color.blue);
        redBall.report();
        blueBall.report();
        redBall.move();
        redBall.report();
    }
}
