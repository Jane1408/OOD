#include <iomanip>
#include <sstream>
#include "Canvas.h"

CCanvas::CCanvas(std::ostream & strm)
	: m_strm(strm)
{
}

CCanvas::~CCanvas()
{
}

void CCanvas::SetLineColor(RGBAColor color)
{
	m_strm << "Line color " << TextedColor(color) << std::endl;
}

void CCanvas::BeginFill(RGBAColor color)
{
	m_strm << "Start Filling shape by " << TextedColor(color) << " color " << std::endl;
}

void CCanvas::EndFill()
{
	m_strm << "Stop Filling" << std::endl;
}

void CCanvas::MoveTo(double x, double y)
{
	m_strm << "Move to { " << x << ", " << y << " }" << std::endl;
}

void CCanvas::LineTo(double x, double y)
{
	m_strm << "Line to { " << x << ", " << y << " }" << std::endl;
}

void CCanvas::DrawEllipse(double left, double top, double width, double height)
{
	auto radiusX = width / 2.0;
	auto radiusY = height / 2.0;

	auto centreX = left + radiusX;
	auto centreY = top + radiusY;

	m_strm << "Drawing ellipse. Centre {" << centreX << ", " << centreY
		<< "} and radiuses = {" << radiusX << ", " << radiusY << "} " << std::endl;

}

std::string CCanvas::TextedColor(RGBAColor color)
{
	std::stringstream strStrm;
	strStrm << "#" << std::hex << std::setw(6) << std::setfill('0') << color << std::dec;
	return strStrm.str();
}