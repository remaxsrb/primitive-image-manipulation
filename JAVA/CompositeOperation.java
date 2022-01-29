package Picture;

import java.util.ArrayList;

/*
*
* Zadatak je da c++ kodu prosledim operacije sa konstantama s kojim se izvrsavaju
*
* */


public class CompositeOperation extends Operation{

    private ArrayList<Operation> constituents = new ArrayList<>();
    private ArrayList<Integer> constants = new ArrayList<>();

    public CompositeOperation(String _name, ArrayList<Operation> _constituents, ArrayList<Operation> constants) {
        super(_name);
    }

    public void addOperation (Operation op, int constant)
    {
        this.constituents.add(op);
        this.constants.add(constant);
    }

    public ArrayList<Integer> getConstants() {
        return constants;
    }

    public ArrayList<Operation> getConstituents() {
        return constituents;
    }
}
