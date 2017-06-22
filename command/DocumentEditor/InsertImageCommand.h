#pragma once
#include "AbstractCommand.h"
#include "DocumentItem.h"
#include "IImage.h"


class CInsertImageCommand :
	public CAbstractCommand
{
public:
	CInsertImageCommand(std::vector<CDocumentItem> & items, std::shared_ptr<IImage> const & image, size_t position);
	~CInsertImageCommand();

protected:
	void DoExecute() override;
	void DoUnexecute() override;
private:
	std::shared_ptr<IImage> m_image;
	size_t m_position;
	std::vector<CDocumentItem> & m_items;
};


