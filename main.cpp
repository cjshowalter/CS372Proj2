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
	std::cout << circleString << std::endl;

	std::ofstream ofs;
	ofs.open("test.ps", std::ofstream::out | std::ofstream::app);
	ofs << "%!\n";


	ofs << circleString;
	ofs << "\n";
	ofs << "showpage\n";


	// *** Rectangle Test ***
	Rectangle r(20, 40);
	std::string rectangleString = r.generatePostScript();
	std::cout << rectangleString << std::endl;

	std::ofstream ofss;
	ofss.open("rectest.ps", std::ofstream::out | std::ofstream::app);
	ofss << "%!\n";
	ofss << rectangleString;
	ofss << "\n";
	ofss << "showpage";
	ofss.close();

	ofs << rectangleString;
	ofs << "\n";
	ofs << "showpage\n";

	// *** Square Test ***
	Polygon p_0(5, 100);
	std::string polyString = p_0.generatePostScript();
	std::cout << polyString << std::endl;

	ofs << polyString;
	ofs << "\n";
	ofs << "showpage\n";

	Square squ(100);
	std::string squString = squ.generatePostScript();
	std::cout << squString << std::endl;

	ofs << squString;
	ofs << "\n";
	ofs << "showpage\n";

	/*
	std::vector<Shape*> vectorShapes = {c, r, p_0, squ};
	ofs << Layered::generatePostScript(vectorShapes);
	*/





	// *** Scaled Test ***

	Circle circ(200);
	Scaled s(circ, 0.5, 0.5);
	std::string scaleString = s.generatePostScript();
	std::cout << scaleString << std::endl;
	ofs << scaleString;
	ofs << "\n";
	ofs << "showpage\n";


	//**** Layered Test

	std::vector<Shape*> shapeVec = { &circ, &squ };
	Layered lay(shapeVec);
	std::string layString = lay.generatePostScript();
	std::cout << layString << std::endl;
	ofs << layString;
	ofs << "\n";
	ofs << "showpage\n";

	ofs.close();


	return 0;
}
