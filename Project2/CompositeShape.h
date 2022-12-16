#pragma once
#include "Shape.h"

class CompositeShape : public Shape
{
public:
	CompositeShape();
	~CompositeShape();

	void addShape(Shape* shape);
	float getArea();
	Shape* clone();
	rectangle_t getFrameRect();
	std::string getName();
	void move(float x, float y);
	void move(point_t& newCentre);
	void scale(float k);
private:
	Shape** shapes_ = new Shape*;
	int size_;
	point_t pos_;
};