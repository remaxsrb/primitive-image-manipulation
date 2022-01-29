#pragma once
#include"Rechtangle.h"
Rechtangle::Rechtangle(int32_t _x, int32_t _y, int32_t _height, int32_t _width) : x(_x), y(_y), height(_height), width(_width){}
Rechtangle::Rechtangle(const Rechtangle& r) 
{
	this->x = r.x;
	this->y = r.y;
	this->height = r.height;
	this->width = r.width;
}

int32_t Rechtangle::getX() const { return this->x; }
int32_t Rechtangle::getY()  const { return this->y; }
int32_t Rechtangle::getHeight() const { return this->height; }
int32_t Rechtangle::getWidth() const { return this->width; }
bool Rechtangle::operator < (const Rechtangle& right) const 
{
	if (this->x < right.x) return 1;
	else if (this->x > right.x) return 0;
	else if (this->y < right.y) return 1;
	else if (this->y > right.y) return 0;
	else return 1;
	/*if (this->width == right.width && this->height == right.height) return 0;
	else return 1;*/
}
void Rechtangle::setHeight(int32_t newHeight) { this->height = newHeight; }
void Rechtangle::setWidth(int32_t newWidth) { this->width = newWidth; }
void Rechtangle::setY(int32_t newY) { this->y = newY; }
void Rechtangle::setX(int32_t newX) { this->x = newX; }