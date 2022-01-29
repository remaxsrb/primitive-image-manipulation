package Picture;

import java.io.*;
import java.util.ArrayList;
import java.util.Stack;
import java.util.Vector;
import java.util.concurrent.atomic.AtomicInteger;
import java.util.regex.Matcher;
import java.util.regex.Pattern;
import java.util.stream.Stream;

import GUI.ErrorWindow;
import org.json.simple.*;
public class JSONFormater implements Formater {

    private int NS;
    private int NL;
    private int depth;

    private int height;
    private int width;
    private String fileName;

    private ArrayList<Short> pixels= new ArrayList<>();


    @Override
    public void readFile(String sourceFileName, Image image)   {



        try {

            FileReader reader = new FileReader(new File(sourceFileName));
            BufferedReader buffreader = new BufferedReader(reader);

            AtomicInteger count = new AtomicInteger();
            Stream<String> JSONLines = buffreader.lines();

            JSONLines.forEach(JSONLine->
            {
                int counter = count.incrementAndGet();

                if(counter ==1)
                {
                    Pattern metaData1 = Pattern.compile("^.\"NS\":(.*),\"NL\":(.*),\"Depth\":(.*)}$");
                    Matcher matcher = metaData1.matcher(JSONLine);

                    if(matcher.matches())
                    {
                        this.NS = Integer.parseInt(matcher.group(1));
                        this.NL = Integer.parseInt(matcher.group(2));
                        this.depth = Integer.parseInt(matcher.group(3));

                    }
                }


                else if ((counter>=2)&&(counter<=(NL*2+1)))
                {
                    if(counter%2==0)
                    {
                        if (sourceFileName.equals("intermediateJSON.json"))
                        {
                            Pattern metaData1 = Pattern.compile("^.\"File\":(.*),\"Height\":(.*),\"Width\":(.*)}$");
                            Matcher matcher = metaData1.matcher(JSONLine);

                            if(matcher.matches())
                            {
                                this.fileName=matcher.group(1);
                                this.height = Integer.parseInt(matcher.group(2));
                                this.width = Integer.parseInt(matcher.group(3));
                            }
                        }
                        else
                            {
                                Pattern metaData1 = Pattern.compile("^.\"Height\":(.*),\"File\":(.*),\"Width\":(.*)}$");
                                Matcher matcher = metaData1.matcher(JSONLine);

                                if(matcher.matches())
                                {


                                    this.height = Integer.parseInt(matcher.group(1));
                                    this.fileName=matcher.group(2);
                                    this.width = Integer.parseInt(matcher.group(3));
                                }
                            }

                    }
                    else
                        {
                            Pattern metaData1 = Pattern.compile("[\\d]+");
                            Matcher matcher = metaData1.matcher(JSONLine);

                            while (matcher.find())
                                pixels.add((short)Integer.parseInt(matcher.group(0)));

                            Layer layer  = new Layer(fileName,height,width,pixels);

                            Stack<Short> shortStack = new Stack<>();
                            Stack<Pixel> pxsStack = new Stack<>();
                            Stack<Vector<Pixel>> pixelVStack = new Stack<>();
                            pixels.clear();

                            for (Vector<Pixel> pixelVector: layer.getPixelMap())
                            {
                                pixelVStack.push(pixelVector);

                            }

                            while (!pixelVStack.empty())
                            {
                                for (Pixel p : pixelVStack.pop())
                                {

                                    pxsStack.push(p);

                                }
                            }

                            while(!pxsStack.empty())
                            {
                                Pixel p = pxsStack.pop();
                                shortStack.push(p.getAlpha());
                                shortStack.push(p.getBlue());
                                shortStack.push(p.getGreen());
                                shortStack.push(p.getRed());
                            }

                            while(!shortStack.empty())
                                pixels.add(shortStack.pop());
                            Layer newLayer  = new Layer(fileName,height,width,pixels);

                            image.loadLayer(newLayer);
                            pixels.clear();
                        }
                }

                else if (counter>(NL*2+1)&&(counter<=(NL*2+1+NS)))
                {
                    Pattern p = Pattern.compile("^.\"Layer\":(.*),\"Name\":\"([A-Za-z0-9]*)\"}(.*)$");
                    Matcher matcher = p.matcher(JSONLine);

                    ArrayList<Rechtangle> rechtangles = new ArrayList<>();
                    String rechtanglesString="";
                    int layerNo=0;
                    String name="";
                    if(matcher.matches())
                    {
                        layerNo=Integer.parseInt(matcher.group(1));
                        name=matcher.group(2);
                        rechtanglesString=matcher.group(3);

                    }
                    //System.out.println(rechtangleString);
                    Pattern rechtanglesPattern = Pattern.compile("(\\{\"x\":([0-9]+),\"y\":([0-9]+),\"Height\":([0-9]+),\"Width\":([0-9]+)})");
                    Matcher rsmatcher = rechtanglesPattern.matcher(rechtanglesString);

                    while(rsmatcher.find())
                    {
                        String rechtangle = rsmatcher.group(0);

                        Pattern rechtanglePattern = Pattern.compile("\\{\"x\":([0-9]+),\"y\":([0-9]+),\"Height\":([0-9]+),\"Width\":([0-9]+)}");
                        Matcher rmatcher = rechtanglePattern.matcher(rechtangle);

                        if(rmatcher.matches())
                        {
                            int x = Integer.parseInt(rmatcher.group(1));
                            int y = Integer.parseInt(rmatcher.group(2));
                            int rheight = Integer.parseInt(rmatcher.group(3));
                            int rwidth = Integer.parseInt(rmatcher.group(4));

                            rechtangles.add(new Rechtangle(x,y,rheight,rwidth));
                        }


                    }


                    image.createSelecton(rechtangles,name,layerNo);

                }


            });

            buffreader.close();


        }catch (IOException e)
        {
            new ErrorWindow(image.aplikacija,"File not found!",true);
        }


    }

