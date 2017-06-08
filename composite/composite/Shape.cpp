#include "Shape.h"

CShape::CShape()
{
}


CShape::~CShape()
{
}

OptionalStyle CShape::GetLineStyle() const
{
	return m_lineStyle;
}

void CShape::SetLineStyle(const CStyle & style)
{
	m_lineStyle = style;
}

OptionalStyle CShape::GetFillStyle() const
{
	return m_fillStyle;
}

void CShape::SetFillStyle(const CStyle & style)
{
	m_fillStyle = style;
}

RectD CShape::GetFrame() const
{
	return m_frame;
}

void CShape::SetFrame(const RectD & rect)
{
	m_frame = rect;
}

IGroupPtr CShape::GetGroup()
{
	return nullptr;
}