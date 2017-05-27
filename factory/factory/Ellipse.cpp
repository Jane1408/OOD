#include "stdafx.h"

#include "Ellipse.h"


CEllipse::CEllipse(Vector2 const& center, double const& horizontalRadius, double const& verticalRadius)
{
	if ((center.x < 0 || horizontalRadius < 0 || center.y < 0 || verticalRadius < 0) ||
		(center.x - horizontalRadius < 0 || center.y - verticalRadius < 0))
		throw std::invalid_argument("Invalid data");
	m_center = center;
	m_horizontalRadius = horizontalRadius;
	m_verticalRadius = verticalRadius;
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
