#include "ConstDocumentItem.h"

CConstDocumentItem::CConstDocumentItem(std::shared_ptr<const IImage> const & image)
	: m_image(image)
{
}

CConstDocumentItem::CConstDocumentItem(std::shared_ptr<const IParagraph> const & paragraph)
	: m_paragraph(paragraph)
{
}

std::shared_ptr<const IImage> CConstDocumentItem::GetImage() const
{
	return m_image;
}

std::shared_ptr<const IParagraph> CConstDocumentItem::GetParagraph() const
{
	return m_paragraph;
}
