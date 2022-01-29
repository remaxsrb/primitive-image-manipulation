#include"Formater.h"
#include"BMP.h"

BMPFormater::BMPFormater(Image& image) :Formater(image)
{  }

void BMPFormater::read(std::string sourceFileName)
{
    {
        std::ifstream input{ sourceFileName, std::ios_base::binary };
        if (input)
        {
           

            BMPFileHeader fileHeader;
            BMPInfoHeader infoHeader;
            BMPColorHeader colorHeader;

            uint32_t row_stride{ 0 };

            input.read((char*)&fileHeader, sizeof(fileHeader));
            if (fileHeader.fileType != BMPID) {
                throw std::runtime_error("Error! Unrecognized file format.");
            }

            input.read((char*)&infoHeader, sizeof(infoHeader));

            this->bitsPerPixel= infoHeader.bitsPerPixel;
           this->height=infoHeader.height;
           this->width=infoHeader.width;

            if (infoHeader.height < 0)
                throw std::runtime_error("The program can treat only BMP images with the origin in the bottom left corner!");

            // Jump to the pixel data location
            input.seekg(fileHeader.data_offset, input.beg);


           this->pixels.resize(this->width * this->height * this->bitsPerPixel / 8);

            // Here we check if we need to take into account row padding
            if (infoHeader.width % 4 == 0)
                input.read((char*)this->pixels.data(), this->pixels.size());

            else {
                row_stride = infoHeader.width * infoHeader.bitsPerPixel / 8;

               // uint32_t new_stride = 0;
                uint32_t new_stride = row_stride;
                    while (new_stride % 4 != 0)
                        new_stride++;
                

                std::vector<uint8_t> padding_row(new_stride - row_stride);

                for (int y = 0; y < infoHeader.height; ++y) { //cita red po red i svaki red peduje
                    input.read((char*)(this->pixels.data() + row_stride * y), row_stride);
                    input.read((char*)padding_row.data(), padding_row.size());
                }

            }



            //zamena crvenog i plavog piksela BGR(A) -> RGB(A)
            if (infoHeader.bitsPerPixel == 32)
            {
                //iterator se inkrementira za 4
                for (int i = 0; i < infoHeader.width * infoHeader.height * infoHeader.bitsPerPixel / 8; i += 4)
                {
                    uint8_t temp = this->pixels[i];
                    this->pixels[i] = this->pixels[i + 2];
                    this->pixels[i + 2] = temp;
                }

               
            }
            else if (infoHeader.bitsPerPixel == 24)
            {
                //iterator se inkrementira za 3
                for (int i = 0; i < infoHeader.width * infoHeader.height * infoHeader.bitsPerPixel / 8; i += 3)
                {
                    uint8_t temp = this->pixels[i];
                    this->pixels[i] = this->pixels[i + 2];
                    this->pixels[i + 2] = temp;
                }
                
            }
            
            Layer newLayer(sourceFileName,this->height,this->width,this->bitsPerPixel,this->pixels);

            if (image->numberOfLayers != 0)
                //proveri da li treba prosiriti prethodne slojeve ili tek ucitani sloj
                image->resizeLayers(newLayer);

            image->layers.push_back(newLayer);
            image->numberOfLayers++;

            input.close();
        }
        else {
            throw std::runtime_error("Unable to open the input image file.");
        }
    }
}
void BMPFormater:: writeToFile(std::string outputFileName)
{
    std::ofstream output{ outputFileName, std::ios_base::binary };
    if (output)
    {
        BMPFileHeader fileHeader;
        BMPInfoHeader infoHeader;
        BMPColorHeader colorHeader;

        
        this->height = image->layers.back().getHeight(); //validno je ovako reci jer se nakon ubacivanja garantuje indenticnost dimenzija
        this->width = image->layers.back().getWidth();
        this->pixels.resize(this->height * this->width * 4);
        image->createExportData(this->pixels);

        std::vector<uint8_t>::iterator it;

        for (it = this->pixels.begin(); it!= this->pixels.end(); ++it)
    {
      /*  for (int i = 0; i < 4; i++)
            std::cout << *it;
        std::cout<<std::endl;
        system("pause");*/
    }


        infoHeader.headerSize = sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
        fileHeader.data_offset = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + sizeof(BMPColorHeader);
        fileHeader.fileSize = fileHeader.data_offset;

        infoHeader.bitsPerPixel = 32;
        infoHeader.height = this->height;
        infoHeader.width = this->width;

        fileHeader.fileSize +=this->pixels.size();
        output.write((const char*)&fileHeader, sizeof(fileHeader));
        output.write((const char*)&infoHeader, sizeof(infoHeader));
        output.write((const char*)&colorHeader, sizeof(colorHeader));
        output.write((const char*)this->pixels.data(), this->pixels.size());

        output.close();
    }
    else {
        throw std::runtime_error("Unable to open the output image file.");
    }
}