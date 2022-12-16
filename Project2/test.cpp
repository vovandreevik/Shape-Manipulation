#include <iostream>
#include <fstream>
#include "Shape.h"
#include "Rectangle.h"
#include "CompositeShape.h"

void sort(Shape** mass, int size);

void moveNewCentre(Shape* shape, float x, float y);

void isotropicScale(Shape* shape, float posX, float posY, float k);

Rectangle* readRect(std::ifstream& in);

void moveMass(Shape** mass, int count, std::ifstream& in);

void scaleMass(Shape** mass, int count, std::ifstream& in);

int main()
{
	std::cout << "Enter the input file: ";
	std::string inputFile;
	std::cin >> inputFile;

	std::ifstream in;

	try {
		in.open(inputFile);
		if (!in) {
			throw std::runtime_error("no such file or directory");
		}
	}
	catch (std::exception const& e) {
		std::cerr << "Error: " << e.what() << "\n";
		return -1;
	}

	int count = 0;
	int size = 0;
	std::string name;

	CompositeShape complex;
	std::string type;

	Shape** mass = new Shape * [50];

	while (!in.eof()) {
		in >> type;
		if (type == "COMPLEX") {
			in >> size;
			for (int i = 0; i < size; i++) {
				in >> name;
				if (name == "RECTANGLE") {
					Shape* shape = readRect(in);
					if (shape != NULL) {
						complex.addShape(shape);
					}
				}
				else {
					in.ignore(100, '\n');
				}
			}
			mass[count] = &complex;
			count++;
			
		}
		else if (type == "RECTANGLE") {
			Shape* shape = readRect(in);
			if (shape != NULL) {
				mass[count] = shape->clone();
				count++;
			}
		}
		else if (type == "MOVE") {
			moveMass(mass, count, in);
		}
		else if (type == "SCALE") {
			scaleMass(mass, count, in);
		}
		else {
			in.ignore(100, '\n');
		}
	}

	sort(mass, count);

	std::cout << "SHAPES AFTER SORTING: \n";
	for (int i = 0; i < count; i++) {
		std::cout << *(mass[i]) << '\n';
	}

	delete[] mass;
	in.close();
	return 0;
}

Rectangle* readRect(std::ifstream& in) {
	float leftX = 0.0, leftY = 0.0, rightX = 0.0, rightY = 0.0;
	in >> leftX >> leftY >> rightX >> rightY;
	if (rightX <= leftX or rightX <= leftY) {
		std::cerr << "Errors in the description of figures! (RECTANGLE is not accepted) \n";
		return NULL;
	}
	Rectangle rectangle(leftX, leftY, rightX, rightY);
	return &rectangle;
}

void moveNewCentre(Shape* shape, float x, float y) {
	point_t newCentre{};
	newCentre.x = x;
	newCentre.y = y;
	shape->move(newCentre);
}

void moveMass(Shape** mass, int count, std::ifstream& in) {
	float x = 0.0;
	float y = 0.0;
	in >> x >> y;
	for (int i = 0; i < count; i++) {
		moveNewCentre(mass[i], x, y);
	}
}

void isotropicScale(Shape* shape, float posX, float posY, float k) {
	point_t a1{};
	a1.x = shape->getFrameRect().pos.x + shape->getFrameRect().width / 2;
	a1.y = shape->getFrameRect().pos.y + shape->getFrameRect().height / 2;
	point_t isotropicCenter{};
	isotropicCenter.x = posX;
	isotropicCenter.y = posY;
	shape->move(isotropicCenter);
	point_t a2{};
	a2.x = shape->getFrameRect().pos.x + shape->getFrameRect().width / 2;
	a2.y = shape->getFrameRect().pos.y + shape->getFrameRect().height / 2;
	float x = a2.x - a1.x;
	float y = a2.y - a1.y;
	shape->scale(k);
	x *= k;
	y *= k;
	point_t newCentre{};
	newCentre.x = posX + x;
	newCentre.y = posY + y;
	shape->move(newCentre);
}

void scaleMass(Shape** mass, int count, std::ifstream& in) {
	float posX, posY, k;
	in >> posX >> posY >> k;
	for (int i = 0; i < count; i++) {
		isotropicScale(mass[i], posX, posY, k);
	}
}

void sort(Shape** mass, int size) {
	Shape* swapper;
	bool flag = 1;
	while (flag == 1) {
		for (int i = 0; i < size - 1; i++) {
			if (*(mass[i + 1]) < *(mass[i])) {
				swapper = &(*mass[i + 1]);
				mass[i + 1] = &(*mass[i]);
				mass[i] = &(*swapper);
			}
		}
		flag = 0;
	}
}