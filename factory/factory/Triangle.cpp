#include "stdafx.h"
#include "Triangle.h"


CTriangle::CTriangle(Vector2 const& vertex1, Vector2 const& vertex2, Vector2 const& vertex3)
{
	if (vertex1.x < 0 || vertex1.y < 0 || vertex2.x < 0 || vertex2.y < 0 || vertex3.x < 0 || vertex3.y < 0)
		throw std::invalid_argument("Invalid data");
	m_vertex1 = vertex1;
	m_vertex2 = vertex2;
	m_vertex3 = vertex3;
}


CTriangle::~CTriangle()
{
}

void CTriangle::Draw(ICanvas & canvas) const
{
	canvas.DrawLine(m_vertex1, m_vertex2);
	canvas.DrawLine(m_vertex2, m_vertex3);
	canvas.DrawLine(m_vertex3, m_vertex1);

}

Vector2 CTriangle::Getvertex1()
{
	return m_vertex1;
}

Vector2 CTriangle::Getvertex2()
{
	return m_vertex2;
}

Vector2 CTriangle::Getvertex3()
{
	return m_vertex3;
}
