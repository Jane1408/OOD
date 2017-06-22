#pragma once
#include "AbstractCommand.h"
#include "IImage.h"

class CResizeImageCommand :
	public CAbstractCommand
{
public:
	CResizeImageCommand(std::shared_ptr<IImage> & image, unsigned oldWidth, unsigned oldHeight, unsigned newWidth, unsigned newHeight);
	~CResizeImageCommand();

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::shared_ptr<IImage> & m_image;
	unsigned m_oldWidth;
	unsigned m_oldHeight;
	unsigned m_newWidth;
	unsigned m_newHeight;
};

