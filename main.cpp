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


	std::ofstream ofsCirc;
	ofsCirc.open("circTest.ps", std::ofstream::out | std::ofstream::app);
	ofsCirc << "%!\n";
	ofsCirc << circleString;
	ofsCirc << "\n";
	ofsCirc << "showpage\n";
	//ofsCirc.close();


	// *** Rectangle Test ***
	Rectangle r(20, 40);
	std::string rectangleString = r.generatePostScript();
	if (r.height != 40 || r.width != 20)
	{
		std::cout << "Rectangle has incorrect height or width" << std::endl;
	}

	//std::ofstream ofsRect;
	//ofsRect.open("recTest.ps", std::ofstream::out | std::ofstream::app);
	//ofsRect << "%!\n";
	ofsCirc << rectangleString;
	ofsCirc << "\n";
	ofsCirc << "showpage\n";
	//ofsRect.close();

	// *** Polygon Test ***
	Polygon p_0(5, 100);
	std::string polyString = p_0.generatePostScript();
	if (p_0.height - 153.884 > 1 || p_0.width - 161.803 > 1)
	{
		std::cout << "Polygon has incorrect height or width" << std::endl;
	}

	//std::ofstream ofsPoly;
	//ofsPoly.open("polyTest.ps", std::ofstream::out | std::ofstream::app);
	//ofsPoly << "%!\n";
	ofsCirc << polyString;
	ofsCirc << "\n";
	ofsCirc << "showpage\n";
	///ofsPoly.close();

	// *** Square Test ***
	Square squ(100);
	std::string squString = squ.generatePostScript();
	if ((squ.height - 100) > 1 || (squ.width - 100 > 1) || (squ.height - 100) < -1 || (squ.width - 100 < -1))
	{
		std::cout << "Square has incorrect height or width" << std::endl;
	}

	//std::ofstream ofsSqu;
	//ofsSqu.open("squTest.ps", std::ofstream::out | std::ofstream::app);
	//ofsSqu << "%!\n";
	ofsCirc << squString;
	ofsCirc << "\n";
	ofsCirc << "showpage\n";
	//ofsSqu.close();

	// *** Scaled Test ***

	Circle circ(200);
	std::string circString = circ.generatePostScript();
	//std::cout << circString << std::endl;

	Scaled s(circ, 0.5, 0.5);
	std::string scaleString = s.generatePostScript();
	if ((s.height - 100 > 1) || (s.width - 100 > 1) || (s.height - 100 < -1) || (s.width - 100 < -1))
	{
		std::cout << "Scaled has incorrect height or width" << std::endl;
	}

	//std::ofstream ofsScale;
	//ofsScale.open("scaleTest.ps", std::ofstream::out | std::ofstream::app);
	//ofsScale << "%!\n";
	//ofsCirc << circString;
	//ofsCirc << "\n";
	//ofsCirc << "showpage\n";
	ofsCirc << scaleString;
	ofsCirc << "\n";
	ofsCirc << "showpage\n";
	//ofsScale.close();

	// *** Layered Test ***

	Circle circ2(100);

    Rectangle rect(40, 60);

	std::vector<Shape*> shapeVec = { &circ, &circ2, &squ, &rect, &p_0 };

	Layered lay(shapeVec);
	std::string layString = lay.generatePostScript();
	//std::cout << layString << std::endl;

	//	std::ofstream ofsLayer;
	//ofsLayer.open("layerTest.ps", std::ofstream::out | std::ofstream::app);
	//ofsLayer << "%!\n";
	ofsCirc << layString;
	ofsCirc << "\n";
	ofsCirc << "showpage\n";




	ofsCirc.close();


	return 0;
}
