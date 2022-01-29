#include"Image.h"

Image* Image::instance = nullptr;


void Image::addLayer(int32_t height, int32_t width) 
{
    
    this->layers.push_back((Layer(height,width)));
    this->numberOfLayers++;
}


void Image::addLayer(std::string &inputFilename) 
{
    std::smatch result;
    std::regex rx ("[^.]*\.(.*)");

    std::string fileFormat = "";
   
    if (std::regex_match(inputFilename, result, rx))
        fileFormat = result.str(1);
    
    if (strcmp(fileFormat.c_str(), "bmp") == 0) 
    {
     
       BMPFormater formater(*this);
       formater.read(inputFilename);

    }
    else if (strcmp(fileFormat.c_str(), "pam") == 0) 
    {
        
       PAMFormater formater(*this);
        formater.read(inputFilename);
      
    }
    else 
    {
        std::cerr << "INVALID FORMAT";
    }

}

void Image::exportImage(std::string outputFile)
{

    if (this->numberOfLayers == 0) 
    {
        std::cerr << "Ne moze se snimiti slika bez sloja";
        throw std::runtime_error("Can not export image with no layers");
    }

  
    std::smatch result;
    std::regex rx("[^.]*\.(.*)"); 
    std::string fileFormat = "";
    if (std::regex_match(outputFile, result, rx))
         fileFormat = result.str(1);
 

 

    if (strcmp(fileFormat.c_str(), "bmp") == 0) 
    {
        BMPFormater formater(*this);
        formater.writeToFile(outputFile);
    }
    

    else if (strcmp(fileFormat.c_str(), "pam") == 0) 
    {
       PAMFormater formater(*this);
        formater.writeToFile(outputFile);
    }
       
    else
    {
        std::cerr << "Ovaj format slike nije podrzan!";
        throw std::runtime_error("This format is not supported!");
    }
    
}

void Image::deactivateLayers(std::string& userActivatedLayers)
{
    
    if (std::strcmp(userActivatedLayers.c_str(), "") != 0)
    {
        std::vector<uint16_t> layersActive;
        std::function< std::vector<uint16_t> & ()> numbers = [&layersActive, &userActivatedLayers]() -> std::vector<uint16_t>&

        {
            std::regex rx1("[(0-9)]+");
            for (auto it = std::sregex_iterator{ userActivatedLayers.begin(),userActivatedLayers.end(),rx1 }, end = std::sregex_iterator{};
                it != end;
                ++it) {
                layersActive.push_back(std::stoi(it->str(0)));
               
            }

           

            return layersActive;
        };
        layersActive = numbers(); //vektor int-ova koji predstavljaju aktivne slojeve

        //metoda ce zapravo deaktivirati one slojeve koji nisu uneti od strane korisnika
    //vodio sam se logikom da slagani slojevi sluze kao neki preview konacne slike
    //korisnik na kraju bira aktivne slojeve tj. indirektno bira neaktivne sto on ne zna
        
        if (this->numberOfLayers >= 1) 
        {
            for (int i = 1; i < this->numberOfLayers + 1; i++)
            {
                if (std::none_of(layersActive.begin(), layersActive.end(), [=](int16_t j) {return i == j; }))
                    this->layers[i - 1].setActivity(false);
            }
        }
       
    }
    
}

void Image::createExportData(std::vector<uint8_t> &pixelsForExport)
{
   
    
    std::vector<std::vector<Pixel>> moldedPxs;

    std::function<std::vector<std::vector<Pixel>> & ()> pxsToExport = [this,&moldedPxs]() -> std::vector<std::vector<Pixel>>& {return moldLayers(moldedPxs);};

    std::vector<std::vector<Pixel>>::iterator row;
    std::vector<Pixel>::iterator col;
    moldedPxs = pxsToExport();
    int index = 0;
   
    for (row = moldedPxs.begin(); row != moldedPxs.end(); ++row)
    {
        for (col = row->begin(); col != row->end(); ++col)
        {
            pixelsForExport[index++] = ((*col).getBlue());
            pixelsForExport[index++] = ((*col).getGreen());
            pixelsForExport[index++] = ((*col).getRed());
            pixelsForExport[index++] = ((*col).getAlpha());
        }
    }
    
   
}

