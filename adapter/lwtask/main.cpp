#include <iostream>
#include <stdexcept>
#include <string>
#include <boost/format.hpp>
#include <cstdint>
#include <iomanip>
#include "graphics_lib.h"
#include "modern_graphics_lib.h"
#include "shape_drawing_lib.h"
#include "modern_graphics_lib_pro.h"
#include "graphics_lib_pro.h"
#include "shape_drawing_lib_pro.h"


using namespace std;

// Пространство имен приложения (доступно для модификации)
namespace app
{
	class CCanvasAdapter : public graphics_lib::ICanvas
	{
	public:
		CCanvasAdapter(modern_graphics_lib::CModernGraphicsRenderer & renderer)
			: m_renderer(renderer)
			, m_from({0, 0})
		{
			m_renderer.BeginDraw();
		}

		~CCanvasAdapter()
		{
			m_renderer.EndDraw();
		}

		void MoveTo(int x, int y) override
		{
			m_from = { x, y };
		}
		void LineTo(int x, int y) override
		{
			m_renderer.DrawLine(m_from, { x, y });
			m_from = { x, y };
		}

	private:
		modern_graphics_lib::CModernGraphicsRenderer m_renderer;
		modern_graphics_lib::CPoint m_from;
	};


void PaintPicture(shape_drawing_lib::CCanvasPainter & painter)
{
	using namespace shape_drawing_lib;

	CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 });
	CRectangle rectangle({ 30, 40 }, 18, 24);

	painter.Draw(triangle);
	painter.Draw(rectangle);
}

void PaintPictureOnCanvas()
{
	graphics_lib::CCanvas simpleCanvas;
	shape_drawing_lib::CCanvasPainter painter(simpleCanvas);
	PaintPicture(painter);
}

void PaintPictureOnModernGraphicsRenderer()
{
	modern_graphics_lib::CModernGraphicsRenderer renderer(std::cout);
	CCanvasAdapter rendererAdapter(renderer);
	shape_drawing_lib::CCanvasPainter painter(rendererAdapter);
	
	PaintPicture(painter);
}
}

namespace app_pro
{
	class CProAdapter : public graphics_lib_pro::ICanvas
		, public modern_graphics_lib_pro::CModernGraphicsRenderer
	{
	public:
		CProAdapter(std::ostream & strm)
			: modern_graphics_lib_pro::CModernGraphicsRenderer(strm)
			, m_from ({0, 0})
			, m_modernColor(0, 0, 0, 0)
		{
		}

		void MoveTo(int x, int y) override
		{
			m_from = { x, y };
		}
		void LineTo(int x, int y) override
		{
			DrawLine(m_from, { x, y }, m_modernColor);
			m_from = { x, y };
		}

		void SetColor(uint32_t rgbColor) override
		{
			m_color = rgbColor;

			float a = 1.f;
			float r = ((m_color >> 16) & 0xFF) / 255.f;
			float g = ((m_color >> 8) & 0x00FF) / 255.f;
			float b = ((m_color ) & 0x0000FF) / 255.f;
		
			modern_graphics_lib_pro::CRGBAColor color(r,g,b,a);
			m_modernColor = color;
		}

	private:
		modern_graphics_lib_pro::CPoint m_from;
		modern_graphics_lib_pro::CRGBAColor m_modernColor;
		uint32_t m_color;
	};

	void PaintPicture(shape_drawing_lib_pro::CCanvasPainter & painter)
	{
		using namespace shape_drawing_lib_pro;

		CTriangle triangle({ 10, 15 }, { 100, 200 }, { 150, 250 }, 570789);
		CRectangle rectangle({ 30, 40 }, 18, 24, 555555);

		painter.Draw(triangle);
		painter.Draw(rectangle);
	}

	void PaintPictureOnCanvas()
	{
		graphics_lib_pro::CCanvas simpleCanvas;
		shape_drawing_lib_pro::CCanvasPainter painter(simpleCanvas);
		PaintPicture(painter);
	}

	void PaintPictureOnModernGraphicsRenderer()
	{
		CProAdapter adapter(std::cout);
		adapter.BeginDraw();
		shape_drawing_lib_pro::CCanvasPainter painter(adapter);
		PaintPicture(painter);
		adapter.EndDraw();
	}
}

int main()
{
	cout << "Should we use pro API (y)?";
	string userInput;
	if (getline(cin, userInput) && (userInput == "y" || userInput == "Y"))
	{
		cout << "Should we use new pro API (y)?";
		if (getline(cin, userInput) && (userInput == "y" || userInput == "Y"))
		{
			app_pro::PaintPictureOnModernGraphicsRenderer();
		}
		else
		{
			app_pro::PaintPictureOnCanvas();
		}
	}
	else
	{
		cout << "Should we use new API (y)?";
		if (getline(cin, userInput) && (userInput == "y" || userInput == "Y"))
		{
			app::PaintPictureOnModernGraphicsRenderer();
		}
		else
		{
			app::PaintPictureOnCanvas();
		}
	}

	return 0;
}
