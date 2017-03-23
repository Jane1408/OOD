#pragma once
#include "stdafx.h"
#include "PictureDraft.h"

class IDesigner
{
public:
	IDesigner() {};
	~IDesigner() {};

	virtual CPictureDraft CreateDraft(std::istream & strm) = 0;
};

