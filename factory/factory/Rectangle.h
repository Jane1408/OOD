#pragma once
#include "Shape.h"
class CRectangle :
	public CShape
{
public:
	CRectangle(Vector2 const& leftTop, Vector2 const& rightBottom);
	~CRectangle();

	void Draw(ICanvas & canvas) const override;
	
	Vector2 GetLeftTop();
	Vector2 GetRightBottom();

private:
	Vector2 m_leftTop;
	Vector2 m_rightBottom;
};

