#include"Pixel.h"



Pixel::Pixel() : red(MIN_PIXEL_VALUE), green(MIN_PIXEL_VALUE), blue(MIN_PIXEL_VALUE), alpha(MAX_TRANSPARENCY) {}
Pixel::Pixel(uint8_t _red, uint8_t _green, uint8_t _blue, uint8_t _alpha)
{
	if (_red > MAX_PIXEL_VALUE)
		this->red = MAX_PIXEL_VALUE;
	else
		this->red = _red;
	if (_green > MAX_PIXEL_VALUE)
		this->green = MAX_PIXEL_VALUE;
	else
		this->green = _green;
	if (_blue > MAX_PIXEL_VALUE)
		this->blue = MAX_PIXEL_VALUE;
	else
		this->blue = _blue;
	if (_alpha > MIN_TRANSPARENCY)
		this->alpha = MIN_TRANSPARENCY;
	else
		this->alpha = _alpha;

}

Pixel& Pixel:: operator = (const Pixel& px) 
{
	this->red = px.red;
	this->green = px.green;
	this->blue = px.blue;
	this->alpha = px.alpha;

	return *this;
}

uint8_t Pixel::getRed() const { return this->red; }
uint8_t Pixel::getGreen() const { return this->green; }
uint8_t Pixel::getBlue() const { return this->blue; }
uint8_t Pixel::getAlpha() const { return this->alpha; }

void Pixel::setRed(uint8_t newRed) 
{
	if (newRed > MAX_PIXEL_VALUE)
		this->red = MAX_PIXEL_VALUE;
	else if (newRed < MIN_PIXEL_VALUE)
		this->red = MIN_PIXEL_VALUE;
	else this->red = newRed;
	
}
void Pixel::setGreen(uint8_t newGreen) 
{
	if (newGreen > MAX_PIXEL_VALUE)
		this->green = MAX_PIXEL_VALUE;
	else if (newGreen < MIN_PIXEL_VALUE)
		this->green = MIN_PIXEL_VALUE;
	else this->green = newGreen;
	
}
void Pixel::setBlue(uint8_t newBlue)
{
	if (newBlue > MAX_PIXEL_VALUE)
		this->blue = MAX_PIXEL_VALUE;
	else if (newBlue < MIN_PIXEL_VALUE)
		this->blue = MIN_PIXEL_VALUE;
	else this->blue = newBlue;
}
void Pixel::setAlpha(uint8_t newAlpha) 
{
	if (newAlpha > MIN_TRANSPARENCY)
		this->alpha = MIN_TRANSPARENCY;
	else if (newAlpha < MAX_TRANSPARENCY)
		this->alpha = MAX_TRANSPARENCY;
	else this->alpha = newAlpha;

}

void Pixel::toGrayscale() 
{
	this->red = (this->getRed() + this->getGreen() + this->getBlue()) / 3;
	this->green = (this->getRed() + this->getGreen() + this->getBlue()) / 3;
	this->blue = (this->getRed() + this->getGreen() + this->getBlue()) / 3;
}
void Pixel::toBlackAndWhite() 
{
	if (((this->getRed() + this->getGreen() + this->getBlue()) / 3) > 127) 
	{
		this->red = MAX_PIXEL_VALUE;
		this->green = MAX_PIXEL_VALUE;
		this->blue = MAX_PIXEL_VALUE;
	}
	else 
	{
		this->red = MIN_PIXEL_VALUE;
		this->green = MIN_PIXEL_VALUE;
		this->blue = MIN_PIXEL_VALUE;
	}
}
void Pixel::inverse() 
{
	this->red = (_CMATH_::abs(this->red - MAX_PIXEL_VALUE));
	this->green = (_CMATH_::abs(this->green - MAX_PIXEL_VALUE));
	this->blue = (_CMATH_::abs(this->blue - MAX_PIXEL_VALUE));
}
void Pixel::median(std::vector<Pixel>& pxs)
{
	
	std::vector<uint8_t> reds;
	std::vector<uint8_t> blues;
	std::vector<uint8_t> greens;
	std::for_each(pxs.begin(), pxs.end(), [&](Pixel& px)
		{
			reds.push_back(px.getRed());
			blues.push_back(px.getBlue());
			greens.push_back(px.getGreen());
		});
	std::sort(reds.begin(),reds.end(),std::greater<uint8_t>());
	std::sort(blues.begin(), blues.end(), std::greater<uint8_t>());
	std::sort(greens.begin(), greens.end(), std::greater<uint8_t>());

	if (pxs.size() % 2 != 0) 
	{
		this->red = static_cast<uint8_t>(round(reds[pxs.size() / 2]));
		this->blue = static_cast<uint8_t>(round(blues[pxs.size() /2 ]));
		this->green = static_cast<uint8_t>(round(greens[pxs.size() / 2]));
	}
	else
	{

		this->red = static_cast<uint8_t>(round((reds[(pxs.size() - 1) / 2] + reds[pxs.size() / 2]) / 2));
		this->blue = static_cast<uint8_t>(round((blues[(pxs.size() - 1) / 2] + blues[pxs.size() / 2]) / 2));
		this->green = static_cast<uint8_t>(round((greens[(pxs.size() - 1) / 2] + greens[pxs.size() / 2]) / 2));

	}
}
void Pixel::add(int i) 
{
	this->red += i;
	this->green += i;
	this->blue += i;
}
void Pixel::sub(int i) 
{
	this->red -= i;
	this->green -= i;
	this->blue -= i;
}
void Pixel::inverseSub(int i)
{
	this->red = i-this->red;
	this->green  = i - this->green;
	this->blue = i - this->blue;
}
void Pixel::mul(int i) 
{
	this->red *= i;
	this->green *= i;
	this->blue *= i;
}
void Pixel::div(int i)
{
	this->red /= i;
	this->green /= i;
	this->blue /= i;
}
void Pixel::inverseDiv(int i)
{
	if (this->red != 0)
		this->red = i / this->red;
	if (this->green != 0)
		this->green = i / this->green;
	if (this->blue != 0) 
		this->blue = i / this->blue;
}
void Pixel::power(int i) 
{
	this->red = (int)pow(this->red, i);
	this->green = (int)pow(this->green, i);
	this->blue = (int)pow(this->blue, i);
}
void Pixel::Log() 
{
	this->red = (int)(round(log(this->red)));
	this->green = (int)(round(log(this->green)));
	this->blue = (int)(round(log(this->blue)));
}
void Pixel::min(int min) 
{
	if (this->red > min)
		this->red = min;
	if (this->green > min)
		this->green = min;
	if (this->blue > min)
		this->blue = min;
}
void Pixel::max(int max)
{
	if (this->red < max)
		this->red = max;
	if (this->green < max)
		this->green = max;
	if (this->blue < max)
		this->blue = max;
}
void Pixel::abs() 
{
	this->red = _CMATH_::abs(this->red);
	this->green = _CMATH_::abs(this->green);
	this->blue = _CMATH_::abs(this->blue);
}