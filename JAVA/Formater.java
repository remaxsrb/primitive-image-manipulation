package Picture;

import java.io.IOException;

public interface Formater {

     void readFile(String sourceFileName, Image image) ;
     void writeToFile(String targetFileName, String jsonBridge ,Image image);
}
