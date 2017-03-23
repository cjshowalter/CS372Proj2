// shape.cpp : Defines the entry point for the console application.
//

#include "shape.hpp"
#include <iostream>
#include <fstream>      // std::ofstream
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

	ofs << rectangleString;
	ofs << "\n";
	ofs << "showpage\n";

	// *** Polygon Test ***
	Polygon p_0(5, 50);
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

	ofs.close();

	return 0;
}
