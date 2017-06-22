#pragma once
#include "DocumentItem.h"
#include "AbstractCommand.h"

class CInsertParagraphCommand :
	public CAbstractCommand
{
public:
	CInsertParagraphCommand(std::vector<CDocumentItem> & items,	std::shared_ptr<IParagraph> const & paragraph,	size_t pos);
	~CInsertParagraphCommand();

protected:
	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::shared_ptr<IParagraph> m_paragraph;
	std::vector<CDocumentItem> & m_items;
	size_t m_position;
};

