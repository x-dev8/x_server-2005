
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
	// �Ե�ǰ��������м���
	for( int i = 0; i < m_vectorBoneGroup.size(); i++ )
	{
		// �õ�������еĲ���
		int nDiff = GetDiff( pFace, &m_vectorBoneGroup[i] );
		// ��������С��˵�����ӵ�ƥ�䣬���ҿ������������Ĺ����б�
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
		// ��ƥ��Ĺ������м������Ĺ����б�
		m_vectorBoneGroup[nMinDiffGroupID].AddBone( pFace->vectorBoneID );
	}
	else
	{
		// �¼���һ��������
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
		// ���û���ҵ�
		if( pBoneGroup->Find( pFace->vectorBoneID[i] ) == -1 )
			nDiff++;
	}
	return nDiff;
	unguard;
}
BOOL CBoneCombination::GenBlocks( int nChunkCount, std::vector<Chunk>* pvectorChunk )
{
	guardfunc;
	// chunk�����������ú�
	pvectorChunk->reserve( nChunkCount );
	pvectorChunk->resize( nChunkCount );

	int nBoneGroupCount = m_vectorBoneGroup.size();
	// ��ÿһ������м���
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

