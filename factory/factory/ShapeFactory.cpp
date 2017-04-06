#include "stdafx.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Triangle.h"
#include "ShapeFactory.h"

void ShowHelp()
{
	std::cout << "<EllipseType> <center.x> <center.y> <horizontalRadius> <verticalRadius>" << std::endl;
	std::cout << "example: Ellipse 5 5 2 3" << std::endl;
	std::cout << "<RectangleType> <leftTop.x> <leftTop.y> <rightBottom.x> <rightBottom.y>" << std::endl;
	std::cout << "example : Rectangle 1 1 4 4" << std::endl;
	std::cout << "<TriangleType> <vertex1.x> <vertex1.y> <vertex2.x> <vertex2.y> <vertex3.x> <vertex3.y>" << std::endl;
	std::cout << "example : Triangle 2 2 4 4 0 4" << std::endl;
}

CShapeFactory::CShapeFactory()
{
}


CShapeFactory::~CShapeFactory()
{
}

std::shared_ptr<CShape> CShapeFactory::CreateShape(std::string const & descriptionShape)
{
	std::stringstream dscr(descriptionShape);
	std::string type;
	dscr >> type;
	if (type == "Rectangle")
	{
		return CreateRectangle(dscr);
	}
	else if (type == "Ellipse")
	{
		return CreateEllipse(dscr);
	}
	else if (type == "Triangle")
	{
		return CreateTriangle(dscr);
	}
	else if (type == "help")
	{
		ShowHelp();
		throw std::invalid_argument("Show Help");
	}
	else
	{
		throw std::invalid_argument("Unknown type");
	}
	return std::shared_ptr<CShape>();
}

std::shared_ptr<CShape> CShapeFactory::CreateRectangle(std::istream & dscr)
{
	
	Vector2 leftTop(-1.0, -1.0);
	Vector2 rightBottom(-1.0, -1.0);
	dscr >> leftTop.x >> leftTop.y >> rightBottom.x >> rightBottom.y;

	if ((leftTop.x < rightBottom.x || leftTop.y > rightBottom.y)
		&& !(leftTop.x >= 0 && rightBottom.x >= 0 && leftTop.y >= 0 && rightBottom.y >= 0))
	{
		throw std::invalid_argument("Invalid data");
	}

	auto shape = std::make_shared<CRectangle>(leftTop, rightBottom);
	return shape;
}

std::shared_ptr<CShape> CShapeFactory::CreateEllipse(std::istream & dscr)
{
	Vector2 center(-1.0, -1.0);
	double horizontalRadius = -1.0;
	double verticalRadius = -1.0;
	dscr >> center.x >> center.y;
	dscr >> horizontalRadius;
	dscr >> verticalRadius;

	if (!(center.x >= 0 && horizontalRadius >= 0 && center.y >= 0 && verticalRadius >= 0))
	{
		throw std::invalid_argument("Invalid data");
	}

	auto shape = std::make_shared<CEllipse>(center, horizontalRadius, verticalRadius);
	return shape;
}

std::shared_ptr<CShape> CShapeFactory::CreateTriangle(std::istream & dscr)
{
	Vector2 vertex1(-1.0, -1.0);
	Vector2 vertex2(-1.0, -1.0);
	Vector2 vertex3(-1.0, -1.0);
	dscr >> vertex1.x >> vertex1.y;
	dscr >> vertex2.x >> vertex2.y;
	dscr >> vertex3.x >> vertex3.y;

	if (!(vertex1.x >= 0 && vertex1.y >= 0 && vertex2.x >= 0 && vertex2.y >= 0 && vertex3.x >= 0 && vertex3.y >= 0))
	{
		throw std::invalid_argument("Invalid data");
	}

	auto shape = std::make_shared<CTriangle>(vertex1, vertex2, vertex3);
	return shape;
}
