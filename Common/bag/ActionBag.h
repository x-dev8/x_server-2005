//
//#pragma once
//#include "GlobalDef.h"
//#include "..\ItemDetail.h"
//
//class CActionBag
//{
//public:
//	CActionBag( );
//	~CActionBag( );
//
//	//初始化
//	void CreateFromData( SCharAction *pBaseAction, 
//						 SCharAction *pCommunityAction,
//						 SCharAction *pSocialAction,
//						 int iBagSize );
//
//	//增加动作
//	bool AddAction( unsigned short ustActionID, short stIndex = -1 );
//
//	//移除动作
//	bool RemoveAction( unsigned short ustActionID );
//	bool RemoveAction( short stWhichActionBag, short stIndex );
//
//	//获取空位索引
//	int  FindNullActionOffSet( short stWhichActionBag );
//
//	//获取指定背包,索引的信息
//	bool GetAction( short stWhichActionBag, short stIndex, SCharAction *pAction );
//
//	//清空指定背包,索引的信息
//	bool ClearAction( short stWhichActionBag, short stIndex );
//
//	//获取指定背包,索引的状况...判断该位置是有
//	bool IsHaveAction( short stWhichActionBag, short stIndex );
//
//	int GetBaseActionNum( ) 
//	{
//		return m_iBaseActionCount;
//	}
//
//	int GetCommunityActionNum( ) 
//	{
//		return m_iCommunityActionCount;
//	} 
//
//	int GetSocialActionNum( )
//	{
//		return m_iSocialActionCount;
//	}
//
//private:
//	int  m_iBagSize;
//
//	int  m_iBaseActionCount;
//	int	 m_iCommunityActionCount;
//	int  m_iSocialActionCount;
//
//	SCharAction *m_pBaseAction;
//	SCharAction *m_pCommunityAction;
//	SCharAction *m_pSocialAction;
//};
