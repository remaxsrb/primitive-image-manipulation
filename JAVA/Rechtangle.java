package Picture;

public class Rechtangle {

    private int x = 0;
    private int y =0;
    private int height = 0;
    private int width = 0;

    public Rechtangle(int _x, int _y, int _height, int _width)
    {
        this.x=_x;
        this.y=_y;
        this.height=_height;
        this.width=_width;
    }

    public Rechtangle(Rechtangle r)
    {
        this.x=r.x;
        this.y=r.y;
        this.height=r.height;
        this.width= r.width;;
    }

    public int getHeight() {
        return height;
    }

    public int getWidth() {
        return width;
    }

    public int getX() {
        return x;
    }

    public int getY() {
        return y;
    }

    public void setHeight(int height) {
        this.height = height;
    }

    public void setWidth(int width) {
        this.width = width;
    }

    public void setX(int x) {
        this.x = x;
    }

    public void setY(int y) {
        this.y = y;
    }

    boolean isLessThan (Rechtangle r)
    {
        if (this.x<r.x) return true;
        else if (this.x > r.x) return false;
        else if (this.y<r.y) return true;
        else if(this.y>r.y) return false;
        else return true;
    }
}
