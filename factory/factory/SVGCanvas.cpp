#include "stdafx.h"
#include "SVGCanvas.h"


CSVGCanvas::CSVGCanvas(std::ostream & strm)
	: m_oStrm(strm)
{
	m_oStrm << "<svg xmlns='http://www.w3.org/2000/svg'>" << std::endl;
}

CSVGCanvas::~CSVGCanvas()
{
	m_oStrm << "</svg>";
}

void CSVGCanvas::SetColor(Color color)
{
	m_currentColor = color;
}

void CSVGCanvas::DrawLine(Vector2 from, Vector2 to)
{
	m_oStrm << "<line x1= '" << from.x << "' y1= '" << from.y << "' x2= '" << to.x << "' y2= '" << to.y
		<< "' stroke-width= '1' fill = 'none' stroke= '" << COLOR_TO_STR_LIST.find(m_currentColor)->second << "' />" << std::endl;
}

void CSVGCanvas::DrawEllipse(Vector2 center, double horizontalRadius, double verticalRadius)
{
	m_oStrm << "<ellipse cx= '" << center.x << "' cy= '" << center.y << "' rx= '" << horizontalRadius << "' ry= '" << verticalRadius
		<< "' stroke-width= '1' fill = 'none' stroke= '" << COLOR_TO_STR_LIST.find(m_currentColor)->second << "' />" << std::endl;
}