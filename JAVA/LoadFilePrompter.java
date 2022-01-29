package GUI;

import java.awt.*;
import java.awt.event.*;

import java.security.Key;

public class LoadFilePrompter extends Dialog implements  MouseListener, KeyListener{

    private String inputText="";
    private TextField textField = new TextField();
    private Button loadButton = new Button("Load");

    public LoadFilePrompter(Frame owner, String title, boolean modal) {
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
       Label l = (new Label("Enter file name:"));

       Panel interakcija = new Panel(new BorderLayout());
       loadButton.addMouseListener(this);
       loadButton.setEnabled(false);
       textField.addMouseListener(this);
       interakcija.add(textField);
       interakcija.add(loadButton,BorderLayout.EAST);

        //raspored.add(l);
        //raspored.add(interakcija);

       add(l);
       add(interakcija,BorderLayout.SOUTH);



    }

    public String getInputText() {return this.inputText;}

    @Override
    public void mouseClicked(MouseEvent e) {

        if(e.getSource() instanceof Button)
        {

            if(((Button) e.getSource()).getLabel().equals("Load"))
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

        if(e.getSource() instanceof TextField)
        {
            if(!textField.getText().equals(""))
                loadButton.setEnabled(true);
        }

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

