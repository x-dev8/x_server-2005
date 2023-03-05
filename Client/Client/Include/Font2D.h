#pragma once
#include "RTTFont.h"

class Font2D : public RTTFont
{
public:
	Font2D()
	{
		eFontType_ = ERTT_2D;
	}

	virtual ~Font2D()
	{}

	virtual void Destroy();

protected:
	virtual void CreateVertex();
};
