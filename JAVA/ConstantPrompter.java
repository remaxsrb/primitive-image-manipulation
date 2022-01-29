package GUI;

        import java.awt.*;
        import java.awt.event.*;

        import java.security.Key;

public class ConstantPrompter extends Dialog implements MouseListener, KeyListener {

    private String inputText;
    private TextField textField = new TextField();
    private Button enterButton = new Button("Enter");

    public ConstantPrompter(Frame owner, String title, boolean modal) {
        super(owner, title, modal);

        addWindowListener(new WindowAdapter()
        {
            public void windowClosing(WindowEvent e) {dispose();}
        });
        pack();
        setMinimumSize(new Dimension(300,100));
        setMaximumSize(new Dimension(300,100));
        setLocationRelativeTo(owner);
        addComponents();
        setVisible(true);

    }

    private void addComponents()
    {
        //Panel raspored = new Panel(new GridLayout(2,1));
        Label l = (new Label("Enter constant:"));

        Panel interakcija = new Panel(new BorderLayout());
        enterButton.addMouseListener(this);
        interakcija.add(textField);
        interakcija.add(enterButton,BorderLayout.EAST);

        //raspored.add(l);
        //raspored.add(interakcija);

        add(l);
        add(interakcija,BorderLayout.SOUTH);



    }

    public int getConstant() {return Integer.parseInt(this.inputText);}

    @Override
    public void mouseClicked(MouseEvent e) {

        if(e.getSource() instanceof Button)
        {

            if(((Button) e.getSource()).getLabel().equals("Enter"))
            {
                inputText=textField.getText();
                setVisible(false);
            }

        }
        else if (e.getSource() instanceof TextField)
        {
            ((TextField) e.getSource()).requestFocus();
        }
    }

    @Override
    public void mousePressed(MouseEvent e) {

    }

    @Override
    public void mouseReleased(MouseEvent e) {

    }

    @Override
    public void mouseEntered(MouseEvent e) {

    }

    @Override
    public void mouseExited(MouseEvent e) {

    }

    @Override
    public void keyTyped(KeyEvent e) {

        textField.setText(textField.getText() + Character.toString(e.getKeyChar()));

    }

    @Override
    public void keyPressed(KeyEvent e) {

    }

    @Override
    public void keyReleased(KeyEvent e) {

    }
}