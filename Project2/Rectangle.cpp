#include "Rectangle.h"

Rectangle::Rectangle() 
{ 
	leftPoint_.x = 0.0; 
	leftPoint_.y = 0.0;
	rightPoint_.x = 0.0;
	rightPoint_.y = 0.0;
}
Rectangle::Rectangle(float leftX, float leftY, float rightX, float rightY) {
	leftPoint_.x = leftX;
	leftPoint_.y = leftY;
	rightPoint_.x = rightX;
	rightPoint_.y = rightY;
}
Rectangle::~Rectangle() = default;

float Rectangle::getArea() {
	return (rightPoint_.x - leftPoint_.x) * (rightPoint_.y - leftPoint_.y);
}

rectangle_t Rectangle::getFrameRect() {
	rectangle_t FrameRect{};
	point_t pos{};
	FrameRect.width = rightPoint_.x - leftPoint_.x;
	FrameRect.height = rightPoint_.y - leftPoint_.y;
	pos.x = (rightPoint_.x + leftPoint_.x) / 2;
	pos.y = (rightPoint_.y + leftPoint_.y) / 2;
	FrameRect.pos = pos;
	
	return FrameRect;
}

void Rectangle::move(float x, float y) {
	rightPoint_.x += x;
	rightPoint_.y += y;
	leftPoint_.x += x;
	leftPoint_.y += y;
}

void Rectangle::move(point_t& newCentre) {
	leftPoint_.x = newCentre.x - (rightPoint_.x - leftPoint_.x) / 2;
	leftPoint_.y = newCentre.y - (rightPoint_.y - leftPoint_.y) / 2;
	rightPoint_.x = newCentre.x + (rightPoint_.x - leftPoint_.x) / 2; 
	rightPoint_.y = newCentre.y + (rightPoint_.y - leftPoint_.y) / 2;
}

void Rectangle::scale(float k) {
	rectangle_t frame = getFrameRect();
	rightPoint_.x = frame.pos.x + frame.width / 2 * k;
	rightPoint_.y = frame.pos.y + frame.height / 2 * k;
	leftPoint_.x = frame.pos.x - frame.width / 2 * k;
	leftPoint_.y = frame.pos.y - frame.height / 2 * k;
}

std::string Rectangle::getName() {
	return "RECTANGLE";
}

Shape* Rectangle::clone() {
	Shape* cloneShape;
	Rectangle *rectangle = new Rectangle;
	rectangle->leftPoint_ = this->leftPoint_;
	rectangle->rightPoint_ = this->rightPoint_;
	cloneShape = rectangle;
	return cloneShape;
}