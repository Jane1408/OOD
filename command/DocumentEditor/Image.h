#pragma once
#include "IImage.h"
#include "History.h"


class CImage 
	: public IImage
{
public:
	CImage(Path const& path, unsigned width, unsigned height, CHistory & history);
	~CImage();
	Path GetPath()const override;
	unsigned GetWidth()const override;
	unsigned GetHeight()const override;
	void Resize(unsigned width, unsigned height) override;
	void SetSize(unsigned width, unsigned height) override;
private:
	Path m_path;
	unsigned m_width;
	unsigned m_height;
	CHistory & m_history;
};

