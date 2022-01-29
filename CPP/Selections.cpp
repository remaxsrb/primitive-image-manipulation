#include"Selections.h"

Selection::Selection(const std::list <Rechtangle>& vOfRechtangles, std::string& givenName, int layerNo) 
{
	std::for_each(vOfRechtangles.cbegin(), vOfRechtangles.cend(), [this](Rechtangle r) 
		{
			rechtangles.insert(r);
		});
	this->name = givenName;
	this->layerNo = layerNo;
}
Selection ::Selection(const Selection& s) 
{
	this->rechtangles = s.rechtangles;
	this->name = s.name;
	this->layerNo = s.layerNo;
}
int Selection::getLayerNumber() const { return this->layerNo; }
std::string& Selection::getName()  { return this->name; }
std::set<Rechtangle>& Selection::getRechtangles()  { return this->rechtangles; };