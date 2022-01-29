#pragma once


struct PAMHeader 
{
	std::string id = "P7";
	int32_t height=0;
	int32_t width=0;
	uint32_t depth=0; //number of chanels
	uint32_t maxVal=0;
	std::string type="";
	std::string end = "ENDHDR";

	
};

