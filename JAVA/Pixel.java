package Picture;

import java.util.ArrayList;
import java.util.Collections;

public class Pixel {

    private static final short MIN_PIXEL_VALUE = 0;
    private static final short MAX_PIXEL_VALUE = 255;

    private static final short MIN_TRANSPARENCY = 255;
    private static final short MAX_TRANSPARENCY = 0;

    private short red;
    private short green;
    private short blue;
    private short alpha;

    public Pixel()
    {
        this.red=MIN_PIXEL_VALUE;
        this.green=MIN_PIXEL_VALUE;
        this.blue=MIN_PIXEL_VALUE;
        this.alpha=MAX_TRANSPARENCY;
    }

    public Pixel (short _red, short _green, short _blue, short _alpha)
    {
        this.red=_red;
        this.green=_green;
        this.blue=_blue;
        this.alpha=_alpha;
    }

    public Pixel(Pixel px)
    {
        this.red=px.red;
        this.green=px.green;
        this.blue=px.blue;
        this.alpha=px.alpha;
    }

    public short getRed() {return this.red;}

    public short getGreen() { return this.green;}

    public short getBlue() { return this.blue; }

    public short getAlpha() {return this.alpha;}

    public void setRed (short newRed)
    {
        if(newRed>MAX_PIXEL_VALUE)
            this.red=MAX_PIXEL_VALUE;
        else if (newRed<MIN_PIXEL_VALUE)
            this.red=MIN_PIXEL_VALUE;
        else
            this.red=newRed;
    }
    public void setGreen (short newGreen)
    {
        if(newGreen>MAX_PIXEL_VALUE)
            this.green=MAX_PIXEL_VALUE;
        else if (newGreen<MIN_PIXEL_VALUE)
            this.green=MIN_PIXEL_VALUE;
        else
             this.green=newGreen;
    }
    public void setBlue(short newBlue) {
        if(newBlue>MAX_PIXEL_VALUE)
            this.blue=MAX_PIXEL_VALUE;
        else if (newBlue<MIN_PIXEL_VALUE)
            this.blue=MIN_PIXEL_VALUE;
        else
             this.blue=newBlue;
    }
    public void setAlpha (short newAlpha) {
        if(newAlpha>MIN_TRANSPARENCY)
            this.alpha=MIN_TRANSPARENCY;
        else if (newAlpha<MAX_TRANSPARENCY)
            this.alpha=MAX_TRANSPARENCY;
        else
            this.alpha=newAlpha;
    }

    public void inverse()
    {
        this.red=(short)(Math.abs((this.red-MAX_PIXEL_VALUE)));
        this.green=(short)(Math.abs((this.green-MAX_PIXEL_VALUE)));
        this.blue=(short)(Math.abs((this.blue-MAX_PIXEL_VALUE)));
    }

    public void toGrayscale()
    {
        this.red = (short)((this.red+this.green+this.blue)/3);
        this.green = (short)((this.red+this.green+this.blue)/3);
        this.blue = (short)((this.red+this.green+this.blue)/3);

    }

    public void toBlackAndWhite ()
    {
        if (((this.red+this.green+this.blue)/3)>127)
            {
                this.red=MAX_PIXEL_VALUE;
                this.green=MAX_PIXEL_VALUE;
                this.blue=MAX_PIXEL_VALUE;
            }
        else
            {
                this.red=MIN_PIXEL_VALUE;
                this.green=MIN_PIXEL_VALUE;
                this.blue=MIN_PIXEL_VALUE;
            }
    }

    public void median(ArrayList<Pixel> pxs)
    {
        ArrayList<Short> reds = new ArrayList<Short>();
        ArrayList<Short> blues = new ArrayList<Short>();
        ArrayList<Short> greens = new ArrayList<Short>();

        for (Pixel px: pxs) {

            reds.add(px.red);
            blues.add(px.blue);
            greens.add(px.green);
        }

        Collections.sort(reds);
        Collections.sort(greens);
        Collections.sort(blues);

        if(pxs.size() % 2 != 0)
        {
            this.red = (short)Math.round(reds.get(pxs.size()/2));
            this.green = (short)Math.round(greens.get(pxs.size()/2));
            this.blue = (short)Math.round(blues.get(pxs.size()/2));
        }
        else
        {
            this.red = (short)Math.round((double)(reds.get((pxs.size()-1)/2) + reds.get((pxs.size()/2)))/2);
            this.green = (short)Math.round((double)(greens.get((pxs.size()-1)/2) + greens.get((pxs.size()/2)))/2);
            this.blue = (short)Math.round((double)(blues.get((pxs.size()-1)/2) + blues.get((pxs.size()/2)))/2);
        }

        reds.clear();
        greens.clear();
        blues.clear();

    }

    public void add(int i)
    {
        this.red+=i;
        this.green+=i;
        this.blue+=i;

    }

    public void sub(int i)
    {
        this.red-=i;
        this.green-=i;
        this.blue-=i;
    }
    public void inverseSub(int i)
    {
        this.red = (short)(i-this.red);
        this.green = (short)(i-this.green);
        this.blue = (short)(i-this.blue);

    }

    public void mul (int i)
    {
        this.red*=i;
        this.green*=i;
        this.blue*=i;
    }

    public void div (int i)
    {
        if(i!=0)
        {
            this.red /= i;
            this.green /= i;
            this.blue /= i;
        }

    }

    public void inverseDiv(int i)
    {
        if (this.red != 0)
        this.red = (short)(i / this.red);
        if (this.green != 0)
        this.green = (short)(i / this.green);
        if (this.blue != 0)
        this.blue = (short)(i / this.blue);
    }

    public void power(int i)
    {
        this.red = (short)Math.pow(this.red,i);
        this.green = (short)Math.pow(this.green,i);
        this.blue = (short)Math.pow(this.blue,i);
    }

    public void log ()
    {
        this.red = (short)Math.round(Math.log(this.red));
        this.green = (short)Math.round(Math.log(this.green));
        this.blue = (short)Math.round(Math.log(this.blue));
    }

    public void min (int min)
    {
        if(this.red > min)
            this.red=(short)min;
        if(this.green > min)
            this.green=(short)min;
        if(this.blue > min)
            this.blue=(short)min;
    }

    public void max (int max)
    {
        if(this.red < max)
            this.red=(short)max;
        if(this.green < max)
            this.green=(short)max;
        if(this.blue < max)
            this.blue=(short)max;
    }

    public void abs()
    {
        this.red = (short)Math.abs(this.red);
        this.green = (short)Math.abs(this.green);
        this.blue = (short)Math.abs(this.blue);
    }

    public String toString()
    {
        String output = "["+"R:"+red+" G:"+green+" B:" + blue+" A:"+alpha+ "]";
        return output;
    }

}
