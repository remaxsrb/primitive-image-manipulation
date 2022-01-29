#include"Formater.h"
#include"PAM.h"
#include<regex>
PAMFormater::PAMFormater(Image& image) :Formater(image)
{  }
void PAMFormater::read(std::string sourceFileName)
{

	std::ifstream input{ sourceFileName, std::ios_base::binary };

	if (input)
	{
		std::string line;
		std::string lines;
		std::smatch result;
		std::regex rx("(P7)WIDTH ([0-9]*)HEIGHT ([0-9]*)DEPTH ([0-9]*)MAXVAL ([0-9]*)TUPLTYPE ([A-_]*)(ENDHDR)");
		int count = 0;
		while (count < 7)
		{
			getline(input, line);
			lines += line;
			count++;
		}



		if (std::regex_match(lines, result, rx))
		{


			this->height = std::stoi(result.str(2));
			this->width= std::stoi(result.str(3));
			this->depth= std::stoi(result.str(4));
			this->type= result.str(6);

		}
		
		
		this->pixels.resize(this->height * this->width * this->depth);

		input.read((char*)this->pixels.data(), this->pixels.size());

		Layer newLayer(sourceFileName,this->height,this->width,this->pixels,this->type);

		if (image->numberOfLayers != 0)
			//proveri da li treba prosiriti prethodne slojeve ili tek ucitani sloj
			image->resizeLayers(newLayer);

		image->layers.push_back(newLayer);
		image->numberOfLayers++;
		input.close();
	}
	else
	{
		std::cerr << "Failed to open a file!\n";
	}
}

void PAMFormater::writeToFile(std::string outputFileName)
{

	std::ofstream outputFile(outputFileName, std::ios_base::binary);

	if (outputFile)
	{
		PAMHeader header;

		this->height = image->layers.back().getHeight(); //validno je ovako reci jer se nakon ubacivanja garantuje indenticnost dimenzija
		this->width = image->layers.back().getWidth();
		this->pixels.resize(this->height * this->width * 4);
		image->createExportData(this->pixels);

		header.height =this->height;
		header.width = this->width;
		header.depth = 4;
		header.maxVal = 255;
		header.type = "RGB_ALPHA";

		std::string linesToWrite = header.id + "\n" + "WIDTH" + " " + std::to_string(header.height) + "\n" + "HEIGHT" + " " +
			std::to_string(header.width) + "\n" + "DEPTH" + " " + std::to_string(header.depth) + "\n" + "MAXVAL" + " " +
			std::to_string(header.maxVal) + "\n" + "TUPLTYPE" + " " + header.type + "\n" + header.end + "\n";
		//"(P7).WIDTH ([0-9]*).HEIGHT ([0-9]*).DEPTH ([0-9]*).MAXVAL ([0-9]*).TUPLTYPE ([A-_]*).(ENDHDR)"

		outputFile << linesToWrite;
		outputFile.write((const char*)this->pixels.data(),this->pixels.size());

		outputFile.close();

	}
	else {}
}