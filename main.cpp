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

	std::ofstream ofsCirc;
	ofsCirc.open("circTest.ps", std::ofstream::out | std::ofstream::app);
	ofsCirc << "%!\n";
	ofsCirc << circleString;
	ofsCirc << "\n";
	ofsCirc << "showpage\n";
	ofsCirc.close();


	// *** Rectangle Test ***
	Rectangle r(20, 40);
	std::string rectangleString = r.generatePostScript();
	std::cout << rectangleString << std::endl;

	std::ofstream ofsRect;
	ofsRect.open("recTest.ps", std::ofstream::out | std::ofstream::app);
	ofsRect << "%!\n";
	ofsRect << rectangleString;
	ofsRect << "\n";
	ofsRect << "showpage";
	ofsRect.close();

	// *** Polygon Test ***
	Polygon p_0(5, 100);
	std::string polyString = p_0.generatePostScript();
	std::cout << polyString << std::endl;

	std::ofstream ofsPoly;
	ofsPoly.open("polyTest.ps", std::ofstream::out | std::ofstream::app);
	ofsPoly << "%!\n";
	ofsPoly << polyString;
	ofsPoly << "\n";
	ofsPoly << "showpage\n";
	ofsPoly.close();

	// *** Square Test ***
	Square squ(100);
	std::string squString = squ.generatePostScript();
	std::cout << squString << std::endl;

	std::ofstream ofsSqu;
	ofsSqu.open("squTest.ps", std::ofstream::out | std::ofstream::app);
	ofsSqu << "%!\n";
	ofsSqu << squString;
	ofsSqu << "\n";
	ofsSqu << "showpage\n";
	ofsSqu.close();

	/*
	std::vector<Shape*> vectorShapes = {c, r, p_0, squ};
	ofs << Layered::generatePostScript(vectorShapes);
	*/

	// *** Scaled Test ***

	Circle circ(200);
	std::string circString = circ.generatePostScript();
	std::cout << circString << std::endl;

	Scaled s(circ, 0.5, 0.5);
	std::string scaleString = s.generatePostScript();
	std::cout << scaleString << std::endl;

	std::ofstream ofsScale;
	ofsScale.open("scaleTest.ps", std::ofstream::out | std::ofstream::app);
	ofsScale << "%!\n";
	ofsCirc << circString;
	ofsCirc << "\n";
	ofsCirc << "showpage\n";
	ofsScale << scaleString;
	ofsScale << "\n";
	ofsScale << "showpage\n";
	ofsScale.close();

	// *** Layered Test ***

	std::vector<Shape*> shapeVec = { &circ, &squ, &p_0 };
	Layered lay(shapeVec);
	std::string layString = lay.generatePostScript();
	std::cout << layString << std::endl;

	std::ofstream ofsLayer;
	ofsLayer.open("layerTest.ps", std::ofstream::out | std::ofstream::app);
	ofsLayer << "%!\n";
	ofsLayer << layString;
	ofsLayer << "\n";
	ofsLayer << "showpage\n";
	ofsLayer.close();


	return 0;
}
