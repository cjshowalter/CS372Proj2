//Cameron Showalter
//Refactoring, Assignment 4
//CS 372
//4-26-17


#include "shape.hpp"
#include <string>	//std::string std::to_string
#include <cmath>	//std::sin std::cos 
#include <vector> //std::vector std::move
#include <memory> //std::shared_ptr std::make_shared


//Slightly better comments inside shape.hpp


//Class Circle
Circle::Circle(double radius) 
{
	height = radius * 2;
	width = radius * 2;
}
std::string Circle::generatePostScript()
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

//Class Polygon
Polygon::Polygon(int numSides, double sideLength)
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
std::string Polygon::generatePostScript()
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

//Class Rectangle
Rectangle::Rectangle(double w, double h) 
{
	height = h;
	width = w;
}
std::string Rectangle::generatePostScript()
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

//Class Spacer
Spacer::Spacer(double w, double h)
{
	width = w;
	height = h;
	x = 0;
	y = 0;
}
std::string Spacer::generatePostScript()
{
	std::string spacerString = "newpath\n";
	spacerString += std::to_string(x);
	spacerString += " ";
	spacerString += std::to_string(y);
	spacerString += " moveto\n";

	spacerString += std::to_string(width);
	spacerString += " ";
	spacerString += std::to_string(x);
	spacerString += " rlineto\n";

	spacerString += std::to_string(y);
	spacerString += " ";
	spacerString += std::to_string(height);
	spacerString += " rlineto\n";

	spacerString += std::to_string(-width);
	spacerString += " ";
	spacerString += std::to_string(x);
	spacerString += " rlineto closepath\n";
	return spacerString;
}

//Class Square
Square::Square(double sideLength) : Polygon(4, sideLength) {}

//Class Triangle
Triangle::Triangle(double sideLength) : Polygon(3, sideLength) {}

//Class Custom
Custom::Custom(double sideLength)
{
	width = sideLength;
	height = sideLength;
}
std::string Custom::generatePostScript()
{
	// Head
	std::string triangleString = "";
	Square s_0(width);
	triangleString += s_0.generatePostScript();

	triangleString += std::to_string(width / 4);
	triangleString += " ";
	triangleString += std::to_string(height / 4);
	triangleString += " translate\n";

	// Eyes
	Square s_1(width / 5);
	triangleString += s_1.generatePostScript();

	triangleString += std::to_string(-width / 4);
	triangleString += " ";
	triangleString += std::to_string(-height / 4);
	triangleString += " translate\n";

	triangleString += std::to_string(-width / 4);
	triangleString += " ";
	triangleString += std::to_string(height / 4);
	triangleString += " translate\n";

	triangleString += s_1.generatePostScript();

	triangleString += std::to_string(width / 4);
	triangleString += " ";
	triangleString += std::to_string(-height / 4);
	triangleString += " translate\n";

	// Mouth
	Rectangle mouth((width / 2), (height / 4));
	
	triangleString += std::to_string(0);
	triangleString += " ";
	triangleString += std::to_string(-height / 4);
	triangleString += " translate\n";
	
	triangleString += mouth.generatePostScript();

	triangleString += std::to_string(0);
	triangleString += " ";
	triangleString += std::to_string(height / 4);
	triangleString += " translate\n";

	// Teeth
	Square teeth(width / 8);
	double halfTeeth = (width / 8);
	double quarterTeeth = halfTeeth/2;

	// Top row of teeth
	int scale = 0;
	for (int ii = 1; ii <= 4; ++ii) {
		triangleString += std::to_string((-width / 4));
		triangleString += " ";
		triangleString += std::to_string((-height / 4));
		triangleString += " translate\n";
		triangleString += std::to_string((quarterTeeth*ii) + (quarterTeeth*scale));
		triangleString += " ";
		triangleString += std::to_string(quarterTeeth);
		triangleString += " translate\n";
		triangleString += teeth.generatePostScript();
		triangleString += std::to_string((-quarterTeeth*ii) - (quarterTeeth*scale));
		triangleString += " ";
		triangleString += std::to_string(-quarterTeeth);
		triangleString += " translate\n";
		triangleString += std::to_string((width / 4));
		triangleString += " ";
		triangleString += std::to_string((height / 4));
		triangleString += " translate\n";
		scale++;
	}
	// Bottom row of teeth
	scale = 0;
	for (int ii = 1; ii <= 4; ++ii) {
		triangleString += std::to_string((-width / 4));
		triangleString += " ";
		triangleString += std::to_string((-height / 4));
		triangleString += " translate\n";
		triangleString += std::to_string((quarterTeeth*ii) + (quarterTeeth*scale));
		triangleString += " ";
		triangleString += std::to_string(-quarterTeeth);
		triangleString += " translate\n";
		triangleString += teeth.generatePostScript();
		triangleString += std::to_string((-quarterTeeth*ii) - (quarterTeeth*scale));
		triangleString += " ";
		triangleString += std::to_string(quarterTeeth);
		triangleString += " translate\n";
		triangleString += std::to_string((width / 4));
		triangleString += " ";
		triangleString += std::to_string((height / 4));
		triangleString += " translate\n";
		scale++;
	}
	return triangleString;
}

