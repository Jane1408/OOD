#include "stdafx.h"
#include "ResizeImageCommand.h"


CResizeImageCommand::CResizeImageCommand(std::shared_ptr<IImage> & image, unsigned oldWidth, unsigned oldHeight, unsigned newWidth, unsigned newHeight)
	: m_oldWidth(oldWidth)
	, m_oldHeight(oldHeight)
	, m_newWidth(newWidth)
	, m_newHeight(newHeight)
	, m_image(image)
{
}

CResizeImageCommand::~CResizeImageCommand()
{
}

void CResizeImageCommand::DoExecute()
{
	m_image->SetSize(m_newWidth, m_newHeight);
}

void CResizeImageCommand::DoUnexecute()
{
	m_image->SetSize(m_oldWidth, m_oldHeight);
}
