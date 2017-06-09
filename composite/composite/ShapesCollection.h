#pragma once
#include "IShapeCollection.h"

class CShapesCollection :
	public IShapesCollection
{
public:
	CShapesCollection();
	~CShapesCollection();

	IShapePtr GetShape(size_t index)const override;
	void InsertShape(const IShapePtr &component, size_t position = std::numeric_limits<size_t>::max()) override;
	void RemoveShape(const IShapePtr &component) override;
	size_t ShapesCount() const override;

	const std::vector<IShapePtr> & GetShapes() const override;

private:
	std::vector<IShapePtr> m_shapes;
};

