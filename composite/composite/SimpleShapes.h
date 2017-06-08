#pragma once
#include "Shape.h"

class CRectangle : public CShape
{
public:
	CRectangle(const RectD & rect);
	void Draw(ICanvas & canvas) final;
};

class CEllipse : public CShape
{
public:
	CEllipse(const RectD & rect);
	void Draw(ICanvas & canvas) final;
};

class CTriangle : public CShape
{
public:
	CTriangle(const RectD & rect);
	void Draw(ICanvas & canvas) final;
};