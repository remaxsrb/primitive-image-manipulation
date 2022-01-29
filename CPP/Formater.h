#pragma once

#include<iostream>
#include<fstream>
#include<functional>
#include<queue>
#include"Image.h"
#include"json.hpp"
#include"Layer.h"
#include"fifo_map.hpp"


class Image;
class Operation;

class Formater 
{
protected:
	Image* image;
public:
	Formater(Image& image) : image(&image){}
	virtual void read(std::string sourceFileName)=0;
	virtual void writeToFile(std::string fname)=0;
	~Formater() {}
	
};

class BMPFormater : public Formater 
{
	int32_t height = 0;
	int32_t width = 0;
	uint16_t bitsPerPixel = 0;
	std::vector<uint8_t> pixels; //RGB poredak
public:
	BMPFormater(Image& image);
	void read(std::string sourceFileName) override;
	void writeToFile(std::string outputFileName) override;
	~BMPFormater() {}
};
class PAMFormater : public Formater 
{
private:
	int32_t height = 0;
	int32_t width = 0;
	uint16_t depth = 0;
	std::string type = "";
	std::vector<uint8_t> pixels;
public:
	PAMFormater(Image& image);
	void read(std::string sourceFileName)override;
	void writeToFile(std::string outputFileName) override;
	~PAMFormater() {}
};
class JSONFormater : public Formater
{
private:
	int numberOfLayers = 0;
	int numberOfSelections = 0;
	uint16_t bitsPerPixel = 32;
	int layerHeight=0;
	int layerWidth=0;
	std::string layerSource;
	//void recurseWrite(std::vector<std::shared_ptr<Operation>> opsVector, std::vector<int> constantsVector, std::ofstream&of);
	
public:
	JSONFormater(Image& image);
	void read(std::string sourceFileName);
	void writeToFile(std::string outputFileName);
	void loadCompositeOperations(std::string inputFileName);
	void saveCompositeOperations(std::string outputFileName);
	void readOperation(std::string inputFileName);
	~JSONFormater() {}
	
};
