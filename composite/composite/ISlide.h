#pragma once
#include "IDrawable.h"
#include "IShapeCollection.h"

class ISlide :
	public IDrawable
{
public:
	virtual ~ISlide() = default;

	virtual double GetWidth()const = 0;
	virtual double GetHeight()const = 0;
};

