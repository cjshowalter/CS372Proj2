#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include <cmath>
#include <vector>

class Shape {

public:
	virtual ~Shape() = default;
	//virtual double height()=0;
	//virtual double width()=0;
	virtual std::string generatePostScript() = 0;

//protected:
	double height;
	double width;
	double x;
	double y;
};

class Circle : public Shape {
public:
	Circle(double radius) {
		height = radius * 2;
		width = radius * 2;
	}
	std::string generatePostScript() override
	{
		std::string circleString = "";
		circleString += std::to_string(height / -2);
		circleString += " ";
		circleString += std::to_string(width / -2);
		circleString += " translate\n";
		circleString += std::to_string(height / 2);
		circleString += " ";
		circleString += std::to_string(width / 2);
		circleString += " ";
		circleString += std::to_string(width / 2);
		circleString += " 0 360 arc closepath\n";
		circleString += "stroke\n";

		circleString += std::to_string(height / 2);
		circleString += " ";
		circleString += std::to_string(width / 2);
		circleString += " translate\n";
		return circleString;
	}
};

class Polygon : public Shape {
public:
	Polygon() = default;
	Polygon(int numSides, double sideLength)
	{
		sideLength_g = sideLength;
		numSides_g = numSides;
		const double pi = 3.141592653589793238;

		if (numSides % 2 == 1)
		{
			height = sideLength*(1 + cos(pi / numSides)) / (2 * sin(pi / numSides));
			width = (sideLength*sin(pi*(numSides - 1) / (2 * numSides)) / (sin(pi / numSides)));
		}
		else if (numSides % 4 != 0) // numSides%2==0
		{
			height = sideLength * (cos(pi / numSides)) / (sin(pi / numSides));
			width = sideLength / (sin(pi / numSides));
		}
		else // numSides%2 == 0 && numSides%4 == 0
		{
			height = sideLength*(cos(pi / numSides)) / (sin(pi / numSides));
			width = height;
		}
	}
	std::string generatePostScript() override
	{

		int totalAngle = (numSides_g - 2) * 180;
		int anglePerSide = 180 - totalAngle / numSides_g;
		std::string sideAngle = std::to_string(anglePerSide);

		std::string myLength = std::to_string(sideLength_g);

		std::string polyString = "";
		polyString += std::to_string(sideLength_g / -2);
		polyString += " ";
		polyString += std::to_string(height / -2);
		polyString += " translate\n";
		polyString += "newpath\n";

		//polyString += std::to_string(width);
		//polyString += " ";
		//polyString += " 0 translate\n";
		polyString += "0 0 moveto\n";

		for (int i = 0; i < numSides_g; i++)
		{
			polyString += myLength + " 0" + " lineto\n";
			polyString += myLength + " 0" + " translate\n";
			polyString += sideAngle + " rotate\n";

		}
		polyString += "closepath\n";
		polyString += "stroke\n";
		polyString += std::to_string(sideLength_g / 2);
		polyString += " ";
		polyString += std::to_string(height / 2);
		polyString += " translate\n";


		return polyString;
	}

private:
	double sideLength_g;
	double numSides_g;
};

class Rectangle : public Shape {
public:
	Rectangle(double w, double h) {
		height = h;
		width = w;
	}
	std::string generatePostScript() override
	{
        negHalfHeight_=-1.0*height/2.0;
        negHalfWidth_=-1.0*width/2.0;

		std::string rectangleString = "";
		rectangleString += "0";
		rectangleString += " ";
		rectangleString += "0";
		rectangleString += " moveto\n";

        rectangleString += std::to_string(negHalfWidth_);
		rectangleString += " ";
		rectangleString += std::to_string(negHalfHeight_);
		rectangleString += " moveto\n";
		rectangleString += std::to_string(negHalfWidth_);
		rectangleString += " ";
		rectangleString += std::to_string(negHalfHeight_);
		rectangleString += " translate\n";

		rectangleString += std::to_string(width);
		rectangleString += " ";
		rectangleString += "0";     					// Bottom
		rectangleString += " ";
		rectangleString += "rlineto\n";

		rectangleString += "0";
		rectangleString += " ";
		rectangleString += std::to_string(height);      // Right
		rectangleString += " ";
		rectangleString += "rlineto\n";

		rectangleString += std::to_string(width*-1);
		rectangleString += " ";
		rectangleString += "0";      					// Top
		rectangleString += " ";
		rectangleString += "rlineto\n";

		rectangleString += "closepath\n";               // Left
		rectangleString += "stroke\n";
		return rectangleString;
	}
private:
    double negHalfHeight_;
    double negHalfWidth_;
};

class Spacer : public Shape {
public:
	Spacer(double w, double h) {
		width = w;
		height = h;
		x = 0;
		y = 0;
	}
	std::string generatePostScript() override
	{
		std::string SpacerString = "newpath\n";
		SpacerString += std::to_string(x);
		SpacerString += " ";
		SpacerString += std::to_string(y);
		SpacerString += " moveto\n";

		SpacerString += std::to_string(width);
		SpacerString += " ";
		SpacerString += std::to_string(x);
		SpacerString += " rlineto\n";

		SpacerString += std::to_string(y);
		SpacerString += " ";
		SpacerString += std::to_string(height);
		SpacerString += " rlineto\n";

		SpacerString += std::to_string(-width);
		SpacerString += " ";
		SpacerString += std::to_string(x);
		SpacerString += " rlineto closepath\n";
		return SpacerString;
	}
};

class Square : public Polygon {
public:
	Square(double sideLength) : Polygon(4, sideLength) {}
};

class Triangle : public Polygon {
public:
	Triangle(double sideLength) : Polygon(3, sideLength) {}
};

class Layered : public Shape
{
public:
	Layered(std::vector<Shape*> shapeListGiven)
	{
		shapeList = shapeListGiven;
		int width = 0;
		int height = 0;

		for(auto i=0; i<shapeList.size(); ++i)
        {
            if(width < shapeList[i]->width)
            {
                width = shapeList[i]->width;
            }
            if(height < shapeList[i]->height)
            {
                height = shapeList[i]->height;
            }
        }
	}
	std::string generatePostScript()
	{
		std::string totalString = "newpath\n";
		for (unsigned int i = 0; i<shapeList.size(); ++i)
		{
			totalString += shapeList[i]->generatePostScript();
		}
		return totalString;
	}

private:
	std::vector<Shape*> shapeList;
};

class Scaled : public Shape
{
public:
	Scaled(Shape &shape, double fx, double fy) {
		std::string s = shape.generatePostScript();
		ScaleString = std::to_string(fx) + " " + std::to_string(fy) + " scale\n";
		ScaleString += s;
	}
	std::string generatePostScript() override {
		return ScaleString;
	}

private:
	std::string ScaleString;
};

class Rotated : public Shape {
public:
	Rotated(Shape &shape, int rotationAngle)
		:refShape(shape), rotAngle(rotationAngle) {}

	std::string generatePostScript() override
	{
		std::string RotateString = std::to_string(rotAngle);
		RotateString += " rotate\n";
		RotateString += refShape.generatePostScript();

		return RotateString;
	}

private:
	Shape &refShape;
	int rotAngle;
};
#endif // SHAPE_HPP
