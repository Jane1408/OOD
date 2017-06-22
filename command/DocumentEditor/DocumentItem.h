#pragma once
#include <memory>
#include "ConstDocumentItem.h"

/*
Элемент документа. Позволяет получить доступ к изображению или параграфу
*/
class CDocumentItem :
	public CConstDocumentItem
{
public:
	CDocumentItem(std::shared_ptr<IImage> const& image);
	CDocumentItem(std::shared_ptr<IParagraph> const& paragraph);
	~CDocumentItem();

	// Возвращает указатель на изображение, либо nullptr, если элемент не является изображением
	std::shared_ptr<IImage> GetImage();
	// Возвращает указатель на параграф, либо nullptr, если элемент не является параграфом
	std::shared_ptr<IParagraph> GetParagraph();

private:
	std::shared_ptr<IImage> m_image;
	std::shared_ptr<IParagraph> m_paragraph;
};

