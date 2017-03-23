#include "stdafx.h"
#include "ShapeFactory.h"
#include "Designer.h"


CDesigner::CDesigner()
	: m_shapeFactory(std::make_unique<CShapeFactory>())
{
}


CDesigner::~CDesigner()
{
}

CPictureDraft CDesigner::CreateDraft(std::istream & strm)
{
	CPictureDraft draft;
	std::string str;
	while (std::getline(strm, str))
	{
		try
		{
			draft.AddShape(m_shapeFactory->CreateShape(str));
		}
		catch (...)
		{
			std::cout << "Can't create shape" << std::endl;
		}
	}
	return draft;
}
