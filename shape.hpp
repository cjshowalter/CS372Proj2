#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include <cmath>
#include <vector>
#include <memory>
using std::unique_ptr;
using std::make_unique;

class Shape {

public:
	virtual ~Shape() = default;
	//virtual double height()=0;
	//virtual double width()=0;
	virtual std::string generatePostScript() = 0;

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
		std::string circleString = "newpath\n";
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

//Given a number of sides and a length, create a shape with that number of sides
//with given length
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
		halfHeight_ = height / 2.0;
		halfWidth_ = width / 2.0;

		std::string rectangleString = "newpath\n";
		rectangleString += "0";
		rectangleString += " ";
		rectangleString += "0";
		rectangleString += " moveto\n";

		rectangleString += std::to_string(-1 * halfWidth_); //move to draw at origin
		rectangleString += " ";
		rectangleString += std::to_string(-1 * halfHeight_);
		rectangleString += " moveto\n";
		rectangleString += std::to_string(-1 * halfWidth_);
		rectangleString += " ";
		rectangleString += std::to_string(-1 * halfHeight_);
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

		rectangleString += std::to_string(halfWidth_);//move back from origin
		rectangleString += " ";
		rectangleString += std::to_string(halfHeight_);
		rectangleString += " moveto\n";
		rectangleString += std::to_string(halfWidth_);
		rectangleString += " ";
		rectangleString += std::to_string(halfHeight_);
		rectangleString += " translate\n";

		return rectangleString;
	}
private:
	double halfHeight_;
	double halfWidth_;
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
//Create a 4 sided polygon with the given side length
class Square : public Polygon {
public:
	Square(double sideLength) : Polygon(4, sideLength) {}
};
//Create a 3 sided polygon with the given side length
class Triangle : public Polygon {
public:
	Triangle(double sideLength) : Polygon(3, sideLength) {}
};

class Custom : public Shape
{
public:
	Custom(double sideLength)
	{
		width = sideLength;
		height = sideLength;
	}
	std::string generatePostScript()
	{
		// Head
		std::string totalString = "";
		Square s_0(width);
		totalString += s_0.generatePostScript();

		totalString += std::to_string(width / 4);
		totalString += " ";
		totalString += std::to_string(height / 4);
		totalString += " translate\n";

		// Eyes
		Square s_1(width / 5);
		totalString += s_1.generatePostScript();

		totalString += std::to_string(-width / 4);
		totalString += " ";
		totalString += std::to_string(-height / 4);
		totalString += " translate\n";

		totalString += std::to_string(-width / 4);
		totalString += " ";
		totalString += std::to_string(height / 4);
		totalString += " translate\n";

		totalString += s_1.generatePostScript();

		totalString += std::to_string(width / 4);
		totalString += " ";
		totalString += std::to_string(-height / 4);
		totalString += " translate\n";

		// Mouth
		Rectangle mouth((width / 2), (height / 4));
		
		totalString += std::to_string(0);
		totalString += " ";
		totalString += std::to_string(-height / 4);
		totalString += " translate\n";
		
		totalString += mouth.generatePostScript();

		totalString += std::to_string(0);
		totalString += " ";
		totalString += std::to_string(height / 4);
		totalString += " translate\n";

		// Teeth
		Square teeth(width / 8);
		double halfTeeth = (width / 8);
		double quarterTeeth = halfTeeth/2;
		int totalTeeth = (width / 8) - 4;
		
		for (int i = 1; i <= 2; ++i) {
			int scale = 0;
			
			for (int j = 1; j <= totalTeeth/2; ++j) {
				if (i==1) {
					totalString += std::to_string((-width / 4));
					totalString += " ";
					totalString += std::to_string((-height / 4));
					totalString += " translate\n";
					totalString += std::to_string((quarterTeeth*j) + (quarterTeeth*scale));
					totalString += " ";
					totalString += std::to_string(quarterTeeth*i);
					totalString += " translate\n";
					totalString += teeth.generatePostScript();
					totalString += std::to_string((-quarterTeeth*j) - (quarterTeeth*scale));
					totalString += " ";
					totalString += std::to_string(-quarterTeeth*i);
					totalString += " translate\n";
					totalString += std::to_string((width / 4));
					totalString += " ";
					totalString += std::to_string((height / 4));
					totalString += " translate\n";
					scale++;
				}
				if (i==2) {
					totalString += std::to_string((-width / 4));
					totalString += " ";
					totalString += std::to_string((-height / 4));
					totalString += " translate\n";
					totalString += std::to_string((quarterTeeth*j) + (quarterTeeth*scale));
					totalString += " ";
					totalString += std::to_string(-quarterTeeth);
					totalString += " translate\n";
					totalString += teeth.generatePostScript();
					totalString += std::to_string((-quarterTeeth*j) - (quarterTeeth*scale));
					totalString += " ";
					totalString += std::to_string(quarterTeeth);
					totalString += " translate\n";
					totalString += std::to_string((width / 4));
					totalString += " ";
					totalString += std::to_string((height / 4));
					totalString += " translate\n";
					scale++;	
				}
			}
		}
		return totalString;
	}
};
class Layered : public Shape
{
public:
	Layered(std::vector<unique_ptr<Shape>> shapeListGiven)
	{
		shapeList = std::move(shapeListGiven);
		double width = 0;
		double height = 0;

		for (unsigned int i = 0; i<shapeList.size(); ++i)
		{
			if (width < shapeList[i]->width)
			{
				width = shapeList[i]->width;
			}
			if (height < shapeList[i]->height)
			{
				height = shapeList[i]->height;
			}
		}
	}
	std::string generatePostScript()
	{
		std::string totalString = "";
		for (unsigned int i = 0; i<shapeList.size(); ++i)
		{
			totalString += shapeList[i]->generatePostScript();
		}
		return totalString;
	}

private:
	std::vector<unique_ptr<Shape>> shapeList;
};

