#include <vector>
#include "InsertParagraphCommand.h"


CInsertParagraphCommand::CInsertParagraphCommand(std::vector<CDocumentItem> & items, std::shared_ptr<IParagraph> const & paragraph, size_t pos)
	: m_items(items)
	, m_paragraph(paragraph)
	, m_position(pos)
{
}

CInsertParagraphCommand::~CInsertParagraphCommand()
{
}
