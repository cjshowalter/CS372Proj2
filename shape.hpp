//Cameron Showalter
//Refactoring, Assignment 4
//CS 372
//4-26-17



#ifndef SHAPE_HPP_INCLUDED
#define SHAPE_HPP_INCLUDED

#include <string>	//std::string std::to_string
#include <cmath>	//std::sin std::cos 
#include <vector> //std::vector std::move
#include <memory> //std::shared_ptr std::make_shared

//Class Shape
//Very base class that everything dirives from
//		Shapes will return a std::string that prints postscript for generating
//		the shape around the origin.
class Shape 
{
public:
	virtual ~Shape() = default;
	virtual std::string generatePostScript() = 0;

	double height;
	double width;
	double x;
	double y;
};

//Class Circle
//returns a std::string that prints postscript for generating a circle of double 
//		radius. Draws around the origin.
class Circle : public Shape 
{
public:
	Circle(double radius);
	std::string generatePostScript() override;
};

//Class Polygon
//returns a std::string that prints postscript for generating a circle of 
//		int sides, and double sideLength. Draws around the origin.
class Polygon : public Shape 
{
public:
	Polygon() = default;
	Polygon(int numSides, double sideLength);
	std::string generatePostScript() override;

private:
	double sideLength_g;
	double numSides_g;
};

//Class Rectangle
//returns a std::string that prints postscript for generating a rectangle of 
//		double width, and double height. Draws around the origin.
class Rectangle : public Shape 
{
public:
	Rectangle(double w, double h);
	std::string generatePostScript() override;

private:
	double halfHeight_;
	double halfWidth_;
};

//Class Spacer
//returns a std::string that prints postscript for generating a spacer of 
//		int sides, and double sideLength. Draws around the origin.
//		"Draws" nothing, just creates a space to fill.
class Spacer : public Shape 
{
public:
	Spacer(double w, double h);
	std::string generatePostScript() override;
};

//Class Square
//		Create a 4 sided polygon with the given side length
class Square : public Polygon 
{
public:
	Square(double sideLength);
};

//Class Triangle
//		Create a 3 sided polygon with the given side length
class Triangle : public Polygon 
{
public:
	Triangle(double sideLength);
};

//Class Custom
//		creates a little robot head using different shapes and translates
class Custom : public Shape
{
public:
	Custom(double sideLength);
	//I just realized while refactoring that this generatePostScript is missing
	//override, but the program still compiles and runs.....
	std::string generatePostScript();
};

//Class Scaled
//		When given a Shape &Shape, double width, and double height, Will
//		scale shape to new width and height sizes.
class Scaled : public Shape
{
public:
	Scaled(Shape &shape, double fx, double fy);
	std::string generatePostScript() override;

private:
	std::string scaledString;
};

//Class Rotated
//		Will rotate a Shape when given an int rotation to rotate.
//		only works when the int == 0, 90, 180, or 270
class Rotated : public Shape 
{
public:
	Rotated(Shape &shape, int rotationAngle);
	std::string generatePostScript() override;

private:
	Shape &refShape;
	int rotAngle;
};

// AdvancedShape shape class
// 	All classes that inherits from this take std::vectors and draw shapes 
// 		that translate different amounts in different directions
//		Shapes may/maaynot overlap.
class AdvancedShape : public Shape
{
public:
	//can't remember if this is actually needed because AdvancedShape inherits from Shape but:
	~AdvancedShape() = default;
	AdvancedShape() = default;

	AdvancedShape(std::vector<std::shared_ptr<Shape>> shapeList);
	std::string generatePostScript() override;

protected:
	virtual std::string translateMe(std::shared_ptr<Shape> currShape) = 0; 
	std::vector<std::shared_ptr<Shape>> shapeList_;	

private:

};

// Layered shape class
// Creates a stack of shapes. Shapes are centered on origin.
//		All Shapes overlap.
class Layered : public AdvancedShape
{
public:
	Layered(std::vector<std::shared_ptr<Shape>> shapeListGiven);
	std::string translateMe(std::shared_ptr<Shape> currShape) override;

private:
	std::vector<std::shared_ptr<Shape>> layeredStack;
};

// Vertical shape class
// Creates a stack of shapes. Shapes are centered based on the widest shape.
//		Shapes do not overlap.
class Vertical : public AdvancedShape 
{
public:
	// Ctor from std::vector of shapes.
	// Ctor accepts a std::vector of any size containing pointers to created shapes.
	Vertical(std::vector<std::shared_ptr<Shape>> shapeListGiven);
	std::string translateMe(std::shared_ptr<Shape> currShape) override;

private:
	std::vector<std::shared_ptr<Shape>> verticalStack;
};

// Horizontal shape class
// Creates a row of shapes. Shapes are centered based on the tallest shape.
//		Shapes do not overlap.
class Horizontal : public AdvancedShape 
{
public:
	// Ctor from std::vector of shapes.
	// Ctor accepts a std::vector of any size containing pointers to created shapes.
	Horizontal(std::vector<std::shared_ptr<Shape>> shapeListGiven);
	std::string translateMe(std::shared_ptr<Shape> currShape) override;

private:
	std::vector<std::shared_ptr<Shape>> horizontalStack;
};

#endif // SHAPE_HPP_INCLUDED
