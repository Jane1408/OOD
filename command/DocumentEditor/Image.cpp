#include "Image.h"
#include "ResizeImageCommand.h"



CImage::CImage(Path const& path, unsigned width, unsigned height, CHistory & history)
	: m_path(path)
	, m_width(width)
	, m_height(height)
	, m_history(history)
{
}


CImage::~CImage()
{
}

Path CImage::GetPath() const
{
	return m_path;
}

unsigned CImage::GetWidth() const
{
	return m_width;
}

unsigned CImage::GetHeight() const
{
	return m_height;
}

void CImage::Resize(unsigned width, unsigned height)
{
	//m_history.AddAndExecuteCommand(std::make_unique<CResizeImageCommand>())
}

void CImage::SetSize(unsigned width, unsigned height)
{
	m_width = width;
	m_height = height;
}
