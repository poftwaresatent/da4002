import java.awt.*;
import java.awt.event.*;

class VisualReports
    extends Frame
    implements ActionListener
{
    private Ball redBall, blueBall;
    
    public static void main(String [] cmd)
    {
        VisualReports vr = new VisualReports();
        vr.setVisible(true);
    }
    
    public VisualReports()
    {
        setSize(600,600);
        setTitle("Reporting Positions");
        setBackground(Color.white);
	
        // a panel with three control buttons.
        Panel control = new Panel();
        Button quit = new ControlButton(this, "quit");
        Button rb = new ControlButton(this, "red ball");
        Button bb = new ControlButton(this, "blue ball");
        control.add(quit);
	control.add(rb);
	control.add(bb);
        add("South", control);

        redBall = new Ball(100, 50, 20, Color.red);
        blueBall = new Ball(100, 50, 20, Color.blue);
    }
    
    public void paint(Graphics gfx)
    {
        redBall.report(gfx);
        blueBall.report(gfx);
    }
    
    public void actionPerformed(ActionEvent ee)
    {
        if(ee.getActionCommand().equals("quit")) {
            System.exit(0);
	}
        else if(ee.getActionCommand().equals("red ball")) {
	    redBall.move();
	    repaint();
	}
        else {
	    blueBall.move();
	    repaint();
	}
    }
    
}


class ControlButton
    extends Button
{
    public ControlButton(ActionListener ff, String name)
    {
        super(name);
        setForeground(Color.black);
        addActionListener(ff);
    }
}
