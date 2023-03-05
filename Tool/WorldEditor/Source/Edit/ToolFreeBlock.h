/*@Author: jiayi.*/
#pragma once

#include "BaseTool.h"

class CToolManager;

/// Block structures.
struct FreeBlock
{
	float m_fLength;			// Bottom border length.
	std::string m_strFilename;	// File name.
};

typedef std::map<std::string, FreeBlock> Blocks;
typedef Blocks::iterator BlocksIter;

/**
* @brief Put blocks on map automatically.
*/
class ToolFreeBlock :  public CBaseTool
{
// Enumerate.
public:
	enum EOperationStatus
	{
		EOS_NONE,
		EOS_READYBLOCK
	};
// Construction.
public:
	/// Constructor.
	ToolFreeBlock();
	
	/// Destructor.
	virtual ~ToolFreeBlock();

	/// Copy constructor.
	ToolFreeBlock( const ToolFreeBlock& kClass ){}

// Overload operator.
public:
	/// Assignment operator.
	const ToolFreeBlock& operator=( const ToolFreeBlock& kClass ){ return *this; }

// Override.
public:
	/// Get tool id.
	virtual ToolID GetToolId(){ return TOOL_FREEBLOCK; };

	/// Initialize.
	virtual bool Create( CToolManager* toolMgr );

	/// Mouse & Keyboard relative operations.
	virtual bool OnLMouseDown( UINT nFlags, CPoint point );
	virtual bool OnLMouseUp( UINT nFlags, CPoint point );
	virtual bool OnLMouseDblClk( UINT nFlags, CPoint point );
	virtual bool OnRMouseDown( UINT nFlags, CPoint point );
	virtual bool OnRMouseUp( UINT nFlags, CPoint point );
	virtual bool OnMouseMove( UINT nFlags, CPoint point );
	virtual bool OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	virtual bool OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );

	/// Render every frame.
	virtual void Render();

// Methods.
public:
	/// Enable free block edit.
	void EnableFreeBlock( bool bEnable ){ m_bEnable = bEnable; }
	bool EnableFreeBlock() const{ return m_bEnable; }

// Methods.
protected:
	/// Load blocks info.
	void LoadBlocksFromDisk();

	/// Set current operation status.
	void SetCurrentOperationStatus( ToolFreeBlock::EOperationStatus eStatus ){
		m_eStatus = eStatus;
	}

	/// Get current operation status.
	EOperationStatus GetCurrentOperationStatus() const{ 
		return m_eStatus;
	}

	/// Put blocks on terrain.
	void PutBlock( float fLength );

	/// Get length according to block file name.
	int GetBlockLengthByName( const std::string& strFilename ) const;

	/// Find a block with a length most close to the give length.
	BlocksIter FindBlockIndexByLength( float fLength );

	/// Get max block length.
	float GetMaxBlockLength() const{ return m_fMaxBlockLength; }

// Members.
protected:
	/// Enable.
	bool m_bEnable;

	/// Last point with the mouse click.
	Vector m_kLastPt;
	
	/// Current point with the mouse click.
	Vector m_kCurrentPt;

	/// Current status.
	EOperationStatus m_eStatus;

	/// Store blocks info.
	Blocks mBlocks;

	/// Max block length.
	float m_fMaxBlockLength;	
};