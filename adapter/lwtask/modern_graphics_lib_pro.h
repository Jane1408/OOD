#pragma once

// Пространство имен обновленной современной графической библиотеки (недоступно для изменения)
namespace modern_graphics_lib_pro
{
	class CPoint
	{
	public:
		CPoint(int x, int y);

		int x;
		int y;
	};

	// Цвет в формате RGBA, каждый компонент принимает значения от 0.0f до 1.0f
	class CRGBAColor
	{
	public:
		CRGBAColor(float r, float g, float b, float a);
		float r, g, b, a;
	};

	// Класс для современного рисования графики
	class CModernGraphicsRenderer
	{
	public:
		CModernGraphicsRenderer(std::ostream & strm);
		~CModernGraphicsRenderer();

		void BeginDraw();

		void DrawLine(const CPoint & start, const CPoint & end, const CRGBAColor& color);

		void EndDraw();
	private:
		std::ostream & m_out;
		bool m_drawing = false;
	};
}
