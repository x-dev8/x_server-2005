#include "Me3d/Me3d.h"
#include "Me3d/Global.h"
#include "Me3d/D3DRes.h"
#include "FuncPerformanceLog.h"
#include "Me3d/Engine/RendererDx.h"
#define RESOURCE_POOL D3DPOOL_MANAGED
//
//	GetResourceHashIndex
//
INT GetResourceHashIndex(QWORD CacheId)
{
	return ((DWORD) CacheId & 0xfff) ^ (((DWORD) CacheId & 0xff00) >> 4) + (((DWORD) CacheId & 0xf0000) >> 16);
}


FD3DResource::FD3DResource(IRenderer* InRenDev,QWORD InCacheId)
{
	guardfunc;
	RI = InRenDev;
	CacheId = InCacheId;
	CachedRevision = 0;

	RI = InRenDev;
	CacheId = InCacheId;
	CachedRevision = 0;

	RendererDx *pDx = dynamic_cast<RendererDx*>(InRenDev);

	// Add this resource to the device resource list.
	NextResource = pDx->ResourceList;
	pDx->ResourceList = this;

	// Calculate a hash index.
	HashIndex = GetResourceHashIndex(CacheId);

	// Add this resource to the device resource hash.
	HashNext = pDx->ResourceHash[HashIndex];
	pDx->ResourceHash[HashIndex] = this;

	LastFrameUsed = 0;

	unguard;
}

FD3DResource::~FD3DResource()
{
	guardfunc;

	RendererDx *pDx = dynamic_cast<RendererDx*>(RI);
	FD3DResource*	ResourcePtr;

	// Remove this resource from the device resource list.
	if(pDx->ResourceList != this)
	{
		ResourcePtr = pDx->ResourceList;

		while(ResourcePtr && ResourcePtr->NextResource != this)
			ResourcePtr = ResourcePtr->NextResource;

		if(ResourcePtr)
			ResourcePtr->NextResource = NextResource;

		NextResource = NULL;
	}
	else
	{
		pDx->ResourceList = NextResource;
		NextResource = NULL;
	}

	// Remove this resource from the device resource hash.
	if(pDx->ResourceHash[HashIndex] != this)
	{
		ResourcePtr = pDx->ResourceHash[HashIndex];

		while(ResourcePtr && ResourcePtr->HashNext != this)
			ResourcePtr = ResourcePtr->HashNext;

		if(ResourcePtr)
			ResourcePtr->HashNext = HashNext;

		HashNext = NULL;
	}
	else
	{
		pDx->ResourceHash[HashIndex] = HashNext;
		HashNext = NULL;
	}
	unguard;
}

//
//	FD3DVertexStream::FD3DVertexStream
//
FD3DVertexStream::FD3DVertexStream(IRenderer* InRenDev,QWORD InCacheId) : FD3DResource(InRenDev,InCacheId)
{
	Direct3DVertexBuffer8 = NULL;
}

//
//	FD3DVertexStream::~FD3DVertexStream
//
FD3DVertexStream::~FD3DVertexStream()
{
	if(Direct3DVertexBuffer8)
		Direct3DVertexBuffer8->Release();
}

//
//  FD3DVertexStream::CalculateFootprint
//
INT FD3DVertexStream::CalculateFootprint()
{
	return CachedSize;
}


//
//	FD3DVertexStream::Cache
//
void FD3DVertexStream::Cache(FVertexStream* SourceStream)
{
	guard(FD3DVertexStream::Cache);

	INT		Size = SourceStream->GetSize();
	HRESULT	Result;

	if(!Direct3DVertexBuffer8 || CachedSize != Size)
	{
		// Release the existing vertex buffer.
		if(Direct3DVertexBuffer8)
			Direct3DVertexBuffer8->Release();

		// Create a MeNew Direct3D vertex buffer.
		Result = RI->CreateVertexBuffer(Size,D3DUSAGE_WRITEONLY,0,RESOURCE_POOL,(VOID**)&Direct3DVertexBuffer8);

		if( FAILED(Result) )
		{
			OutputDebugString( "CreateVertexBuffer failed" );
		//	appErrorf(TEXT("CreateVertexBuffer failed(%s)."),*D3DError(Result));
		}
	}

	// Lock the vertex buffer.
	BYTE*	VertexBufferContents;

	Result = Direct3DVertexBuffer8->Lock(0,Size,(void**)&VertexBufferContents,0);

	if( FAILED(Result) )
	{
		OutputDebugString( "IDirect3DVertexBuffer9 Lock failed" );
	}

	// Copy the stream contents into the vertex buffer.
	SourceStream->GetStreamData(VertexBufferContents);

	// Unlock the vertex buffer.
	Result = Direct3DVertexBuffer8->Unlock();

	if( FAILED(Result) )
	{
		OutputDebugString( "IDirect3DVertexBuffer9::Unlock failed" );
	}

	// Update the cached info.
	CachedRevision = SourceStream->GetRevision();
	CachedSize = Size;

	unguard;
}

