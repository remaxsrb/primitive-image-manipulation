package GUI;

import java.awt.*;
import java.awt.event.*;


public class SaveProjectPrompter extends Dialog implements MouseListener, KeyListener {

    private String inputText;
    private TextField textField = new TextField();
    private Button saveButton = new Button("Save");


    public SaveProjectPrompter(Frame owner, String title, boolean modal) {
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
        Panel raspored = new Panel(new GridLayout(2,1));
        raspored.add(new Label("Enter file name:"));

        Panel interakcija = new Panel(new GridLayout(1,2));

        interakcija.add(textField);

        saveButton.addMouseListener(this);
        interakcija.add(saveButton);

        raspored.add(interakcija);

        add(raspored);


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

    @Override
    public void mouseClicked(MouseEvent e) {

        if(e.getSource() instanceof Button)
        {

            if(((Button) e.getSource()).getLabel().equals("Save"))
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

    public String getInputText() {return this.inputText;}


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
}
