package Picture;

import GUI.ErrorWindow;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class PAMFormater implements Formater{
    @Override
    public void readFile(String sourceFileName, Image image)   {

        String abspath = "C:\\Users\\mjova\\IdeaProjects\\POOP_Project_2020\\src\\Picture\\" + sourceFileName;

        int width =0;
        int height = 0;
        ArrayList<Short> pixels = new ArrayList<>();
        String type = "";

        int bitsPerPixel =0;
        int maxVal =0;

        try
        {
            InputStream inputFile = new FileInputStream(abspath);

            int byte_read;

            String [] readAtributes = {"","","","","","",""};

            try {

                for (int i = 0; i < 7; i++) {
                    StringBuilder readBytes = new StringBuilder();
                    while ((byte_read = inputFile.read()) != 10)
                        readBytes.append((char) byte_read);
                    readAtributes[i] = readBytes.toString();
                }

                Pattern widthPattern =  Pattern.compile("^WIDTH (.*)$");
                Matcher widthMatcher = widthPattern.matcher(readAtributes[1]);
                if(widthMatcher.matches())
                    width=Integer.parseInt(widthMatcher.group(1));

                Pattern heightPattern = Pattern.compile("^HEIGHT (.*)$");
                Matcher heightMatcher = heightPattern.matcher(readAtributes[2]);
                if(heightMatcher.matches())
                    height= Integer.parseInt(heightMatcher.group(1));

                Pattern depthPattern = Pattern.compile("^DEPTH (.*)$");
                Matcher depthMatcher = depthPattern.matcher(readAtributes[3]);
                if(depthMatcher.matches())
                    bitsPerPixel= Integer.parseInt(depthMatcher.group(1));

                Pattern maxvalPattern = Pattern.compile("^MAXVAL (.*)$");
                Matcher maxvalMatcher = maxvalPattern.matcher(readAtributes[4]);
                if(maxvalMatcher.matches())
                    maxVal= Integer.parseInt(maxvalMatcher.group(1));

                Pattern tupplePattern = Pattern.compile("^TUPLTYPE (.*)$");
                Matcher tuppleMatcher = tupplePattern.matcher(readAtributes[5]);
                if(tuppleMatcher.matches())
                   type=tuppleMatcher.group(1);

                int byte_read1;

                while((byte_read1=inputFile.read())!=-1)
                 pixels.add((short)byte_read1);

                image.loadLayer(new Layer(sourceFileName,height,width,pixels,type));

            } catch (IOException e) {new ErrorWindow(image.aplikacija,"File could not be opened!",true);}
        }
        catch (FileNotFoundException e)
        {
            new ErrorWindow(image.aplikacija,"File not found!",true);
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
            System.out.println("Starting process");
            Process process = runtime.exec(arguments);
            System.out.println("Waiting for completion");
            process.waitFor();
            System.out.println("Action completed");
        } catch (InterruptedException | IOException e) {
            e.printStackTrace();
        }


    }
}

