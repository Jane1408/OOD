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
	if (index >= m_shapes.size())
	{
		throw std::invalid_argument("Shapes index out of range");
	}
	return m_shapes.at(index);
}

void CGroup::InsertShape(const IShapePtr & component, size_t position)
{
	if (position == std::numeric_limits<size_t>::max())
	{
		m_shapes.push_back(component);
	}
	else if (position >= m_shapes.size())
	{
		throw std::invalid_argument("Shape position out of range");
	}
	else
	{
		m_shapes.insert(m_shapes.begin() + position, component);
	}
}

void CGroup::RemoveShape(const IShapePtr & component)
{
	for (auto i = m_shapes.begin(); i != m_shapes.end(); ++i)
	{
		if (*i == component)
		{
			m_shapes.erase(i);
		}
	}
}

size_t CGroup::ShapesCount() const
{
	return m_shapes.size();
}

OptionalStyle CGroup::GetLineStyle() const
{
	OptionalStyle style;
	for (auto &shape : m_shapes)
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
	for (auto &shape : m_shapes)
	{
		shape->SetLineStyle(style);
	}
}

OptionalStyle CGroup::GetFillStyle() const
{
	OptionalStyle style;
	for (auto &shape : m_shapes)
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
	for (auto &shape : m_shapes)
	{
		shape->SetFillStyle(style);
	}
}

RectD CGroup::GetFrame() const
{
	if (m_shapes.empty())
	{
		return { 0,0,0,0 };
	}
	RectD rect = m_shapes.front()->GetFrame();
	for (auto &shape : m_shapes)
	{
		RectD shapeRect = shape->GetFrame();
		rect.left = std::min(shapeRect.left, rect.left);
		rect.top = std::min(shapeRect.top, rect.top);
		rect.width = std::max(shapeRect.width, rect.width);
		rect.height = std::max(shapeRect.height, rect.height);
	}
	return rect;
}

void CGroup::SetFrame(const RectD & rect)
{
	auto currentRect = GetFrame();
	auto xScale = rect.width / currentRect.width;
	auto yScale = rect.height / currentRect.height;

	for (auto &shape : m_shapes)
	{
		auto shapeRect = shape->GetFrame();
		auto xOffset = rect.left - currentRect.left;
		auto yOffset = rect.top - currentRect.top;

		RectD newRect{ shapeRect.left + xOffset, shapeRect.top + yOffset, shapeRect.width * xScale, shapeRect.height * yScale };
		shape->SetFrame(newRect);
	}
}

IGroupPtr CGroup::GetGroup()
{
	return shared_from_this();
}

void CGroup::Draw(ICanvas & canvas)
{
	for (auto &shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}
