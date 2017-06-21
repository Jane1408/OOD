#pragma once
#include <memory>

class IParagraph;
class IImage;

/*
Неизменяемый элемент документа
*/
class CConstDocumentItem
{
public:
	CConstDocumentItem(std::shared_ptr<const IImage> const& image);
	CConstDocumentItem(std::shared_ptr<const IParagraph> const& paragraph);
	// Возвращает указатель на константное изображение, либо nullptr, если элемент не является изображением
	std::shared_ptr<const IImage> GetImage()const;
	// Возвращает указатель на константный параграф, либо nullptr, если элемент не является параграфом
	std::shared_ptr<const IParagraph> GetParagraph()const;
	virtual ~CConstDocumentItem() = default;
private:
	std::shared_ptr<const IImage> m_image = nullptr;
	std::shared_ptr<const IParagraph> m_paragraph = nullptr;
};

