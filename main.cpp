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
	ofs << "showpage";
	ofs.close();

	// *** Rectangle Test ***
	Rectangle r(20,40);
	std::string rectangleString = r.generatePostScript();
	std::cout << rectangleString << std::endl;

	std::ofstream ofss;
	ofss.open("rectest.ps", std::ofstream::out | std::ofstream::app);
	ofss << "%!\n";
	ofss << rectangleString;
	ofss<<"\n";
	ofss << "showpage";
	ofss.close();


	return 0;
}
