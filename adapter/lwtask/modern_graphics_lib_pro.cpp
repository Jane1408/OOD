#include <iostream>
#include <boost/format.hpp>
#include "modern_graphics_lib_pro.h"

using namespace std;

namespace modern_graphics_lib_pro
{
	CPoint::CPoint(int x, int y)
		: x(x)
		, y(y)
	{}

	CRGBAColor::CRGBAColor(float r, float g, float b, float a)
		: r(r)
		, g(g)
		, b(b)
		, a(a)
	{}

	CModernGraphicsRenderer::CModernGraphicsRenderer(std::ostream & strm) : m_out(strm)
	{
	}

	CModernGraphicsRenderer::~CModernGraphicsRenderer()
	{
		if (m_drawing)
		{
			EndDraw();
		}
	}

	// Ётот метод должен быть вызван в начале рисовани€
	void CModernGraphicsRenderer::BeginDraw()
	{
		if (m_drawing)
		{
			throw logic_error("Drawing has already begun");
		}
		m_out << "<draw>" << endl;
		m_drawing = true;
	}

	void CModernGraphicsRenderer::DrawLine(const CPoint & start, const CPoint & end, const CRGBAColor& color)
	{
		if (m_drawing)
		{
			cout << boost::format(R"(<line fromX="%1%" fromY="%2%" toX="%3%" toY="%4%">
			<color r="%5%" g="%6%" b="%7%" a="%8%" />
			</line>)") % start.x % start.y % end.x %end.y % color.r % color.g % color.b % color.a;
		}
	}

	void CModernGraphicsRenderer::EndDraw()
	{
		if (!m_drawing)
		{
			throw logic_error("Drawing has not been started");
		}
		m_out << "</draw>" << endl;
		m_drawing = false;
	}
}
