#include "CompositeShape.h"

CompositeShape::CompositeShape() {
	pos_.x = 0.0;
	pos_.y = 0.0;
	size_ = 0;
}

CompositeShape::~CompositeShape() = default;

void CompositeShape::addShape(Shape* shape) {
	Shape* copyShape;
	copyShape = shape->clone();
	shapes_[size_] = copyShape;
	size_++;

	pos_.x = this->getFrameRect().pos.x;
	pos_.y = this->getFrameRect().pos.y;
}

float CompositeShape::getArea() {
	float area = 0;
	for (int i = 0; i < size_; i++) {
		area += shapes_[i][0].getArea();
	}
	return area;
}

Shape* CompositeShape::clone() {
	Shape* shape;
	CompositeShape newCompositeShape;
	
	for (int i = 0; i < size_; i++) {
		newCompositeShape.addShape(shapes_[i]);
	}
	newCompositeShape.pos_ = this->pos_;
	shape = &newCompositeShape;
	return shape;
}

std::string CompositeShape::getName() {
	return "COMPLEX";
}

rectangle_t CompositeShape::getFrameRect() {
	float leftX = 1e10, leftY = 1e10, rightX = -1e10, rightY = -1e10;
	rectangle_t current{};
	rectangle_t frame{};
	for (int i = 0; i < size_; i++) {
		current = shapes_[i][0].getFrameRect();
		
		float currentLeftX = current.pos.x - current.width / 2;
		float currentLeftY = current.pos.y - current.height / 2;
		float currentRightX = current.pos.x + current.width / 2;
		float currentRightY = current.pos.y + current.height / 2;

		if (leftX > currentLeftX) {
			leftX = currentLeftX;
		}
		if (leftY > currentLeftY) {
			leftY = currentLeftY;
		}
		if (rightX < currentRightX) {
			rightX = currentRightX;
		}
		if (rightY < currentRightY) {
			rightY = currentRightY;
		}
	}
	frame.width = rightX - leftX;
	frame.height = rightY - leftY;
	frame.pos.x = leftX + frame.width / 2;
	frame.pos.y = rightY + frame.height / 2;
	return frame;
}

void CompositeShape::move(float x, float y) {
	for (int i = 0; i < size_; i++) {
		shapes_[i]->move(x, y);
	}
}

void CompositeShape::move(point_t& newCentre) {
	for (int i = 0; i < size_; i++) {
		point_t tp{};
		tp.x = shapes_[i][0].getFrameRect().pos.x + newCentre.x - pos_.x;
		tp.y = shapes_[i][0].getFrameRect().pos.y + newCentre.y - pos_.y;
		shapes_[i][0].move(tp);
	}
	pos_.x = newCentre.x;
	pos_.y = newCentre.y;
}

void CompositeShape::scale(float k) {

	for (int i = 0; i < size_; i++) {
		shapes_[i][0].scale(k);
	}
}