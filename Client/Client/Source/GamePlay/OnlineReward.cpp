#include "OnlineReward.h"
#include "OnLineRewardConfig.h"
#include "MeRTLibs.h"
#include "PlayerRole.h"
#include "OnlineAward.h"
#include "OnlineAward2.h"

extern BOOL g_bIsShowSceneAndPlayer;

COnlineReward::COnlineReward( void )
{
	Reset();
}

void COnlineReward::Reset()
{
	SetCurrentStatus( ORS_FIRST );
	SetUpdateOnlineReward();
	m_dwEnterWorldTime = 0;
	m_shCurrentReward = -1;
	m_shCanGetMaxReward = -1;
	m_bUpdateTime = false;
}

void COnlineReward::SetCurrentStatus( EOnlineRewardStatus status )
{
	m_eStatus = status;
}

DWORD COnlineReward::GetCurrentOnlineTime()
{
	// 计算当前在线时间
	if( m_dwEnterWorldTime == 0 )
		m_dwEnterWorldTime = HQ_TimeGetTime();
	DWORD dwInGameDuration = HQ_TimeGetTime() - m_dwEnterWorldTime;	// 本次在线时间，毫秒
	int iInGameMinutes = dwInGameDuration * 1.f / 60000;	// 在线时间转成分钟
	unsigned int iCurrentOnlineTime = thePlayerRole.m_charinfo.baseinfo.liveinfo.dwOnlineTime + iInGameMinutes;
	return iCurrentOnlineTime;
}
DWORD COnlineReward::GetOnlineTime()
{
	if( m_dwEnterWorldTime == 0 )
		return 0;
	DWORD dwInGameDuration = HQ_TimeGetTime() - m_dwEnterWorldTime;	
	return dwInGameDuration;
}
short COnlineReward::GetMaxCanGetRewardId()
{
	int iMaxCount = theOnLineRewardConfig.GetMaxRewardCount();
	int iRewardId = 0;
	for( iRewardId=iMaxCount-1; iRewardId>=0; --iRewardId )
	{
		const OnLineRewardConfig::OnLineReward* pReward = theOnLineRewardConfig.GetOnLineReward(iRewardId);
		if( !pReward )
			continue;

		if( pReward->dwOnLineTime <= GetCurrentOnlineTime() )
			break;
	}
	// 可以领取全部物品前面已经判断，所以iRewardId必定小于iMaxCount-1
	if( iRewardId >= iMaxCount )
		iRewardId = iMaxCount-1;

	return iRewardId;
}

short COnlineReward::GetNextRewardId()
{
	return GetMaxCanGetRewardId() + 1;
}

bool COnlineReward::HaveReward()
{
	int iMaxCount = theOnLineRewardConfig.GetMaxRewardCount() - 1;

	if( iMaxCount < 0 )
		return false;

	unsigned long dwRewardItemInfo = thePlayerRole.m_charinfo.baseinfo.liveinfo.dwRewardItemInfo;
	for( int i=0; i<=iMaxCount; ++i )
	{
		if( (dwRewardItemInfo & (1<<i)) == 0 )
		{
			return true;
		}
	}
	return false;
}

void COnlineReward::ShowCurrentRewardUI()
{
	short stMaxId = GetMaxCanGetRewardId();

	int iCurReward = GetAvailableOnlineReward( stMaxId );
	if( iCurReward != -1 && iCurReward <= stMaxId )
	{
		const OnLineRewardConfig::OnLineReward* pReward = theOnLineRewardConfig.GetOnLineReward(iCurReward);
		if( pReward )
		{
			// 显示领取礼物界面
			bool bRet = s_CUI_ID_FRAME_OnlineAward2.ShowOnlineReward( iCurReward, pReward );
			if( bRet )
			{
				s_CUI_ID_FRAME_OnlineAward2.SetVisable(true);
			}
		}
	}
}

