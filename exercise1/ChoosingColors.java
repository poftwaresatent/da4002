import javax.swing.*;

class ChoosingColors {
    public static void main(String[] commandLine) {
        JFrame frame = new JFrame("see your choice");
        frame.getContentPane().add(new JColorChooser());
        frame.pack();
        frame.setVisible(true);
    }
}
