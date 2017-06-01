#pragma once
#include "ICanvas.h"

class CShape
{
public:
	CShape(Color color);
	virtual ~CShape();

	virtual void Draw(ICanvas & canvas) const;
	virtual Color GetColor() const;

private:

	Color m_color;
};

