#pragma once
#include "ShapesCollection.h"
#include <vector>


class CGroup :
	public IShape,
	public std::enable_shared_from_this<CGroup>
{
public:
	CGroup();
	~CGroup();

	IShapePtr GetShape(size_t index)const;
	void InsertShape(const IShapePtr &component, size_t position = std::numeric_limits<size_t>::max());
	void RemoveShape(const IShapePtr &component);
	size_t ShapesCount() const;

	OptionalStyle GetLineStyle()const override;
	void SetLineStyle(const CStyle& style) override;

	OptionalStyle GetFillStyle()const override;
	void SetFillStyle(const CStyle& style) override;

	RectD GetFrame() const override;
	void SetFrame(const RectD & rect) override;

	IGroupPtr GetGroup() override;

	void Draw(ICanvas & canvas) const override;

private:
	CShapesCollection m_shapesCollection;
};

