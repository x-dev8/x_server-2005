/*******************************************************************************
* Copyright ShenWang 2009 - All Rights Reserved
* 
* File: 	TileQuadTreeNode.cpp
* Create: 	03/03/2009
* Desc:		地表四叉树节点，记录BBox，子节点和叶子数据
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#include "MeTerrain/stdafx.h"
#include "MeTerrain/TileQuadTreeNode.h"
#include "MeTerrain/WorldChunk.h"
#include "FuncPerformanceLog.h"

TileQuadTreeNode::TileQuadTreeNode():
m_bLeaf(FALSE),
m_nDepth(0),
m_bHasBuiltBBox(FALSE)
{
	guardfunc;
	for( int i = 0; i < 4; i++ )
		m_pChildNode[i] = NULL;
	m_vctChunkNode.clear();
	unguard;

}
TileQuadTreeNode::~TileQuadTreeNode()
{
	guardfunc;
	for( int i = 0; i < 4; i++ )
	{
		if( m_pChildNode[i] )
		{
			delete m_pChildNode[i];
			m_pChildNode[i] = NULL;
		}
	}
	m_vctChunkNode.clear();
	unguard;

}
