//
//#include "actionbag.h"
//#include "..\..\common\ItemDetail.h"
//
//extern CItemDetail theItemDetail;
//
//CActionBag::CActionBag( )
//{
//	m_iBagSize = 0;
//
//	m_iBaseActionCount = 0;
//	m_iCommunityActionCount = 0;
//	m_iSocialActionCount = 0;
//
//	m_pBaseAction = NULL;
//	m_pCommunityAction = NULL;
//	m_pSocialAction = NULL;
//}
//
//CActionBag::~CActionBag( )
//{
//
//}
//
//void CActionBag::CreateFromData( SCharAction *pBaseAction, 
//								 SCharAction *pCommunityAction,
//								 SCharAction *pSocialAction,
//								 int iBagSize )
//{
//	m_iBagSize = iBagSize;
//
//	m_iBaseActionCount		= 0;
//	m_iCommunityActionCount = 0;
//	m_iSocialActionCount	= 0;
//
//	m_pBaseAction			= pBaseAction;
//	m_pCommunityAction		= pCommunityAction;
//	m_pSocialAction			= pSocialAction;
//
//	for( int i=0; i<m_iBagSize; i++ )
//	{
//		if(pBaseAction[ i ].ustActionID!=ErrorUnsignedShortID)
//		{
//			m_iBaseActionCount++;
//		}
//		if(pCommunityAction[ i ].ustActionID!=ErrorUnsignedShortID)
//		{
//			m_iCommunityActionCount++;
//		}
//		if(pSocialAction[ i ].ustActionID!=ErrorUnsignedShortID)
//		{
//			m_iSocialActionCount++;
//		}
//	}
//}
//
//int CActionBag::FindNullActionOffSet( short stWhichActionBag )
//{
//	// ToLog( false && "该函数不用!!!!!!" );
//
//	//int iLoop;
//	//for( iLoop=0; iLoop < m_iBagSize; iLoop++ )
//	//{
//	//	if( stWhichActionBag==BagTypeBaseaction )
//	//	{
//	//		if( ErrorUnsignedShortID == m_pBaseAction[iLoop].ustActionID )
//	//			return iLoop;
//	//	}
//	//	if( stWhichActionBag==BagTypeCommunityaction )
//	//	{
//	//		if( ErrorUnsignedShortID == m_pCommunityAction[iLoop].ustActionID )
//	//			return iLoop;
//	//	}
//	//	if( stWhichActionBag==BagTypeSocialaction )
//	//	{
//	//		if( ErrorUnsignedShortID == m_pSocialAction[iLoop].ustActionID )
//	//			return iLoop;
//	//	}
//	//}
//	return -1;
//}
//
//bool CActionBag::AddAction( unsigned short ustActionID, short stIndex )
//{
//	// ToLog( false && "该函数不用!!!!!!" );
//
//	//ItemDefine::SItemAction *pAction;
//	//pAction = (ItemDefine::SItemAction *)(theItemDetail.GetItemByID(ustActionID));
//	//if(!pAction)
//	//	return false;
//	//
//	//int iOffset = stIndex;
//	//if( iOffset==-1 )
//	//{
//	//	iOffset = FindNullActionOffSet( pAction->stType+BagTypeBaseaction );
//	//	if( iOffset==-1 )
//	//		return false;
//	//}
//	//else
//	//{
//	//	if( iOffset<0 || iOffset>=m_iBagSize )
//	//		return false;
//	//}
//
//	//if( pAction->stType==BagTypeBaseaction )
//	//{
//	//	if(m_pBaseAction[iOffset].ustActionID!=ErrorUnsignedShortID)
//	//		return false;
//
//	//	m_pBaseAction[iOffset].ustActionID = ustActionID;
//	//	m_iBaseActionCount++;
//	//}
//	//else if( pAction->stType==BagTypeCommunityaction )
//	//{
//	//	if(m_pCommunityAction[iOffset].ustActionID!=ErrorUnsignedShortID)
//	//		return false;
//
//	//	m_pCommunityAction[iOffset].ustActionID = ustActionID;
//	//	m_iCommunityActionCount++;
//	//}
//	//else if( pAction->stType==BagTypeSocialaction )
//	//{
//	//	if(m_pSocialAction[iOffset].ustActionID!=ErrorUnsignedShortID)
//	//		return false;
//
//	//	m_pSocialAction[iOffset].ustActionID = ustActionID;
//	//	m_iSocialActionCount++;
//	//}
//
//	return true;
//}
//
//bool CActionBag::RemoveAction( unsigned short ustActionID )
//{
//	// ToLog( false && "该函数不用!!!!!!" );
//
//	//ItemDefine::SItemAction *pAction;
//	//pAction = (ItemDefine::SItemAction *)(theItemDetail.GetItemByID(ustActionID));
//	//if(!pAction)
//	//	return false;
//
//	//for( int i=0; i<m_iBagSize; i++ )
//	//{
//	//	if( pAction->stType==BagTypeBaseaction )
//	//	{
//	//		if( m_pBaseAction[ i ].ustActionID==ustActionID )
//	//		{
//	//			m_pBaseAction[ i ].ustActionID = ErrorUnsignedShortID;
//	//			m_iBaseActionCount--;
//	//			return true;
//	//		}
//	//	}
//	//	else if( pAction->stType==BagTypeCommunityaction )
//	//	{
//	//		if( m_pCommunityAction[ i ].ustActionID==ustActionID )
//	//		{
//	//			m_pCommunityAction[ i ].ustActionID = ErrorUnsignedShortID;
//	//			m_iCommunityActionCount--;
//	//			return true;
//	//		}
//	//	}
//	//	else if( pAction->stType==BagTypeSocialaction )
//	//	{
//	//		if( m_pSocialAction[ i ].ustActionID==ustActionID )
//	//		{
//	//			m_pSocialAction[ i ].ustActionID = ErrorUnsignedShortID;
//	//			m_iSocialActionCount--;
//	//			return true;
//	//		}
//	//	}
//	//}
//	return false;
//}
//
//bool CActionBag::RemoveAction( short stWhichActionBag, short stIndex )
//{
//	// ToLog( false && "该函数不用!!!!!!" );
//
//	//if( stWhichActionBag<BagTypeBaseaction
//	//|| stWhichActionBag>BagTypeSocialaction )
//	//	return false;
//
//	//if( stIndex<0 || stIndex>=m_iBagSize )
//	//	return false;
//
//	//if( stWhichActionBag==BagTypeBaseaction )
//	//{
//	//	if(m_pBaseAction[stIndex].ustActionID==ErrorUnsignedShortID)
//	//		return false;
//
//	//	m_pBaseAction[stIndex].ustActionID = ErrorUnsignedShortID;
//	//	m_iBaseActionCount--;
//	//}
//	//else if( stWhichActionBag==BagTypeCommunityaction )
//	//{
//	//	if(m_pCommunityAction[stIndex].ustActionID==ErrorUnsignedShortID)
//	//		return false;
//
//	//	m_pCommunityAction[stIndex].ustActionID = ErrorUnsignedShortID;
//	//	m_iCommunityActionCount--;
//	//}
//	//else if( stWhichActionBag==BagTypeSocialaction )
//	//{
//	//	if(m_pSocialAction[stIndex].ustActionID==ErrorUnsignedShortID)
//	//		return false;
//
//	//	m_pSocialAction[stIndex].ustActionID = ErrorUnsignedShortID;
//	//	m_iSocialActionCount--;
//	//}
//	return true;
//}
//
////获取指定背包,索引的信息
//bool CActionBag::GetAction( short stWhichActionBag, short stIndex, SCharAction *pAction )
//{
//	// ToLog( false && "该函数不用!!!!!!" );
//
//	//if( stWhichActionBag<BagTypeBaseaction
//	//||  stWhichActionBag>BagTypeSocialaction )
//	//	return false;
//
//	//if( stIndex<0 || stIndex>=m_iBagSize )
//	//	return false;
//
//	//if( stWhichActionBag==BagTypeBaseaction )
//	//{
//	//	memcpy( pAction, &m_pBaseAction[stIndex], sizeof(SCharAction) );
//	//}
//	//else if( stWhichActionBag==BagTypeCommunityaction )
//	//{
//	//	memcpy( pAction, &m_pCommunityAction[stIndex], sizeof(SCharAction) );
//	//}
//	//else if( stWhichActionBag==BagTypeSocialaction )
//	//{
//	//	memcpy( pAction, &m_pSocialAction[stIndex], sizeof(SCharAction) );
//	//}
//	return true;
//}
//
////清空指定背包,索引的信息
//bool CActionBag::ClearAction( short stWhichActionBag, short stIndex )
//{
//	// ToLog( false && "该函数不用!!!!!!" );
//
//	//if( stWhichActionBag<BagTypeBaseaction
//	//||  stWhichActionBag>BagTypeSocialaction )
//	//	return false;
//
//	//if( stIndex<0 || stIndex>=m_iBagSize )
//	//	return false;
//
//	//if( stWhichActionBag==BagTypeBaseaction )
//	//{
//	//	m_pBaseAction[stIndex].ustActionID = ErrorUnsignedShortID;
//	//}
//	//else if( stWhichActionBag==BagTypeCommunityaction )
//	//{
//	//	m_pCommunityAction[stIndex].ustActionID = ErrorUnsignedShortID;
//	//}
//	//else if( stWhichActionBag==BagTypeSocialaction )
//	//{
//	//	m_pSocialAction[stIndex].ustActionID = ErrorUnsignedShortID;
//	//}
//	return true;
//}
//
////获取指定背包,索引的状况...判断该位置是有
//bool CActionBag::IsHaveAction( short stWhichActionBag, short stIndex )
//{
//	// ToLog( false && "该函数不用!!!!!!" );
//
//	//if( stWhichActionBag<BagTypeBaseaction
//	//||  stWhichActionBag>BagTypeSocialaction )
//	//	return false;
//
//	//if( stIndex<0 || stIndex>=m_iBagSize )
//	//	return false;
//
//	//if( stWhichActionBag==BagTypeBaseaction )
//	//{
//	//	return (m_pBaseAction[stIndex].ustActionID!=ErrorUnsignedShortID );
//	//}
//	//else if( stWhichActionBag==BagTypeCommunityaction )
//	//{
//	//	return (m_pCommunityAction[stIndex].ustActionID!=ErrorUnsignedShortID );
//	//}
//	//else if( stWhichActionBag==BagTypeSocialaction )
//	//{
//	//	return (m_pSocialAction[stIndex].ustActionID!=ErrorUnsignedShortID );
//	//}
//	return true;
//}
//
//
//
//
//
