#pragma once
#include <boost/filesystem.hpp>

using Path = boost::filesystem::path;
/*
Изображение
*/
class IImage
{
public:
	// Возвращает путь относительно каталога документа
	virtual Path GetPath()const = 0;
	// Ширина изображения в пикселях
	virtual unsigned GetWidth()const = 0;
	// Высота изображения в пикселях
	virtual unsigned GetHeight()const = 0;
	// Изменяет размер изображения
	virtual void Resize(unsigned width, unsigned height) = 0;
	virtual void SetSize(unsigned width, unsigned height) = 0;
	virtual ~IImage() = default;
};