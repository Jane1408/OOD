#include "stdafx.h"
#include "Canvas.h"


CCanvas::CCanvas()
{
}


CCanvas::~CCanvas()
{
}

void CCanvas::SetColor(Color color)
{
	try 
	{
		std::cout << "Current color " << COLOR_STR_MAP.at(color) << std::endl;
		m_currentColor = color;
	}
	catch (...)
	{
		std::cout << "Can not change color" << std::endl;
	}
}

void CCanvas::DrawLine(Vector2 from, Vector2 to)
{
	std::cout << "---BEGIN_DRAW_LINE---" << std::endl;
	std::cout << "Vertex1 ( " << from.x << " , " << from.y << " )" << std::endl;
	std::cout << "Vertex2 ( " << to.x << " , " << to.y << " )" << std::endl;
	std::cout << "---FINISH_DRAW_LINE---" << std::endl;
}

void CCanvas::DrawEllipse(Vector2 center, double horizontalRadius, double verticalRadius)
{
	std::cout << "---BEGIN_DRAW_ELLIPSE---" << std::endl;
	std::cout << "Center ( " << center.x << " , " << center.y << " )" << std::endl;
	std::cout << "horizontal Radius " << horizontalRadius << std::endl;
	std::cout << "Vertical Radius " << verticalRadius << std::endl;
	std::cout << "---FINISH_DRAW_ELLIPSE---" << std::endl;
}
