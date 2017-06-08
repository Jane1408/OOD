#pragma once
#include "ISlide.h"
#include <vector>

class CSlide :
	public ISlide,
	public IShapesCollection
{
public:
	CSlide();
	~CSlide();

	double GetWidth()const override;
	double GetHeight()const override;

	IShapePtr GetShape(size_t index)const override;
	void InsertShape(const IShapePtr &component, size_t position = std::numeric_limits<size_t>::max()) override;
	void RemoveShape(const IShapePtr &component) override;
	size_t ShapesCount() const override;

	RGBAColor GetBackgroundColor()const;
	void SetBackgroundColor(RGBAColor color);
	void Draw(ICanvas & canvas) override;

private:
	RGBAColor m_backgroundColor;
	std::vector<IShapePtr> m_shapes;

};
