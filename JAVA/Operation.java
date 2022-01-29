package Picture;

public class Operation {

    private String name;
    public Operation(String _name) {this.name=_name;}

    public String getName() {return  this.name;}

}

/*
*
* U jednom trenutku se izvrsava samo jedna operacija
*
*pri eksportovanju u json fajl radi izvrsavanja upisace se i slojevi
* nad kojima se data operacija izvrsava razdvojeni razmakom
*
*
*
* */