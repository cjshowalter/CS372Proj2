#ifndef SHAPE_HPP
#define SHAPE_HPP

#include <string>


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
	Polygon(double numSides, double sideLength) {
		
	}

private:

};

#endif // SHAPE_HPP