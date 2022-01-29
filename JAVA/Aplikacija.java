package GUI;
import java.awt.*;
import java.awt.event.*;
import java.text.Format;
import java.text.NumberFormat;
import java.text.ParseException;
import java.util.ArrayList;
import java.util.Formatter;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import Picture.*;
import Picture.Image;

import javax.swing.*;
import javax.swing.text.DocumentFilter;
import javax.swing.text.MaskFormatter;
import javax.swing.text.NumberFormatter;


public class Aplikacija extends Frame implements ItemListener, ActionListener,MouseListener,KeyListener{

    private MenuBar menuBar = new MenuBar();
    private static Image imageInstance = null;
    private ScrollPane imageScrollPane = new ScrollPane();
    private  static final Label labelOperation = new Label("Operations");
    private  static final Label labelLayers = new Label("Layers");
    private  static final Label labelSelections = new Label("Selections");

    private Button createOp = new Button("Create composite operation");
    private Button applyOp = new Button("Apply operation");
    private ScrollPane opBoxesScrollPane = new ScrollPane();
    private CheckboxGroup operationGroup = new CheckboxGroup();
    private ArrayList<Checkbox>  operationsButtonList = null;
    private Panel opBoxes = new Panel(new GridLayout(0,1));
    private Panel layerBoxes = new Panel(new GridLayout(5,1));
    private ArrayList<Checkbox>  layerButtonList = null;
    private ScrollPane layerScrollPane = new ScrollPane();
    private JFormattedTextField alphaTextField = new JFormattedTextField(rgbaFormater());
    private Button setTransparency = new Button("Set Alpha");
    private Button layerDeletion = new Button("Delete Layer");

    private ScrollPane selectionScrollPane = new ScrollPane();
    private Button createSelection = new Button("Create Selection");
    private Button deleteSelection = new Button("Delete Selection");
    private TextField selectionNaming = new TextField();
    private TextField selectionLayer = new TextField();
    private Button fillSelection = new Button("Fill Selection");
    private JFormattedTextField redTextField = new JFormattedTextField(rgbaFormater());
    private JFormattedTextField greenTextField = new JFormattedTextField(rgbaFormater());
    private JFormattedTextField blueTextField = new JFormattedTextField(rgbaFormater());
    private int x,y,x1,y1;
    private boolean selecting=false;
    private ArrayList<Rechtangle> rectangles = null;
    private Panel selectionBoxes = new Panel(new GridLayout(0,1));
    private CheckboxGroup checkBoxSelections = new CheckboxGroup();
    private ArrayList<Checkbox> selectionButtons = null;

    private boolean generatedFile = false;

    private  Image createImage()
    {
        if(imageInstance==null)
            return new Image(this);
        else
            return null;
    }

    public Aplikacija()
    {
        super("POOP_Project_2020");
        setSize(1000,800);
        setMinimumSize(new Dimension(1000,800));
        setMaximumSize(new Dimension(Frame.MAXIMIZED_HORIZ,Frame.MAXIMIZED_VERT));
        addWindowListener(new WindowAdapter()
        {
            public void windowClosing(WindowEvent e)
            {
                if(!generatedFile && imageInstance.getNumberOfLayers()>0)
                {

                    ExitPrompter exitPrompter = new ExitPrompter(Aplikacija.this,"Exit",true);

                        if(!exitPrompter.isVisible())
                        {
                            if(exitPrompter.getAnswer())
                            {
                                SaveImagePrompter saveImagePrompter = new SaveImagePrompter(Aplikacija.this, "Save Image", true);

                                if(!saveImagePrompter.isVisible())
                                {

                                    String targetName = saveImagePrompter.getInputText();
                                    saveImagePrompter.dispose();
                                    imageInstance.saveImage(targetName);


                                }
                            }
                        }

                }
                System.exit(0);

            }
        });

        imageInstance = createImage();
        if(imageInstance!=null)
            imageInstance.addMouseListener(this);
        addMenus();
        addComponents();
        setVisible(true);
    }

