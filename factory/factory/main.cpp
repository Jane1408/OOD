#include "stdafx.h"
#include "Canvas.h"
#include "Designer.h"
#include "Painter.h"
#include "Client.h"
#include "SVGCanvas.h"


int main()
{
	CCanvas canvas;
	CDesigner designer;
	CPainter painter;
	CClient client(designer, painter);
	std::cout << "Load from file? (y/n)" << std::endl;
	std::string answer;
	std::cin >> answer;
	if (answer == "y")
	{
		std::cout << "Enter file name: ";
		std::string fileName;
		std::cin >> fileName;
		std::ifstream iStrm(fileName);
		client.TurnToDesigner(iStrm);
	}
	else 
	{
		client.TurnToDesigner(std::cin);
	}	
	client.TurnToPainter(canvas);

	std::ofstream oStrm(boost::filesystem::unique_path("Image%%%%.svg").string());
	CSVGCanvas svgCanvas(oStrm);
	client.TurnToPainter(svgCanvas);
	
    return 0;
}

