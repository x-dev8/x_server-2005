//
//#pragma once
//#include "GlobalDef.h"
//#include "..\ItemDetail.h"
//
//class CSkillBag;
//class CSymbolStoneBag
//{
//public:
//	CSymbolStoneBag( );
//	~CSymbolStoneBag( );
//
//	//初始化
//	void SetSkillBagPoint( CSkillBag *pSkillBag );
//	void CreateFromData( SCharSymbolStone *pStoneData, int iBagSize );
//
//	//放置符石(可以让程序自动指定位置,玩家也可以指定位置)
//	bool AddStone( unsigned short ustStoneID, short stIndex=-1 );
//	//移除符石(只能传入索引,因为符石有可能一样)
//	bool RemoveStone( short stStoneIndex );
//	//找一个空的位置
//	int  FindNullStoneOffSet( );
//
//	//获取指定索引的符石信息
//	bool GetStone( short stIndex, SCharSymbolStone *pStone );
//	//获取指定索引的状况...判断该位置是有
//	bool IsHaveStone( short stIndex );
//	//清空指定索引的符石
//	bool ClearStone( short stIndex );
//
//	//连接到技能上
//	void AttachToSkill( short stStoneIndex, short stSkillIndex );	
//	//从技能脱离
//	void DetachFromSkill( short stStoneIndex );						
//
//	//有效符石的个数
//	int GetStoneNum( )
//	{
//		return m_iBagSize;
//	}
//
//	//获取指定索引符石的ID
//	unsigned short GetStoneIDByIndex( int iIndex )
//	{
//		return m_pStoneData[iIndex].ustStoneID;
//	}
//
//private:
//	//背包的最大数目
//	int	 m_iBagSize;
//
//	//符石的数据指针
//	SCharSymbolStone *m_pStoneData;
//	
//	//技能背包的指针(获取技能类的数据)
//	CSkillBag *m_pSkillBag;
//};
