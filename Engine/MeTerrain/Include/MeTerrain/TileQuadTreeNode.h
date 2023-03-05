/*******************************************************************************
* Copyright ShenWang 2009 - All Rights Reserved
* 
* File: 	TileQuadTreeNode.h
* Create: 	03/03/2009
* Desc:		�ر��Ĳ����ڵ㣬��¼BBox���ӽڵ��Ҷ�����ݣ�Ҷ�Ӿ�ȷ��һ��chunk
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef __TILEQUADTREENODE_H__
#define __TILEQUADTREENODE_H__

class CWorldChunk;
class TileQuadTreeNode : public MeCommonAllocObj<TileQuadTreeNode>
{
public:
	struct ChunkNode
	{
		CWorldChunk*	chunk;
		SBBox			sbbox;
		D3DXVECTOR3		vMax;
		D3DXVECTOR3		vMin;
		int				Id;
	};
	TileQuadTreeNode();
	~TileQuadTreeNode();

	BOOL	IsLeaf(){ return m_bLeaf; }
public:
	BOOL m_bLeaf;
	std::vector<ChunkNode> m_vctChunkNode;
	TileQuadTreeNode* m_pChildNode[4];
	BOOL		m_bHasBuiltBBox;
	SBBox		m_sbbox;
	D3DXVECTOR3	m_vMin;
	D3DXVECTOR3	m_vMax;
	int m_nDepth;
	BOOL m_bVisible;
};
#endif