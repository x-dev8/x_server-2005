#pragma once
#include "Dxsdk/d3d9.h"
#pragma warning(disable : 4995)
#include <string>
#pragma warning(default : 4995)
#include "Billboard3D.h"
#include "Cfg.h"
#include "RTTFont.h"

class Font3D : public RTTFont
{
public:
	Font3D()
    {
		eFontType_ = ERTT_3D;
    }

    virtual ~Font3D()
    {
        //Destroy();
    }

    virtual void Destroy();

protected:
	virtual void CreateVertex() ;
};
