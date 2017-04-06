#include <cstdint>
#include "graphics_lib_pro.h"
#include "shape_drawing_lib_pro.h"

namespace shape_drawing_lib_pro
{

	CTriangle::CTriangle(const Point & p1, const Point & p2, const Point & p3, const uint32_t & color)
		: m_p1(p1)
		, m_p2(p2)
		, m_p3(p3)
		, m_color(color)
	{
	}

	void CTriangle::Draw(graphics_lib_pro::ICanvas & canvas) const
	{
		canvas.SetColor(m_color);
		canvas.MoveTo(m_p1.x, m_p1.y);
		canvas.LineTo(m_p2.x, m_p2.y);
		canvas.LineTo(m_p3.x, m_p3.y);
		canvas.LineTo(m_p1.x, m_p1.y);
	}


	CRectangle::CRectangle(const Point & leftTop, int width, int height, const uint32_t & color)
		: m_leftTop(leftTop)
		, m_width(width)
		, m_height(height)
		, m_color(color)
	{
	}

	void CRectangle::Draw(graphics_lib_pro::ICanvas & canvas) const
	{
		canvas.SetColor(m_color);
		canvas.MoveTo(m_leftTop.x, m_leftTop.y);
		canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y);
		canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y + m_height);
		canvas.LineTo(m_leftTop.x, m_leftTop.y + m_height);
		canvas.LineTo(m_leftTop.x, m_leftTop.y);
	}

	CCanvasPainter::CCanvasPainter(graphics_lib_pro::ICanvas & canvas)
		: m_canvas(canvas)
	{
	}
	void CCanvasPainter::Draw(const ICanvasDrawable & drawable)
	{
		drawable.Draw(m_canvas);
	}

}