#include "stdafx.h"
#include "Rectangle.h"
#include "Ellipse.h"
#include "Triangle.h"
#include "RegularPolygon.h"
#include "ShapeFactory.h"

void ShowHelp()
{
	std::cout << "<EllipseType> <center.x> <center.y> <horizontalRadius> <verticalRadius> <color>" << std::endl;
	std::cout << "example: Ellipse 5 5 2 3 Red" << std::endl;
	std::cout << "<RectangleType> <leftTop.x> <leftTop.y> <rightBottom.x> <rightBottom.y> <color>" << std::endl;
	std::cout << "example : Rectangle 1 1 4 4 Yellow" << std::endl;
	std::cout << "<TriangleType> <vertex1.x> <vertex1.y> <vertex2.x> <vertex2.y> <vertex3.x> <vertex3.y> <color>" << std::endl;
	std::cout << "example : Triangle 2 2 4 4 0 4 Blue" << std::endl;
	std::cout << "<RegularPolygonType> <vertexCount> <center.y> <center.x> <radius> <color>" << std::endl;
	std::cout << "example : RegularPolygon 5 10 10 7 Blue" << std::endl;
}

Color GetColor(std::istream & dscr)
{
	std::string colorString;
	dscr >> colorString;
	if (STR_TO_COLOR_LIST.find(colorString) == STR_TO_COLOR_LIST.end())
		throw std::invalid_argument("Unknown color");
	return STR_TO_COLOR_LIST.find(colorString)->second;
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
	else if (type == "RegularPolygon")
	{
		return CreateRegularPolygon(dscr);
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
	try 
	{
		dscr >> leftTop.x >> leftTop.y >> rightBottom.x >> rightBottom.y;
		Color color = GetColor(dscr);
		auto shape = std::make_shared<CRectangle>(color, leftTop, rightBottom);
		return shape;
	}
	catch(...)
	{
		std::cout << "Can't create rectangle" << std::endl;
	}
	return std::shared_ptr<CShape>();
}

std::shared_ptr<CShape> CShapeFactory::CreateEllipse(std::istream & dscr)
{
	Vector2 center(-1.0, -1.0);
	double horizontalRadius = -1.0;
	double verticalRadius = -1.0;
	try
	{
		dscr >> center.x >> center.y;
		dscr >> horizontalRadius;
		dscr >> verticalRadius;
		Color color = GetColor(dscr);
		auto shape = std::make_shared<CEllipse>(color, center, horizontalRadius, verticalRadius);
		return shape;
	}
	catch (...)
	{
		std::cout << "Can't create ellipse" << std::endl;
	}
	return std::shared_ptr<CShape>();
}

std::shared_ptr<CShape> CShapeFactory::CreateTriangle(std::istream & dscr)
{
	Vector2 vertex1(-1.0, -1.0);
	Vector2 vertex2(-1.0, -1.0);
	Vector2 vertex3(-1.0, -1.0);
	try
	{
		dscr >> vertex1.x >> vertex1.y;
		dscr >> vertex2.x >> vertex2.y;
		dscr >> vertex3.x >> vertex3.y;
		Color color = GetColor(dscr);
		auto shape = std::make_shared<CTriangle>(color, vertex1, vertex2, vertex3);
		return shape;
	}
	catch (...)
	{
		std::cout << "Can't create triangle" << std::endl;
	}
	return std::shared_ptr<CShape>();
}

std::shared_ptr<CShape> CShapeFactory::CreateRegularPolygon(std::istream & dscr)
{
	size_t vertCount = 0;
	Vector2 center(-1.0, -1.0);
	double radius = 0;
	try
	{
		dscr >> vertCount;
		dscr >> center.x >> center.y;
		dscr >> radius;
		Color color = GetColor(dscr);
		auto shape = std::make_shared<CRegularPolygon>(color, vertCount, center, radius);
		return shape;
	}
	catch (...)
	{
		std::cout << "Can't create regular polygon" << std::endl;
	}
	return std::shared_ptr<CShape>();
}