package GUI;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;

public class CompositePrompter extends Dialog implements MouseListener, ItemListener {

    private Set<String> operacije = new HashSet<String>();
    private TextField nameField = new TextField();
    private ArrayList<String> opNames = new ArrayList<>();
    private ArrayList<Integer> constants = new ArrayList<>();

    private Button add = new Button("Add");
    private TextField constField = new TextField();
    private TextArea overview = new TextArea();

    private Choice izborOperacija = new Choice();

    private Button clear = new Button("Clear");
    private Button done = new Button("Done");

    private boolean requiersConstant = true;
    private String name;
    private String op;
    private int c;
    private int counter = 0;
    private boolean cleared = false;

    private void initSet()
    {
        operacije.add("Abs");
        operacije.add("Grayscale");
        operacije.add("BlackAndWhite");
        operacije.add("Inverse");
        operacije.add("Median");
        operacije.add("Add");
        operacije.add("Sub");
        operacije.add("InverseSub");
        operacije.add("Mul");
        operacije.add("Div");
        operacije.add("InverseDiv");
        operacije.add("Power");
        operacije.add("Log");
        operacije.add("Min");
        operacije.add("Max");

    /*!((operacije.equals("Abs") || operacije.equals("Grayscale")||operacije.equals("BlackAndWhite")
                || operacije.equals("Inverse") || operacije.equals("Log") || operacije.equals("Median")) );*/

    }

    public CompositePrompter(Frame owner, String title, boolean modal) {
        super(owner, title, modal);
        addWindowListener(new WindowAdapter()
        {
            public void windowClosing(WindowEvent e) {
                clear();
                dispose();
            }
        });
        pack();
        initSet();
        setMinimumSize(new Dimension(300,200));
        setMaximumSize(new Dimension(300,200));
        setLocationRelativeTo(owner);
        addComponents();
        setVisible(true);


    }
    private void clear()
    {
        op="";
        c=0;
        name="";
        opNames.clear();
        constants.clear();
        nameField.setText("");
        constField.setText("");
        overview.setText("");
        cleared = true;
        done.setEnabled(false);
        clear.setEnabled(false);
    }

    public boolean isClear() {return  this.cleared;}

    private void addComponents()
    {
        for (String s: operacije) {

            izborOperacija.add(s);
        }

        izborOperacija.addItemListener(this);
        add.addMouseListener(this);

        Panel namePanel = new Panel(new GridLayout(1,2));
        namePanel.add(new Label("Name"));
        nameField.addMouseListener(this);
        namePanel.add(nameField);

        Panel izbor = new Panel(new GridLayout(1,3));
        izbor.add(izborOperacija);
        izbor.add(constField);
        izbor.add(add);

        done.addMouseListener(this);
        done.setEnabled(false);
        clear.addMouseListener(this);
        clear.setEnabled(false);

        Panel south = new Panel(new GridLayout(3,1));

        south.add(namePanel);
        south.add(clear);
        south.add(done);

        Panel panel = new Panel(new BorderLayout());
        panel.add(izbor,BorderLayout.NORTH);
        panel.add(overview,BorderLayout.CENTER);
        panel.add(south,BorderLayout.SOUTH);

        add(panel);

    }

    @Override
    public void mouseClicked(MouseEvent e) {

        if(e.getSource() instanceof Button)
        {
            if(((Button) e.getSource()).getLabel().equals(add.getLabel()))
            {
                if(!op.equals(""))
                {
                    if(!requiersConstant)
                        c=-1;
                    else
                    {
                        if(constField.getText().equals(""))
                            c=0;
                        else
                            c=Integer.parseInt(constField.getText());
                    }



                    opNames.add(op);
                    constants.add(c);
                    counter++;
                    String sop = op + " " +c+"\n";

                    if(opNames.size()>1 && !nameField.getText().equals(""))
                        done.setEnabled(true);
                    constField.setText("");
                    clear.setEnabled(true);
                    overview.append(sop);
                    sop ="";
                }

            }
            else if(((Button) e.getSource()).getLabel().equals(done.getLabel()))
            {
                if(opNames.size()!=0 && constants.size()!=0)
                {
                    name=nameField.getText();
                    setVisible(false);
                }

            }
            else if(((Button) e.getSource()).getLabel().equals(clear.getLabel()))
            {
                clear();
                revalidate();
                repaint();
            }
        }

    }

    public String getCompositeName() {return  this.name;}

    public ArrayList<Integer> getConstants() {
        return constants;
    }
    public ArrayList<String> getOpNames() {
        return opNames;
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
            if(opNames.size()>1 && !nameField.getText().equals(""))
                done.setEnabled(true);
        }

    }

    @Override
    public void itemStateChanged(ItemEvent e) {

        if(e.getSource() instanceof Choice)
        {
            op = ((Choice) e.getSource()).getSelectedItem();

            requiersConstant =  (!((op.equals("Abs") || op.equals("Grayscale")||op.equals("BlackAndWhite")
                    || op.equals("Inverse") || op.equals("Log") || op.equals("Median")) ));

            if(!requiersConstant)
                constField.setEnabled(false);

        }



    }
}
