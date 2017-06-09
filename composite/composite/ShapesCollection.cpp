#include "stdafx.h"
#include <vector>
#include "ShapesCollection.h"



CShapesCollection::CShapesCollection()
{
}


CShapesCollection::~CShapesCollection()
{
}

IShapePtr CShapesCollection::GetShape(size_t index) const
{
	if (index >= m_shapes.size())
	{
		throw std::invalid_argument("Shapes index out of range");
	}
	return m_shapes.at(index);
}

void CShapesCollection::InsertShape(const IShapePtr & component, size_t position)
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

void CShapesCollection::RemoveShape(const IShapePtr & component)
{
	for (auto i = m_shapes.begin(); i != m_shapes.end(); ++i)
	{
		if (*i == component)
		{
			m_shapes.erase(i);
		}
	}
}

size_t CShapesCollection::ShapesCount() const
{
	return m_shapes.size();
}

const std::vector<IShapePtr>& CShapesCollection::GetShapes() const
{
	return m_shapes;
}
