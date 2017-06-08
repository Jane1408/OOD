#pragma once
#include "ICanvas.h"
#include <iostream>

class CCanvas :
	public ICanvas
{
public:
	CCanvas(std::ostream& strm);
	~CCanvas();
	void SetLineColor(RGBAColor color) override;
	void BeginFill(RGBAColor color) override;
	void EndFill() override;
	void MoveTo(double x, double y) override;
	void LineTo(double x, double y) override;
	void DrawEllipse(double left, double top, double width, double height) override;
private:
	std::string TextedColor(RGBAColor color);

	std::ostream& m_strm;
};