void Image::resizeLayers(Layer& newLayer)
{
    if (layers.back().getHeight() > newLayer.getHeight() && layers.back().getWidth() > newLayer.getWidth())
        newLayer.resize(layers.back().getHeight(), layers.back().getWidth());
    else if (layers.back().getHeight() > newLayer.getHeight() && layers.back().getWidth() < newLayer.getWidth())
    {
        int32_t new_height = layers.back().getHeight();
        int32_t new_width = newLayer.getWidth();

        newLayer.resize(new_height, new_width);
        std::for_each(layers.begin(), layers.end(), [=](Layer& layer) {layer.resize(new_height, new_width); });
    }
    else if (layers.back().getHeight() < newLayer.getHeight() && layers.back().getWidth() < newLayer.getWidth())
    {
        int32_t new_height = newLayer.getHeight();
        int32_t new_width = newLayer.getWidth();

        std::for_each(layers.begin(), layers.end(), [=](Layer& layer) {layer.resize(new_height, new_width); });
    }
    else if (layers.back().getHeight() < newLayer.getHeight() && layers.back().getWidth() > newLayer.getWidth())
    {
        int32_t new_height = newLayer.getHeight();
        int32_t new_width = layers.back().getWidth();

        newLayer.resize(new_height, new_width);
        std::for_each(layers.begin(), layers.end(), [=](Layer& layer) {layer.resize(new_height, new_width); });
    }

}

void Image::deleteLayer(int32_t index) 
{
    //index predstavlja redni broj sloja od "dna" slike
    if (index <= 0) 
    {
        std::cerr << "Na korisnickom nivou slojevi se indeksiraju od 1!" << std::endl;
        std::cerr << "Uneti ispravan indeks!" << std::endl;
        std::cin >> index;
    }
    if (index > this->numberOfLayers)
    {
        std::cerr << "Uneti broj je veci od broja slojeva!" << std::endl;
        std::cerr << "Uneti ispravan indeks!" << std::endl;
        std::cin >> index;
    }
    
    this->layers.erase(layers.begin() + index - 1);
    this->numberOfLayers--;
}

void Image::buildCompositeOperation(std::vector<std::string> ops, std::vector<int>constants, std::string compositeName)
{
    std::vector<std::shared_ptr<Operation>> operations;

    std::map<std::string, std::shared_ptr<Operation>>::iterator it;

    it = this->operacije.find(compositeName);

    if (it == operacije.end()) 
    {
        std::for_each(ops.begin(), ops.end(), [&](std::string op)
            {
                std::map<std::string, std::shared_ptr<Operation>>::iterator it1;

                it1 = this->operacije.find(op);
                int count = 0;

                if (it1 != operacije.end())
                {

                    operations.push_back(((*it1).second));
                }

            });
        


        this->operacije.insert(std::pair<std::string, std::shared_ptr<Operation>>(compositeName, std::make_shared<CompositeOperation>(operations, constants, compositeName)));
    }

    
    
    
}

void Image::executeOperation(std::string opName, int i) 
{
   
    std::map<std::string, std::shared_ptr<Operation>>::iterator it;
    it = this->operacije.find(opName);
    if (it != operacije.end()) 
    {
        (*(*it).second)(this->layers, i); //izvrsavanje opracije
        //nakon izvrsene operacije, ovde se vrsi kontrola piksela

        
    }
    std::for_each(layers.begin(), layers.end(), [](Layer& layer)
        {
            for (int i = 0; i < layer.getHeight(); i++)
                for (int j = 0; j < layer.getWidth(); j++)
                {
                    layer.getPixels()[i][j].setRed(layer.getPixels()[i][j].getRed());
                    layer.getPixels()[i][j].setGreen(layer.getPixels()[i][j].getGreen());
                    layer.getPixels()[i][j].setBlue(layer.getPixels()[i][j].getBlue());
                }
            /*istina je da deluje konfuzno i paradoksalno. Razlog tome je sto samo izvrsavanje operacija ne vodi racuna o max i min vrednosti komponenti
            seteri medjutim imaju taj mehanizam koji ne dozvoljava vrednostima da predju te granice pa iz tog razloga postavljam vrednost
            koju vraca geter.*/

            if (layer.getActivity() == false) layer.setActivity(true);
        });
}


