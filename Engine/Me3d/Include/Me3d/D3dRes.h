#pragma once

#include "Me3d.h"
class FD3DVertexStream;
class FD3DIndexBuffer;

class FRenderResource;

//
//	FD3DResource
//
class FD3DResource
{
public:

	IRenderer*		RI;
	QWORD				CacheId;
	INT					CachedRevision,
						HashIndex;

	FD3DResource*		NextResource;
	FD3DResource*		HashNext;

	INT					LastFrameUsed;

	// Constructor/destructor.
	FD3DResource(IRenderer* InRenDev,QWORD InCacheId);
	virtual ~FD3DResource();

	// GetTexture
	//virtual class FD3DTexture* GetTexture() { return NULL; }

	// GetVertexStream
	virtual class FD3DVertexStream* GetVertexStream() { return NULL; }

	// GetIndexBuffer
	virtual class FD3DIndexBuffer* GetIndexBuffer() { return NULL; }

	// CalculateFootprint
	virtual INT CalculateFootprint() { return 0; }
};



//
//	FD3DVertexStream
//
class FD3DVertexStream : public FD3DResource
{
public:

	IDirect3DVertexBuffer9*	Direct3DVertexBuffer8;
	INT						CachedSize;

	// Constructor/destructor.
	FD3DVertexStream(IRenderer* InRenDev,QWORD InCacheId);
	virtual ~FD3DVertexStream();

	// GetVertexStream
	virtual FD3DVertexStream* GetVertexStream() { return this; }

	// CalculateFootprint
	virtual INT CalculateFootprint();

	// Cache - Ensure that the cached vertex stream is up to date.
	void Cache(FVertexStream* SourceStream);
};


//
//	FD3DDynamicVertexStream
//
class FD3DDynamicVertexStream : public FD3DVertexStream, public MeCommonAllocObj<FD3DDynamicVertexStream>
{
public:

	INT	Tail;

	// Constructor/destructor.
	FD3DDynamicVertexStream(IRenderer* InRenDev);

	// Reallocate - Reallocates the dynamic vertex buffer.
	void Reallocate(INT NewSize);

	// AddVertices - Adds the vertices from the given stream to the end of the stream.  
	// Returns the index of the first vertex in the stream.
	INT AddVertices(FVertexStream* Vertices);
};


//
//	FD3DIndexBuffer
//
class FD3DIndexBuffer : public FD3DResource
{
public:

	IDirect3DIndexBuffer9*	Direct3DIndexBuffer8;
	INT						CachedSize;

	// Constructor/destructor.
	FD3DIndexBuffer(IRenderer* InRenDev,QWORD InCacheId);
	~FD3DIndexBuffer();

	// GetIndexBuffer
	virtual FD3DIndexBuffer* GetIndexBuffer() { return this; }

	// CalculateFootprint
	virtual INT CalculateFootprint();

	// Cache - Ensure the cached index buffer is up to date.
	void Cache(FIndexBuffer* SourceIndexBuffer);
};

//
//	FD3DDynamicIndexBuffer
//
class FD3DDynamicIndexBuffer : public FD3DIndexBuffer, public MeCommonAllocObj<FD3DDynamicIndexBuffer>
{
public:

	INT	Tail;
	INT IndexSize;

	// Constructor/destructor.
	FD3DDynamicIndexBuffer(IRenderer* InRenDev, INT InIndexSize);

	// Reallocate - Reallocates the dynamic index buffer.
	void Reallocate(INT NewSize);

	// AddIndices - Adds the indices from the given buffer to the end of this buffer.  Returns the old tail.
	INT AddIndices(FIndexBuffer* Indices);
};