//
//	FD3DDynamicVertexStream::FD3DDynamicVertexStream
//
#define INITIAL_DYNAMIC_VERTEXBUFFER_SIZE	65536	// Initial size of dynamic vertex buffers, in bytes.

FD3DDynamicVertexStream::FD3DDynamicVertexStream(IRenderer* InRenDev)
: FD3DVertexStream(InRenDev,NULL)
{
	guard(FD3DDynamicVertexStream::FD3DDynamicVertexStream);

	Reallocate(INITIAL_DYNAMIC_VERTEXBUFFER_SIZE);

	unguard;
}


//
//	FD3DDynamicVertexStream::Reallocate
//
void FD3DDynamicVertexStream::Reallocate(INT NewSize)
{
	guard(FD3DDynamicVertexStream::Reallocate);

	// Release the old vertex buffer.
	if(Direct3DVertexBuffer8)
	{
		// Make sure it's not currently bound via SetStreamSource.
		RendererDx* RenDev = (RendererDx*)RI;
		//RenDev->DeferredState.UnSetVertexBuffer( Direct3DVertexBuffer8 );
		Direct3DVertexBuffer8->Release();
		Direct3DVertexBuffer8 = NULL;
	}

	// Create a dynamic vertex buffer to hold the vertices.
	CachedSize = NewSize;
	Tail = 0;

	
	HRESULT	Result = RI->CreateVertexBuffer(CachedSize,D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,0,RESOURCE_POOL,(VOID**)&Direct3DVertexBuffer8);

	unguard;
}


//
//	FD3DDynamicVertexStream::AddVertices
//
INT FD3DDynamicVertexStream::AddVertices(FVertexStream* Stream)
{
	guard(FD3DDynamicVertexStream::AddVertices);

	INT	Size = Stream->GetSize(),
		Stride = Stream->GetStride();

	// If the dynamic vertex buffer isn't big enough to contain all the vertices, resize it.
	QWORD	LockFlags = D3DLOCK_NOOVERWRITE;

	if(Size > CachedSize)
	{
		Reallocate(Size);
		LockFlags = D3DLOCK_DISCARD;
	}

	// If the dynamic vertex buffer will overflow with the additional vertices, flush it.
	RendererDx *RenDev = (RendererDx*)RI;
	if(Tail + Stride + Size > CachedSize 
		|| ((QWORD) (Tail + Stride + Size) / Stride) 
			> RenDev->DeviceCaps8.MaxVertexIndex)
	{
		Tail = 0;
		LockFlags = D3DLOCK_DISCARD;
	}

	INT	VertexBufferOffset = ((Tail + Stride - 1) / Stride) * Stride;

	// Lock the dynamic vertex buffer.
	BYTE*	VertexBufferContents = NULL;

	HRESULT	Result = Direct3DVertexBuffer8->Lock(VertexBufferOffset,Size,(void**)&VertexBufferContents,LockFlags);
	
	Stream->GetStreamData(VertexBufferContents);

	// Unlock the dynamic vertex buffer.
	Result = Direct3DVertexBuffer8->Unlock();

	// Update the tail pointer.
	Tail = VertexBufferOffset + Size;

	return VertexBufferOffset / Stride;

	unguard;
}


//
//	FD3DIndexBuffer::FD3DIndexBuffer
//
FD3DIndexBuffer::FD3DIndexBuffer(IRenderer* InRenDev,QWORD InCacheId) : FD3DResource(InRenDev,InCacheId)
{
	Direct3DIndexBuffer8 = NULL;
}

//
//	FD3DIndexBuffer::~FD3DIndexBuffer
//
FD3DIndexBuffer::~FD3DIndexBuffer()
{
	if(Direct3DIndexBuffer8)
		Direct3DIndexBuffer8->Release();
}

//
//  FD3DIndexBuffer::CalculateFootprint
//
INT FD3DIndexBuffer::CalculateFootprint()
{
	return CachedSize;
}

