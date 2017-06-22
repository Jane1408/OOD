#pragma once
#include <boost/filesystem.hpp>

using Path = boost::filesystem::path;
/*
�����������
*/
class IImage
{
public:
	// ���������� ���� ������������ �������� ���������
	virtual Path GetPath()const = 0;
	// ������ ����������� � ��������
	virtual unsigned GetWidth()const = 0;
	// ������ ����������� � ��������
	virtual unsigned GetHeight()const = 0;
	// �������� ������ �����������
	virtual void Resize(unsigned width, unsigned height) = 0;
	virtual void SetSize(unsigned width, unsigned height) = 0;
	virtual ~IImage() = default;
};