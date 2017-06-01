#include "stdafx.h"
#include "Shape.h"


CShape::CShape(Color color)
	: m_color(color)
{
}


CShape::~CShape()
{
}

void CShape::Draw(ICanvas & canvas) const
{
}

Color CShape::GetColor() const
{
	return m_color;
}
