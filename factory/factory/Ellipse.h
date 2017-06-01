#pragma once
#include "Shape.h"
class CEllipse :
	public CShape
{
public:
	CEllipse(Color color, Vector2 const& center, double const& horizontalRadius, double const& verticalRadius);
	~CEllipse();

	void Draw(ICanvas & canvas) const override;

	Vector2 GetCenter();
	double GetHorizontalRadius();
	double GetverticalRadius();

private:
	double m_horizontalRadius;
	double m_verticalRadius;
	Vector2 m_center;

};

