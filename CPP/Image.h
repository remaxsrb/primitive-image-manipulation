#pragma once
#ifndef IMAGE_H
#define IMAGE_H
#include<vector>
#include<map>
#include<regex>
#include<functional>
#include<algorithm>
#include<memory>
#include<string>
#include<list>
#include"Formater.h"
#include"Layer.h"
#include"Operations.h"
#include"Selections.h"

class Image 
{
private: 
	//polja
	
	std::vector<Layer> layers;
	std::map<std::string, std::shared_ptr<Operation>> operacije;
	std::map < std::string, Selection> selekcije;
	int numberOfLayers=0;
	int numberOfSelections = 0;
	static Image* instance;
	std::vector<std::vector<Pixel>>& moldLayers(std::vector<std::vector<Pixel>>& moldedPxs);
	void resizeLayers(Layer& newLayer);
	void createExportData(std::vector<uint8_t>& pixelsForExport);
	
	/*
	
	napisati privatnu metodu koja izvrsava operacije dobijene iz jave putem json fajla

	isto tako izvrsiti kompozitne operacije

	ista ta metoda ce da upise rezultat u json fajla tj sacuvace projekat
	
	*/
	
	Image() {}

	

public:
	static Image* createInstance() //zabranjivanje da se kreira vise od jedne image instance
	{
		if (instance == nullptr) 
		{
			instance = new Image();
			instance->operacije.insert(std::pair<std::string, std::shared_ptr<Operation>>("Abs", std::make_shared<Abs>("Abs")));
			instance->operacije.insert(std::pair<std::string, std::shared_ptr<Operation>>("Grayscale", std::make_shared<Grayscale>("Grayscale")));
			instance->operacije.insert(std::pair<std::string, std::shared_ptr<Operation>>("BlackAndWhite", std::make_shared<BlackAndWhite>("BlackAndWhite")));
			instance->operacije.insert(std::pair<std::string, std::shared_ptr<Operation>>("Inverse", std::make_shared < Inverse>("Inverse")));
			instance->operacije.insert(std::pair<std::string, std::shared_ptr<Operation>>("Median", std::make_shared < Median>("Median")));
			instance->operacije.insert(std::pair<std::string, std::shared_ptr<Operation>>("Add", std::make_shared < Add>("Add")));
			instance->operacije.insert(std::pair<std::string, std::shared_ptr<Operation>>("Sub", std::make_shared < Sub>("Sub")));
			instance->operacije.insert(std::pair<std::string, std::shared_ptr<Operation>>("InverseSub", std::make_shared < InverseSub>("InverseSub")));
			instance->operacije.insert(std::pair<std::string, std::shared_ptr<Operation>>("Mul", std::make_shared < Mul>("Mul")));
			instance->operacije.insert(std::pair<std::string, std::shared_ptr<Operation>>("Div", std::make_shared < Div>("Div")));
			instance->operacije.insert(std::pair<std::string, std::shared_ptr<Operation>>("InverseDiv", std::make_shared < InverseDiv>("InverseDiv")));
			instance->operacije.insert(std::pair<std::string, std::shared_ptr<Operation>>("Power", std::make_shared < Power>("Power")));
			instance->operacije.insert(std::pair<std::string, std::shared_ptr<Operation>>("Log", std::make_shared < Log>("Log")));
			instance->operacije.insert(std::pair<std::string, std::shared_ptr<Operation>>("Min", std::make_shared < Min>("Min")));
			instance->operacije.insert(std::pair<std::string, std::shared_ptr<Operation>>("Max", std::make_shared < Max>("Max")));
			
		}
			
		return instance;
	}

	~Image();
	//metode
	void addLayer(int32_t height, int32_t width);
	void addLayer(std::string &inputFilename); //metoda koja prima fajl i prosledjuje ga citacu
	void exportImage(std::string outputFile); //metoda koja upisuje sliku u fajl
	void deleteLayer(int32_t index); 
	void deactivateLayers(std::string& userActivatedLayers);
	void executeOperation(std::string opName, int i);
	void buildCompositeOperation(std::vector<std::string> ops, std::vector<int>constants, std::string compositeName);
	void createSelection(std::list<Rechtangle> rechtangles, std::string name, int layerno);
	void fillSelection(std::string& name, int red, int green,int blue);
	void deleteSelection(std::string& name);
	void saveProject(std::string filename);
	void loadProject(std::string filename);
	void executeComposites();
	void loadOperation(std::string inputFileName);
	void loadCompositeOp(std::string inputFileName);

	std::map<std::string, std::shared_ptr<Operation>> &  getOperations();
	
	
	friend class BMPFormater;
	friend class PAMFormater;
	friend class JSONFormater;



};
#endif IMAGE_H