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
private:
};

class Circle : public Shape {
public:
	Circle(double radius) {
		height = radius*2;
		width = radius*2;
		//std::string generatePostScript = "0";
	}
	std::string generatePostScript() override
	{
		return std::to_string(height);
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