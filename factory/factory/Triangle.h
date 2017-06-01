#pragma once
#include "Shape.h"
class CTriangle :
	public CShape
{
public:
	CTriangle(Color color, Vector2 const& vertex1, Vector2 const& vertex2, Vector2 const& vertex3);
	~CTriangle();

	void Draw(ICanvas & canvas) const override;

	Vector2 Getvertex1();
	Vector2 Getvertex2();
	Vector2 Getvertex3();

private:
	Vector2 m_vertex1;
	Vector2 m_vertex2;
	Vector2 m_vertex3;
};

