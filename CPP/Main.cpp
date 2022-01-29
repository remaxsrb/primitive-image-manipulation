#include <iostream>
#include"Image.h"
int main(int argc, char** argv) 
{

	
	Image& image = *(Image::createInstance());


	
	//////execute opertations
	//image.loadProject(argv[1]);
	//image.loadOperation(argv[2]);
	//image.saveProject(argv[1]);

	/*std::cout << "Loading project....";
	image.loadProject(s1);
	std::cout << "Executing operation....";
	image.loadOperation(s2);
	std::cout << "Saving project....";
	image.saveProject(s3);*/


	
	
	//Saving image
	image.loadProject(argv[1]);
	image.exportImage(argv[2]);
	


	/*
	
	napraviti po exe fajl za pisanje u bmp, pam i json
	ulazni parametri ce biti objekat image, format fajla i naziv fajla

	--------------------------------------------------------------------------------
	napraviti exe fajl za izvrsavanje operacija:
	prima vektor stringova operacija, izvrsi operaciju
	snimi u json



	*/


	
	//std::cout << "Da li zelite da se automatski izvrsi promena slike ili zelite da vam se prikaze meni?\nAutomatsko: 1\nMeni: 2\n";
	//std::cout << "Vas izbor: ";
	//int userDecidion;
	//std::cin >> userDecidion;

	//if (userDecidion == 1) 
	//{
	//	image.loadProject(".jsonTestRun.json");
	//	image.executeComposites();
	//	image.saveProject(".jsonTestRunTest.json");
	//	image.exportImage("jsonTestRun.bmp");
	//}
	//else if (userDecidion == 2) 
	//{
	//	char userChoice;
	//	bool generatedFile = false;
	//	while (1)
	//	{
	//		std::cout << "1. Zapocni rad sa slikama" << std::endl;
	//		std::cout << "2. Dodaj sloj na sliku" << std::endl;
	//		std::cout << "3. Izbrisi sloj" << std::endl;
	//		std::cout << "4. Izvrsi operaciju" << std::endl;
	//		std::cout << "5. Napravi slozenu operaciju" << std::endl;
	//		std::cout << "6. Napravi selekciju" << std::endl;
	//		std::cout << "7. izbrisi selekciju" << std::endl;
	//		std::cout << "8. Oboji selekciju" << std::endl;
	//		std::cout << "9. Snimi rad" << std::endl;
	//		std::cout << "s. JSON test" << std::endl;
	//		std::cout << "x. Izadji iz programa" << std::endl << std::endl;

	//		std::cout << "Vas izbor: ";
	//		std::cin >> userChoice;

	//		switch (userChoice)
	//		{
	//		case '1':
	//		{
	//			char userChoice1;
	//			std::cout << "Zelite li da zapocnete slikom ili praznim slojem?\n Uneti 1 za sliku\n 0 za prazan sloj\n" << std::endl;
	//			std::cout << "Vas izbor: ";
	//			std::cin >> userChoice1;
	//			if (userChoice1 == '1')
	//			{
	//				std::string inputFilename;
	//				std::cout << "Unesite ime fajla koji ucitavate: ";
	//				std::cin >> inputFilename;
	//				image.addLayer(inputFilename);
	//			}
	//			else if (userChoice1 == '0')
	//			{
	//				int height;
	//				int width;

	//				std::cout << "Unesite visinu sloja: ";
	//				std::cin >> height;
	//				std::cout << "Unesite sirinu sloja: ";
	//				std::cin >> width;

	//				image.addLayer(height, width);
	//			}
	//			else
	//			{
	//				std::cout << "Pritisnut je neodgovarajuci taster, pokusati ponovo: ";
	//				std::cin >> userChoice1;
	//				if (userChoice1 == '1')
	//				{
	//					std::string inputFilename;
	//					std::cout << "Unesite ime fajla koji ucitavate: ";
	//					std::cin >> inputFilename;
	//					image.addLayer(inputFilename);
	//				}
	//				else if (userChoice1 == '0')
	//				{
	//					int height;
	//					int width;

	//					std::cout << "Unesite visinu sloja: ";
	//					std::cin >> height;
	//					std::cout << "Unesite sirinu sloja: ";
	//					std::cin >> width;

	//					image.addLayer(height, width);
	//				}
	//			}


	//		}

	//		break;

	//		case '2':
	//		{
	//			std::string inputFilename;
	//			std::cout << "Ime fajla koji ucitavate: ";
	//			std::cin >> inputFilename;
	//			image.addLayer(inputFilename);
	//		}
	//		break;
	//		case '3':
	//		{
	//			int indexToDelete;
	//			std::cout << "Redni broj sloja koji se brise: ";
	//			std::cin >> indexToDelete;
	//			image.deleteLayer(indexToDelete);
	//		}
	//		break;
	//		case '4':
	//		{
	//			std::cout << "Operacije:" << std::endl;
	//			std::map<std::string, std::shared_ptr<Operation>>::iterator it;
	//			it = image.getOperations().begin();
	//			while (it != image.getOperations().end())
	//			{
	//				std::cout << (*it).first << std::endl;
	//				++it;
	//			}
	//			std::cout << "Unesite ime operacije koju zelite da izvrsite: ";
	//			std::string opName;
	//			std::cin >> opName;



	//			it = image.getOperations().find(opName);
	//			if (it != image.getOperations().end())
	//			{
	//				std::string userActivatedLayers;
	//				std::cout << "Izaberite slojeve nad kojima se vrsi operacija. \nAko se ne izaberu slojevi, operacija ce biti izvrsena na svim postojecim: ";

	//				std::cin.ignore();
	//				std::getline(std::cin, userActivatedLayers);
	//				image.deactivateLayers(userActivatedLayers);

	//				//((*it).first == "grayscale")

	//				if ((*it).first == "add")
	//				{
	//					int constant;
	//					std::cout << "Unesite konstantu sa kojom ce se izvrsavati operacija: ";
	//					std::cin >> constant;
	//					image.executeOperation(opName, constant);

	//				}
	//				else if ((*it).first == "sub")
	//				{
	//					int constant;
	//					std::cout << "Unesite konstantu sa kojom ce se izvrsavati operacija: ";
	//					std::cin >> constant;
	//					image.executeOperation(opName, constant);

	//				}
	//				else if ((*it).first == "isub")
	//				{
	//					int constant;
	//					std::cout << "Unesite konstantu sa kojom ce se izvrsavati operacija: ";
	//					std::cin >> constant;
	//					image.executeOperation(opName, constant);


	//				}
	//				else if ((*it).first == "mul")
	//				{
	//					int constant;
	//					std::cout << "Unesite konstantu sa kojom ce se izvrsavati operacija: ";
	//					std::cin >> constant;
	//					image.executeOperation(opName, constant);

	//				}
	//				else if ((*it).first == "div")
	//				{
	//					int constant;
	//					std::cout << "Unesite konstantu sa kojom ce se izvrsavati operacija: ";
	//					std::cin >> constant;
	//					image.executeOperation(opName, constant);

	//				}
	//				else if ((*it).first == "idiv")
	//				{
	//					int constant;
	//					std::cout << "Unesite konstantu sa kojom ce se izvrsavati operacija: ";
	//					std::cin >> constant;
	//					image.executeOperation(opName, constant);

	//				}
	//				else if ((*it).first == "power")
	//				{
	//					int constant;
	//					std::cout << "Unesite konstantu sa kojom ce se izvrsavati operacija: ";
	//					std::cin >> constant;
	//					image.executeOperation(opName, constant);

	//				}
	//				else if ((*it).first == "min")
	//				{
	//					int constant;
	//					std::cout << "Unesite konstantu sa kojom ce se izvrsavati operacija: ";
	//					std::cin >> constant;
	//					image.executeOperation(opName, constant);

	//				}
	//				else if ((*it).first == "max")
	//				{
	//					int constant;
	//					std::cout << "Unesite konstantu sa kojom ce se izvrsavati operacija: ";
	//					std::cin >> constant;
	//					image.executeOperation(opName, constant);

	//				}
	//				else image.executeOperation(opName, 0);


	//			}
	//			else std::cout << "Izabrali ste opciju koja ne postoji, slika nije promenjena!" << std::endl;
	//			std::cout << std::endl;
	//		}
	//		break;
	//		case '5':
	//		{
	//			std::vector<std::string> ops;
	//			std::vector<int> constants;

	//			std::cout << "Dostupne operacije za stvaranje slozenih:" << std::endl;
	//			std::map<std::string, std::shared_ptr<Operation>>::iterator it;
	//			it = image.getOperations().begin();
	//			while (it != image.getOperations().end())
	//			{
	//				std::string type = typeid(*(*it).second).name();
	//				if (type != "class CompositeOperation")
	//					std::cout << (*it).first << std::endl;
	//				++it;
	//			}
	//			bool doneBuilding = false;
	//			int count = 0;


	//			while (!doneBuilding)
	//			{
	//				std::cout << "Unesite ime operacije koje ce uci u sastav kompozitne, ako ste zavrsili pritisnite x: \n";

	//				std::string uinput;
	//				std::cin >> uinput;
	//				it = image.getOperations().find(uinput);
	//				if (it != image.getOperations().end())
	//				{
	//					if ((*it).first == "add")
	//					{
	//						int constant;
	//						std::cout << "Unesite konstantu sa kojom ce se izvrsavati operacija: ";
	//						std::cin >> constant;
	//						constants.push_back(constant);
	//						ops.push_back(uinput);
	//					}
	//					else if ((*it).first == "sub")
	//					{
	//						int constant;
	//						std::cout << "Unesite konstantu sa kojom ce se izvrsavati operacija: ";
	//						std::cin >> constant;
	//						constants.push_back(constant);
	//						ops.push_back(uinput);
	//					}
	//					else if ((*it).first == "isub")
	//					{
	//						int constant;
	//						std::cout << "Unesite konstantu sa kojom ce se izvrsavati operacija: ";
	//						std::cin >> constant;
	//						constants.push_back(constant);
	//						ops.push_back(uinput);
	//					}
	//					else if ((*it).first == "mul")
	//					{
	//						int constant;
	//						std::cout << "Unesite konstantu sa kojom ce se izvrsavati operacija: ";
	//						std::cin >> constant;
	//						constants.push_back(constant);
	//						ops.push_back(uinput);
	//					}
	//					else if ((*it).first == "div")
	//					{
	//						int constant;
	//						std::cout << "Unesite konstantu sa kojom ce se izvrsavati operacija: ";
	//						std::cin >> constant;
	//						constants.push_back(constant);
	//						ops.push_back(uinput);
	//					}
	//					else if ((*it).first == "idiv")
	//					{
	//						int constant;
	//						std::cout << "Unesite konstantu sa kojom ce se izvrsavati operacija: ";
	//						std::cin >> constant;
	//						constants.push_back(constant);
	//						ops.push_back(uinput);

	//					}
	//					else if ((*it).first == "power")
	//					{
	//						int constant;
	//						std::cout << "Unesite konstantu sa kojom ce se izvrsavati operacija: ";
	//						std::cin >> constant;
	//						constants.push_back(constant);
	//						ops.push_back(uinput);

	//					}
	//					else if ((*it).first == "min")
	//					{
	//						int constant;
	//						std::cout << "Unesite konstantu sa kojom ce se izvrsavati operacija: ";
	//						std::cin >> constant;
	//						constants.push_back(constant);
	//						ops.push_back(uinput);

	//					}
	//					else if ((*it).first == "max")
	//					{
	//						int constant;
	//						std::cout << "Unesite konstantu sa kojom ce se izvrsavati operacija: ";
	//						std::cin >> constant;
	//						constants.push_back(constant);
	//						ops.push_back(uinput);

	//					}
	//					else
	//					{
	//						constants.push_back(0);
	//						ops.push_back(uinput);
	//					}
	//				}

	//				else if (uinput == "x")
	//					doneBuilding = true;
	//				else std::cout << "Ime operacije koje je uneto ne pripada dostupnim operacijama!\n";
	//			}

	//			std::string compositeName;
	//			std::cout << "Unesite ime kompozitne operacije: ";
	//			std::cin >> compositeName;

	//			image.buildCompositeOperation(ops, constants, compositeName);


	//		}
	//		break;
	//		case '6':
	//		{

	//			bool doneSelecting = false;
	//			std::list<Rechtangle> rechtangles;
	//			while (!doneSelecting)
	//			{
	//				std::cout << "Unesite podatke o jednom od pravougaonika koji ulazi u sastav selekcije.\n ";
	//				int x;
	//				int y;
	//				int height;
	//				int width;
	//				std::cout << "X koorinata gornjeg levog ugla pravougaonika: ";
	//				std::cin >> x;
	//				std::cout << "Y koorinata gornjeg levog ugla pravougaonika: ";
	//				std::cin >> y;
	//				std::cout << "Visina: ";
	//				std::cin >> height;
	//				std::cout << "Sirina: ";
	//				std::cin >> width;
	//				rechtangles.push_back(Rechtangle(x, y, height, width));
	//				std::cout << "Ako ste zavrsili sa dodavanjem pravougaonika, pritisnite x: ";
	//				char exit;
	//				std::cin >> exit;
	//				if (exit == 'x') doneSelecting = true;

	//			}
	//			int layerNo;
	//			std::cout << "Sloj koji ce primiti selekciju: ";
	//			std::cin >> layerNo;
	//			std::string selectionName;
	//			std::cout << "Ime selekcije: ";
	//			std::cin >> selectionName;
	//			image.createSelection(rechtangles, selectionName, layerNo);
	//		}
	//		break;
	//		case '7':
	//		{
	//			std::cout << "Ime selekcije koja se brise: ";
	//			std::string name;
	//			std::cin >> name;
	//			image.deleteSelection(name);
	//		}
	//		break;
	//		case '8':
	//		{

	//			std::cout << "Komponente boja su u opsegu od 0-255\n";
	//			std::cout << "Crvena: ";
	//			int red;
	//			std::cin >> red;
	//			std::cout << "Zelena: ";
	//			int green;
	//			std::cin >> green;
	//			std::cout << "Plava: ";
	//			int blue;
	//			std::cin >> blue;

	//			std::cout << "Ime selekcije: ";
	//			std::string name;
	//			std::cin >> name;
	//			image.fillSelection(name, red, green, blue);

	//		}
	//		break;
	//		case '9':
	//		{

	//			std::string userActivatedLayers;
	//			std::cout << "Izaberite slojeve koji ucestvuju u stvaranju slike tako sto 1 predstavlja sloj na dnu a X sloj na vrhu." << std::endl <<
	//				"Ako se ne odrede slojevi, svi postojeci ce ucestvovati: ";
	//			std::cin.ignore();
	//			std::getline(std::cin, userActivatedLayers);
	//			image.deactivateLayers(userActivatedLayers);
	//			std::string format;
	//			std::cout << "Uneti format slike u kom se snima fajl. Podrzani formati su: bmp, pam: ";
	//			std::cin >> format;

	//			if (format != "bmp" && format != "pam")
	//			{
	//				std::cerr << "Pokusali ste izabrati formati koji nije podrzan pokusajte ponovo!";
	//				std::cout << "Podrzani formati su: bmp, pam: ";
	//				std::cin >> format;
	//			}

	//			std::string outputFilename;
	//			std::cout << "Ime fajla u kom se snima slika: ";
	//			std::cin >> outputFilename;
	//			outputFilename = outputFilename + "." + format;


	//			image.exportImage(outputFilename);
	//			generatedFile = true;

	//		}
	//		break;
	//		case 's':
	//		{
	//			image.saveProject(".jsonTestRun.json");
	//			image.loadProject(".jsonTestRun.json");
	//			image.executeComposites();
	//			image.saveProject(".jsonTestRunTest2.json");
	//			image.exportImage("jsonTestRun.bmp");
	//		}
	//		break;
	//		case 'x':
	//		{


	//			if (!generatedFile)
	//			{
	//				int userChoice0;
	//				std::cout << "Zelite li da snimite rad? Uneti 1 za DA, 0 za NE:" << std::endl;
	//				std::cin >> userChoice0;
	//				if (userChoice0 == 1)
	//				{


	//					std::string userActivatedLayers;
	//					std::cout << "Izaberite slojeve koji ucestvuju u stvaranju slike tako sto 1 predstavlja sloj na dnu a X sloj na vrhu." << std::endl <<
	//						"Ako se ne odrede slojevi, svi postojeci ce ucestvovati: ";
	//					std::cin.ignore();
	//					std::getline(std::cin, userActivatedLayers);
	//					image.deactivateLayers(userActivatedLayers);
	//					std::string format;
	//					std::cout << "Uneti format slike u kom se snima fajl. Podrzani formati su: bmp, pam: ";
	//					std::cin >> format;

	//					if (format != "bmp" && format != "pam")
	//					{
	//						std::cerr << "Pokusali ste izabrati formati koji nije podrzan pokusajte ponovo!";
	//						std::cout << "Podrzani formati su: bmp, pam: ";
	//						std::cin >> format;
	//					}

	//					std::string outputFilename;
	//					std::cout << "Ime fajla u kom se snima slika: ";
	//					std::cin >> outputFilename;
	//					outputFilename = outputFilename + "." + format;


	//					image.exportImage(outputFilename);
	//					exit(0);
	//				}
	//				else if (userChoice0 == 0)
	//				{
	//					exit(0);
	//				}
	//			}
	//			else exit(0);

	//		}


	//		default:
	//			break;
	//		}

	//	}

	//}
	
	
	
	return 0;
}
