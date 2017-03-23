#pragma once
#include "stdafx.h"
#include "Shape.h"

class IShapeFactory
{
public:
	IShapeFactory() {};
	~IShapeFactory() {};

	virtual std::shared_ptr<CShape> CreateShape(std::string const& descriptionShape) = 0;
};

