#pragma once

class CShape;

class CPictureDraft
{
public:
	CPictureDraft();
	~CPictureDraft();

	size_t GetShapeCount() const;
	std::shared_ptr<CShape> GetShape(size_t position) const;
	std::vector<std::shared_ptr<CShape>> GetShapesList();
	void AddShape(std::shared_ptr<CShape> const& shape);

private:
	std::vector<std::shared_ptr<CShape>> m_shapes;

};

