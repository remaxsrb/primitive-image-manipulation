package GUI;

import java.awt.*;

public class ProcessDialog extends Dialog {
    private String message;
    public ProcessDialog(Frame owner, String title, boolean modal) {

        super(owner, title, modal);
        pack();
        setMinimumSize(new Dimension(300,100));
        setMaximumSize(new Dimension(300,100));
        setLocationRelativeTo(owner);
        message=title+"...please wait...";
        Label l = new Label(message);
        l.setAlignment(Label.CENTER);
        add(l);
        setVisible(true);
    }


}
