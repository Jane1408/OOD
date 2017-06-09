#include "stdafx.h"
#include <algorithm>
#include "CommonTypes.h"
#include "Group.h"

CGroup::CGroup()
{
}


CGroup::~CGroup()
{
}

IShapePtr CGroup::GetShape(size_t index) const
{
	return m_shapesCollection.GetShape(index);
}

void CGroup::InsertShape(const IShapePtr & component, size_t position)
{
	m_shapesCollection.InsertShape(component);
}

void CGroup::RemoveShape(const IShapePtr & component)
{
	m_shapesCollection.RemoveShape(component);
}

size_t CGroup::ShapesCount() const
{
	return m_shapesCollection.ShapesCount();
}

OptionalStyle CGroup::GetLineStyle() const
{
	OptionalStyle style;
	for (auto &shape : m_shapesCollection.GetShapes())
	{
		if (!style)
		{
			style = shape->GetLineStyle();
		}
		else if (style != shape->GetLineStyle())
		{
			return OptionalStyle();
		}
	}
	return style;
}

void CGroup::SetLineStyle(const CStyle & style)
{
	for (auto &shape : m_shapesCollection.GetShapes())
	{
		shape->SetLineStyle(style);
	}
}

OptionalStyle CGroup::GetFillStyle() const
{
	OptionalStyle style;
	for (auto &shape : m_shapesCollection.GetShapes())
	{
		if (!style)
		{
			style = shape->GetFillStyle();
		}
		else if (style != shape->GetFillStyle())
		{
			return OptionalStyle();
		}
	}
	return style;
}

void CGroup::SetFillStyle(const CStyle & style)
{
	for (auto &shape : m_shapesCollection.GetShapes())
	{
		shape->SetFillStyle(style);
	}
}

RectD CGroup::GetFrame() const
{
	auto shapes = m_shapesCollection.GetShapes();
	if (shapes.empty())
	{
		return { 0,0,0,0 };
	}
	RectD rect = shapes.front()->GetFrame();
	for (auto &shape : shapes)
	{
		RectD shapeRect = shape->GetFrame();
		rect.left = std::min(shapeRect.left, rect.left);
		rect.top = std::min(shapeRect.top, rect.top);
		rect.width = std::max(shapeRect.width, rect.left + rect.width);
		rect.height = std::max(shapeRect.height, rect.top + rect.height);
	}
	return rect;
}

void CGroup::SetFrame(const RectD & rect)
{
	auto currentRect = GetFrame();
	auto xScale = rect.width / currentRect.width;
	auto yScale = rect.height / currentRect.height;

	for (auto &shape : m_shapesCollection.GetShapes())
	{
		auto shapeRect = shape->GetFrame();
		auto xOffset = (shapeRect.left - currentRect.left) * xScale;
		auto yOffset = (shapeRect.top - currentRect.top) * yScale;

		RectD newRect{ rect.left + xOffset, rect.top + yOffset, shapeRect.width * xScale, shapeRect.height * yScale };
		shape->SetFrame(newRect);
	}
}

IGroupPtr CGroup::GetGroup()
{
	return shared_from_this();
}

void CGroup::Draw(ICanvas & canvas) const
{
	for (auto &shape : m_shapesCollection.GetShapes())
	{
		shape->Draw(canvas);
	}
}