    public void paint(Graphics g) {}


    public void addOperations()
    {
        operationsButtonList = new ArrayList<>(imageInstance.getOperations().size());
        opBoxes.removeAll();

        int count =0;
        for (String s: imageInstance.getOperations()) {

            Checkbox cb = new Checkbox(s,operationGroup,false);
            cb.setMinimumSize(new Dimension(opBoxes.getWidth(), cb.getHeight()));
            operationsButtonList.add(cb);
            operationsButtonList.get(count).addItemListener(this);
            opBoxes.add(operationsButtonList.get(count));
            count++;
        }



    }

    public void addLayers()
    {
        int layerCount = imageInstance.getNumberOfLayers();

        if(layerCount!=0)
        {
            layerButtonList = new ArrayList<>(layerCount);

            layerBoxes.removeAll();
            int count =0;

            for (Layer l: imageInstance.getLayers()) {

                String layerLabel = "Layer"+ Integer.toString(count+1) + ":"+ l.getSourceFile();
                layerButtonList.add(new Checkbox(layerLabel,true));
                layerButtonList.get(count).addItemListener(this);
                layerBoxes.add(layerButtonList.get(count));
                count++;

            }
        }
    }

    public void addSelections()
    {

        int count=0;
        selectionButtons=new ArrayList<>();
        selectionBoxes.removeAll();
        for(Selection s: imageInstance.getSelections().values())
        {
            String sLabel = s.getName() + ":"+ (s.getLayerNo() + 1);
            selectionButtons.add(new Checkbox(sLabel,checkBoxSelections,false));
            selectionButtons.get(count).addItemListener(this);
            selectionBoxes.add(selectionButtons.get(count));
            count++;
        }
    }

