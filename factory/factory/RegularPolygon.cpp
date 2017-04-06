#include "stdafx.h"
#include "RegularPolygon.h"


CRegularPolygon::CRegularPolygon(size_t const& vertexCount, Vector2 const& center, double const& radius)
	:m_vertexCount(vertexCount)
	, m_center(center)
	, m_radius(radius)
{
}


CRegularPolygon::~CRegularPolygon()
{
}

void CRegularPolygon::Draw(ICanvas & canvas) const
{
	
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
