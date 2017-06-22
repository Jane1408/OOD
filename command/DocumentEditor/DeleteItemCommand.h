#pragma once
#include "DocumentItem.h"

#include "AbstractCommand.h"
class CDeleteItemCommand :
	public CAbstractCommand
{
public:
	CDeleteItemCommand(std::vector<CDocumentItem> & items, size_t position);
	~CDeleteItemCommand();

	void DoExecute() override;
	void DoUnexecute() override;

private:
	std::vector<CDocumentItem> & m_items;
	size_t m_position;
	CDocumentItem m_item;
};

