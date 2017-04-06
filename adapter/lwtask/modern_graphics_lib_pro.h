#pragma once

// ������������ ���� ����������� ����������� ����������� ���������� (���������� ��� ���������)
namespace modern_graphics_lib_pro
{
	class CPoint
	{
	public:
		CPoint(int x, int y);

		int x;
		int y;
	};

	// ���� � ������� RGBA, ������ ��������� ��������� �������� �� 0.0f �� 1.0f
	class CRGBAColor
	{
	public:
		CRGBAColor(float r, float g, float b, float a);
		float r, g, b, a;
	};

	// ����� ��� ������������ ��������� �������
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
