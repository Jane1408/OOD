#pragma once
#include "IParagraph.h"
#include "History.h"

class CParagraph :
	public IParagraph
{
public:
	CParagraph(std::string const& text, CHistory & history);
	~CParagraph();

	std::string GetText()const override;
	void SetText(const std::string& text) override;
private:
	std::string m_text;
	CHistory & m_history;
};

