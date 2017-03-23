#include "stdafx.h"
#include "Shape.h"
#include "Painter.h"


CPainter::CPainter()
{
}

CPainter::~CPainter()
{
}

void CPainter::DrawPicture(CPictureDraft & draft, ICanvas & canvas)
{
	for (auto &shape : draft.GetShapesList())
	{
		shape->Draw(canvas);
	}
}
