#pragma once
#include "Shape.h"
class CRegularPolygon :
	public CShape
{
public:
	CRegularPolygon(Color color, size_t const& vertexCount, Vector2 const& center, double const& radius);
	~CRegularPolygon();

	void Draw(ICanvas & canvas) const override;

	size_t GetVertexCount();
	Vector2 GetCenter();
	double GetRadius();

private:
	size_t m_vertexCount;
	Vector2 m_center;
	double m_radius;
};

