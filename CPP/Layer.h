#pragma once
#include"Pixel.h"
#include <vector>

#include"Selections.h"

class Layer 
{
private:
	
	std::vector<std::vector<Pixel>> pixelMap;
	int32_t height;
	int32_t width;
	bool active = true; //sloj je pri stvaranju aktivan
	bool hasSelection = false;
	Selection* selection=nullptr;
	std::string sourceFileName;
	
public:
	Layer(std::string sourceFileName,int32_t height,int32_t width,uint16_t bitsPerPixel,std::vector<uint8_t>& pixels);
	Layer(std::string sourceFileName,int32_t height, int32_t width, std::vector<uint8_t>& pixels, std::string type);
	Layer( int32_t height,int32_t width);
	void resize(uint32_t new_height, uint32_t new_width);
	int32_t getHeight()const;
	int32_t getWidth()const;
	std::vector<std::vector<Pixel>>& getPixels();
	bool getActivity()const;
	void setActivity(bool newState);
	void setSelection( Selection* s);
	void fillSelection(int red, int green, int blue);
	Selection* getSelection() ;
	bool selectedState() const;
	std::string getSource();

	~Layer() {}
};