#include <cstdint>
#include <memory>
#include <limits>
#include <functional>
#include <boost/filesystem.hpp>
#include "Slide.h"
#include "SimpleShapes.h"
#include "Group.h"
#include "Canvas.h"
#include "SVGCanvas.h"


int main()
{
	CSlide slide;
	CStyle redStyle;
	redStyle.Enable(true);
	redStyle.SetColor(0xFF0000);

	CStyle greenStyle;
	greenStyle.Enable(true);
	greenStyle.SetColor(0x00FF00);

	CStyle blueStyle;
	blueStyle.Enable(true);
	blueStyle.SetColor(0x0000FF);

	auto rectangleShape = std::make_shared<CRectangle>(RectD{ 30, 200, 200, 150 });
	rectangleShape->SetFillStyle(redStyle);
	rectangleShape->SetLineStyle(greenStyle);

	auto ellipseShape = std::make_shared<CEllipse>(RectD{ 105, 125, 50, 50 });
	ellipseShape->SetFillStyle(blueStyle);
	ellipseShape->SetLineStyle(greenStyle);

	auto triangleShape = std::make_shared<CTriangle>(RectD{ 30, 50, 200, 150 });
	triangleShape->SetLineStyle(blueStyle);

	auto group = std::make_shared<CGroup>();
	group->InsertShape(triangleShape);
	group->InsertShape(ellipseShape);

	group->SetFillStyle(greenStyle);
	group->SetLineStyle(redStyle);

	slide.InsertShape(group);
	slide.InsertShape(rectangleShape);
	slide.SetBackgroundColor(0xFFFFFF);

	CCanvas canvas(std::cout);
	slide.Draw(canvas);

	std::ofstream oStrm(boost::filesystem::unique_path("Image%%%%.svg").string());
	CSVGCanvas svgCanvas(oStrm);
	slide.Draw(svgCanvas);
	return 0;
}
