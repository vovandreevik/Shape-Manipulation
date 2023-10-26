#include <iomanip>
#include "Shape.h"
#include "Rectangle.h"

std::ostream& operator<< (std::ostream& out, Shape& shape) {
	float leftX = 0, leftY = 0, rightX = 0, rightY = 0;
	leftX = round((shape.getFrameRect().pos.x - shape.getFrameRect().width / 2) * 10) / 10;
	leftY = round((shape.getFrameRect().pos.y - shape.getFrameRect().height / 2) * 10) / 10;
	rightX = round((shape.getFrameRect().pos.x + shape.getFrameRect().width / 2) * 10) / 10;
	rightY = round((shape.getFrameRect().pos.y + shape.getFrameRect().height / 2) * 10) / 10;
	float area = round(shape.getArea() * 10) / 10;
	return (out << std::fixed << std::setprecision(1) << shape.getName() << " " << area << " (" << leftX << "; " << leftY << ") (" << rightX << "; " << rightY << ")");
}

bool Shape::operator< (Shape& right) {
	return (this->getArea() < right.getArea());
}