//
//	FD3DIndexBuffer::Cache
//
void FD3DIndexBuffer::Cache(FIndexBuffer* SourceIndexBuffer)
{
	guard(FD3DIndexBuffer::Cache);

	INT		Size = MAX(2,SourceIndexBuffer->GetSize());
	HRESULT	Result;

	if(!Direct3DIndexBuffer8 || CachedSize != Size)
	{
		// Release the existing index buffer.
		if(Direct3DIndexBuffer8)
			Direct3DIndexBuffer8->Release();

		D3DFORMAT IndexFormat;
		if( SourceIndexBuffer->GetIndexSize() == sizeof(DWORD) )
			IndexFormat = D3DFMT_INDEX32;
		else
			IndexFormat = D3DFMT_INDEX16;

		// Create a MeNew index buffer.
		Result = RI->CreateIndexBuffer(Size,D3DUSAGE_WRITEONLY,IndexFormat,RESOURCE_POOL,(VOID**)&Direct3DIndexBuffer8);

		if( FAILED(Result) )
		{
		//	appErrorf(TEXT("CreateIndexBuffer failed(%s)."),*D3DError(Result));
			OutputDebugString( "CreateIndexBuffer failed" );
		}
	}

	if(CachedRevision != SourceIndexBuffer->GetRevision())
	{
		// Lock the index buffer.
		BYTE*	IndexBufferContents = NULL;

		Result = Direct3DIndexBuffer8->Lock(0,Size,(void**)&IndexBufferContents,0);

		if( FAILED(Result) )
		{
			OutputDebugString( "IDirect3DIndexBuffer9::Lock failed" );
		}

		// Fill the index buffer.
		SourceIndexBuffer->GetContents(IndexBufferContents);

		// Unlock the index buffer.
		Result = Direct3DIndexBuffer8->Unlock();

		if( FAILED(Result) )
		{
			OutputDebugString( "IDirect3DIndexBuffer9::Unlock failed" );
		}
	}

	// Update cached info.
	CachedRevision = SourceIndexBuffer->GetRevision();
	CachedSize = Size;

	unguard;
}

//
//	FD3DDynamicIndexBuffer::FD3DDynamicIndexBuffer
//
#define INITIAL_DYNAMIC_INDEXBUFFER_SIZE	16384	// Initial size of dynamic index buffers, in bytes.

FD3DDynamicIndexBuffer::FD3DDynamicIndexBuffer(IRenderer* InRenDev, INT InIndexSize) : FD3DIndexBuffer(InRenDev,NULL), IndexSize(InIndexSize)
{
	guard(FD3DDynamicIndexBuffer::FD3DDynamicIndexBuffer);

	Reallocate(INITIAL_DYNAMIC_INDEXBUFFER_SIZE);

	unguard;
}

//
//	FD3DDynamicIndexBuffer::Reallocate
//
void FD3DDynamicIndexBuffer::Reallocate(INT NewSize)
{
	guard(FD3DDynamicIndexBuffer::Reallocate);

	// Release the old index buffer.
	// NOTE: Unsure of this, but I imagine the old index buffer will actually
	// stick around until all rendering calls using it are retired.
	//!!vogel: see comment in VertexBuffer::Reallocate
	if(Direct3DIndexBuffer8)
	{
		Direct3DIndexBuffer8->Release();
		Direct3DIndexBuffer8 = NULL;
	}

	// Create a dynamic vertex buffer to hold the vertices.
	CachedSize = NewSize;
	Tail = 0;

	D3DFORMAT IndexFormat;
	if( IndexSize == sizeof(DWORD) )
		IndexFormat = D3DFMT_INDEX32;
	else
		IndexFormat = D3DFMT_INDEX16;


	HRESULT	Result = RI->CreateIndexBuffer(CachedSize,D3DUSAGE_DYNAMIC | D3DUSAGE_WRITEONLY,IndexFormat,D3DPOOL_MANAGED,(VOID**)&Direct3DIndexBuffer8);

	if( FAILED(Result) )
	{
		OutputDebugString(("CreateIndexBuffer failed."));
	}

	unguard;
}

//
//	FD3DDynamicIndexBuffer::AddIndices
//
INT FD3DDynamicIndexBuffer::AddIndices(FIndexBuffer* Indices)
{
	guard(FD3DDynamicIndexBuffer::AddIndices);

	INT	Size = Indices->GetSize(),
		Stride = Indices->GetIndexSize();

	// If the dynamic index buffer isn't big enough to contain all the indices, resize it.
	DWORD	LockFlags = D3DLOCK_NOOVERWRITE;

	if(Size > CachedSize)
	{
		Reallocate(Size);
		LockFlags = D3DLOCK_DISCARD;
	}

	// If the dynamic index buffer will overflow with the additional indices, flush it.
	if(Tail + Size > CachedSize)
	{
		Tail = 0;

		LockFlags = D3DLOCK_DISCARD;
	}

	// Determine the offset in the index buffer to allocate the indices at.
	INT	IndexBufferOffset = Tail;

	// Lock the dynamic index buffer.
	BYTE*	IndexBufferContents = NULL;

	HRESULT	Result = Direct3DIndexBuffer8->Lock(IndexBufferOffset,Size,(void**)&IndexBufferContents,LockFlags);

	if( FAILED(Result) )
	{
		OutputDebugString( "IDirect3DIndexBuffer9::Lock failed" );
	}

	// Copy the indices into the index buffer.
	Indices->GetContents(IndexBufferContents);

	// Unlock the dynamic index buffer.
	Result = Direct3DIndexBuffer8->Unlock();

	if( FAILED(Result) )
	{
		OutputDebugString( "IDirect3DIndexBuffer9::Unlock failed" );
	}

	// Update the tail pointer.
	Tail = IndexBufferOffset + Size;

	return IndexBufferOffset / Stride;

	unguard;
}
