#pragma once
#include "IShape.h"

class CShape :
	public IShape
{
public:
	CShape();
	~CShape();

	OptionalStyle GetLineStyle()const override;
	void SetLineStyle(const CStyle& style) override;

	OptionalStyle GetFillStyle()const override;
	void SetFillStyle(const CStyle& style) override;

	RectD GetFrame() const override;
	void SetFrame(const RectD & rect) override;

	IGroupPtr GetGroup() override;
private:
	RectD m_frame;

	CStyle m_lineStyle;
	CStyle m_fillStyle;
};

