package Picture;

import java.util.ArrayList;
import java.util.HashSet;
import java.util.Set;

public class Selection {

    private Set<Rechtangle> rechtangles = new HashSet<Rechtangle>();
    private String name;
    private int layerNo;

    public Selection() {this.layerNo=0;}
    public Selection (ArrayList<Rechtangle> vOfRectangles, String givenName, int _layerNo)
    {
        this.rechtangles.addAll(vOfRectangles);
        this.name=givenName;
        this.layerNo=_layerNo;

    }

    public Selection (Selection s)
    {
        this.rechtangles.addAll(s.rechtangles);
        this.name= s.name;
        this.layerNo = s.layerNo;
    }

    public int getLayerNo () {return this.layerNo;}

    public String getName() {return this.name;}

    public Set<Rechtangle> getRechtangles() {return this.rechtangles;}

}
