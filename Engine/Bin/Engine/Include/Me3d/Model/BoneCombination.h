#pragma once

#include "MeRTLibs.h"

/*
	һ��Chunk����Ϊ������Ⱦ��
	һ�����3�����㣬���������Ĺ����ض�����ͬһ��������
	��Ϊ������һ��Ϊ��λ����������

	Ҫע����ǣ�
	һ�������п��ܻ�����ڶ�������飬
	��Ȼ�ڶ���������У���Ӧ�Ĺ�����һ���ģ�
	���Ƕ�Ӧ�Ĺ����ڹ������е�λ�û��в�ͬ��
	���ԣ���Ҫ����ÿ��������ӳ��

*/
#define MAX_BONE_IN_GROUP 16
class CBoneCombination
{
public:
	struct Face
	{
		int nChunkID;
		int nBoneGroupID;
		int nVertexID[3];
		std::vector<int> vectorBoneID;
		BOOL AddBone( int nBoneID );
		Face()
		{
			nBoneGroupID = -1;
		}
	};
	// blockΪһ����С����Ⱦ����
	struct Block 
	{
		int nBoneGroupID;
		std::vector<int> vectorFaceID;
	};
	// ��Ӧģ�͵�chunk��һ��chunk���Բ������block
	// ������Ϊchunk�е����ܵ���ֹһ���������Ӱ�죬
	struct Chunk
	{
		int nTotalFaceCount;
		std::vector<Block> vectorBlock;
		Chunk():
		nTotalFaceCount(0)
		{}
		int FindBlockByBoneGroupID( int nBoneGroupID );
	};
	// �����飬һ������id���б����Ϊ����16������һ�飬
	// ���Ҫ����shader�ļĴ�������������
	struct BoneGroup
	{
		std::vector<int> vectorBoneID;
		int Find( int nID );
		BOOL AddBone( std::vector<int>& ids );
	};
	
public:
	CBoneCombination(void);
	~CBoneCombination(void);

	BOOL	AddFace( Face* pFace );
	// �õ�����
	int		GetDiff( Face* pFace, BoneGroup* pBoneGroup );

	BOOL	GenBlocks( int nChunkCount, std::vector<Chunk>* pvectorChunk );
public:
	int		m_nMaxBoneInGroup;
	std::vector<Face> m_vectorFace;
	std::vector<BoneGroup> m_vectorBoneGroup;
	std::vector<Chunk> m_vectorChunk;
};
