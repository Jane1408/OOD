#pragma once
#include "PictureDraft.h"
#include "ICanvas.h"

class IPainter
{
public:
	IPainter() {};
	~IPainter() {};

	virtual void DrawPicture(CPictureDraft & draft, ICanvas & canvas) = 0;
};