    private void addComponents()
    {

        Panel operacije = new Panel(new BorderLayout());
        operacije.add(labelOperation, BorderLayout.NORTH);

        addOperations();
        opBoxesScrollPane.add(opBoxes);
        operacije.add(opBoxesScrollPane,BorderLayout.CENTER);

        createOp.addMouseListener(this);
        applyOp.addMouseListener(this);
        applyOp.setEnabled(false);
        Panel opButtons = new Panel(new GridLayout(2,1));
        opButtons.add(createOp);
        opButtons.add(applyOp);
        operacije.add(opButtons,BorderLayout.SOUTH);

        Panel LayersandSelections = new Panel(new GridLayout(2,1));

        Panel layers = new Panel(new BorderLayout());
        setTransparency.addMouseListener(this);
        setTransparency.setEnabled(false);
        layerDeletion.addMouseListener(this);
        layerDeletion.setEnabled(false);
        Panel layerButtons = new Panel (new GridLayout(2,1));
        Panel transparency = new Panel(new GridLayout(1,2));
        alphaTextField.setEnabled(false);

        transparency.add(setTransparency);
        alphaTextField.addKeyListener(this);
        transparency.add(alphaTextField);
        layerButtons.add(transparency);
        layerButtons.add(layerDeletion);

        addLayers();
        layerScrollPane.add(layerBoxes);


        layers.add(labelLayers,BorderLayout.NORTH);
        layers.add(layerScrollPane,BorderLayout.CENTER);
        layers.add(layerButtons,BorderLayout.SOUTH);

        Panel selections = new Panel(new BorderLayout());

        createSelection.addMouseListener(this);
        createSelection.setEnabled(false);
        fillSelection.addMouseListener(this);
        fillSelection.setEnabled(false);
        Panel colorSelection = new Panel(new GridLayout(2,1));
        Panel rgb = new Panel(new GridLayout(1,3));

        Panel r = new Panel(new GridLayout(1,2));
        redTextField.setEnabled(false);
        redTextField.addKeyListener(this);
        r.add(new Label("R:"));
        r.add(redTextField);
        Panel g = new Panel(new GridLayout(1,2));
        greenTextField.setEnabled(false);
        greenTextField.addKeyListener(this);
        g.add(new Label("G:"));
        g.add(greenTextField);
        blueTextField.setEnabled(false);
        blueTextField.addKeyListener(this);
        Panel b = new Panel(new GridLayout(1,2));
        b.add(new Label("B"));

        b.add(blueTextField);
        rgb.add(r);
        rgb.add(g);
        rgb.add(b);
        colorSelection.add(fillSelection);
        colorSelection.add(rgb);

        Panel creatingSelections = new Panel(new GridLayout(2,1));
        Panel paramSelections = new Panel(new GridLayout(1,4));
        paramSelections.add(new Label("Name:"));
        selectionNaming.setEnabled(false);
        paramSelections.add(selectionNaming);
        paramSelections.add(new Label("Layer:"));
        selectionLayer.setEnabled(false);
        paramSelections.add(selectionLayer);
        creatingSelections.add(createSelection);
        creatingSelections.add(paramSelections);

        Panel selectionButtons = new Panel(new GridLayout(0,1));
        selectionButtons.add(creatingSelections);
        selectionButtons.add(colorSelection);
        deleteSelection.addMouseListener(this);
        deleteSelection.setEnabled(false);
        selectionButtons.add(deleteSelection);

        selectionScrollPane.add(selectionBoxes);
        selections.add(labelSelections, BorderLayout.NORTH);
        selections.add(selectionScrollPane,BorderLayout.CENTER);
        selections.add(selectionButtons, BorderLayout.SOUTH);

        LayersandSelections.add(layers);
        LayersandSelections.add(selections);


      add(operacije, BorderLayout.WEST);
      imageScrollPane.addMouseListener(this);
      imageScrollPane.getHAdjustable().setUnitIncrement(50);
      imageScrollPane.getHAdjustable().setBlockIncrement(50);
      imageScrollPane.getVAdjustable().setUnitIncrement(50);
      imageScrollPane.getVAdjustable().setBlockIncrement(50);
      imageScrollPane.setSize((int)(0.7*(double)(getWidth())),getHeight());
      imageScrollPane.add(imageInstance);

      add(imageScrollPane,BorderLayout.CENTER);
      add(LayersandSelections, BorderLayout.EAST);


    }

    private NumberFormatter rgbaFormater()
    {



        NumberFormat rgbaFormat = NumberFormat.getIntegerInstance();
        rgbaFormat.setMinimumIntegerDigits(0);
        rgbaFormat.setMaximumIntegerDigits(3);
        rgbaFormat.setMinimumFractionDigits(0);
        rgbaFormat.setGroupingUsed(false);

        NumberFormatter rgbaFormatter = new NumberFormatter(rgbaFormat) ;
        rgbaFormatter.setValueClass(Integer.class);
        rgbaFormatter.setMinimum(0);
        rgbaFormatter.setMaximum(255);
        rgbaFormatter.setAllowsInvalid(true);
        rgbaFormatter.setCommitsOnValidEdit(true);


        return  rgbaFormatter;

    }

    
    private void disableMenues()
    {
       menuBar.getMenu(0).setEnabled(false);
    }

    private void enableMenues()
    {
        menuBar.getMenu(0).setEnabled(true);
    }

    private void addMenus()
    {

        Menu file = new Menu("File");
        file.add("Import image file");
        file.add("Export image file");
        file.add("Load project");
        file.add("Save project");
        file.addActionListener(this);
        file.getItem(1).setEnabled(false);
        file.getItem(3).setEnabled(false);
        menuBar.add(file);
        setMenuBar(menuBar);
    }


