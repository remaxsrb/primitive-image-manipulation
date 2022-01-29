#include"Formater.h"
#include<stdlib.h>
#include<regex>


using json = nlohmann::json;
JSONFormater::JSONFormater(Image& image) : Formater(image){}
void JSONFormater::read(std::string sourceFileName)
{
	std::ifstream inputFile(sourceFileName);
	if (inputFile)
	{	
			std::string line;
			std::getline(inputFile, line);
			std::regex rx("\\{\"NS\":([0-9]),\"NL\":([0-9]),\"Depth\":([0-9]{2})\\}");

			//std::regex rx("\\{\"Depth\":([0-9]{2}),\"NL\":([0-9]),\"NS\":([0-9])\\}");

			std::smatch sm;
			if (std::regex_match(line, sm, rx))
			{

				
				this->numberOfSelections = std::stoi(sm.str(1));
				this->numberOfLayers = std::stoi(sm.str(2));
				this->bitsPerPixel = std::stoi(sm.str(3));



				/*this->bitsPerPixel = std::stoi(sm.str(1));
				this->numberOfLayers = std::stoi(sm.str(2));
				this->numberOfSelections = std::stoi(sm.str(3));*/

			}
			
		
			for (int i = 0; i < this->numberOfLayers; i++)
			{
				
				std::string metaData;
				std::getline(inputFile, metaData);

				if (i == 0)
				{
					/*mala optimizacija, nije potrebno da se kroz regex provlace sirina i visian sloja svaki put jer
						su one iste za svaki sloj sto je garantovano nakon ubacivanja svakog sloja*/
					std::regex rx("\\{\"Height\":([0-9]*),\"File\":\"(.*)\",\"Width\":([0-9]*)\\}");

					std::smatch sm;
					if (std::regex_match(metaData, sm, rx))
					{

						this->layerHeight = std::stoi(sm.str(1));
						this->layerSource = sm.str(2);
						this->layerWidth = std::stoi(sm.str(3));


					}

				}
				
				std::string data;
				std::string jsonData = "";;

				std::getline(inputFile, data);
				std::regex rx1("[(0-9)]+");
				for (auto it = std::sregex_iterator{ data.begin(),data.end(),rx1 }, end = std::sregex_iterator{};
					it != end;
					++it) {

					jsonData += (uint8_t)(stoi((it->str(0))));
				}
				std::vector<uint8_t> pixels(jsonData.begin(), jsonData.end());

				Layer newLayer(this->layerSource,this->layerHeight, this->layerWidth, this->bitsPerPixel, pixels);

			if (image->numberOfLayers != 0)
				//proveri da li treba prosiriti prethodne slojeve ili tek ucitani sloj
				image->resizeLayers(newLayer);

			image->layers.push_back(newLayer);
			image->numberOfLayers++;

			}
			for (int i = 0; i < this->numberOfSelections; i++)
			{
				std::string selekcija;
				std::getline(inputFile, selekcija);
				std::smatch sm2;
				std::regex rx2("\\{\"Layer\"\:([0-9]),\"Name\":\"([A-Za-z0-9]*)\"\\}(.*)");

				int layerNumber = 0;
				std::string selectionName;
				std::string rechtangles;

				if (std::regex_match(selekcija, sm2, rx2))
				{
					layerNumber = std::stoi(sm2.str(1));
					selectionName = sm2.str(2);
					rechtangles = sm2.str(3);


				}

				std::list<Rechtangle> loadedRechtangles;

				//std::regex rx3("/(?:{.*})+/g");
				//std::regex rx3("(\\{\"Height\":([0-9]*),\"Width\":([0-9]*),\"x\":([0-9]*),\"y\":([0-9]*)\\}*)");
				std::regex rx31("(\\{\"x\":([0-9]*),\"y\":([0-9]*),\"Height\":([0-9]*),\"Width\":([0-9]*)\\}*)");

				//{"Height":100,"Width":100,"x":0,"y":0}

				for (auto it = std::sregex_iterator{ rechtangles.begin(),rechtangles.end(),rx31 }, end = std::sregex_iterator{};
					it != end;
					++it) {
					std::string rechtangle = it->str(0);
					//std::regex rx4("\\{\"Height\":([0-9]*),\"Width\":([0-9]*),\"x\":([0-9]*),\"y\":([0-9]*)\\}");
					std::regex rx4("\\{\"x\":([0-9]*),\"y\":([0-9]*),\"Height\":([0-9]*),\"Width\":([0-9]*)\\}");
					std::smatch sm4;

					if (std::regex_match(rechtangle, sm4, rx4)) 
					{
						/*int height = std::stoi(sm4.str(1));
						int width = std::stoi(sm4.str(2));
						int x = std::stoi(sm4.str(3));
						int y = std::stoi(sm4.str(4));*/

						int x = std::stoi(sm4.str(1));
						int y = std::stoi(sm4.str(2));
						int height = std::stoi(sm4.str(3));
						int width = std::stoi(sm4.str(4));

						loadedRechtangles.push_back(Rechtangle(height, width, x, y));

					}
					
					Selection selection(loadedRechtangles, selectionName, layerNumber);
					image->selekcije.insert(std::pair<std::string, Selection>(selection.getName(), selection));
					std::map < std::string, Selection>::iterator iter;
					iter = image->selekcije.find(selectionName);
					image->layers[layerNumber - 1].setSelection(&(*iter).second);

				}
				
				

			}
			


		inputFile.close();
	}
	else std::cerr << "Error opening a file";
}
void JSONFormater::writeToFile(std::string outputFileName) 
{

	std::ofstream outputFile(outputFileName);
	if (outputFile) 
	{
		this->bitsPerPixel = 32;
	
		this->numberOfLayers = image->numberOfLayers;
		this->numberOfSelections = image->numberOfSelections;
		std::map < std::string, Selection>::iterator it = image->selekcije.begin();
		std::vector<Selection> selections;
		while (it != image->selekcije.end())
		{
			selections.push_back((*it).second);
			++it;
		}
		/*json j;
		j["NS"] = this->numberOfSelections;
		j["NL"] = this->numberOfLayers;
		j["Depth"] = this->bitsPerPixel;*/

		nlohmann::fifo_map<std::string, std::string> JSONqueue;
		outputFile << "{";
		JSONqueue["NS"] = std::to_string(this->numberOfSelections) ;
		JSONqueue["NL"] = std::to_string(this->numberOfLayers);
		JSONqueue["Depth"] = std::to_string(this->bitsPerPixel);

		int count = 0;

		for (auto j : JSONqueue) 
		{
			count++;
			if(count!=JSONqueue.size())
				outputFile << "\""<<j.first<<"\""<<":" << j.second<<",";
			else
				outputFile << "\"" << j.first << "\"" << ":" << j.second;
		}

		outputFile<<"}" <<  std::endl;

		std::for_each(image->layers.begin(), image->layers.end(), [&outputFile](Layer l) 
			{
				json j1;
				j1["Height"] = l.getHeight();
				j1["File"] = l.getSource();
				j1["Width"] = l.getWidth();
				
				

				outputFile << j1 << std::endl;

				std::vector<uint8_t> pixelData;
				for (int i = 0; i < l.getHeight(); i++) 
					for (int j = 0; j < l.getWidth(); j++) 
					{
						pixelData.push_back(l.getPixels()[i][j].getRed());
						pixelData.push_back(l.getPixels()[i][j].getGreen());
						pixelData.push_back(l.getPixels()[i][j].getBlue());
						pixelData.push_back(l.getPixels()[i][j].getAlpha());
					}

				json j_vec(pixelData);
				outputFile << j_vec << std::endl;
			});

		std::for_each(selections.begin(), selections.end(), [&outputFile](Selection s) 
			{
				json j2;
				j2["Name"] = s.getName();
				j2["Layer"] = s.getLayerNumber();
				
				outputFile << j2;
				std::for_each(s.getRechtangles().begin(), s.getRechtangles().end(), [&](Rechtangle r) 
					{
						json j3;
						j3["x"] = r.getX();
						j3["y"] = r.getY();
						j3["Height"] = r.getHeight();
						j3["Width"] = r.getWidth();
						outputFile << j3;

					});
				outputFile << std::endl;
			});
		
		

		outputFile.close();

	}
	else throw std::runtime_error("Failed to create a file for project saving!");
		
	

}
void JSONFormater::loadCompositeOperations(std::string inputFileName) 
{

	std::ifstream inputFile(inputFileName);
	if (inputFile)
	{
		std::string line;
		while (std::getline(inputFile, line)) 
		{
			if (strcmp(line.c_str(), "") != 0) 
			{
				std::regex rx("\\{\"CompositeName\":\"([A-Za-z]*)\"\\}(.*)");
				std::smatch sm;

				std::string compositeName;
				std::string compositeBuildingBlocks;

				if (std::regex_match(line, sm, rx))
				{


					compositeName = sm.str(1);
					compositeBuildingBlocks = sm.str(2);
				}

				std::string primeOperations = "(\\{\"Constant\":(-?[0-9]+),\"Name\":\"([A-Za-z]*)\"\\}*)";

				std::vector<std::string> ops;
				std::vector<int> constants;


				std::regex rx1(primeOperations);
				for (auto it = std::sregex_iterator{ compositeBuildingBlocks.begin(),compositeBuildingBlocks.end(),rx1 }, end = std::sregex_iterator{};
					it != end;
					++it) {

					std::string op = it->str(0);
					std::string primeOperation = "\\{\"Constant\":(-?[0-9]+),\"Name\":\"([A-Za-z]*)\"\\}";
					std::regex rx2(primeOperation);
					std::smatch sm2;
					if (std::regex_match(op, sm2, rx2))
					{

						constants.push_back(std::stoi(sm2.str(1)));
						ops.push_back(sm2.str(2));
					}

				}
				image->buildCompositeOperation(ops, constants, compositeName);

				//std::cout << std::endl;
			}

			inputFile.close();
		}
			
	}
	else throw std::runtime_error("The program has failed to open a file containing composite operation!");



	
}
void JSONFormater::saveCompositeOperations(std::string outputFileName)
{
	std::ofstream outputFile(outputFileName);

	if (outputFile) 
	{
		std::map<std::string, std::shared_ptr<Operation>>::iterator it;
		std::vector<std::shared_ptr<CompositeOperation>> composites;
		it = image->getOperations().begin();
		while (it != image->getOperations().end())
		{
			std::string type =  typeid(*(*it).second).name();
			
			if (type == "class CompositeOperation")
			{
				
				auto comp = std::dynamic_pointer_cast<CompositeOperation>((*it).second);
				
				composites.push_back(comp);
			}
				
			++it;
		}
		std::vector<std::shared_ptr<CompositeOperation>>::iterator cit = composites.begin();
		std::vector<std::shared_ptr<CompositeOperation>>::iterator end = composites.end();

		//vektori koje ima svaka kompozitna operacija. Preglednije je da se ovde deklarisu
		std::vector<std::shared_ptr<Operation>> currentOpsVector; 
		std::vector<int> currentConstantsVector;

		

		while (cit != end)
		{
		

			int constantIter = 0;
			 json jx;
			 jx["CompositeName"] = (*(*cit)).name;
			 outputFile << jx;
			 currentOpsVector = (*(*cit)).opsInComp;
			 currentConstantsVector = (*(*cit)).constants;
			 std::for_each(currentOpsVector.begin(), currentOpsVector.end(), [&currentConstantsVector,&constantIter,&outputFile]
			 (std::shared_ptr<Operation> op)
				 {


					 json j;
					 j["Name"] = op->name;
					 j["Constant"] = currentConstantsVector[constantIter++];
					 outputFile << j;
				 });
			 //ovde ulazi u rekurziju
			// recurseWrite(currentOpsVector, currentConstantsVector, outputFile);
			 outputFile << std::endl;
			
			++cit;
		}
		
	}
	else throw std::runtime_error("Failed to open a file!");
}
//void JSONFormater::recurseWrite(std::vector<std::shared_ptr<Operation>> opsVector, std::vector<int> constantsVector, std::ofstream& of)
//{
//	int count = 0;
//	int constantsCount = 0;
//	
//	std::for_each(opsVector.begin(), opsVector.end(), [&](std::shared_ptr<Operation> op) 
//		{
//			std::string type = typeid((*op)).name();
//			if (type == "class CompositeOperation") 
//			{
//				json j;
//				of << '[';
//				j["CompositeName"] = op->name;
//				j["Constant"] =constantsVector[constantsCount++];
//				of << j;
//				auto compOp = std::dynamic_pointer_cast<CompositeOperation>(op);
//				recurseWrite(compOp->opsInComp, compOp->constants, of);
//				//ispisi ime kompozitne i salji novu rekurziju
//				count++;
//				of << std::string(count, ']');
//			}
//			else 
//			{
//				json j;
//				j["Name"] = op->name;
//				j["Constant"] = constantsVector[constantsCount++];
//				of << j;
//				//ispisi proste
//			}
//		});
//
//		
//		return;
//	
//
//}

//----------------------------------------------------------------------------------------------------------


void JSONFormater::readOperation(std::string inputFileName) 
{
	std::ifstream inputFile(inputFileName);

	if (inputFile) 
	{
		std::string line;
		while (std::getline(inputFile, line)) 
		{
			std::regex rx("\\{\"const\":(.*),\"Layers\":\"(.*)\",\"Name\":\"([A-Za-z]+)\"\\}");
			std::smatch sm;

			

			if (std::regex_match(line, sm, rx))
			{
				int constant = 0;
				std::string name;
				std::string layers;

				constant = std::stoi(sm.str(1));
				layers = sm.str(2);
				name = sm.str(3);

				image->deactivateLayers(layers);
				image->executeOperation(name, constant);

			
			}
			
		}
	}
	else throw std::runtime_error("The program has failed to open a file containing operation!");
}

/*

Napisati metode za citanje imena operacija iz jsonfajla
Ako kompozitna operacija nije kreirana u javi, nece se izvrsiti

*/