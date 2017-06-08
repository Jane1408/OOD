#pragma once
#include "IDrawable.h"
#include "Style.h"
#include <memory>

class IShapesCollection;
class IShape;

using IShapePtr = std::shared_ptr<IShape>;
using IGroupPtr = std::shared_ptr<IShapesCollection>;

class IShape : public IDrawable
{
public:

	virtual ~IShape() = default;

	virtual RectD GetFrame() const = 0;
	virtual void SetFrame(const RectD & rect) = 0;

	virtual OptionalStyle GetLineStyle() const = 0;
	virtual void SetLineStyle(const CStyle& style) = 0;

	virtual OptionalStyle GetFillStyle( ) const = 0;
	virtual void SetFillStyle(const CStyle& style) = 0;
	
	virtual IGroupPtr GetGroup() = 0;
};