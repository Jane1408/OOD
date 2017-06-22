#include "stdafx.h"
#include "ChangeStringCommand.h"
#include "Paragraph.h"


CParagraph::CParagraph(std::string const & text, CHistory & history)
	: m_text(text)
	, m_history(history)
{
}

CParagraph::~CParagraph()
{
}

std::string CParagraph::GetText() const
{
	return m_text;
}

void CParagraph::SetText(const std::string & text)
{
	m_history.AddAndExecuteCommand(std::make_unique<CChangeStringCommand>(m_text, text));
}
