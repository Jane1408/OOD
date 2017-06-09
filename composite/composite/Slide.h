#pragma once
#include "ISlide.h"
#include "ShapesCollection.h"
#include <vector>

class CSlide :
	public ISlide
{
public:
	CSlide();
	~CSlide();

	double GetWidth()const override;
	double GetHeight()const override;

	IShapePtr GetShape(size_t index)const;
	void InsertShape(const IShapePtr &component, size_t position = std::numeric_limits<size_t>::max());
	void RemoveShape(const IShapePtr &component);
	size_t ShapesCount() const;

	RGBAColor GetBackgroundColor()const;
	void SetBackgroundColor(RGBAColor color);
	void Draw(ICanvas & canvas) const override;

private:
	RGBAColor m_backgroundColor;
	CShapesCollection m_shapesCollection;

};
