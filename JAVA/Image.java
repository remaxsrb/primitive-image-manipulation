package Picture;

import java.awt.*;
import java.io.IOException;
import java.util.*;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import GUI.Aplikacija;
import GUI.ErrorWindow;
import org.json.simple.*;

public class Image extends Canvas {

    private Vector<Layer> layers = new Vector<Layer>();
    private Map<String,Selection>  selections = new HashMap<>();
    private int numberOfLayers = 0;
    private int numberOfSelections = 0;
    private Set<String> operacije = new HashSet<String>(); //skup koji sadrzi imena operacija koja ce se slati c++ kodu
    Aplikacija aplikacija;

    private Vector<Vector<Pixel>> moldLayers(int height, int width)
    {

        Vector<Vector<Pixel>> moldedPxs =null;
        Stack<Layer> layerStack = new Stack<>();
        Vector<Layer> reverseLayers = new Vector<>();

        for (Layer l:layers) {
            layerStack.push(l);
        }
        while(!layerStack.empty())
            reverseLayers.add(layerStack.pop());

        int count = 0;

        for (Layer l:reverseLayers) {

            Vector<Vector<Pixel>> lpxsmap = l.getPixelMap();

            if(count ==0)
            {
                if(l.getActivity())
                {
                    moldedPxs=lpxsmap;
                    count++;
                }

            }
            else
                {
                    if(l.getActivity())
                    {
                        short R=0;
                        short G=0;
                        short B=0;

                        for (int i = 0; i < height ; i++) {
                            for (int j = 0; j < width; j++) {


                                double a0 = (double)moldedPxs.get(i).get(j).getAlpha()/255;
                                double a1 = (double)lpxsmap.get(i).get(j).getAlpha()/255;

                                double new_alpha = a0 + (1-a0)*a1;

                                short A = (short)(Math.round(new_alpha*255));

                                if(a0==0)
                                {

                                    R = lpxsmap.get(i).get(j).getRed();
                                    G = lpxsmap.get(i).get(j).getGreen();
                                    B = lpxsmap.get(i).get(j).getBlue();

                                }
                                else
                                    {
                                        //x0 je element iz moldedPXS a x1 element iz postojecih slojeva

                                        double r0 = moldedPxs.get(i).get(j).getRed();
                                        double r1 = lpxsmap.get(i).get(j).getRed();


                                        R = (short)(Math.round(r0*a0/new_alpha + r1*(1-a0)*a1/new_alpha));
                                       //------------------------------------------------
                                        double g0 = moldedPxs.get(i).get(j).getGreen();
                                        double g1 = lpxsmap.get(i).get(j).getGreen();
                                        G = (short)(Math.round(g0*a0/new_alpha+g1*(1-a0)*a1/new_alpha));
                                       //------------------------------------------------
                                        double b0 = moldedPxs.get(i).get(j).getBlue();
                                        double b1 = lpxsmap.get(i).get(j).getBlue();
                                        B = (short)(Math.round(b0*a0/new_alpha+b1*(1-a0)*a1/new_alpha));

                                    }

                                //ovde cu setovati piksele;
                                moldedPxs.get(i).get(j).setRed(R);
                                moldedPxs.get(i).get(j).setGreen(G);
                                moldedPxs.get(i).get(j).setBlue(B);
                                moldedPxs.get(i).get(j).setAlpha(A);


                            }
                        }
                        count++;
                    }
                }

        }




        return  moldedPxs;
    }

    public void paint(Graphics g)
    {


        int height = layers.lastElement().getHeight();
        int width = layers.lastElement().getWidth();

        Vector<Vector<Pixel>> moldedPixels = moldLayers(height,width);


        int red;
        int green;
        int blue;
        int alpha;

        for(int i =0 ;i< height;i++)
            for(int j =0;j< width;j++)
            {
                red = moldedPixels.get(i).get(j).getRed();
                green = moldedPixels.get(i).get(j).getGreen();
                blue = moldedPixels.get(i).get(j).getBlue();
                alpha = moldedPixels.get(i).get(j).getAlpha();

                g.setColor(new Color(red,green,blue,alpha));
                g.drawLine(j,i,j,i);
            }

        setSize(layers.lastElement().getWidth(),layers.lastElement().getHeight());

    }

    private void clearProject()
    {
        this.layers.clear();
        this.numberOfSelections=0;
        this.numberOfLayers=0;
    }

     void loadLayer(Layer l)
    {
        this.layers.add(l);
        this.numberOfLayers++;
        paint(getGraphics());
        //aplikacija.addLayers();
        aplikacija.addLayers();
        aplikacija.revalidate();
        aplikacija.repaint();


    }

