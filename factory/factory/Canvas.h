#pragma once
#include "ICanvas.h"
class CCanvas :
	public ICanvas
{
public:
	CCanvas();
	~CCanvas();

	void SetColor(Color color) override;
	void DrawLine(Vector2 from, Vector2 to) override;
	void DrawEllipse(Vector2 center, double harizontalRadius, double verticalRadius) override;

private:

	Color m_currentColor;
};

