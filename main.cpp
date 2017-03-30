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


	ofsCirc << polyString;
	ofsCirc << "\n";
	ofsCirc << "showpage\n";

	Rotated rot(p_0, 90);
	std::string rotString = rot.generatePostScript();

	if (rot.height - 161.803 > 1 || rot.width - 153.884 > 1)
	{
		std::cout << "Rotated has incorrect height or width" << std::endl;
	}

	ofsCirc << rotString;
	ofsCirc << "\n";
	ofsCirc << "showpage\n";
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
	//std::cout << s.height << std::endl;
	if ((s.height - 200 > 1) || (s.width - 200 > 1) || (s.height - 200 < -1) || (s.width - 200 < -1))
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

	Circle circ3(40);
	Square squ2(30);
	Triangle tri1(30);
	Scaled sca1(circ3, 0.7, 0.7);
	std::vector<Shape*> shapeVec2 = { &circ3, &squ2, &tri1,&sca1,&squ2 };

	Horizontal hor(shapeVec2);

	std::string horString = hor.generatePostScript();

	double totalHeight = circ3.height + squ2.height + tri1.height + sca1.height + squ2.height;
	double totalWidth = circ3.width + squ2.width + tri1.width + sca1.width + squ2.width;

	if ((hor.height - circ3.height > 1) || (hor.width - totalWidth > 1) || (hor.height - circ3.height < -1) || (hor.width - totalWidth < -1))
	{
		std::cout << "Horizontal has incorrect height or width" << std::endl;
	}

	ofsCirc << horString;
	ofsCirc << "\n";
	ofsCirc << "showpage\n";

	Vertical ver(shapeVec2);

	std::string verString = ver.generatePostScript();
	if ((ver.height - totalHeight > 1) || (ver.width - circ3.width > 1) || (ver.height - totalHeight < -1) || (ver.width - circ3.width < -1))
	{
		std::cout << "Vertical has incorrect height or width" << std::endl;
	}

	ofsCirc << verString;
	ofsCirc << "\n";
	ofsCirc << "showpage\n";


	ofsCirc.close();


	return 0;
}