    public Image(Aplikacija app)
    {

        this.aplikacija = app;
        //setBackground(Color.black);

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
    }

    void resizeLayers(Layer newLayer)
    {

        //Odradi JNI metodu ne zajebavaj se sa ovim u javi

        if((layers.lastElement().getHeight()>newLayer.getHeight())&&(layers.lastElement().getWidth()>newLayer.getWidth()))
        {
            int newHeight = layers.lastElement().getHeight();
            int newWidth = layers.lastElement().getWidth();
            newLayer.resize(newHeight,newWidth);

        }
        else if ((layers.lastElement().getHeight()>newLayer.getHeight())&&(layers.lastElement().getWidth()<newLayer.getWidth()))
        {
            int newHeight = layers.lastElement().getHeight();
            int newWidth = newLayer.getWidth();

            newLayer.resize(newHeight,newWidth);
            for (Layer l:layers) {
                l.resize(newHeight,newWidth);
            }
        }
        else if ((layers.lastElement().getHeight()<newLayer.getHeight())&&(layers.lastElement().getWidth()<newLayer.getWidth()))
        {
            int newHeight = newLayer.getHeight();
            int newWidth = newLayer.getWidth();

            for (Layer l:layers) {
                l.resize(newHeight,newWidth);
            }
        }
        else if ((layers.lastElement().getHeight()<newLayer.getHeight()) && ((layers.lastElement().getWidth()>newLayer.getWidth())))
        {
            int newHeight = newLayer.getHeight();
            int newWidth =  layers.lastElement().getWidth();

            newLayer.resize(newHeight,newWidth);

            for (Layer l:layers) {
                l.resize(newHeight,newWidth);
            }

        }

    }

    public Set<String> getOperations() {
        return operacije;
    }

    public void addLayer(int height, int width)
    {
        this.layers.add(new Layer(height,width));
    }
    public void addLayer(String inputFileName)   {
        //regexom razdvojiti format i poslati u odgovarajuci formater


        Pattern regex = Pattern.compile("[^.]*.(.*)");
        Matcher matcher = regex.matcher(inputFileName);

        if (matcher.matches())
        {
           if(matcher.group(1).equals("bmp"))
           {
               BMPFormater formater = new BMPFormater();
               formater.readFile(inputFileName, this);
           }
           else if (matcher.group(1).equals("pam"))
           {
               PAMFormater formater = new PAMFormater();
               formater.readFile(inputFileName,this);
           }
           else new ErrorWindow(aplikacija,"Format not supported!",true);
        }


    }
    public void deleteLayer(int index)
    {
        if((index>=0)&&(index<this.numberOfLayers))
        {
            if(this.layers.get(index).getSelection()!=null)
            {
                deleteSelection(this.layers.get(index).getSelection().getName());
            }

            this.layers.remove(index);
            this.numberOfLayers--;
            aplikacija.addLayers();
        }
    }

    public void setLayerTransparency(int index, short alpha)
    {
        layers.get(index).setAlpha(alpha);
    }
    public void createSelecton(ArrayList<Rechtangle> rechtangles, String name, int layerNo)
    {
        if (layerNo > this.numberOfLayers)
            System.out.println("Error ne postojeci sloj");
        else if (layerNo<=0)
            System.out.println("Error: slika ima bar jedan sloj");
        else
            {
                int designatedLayerWidth = this.layers.get(layerNo-1).getWidth();
                int designatedLayerHeight = this.layers.get(layerNo-1).getHeight();

                rechtangles.removeIf(rechtangle -> ((rechtangle.getX()>designatedLayerWidth)||(rechtangle.getY()>designatedLayerHeight)));

                for (Rechtangle r: rechtangles) {
                    if((r.getHeight()+r.getY())>designatedLayerHeight)

                        r.setHeight(designatedLayerHeight-r.getY());

                    if ((r.getWidth()+r.getX() > designatedLayerWidth))

                        r.setWidth(designatedLayerWidth-r.getX());

                    //r.setY(designatedLayerHeight-r.getY()-1);
                }

                Selection s = new Selection(rechtangles,name,layerNo-1);
                this.selections.put(s.getName(),s);

                this.getLayers().get(layerNo-1).setSelection(this.selections.get(name));
                this.numberOfSelections++;


            }
        aplikacija.addSelections();
        aplikacija.revalidate();
        aplikacija.repaint();
    }
    public void fillSelection(String name, short red, short green, short blue)
    {
        if(selections.get(name)!=null)
        {
            this.layers.get(selections.get(name).getLayerNo()).fillSelection(red,green,blue);

            repaint();
            aplikacija.revalidate();
            aplikacija.repaint();
        }
        else
            System.out.println("Error ne postoji selekcija");
    }
    public void deleteSelection(String name)
    {
        if(selections.get(name)!=null)
        {
            selections.remove(name);
            for (Layer l:layers) {

                if(l.getSelection().getName().equals(name))
                    l.setSelection(null);
            }
            this.numberOfSelections--;
        }

        else
            System.out.println("Error selecija ne postoji");
    }