    @Override
    public void writeToFile(String targetFileName , String jsonBridge ,Image image)  {

    /* metoda write to file ce imati prazno  telo jer nece koristiti
    dodatni parametar json bridge tj nema smisla da ga koristi formater koji ga kreira */

    }

    public void serialize(String targetFileName ,Image image)   throws IOException
    {
        String outputFile= targetFileName+".json";

        FileWriter file = new FileWriter(outputFile);

        try {

            byte bitsPerPixel = 32;

            JSONObject jsonObject = new JSONObject();

            int activeLayers=0;

            for (Layer l: image.getLayers()) {

                if(l.getActivity())
                    activeLayers++;

            }

            jsonObject.put("NS", image.getNumberOfSelections());
            jsonObject.put("NL", activeLayers);
            jsonObject.put("Depth", bitsPerPixel);



            file.write(jsonObject.toJSONString());
            file.write("\n");

        } catch (IOException e)
        {
            //
        }

        try {

            for (Layer l: image.getLayers()) {

                if(l.getActivity())
                {

                    JSONObject jsonObject1 = new JSONObject();
                    jsonObject1.put("File",l.getSourceFile());
                    jsonObject1.put("Height", l.getHeight());
                    jsonObject1.put("Width", l.getWidth());

                    file.write(jsonObject1.toJSONString());

                    file.write("\n");

                    JSONArray jvec = new JSONArray();
                    Stack<Vector<Pixel>> rowStack = new Stack<>();

                    for (Vector<Pixel> pixelVector: l.pixelMap)
                        rowStack.push(pixelVector);

                    while (!rowStack.empty())
                    {
                        for (Pixel p: rowStack.pop()) {

                            jvec.add(p.getRed());
                            jvec.add(p.getGreen());
                            jvec.add(p.getBlue());
                            jvec.add(p.getAlpha());

                        }
                    }

                    file.write(jvec.toJSONString());
                    file.write("\n");
                }

            }
        } catch (IOException e)
        {
            //
        }


        try {

            if(image.getNumberOfSelections()>0)
            {
                for (Selection s: image.getSelections().values()) {

                    if(image.getLayers().get(s.getLayerNo()-1).getActivity())
                    {
                        JSONObject jsonObject2 = new JSONObject();

                        jsonObject2.put("Name", s.getName());
                        jsonObject2.put("Layer", s.getLayerNo());

                        file.write(jsonObject2.toJSONString());

                        for (Rechtangle r: s.getRechtangles()) {

                            JSONObject jsonObject3 = new JSONObject();

                            jsonObject3.put("Height", r.getHeight());
                            jsonObject3.put("Width", r.getWidth());
                            jsonObject3.put("x", r.getX());
                            jsonObject3.put("y", r.getY());
                            file.write(jsonObject3.toJSONString());

                        }
                        file.write("\n");


                    }
                    }




            }

        } catch (IOException e)
        {
            //
        }
        file.close();
    }

    public void serializeOperation(String name, int constant, String layers)
    {

        String JSONDest = name + ".json";

        try {
            FileWriter file = new FileWriter(JSONDest);

            JSONObject jobj = new JSONObject();

            jobj.put("Name",name);
            jobj.put("const",constant);
            jobj.put("Layers",layers);

            file.write(jobj.toJSONString());

            file.close();
        } catch (IOException e)
        {
            //
        }

    }

    public void saveCompositeOp(ArrayList<String> opNames, ArrayList<Integer> constants, String compositeName)
    {
        String JSONopFile = compositeName + ".json";

        try
        {

            FileWriter file = new FileWriter(JSONopFile);

            JSONObject jobj = new JSONObject();
            jobj.put("CompositeName",compositeName);
            file.write(jobj.toJSONString());

            for(int i =0;i<opNames.size();i++)
            {
                JSONObject jobj1 = new JSONObject();
                jobj1.put("Constant",constants.get(i));
                jobj1.put("Name", opNames.get(i));
                file.write(jobj1.toJSONString());
            }
            file.close();

        } catch (IOException e)
        {
            //
        }



    }
}