    @Override
    public void actionPerformed(ActionEvent e) {

        String request = e.getActionCommand();

        if(request.equals("Import image file"))
        {
            LoadFilePrompter loadImagePrompter = new LoadFilePrompter(this, request, true);

            if(!loadImagePrompter.isVisible())
            {
                if(!loadImagePrompter.getInputText().equals(""))
                {
                    layerDeletion.setEnabled(true);
                    setTransparency.setEnabled(true);
                    alphaTextField.setEnabled(true);
                    applyOp.setEnabled(true);
                    createSelection.setEnabled(true);
                    selectionNaming.setEnabled(true);
                    selectionLayer.setEnabled(true);
                    imageInstance.addLayer(loadImagePrompter.getInputText());
                    loadImagePrompter.dispose();
                    generatedFile=false;
                    menuBar.getMenu(0).getItem(0).setEnabled(true);
                    menuBar.getMenu(0).getItem(1).setEnabled(true);
                    menuBar.getMenu(0).getItem(2).setEnabled(false);
                    menuBar.getMenu(0).getItem(3).setEnabled(true);



                }


            }

        }
        else if(request.equals("Export image file"))
        {
            SaveImagePrompter saveImagePrompter = new SaveImagePrompter(this, request, true);

            if(!saveImagePrompter.isVisible())
            {
                if(!saveImagePrompter.getInputText().equals(""))
                {
                    String targetName = saveImagePrompter.getInputText();
                    saveImagePrompter.dispose();
                    ProcessDialog pd = new ProcessDialog(this,"Exporting image file",false);
                    if(pd.isVisible())
                    {
                        disableMenues();
                        imageInstance.saveImage(targetName);
                        pd.dispose();
                        enableMenues();
                        generatedFile=true;
                    }
                }


            }

        }
        else if(request.equals("Load project"))
        {
            LoadFilePrompter loadProjectPrompter = new LoadFilePrompter(this, request, true);

            if(!loadProjectPrompter.isVisible())
            {
                if(!loadProjectPrompter.getInputText().equals(""))
                {
                    layerDeletion.setEnabled(true);
                    setTransparency.setEnabled(true);
                    alphaTextField.setEnabled(true);
                    applyOp.setEnabled(true);
                    createSelection.setEnabled(true);
                    selectionNaming.setEnabled(true);
                    selectionLayer.setEnabled(true);
                    imageInstance.loadProject(loadProjectPrompter.getInputText());
                    generatedFile=false;
                    menuBar.getMenu(0).getItem(1).setEnabled(true);
                    menuBar.getMenu(0).getItem(2).setEnabled(false);
                    menuBar.getMenu(0).getItem(3).setEnabled(true);
                }

                loadProjectPrompter.dispose();
            }

        }
        else if(request.equals("Save project"))
        {
            SaveProjectPrompter saveProjectPrompter = new SaveProjectPrompter(this, request, true);

            if(!saveProjectPrompter.isVisible())
            {
                if(!saveProjectPrompter.getInputText().equals(""))
                {
                    imageInstance.saveProject(saveProjectPrompter.getInputText());
                    saveProjectPrompter.dispose();
                }

            }

        }

    }


    @Override
    public void itemStateChanged(ItemEvent e) {

        if(e.getSource() instanceof Checkbox)
        {
            if(layerButtonList.contains(e.getSource()))
            {
                int index = layerButtonList.indexOf(e.getSource());
                if(((Checkbox) e.getSource()).getState())
                    imageInstance.getLayers().get(index).setActivity(true);
                else
                    imageInstance.getLayers().get(index).setActivity(false);

                imageInstance.repaint();
                revalidate();
                repaint();
            }

        }

    }

