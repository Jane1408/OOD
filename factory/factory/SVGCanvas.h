#pragma once
#include "ICanvas.h"

class CSVGCanvas :
	public ICanvas
{
public:
	CSVGCanvas(std::ostream & strm);
	~CSVGCanvas();

	void SetColor(Color color) override;
	void DrawLine(Vector2 from, Vector2 to) override;
	void DrawEllipse(Vector2 center, double horizontalRadius, double verticalRadius) override;
private:
	Color m_currentColor;
	std::ostream & m_oStrm;
};
