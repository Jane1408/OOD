#include "stdafx.h"
#include "Shape.h"
#include "PictureDraft.h"


CPictureDraft::CPictureDraft()
{
}


CPictureDraft::~CPictureDraft()
{
}

size_t CPictureDraft::GetShapeCount() const
{
	return m_shapes.size();
}

std::shared_ptr<CShape> CPictureDraft::GetShape(size_t position) const
{
	if (position < m_shapes.size())
	{
		return m_shapes[position];
	}
	else
	{
		return std::shared_ptr<CShape>();
	}
}

std::vector<std::shared_ptr<CShape>> CPictureDraft::GetShapesList()
{
	return m_shapes;
}

void CPictureDraft::AddShape(std::shared_ptr<CShape> const & shape)
{
	m_shapes.push_back(shape);
}