    @Override
    public void mouseClicked(MouseEvent e) {

        if(e.getSource() instanceof Button)
        {
            if(((Button) e.getSource()).getLabel().equals(layerDeletion.getLabel()))
            {
                for (Checkbox cb: layerButtonList) {

                    if(cb.getState())
                    {
                        layerBoxes.remove(cb);
                        imageInstance.deleteLayer(layerButtonList.indexOf(cb));
                        layerButtonList.remove(cb);
                        if(imageInstance.getNumberOfLayers()==0)
                        {
                            layerDeletion.setEnabled(false);
                            setTransparency.setEnabled(false);
                            alphaTextField.setEnabled(false);
                            applyOp.setEnabled(false);
                            createSelection.setEnabled(false);
                            selectionNaming.setEnabled(false);
                            selectionLayer.setEnabled(false);
                            menuBar.getMenu(0).getItem(0).setEnabled(true);
                            menuBar.getMenu(0).getItem(1).setEnabled(false);
                            menuBar.getMenu(0).getItem(2).setEnabled(true);
                            menuBar.getMenu(0).getItem(3).setEnabled(false);
                            alphaTextField.setText("");


                        }

                        imageInstance.repaint();
                        revalidate();
                        repaint();
                    }

                }

               /* for(int i =0;i<imageInstance.getNumberOfLayers();i++)
                {



                }*/
            }
            else if(((Button) e.getSource()).getLabel().equals(applyOp.getLabel()))
            {
                String layers="";
                String operation="";
                boolean requiersConstant=true;
                int constant=-1;
                for(int i=0;i<imageInstance.getOperations().size();i++)
                {
                    if(operationsButtonList.get(i).getState())
                     operation=operationsButtonList.get(i).getLabel();

                }
                requiersConstant = (!((operation.equals("Abs") || operation.equals("Grayscale")||operation.equals("BlackAndWhite")
                        || operation.equals("Inverse") || operation.equals("Log") || operation.equals("Median")) ));

                if(requiersConstant)
                {
                   ConstantPrompter constantPrompter = new ConstantPrompter(this,"Constant prompter",true);
                   constant=constantPrompter.getConstant();
                   constantPrompter.dispose();
                }

                for(int i =0;i<imageInstance.getNumberOfLayers();i++)
                {
                    if(layerButtonList.get(i).getState()) {
                        //op name constant layers
                        layers += Integer.toString(i + 1);

                        ProcessDialog pd = new ProcessDialog(this,"Applying operation",false);

                        if(pd.isVisible())
                        {
                            disableMenues();
                            imageInstance.executeOperation(operation, constant, layers);
                            enableMenues();
                            pd.dispose();

                        }


                    }
                }
                imageInstance.repaint();
                revalidate();
                repaint();
            }
            else if(((Button) e.getSource()).getLabel().equals(setTransparency.getLabel()))
            {
                for(int i =0;i<imageInstance.getNumberOfLayers();i++)
                {
                    if(layerButtonList.get(i).getState()) {
                        //op name constant layers

                        //System.out.println((short)Integer.parseInt(alphaTextField.getText()));
                        imageInstance.setLayerTransparency(i, (short)Integer.parseInt(alphaTextField.getText()));
                        alphaTextField.setText("");
                        imageInstance.repaint();
                        revalidate();
                        repaint();

                    }
                }
            }
            else if(((Button) e.getSource()).getLabel().equals(createSelection.getLabel()))
            {
                String n = selectionNaming.getText();
                String i = selectionLayer.getText();
                if((!n.equals("")) && (!i.equals("")))
                {
                    if(createSelection.getLabel().equals("Create Selection"))
                    {
                        selecting=true;
                        rectangles = new ArrayList<>();
                        createSelection.setLabel("Done");
                    }
                    else if (createSelection.getLabel().equals("Done"))
                    {
                        selecting=false;
                        imageInstance.createSelecton(rectangles,selectionNaming.getText(),Integer.parseInt(selectionLayer.getText()));
                        selectionLayer.setText("");
                        selectionNaming.setText("");
                        createSelection.setLabel("Create Selection");
                        fillSelection.setEnabled(true);
                        deleteSelection.setEnabled(true);
                        redTextField.setEnabled(true);
                        greenTextField.setEnabled(true);
                        blueTextField.setEnabled(true);


                    }
                }

            }
            else if(((Button) e.getSource()).getLabel().equals(fillSelection.getLabel()))
            {
                int selectionNum = imageInstance.getNumberOfSelections();
                if( createSelection.getLabel().equals("Create Selection"))
                {
                    for(int i =0;i<selectionNum;i++)
                    {
                        if(selectionButtons.get(i).getState())
                        {
                            String s =  selectionButtons.get(i).getLabel();


                            Pattern pattern = Pattern.compile("^(.*):.*$");
                            Matcher matcher = pattern.matcher(s);

                            if(matcher.matches())
                            {
                                short r =  (short)Integer.parseInt(redTextField.getText());
                                short g = (short)Integer.parseInt(greenTextField.getText());
                                short b = (short)Integer.parseInt(blueTextField.getText());
                                redTextField.setText("");
                                greenTextField.setText("");
                                blueTextField.setText("");
                                imageInstance.fillSelection(matcher.group(1),r,g,b);
                            }

                        }
                    }
                }
            }
            else if(((Button) e.getSource()).getLabel().equals(deleteSelection.getLabel()))
            {
                for(int i =0;i<imageInstance.getNumberOfSelections();i++)
                {

                    if(selectionButtons.get(i).getState())
                    {
                        String s =  selectionButtons.get(i).getLabel();


                        Pattern pattern = Pattern.compile("^(.*):.*$");
                        Matcher matcher = pattern.matcher(s);

                        if(matcher.matches())
                        {
                            selectionButtons.remove(i);
                            selectionBoxes.remove(i);
                            imageInstance.deleteSelection(matcher.group(1));
                            if(imageInstance.getNumberOfSelections()==0)
                            {
                                fillSelection.setEnabled(false);
                                deleteSelection.setEnabled(false);
                                redTextField.setEnabled(false);
                                greenTextField.setEnabled(false);
                                blueTextField.setEnabled(false);
                            }
                            imageInstance.repaint();
                            revalidate();
                            repaint();

                        }


                    }


                }

            }
            else if(((Button) e.getSource()).getLabel().equals(createOp.getLabel()))
            {
                CompositePrompter cpromter = new CompositePrompter(this,((Button) e.getSource()).getLabel(),true);

                if(!cpromter.isVisible() && !cpromter.isClear())
                {
                    imageInstance.buildCompositeOperation(cpromter.getOpNames(),cpromter.getConstants(),cpromter.getCompositeName());
                    cpromter.dispose();
                    revalidate();
                    repaint();

                }
            }
        }

    }



