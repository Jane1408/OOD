#pragma once
#include "PictureDraft.h"
#include "ICanvas.h"

class IPainter
{
public:
	IPainter() {};
	virtual ~IPainter() = default;

	virtual void DrawPicture(CPictureDraft & draft, ICanvas & canvas) = 0;
};

