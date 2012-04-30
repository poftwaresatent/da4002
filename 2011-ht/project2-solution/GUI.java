import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;
import javax.imageio.*;
import java.io.*;


class GraphPainting
    extends Canvas
{
    BufferedImage img;
    
    public GraphPainting(String imgfname)
    {
	try {
	    img = ImageIO.read(new File(imgfname));
	} catch (IOException e) {
	}
    }
    
    public Dimension getPreferredSize() {
        if (null == img) {
	    return new Dimension(100, 100);
        }
	return new Dimension(img.getWidth(null), img.getHeight(null));
    }
    
    public void paint(Graphics gfx)
    {
	gfx.drawImage(img, 0, 0, null);
    }
}


public class GUI
    extends Frame
    implements ActionListener
{
    GraphPainting gp;
    Panel cp;
    
    public GUI(String imgfname)
    {
	super("Grid Viewer");
        setBackground(new Color(0, 0, 63));
	
	gp = new GraphPainting(imgfname);
	add("North", gp);
	
        Button quit = new Button("quit");
	quit.addActionListener(this);
        cp = new Panel();
        cp.add(quit);
        add("South", cp);
	
	Dimension gpdim = gp.getPreferredSize();
	setSize(gpdim.width, gpdim.height + 80);
    }
    
    public void actionPerformed(ActionEvent ae)
    {
        if (ae.getActionCommand().equals("quit")) {
            System.exit(0);
	}
    }
    
    public static void main(String[] args)
    {
	GUI gui = new GUI(args.length > 0 ? args[0] : "maze.png");
	gui.setVisible(true);
    }
}
