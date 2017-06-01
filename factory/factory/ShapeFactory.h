#pragma once
#include "IShapeFactory.h"
class CShapeFactory :
	public IShapeFactory
{
public:
	CShapeFactory();
	~CShapeFactory();

	std::shared_ptr<CShape> CreateShape(std::string const& descriptionShape) override;
private:
	std::shared_ptr<CShape> CreateRectangle(std::istream & dscr);
	std::shared_ptr<CShape> CreateEllipse(std::istream & dscr);
	std::shared_ptr<CShape> CreateTriangle(std::istream & dscr);
	std::shared_ptr<CShape> CreateRegularPolygon(std::istream & dscr);
};

