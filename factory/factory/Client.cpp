#include "stdafx.h"
#include "Client.h"


CClient::CClient(IDesigner & designer, IPainter & painter)
	: m_designer(designer)
	, m_painter(painter)
{
}

CClient::~CClient()
{
}

void CClient::TurnToDesigner(std::istream & strm)
{
	m_pictureDraft = m_designer.CreateDraft(strm);
}

void CClient::TurnToPainter(ICanvas & canvas)
{
	m_painter.DrawPicture(m_pictureDraft, canvas);
}
