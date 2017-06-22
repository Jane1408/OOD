#include "stdafx.h"
#include "DeleteItemCommand.h"


CDeleteItemCommand::CDeleteItemCommand(std::vector<CDocumentItem> & items, size_t position)
	: m_items(items)
	, m_position(position)
	, m_item(items[position])
{
}

CDeleteItemCommand::~CDeleteItemCommand()
{
}

void CDeleteItemCommand::DoExecute()
{
	m_items.erase(m_items.begin() + m_position);
}

void CDeleteItemCommand::DoUnexecute()
{
	m_items.insert(m_items.begin() + m_position, m_item);
}
