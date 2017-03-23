// shape.cpp : Defines the entry point for the console application.
//

#include "shape.hpp"
#include <iostream>

int main() {
	
	Circle c(20);
	std::string circleString = c.generatePostScript();
	std::cout << circleString << std::endl;
	return 0;
}
