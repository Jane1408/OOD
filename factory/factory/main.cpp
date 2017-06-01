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
	client.TurnToDesigner(std::cin);
	client.TurnToPainter(canvas);

	std::ofstream oStrm(boost::filesystem::unique_path("Image%%%%.svg").string());
	CSVGCanvas svgCanvas(oStrm);
	client.TurnToPainter(svgCanvas);
	
    return 0;
}

