// shape.cpp : Defines the entry point for the console application.
//

#include "shape.hpp"
#include <iostream>
#include <fstream>      // std::ofstream
int main() {
	
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



	return 0;
}
