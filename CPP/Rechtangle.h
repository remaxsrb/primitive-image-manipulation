#pragma once
#include<iostream>
class Rechtangle 
{
private:
	int32_t x=0;
	int32_t y=0;
	int32_t height=0;
	int32_t width=0;
public:
	
	Rechtangle(int32_t _x, int32_t _y, int32_t _height, int32_t _width);
	Rechtangle(const Rechtangle& r);

	int32_t getX()const;
	int32_t getY()const;
	int32_t getHeight()const;
	int32_t getWidth()const;
	bool operator < (const Rechtangle& right)const;
	void setHeight(int32_t newHeight);
	void setWidth(int32_t newWidth);
	void setX(int32_t newX);
	void setY(int32_t newY);
	~Rechtangle() {}
};