std::vector<std::vector<Pixel>>& Image::moldLayers(std::vector<std::vector<Pixel>>& moldedPxs)
{
    int32_t height = this->layers.back().getHeight();
    int32_t width = this->layers.back().getWidth();
    moldedPxs.resize(height, std::vector<Pixel>(width));
    int count = 0;
    std::for_each(layers.crbegin(), layers.crend(), [&](Layer currL) 
        {  
            

            if (count == 0)  //prazna matrica piksela uzima prvi sloj sa "vrha" 
            {
                if (currL.getActivity() == true) 
                {
                    std::copy(currL.getPixels().begin(), currL.getPixels().end(), moldedPxs.begin());
                    count++;
                }
                 
            }
            else 
            {
                if (currL.getActivity() == true)
                {

                    uint8_t R;
                    uint8_t G;
                    uint8_t B;
                    uint8_t A;

                    

                    for (int i = 0; i < height; i++)
                        for (int j = 0; j < width; j++) //ovde se desava stapanje. moldedPxs predstavlja A0 a CurrL A1 sloj, tako sve do AX-1
                        {

                            double a0 = (double)((int)moldedPxs[i][j].getAlpha()) / 255;
                            double a1 = (double)((int)currL.getPixels()[i][j].getAlpha()) / 255;

                            double new_alpha = a0 + (1 - a0) * a1;
                            A = (uint8_t)((int)(round(new_alpha*255)));

                            if (a0 == 0)
                            {
                                R = currL.getPixels()[i][j].getRed();
                                G = currL.getPixels()[i][j].getRed();
                                B = currL.getPixels()[i][j].getBlue();
                               
                            }

                            else
                            {

                                double r0 = (double)((int)moldedPxs[i][j].getRed());
                                double r1 = (double)((int)currL.getPixels()[i][j].getRed());
                                R = (uint8_t)((int)(round(r0*a0/new_alpha+r1*(1-a0)*a1/new_alpha)));
                                //----------------------------------------------------------------------
                                double g0 = (double)((int)moldedPxs[i][j].getGreen());
                                double g1 = (double)((int)currL.getPixels()[i][j].getGreen());
                                G = (uint8_t)((int)(round(g0 * a0 / new_alpha + g1 * (1 - a0) * a1 / new_alpha)));
                                //--------------------------------------------------------------------------------
                                double b0 = (double)((int)moldedPxs[i][j].getBlue());
                                double b1 = (double)((int)currL.getPixels()[i][j].getBlue());
                                B = (uint8_t)((int)(round(b0 * a0 / new_alpha + b1 * (1 - a0) * a1 / new_alpha)));
                                
                                //radim eksplicitan c-style cast da bih bio siguran da se zaokruzeni double pretvara u int a int u char. isto vazi i za obrnut proces
                                 // mogli su se koristiti i drugi cast-ovi ali bi kod izgleda jos konfuznije nego sto je sad
                            }

                            moldedPxs[i][j].setRed(R);
                            moldedPxs[i][j].setGreen(G);
                            moldedPxs[i][j].setBlue(B);
                            moldedPxs[i][j].setAlpha(A);
                        }
                }
                     count++;
            }
               
            
        });



    return moldedPxs;

}

