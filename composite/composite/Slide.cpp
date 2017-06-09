#include "stdafx.h"
#include "Slide.h"
#include <algorithm>


CSlide::CSlide()
{
}

CSlide::~CSlide()
{
}

double CSlide::GetWidth() const
{
	double width = 0;
	for (auto &shape : m_shapesCollection.GetShapes())
	{
		RectD frame = shape->GetFrame();
		width = std::max(width, frame.left + frame.width);
	}
	return width;
}

double CSlide::GetHeight() const
{
	double height = 0;
	for (auto &shape : m_shapesCollection.GetShapes())
	{
		RectD frame = shape->GetFrame();
		height = std::max(height, frame.top + frame.height);
	}
	return height;
}

IShapePtr CSlide::GetShape(size_t index) const
{
	return m_shapesCollection.GetShape(index);
}

void CSlide::InsertShape(const IShapePtr & component, size_t position)
{
	m_shapesCollection.InsertShape(component);
}

void CSlide::RemoveShape(const IShapePtr & component)
{
	m_shapesCollection.RemoveShape(component);
}

size_t CSlide::ShapesCount() const
{
	return m_shapesCollection.ShapesCount();
}

RGBAColor CSlide::GetBackgroundColor() const
{
	return m_backgroundColor;
}

void CSlide::SetBackgroundColor(RGBAColor color)
{
	m_backgroundColor = color;
}

void CSlide::Draw(ICanvas & canvas) const
{
	canvas.BeginFill(m_backgroundColor);
	canvas.EndFill();
	for (auto &shape : m_shapesCollection.GetShapes())
	{
		shape->Draw(canvas);
	}
}