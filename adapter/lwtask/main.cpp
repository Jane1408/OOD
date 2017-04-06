﻿#include <iostream>
#include <stdexcept>
#include <string>
#include <boost/format.hpp>
#include <cstdint>

using namespace std;

// Пространство имен графической библиотеки (недоступно для изменения)
namespace graphics_lib
{
// Холст для рисования
	class ICanvas
	{
	public:
		virtual void MoveTo(int x, int y) = 0;
		virtual void LineTo(int x, int y) = 0;
		virtual ~ICanvas() = default;
	};

// Реализация холста для рисования
class CCanvas : public ICanvas
{
public:
	void MoveTo(int x, int y) override
	{
		cout << "MoveTo (" << x << ", " << y << ")" << endl;
	}
	void LineTo(int x, int y) override
	{
		cout << "LineTo (" << x << ", " << y << ")" << endl;
	}
};
}

// Пространство имен библиотеки для рисования фигур (использует graphics_lib)
// Код библиотеки недоступен для изменения
namespace shape_drawing_lib
{
	struct Point
	{
		int x;
		int y;
	};

	// Интерфейс объектов, которые могут быть нарисованы на холсте из graphics_lib
	class ICanvasDrawable
	{
	public:
		virtual void Draw(graphics_lib::ICanvas & canvas)const = 0;
		virtual ~ICanvasDrawable() = default;
	};

	class CTriangle : public ICanvasDrawable
	{
	public:
		CTriangle(const Point & p1, const Point & p2, const Point & p3)
			: m_p1(p1)
			, m_p2(p2)
			, m_p3(p3)
		{
		}

		void Draw(graphics_lib::ICanvas & canvas)const override
		{
			canvas.MoveTo(m_p1.x, m_p1.y);
			canvas.LineTo(m_p2.x, m_p2.y);
			canvas.LineTo(m_p3.x, m_p3.y);
			canvas.LineTo(m_p1.x, m_p1.y);
		}
	private:
		Point m_p1;
		Point m_p2;
		Point m_p3;
	};

	class CRectangle : public ICanvasDrawable
	{
	public:
		CRectangle(const Point & leftTop, int width, int height)
			: m_leftTop(leftTop)
			, m_width(width)
			, m_height(height)
		{
		}

		void Draw(graphics_lib::ICanvas & canvas)const override
		{
			canvas.MoveTo(m_leftTop.x, m_leftTop.y);
			canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y);
			canvas.LineTo(m_leftTop.x + m_width, m_leftTop.y + m_height);
			canvas.LineTo(m_leftTop.x, m_leftTop.y + m_height);
			canvas.LineTo(m_leftTop.x, m_leftTop.y);
		}
	private:
		Point m_leftTop;
		int m_width;
		int m_height;
	};

	// Художник, способный рисовать ICanvasDrawable-объекты на ICanvas
	class CCanvasPainter
	{
	public:
		CCanvasPainter(graphics_lib::ICanvas & canvas)
			: m_canvas(canvas)
		{
		}
		void Draw(const ICanvasDrawable & drawable)
		{
			drawable.Draw(m_canvas);
		}
	private:
		graphics_lib::ICanvas & m_canvas;
	};
}

// Пространство имен современной графической библиотеки (недоступно для изменения)
namespace modern_graphics_lib
{
	class CPoint
	{
	public:
		CPoint(int x, int y) :x(x), y(y) {}

		int x;
		int y;
	};

	// Класс для современного рисования графики
	class CModernGraphicsRenderer
	{
	public:
		CModernGraphicsRenderer(ostream & strm) : m_out(strm)
		{
		}

		~CModernGraphicsRenderer()
		{
			if (m_drawing) // Завершаем рисование, если оно было начато
			{
				EndDraw();
			}
		}

		// Этот метод должен быть вызван в начале рисования
		void BeginDraw()
		{
			if (m_drawing)
			{
				throw logic_error("Drawing has already begun");
			}
			m_out << "<draw>" << endl;
			m_drawing = true;
		}

		// Выполняет рисование линии
		void DrawLine(const CPoint & start, const CPoint & end)
		{
			if (!m_drawing)
			{
				throw logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
			}
			m_out << boost::format(R"(  <line fromX="%1%" fromY="%2%" toX="%3%" toY="%4%"/>)") % start.x % start.y % end.x % end.y << endl;
		}