void COnlineReward::UpdateTime()
{
	if( !m_bUpdateTime )
		return;
}

void COnlineReward::UpdateOnlineReward()
{
 	if( !g_bIsShowSceneAndPlayer )
 		return;
 
 	if( !m_bUpdateOnlineReward )
		return;

	m_bUpdateOnlineReward = FALSE;
 
 	int iMaxCount = theOnLineRewardConfig.GetMaxRewardCount();
 	if( iMaxCount <= 0 )
 		return;
 	if( iMaxCount > 32 )
 		iMaxCount = 32;
 
	const OnLineRewardConfig::OnLineReward* pReward = theOnLineRewardConfig.GetOnLineReward(iMaxCount-1);
 	if( !pReward )
 		return; 
 
 	// 计算当前在线时间
 	unsigned int iCurrentOnlineTime = GetCurrentOnlineTime();

	switch( m_eStatus )
	{
	case ORS_FIRST:
		{
			/// 看是否有可领取，时间满足的奖励，如果有，显示界面。
			/// 如果没有，两种情况:
			/// 1.>没有任何奖励了。那么over
			/// 2.>还有奖励，但是没有满足时间。update时间，直到时间到了触发。
			if( HaveReward() )
			{
				short stMaxCanGetRewardId = GetMaxCanGetRewardId();
				int iCurReward = GetAvailableOnlineReward(stMaxCanGetRewardId);
				if( iCurReward != -1 && iCurReward <= stMaxCanGetRewardId )
				{
					pReward = theOnLineRewardConfig.GetOnLineReward( iCurReward );
					if( pReward )
					{
						/// 可以倒计时了，出提示界面
						//s_CUI_ID_FRAME_OnlineAward2.ShowConfirmAward( iCurReward, pReward );
						unsigned int uiGetRewardTime = pReward->dwCountDown;
						// 显示倒计时界面，传入下个礼物ID
						bool bRet = s_CUI_ID_FRAME_OnlineAward.SetNextAward(uiGetRewardTime,iCurReward);
						if( bRet )
							s_CUI_ID_FRAME_OnlineAward.SetVisable(true);
					}
					else
					{
						assert( 0 && " not reward, impossible!");
					}
					
				}
				else
				{
					/// 更新时间
					//EnableUpdateTime( true );
					SetCurrentStatus( ORS_FIRST );
					SetUpdateOnlineReward();
				}
			}
			else
			{
				SetCurrentStatus( ORS_OVER );
				SetUpdateOnlineReward();
			}
			
			///// 先确定是否有没有领取的奖励，有的话不显示倒计时，而是礼盒图片			
			//short stMaxCanGetRewardId = GetMaxCanGetRewardId();
			//int iCurReward = GetAvailableOnlineReward(stMaxCanGetRewardId);
			//if( iCurReward != -1 && iCurReward <= stMaxCanGetRewardId )
			//{
			//	// 需要领取奖励，仅显示礼盒
			//	s_CUI_ID_FRAME_OnlineAward.ShowOnlyRewardBox( true );
			//}
			//else
			//{
			//	/// 没有奖励可领取，显示奖励展示界面；如果今后没有任何奖励了，go over.

			//	// 获取下个礼物
			//	pReward = theOnLineRewardConfig.GetOnLineReward(stMaxCanGetRewardId+1);
			//	if( pReward )
			//	{
			//		unsigned int uiGetRewardTime = pReward->dwCountDown;
			//		// 显示倒计时界面，传入下个礼物ID
			//		bool bRet = s_CUI_ID_FRAME_OnlineAward.SetNextAward(uiGetRewardTime-iCurrentOnlineTime,stMaxCanGetRewardId+1);
			//		if( bRet )
			//			s_CUI_ID_FRAME_OnlineAward.SetVisable(true);
			//	}
			//	else //没有奖励了已经
			//	{
			//		SetCurrentStatus( ORS_OVER );
			//		SetUpdateOnlineReward();
			//	}

			//}
		}
		break;
		
	case ORS_CLICKOK:
		{
			/// 点击确定后，只有一个情况:弹出倒计时框
			short stMaxCanGetRewardId = GetMaxCanGetRewardId();
			int iCurReward = GetAvailableOnlineReward(stMaxCanGetRewardId);
			if( iCurReward != -1 && iCurReward <= stMaxCanGetRewardId )
			{
				pReward = theOnLineRewardConfig.GetOnLineReward( iCurReward );
				if( pReward )
				{
					unsigned int uiGetRewardTime = pReward->dwCountDown;
					// 显示倒计时界面，传入下个礼物ID
					bool bRet = s_CUI_ID_FRAME_OnlineAward.SetNextAward(uiGetRewardTime,iCurReward);
					if( bRet )
						s_CUI_ID_FRAME_OnlineAward.SetVisable(true);
				}
			}
			else
			{
				assert( 0 && " Not a valid reward id, impossible! " );				
			}
		}
		break;

	case ORS_TIMEFINISH:
		{
			/// 倒计时结束，只显示礼盒；如果已经显示，则enable按键，隐藏礼盒
			if( s_CUI_ID_FRAME_OnlineAward2.IsVisable() )
			{
				s_CUI_ID_FRAME_OnlineAward.SetVisable( false );
				// 如果已经打开了礼盒，enable按键
				s_CUI_ID_FRAME_OnlineAward2.ShowGetAward();
				s_CUI_ID_FRAME_OnlineAward2.SetButGetAwardEnable( true );				
			}
			else
			{
				s_CUI_ID_FRAME_OnlineAward.ShowOnlyRewardBox( true );
				s_CUI_ID_FRAME_OnlineAward.ShowRewardBoxEffect( true );
			}
		}
		break;
		
	case ORS_CLICKBOX:
		{
			/// 点击后，显示领取界面。可以领或不可以领。可以领则隐藏倒计时ui，
			/// 否则继续显示该ui，并灰态领取按钮。

			short stMaxCanGetRewardId = GetMaxCanGetRewardId();
			int iCurReward = GetAvailableOnlineReward(stMaxCanGetRewardId);
			pReward = 0;
			if( iCurReward != -1 && iCurReward <= stMaxCanGetRewardId ) // 存在奖励
			{
				pReward = theOnLineRewardConfig.GetOnLineReward(iCurReward);
				if( s_CUI_ID_FRAME_OnlineAward.IsRunning() )//正在倒计时, 也就是不可领取
				{
					// 不能领取，则显示物品，并灰态 
					// 将领取奖励设置为当前正在倒计时的奖励id
					iCurReward = s_CUI_ID_FRAME_OnlineAward.GetNextAwardIndex();
					s_CUI_ID_FRAME_OnlineAward2.SetVisable( true );
					s_CUI_ID_FRAME_OnlineAward2.ShowGetAward();
					s_CUI_ID_FRAME_OnlineAward2.SetButGetAwardEnable( false );
				}
				else
				{
					if( pReward )
					{
						// 隐藏礼盒和倒计时
						s_CUI_ID_FRAME_OnlineAward.SetVisable( false );
						s_CUI_ID_FRAME_OnlineAward2.SetVisable(true);
						s_CUI_ID_FRAME_OnlineAward2.ShowGetAward();
						s_CUI_ID_FRAME_OnlineAward2.SetButGetAwardEnable( true );
					}
				}				
			}
			if( pReward )
			{
				// 显示领取礼物界面
				s_CUI_ID_FRAME_OnlineAward2.ShowOnlineReward( iCurReward, pReward );
			}

		}
		break;

	case ORS_GOT:
		{
			/// 此时服务器已经回了消息，隐藏了奖励界面，并且将该次奖励设置为不可领取。
			/// 点击领取物品。情况如下:
			/// 1.> 还有其他奖励，并且还不能领取，继续倒计时。
			/// 2.> 还有其他奖励，并可以领取，仅显示礼盒
			/// 3.> 没有奖励，go ORS_OVER.
			// 与ORS_FIRST逻辑一致。
			SetCurrentStatus( ORS_FIRST );
			SetUpdateOnlineReward();

		}
		break;

	case ORS_GOTEND:
		break;

	case ORS_OVER:
		{
			EnableUpdateTime( false );
			s_CUI_ID_FRAME_OnlineAward.ShowRewardBoxEffect( false );
			s_CUI_ID_FRAME_OnlineAward.SetVisable( false );
			s_CUI_ID_FRAME_OnlineAward2.SetVisable( false );
		}
		break;
	}
 
//  	if( iCurrentOnlineTime > pReward->dwCountDown )
//  	{
//  		// 当前在线时间超过最后一次送礼物时间，不显示倒计时
//  		m_shCanGetMaxReward = iMaxCount-1;
//  	}
//  	else
//  	{
//  		// 倒计时显示，获取倒计时到第几个礼物
//  		int iRewardId = GetMaxCanGetRewardId();
// 
//  		m_shCanGetMaxReward = iRewardId;
//  
//  		// 获取下个礼物
//  		pReward = theOnLineRewardConfig.GetOnLineReward(iRewardId+1);
//  		if( pReward )
//  		{
//  			unsigned int uiGetRewardTime = pReward->dwCountDown;
//  			// 显示倒计时界面，传入下个礼物ID
//  			bool bRet = s_CUI_ID_FRAME_OnlineAward.SetNextAward(uiGetRewardTime-iCurrentOnlineTime,iRewardId+1);
//  			if( bRet )
//  				s_CUI_ID_FRAME_OnlineAward.SetVisable(true);
//  		}
//  	}
//  
//  	// 获取当前能领的礼物ID
//  	if( m_shCanGetMaxReward >= 0 )
//  	{
//  		int iCurReward = GetAvailableOnlineReward(m_shCanGetMaxReward);
//  		if( iCurReward != -1 && iCurReward <= m_shCanGetMaxReward )
//  		{
//  			pReward = theOnLineRewardConfig.GetOnLineReward(iCurReward);
//  			if( pReward )
//  			{
//  				m_shCurrentReward = iCurReward;
//  				// 显示领取礼物界面
// 				s_CUI_ID_FRAME_OnlineAward2.ClearList();
// 				for( int i = 0 ; i < OnLineRewardConfig::EConstDefine_RewardItemMaxSize; ++ i )
// 				{
// 					if( pReward->nItemID[i] == InvalidLogicNumber )
// 						continue;
// 					bool bRet = s_CUI_ID_FRAME_OnlineAward2.SetOnlineReward(m_shCurrentReward, pReward->nItemID[i], pReward->nCount[i]);
// 					if( bRet )
// 					{
// 						s_CUI_ID_FRAME_OnlineAward2.SetVisable(true);
// 					}
// 				}
//  			}
//  		}
//  	}
}

short COnlineReward::GetAvailableOnlineReward(int iMaxReward)
{
	if( iMaxReward < 0 || iMaxReward >= 32 )
		return -1;

	short reward = -1;
	unsigned long dwRewardItemInfo = thePlayerRole.m_charinfo.baseinfo.liveinfo.dwRewardItemInfo;
	for( int i=0; i<=iMaxReward; ++i )
	{
		if( (dwRewardItemInfo & (1<<i)) == 0 )
		{
			reward = i;
			break;
		}
	}
	return reward;
}

void COnlineReward::GotOnlineReward(unsigned char rewardId)
{
	if( rewardId < 0 || rewardId >= 32 )
		return;

	thePlayerRole.m_charinfo.baseinfo.liveinfo.dwRewardItemInfo |= 1<<rewardId;
	m_bUpdateOnlineReward = TRUE;
}
