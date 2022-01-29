#pragma once
#include"Layer.h"



Layer::Layer(int32_t height, int32_t width) 
{
	this->height = height;
	this->width = width;
	this->pixelMap.resize(this->height, std::vector<Pixel>(this->width));

	std::vector<std::vector<Pixel>>::iterator row;
	std::vector<Pixel>::iterator col;


	for (row = pixelMap.begin(); row != pixelMap.end(); ++row)
		for (col = row->begin(); col != row->end(); ++col)
			*col = Pixel();
}


Layer::Layer(std::string sourceFileName,int32_t height, int32_t width, uint16_t bitsPerPixel, std::vector<uint8_t>& pixels)
{
	this->sourceFileName = sourceFileName;
	this->height = height;
	this->width = width;

	std::vector<uint8_t>::iterator it;

	/*for (it = pixels.begin(); it!= pixels.end(); ++it) 
	{
		for (int i = 0; i < 4; i++)
			std::cout << *it;

		system("pause");
	}*/

	
	pixelMap.resize(this->height, std::vector<Pixel>(this->width));

	int index = 0;

	std::vector<std::vector<Pixel>>::iterator row;
	std::vector<Pixel>::iterator col;

	if (bitsPerPixel == 32) 
	{
		for (row = pixelMap.begin(); row != pixelMap.end(); ++row)
		{
			for (col = row->begin(); col != row->end(); ++col)

			{
				*col = Pixel(pixels[index], pixels[index + 1],
					pixels[index + 2], pixels[index + 3]);
				index += 4;
			}
		}
	}
	else if (bitsPerPixel == 24)
	{
		for (row = pixelMap.begin(); row != pixelMap.end(); ++row)
		{
			for (col = row->begin(); col != row->end(); ++col)

			{
				*col = Pixel(pixels[index], pixels[index + 1],
					pixels[index + 2], 255);
				index += 3;
			}
		}
	}

}
Layer::Layer(std::string sourceFileName,int32_t height, int32_t width, std::vector<uint8_t>& pixels, std::string type)
{
	this->sourceFileName = sourceFileName;
	this->height = height;
	this->width = width;

	this->pixelMap.resize(this->height, std::vector<Pixel>(this->width));

	int index = 0;

	std::vector<std::vector<Pixel>>::iterator row;
	std::vector<Pixel>::iterator col;

	if (strcmp(type.c_str(), "BLACKANDWHITE") == 0)
	{
		for (row = pixelMap.begin(); row != pixelMap.end(); ++row)
		{
			for (col = row->begin(); col != row->end(); ++col)

			{
				*col = Pixel(pixels[index]<<8, pixels[index]<<8,
					pixels[index]<<8, 255);
				index ++;
			}

		}
	}
	else if (strcmp(type.c_str(), "GRAYSCALE") == 0)
	{

		for (row = pixelMap.begin(); row != pixelMap.end(); ++row)
		{
			for (col = row->begin(); col != row->end(); ++col)

			{
				*col = Pixel(pixels[index], pixels[index],
					pixels[index], 255);
				index++;
			}
		}
	}
	else if (strcmp(type.c_str(), "RGB") == 0)
	{

		for (row = pixelMap.begin(); row != pixelMap.end(); ++row)
		{
			for (col = row->begin(); col != row->end(); ++col)

			{
				*col = Pixel(pixels[index], pixels[index + 1],
					pixels[index + 2], 255);
				index += 3;
			}
		}
		
	}
	else if (strcmp(type.c_str(), "BLACKANDWHITE_ALPHA") == 0)
	{
		for (row = pixelMap.begin(); row != pixelMap.end(); ++row)
		{
			for (col = row->begin(); col != row->end(); ++col)

			{
				*col = Pixel(pixels[index] << 8, pixels[index] << 8,
					pixels[index] << 8, pixels[index + 1] << 8);
				index += 2;
			}


		}
	}
	else if (strcmp(type.c_str(), "GRAYSCALE_ALPHA") == 0)
	{

		for (row = pixelMap.begin(); row != pixelMap.end(); ++row)
		{
			for (col = row->begin(); col != row->end(); ++col)

			{
				*col = Pixel(pixels[index], pixels[index],
					pixels[index], pixels[index + 1]);
				index += 2;
			}

		}
	}
	else if (strcmp(type.c_str(), "RGB_ALPHA") == 0) 
	{
		for (row = pixelMap.begin(); row != pixelMap.end(); ++row)
		{
			for (col = row->begin(); col != row->end(); ++col)

			{
				*col = Pixel(pixels[index], pixels[index + 1],
					pixels[index + 2], pixels[index + 3]);
				index += 4;
			}
		}
	}

}

void Layer::resize(uint32_t new_height, uint32_t new_width)
{
	std::vector<std::vector<Pixel>> temp (this->height, std::vector<Pixel>(this->width));
	temp = this->pixelMap;

	int32_t old_height = this->height;
	int32_t old_width = this->width;

	pixelMap.clear();
	
	this->height = new_height;
	this->width = new_width;
	this->pixelMap.resize(this->height, std::vector<Pixel>(this->width));

	std::vector<std::vector<Pixel>>::iterator row;
	std::vector<Pixel>::iterator col;

	int32_t i = 0;
	int32_t j = 0;

	for ( row = pixelMap.begin(); row != pixelMap.end(); ++row)
	{
		for (col = row->begin(); col != row->end(); ++col) 
		{
			if (j <= (old_width - 1) && i <= (old_height - 1)) 
				*col = temp[i][j];
			else 
				*col = Pixel();
			j++;
		}
		j = 0;
		i++;
	}
	temp.clear();
}

int32_t Layer::getHeight() const { return this->height; }
int32_t Layer::getWidth() const { return this->width; }
std::vector<std::vector<Pixel>>& Layer::getPixels()  { return this->pixelMap; }

bool Layer::getActivity() const { return this->active; }
void Layer::setActivity(bool newState) { this->active = newState; }

void Layer::setSelection( Selection* s) 
{
	
	this->selection = s;
	this->hasSelection = true;
}
bool Layer::selectedState() const { return this->hasSelection; }
void Layer::fillSelection(int red, int green, int blue)
{
	//podesu granice iteracije
	for (auto r : this->selection->getRechtangles()) 
	{
		
		for (int i = r.getY(); i > (r.getY()- r.getHeight())-1; i--)
		{
			for (int j = r.getX(); j < (r.getX() + r.getWidth()); j++)
			{
				this->pixelMap[i][j].setRed(red);
				this->pixelMap[i][j].setGreen(green);
				this->pixelMap[i][j].setBlue(blue);
			}

		}
	}
		
		
}
Selection* Layer::getSelection()  { return this->selection; }

std::string Layer::getSource() { return this->sourceFileName; }