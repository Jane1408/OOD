#pragma once
#include <memory>
#include "ConstDocumentItem.h"

/*
������� ���������. ��������� �������� ������ � ����������� ��� ���������
*/
class CDocumentItem :
	public CConstDocumentItem
{
public:
	CDocumentItem(std::shared_ptr<IImage> const& image);
	CDocumentItem(std::shared_ptr<IParagraph> const& paragraph);
	~CDocumentItem();

	// ���������� ��������� �� �����������, ���� nullptr, ���� ������� �� �������� ������������
	std::shared_ptr<IImage> GetImage();
	// ���������� ��������� �� ��������, ���� nullptr, ���� ������� �� �������� ����������
	std::shared_ptr<IParagraph> GetParagraph();

private:
	std::shared_ptr<IImage> m_image;
	std::shared_ptr<IParagraph> m_paragraph;
};