void Image::createSelection(std::list<Rechtangle> rechtangles, std::string name, int layerno)
{
   
    if (layerno > this->numberOfLayers)
        std::cerr << "Broj slojeva na slici je manji od rednog broja koji ste uneli!";
    else if (layerno <= 0)
        std::cerr << "Slika ima minimum jedan sloj!";
    else
    {

        int designatedLayerHeight = this->layers[layerno - 1].getHeight();
        int designatedLayerWidth = this->layers[layerno - 1].getWidth();
       
        //proveravam da li su pravougaonicu u opsegu slike, ako nisu brisem ih dok ih ne ubacim u skup. 
      
       
        rechtangles.remove_if([=](Rechtangle r) 
            {
                return ((r.getX() > designatedLayerWidth) || (r.getY() > designatedLayerHeight));
            });
      

        /*ako su pravougaonici kordinatno u slici, podesavam njihove dimenzije tako da u slucaju da
        zbir kordinate i dimenzije prelazi dimenziju slike, dimenziju pravougaonika podesavam tako da onda dodje do ivice slike a ne preko*/
        /* Takodje Y koordinatu transformisem iz donjeg u gornji levi ugao jer korisnik zapravo nije svestan da mi on daje donji levi a ne gornji
        levi ugao*/
       

        std::transform(rechtangles.begin(), rechtangles.end(), rechtangles.begin(), [&](Rechtangle &r)->Rechtangle& 
            {

               

                if ((r.getHeight() + r.getY()) > designatedLayerHeight) 
                     r.setHeight(designatedLayerHeight - r.getY());
                if ((r.getWidth() + r.getX()) > designatedLayerWidth)
                    r.setWidth((designatedLayerWidth - r.getX()));
             
                r.setY(designatedLayerHeight - r.getY()-1);
              
                return r;
            });

   
        Selection selection(rechtangles, name, layerno);
 

        this->selekcije.insert(std::pair<std::string, Selection>(selection.getName(), selection));
        std::map < std::string, Selection>::iterator it;
        it = this->selekcije.find(name);
        this->layers[layerno-1].setSelection(&(*it).second);
      
        this->numberOfSelections++;
    }

}
void Image::fillSelection(std::string& name, int red, int green, int blue)
{
    std::map < std::string, Selection>::iterator it;
    it = this->selekcije.find(name);
    if (it != this->selekcije.end())
    {
        //napisati za slojeve operacije fill za svih pet boja
        this->layers[(*it).second.getLayerNumber()-1].fillSelection(red,green,blue);
    }
    else std::cerr << "Selekcija sa ovim imenom ne postoji!";

}
void Image::deleteSelection(std::string& name) 
{
    std::map < std::string, Selection>::iterator it;
    it = this->selekcije.find(name);
    if (it != this->selekcije.end())
    {
        this->selekcije.erase(name);
       
    }
    else std::cerr << "Selekcija sa ovim imenom ne postoji!";
}
 Image::~Image() {}

 void Image::saveProject(std::string filename) 
 {
    
    JSONFormater formater(*this);
    formater.writeToFile(filename);
    formater.saveCompositeOperations("C:\\Users\\mjova\\IdeaProjects\\POOP_Project_2020\\compositeoperations.json");
   
      

 }
 void Image::loadProject(std::string filename) 
 {
     JSONFormater formater(*this);
     formater.read(filename);
     formater.loadCompositeOperations("C:\\Users\\mjova\\IdeaProjects\\POOP_Project_2020\\compositeoperations.json");
 }

 std::map<std::string, std::shared_ptr<Operation>>&  Image::getOperations()  { return this->operacije; }

 void Image::executeComposites() 
 {

     std::map<std::string, std::shared_ptr<Operation>>::iterator it = operacije.begin();
     std::map<std::string, std::shared_ptr<Operation>>::iterator end = operacije.end();
     
     while (it != end) 
     {
         std::string type = typeid(*(*it).second).name();
         if (type == "class CompositeOperation") 
         {
             (*(*it).second)(this->layers, 0);
         }
         ++it;
     }

     std::for_each(layers.begin(), layers.end(), [](Layer& layer)
         {
             for (int i = 0; i < layer.getHeight(); i++)
                 for (int j = 0; j < layer.getWidth(); j++)
                 {
                     layer.getPixels()[i][j].setRed(layer.getPixels()[i][j].getRed());
                     layer.getPixels()[i][j].setGreen(layer.getPixels()[i][j].getGreen());
                     layer.getPixels()[i][j].setBlue(layer.getPixels()[i][j].getBlue());
                 }
             
           
         });
 }

 void Image::loadOperation(std::string inputFileName) 
 {
     JSONFormater formater(*this);
     formater.readOperation(inputFileName);
 }

 void Image::loadCompositeOp(std::string inputFileName) 
 {
     JSONFormater formater(*this);
     formater.loadCompositeOperations(inputFileName);
     formater.saveCompositeOperations("C:\\Users\\mjova\\IdeaProjects\\POOP_Project_2020\\compositeoperations.json");

 }