class Scaled : public Shape
{
public:
	Scaled(Shape &shape, double fx, double fy) {
		std::string s = shape.generatePostScript();
		ScaleString = std::to_string(fx) + " " + std::to_string(fy) + " scale\n";
		ScaleString += s;
		ScaleString += std::to_string(1 / fx) + " " + std::to_string(1 / fy) + " scale\n";

		height = shape.height * fy;
		width = shape.width * fx;
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
		:refShape(shape), rotAngle(rotationAngle) {

		if (rotationAngle == 90 || rotationAngle == 270)
		{
			height = shape.width;
			width = shape.height;
		}
		else
		{
			height = shape.height;
			width = shape.width;
		}
	}

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

class Vertical : public Shape {
public:
	Vertical(std::vector<unique_ptr<Shape>> vertVec)
	{
		vertStack = std::move(vertVec);
		height = 0;
		width = 0;
		for (unsigned int i = 0; i<vertStack.size(); ++i) {
			height += std::move((vertStack[i]->height) + 1);
			width += std::move(vertStack[i]->width);
		}
	}

	std::string generatePostScript() override {
		std::string vertString = "\n% **** VERTICAL PS ****\n\n";
		double maxWidth = 0;

		for (unsigned int i = 0; i<vertStack.size(); ++i) {
			if (vertStack[i]->width > maxWidth) {
				maxWidth = std::move(vertStack[i]->width);
			}
		}
		for (unsigned int i = 0; i<vertStack.size(); ++i) {
			vertString += std::to_string(maxWidth);
			vertString += " ";
			vertString += std::to_string(vertStack[i]->height / 2);
			vertString += " translate\n";
			vertString += vertStack[i]->generatePostScript();
			vertString += std::to_string(-maxWidth);
			vertString += " ";
			vertString += std::to_string((vertStack[i]->height / 2) + 1);
			vertString += " translate\n";
			vertString += "\n";
		}
		//vertString += "showpage\n\n";
		vertString += "% **** VERTICAL END ****\n";
		return vertString;
	}

private:
	std::vector<unique_ptr<Shape>> vertStack;
};

class Horizontal : public Shape {
public:
	Horizontal(std::vector<unique_ptr<Shape>> horizontalVec)
	{
		horizontalStack = std::move(horizontalVec);
		height = 0;
		width = 0;
		for (unsigned int i = 0; i<horizontalStack.size(); ++i) {
			height += std::move(horizontalStack[i]->height);
			width += std::move((horizontalStack[i]->width) + 1);
		}
	}

	std::string generatePostScript() override {

		std::string horizontalString = "\n% **** HORIZONTAL PS ****\n\n";
		double maxHeight = 0;

		for (unsigned int i = 0; i<horizontalStack.size(); ++i) {
			if (horizontalStack[i]->height > maxHeight) {
				maxHeight = std::move(horizontalStack[i]->height);
			}
		}

		for (unsigned int i = 0; i<horizontalStack.size(); ++i) {
			horizontalString += std::to_string(horizontalStack[i]->width / 2);
			horizontalString += " ";
			horizontalString += std::to_string(maxHeight);
			horizontalString += " translate\n";
			horizontalString += horizontalStack[i]->generatePostScript();
			horizontalString += std::to_string((horizontalStack[i]->width / 2) + 1);
			horizontalString += " ";
			horizontalString += std::to_string(-maxHeight);
			horizontalString += " translate\n";
			horizontalString += "\n";
		}
		//horizontalString += "showpage\n\n";
		horizontalString += "% **** HORIZONTAL END ****\n";
		return horizontalString;
	}

private:
	std::vector<unique_ptr<Shape>> horizontalStack;

};

#endif // SHAPE_HPP
