#pragma once
#include "IDesigner.h"
#include "IShapeFactory.h"

class CDesigner :
	public IDesigner
{
public:
	CDesigner();
	~CDesigner();
	CPictureDraft CreateDraft(std::istream & strm) override;

private:
	std::unique_ptr<IShapeFactory> m_shapeFactory;

};

