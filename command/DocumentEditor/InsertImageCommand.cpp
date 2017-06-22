#include "stdafx.h"
#include "InsertImageCommand.h"


CInsertImageCommand::CInsertImageCommand(std::vector<CDocumentItem> & items, std::shared_ptr<IImage> const & image, size_t position)
	: m_items(items)
	, m_image(image)
	, m_position(position)
{
}

CInsertImageCommand::~CInsertImageCommand()
{
}

void CInsertImageCommand::DoExecute()
{
	m_items.insert(m_items.begin() + m_position, CDocumentItem(m_image));
}

void CInsertImageCommand::DoUnexecute()
{
	m_items.erase(m_items.begin() + m_position);
}
