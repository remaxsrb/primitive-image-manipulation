package Picture;

import GUI.ErrorWindow;

import javax.imageio.ImageIO;
import java.awt.*;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.util.ArrayList;

public class BMPFormater implements Formater{
    @Override
    public void readFile(String sourceFileName, Image image) {

        ArrayList<Short> pixels = new ArrayList<>();
        try {


           BufferedImage img = ImageIO.read(getClass().getResource(sourceFileName));

            for (int i =0;i<img.getHeight();i++)
                for (int j =0;j<img.getWidth();j++)
                {
                    Color c = new Color(img.getRGB(j,i),true);
                    pixels.add((short)(c.getRed()));
                    pixels.add((short)(c.getGreen()));
                    pixels.add((short)(c.getBlue()));
                    pixels.add((short)(c.getAlpha()));
                }

            Layer newLayer = new Layer(sourceFileName,img.getHeight(),img.getWidth(),pixels);

            if(image.getNumberOfLayers()!=0)
                image.resizeLayers(newLayer);

          image.loadLayer(newLayer);

        } catch (IOException e)
        {
            new ErrorWindow(image.aplikacija,"Format not supported by API!",true);
        }



    }

    @Override
    public void writeToFile(String targetFileName, String jsonBridge  ,Image image)   {

        image.saveProject(jsonBridge);

        String jsonbridgeFull= jsonBridge+".json";


        String targetAbspath = "C:\\Users\\mjova\\IdeaProjects\\POOP_Project_2020\\" +targetFileName;
        String jsonBridgeAbsPath = "C:\\Users\\mjova\\IdeaProjects\\POOP_Project_2020\\" +jsonbridgeFull;
        String executableCPP = "C:\\Users\\mjova\\source\\repos\\POOP_project_2020\\Debug\\saveImage.exe";
        String arguments = executableCPP+" "+jsonBridgeAbsPath+" "+targetAbspath;

        Runtime runtime = Runtime.getRuntime();


        try {
            System.out.println("Sending image information");
            Process process = runtime.exec(arguments);
            System.out.println("Waiting for completion");
            process.waitFor();
            System.out.println("Image saved");
        } catch (InterruptedException | IOException e) {
            e.printStackTrace();
        }


    }
}
