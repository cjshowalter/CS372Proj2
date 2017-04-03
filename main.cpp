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
	std::vector<unique_ptr<Shape>> shapeVec2;
	shapeVec2.push_back(make_unique<Circle>(circ3));
	shapeVec2.push_back(make_unique<Square>(squ2));
	shapeVec2.push_back(make_unique<Triangle>(tri1));
	shapeVec2.push_back(make_unique<Scaled>(sca1));
	shapeVec2.push_back(make_unique<Square>(squ2));
	int shapeVec2Size = shapeVec2.size();

	Horizontal hor(std::move(shapeVec2));

	std::string horString = hor.generatePostScript();

	double totalHeight = circ3.height + squ2.height + tri1.height + sca1.height + squ2.height;
	double totalWidth = circ3.width + squ2.width + tri1.width + sca1.width + squ2.width;

	if ((hor.height - totalHeight > 1) || (hor.width - (totalWidth+shapeVec2Size) > 1) || (hor.height - circ3.height < -1) || (hor.width - totalWidth < -1))
	{
		std::cout << "Horizontal has incorrect height or width" << std::endl;
		std::cout << "Horizontal Width = " << hor.width << "\n";
		std::cout << "Total Width = " << totalWidth+shapeVec2Size << "\n";
		std::cout << "Horizontal Height " << hor.height << "\n";
		std::cout << "Total Height = " << totalHeight << "\n";
	}
	else {
		std::cout << "Horizontal tests passed" << std::endl;
	}

	ofs << "144 144 translate\n";
	ofs << horString;
	ofs << "\n";
	ofs << "showpage\n";

	// *** Vertical Test ***

	std::vector<unique_ptr<Shape>> shapeVec3;
	shapeVec3.push_back(make_unique<Circle>(circ3));
	shapeVec3.push_back(make_unique<Square>(squ2));
	shapeVec3.push_back(make_unique<Triangle>(tri1));
	shapeVec3.push_back(make_unique<Scaled>(sca1));
	shapeVec3.push_back(make_unique<Square>(squ2));
	int shapeVec3Size = shapeVec3.size();
	Vertical ver(std::move(shapeVec3));

	std::string verString = ver.generatePostScript();
	if ((ver.height - (totalHeight+shapeVec3Size) > 1) || (ver.width - totalWidth > 1) || (ver.height - totalHeight < -1) || (ver.width - circ3.width < -1))
	{
		std::cout << "Vertical has incorrect height or width" << std::endl;
		std::cout << "Vertical Width = " << ver.width << "\n";
		std::cout << "Total Width = " << totalWidth << "\n";
		std::cout << "Vertical Height " << ver.height << "\n";
		std::cout << "Total Height = " << totalHeight+shapeVec3Size << "\n";
	}
	else {
		std::cout << "Vertical tests passed" << std::endl;
	}

	ofs << "144 144 translate\n";
	ofs << verString;
	ofs << "\n";
	ofs << "showpage\n";

	ofs.close();

	return 0;
}
