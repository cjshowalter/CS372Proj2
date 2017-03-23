// shape.cpp : Defines the entry point for the console application.
//

#include "shape.hpp"
#include <iostream>
#include <fstream>      // std::ofstream
#include <vector>


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

    /*
	std::vector<Shape*> vectorShapes = {c, r, p_0, squ};
	ofs << Layered::generatePostScript(vectorShapes);
    */


	ofs.close();


	// *** Scaled Test ***

	Circle circ(200);
	Scaled s(circ, 0.5, 0.5);
	std::string scaleString = s.generatePostScript();
	std::cout << scaleString << std::endl;
	ofs << scaleString;
	ofs << "\n";

//	Polygon p_1(5, 50);
//	Scaled s1(p_1, 2, 2);
//  std::string scaleString1 = s1.generatePostScript();
//	std::cout << scaleString1 << std::endl;
//	ofs << scaleString1;
//	ofs << "\n";

	ofs << "showpage\n";

	ofs.close();


	return 0;
}
