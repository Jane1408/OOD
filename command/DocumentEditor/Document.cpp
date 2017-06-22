#include "stdafx.h"
#include "Paragraph.h"
#include "Image.h"
#include "Document.h"
#include "ChangeStringCommand.h"
#include "InsertParagraphCommand.h"
#include "InsertImageCommand.h"
#include "DeleteItemCommand.h"


CDocument::CDocument()
{
	m_path = boost::filesystem::temp_directory_path() / boost::lexical_cast<std::string>(boost::uuids::random_generator()());
	boost::filesystem::create_directory(m_path);
	boost::filesystem::create_directory(boost::filesystem::path(m_path) / "images");
}

CDocument::~CDocument()
{
	boost::filesystem::remove_all(m_path);
}

std::shared_ptr<IParagraph> CDocument::InsertParagraph(const std::string & text, optional<size_t> position)
{
	auto paragraph = std::make_shared<CParagraph>(text, m_history);
	size_t pos = position ? *position : m_items.size();
	if (pos > m_items.size())
		throw std::out_of_range("Position out of range");
	m_history.AddAndExecuteCommand(std::make_unique<CInsertParagraphCommand>(m_items, paragraph, pos));
	return paragraph;
}

std::shared_ptr<IImage> CDocument::InsertImage(const Path & path, int width, int height, optional<size_t> position)
{
	auto image = std::make_shared<CImage>(path, width, height, m_history);
	size_t pos = position ? *position : m_items.size();
	if (pos > m_items.size())
		throw std::out_of_range("Position out of range");
	if (width < 1 || width > 10000)
		throw std::invalid_argument("Invalid width of image");
	if (height < 1 || height > 10000)
		throw std::invalid_argument("Invalid height of image");
	auto extention = boost::filesystem::path(path).extension();
	std::string newName = boost::lexical_cast<std::string>(boost::uuids::random_generator()());
	auto newPath = m_path / "images" / (newName + extention.generic_string());
	boost::filesystem::copy_file(path, newPath, boost::filesystem::copy_option::overwrite_if_exists);
	auto image = std::make_shared<CImage>(newPath.generic_string(), width, height, m_history);
	m_history.AddAndExecuteCommand(std::make_unique<CInsertImageCommand>(m_items, image, pos));
	return image;
}

size_t CDocument::GetItemsCount() const
{
	return m_items.size();
}

CConstDocumentItem CDocument::GetItem(size_t index) const
{
	if (index >= m_items.size())
		throw std::out_of_range("Index out of range");
	return *next(m_items.begin(), index);
}

CDocumentItem CDocument::GetItem(size_t index)
{
	if (index >= m_items.size())
		throw std::out_of_range("Index out of range");
	return *next(m_items.begin(), index);
}

void CDocument::DeleteItem(size_t index)
{
	if (index >= m_items.size())
		throw std::out_of_range("Index out of range");
	m_history.AddAndExecuteCommand(std::make_unique<CDeleteItemCommand>(m_items, index));
}

void CDocument::SetTitle(const std::string & title)
{
	m_history.AddAndExecuteCommand(std::make_unique<CChangeStringCommand>(m_title, title));
}

std::string CDocument::GetTitle() const
{
	return m_title;
}

bool CDocument::CanUndo() const
{
	return m_history.CanUndo();
}

void CDocument::Undo()
{
	m_history.Undo();
}

bool CDocument::CanRedo() const
{
	return m_history.CanRedo();
}

void CDocument::Redo()
{
	m_history.Redo();
}

