#ifndef _emitter_h
#define _emitter_h
//#include "particle.h"
class Emitter
{
public:
protected:
public:
	Emitter();
	virtual ~Emitter();
	static short* GetCWIndexBuffer();
	static short* GetCCWIndexBuffer();
	static LPDIRECT3DINDEXBUFFER9				GetD9IndexBuffer();
};



#endif