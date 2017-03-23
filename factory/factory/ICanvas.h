#pragma once
class ICanvas
{
public:
	ICanvas() {};
	~ICanvas() {};

	virtual void SetColor(Color color) = 0;
	virtual void DrawLine(Vector2 from, Vector2 to) = 0;
	virtual void DrawEllipse(Vector2 center, double harizontalRadius, double verticalRadius)= 0;
};

