#pragma once
#include"Rechtangle.h"
#include<set>
#include<vector>
#include<list>
#include<algorithm>
class Selection 
{
private:
	std::set<Rechtangle> rechtangles;
	std::string name;
	int layerNo;
public:
	Selection() { this->layerNo = 0; }
	Selection(const std::list<Rechtangle>& vOfRechtangles, std::string& givenName, int layerNo);
	Selection(const Selection &s);
	int getLayerNumber() const;
	std::string& getName() ;
	std::set<Rechtangle>& getRechtangles() ;
	~Selection() {}

};