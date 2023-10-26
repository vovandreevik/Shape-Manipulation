#pragma once
#include "Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle();
	Rectangle(float leftX, float leftY, float rightX, float rightY);
	~Rectangle();

	float getArea();
	rectangle_t getFrameRect();
	void move(float x, float y);
	void move(point_t& newCentre);
	void scale(float k);
	std::string getName();
	Shape* clone();
private:
	point_t leftPoint_;
	point_t rightPoint_;
};