    public void executeOperation(String name, int constant, String layers)
    {

        if(operacije.contains(name))
        {
            JSONFormater formater = new JSONFormater();
            String operation = name+".json";
            String intermediateJSON = "C:\\Users\\mjova\\IdeaProjects\\POOP_Project_2020\\intermediateJSON.json";
            formater.serializeOperation(name,constant,layers);
            try {
                formater.serialize("intermediateJSON",this);
                clearProject();

            } catch (IOException e)
            {
                e.printStackTrace();
            }

            String executableCPP = "C:\\Users\\mjova\\source\\repos\\POOP_project_2020\\Debug\\executeOperation.exe";
            String operationAbsPath = "C:\\Users\\mjova\\IdeaProjects\\POOP_Project_2020\\"+operation;

            String arguments = executableCPP + " " + intermediateJSON + " " + operationAbsPath;

            Runtime runtime = Runtime.getRuntime();

            try {
                System.out.println("Sending information...");
                Process process = runtime.exec(arguments);
                System.out.println("Executing operation...");
                process.waitFor();
                System.out.println("Operation executed!");
            } catch (InterruptedException | IOException e)
            {
                e.printStackTrace();
            }

            formater.readFile("intermediateJSON",this);


            /*
             * 1. exe fajl
             * 2. slika nad kojom se vrsi operacija
             * 3. Operacija
             * 4. Json fajl u kom se snima izmenjen slika
             * */


        }


    }

    public void saveProject(String targetFileName)  {

        //upisati projekat u json

        JSONFormater formater = new JSONFormater();
        try {
            formater.serialize(targetFileName,this);
        } catch (IOException e)
        {
            //
        }


    }
    public void loadProject(String sourceFileName)  {
        //ucitati projekat iz jsona
        Formater formater = new JSONFormater();
        formater.readFile(sourceFileName,this);

    }

    public void buildCompositeOperation(ArrayList<String> opNames, ArrayList<Integer> constants, String compositeName)
    {
        if(!operacije.contains(compositeName))
        {
            /*
            *
            * serijalizujem slozenu operaciju u json
            * u c++ je ubacujem u mapu
            * dodajem njeno ime u skup operacija
            * */

            JSONFormater formater = new JSONFormater();
            formater.saveCompositeOp(opNames,constants,compositeName);

            operacije.add(compositeName);
            aplikacija.addOperations();

            String executableCPP = "C:\\Users\\mjova\\source\\repos\\POOP_project_2020\\Debug\\loadComposite.exe";
            String compositeJSON = "C:\\Users\\mjova\\IdeaProjects\\POOP_Project_2020\\"+compositeName+".json";

            String arguments = executableCPP+" "+compositeJSON;

            Runtime runtime = Runtime.getRuntime();

            try {

                System.out.println("Sending composite operation info");
                Process process = runtime.exec(arguments);
                System.out.println("Loading composite operation...");
                process.waitFor();
                System.out.println("Composite op is loaded!");

            } catch (IOException | InterruptedException e) {
                e.printStackTrace();
            }


        }
    }

    public void saveImage(String targetFileName) {
        //snimiti sliku u bmp ili pam

        String format="";
        String jsonBridge="";

        Pattern regex = Pattern.compile("^(.+).(bmp|pam)$");
        Matcher matcher = regex.matcher(targetFileName);

        if (matcher.matches())
        {
            jsonBridge = matcher.group(1);
            format=matcher.group(2);

            if(format.equals("bmp"))
            {
                BMPFormater formater = new BMPFormater();

                formater.writeToFile(targetFileName,jsonBridge,this);
            }
            else if (format.equals("pam"))
            {
                PAMFormater formater = new PAMFormater();
                formater.writeToFile(targetFileName,jsonBridge,this);
            }
        }



        //na osnovu kliknute opcije ce se odrediti koji formater ce se pozvati




    }

    public int getNumberOfLayers() {
        return numberOfLayers;
    }

    public int getNumberOfSelections() {
        return numberOfSelections;
    }

    public Vector<Layer> getLayers() {
        return layers;
    }

    public Map<String, Selection> getSelections() {
        return selections;
    }


}
