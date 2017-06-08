#pragma once
#include "IShape.h"
#include "IShapeCollection.h"

class IGroup : public IShape, public IShapesCollection
{
public:
	virtual ~IGroup() = default;
};