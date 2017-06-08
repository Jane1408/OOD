#include <ostream>
#include <iomanip>
#include "CommonTypes.h"
#include "SVGCanvas.h"
#include <string>


CSVGCanvas::CSVGCanvas(std::ostream & strm)
	: m_oStrm(strm)
	, m_isFill(false)
{
	m_oStrm << "<svg xmlns='http://www.w3.org/2000/svg'>" << std::endl;
}

CSVGCanvas::~CSVGCanvas()
{
	m_oStrm << "</svg>";
}

void CSVGCanvas::SetLineColor(RGBAColor color)
{
	m_lineColor = color;
}

void CSVGCanvas::BeginFill(RGBAColor color)
{
	m_fillColor = color;
	m_isFill = true;
}

void CSVGCanvas::EndFill()
{
	m_fillColor = 1;
	m_isFill = false;
}

void CSVGCanvas::MoveTo(double x, double y)
{
	m_currPos.first = x;
	m_currPos.second = y;
}

void CSVGCanvas::LineTo(double x, double y)
{
	if (m_isFill)
	{
		std::string comma = (m_points.length == 0) ? " " + std::to_string(m_currPos.first) + " " + std::to_string(m_currPos.second) + "," : " " + std::to_string(m_currPos.first) + " " + std::to_string(m_currPos.second) + ",";
		m_points = m_points + comma + " " + std::to_string(m_currPos.first) + " " + std::to_string(m_currPos.second);
	}
	else {
		m_oStrm << "<line x1= '" << m_currPos.first << "' y1= '" << m_currPos.second << "' x2= '" << x << "' y2= '" << y
			<< "' stroke-width= '1' fill = '" << "#" << std::hex << std::setw(6) << std::setfill('0') << m_fillColor << std::dec
			<< "' stroke= '" << "#" << std::hex << std::setw(6) << std::setfill('0') << m_lineColor << std::dec << "' />" << std::endl;
		m_currPos.first = x;
		m_currPos.second = y;
	}
	
}

void CSVGCanvas::DrawEllipse(double left, double top, double width, double height)
{
	auto radiusX = width / 2.0;
	auto radiusY = height / 2.0;

	auto centreX = left + radiusX;
	auto centreY = top + radiusY;
	m_oStrm << "<ellipse cx= '" << centreX << "' cy= '" << centreY << "' rx= '" << radiusX << "' ry= '" << radiusY
		<< "' stroke-width= '1' fill = '" << "#" << std::hex << std::setw(6) << std::setfill('0') << m_fillColor << std::dec
		<< "' stroke= '" << "#" << std::hex << std::setw(6) << std::setfill('0') << m_lineColor << std::dec <<"' />" << std::endl;
}

void CSVGCanvas::DrawFillShape()
{
	m_oStrm << " <polygon points= '" << m_points <<"' style=' fill: yellow; fill-opacity: 0.5; stroke: black; stroke-width: 2;' /> " << std::endl;
}
