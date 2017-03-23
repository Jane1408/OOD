#pragma once
#include "IPainter.h"
#include "IDesigner.h"
#include "PictureDraft.h"

class CClient
{
public:
	CClient(IDesigner & designer, IPainter & painter);
	~CClient();

	void TurnToDesigner(std::istream & strm);
	void TurnToPainter(ICanvas & canvas);

private:
	IDesigner & m_designer;
	IPainter & m_painter;
	CPictureDraft m_pictureDraft;
};

