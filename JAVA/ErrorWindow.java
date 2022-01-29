

package GUI;

import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

public class ErrorWindow extends Dialog {
    private String message;
    public ErrorWindow(Frame owner, String title, boolean modal) {

        super(owner, title, modal);
        pack();
        addWindowListener(new WindowAdapter()
        {
            public void windowClosing(WindowEvent e) {dispose();}
        });
        setMinimumSize(new Dimension(300,100));
        setMaximumSize(new Dimension(300,100));
        setLocationRelativeTo(owner);
        message=title;

        Label l = new Label(message);
        l.setAlignment(Label.CENTER);

        add(l);
        setVisible(true);
    }


}
