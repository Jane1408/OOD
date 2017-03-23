#include "stdafx.h"
#include "Rectangle.h"


CRectangle::CRectangle(Vector2 const& leftTop, Vector2 const& rightBottom)
	: m_leftTop(leftTop)
	, m_rightBottom(rightBottom)
{
}


CRectangle::~CRectangle()
{
}

void CRectangle::Draw(ICanvas & canvas) const
{
	canvas.DrawLine(m_leftTop, { m_rightBottom.x, m_leftTop.y });
	canvas.DrawLine({ m_rightBottom.x, m_leftTop.y }, m_rightBottom);
	canvas.DrawLine(m_rightBottom, { m_leftTop.x, m_rightBottom.y, });
	canvas.DrawLine({ m_leftTop.x, m_rightBottom.y, }, m_leftTop);
}

Vector2 CRectangle::GetLeftTop()
{
	return m_leftTop;
}

Vector2 CRectangle::GetRightBottom()
{
	return m_rightBottom;
}
