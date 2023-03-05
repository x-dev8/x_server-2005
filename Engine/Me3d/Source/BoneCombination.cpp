
#include "Me3d/BoneCombination.h"
#include "FuncPerformanceLog.h"
#include <windows.h>
#include <assert.h>

int CBoneCombination::Chunk::FindBlockByBoneGroupID( int nBoneGroupID )
{
	guardfunc;
	for( int i = 0; i < vectorBlock.size(); i++ )
	{
		if( vectorBlock[i].nBoneGroupID == nBoneGroupID )
			return i;
	}
	return -1;
	unguard;
}

int CBoneCombination::BoneGroup::Find( int nID )
{
	guardfunc;
	for( int i = 0; i < vectorBoneID.size(); i++ )
	{
		if( nID == vectorBoneID[i] )
			return i;
	}
	return -1;
	unguard;
}
BOOL CBoneCombination::BoneGroup::AddBone( std::vector<int>& ids )
{
	guardfunc;
	for( int i = 0; i < ids.size(); i++ )
	{
		if( Find( ids[i] ) == -1 )
			vectorBoneID.push_back( ids[i] );
	}
	return TRUE;
	unguard;
}
BOOL CBoneCombination::Face::AddBone( int nBoneID )
{
	guardfunc;
	for( int i = 0; i < vectorBoneID.size(); i++ )
	{
		if( vectorBoneID[i] == nBoneID )
			return TRUE;
	}
	vectorBoneID.push_back( nBoneID );
	return TRUE;
	unguard;;
}
CBoneCombination::CBoneCombination(void):
m_nMaxBoneInGroup(MAX_BONE_IN_GROUP)
{
	guardfunc;
	unguard;
}

CBoneCombination::~CBoneCombination(void)
{
	guardfunc;
	unguard;
}

BOOL CBoneCombination::AddFace( Face* pFace )
{
	guardfunc;
	int nMinDiffGroupID = -1;
	int nMinDiff = 10000;
	// 对当前骨骼组进行计算
	for( int i = 0; i < m_vectorBoneGroup.size(); i++ )
	{
		// 得到这个面中的差异
		int nDiff = GetDiff( pFace, &m_vectorBoneGroup[i] );
		// 如果差异更小，说明更加的匹配，而且可以容纳新增的骨骼列表，
		if( nDiff < nMinDiff &&
			m_vectorBoneGroup[i].vectorBoneID.size()+nDiff <= m_nMaxBoneInGroup )
		{
			nMinDiff = nDiff;
			nMinDiffGroupID = i;
		}
	}
	int nFaceID = m_vectorFace.size();
	if( nMinDiffGroupID != -1 )
	{
		pFace->nBoneGroupID = nMinDiffGroupID;
		// 最匹配的骨骼组中加入该面的骨骼列表
		m_vectorBoneGroup[nMinDiffGroupID].AddBone( pFace->vectorBoneID );
	}
	else
	{
		// 新加入一个骨骼组
		pFace->nBoneGroupID = m_vectorBoneGroup.size();
		
		BoneGroup bg;
		bg.AddBone( pFace->vectorBoneID );
		m_vectorBoneGroup.push_back( bg );
		
	}
	
	m_vectorFace.push_back( *pFace );

	return TRUE;
	unguard;
}
int CBoneCombination::GetDiff( Face* pFace, BoneGroup* pBoneGroup )
{
	guardfunc;
	int nDiff = 0;
	for( int i = 0; i < pFace->vectorBoneID.size(); i++ )
	{
		// 如果没有找到
		if( pBoneGroup->Find( pFace->vectorBoneID[i] ) == -1 )
			nDiff++;
	}
	return nDiff;
	unguard;
}
BOOL CBoneCombination::GenBlocks( int nChunkCount, std::vector<Chunk>* pvectorChunk )
{
	guardfunc;
	// chunk的数量先设置好
	pvectorChunk->reserve( nChunkCount );
	pvectorChunk->resize( nChunkCount );

	int nBoneGroupCount = m_vectorBoneGroup.size();
	// 对每一个面进行计算
	for( int nFace = 0; nFace < m_vectorFace.size(); nFace++ )
	{
		Face* pFace = &m_vectorFace[nFace];
		if( pFace->nChunkID < 0 ||
			pFace->nChunkID >= pvectorChunk->size() )
		{
			assert( false );
			continue;
		}
		Chunk* pChunk = &(*pvectorChunk)[pFace->nChunkID];
		int nBlockID = pChunk->FindBlockByBoneGroupID( pFace->nBoneGroupID );
		if( nBlockID != -1 )
			pChunk->vectorBlock[nBlockID].vectorFaceID.push_back( nFace );
		else
		{
			Block block;
			block.nBoneGroupID = pFace->nBoneGroupID;
			block.vectorFaceID.push_back( nFace );
			pChunk->vectorBlock.push_back( block );
		}
		pChunk->nTotalFaceCount++;
	}

	return TRUE;
	unguard;
}