//Class Scaled
Scaled::Scaled(Shape &shape, double fx, double fy)
{
	std::string s = shape.generatePostScript();
	scaledString = std::to_string(fx) + " " + std::to_string(fy) + " scale\n";
	scaledString += s;
	scaledString += std::to_string(1 / fx) + " " + std::to_string(1 / fy) + " scale\n";

	height = shape.height * fy;
	width = shape.width * fx;
}
std::string Scaled::generatePostScript()
{
	return scaledString;
}

//Class Rotated
Rotated::Rotated(Shape &shape, int rotationAngle)
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
std::string Rotated::generatePostScript()
{
	std::string rotatedString = std::to_string(rotAngle);
	rotatedString += " rotate\n";
	rotatedString += refShape.generatePostScript();

	return rotatedString;
}

// AdvancedShape shape class
AdvancedShape::AdvancedShape(std::vector<std::shared_ptr<Shape>> shapeList)
{
	//shapeList_ = std::move(shapeList);
	shapeList_ = shapeList;
}
std::string AdvancedShape::generatePostScript()
{
	std::string returnString = "";
	for (auto i = 0; i<shapeList_.size(); ++i)
	{	
		//translates half in the right direction (or not at all for layered)
		returnString += translateMe(shapeList_[i]);
		//draws the current shape
		returnString += shapeList_[i]->generatePostScript();
		//translate the last half of the current shape(not for layered, again)
		returnString += translateMe(shapeList_[i]);
	}
	return returnString;
}


// Layered shape class
Layered::Layered(std::vector<std::shared_ptr<Shape>> shapeListGiven): AdvancedShape(shapeListGiven)
{
	layeredStack = std::move(shapeListGiven);
	width = 0;
	height = 0;

	for (auto i = 0; i<layeredStack.size(); ++i){
		if (width < layeredStack[i]->width){
			width = layeredStack[i]->width;
		}
		if (height < layeredStack[i]->height){
			height = layeredStack[i]->height;
		}
	}
}
std::string Layered::translateMe(std::shared_ptr<Shape> currShape)
{
	return "0 0 translate\n";
}

// Vertical shape class
Vertical::Vertical(std::vector<std::shared_ptr<Shape>> shapeListGiven): AdvancedShape(shapeListGiven)
{
	verticalStack = std::move(shapeListGiven);
	height = 0;
	width = 0;
	// Find the total height and max width of the vertical shape.
	for (auto i = 0; i<verticalStack.size(); ++i) {
		height += std::move((verticalStack[i]->height) + 1);
		// Find max width
		if (width < verticalStack[i]->width) {
			width = verticalStack[i]->width;
		}
	}
}
std::string Vertical::translateMe(std::shared_ptr<Shape> currShape)
{
	return "0 " + std::to_string(currShape->height/2) + " translate\n";
}

// Horizontal shape class
Horizontal::Horizontal(std::vector<std::shared_ptr<Shape>> shapeListGiven): AdvancedShape(shapeListGiven)
{
	horizontalStack = std::move(shapeListGiven);
	height = 0;
	width = 0;
	// Find max height and total width of horizontal shape.
	for (auto i = 0; i<horizontalStack.size(); ++i) {
		width += std::move((horizontalStack[i]->width) + 1);
		// Find max height
		if (height < horizontalStack[i]->height) {
			height = horizontalStack[i]->height;
		}
	}
}
std::string Horizontal::translateMe(std::shared_ptr<Shape> currShape)
{
	return std::to_string(currShape->width/2) + " 0 translate\n";
}


