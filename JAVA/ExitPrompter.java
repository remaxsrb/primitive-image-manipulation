package GUI;

import java.awt.*;
import java.awt.event.*;

public class ExitPrompter  extends Dialog implements MouseListener {

    private Button yes = new Button("Yes");
    private Button no = new Button("No");
    boolean userAnswer=false;




    public ExitPrompter(Frame owner, String title, boolean modal) {
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

    public void addComponents()
    {
        Panel panel = new Panel(new BorderLayout());
        Label l =new Label("Do you want to save the image?",Label.CENTER);
        panel.add(l,BorderLayout.NORTH);
        Panel buttons = new Panel(new FlowLayout());
        yes.addMouseListener(this);
        no.addMouseListener(this);
        buttons.add(yes);
        buttons.add(no);

        panel.add(buttons,BorderLayout.SOUTH);
        add(panel);

    }

    public boolean getAnswer() {return  this.userAnswer;}

    @Override
    public void mouseClicked(MouseEvent e) {


        if(e.getSource() instanceof Button)
        {
            if(((Button) e.getSource()).getLabel().equals(yes.getLabel()))
                userAnswer=true;
            setVisible(false);


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
}
