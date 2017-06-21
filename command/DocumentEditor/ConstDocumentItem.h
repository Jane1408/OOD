#pragma once
#include <memory>

class IParagraph;
class IImage;

/*
������������ ������� ���������
*/
class CConstDocumentItem
{
public:
	CConstDocumentItem(std::shared_ptr<const IImage> const& image);
	CConstDocumentItem(std::shared_ptr<const IParagraph> const& paragraph);
	// ���������� ��������� �� ����������� �����������, ���� nullptr, ���� ������� �� �������� ������������
	std::shared_ptr<const IImage> GetImage()const;
	// ���������� ��������� �� ����������� ��������, ���� nullptr, ���� ������� �� �������� ����������
	std::shared_ptr<const IParagraph> GetParagraph()const;
	virtual ~CConstDocumentItem() = default;
private:
	std::shared_ptr<const IImage> m_image = nullptr;
	std::shared_ptr<const IParagraph> m_paragraph = nullptr;
};

