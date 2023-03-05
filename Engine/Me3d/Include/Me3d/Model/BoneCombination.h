#pragma once

#include "MeRTLibs.h"

/*
	一个Chunk被分为若干渲染块
	一个面的3个顶点，其所依赖的骨骼必定处于同一个骨骼组
	因为我们是一面为单位建立骨骼组

	要注意的是，
	一个顶点有可能会从属于多个骨骼组，
	虽然在多个骨骼组中，对应的骨骼是一样的，
	但是对应的骨骼在骨骼组中的位置会有不同，
	所以，需要保留每个骨骼的映射

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
	// block为一个最小的渲染调用
	struct Block 
	{
		int nBoneGroupID;
		std::vector<int> vectorFaceID;
	};
	// 对应模型的chunk，一个chunk可以产生多个block
	// 这是因为chunk中的面受到不止一个骨骼组的影响，
	struct Chunk
	{
		int nTotalFaceCount;
		std::vector<Block> vectorBlock;
		Chunk():
		nTotalFaceCount(0)
		{}
		int FindBlockByBoneGroupID( int nBoneGroupID );
	};
	// 骨骼组，一个骨骼id的列表，最多为比如16个骨骼一组，
	// 这个要根据shader的寄存器数量决定，
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
	// 得到差异
	int		GetDiff( Face* pFace, BoneGroup* pBoneGroup );

	BOOL	GenBlocks( int nChunkCount, std::vector<Chunk>* pvectorChunk );
public:
	int		m_nMaxBoneInGroup;
	std::vector<Face> m_vectorFace;
	std::vector<BoneGroup> m_vectorBoneGroup;
	std::vector<Chunk> m_vectorChunk;
};
