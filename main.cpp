// shape.cpp : Defines the entry point for the console application.
//


#include <iostream>
#include <fstream>      // std::ofstream
#include <vector>
#include "shape.hpp"

int main() {

	// *** Circle Test ***
	Circle c(200);
	std::string circleString = c.generatePostScript();
	if (c.height != 400 || c.width != 400)
	{
		std::cout << "Circle has incorrect height or width" << std::endl;
	}
	else {
		std::cout << "Circle tests passed" << std::endl;
	}
	std::ofstream ofs;
	ofs.open("tests.ps", std::ofstream::out | std::ofstream::app);
	ofs << "%!\n";
	ofs << "216 216 translate\n";
	ofs << circleString;
	ofs << "\n";
	ofs << "showpage\n";


	// *** Rectangle Test ***
	Rectangle r(20, 40);
	std::string rectangleString = r.generatePostScript();
	if (r.height != 40 || r.width != 20)
	{
		std::cout << "Rectangle has incorrect height or width" << std::endl;
	}
	else {
		std::cout << "Rectangle tests passed" << std::endl;
	}

	ofs << "144 144 translate\n";
	ofs << rectangleString;
	ofs << "\n";
	ofs << "showpage\n";

	// *** Polygon Test ***
	Polygon p_0(5, 100);
	std::string polyString = p_0.generatePostScript();
	if (p_0.height - 153.884 > 1 || p_0.width - 161.803 > 1)
	{
		std::cout << "Polygon has incorrect height or width" << std::endl;
	}
	else {
		std::cout << "Polygon tests passed" << std::endl;
	}

	ofs << "144 144 translate\n";
	ofs << polyString;
	ofs << "\n";
	ofs << "showpage\n";

	Rotated rot(p_0, 90);
	std::string rotString = rot.generatePostScript();

	if (rot.height - 161.803 > 1 || rot.width - 153.884 > 1)
	{
		std::cout << "Rotated has incorrect height or width" << std::endl;
	}
	else {
		std::cout << "Rotated tests passed" << std::endl;
	}

	ofs << "144 144 translate\n";
	ofs << rotString;
	ofs << "\n";
	ofs << "showpage\n";

	// *** Square Test ***
	Square squ(100);
	std::string squString = squ.generatePostScript();
	if ((squ.height - 100) > 1 || (squ.width - 100 > 1) || (squ.height - 100) < -1 || (squ.width - 100 < -1))
	{
		std::cout << "Square has incorrect height or width" << std::endl;
	}
	else {
		std::cout << "Square tests passed" << std::endl;
	}

	ofs << "144 144 translate\n";
	ofs << squString;
	ofs << "\n";
	ofs << "showpage\n";

	// *** Scaled Test ***

	Circle circ(200);
	std::string circString = circ.generatePostScript();

	Scaled s(circ, 0.5, 0.5);
	std::string scaleString = s.generatePostScript();

	if ((s.height - 200 > 1) || (s.width - 200 > 1) || (s.height - 200 < -1) || (s.width - 200 < -1))
	{
		std::cout << "Scaled has incorrect height or width" << std::endl;
	}
	else {
		std::cout << "Scaled tests passed" << std::endl;
	}

	ofs << "144 144 translate\n";
	ofs << scaleString;
	ofs << "\n";
	ofs << "showpage\n";

	// *** Layered Test ***

	Circle circ2(100);

	Rectangle rect(40, 60);

	std::vector<unique_ptr<Shape>> shapeVec;
	shapeVec.push_back(make_unique<Circle>(circ));
	shapeVec.push_back(make_unique<Circle>(circ2));
	shapeVec.push_back(make_unique<Square>(squ));
	shapeVec.push_back(make_unique<Polygon>(p_0));

	Layered lay(std::move(shapeVec));
	std::string layString = lay.generatePostScript();
	//std::cout << layString << std::endl;

	ofs << "216 216 translate\n";
	ofs << layString;
	ofs << "\n";
	ofs << "showpage\n";

	// *** Horizontal Test ***

	Circle circ3(40);
	Square squ2(30);
	Triangle tri1(30);
	Scaled sca1(circ3, 0.7, 0.7);
	
	// **** Horizontal test for 0 shapes ****
	double horTotalHeight0 = 0;
	double horTotalWidth0 = 0;
	std::vector<unique_ptr<Shape>> horTest0(0);
	int horTest0Size = horTest0.size();
	Horizontal horTest0Shape(std::move(horTest0));

	if ((horTest0Shape.height - (horTotalHeight0 + horTest0Size) > 1) || 
		(horTest0Shape.width - horTotalWidth0 > 1) || 
		(horTest0Shape.height - horTotalHeight0 < -1))
	{
		std::cout << "\nNo (0) shape horizontal has incorrect height or width" << std::endl;
		std::cout << "Horizontal Width = " << horTest0Shape.width << "\n";
		std::cout << "Total Width = " << horTotalWidth0 << "\n";
		std::cout << "Horizontal Height = " << horTest0Shape.height << "\n";
		std::cout << "Total Height = " << horTotalHeight0 + horTest0Size << "\n\n";
	}
	else {
		std::cout << "No (0) shape horizontal test passed" << std::endl;
	}

	// **** Horizontal test for 1 shape ****
	double horTotalHeight1 = circ3.height;
	double horTotalWidth1 = circ3.width;
	std::vector<unique_ptr<Shape>> horTest1;
	horTest1.push_back(make_unique<Circle>(circ3));
	int horTest1Size = horTest1.size();
	Horizontal horTest1Shape(std::move(horTest1));

	if ((horTest1Shape.height - (horTotalHeight1) > 1) || 
		(horTest1Shape.width - (horTotalWidth1 + horTest1Size) > 1) || 
		(horTest1Shape.height - horTotalHeight1 < -1) || 
		(horTest1Shape.width - circ3.width < -1))
	{
		std::cout << "\nOne shape horizontal has incorrect height or width" << std::endl;
		std::cout << "Horizontal Width = " << horTest1Shape.width << "\n";
		std::cout << "Total Width = " << horTotalWidth1 + horTest1Size << "\n";
		std::cout << "Horizontal Height = " << horTest1Shape.height << "\n";
		std::cout << "Total Height = " << horTotalHeight1 << "\n\n";
	}
	else {
		std::cout << "One shape horizontal test passed" << std::endl;
	}

	// **** Horizontal test for more than 1 shape ****
	double horTotalHeight2 = circ3.height + squ2.height + tri1.height + sca1.height + squ2.height;
	double horTotalWidth2 = circ3.width + squ2.width + tri1.width + sca1.width + squ2.width;
	std::vector<unique_ptr<Shape>> horTest2;
	horTest2.push_back(make_unique<Circle>(circ3));
	horTest2.push_back(make_unique<Square>(squ2));
	horTest2.push_back(make_unique<Triangle>(tri1));
	horTest2.push_back(make_unique<Scaled>(sca1));
	horTest2.push_back(make_unique<Square>(squ2));
	int horTest2Size = horTest2.size();
	Horizontal horTest2Shape(std::move(horTest2));

	std::string horString = horTest2Shape.generatePostScript();
	if ((horTest2Shape.height - horTotalHeight2 > 1) || 
		(horTest2Shape.width - (horTotalWidth2 + horTest2Size) > 1) || 
		(horTest2Shape.height - horTotalHeight2 < -1) || 
		(horTest2Shape.width - circ3.width < -1))
	{
		std::cout << "\nFive shape horizontal has incorrect height or width" << std::endl;
		std::cout << "Horizontal Width = " << horTest2Shape.width << "\n";
		std::cout << "Total Width = " << horTotalWidth2 + horTest2Size << "\n";
		std::cout << "Horizontal Height = " << horTest2Shape.height << "\n";
		std::cout << "Total Height = " << horTotalHeight2 << "\n\n";
	}
	else {
		std::cout << "Five shape horizontal test passed" << std::endl;
	}


	ofs << "144 144 translate\n";
	ofs << horString;
	ofs << "\n";
	ofs << "showpage\n";
	

	// ****************** Vertical Tests ******************

	// **** Vertical test for 0 shapes ****
	double vertTotalHeight0 = 0;
	double vertTotalWidth0 = 0;
	std::vector<unique_ptr<Shape>> vertTest0(0);
	int vertTest0Size = vertTest0.size();
	Vertical vertTest0Shape(std::move(vertTest0));

	if ((vertTest0Shape.height - (vertTotalHeight0 + vertTest0Size) > 1) || 
		(vertTest0Shape.width - vertTotalWidth0 > 1) || 
		(vertTest0Shape.height - vertTotalHeight0 < -1))
	{
		std::cout << "\nNo (0) shape vertical has incorrect height or width" << std::endl;
		std::cout << "Vertical Width = " << vertTest0Shape.width << "\n";
		std::cout << "Total Width = " << vertTotalWidth0 << "\n";
		std::cout << "Vertical Height = " << vertTest0Shape.height << "\n";
		std::cout << "Total Height = " << vertTotalHeight0 + vertTest0Size << "\n\n";
	}
	else {
		std::cout << "No (0) shape vertical test passed" << std::endl;
	}

	// **** Vertical test for 1 shape ****
	double vertTotalHeight1 = circ3.height;
	double vertTotalWidth1 = circ3.width;
	std::vector<unique_ptr<Shape>> vertTest1;
	vertTest1.push_back(make_unique<Circle>(circ3));
	int vertTest1Size = vertTest1.size();
	Vertical vertTest1Shape(std::move(vertTest1));

	if ((vertTest1Shape.height - (vertTotalHeight1 + vertTest1Size) > 1) || 
		(vertTest1Shape.width - vertTotalWidth1 > 1) || 
		(vertTest1Shape.height - vertTotalHeight1 < -1) || 
		(vertTest1Shape.width - circ3.width < -1))
	{
		std::cout << "\nOne shape vertical has incorrect height or width" << std::endl;
		std::cout << "Vertical Width = " << vertTest1Shape.width << "\n";
		std::cout << "Total Width = " << vertTotalWidth1 << "\n";
		std::cout << "Vertical Height = " << vertTest1Shape.height << "\n";
		std::cout << "Total Height = " << vertTotalHeight1 + vertTest1Size << "\n\n";
	}
	else {
		std::cout << "One shape vertical test passed" << std::endl;
	}

	// **** Vertical test for more than 1 shape ****
	double vertTotalHeight2 = circ3.height + squ2.height + tri1.height + sca1.height + squ2.height;
	double vertTotalWidth2 = circ3.width + squ2.width + tri1.width + sca1.width + squ2.width;
	std::vector<unique_ptr<Shape>> vertTest2;
	vertTest2.push_back(make_unique<Circle>(circ3));
	vertTest2.push_back(make_unique<Square>(squ2));
	vertTest2.push_back(make_unique<Triangle>(tri1));
	vertTest2.push_back(make_unique<Scaled>(sca1));
	vertTest2.push_back(make_unique<Square>(squ2));
	int vertTest2Size = vertTest2.size();
	Vertical vertTest2Shape(std::move(vertTest2));

	std::string verString = vertTest2Shape.generatePostScript();
	if ((vertTest2Shape.height - (vertTotalHeight2 + vertTest2Size) > 1) || 
		(vertTest2Shape.width - vertTotalWidth2 > 1) || 
		(vertTest2Shape.height - vertTotalHeight2 < -1) || 
		(vertTest2Shape.width - circ3.width < -1))
	{
		std::cout << "\nFive shape vertical has incorrect height or width" << std::endl;
		std::cout << "Vertical Width = " << vertTest2Shape.width << "\n";
		std::cout << "Total Width = " << vertTotalWidth2 << "\n";
		std::cout << "Vertical Height = " << vertTest2Shape.height << "\n";
		std::cout << "Total Height = " << vertTotalHeight2 + vertTest2Size << "\n\n";
	}
	else {
		std::cout << "Five shape vertical test passed" << std::endl;
	}


	ofs << "144 144 translate\n";
	ofs << verString;
	ofs << "\n";
	ofs << "showpage\n";

	// *** Custom Test ***//
	int cusNum = 100;
	Custom cus_0(cusNum);

	if ((squ.height - cusNum) > 1 || (squ.width - cusNum > 1) || 
		(squ.height - cusNum) < -1 || (squ.width - cusNum < -1))
	{
		std::cout << "Custom has incorrect height or width" << std::endl;
	}
	else {
		std::cout << "Custom tests passed" << std::endl;
	}

	std::string customString = cus_0.generatePostScript();
	ofs << "144 144 translate\n";
	ofs << customString;
	ofs << "\n";
	ofs << "showpage\n";
	ofs.close();

	return 0;
}
