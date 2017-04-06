#pragma once

namespace shape_drawing_lib_pro
{
	struct Point
	{
		int x;
		int y;
	};

	// »нтерфейс объектов, которые могут быть нарисованы на холсте из graphics_lib
	class ICanvasDrawable
	{
	public:
		virtual void Draw(graphics_lib_pro::ICanvas & canvas)const = 0;
		virtual ~ICanvasDrawable() = default;
	};

	class CTriangle : public ICanvasDrawable
	{
	public:
		CTriangle(const Point & p1, const Point & p2, const Point & p3, const uint32_t & color);
		void Draw(graphics_lib_pro::ICanvas & canvas)const override;
	private:
		Point m_p1;
		Point m_p2;
		Point m_p3;
		uint32_t m_color;
	};

	class CRectangle : public ICanvasDrawable
	{
	public:
		CRectangle(const Point & leftTop, int width, int height, const uint32_t & color);
		
		void Draw(graphics_lib_pro::ICanvas & canvas)const override;
	private:
		Point m_leftTop;
		int m_width;
		int m_height;
		uint32_t m_color;
	};

	// ’удожник, способный рисовать ICanvasDrawable-объекты на ICanvas
	class CCanvasPainter
	{
	public:
		CCanvasPainter(graphics_lib_pro::ICanvas & canvas);
		void Draw(const ICanvasDrawable & drawable);
	private:
		graphics_lib_pro::ICanvas & m_canvas;
	};
}
