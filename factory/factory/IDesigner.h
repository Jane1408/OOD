#pragma once
#include "stdafx.h"
#include "PictureDraft.h"

class IDesigner
{
public:
	IDesigner() {};
	virtual ~IDesigner() = default;

	virtual CPictureDraft CreateDraft(std::istream & strm) = 0;
};

