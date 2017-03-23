#pragma once
#include "IPainter.h"
class CPainter :
	public IPainter
{
public:
	CPainter();
	~CPainter();

	void DrawPicture(CPictureDraft & draft, ICanvas & canvas) override;
};

