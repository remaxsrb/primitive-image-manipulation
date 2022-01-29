#pragma once
#include<vector>
#include<algorithm>
#include<cmath>
#define MIN_PIXEL_VALUE 0
#define MAX_PIXEL_VALUE 255

#define MIN_TRANSPARENCY 255 //neproziran
#define MAX_TRANSPARENCY 0

class Pixel 
{
private:
	uint8_t red;
	uint8_t green;
	uint8_t blue;
	uint8_t alpha;
public:
	Pixel();
	Pixel(uint8_t _red, uint8_t _green, uint8_t _blue, uint8_t _alpha);
	Pixel& operator = (const Pixel& px);
	uint8_t getRed() const;
	uint8_t getGreen() const;
	uint8_t getBlue() const;
	uint8_t getAlpha() const;

	void setRed(uint8_t newRed);
	void setGreen(uint8_t newGreen);
	void setBlue(uint8_t newBlue);
	void setAlpha(uint8_t newAlpha);

	void inverse();
	void toGrayscale();
	void toBlackAndWhite(); 
	void median(std::vector<Pixel>& pxs);
	void add(int i);
	void sub(int i);
	void inverseSub(int i);
	void mul(int i);
	void div(int i);
	void inverseDiv(int i);
	void power(int i);
	void Log();
	void min(int min);
	void max(int max);
	void abs();


	~Pixel() {}
};