		// Этот метод должен быть вызван в конце рисования
		void EndDraw()
		{
			if (!m_drawing)
			{
				throw logic_error("Drawing has not been started");
			}
			m_out << "</draw>" << endl;
			m_drawing = false;
		}
	private:
		ostream & m_out;
		bool m_drawing = false;
	};
}

// Пространство имен приложения (доступно для модификации)
namespace app
{
	class CAdapterCanvas : public graphics_lib::ICanvas
	{
	public:
		CAdapterCanvas(modern_graphics_lib::CModernGraphicsRenderer & renderer)
			: m_renderer(renderer)
			, m_from({0, 0})
		{
		}
		void MoveTo(int x, int y) override
		{
			m_from = { x, y };
		}
		void LineTo(int x, int y) override
		{
			m_renderer.BeginDraw();
			m_renderer.DrawLine(m_from, { x, y });
			m_renderer.EndDraw();
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
	modern_graphics_lib::CModernGraphicsRenderer renderer(cout);
	CAdapterCanvas rendererAdapter(renderer);
	shape_drawing_lib::CCanvasPainter painter(rendererAdapter);
	PaintPicture(painter);
	// TODO: при помощи существующей функции PaintPicture() нарисовать
	// картину на renderer
	// Подсказка: используйте паттерн "Адаптер"
}
}

namespace graphics_lib_pro
{
// Холст для рисования
class ICanvas
{
public:
	// Установка цвета в формате 0xRRGGBB
	virtual void SetColor(uint32_t rgbColor) = 0;
	virtual void MoveTo(int x, int y) = 0;
	virtual void LineTo(int x, int y) = 0;
	virtual ~ICanvas() = default;
};

// Реализация холста для рисования
class CCanvas : public ICanvas
{
public:
	void SetColor(uint32_t rgbColor) override
	{
		// TODO: вывести в output цвет в виде строки SetColor (#RRGGBB)
	}
	void MoveTo(int x, int y) override
	{
		cout << "MoveTo (" << x << ", " << y << ")" << endl;
	}
	void LineTo(int x, int y) override
	{
		cout << "LineTo (" << x << ", " << y << ")" << endl;
	}
};
}

// Пространство имен обновленной современной графической библиотеки (недоступно для изменения)
namespace modern_graphics_lib_pro
{
	class CPoint
	{
	public:
		CPoint(int x, int y) :x(x), y(y) {}

		int x;
		int y;
	};

	// Цвет в формате RGBA, каждый компонент принимает значения от 0.0f до 1.0f
	class CRGBAColor
	{
	public:
		CRGBAColor(float r, float g, float b, float a) :r(r), g(g), b(b), a(a) {}
		float r, g, b, a;
	};

	// Класс для современного рисования графики
	class CModernGraphicsRenderer
	{
	public:
		CModernGraphicsRenderer(ostream & strm) : m_out(strm)
		{
		}

		~CModernGraphicsRenderer()
		{
			if (m_drawing) // Завершаем рисование, если оно было начато
			{
				EndDraw();
			}
		}

		// Этот метод должен быть вызван в начале рисования
		void BeginDraw()
		{
			if (m_drawing)
			{
				throw logic_error("Drawing has already begun");
			}
			m_out << "<draw>" << endl;
			m_drawing = true;
		}

		// Выполняет рисование линии
		void DrawLine(const CPoint & start, const CPoint & end, const CRGBAColor& color)
		{
			/*	cout << boost::format(R"(<line fromX="%1%" fromY="%2%" toX="%3%" toY="%4%">
					<color r="%5%" g="%6%" b="%7%" a="%8%" />
					 </line>)") */
					 // TODO: выводит в output инструкцию для рисования линии в виде
					 // <line fromX="3" fromY="5" toX="5" toY="17">
					 //   <color r="0.35" g="0.47" b="1.0" a="1.0" />
					 // </line>
					 // Можно вызывать только между BeginDraw() и EndDraw()
		}

		// Этот метод должен быть вызван в конце рисования
		void EndDraw()
		{
			if (!m_drawing)
			{
				throw logic_error("Drawing has not been started");
			}
			m_out << "</draw>" << endl;
			m_drawing = false;
		}
	private:
		ostream & m_out;
		bool m_drawing = false;
	};
}

int main()
{
	cout << "Should we use new API (y)?";
	string userInput;
	if (getline(cin, userInput) && (userInput == "y" || userInput == "Y"))
	{
		app::PaintPictureOnModernGraphicsRenderer();
	}
	else
	{
		app::PaintPictureOnCanvas();
	}

	return 0;
}
