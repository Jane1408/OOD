#include "DocumentItem.h"



CDocumentItem::CDocumentItem(std::shared_ptr<IImage> const& image)
	: CConstDocumentItem(image)
	, m_image(image)
{
}

CDocumentItem::CDocumentItem(std::shared_ptr<IParagraph> const & paragraph)
	: CConstDocumentItem(paragraph)
	, m_paragraph(paragraph)
{
}

CDocumentItem::~CDocumentItem()
{
}

std::shared_ptr<IImage> CDocumentItem::GetImage()
{
	return m_image;
}

std::shared_ptr<IParagraph> CDocumentItem::GetParagraph()
{
	return m_paragraph;
}
