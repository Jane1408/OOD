#pragma once
#include "ICanvas.h"

class CSVGCanvas :
	public ICanvas
{
public:
	CSVGCanvas(std::ostream & strm);
	~CSVGCanvas();
	void SetLineColor(RGBAColor color) override;
	void BeginFill(RGBAColor color) override;
	void EndFill() override;
	void MoveTo(double x, double y) override;
	void LineTo(double x, double y) override;
	void DrawEllipse(double left, double top, double width, double height) override;
	void DrawFillShape();

private:
	RGBAColor m_lineColor;
	RGBAColor m_fillColor;
	std::ostream & m_oStrm;
	bool m_isFill;
	std::pair <double, double> m_currPos;
	std::string m_points;
};
