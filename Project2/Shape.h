#pragma once
#include "base-types.h"
#include <iostream>

class Shape
{
public:
	virtual float getArea() = 0;
	virtual Shape* clone() = 0;
	virtual std::string getName() = 0;
	virtual void move(float x, float y) = 0;
	virtual void move(point_t& newCentre) = 0;
	virtual rectangle_t getFrameRect() = 0;
	virtual void scale(float k) = 0;

	friend std::ostream& operator<< (std::ostream& out, Shape& s);
	bool operator< (Shape& right);
};