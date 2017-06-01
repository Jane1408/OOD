#include "stdafx.h"
#include "RegularPolygon.h"


CRegularPolygon::CRegularPolygon(Color color, size_t const& vertexCount, Vector2 const& center, double const& radius)
	: m_center(center)
	, CShape(color)
{
	if (vertexCount < 3 || radius <= 0)
		throw std::invalid_argument("Invalid data");
	m_vertexCount = vertexCount;
	m_radius = radius;
}


CRegularPolygon::~CRegularPolygon()
{
}

void CRegularPolygon::Draw(ICanvas & canvas) const
{
	canvas.SetColor(GetColor());

	Vector2 from = {m_radius * cos(0) + m_center.x, m_radius * sin(0) + m_center.y};
	Vector2 to;
	for (size_t i = 1; i <= m_vertexCount; i++)
	{
		double angle = 2 * M_PI * i / m_vertexCount;
		to = { m_radius * cos(angle) + m_center.x, m_radius * sin(angle) + m_center.y };
		canvas.DrawLine(from, to);
		from = to;
	}
}

size_t CRegularPolygon::GetVertexCount()
{
	return m_vertexCount;
}

Vector2 CRegularPolygon::GetCenter()
{
	return m_center;
}

double CRegularPolygon::GetRadius()
{
	return m_radius;
}
