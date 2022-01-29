package Picture;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.Vector;

public class Layer {

     Vector<Vector<Pixel>> pixelMap ;
    private int height;
    private int width;
    private boolean active = true;
    private boolean hasSelection = false;
    private String sourceFile;
    Selection selection=null;


    public Layer(int _height, int _width)
    {
        this.height=_height;
        this.width=_width;

        this.pixelMap= new Vector<Vector<Pixel>>(this.height);

        for(int i =0; i<this.height;i++) {

            Vector<Pixel> row = new Vector<Pixel>(this.width);

            for (int j = 0; j < this.width; j++) {

                row.add(new Pixel());

            }

            pixelMap.add(row);

        }
    }

    public Layer(String _sourceFile, int _height, int _width, ArrayList<Short> pixels) //metoda za bmp slike
    {
        this.sourceFile=_sourceFile;
        this.height=_height;
        this.width=_width;
        this.pixelMap= new Vector<>(this.height);
        int index =0;

       // if(bitsPerPixel==32)
       // {


            for (int i =0; i< this.height;i++) {

                Vector<Pixel> row = new Vector<>(this.width);


                for ( int j =0; j< this.width; j++) {


                    row.add(new Pixel(pixels.get(index), pixels.get(index+1), pixels.get(index+2), pixels.get(index+3)));
                    index+=4;

                }
                pixelMap.add(row);
            }
      //  }

//        if(bitsPerPixel==24)
//        {
//            for (int i =0; i< this.height;i++) {
//
//                Vector<Pixel> row = new Vector<>(this.width);
//
//
//                for ( int j =0; j< this.width; j++) {
//
//                    row.add(new Pixel(pixels.get(index), pixels.get(index+1), pixels.get(index+2), (short)255));
//                    index+=3;
//
//                }
//                pixelMap.add(row);
//            }
//        }
    }

    public Layer(String _sourceFile,int _height, int _width, ArrayList<Short> pxs, String type)
    {
        this.sourceFile=_sourceFile;
        this.height=_height;
        this.width=_width;
        this.pixelMap= new Vector<>(this.height);
        int index =0;

        if (type.equals("BLACKANDWHITE"))
        {
            for (int i =0;i<this.height;i++)
            {
                Vector<Pixel> row = new Vector<Pixel>(this.width);

                for (int j = 0; j<this.width;j++)
                {
                    //row.add(new Pixel(pxs.get(index)<<8, pxs.get(index)<<8, pxs.get(index)<<8, (short) 255));
                    index++;
                }
                this.pixelMap.add(row);
            }
        }
       else if (type.equals("GRAYSCALE"))
       {
           for (int i =0;i<this.height;i++)
           {
               Vector<Pixel> row = new Vector<Pixel>(this.width);

               for (int j = 0; j<this.width;j++)
               {
                   row.add(new Pixel(pxs.get(index),pxs.get(index),pxs.get(index),(short) 255));
                   index++;
               }
               this.pixelMap.add(row);
           }
       }
       else if (type.equals("RGB"))
       {
           for (int i =0;i<this.height;i++)
           {
               Vector<Pixel> row = new Vector<Pixel>(this.width);

               for (int j = 0; j<this.width;j++)
               {
                   row.add(new Pixel(pxs.get(index),pxs.get(index+1),pxs.get(index+2),(short) 255));
                   index+=3;
               }
               this.pixelMap.add(row);
           }
       }
       else if (type.equals("BLACKANDWHITE_ALPHA"))
       {
           for (int i =0;i<this.height;i++)
           {
               Vector<Pixel> row = new Vector<Pixel>(this.width);

               for (int j = 0; j<this.width;j++)
               {
                    //row.add(new Pixel(pxs.get(index)<<8,pxs.get(index)<<8,pxs.get(index)<<8, pxs.get(index+1)<<8));
                    index+=2;

               }
               this.pixelMap.add(row);
           }
       }
       else if (type.equals("GRAYSCALE_ALPHA"))
       {
           for (int i =0;i<this.height;i++)
           {
               Vector<Pixel> row = new Vector<Pixel>(this.width);

               for (int j = 0; j<this.width;j++)
               {
                   row.add(new Pixel(pxs.get(index),pxs.get(index),pxs.get(index),pxs.get(index+1)));
                   index+=2;
               }
               this.pixelMap.add(row);
           }
       }
       else if (type.equals("RGB_ALPHA"))
       {
           for (int i =0;i<this.height;i++)
           {
               Vector<Pixel> row = new Vector<Pixel>(this.width);

               for (int j = 0; j<this.width;j++)
               {
                   row.add(new Pixel(pxs.get(index),pxs.get(index+1),pxs.get(index+2),pxs.get(index+3)));
                   index+=4;
               }
               this.pixelMap.add(row);
           }
       }
    }

    public String getSourceFile() {return  this.sourceFile;}

    public void resize (int newHeight, int newWidth)
    {
        Vector<Vector<Pixel>> newPixelMap = new Vector<>(newHeight);

        int oldHeight = this.height;
        int oldWidth = this.width;

        this.height=newHeight;
        this.width=newWidth;

        for (int i =0;i<newHeight;i++) {

            Vector<Pixel> row = new Vector<>(newWidth);
            for (int j = 0; j < newWidth; j++) {

                if ((j <= (oldWidth - 1)) && (i <= (oldHeight - 1)))
                    row.add(pixelMap.get(i).get(j));
                else
                    row.add(new Pixel());
            }
            newPixelMap.add(row);
        }

        this.pixelMap.clear();
        this.pixelMap=newPixelMap;

    }

    public int getHeight () {return  this.height;}

    public int getWidth() { return this.width; }

    public boolean isActive() { return  this.active; }

    public void setActivity(boolean newState) { this.active = newState; }

    public  boolean getActivity() {return this.active;}

    public void setSelection(Selection s) {this.selection=s;}

    public boolean selectionState() {return  this.hasSelection;}

    public Selection getSelection() {return  this.selection;}

    public void fillSelection (short red, short green, short blue )
    {


        for (Rechtangle r : this.selection.getRechtangles()) {

            for (int i = r.getY(); i < (r.getY()+r.getHeight());i++)
                for (int j = r.getX(); j < (r.getX()+r.getWidth()); j++) {

                    this.pixelMap.get(i).get(j).setRed(red);
                    this.pixelMap.get(i).get(j).setGreen(green);
                    this.pixelMap.get(i).get(j).setBlue(blue);

                }
        }
    }

    public Vector<Vector<Pixel>> getPixelMap() {

        Vector<Vector<Pixel>> copyMap = new Vector<>(this.height);

        for (Vector<Pixel> row: pixelMap) {

            Vector<Pixel> copy = new Vector<>(this.width);

            for (Pixel p: row) {
                copy.add( new Pixel(p));
            }
            copyMap.add(copy);

        }

        //vracace kopiju originalne mape
        return copyMap;
    }



    public void setAlpha(short alpha)
    {
        for (Vector<Pixel> rows: pixelMap) {

            for (Pixel p: rows) {

                p.setAlpha(alpha);
            }

        }
    }

}

