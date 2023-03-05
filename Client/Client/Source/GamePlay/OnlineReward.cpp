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
	// ���㵱ǰ����ʱ��
	if( m_dwEnterWorldTime == 0 )
		m_dwEnterWorldTime = HQ_TimeGetTime();
	DWORD dwInGameDuration = HQ_TimeGetTime() - m_dwEnterWorldTime;	// ��������ʱ�䣬����
	int iInGameMinutes = dwInGameDuration * 1.f / 60000;	// ����ʱ��ת�ɷ���
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
	// ������ȡȫ����Ʒǰ���Ѿ��жϣ�����iRewardId�ض�С��iMaxCount-1
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
			// ��ʾ��ȡ�������
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
 
 	// ���㵱ǰ����ʱ��
 	unsigned int iCurrentOnlineTime = GetCurrentOnlineTime();

	switch( m_eStatus )
	{
	case ORS_FIRST:
		{
			/// ���Ƿ��п���ȡ��ʱ������Ľ���������У���ʾ���档
			/// ���û�У��������:
			/// 1.>û���κν����ˡ���ôover
			/// 2.>���н���������û������ʱ�䡣updateʱ�䣬ֱ��ʱ�䵽�˴�����
			if( HaveReward() )
			{
				short stMaxCanGetRewardId = GetMaxCanGetRewardId();
				int iCurReward = GetAvailableOnlineReward(stMaxCanGetRewardId);
				if( iCurReward != -1 && iCurReward <= stMaxCanGetRewardId )
				{
					pReward = theOnLineRewardConfig.GetOnLineReward( iCurReward );
					if( pReward )
					{
						/// ���Ե���ʱ�ˣ�����ʾ����
						//s_CUI_ID_FRAME_OnlineAward2.ShowConfirmAward( iCurReward, pReward );
						unsigned int uiGetRewardTime = pReward->dwCountDown;
						// ��ʾ����ʱ���棬�����¸�����ID
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
					/// ����ʱ��
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
			
			///// ��ȷ���Ƿ���û����ȡ�Ľ������еĻ�����ʾ����ʱ���������ͼƬ			
			//short stMaxCanGetRewardId = GetMaxCanGetRewardId();
			//int iCurReward = GetAvailableOnlineReward(stMaxCanGetRewardId);
			//if( iCurReward != -1 && iCurReward <= stMaxCanGetRewardId )
			//{
			//	// ��Ҫ��ȡ����������ʾ���
			//	s_CUI_ID_FRAME_OnlineAward.ShowOnlyRewardBox( true );
			//}
			//else
			//{
			//	/// û�н�������ȡ����ʾ����չʾ���棻������û���κν����ˣ�go over.

			//	// ��ȡ�¸�����
			//	pReward = theOnLineRewardConfig.GetOnLineReward(stMaxCanGetRewardId+1);
			//	if( pReward )
			//	{
			//		unsigned int uiGetRewardTime = pReward->dwCountDown;
			//		// ��ʾ����ʱ���棬�����¸�����ID
			//		bool bRet = s_CUI_ID_FRAME_OnlineAward.SetNextAward(uiGetRewardTime-iCurrentOnlineTime,stMaxCanGetRewardId+1);
			//		if( bRet )
			//			s_CUI_ID_FRAME_OnlineAward.SetVisable(true);
			//	}
			//	else //û�н������Ѿ�
			//	{
			//		SetCurrentStatus( ORS_OVER );
			//		SetUpdateOnlineReward();
			//	}

			//}
		}
		break;
		
	case ORS_CLICKOK:
		{
			/// ���ȷ����ֻ��һ�����:��������ʱ��
			short stMaxCanGetRewardId = GetMaxCanGetRewardId();
			int iCurReward = GetAvailableOnlineReward(stMaxCanGetRewardId);
			if( iCurReward != -1 && iCurReward <= stMaxCanGetRewardId )
			{
				pReward = theOnLineRewardConfig.GetOnLineReward( iCurReward );
				if( pReward )
				{
					unsigned int uiGetRewardTime = pReward->dwCountDown;
					// ��ʾ����ʱ���棬�����¸�����ID
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
			/// ����ʱ������ֻ��ʾ��У�����Ѿ���ʾ����enable�������������
			if( s_CUI_ID_FRAME_OnlineAward2.IsVisable() )
			{
				s_CUI_ID_FRAME_OnlineAward.SetVisable( false );
				// ����Ѿ�������У�enable����
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
			/// �������ʾ��ȡ���档������򲻿����졣�����������ص���ʱui��
			/// ���������ʾ��ui������̬��ȡ��ť��

			short stMaxCanGetRewardId = GetMaxCanGetRewardId();
			int iCurReward = GetAvailableOnlineReward(stMaxCanGetRewardId);
			pReward = 0;
			if( iCurReward != -1 && iCurReward <= stMaxCanGetRewardId ) // ���ڽ���
			{
				pReward = theOnLineRewardConfig.GetOnLineReward(iCurReward);
				if( s_CUI_ID_FRAME_OnlineAward.IsRunning() )//���ڵ���ʱ, Ҳ���ǲ�����ȡ
				{
					// ������ȡ������ʾ��Ʒ������̬ 
					// ����ȡ��������Ϊ��ǰ���ڵ���ʱ�Ľ���id
					iCurReward = s_CUI_ID_FRAME_OnlineAward.GetNextAwardIndex();
					s_CUI_ID_FRAME_OnlineAward2.SetVisable( true );
					s_CUI_ID_FRAME_OnlineAward2.ShowGetAward();
					s_CUI_ID_FRAME_OnlineAward2.SetButGetAwardEnable( false );
				}
				else
				{
					if( pReward )
					{
						// ������к͵���ʱ
						s_CUI_ID_FRAME_OnlineAward.SetVisable( false );
						s_CUI_ID_FRAME_OnlineAward2.SetVisable(true);
						s_CUI_ID_FRAME_OnlineAward2.ShowGetAward();
						s_CUI_ID_FRAME_OnlineAward2.SetButGetAwardEnable( true );
					}
				}				
			}
			if( pReward )
			{
				// ��ʾ��ȡ�������
				s_CUI_ID_FRAME_OnlineAward2.ShowOnlineReward( iCurReward, pReward );
			}

		}
		break;

	case ORS_GOT:
		{
			/// ��ʱ�������Ѿ�������Ϣ�������˽������棬���ҽ��ôν�������Ϊ������ȡ��
			/// �����ȡ��Ʒ���������:
			/// 1.> �����������������һ�������ȡ����������ʱ��
			/// 2.> ����������������������ȡ������ʾ���
			/// 3.> û�н�����go ORS_OVER.
			// ��ORS_FIRST�߼�һ�¡�
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
//  		// ��ǰ����ʱ�䳬�����һ��������ʱ�䣬����ʾ����ʱ
//  		m_shCanGetMaxReward = iMaxCount-1;
//  	}
//  	else
//  	{
//  		// ����ʱ��ʾ����ȡ����ʱ���ڼ�������
//  		int iRewardId = GetMaxCanGetRewardId();
// 
//  		m_shCanGetMaxReward = iRewardId;
//  
//  		// ��ȡ�¸�����
//  		pReward = theOnLineRewardConfig.GetOnLineReward(iRewardId+1);
//  		if( pReward )
//  		{
//  			unsigned int uiGetRewardTime = pReward->dwCountDown;
//  			// ��ʾ����ʱ���棬�����¸�����ID
//  			bool bRet = s_CUI_ID_FRAME_OnlineAward.SetNextAward(uiGetRewardTime-iCurrentOnlineTime,iRewardId+1);
//  			if( bRet )
//  				s_CUI_ID_FRAME_OnlineAward.SetVisable(true);
//  		}
//  	}
//  
//  	// ��ȡ��ǰ���������ID
//  	if( m_shCanGetMaxReward >= 0 )
//  	{
//  		int iCurReward = GetAvailableOnlineReward(m_shCanGetMaxReward);
//  		if( iCurReward != -1 && iCurReward <= m_shCanGetMaxReward )
//  		{
//  			pReward = theOnLineRewardConfig.GetOnLineReward(iCurReward);
//  			if( pReward )
//  			{
//  				m_shCurrentReward = iCurReward;
//  				// ��ʾ��ȡ�������
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
