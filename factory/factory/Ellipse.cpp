#include "stdafx.h"

#include "Ellipse.h"


CEllipse::CEllipse(Vector2 const& center, double const& horizontalRadius, double const& verticalRadius)
	: m_center(center)
	, m_horizontalRadius(horizontalRadius)
	, m_verticalRadius(verticalRadius)
{
}


CEllipse::~CEllipse()
{
}

void CEllipse::Draw(ICanvas & canvas) const
{
	canvas.DrawEllipse(m_center, m_horizontalRadius , m_verticalRadius);
}

Vector2 CEllipse::GetCenter()
{
	return m_center;
}

double CEllipse::GetHorizontalRadius()
{
	return m_horizontalRadius;
}

double CEllipse::GetverticalRadius()
{
	return m_verticalRadius;
}