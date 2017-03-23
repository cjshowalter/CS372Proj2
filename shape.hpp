#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>
#include <cmath>

class Shape {

public:
	virtual ~Shape()=default;
	//virtual double height()=0;
	//virtual double width()=0;
	virtual std::string generatePostScript()=0;
	double height;
	double width;
	double x;
	double y;
private:
};

class Circle : public Shape {
public:
	Circle(double radius) {
		height = radius*2;
		width = radius*2;
		x = 0;
		y = 0;
		//std::string generatePostScript = "0";
	}
	std::string generatePostScript() override
	{
		std::string circleString = "";
		circleString += std::to_string(x);
		circleString += " ";
		circleString += std::to_string(y);
		circleString += " translate\n";
		circleString += std::to_string(height/2);
		circleString += " ";
		circleString += std::to_string(width/2);
		circleString += " \n";
		circleString += std::to_string(width/2);
		circleString += " 0 360 arc closepath\n";
		circleString += "stroke\n";
		return circleString;
	}


private:

};

class Polygon : public Shape {
public:
	Polygon(int numSides, double sideLength)
	{
        const double pi = 3.141592653589793238;

		if( numSides%2 == 1 )
        {
            height = sideLength*(1+cos(pi/numSides))/(2*sin(pi/numSides));
            width = (sideLength*sin(pi*(numSides-1)/(2*numSides))/(sin(pi/numSides)));
        }
        else if(numSides%4 != 0) // numSides%2==0
        {
            height = sideLength * (cos(pi/numSides))/(sin(pi/numSides));
            width = sideLength/(sin(pi/numSides));
        }
        else // numSides%2 == 0 && numSides%4 == 0
        {
            height = sideLength*(cos(pi/numSides))/(sin(pi/numSides));
            width = height;
        }
	}

private:

};

class Rectangle : public Shape {
public:
	Rectangle(double w, double h) {
		height = h;
		width = w;
		//std::string generatePostScript = "0";
	}
	std::string generatePostScript() override
	{
		std::string rectangleString = "";
		rectangleString += "0";
		rectangleString += " ";
		rectangleString += "0";
		rectangleString += " moveto\n";

		rectangleString += std::to_string(width);
		rectangleString += " ";
		rectangleString += "0";     					// Bottom
		rectangleString += " ";
		rectangleString += "rlineto ";

		rectangleString += "0";
		rectangleString += " ";
		rectangleString += std::to_string(height);      // Right
		rectangleString += " ";
		rectangleString += "rlineto ";

		rectangleString += std::to_string(width*-1);
		rectangleString += " ";
		rectangleString += "0";      					// Bottom
		rectangleString += " ";
		rectangleString += "rlineto ";

		rectangleString += "closepath\n";
		rectangleString += "stroke\n";
		return rectangleString;
	}


private:

};

class Square : public Polygon {
public:
	Square(double sideLength) {
		Polygon(4, sideLength);
	}

private:

};

#endif // SHAPE_HPP