    @Override
    public void mousePressed(MouseEvent e) {

        if(e.getSource() instanceof Image)
        {

            if(selecting)
            {
                x=e.getX();
                y=e.getY();
            }
        }

    }

    @Override
    public void mouseReleased(MouseEvent e) {

        if(e.getSource() instanceof Image)
        {
                if(selecting)
                {
                    x1=e.getX();
                    y1=e.getY();
                    //rechtangles.add(new Rechtangle(y,x,x1-x,y1-y));
                    rectangles.add(new Rechtangle(x,y,y1-y,x1-x));

                }
        }


    }

    @Override
    public void mouseEntered(MouseEvent e) {

    }

    @Override
    public void mouseExited(MouseEvent e) {

    }

    @Override
    public void keyTyped(KeyEvent e) {

        if(e.getSource() instanceof JFormattedTextField )
        {
            if(e.getSource().equals(alphaTextField) || e.getSource().equals(redTextField)
            || e.getSource().equals(greenTextField) || e.getSource().equals(blueTextField))
            {
                if(alphaTextField.getText().length() ==3)
                    e.consume();
                else if(redTextField.getText().length()==3)
                    e.consume();
                if(greenTextField.getText().length()==3)
                    e.consume();
                if(blueTextField.getText().length()==3)
                    e.consume();



            }
        }

    }

    @Override
    public void keyPressed(KeyEvent e) {

    }

    @Override
    public void keyReleased(KeyEvent e) {

    }
}
