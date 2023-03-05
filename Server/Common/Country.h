#ifndef __GAMECOUNTRY_H__
#define __GAMECOUNTRY_H__

/************************************************************************
            国家类属性定义
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include <vector>
#include "CountryDefine.h"
#include "GameTimer.h"
#include "GlobalDef.h"
#include "../CenterServer/Source/CountryReward.h"

class BordersFight
{
public:
    BordersFight() : nMapID( 0 ), nPosX( 0 ), nPosY( 0 ){}

    void SetMapID( unsigned int ustValue ) { nMapID = ustValue; }
    void SetPosX( int nValue ) { nPosX = nValue; }
    void SetPosY( int nValue ) { nPosY = nValue; }

    unsigned short GetMapID() const { return nMapID; }
    int GetPosX() const { return nPosX; }
    int GetPosY() const { return nPosY; }

    friend bool operator == ( const BordersFight& xLeft, const BordersFight& xRight )
    {
        return ( xLeft.nMapID == xRight.nMapID && xLeft.nPosX == xRight.nPosX && xLeft.nPosY == xRight.nPosY );
    }

private:
    unsigned int nMapID;
    int nPosX;
    int nPosY;
};
// 国家信息
template< class T >
class CountryInfo : public CountryData
{
public:
    CountryInfo() : CountryData(), nImpeachGuildID( CountryDefine::NoneID ), nBordersFightIndex( 0 )
    {
        InitCountryInfo();
    }

    // 初始化国家信息
    void InitCountryInfo();

    // 设置国家属性
    void SetCountryData( CountryData& xData );                  

    // 开启保存数据入库定时器
    void StartSaveTimer( unsigned int nCurrentTime ); 

    // 是否已经开始入库定时器
    bool IsSaveTimerStart();

    // 设置弹劾国王的帮派
    void SetImpeachGuild( unsigned int nValue );

    // 获得弹劾国王的帮派
    unsigned int GetImpeachGuild() const;

    // 是否有弹劾帮会
    bool HaveImpeachGuild() const;                              

    // 是否是青龙帮会
    bool IsDragonGuild( unsigned int nValue ) const;           

    // 是否是朱雀帮会
    bool IsRosefinchGuild( unsigned int nValue ) const;         

    // 是否有国王
    bool IsHaveKing() const;     

    // 是否有青龙帮会
    bool IsHaveDragon() const;     

    // 是否有朱雀帮会
    bool IsHaveRosefinch() const;                               

    // 是否是某个职位
    bool IsRightPosition( unsigned char uchPosition, unsigned int nPlayerID ) const;  

    // 获得国家权利
    unsigned int GetRight( unsigned int nPlayerID );            

    // 获得国家职位
    unsigned char GetPosition( unsigned int nPlayerID );     

    // 是否有国家权限
    bool IsHaveRight( unsigned int nRight, unsigned int nPlayerID );    

    // 自动更新
    void RunUpdate( unsigned int nCurrentTime );

    // 清空所有计数
    void ClearAllOperateTime();     

    // 保存信息入库
    void SaveToDatabase();

    // 清除所有国家官员 
    void ClearOfficial();         

    // 任命国家官员
    void AppointOfficial( unsigned char uchPosition, unsigned int nPlayerID, const char* szName ,uint8 SexID,uint16 faceID,uint16 headerID,uint16 professionID);

    // 检查募集时间
    bool CheckRaiseTime();

    // 开启募集定时器
    void StartRaiseTimer( unsigned int nStartTime, unsigned int nKeepTime );

    // 发送边塞入侵坐标
    void SendBordersFightMessage( unsigned short ustMapID, int nPosX, int nPosY );

    // 添加边塞入侵坐标
    void AddBordersFight( unsigned int ustMapID, int nPosX, int nPosY );

    // 检查是否能飞行到边塞入侵点
    bool CheckCanFlyToBorders( unsigned short ustMapID, int nPosX, int nPosY ) const;

    // 设置国家召集发起时间
    void StartConveneTimer( unsigned int nStartTime, unsigned int nSpaceTime );

    // 停止国家召集的时间
    void StopConveneTimer();

    // 设置国家召集地点
    void SetConvenePlace( unsigned int nMapID, int nPosX, int nPosY );

    // 检查国家召集时间是否有效
    bool CheckConveneStartTime();

    // 获得国家召集地点
    const BordersFight& GetConvenePlace() const;

    // 处理国家公告改变
    void ProcessNoticeChange( unsigned int nPlayerID, const char* szNotice );

	void AddCountryInfo(const char* szInfo,__int64 Time,int Value);

    // 操作国家金钱
    void OperateCountryMoney( unsigned char uchType, unsigned int nValue );

	// 操作国家贡品
	 void OperateCountryTribute( unsigned char uchType, unsigned int nValue );

    // 操作国家实力
    void OperateCountryStrength( unsigned char uchType, unsigned nValue );

    // 更新国家数据
    void UpdateCountryData( unsigned char uchType, __int64 n64Value );

    // 处理国家职位改变
    void ProcessCountryOfficialChange( unsigned char uchPosition, unsigned int nPlayerID, const char* szName,uint8 sexID,uint16 faceID,uint16 headerID,uint16 professionID,SCharItem* pItem = NULL );

    // 处理撤销国家帮派
    void ProcessCountryGuildCancel( unsigned int nGuildID );

    // 处理国家战场结果, 包括弹劾
    void ProcessCountryBattleResult( unsigned char uchBattleType, unsigned char uchWinType, unsigned int nGuildID,unsigned int nLoseGuildID = NULL,SCharItem* pItem = NULL ,unsigned int nCampBattle = NULL);

    // 每周1 0:00清算国家实力
    void ProcessCalcCountryStrength( unsigned int nCurrentTime );

    // 发送国家数据请求改变消息
    void SendCountryDataChangeReq( unsigned char uchChangeType, unsigned char uchOperateType, unsigned int nValue );

protected:
    typedef std::vector< BordersFight > BordersFightVector;
    typedef BordersFightVector::iterator BordersFightVectorIter;
    typedef BordersFightVector::const_iterator BordersFightVectorConstIter;

    // 发送国家公告改变消息
    void SendNoticeChangeMessage( unsigned int nPlayerID );

	void SendCountryInfoChangeMessage(const char * szInfo,__int64 Time,int Value);

    // 发送国家数据改变消息
    void SendUpdateCountryDataMessage( unsigned char uchType, __int64 n64Value );

public:
	void SetCountryInfo(const char* szInfo,__int64 Time,int Value);
	__int64 GetCountryInfoTime(int Index) const {return szCountryTime[Index];}
	const char* GetCountryInfo(int Index) const {return szCountryInfo[Index];}
	int GetCountryInfoValue(int Index) const {return szCountryInfoValue[Index];}
private:
    GameTimerEx m_xSaveTimer;            // 保存的定时器
    unsigned int nImpeachGuildID;        // 发起弹劾的公会 ( 每次只能一个公会弹劾 )
    unsigned int nBordersFightIndex;     // 战斗记录索引
    BordersFightVector vecBordersFight;  // 边塞战斗信息

    GameTimerEx xConveneTimer;           // 召集的定时器
    BordersFight xConvenePlace;          // 召集地点

    GameTimerEx m_xRaiseTimer;           // 募捐定时器
    //GameTimerEx m_xStrengthTimer;        // 国家实力清算定时器
	char szCountryInfo[CountryDefine::MaxCountryInfoSum][CountryDefine::MaxCountryInfoLength];    //国家的基本信息
	__int64 szCountryTime[CountryDefine::MaxCountryInfoSum];//国家信息的时间记录
	int  szCountryInfoValue[CountryDefine::MaxCountryInfoSum];
};


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
template< class T >
inline void CountryInfo< T >::SetCountryData( CountryData& xData )
{
    SetID( xData.GetID() );
    if ( xData.HaveName() )
    { SetName( xData.GetName() ); }
    SetMoney( xData.GetMoney() ); 
	SetTribute( xData.GetTribute());
    SetNotice( xData.GetNotice() );
    SetKingGuild( xData.GetKingGuild() );
    SetDragonGuild( xData.GetDragonGuild() );
    SetRosefinchGuild( xData.GetRosefinchGuild() );
    SetSortIndex( xData.GetSortIndex() );
    SetKillCount( xData.GetKillCount() );
    SetDeathCount( xData.GetDeathCount() );

    for ( int i = CountryDefine::Position_None + 1; i < CountryDefine::Position_Max; ++i )
    {
        AddOfficial( *xData.GetOfficial( i ) );
    }

    SetRecordTime( xData.GetRecordTime() );
    SetPlacardCount( xData.GetPlacardCount() );
    SetConveneCount( xData.GetConveneCount() );
    SetBanSpeakCount( xData.GetBanSpeakCount() );
    SetRaiseCount( xData.GetRaiseCount() );
    SetRemitCount( xData.GetRemitCount() );
    SetLastStrength( xData.GetLastStrength() );
    SetNowStrength( xData.GetNowStrength() );
    SetChangeName( xData.GetChangeName() );

    for ( int i = CountryDefine::QuestType_None; i < CountryDefine::QuestType_Max; ++i )
    {
        xOperate[ i ] = *xData.GetQuestOperate( i );

		nQuestSum[i] = xData.GetQuestSumByType(i);
    }

	nDoneQuestStrength = xData.GetDoneQuestAddStrength();
}
template< class T >
inline void CountryInfo< T >::SetCountryInfo(const char* szInfo,__int64 Time,int Value)
{
	//添加一条新的记录
	for(int i =0;i<CountryDefine::MaxCountryInfoSum;++i)
	{
		if(szCountryTime[i] ==0)
		{
			strncpy_s( szCountryInfo[i], sizeof( szCountryInfo[i] )-1, szInfo, sizeof( szCountryInfo[i] ) - 1 );
			szCountryTime[i] = Time;
			szCountryInfoValue[i] = Value;
			return;
		}
		else
			continue;
	}
	//所有消息已经满了 就替换掉第一条
	for(int i =1;i<CountryDefine::MaxCountryInfoSum;++i)
	{
		szCountryTime[i-1] = szCountryTime[i];
		strncpy_s( szCountryInfo[i-1], sizeof( szCountryInfo[i-1] )-1, szCountryInfo[i], sizeof( szCountryInfo[i-1] ) - 1 );
		szCountryInfoValue[i-1] = szCountryInfoValue[i];
	}
	szCountryTime[CountryDefine::MaxCountryInfoSum -1] = Time;
	szCountryInfoValue[CountryDefine::MaxCountryInfoSum -1] = Value;
	strncpy_s( szCountryInfo[CountryDefine::MaxCountryInfoSum-1], sizeof( szCountryInfo[CountryDefine::MaxCountryInfoSum-1] )-1,szInfo, sizeof( szCountryInfo[CountryDefine::MaxCountryInfoSum-1] ) - 1 );
}
template< class T >
inline void CountryInfo< T >::StartSaveTimer( unsigned int nCurrentTime )
{
    m_xSaveTimer.StartTimer( nCurrentTime, CountryDefine::SaveKeepTime );
}

template< class T >
inline bool CountryInfo< T >::IsSaveTimerStart()
{
    return m_xSaveTimer.IsStart();
}


template< class T >
inline void CountryInfo< T >::SetImpeachGuild( unsigned int nValue )
{
    nImpeachGuildID = nValue;
}

template< class T >
inline unsigned int CountryInfo< T >::GetImpeachGuild() const
{
    return nImpeachGuildID;
}

template< class T >
inline bool CountryInfo< T >::HaveImpeachGuild() const
{
    return nImpeachGuildID != CountryDefine::NoneID;
}

template< class T >
inline bool CountryInfo< T >::IsDragonGuild( unsigned int nValue ) const
{
    return nDragonGuildID == nValue;
}

template< class T >
inline bool CountryInfo< T >::IsRosefinchGuild( unsigned int nValue ) const
{
    return nRosefinchGuildID == nValue;
}

template< class T >
inline bool CountryInfo< T >::IsHaveKing() const
{
    return nKingGuildID != CountryDefine::NoneID;
}

template< class T >
inline bool CountryInfo< T >::IsHaveDragon() const
{
    return nDragonGuildID != CountryDefine::NoneID;
}

template< class T >
inline bool CountryInfo< T >::IsHaveRosefinch() const
{
    return nRosefinchGuildID != CountryDefine::NoneID;
}

template< class T >
inline bool CountryInfo< T >::IsRightPosition( unsigned char uchPosition, unsigned int nPlayerID ) const
{
    if ( uchPosition >= CountryDefine::Position_Max || nPlayerID == CountryDefine::ErrorID )
    { return false; }

    return xOfficial[ uchPosition ].GetID() == nPlayerID;
}

template< class T >
inline unsigned int CountryInfo< T >::GetRight( unsigned int nPlayerID )
{
    unsigned int nRight = CountryDefine::Right_None;
    for ( int i = CountryDefine::Position_None + 1; i < CountryDefine::Position_Max; ++i )
    {
        if ( xOfficial[ i ].GetID() == nPlayerID )
        {
            nRight = xOfficial[ i ].GetRight();
            break;
        }
    }

    return nRight;
}

template< class T >
inline unsigned char CountryInfo< T >::GetPosition( unsigned int nPlayerID )
{
    unsigned char uchPositon = CountryDefine::Position_None;
    for ( int i = CountryDefine::Position_None + 1; i < CountryDefine::Position_Max; ++i )
    {
        if ( xOfficial[ i ].GetID() == nPlayerID )
        {
            uchPositon = xOfficial[ i ].GetPosition();
            break;
        }
    }

    return uchPositon;
}

template< class T >
inline bool CountryInfo< T >::IsHaveRight( unsigned int nRight, unsigned int nPlayerID )
{
    for ( int i = CountryDefine::Position_None + 1; i < CountryDefine::Position_Max; ++i )
    {
        if ( xOfficial[ i ].GetID() == nPlayerID )
        {
            return xOfficial[ i ].HaveRight( nRight );
        }
    }

    return false;
}

template< class T >
inline void CountryInfo< T >::ClearAllOperateTime()
{
    SetPlacardCount( 0 );
    SetRaiseCount( 0 );
    SetRemitCount( 0 );
    SetBanSpeakCount( 0 );
    SetConveneCount( 0 );

    for ( int i = CountryDefine::QuestType_None; i < CountryDefine::QuestType_Max; ++i )
    {
        xOperate[ i ].SetCount( 0 );
        xOperate[ i ].SetStartTime( 0 );

		//nQuestSum[i] = 0;
    }

    m_xRaiseTimer.StopTimer();

	//nDoneQuestStrength =0;
}

template< class T >
inline void CountryInfo< T >::ClearOfficial()
{
    for ( int i = CountryDefine::Position_None; i < CountryDefine::Position_Max; ++i )
    {
		//zhuxincong 删除物品应该放到这里来
		theCountryReward.BSubItemAndMount(xOfficial[ i ].GetPosition(),xOfficial[ i ].GetID());
        xOfficial[ i ].ClearOfficial();
		

    }

    nKingGuildID = CountryDefine::NoneID;
}

template< class T >
void CountryInfo< T >::AppointOfficial( unsigned char uchPosition, unsigned int nPlayerID, const char* szName,uint8 SexID,uint16 faceID,uint16 headerID,uint16 professionID)
{
    // 如果以前是官员
    for ( int i = CountryDefine::Position_None + 1; i < CountryDefine::Position_Max; ++i )
    {
        if ( xOfficial[ i ].GetID() == nPlayerID )
        {
            xOfficial[ i ].ClearOfficial();
            break;
        }
    }

    if ( uchPosition == CountryDefine::Position_None )
    { return; }

    OfficialInfo* pOfficial = GetOfficial( uchPosition );
    if ( pOfficial == NULL )
    { return; }

    pOfficial->SetID( nPlayerID );
    pOfficial->SetName( szName );
    pOfficial->SetRight( CountryDefine::GetRightByPosition( uchPosition ) );
	pOfficial->SetSexID(SexID);
	pOfficial->SetFaceID(faceID);
	pOfficial->SetHeaderID(headerID);
	pOfficial->SetProfessionID(professionID);
}

template< class T >
inline bool CountryInfo< T >::CheckRaiseTime()
{
    m_xRaiseTimer.DoneTimer();

    return m_xRaiseTimer.IsStart();
}

template< class T >
inline void CountryInfo< T >::StartRaiseTimer( unsigned int nStartTime, unsigned int nKeepTime )
{
    m_xRaiseTimer.StartTimer( nStartTime, nKeepTime );
}

template< class T >
inline void CountryInfo< T >::AddBordersFight( unsigned int ustMapID, int nPosX, int nPosY )
{
    if ( nBordersFightIndex >= vecBordersFight.size() )
    { nBordersFightIndex = 0; }

    vecBordersFight[ nBordersFightIndex ].SetMapID( ustMapID );
    vecBordersFight[ nBordersFightIndex ].SetPosX( nPosX );
    vecBordersFight[ nBordersFightIndex ].SetPosY( nPosY );

    ++nBordersFightIndex;
}

template< class T >
inline bool CountryInfo< T >::CheckCanFlyToBorders( unsigned short ustMapID, int nPosX, int nPosY ) const
{
    BordersFight xFight;
    xFight.SetMapID( ustMapID );
    xFight.SetPosX( nPosX );
    xFight.SetPosY( nPosY );

    BordersFightVectorConstIter iter = std::find( vecBordersFight.begin(), vecBordersFight.end(), xFight );
    return ( iter != vecBordersFight.end() );
}

template< class T >
inline void CountryInfo< T >::StartConveneTimer( unsigned int nStartTime, unsigned int nSpaceTime )
{
    xConveneTimer.StopTimer();  // 先关闭定时器
    xConveneTimer.StartTimer( nStartTime, nSpaceTime );
}

template< class T >
inline void CountryInfo< T >::StopConveneTimer()
{
    xConveneTimer.StopTimer();
}

template< class T >
inline void CountryInfo< T >::SetConvenePlace( unsigned int nMapID, int nPosX, int nPosY )
{
    xConvenePlace.SetMapID( nMapID );
    xConvenePlace.SetPosX( nPosX );
    xConvenePlace.SetPosY( nPosY );
}

template< class T >
inline bool CountryInfo< T >::CheckConveneStartTime()
{
    xConveneTimer.DoneTimer();

    return xConveneTimer.IsStart();
}

template< class T >
inline const BordersFight& CountryInfo< T >::GetConvenePlace() const
{
    return xConvenePlace;
}

template< class T >
void CountryInfo< T >::UpdateCountryData( unsigned char uchType, __int64 n64Value )
{
    switch( uchType )
    {
    case CountryDefine::CancelKingGuild:
    case CountryDefine::CancelRosefinchGuild:
    case CountryDefine::CancelDragonGuild:
        break;
    case CountryDefine::UpdateMoney:
        SetMoney( n64Value );
        break;
	case CountryDefine::UpdateTribute:
		SetTribute(n64Value);
		break;
    case CountryDefine::UpdateKingGuild:
        if ( GetDragonGuild() == n64Value )     // 如果是青龙帮
        { SetDragonGuild( CountryDefine::NoneID ); }
        if ( GetRosefinchGuild() == n64Value )  // 如果是朱雀帮
        { SetRosefinchGuild( CountryDefine::NoneID ); }
        SetKingGuild( n64Value );
        SetChangeName( false );  // 换国王了, 可以重新修改国号
        break;
    case CountryDefine::UpdateDragonGuild:
        SetDragonGuild( n64Value );
        break;
    case CountryDefine::UpdateRosefinchGuild:
        SetRosefinchGuild( n64Value );
        break;
    case CountryDefine::UpdateLastStrength:
        SetLastStrength( n64Value );
        break;
    case CountryDefine::UpdateNowStrength:
        SetNowStrength( n64Value );
        break;
    case CountryDefine::UpdateChangeName:
        SetChangeName( false );
        break;
    case CountryDefine::UpdateSortIndex:
        SetSortIndex( static_cast< unsigned char >( n64Value ) );
        break;
    default:
        return;
    }

    SendUpdateCountryDataMessage( uchType, n64Value );
}

template<class T>
void CountryInfo< T >::OperateCountryTribute( unsigned char uchType, unsigned int nValue )
{
	switch ( uchType )
	{
	case CountryDefine::OperateSet:
		break;
	case CountryDefine::OperateAdd:
		nValue += GetTribute();
		break;
	case CountryDefine::OperateSub:
		if ( nValue > GetTribute() )
		{ nValue = GetTribute(); }
		nValue = GetTribute() - nValue;
		break;
	default:
		return;
	}
	UpdateCountryData( CountryDefine::UpdateTribute, nValue );
}

template< class T >
void CountryInfo< T >::OperateCountryMoney( unsigned char uchType, unsigned int nValue )
{
    switch ( uchType )
    {
    case CountryDefine::OperateSet:
        break;
    case CountryDefine::OperateAdd:
        nValue += GetMoney();
        break;
    case CountryDefine::OperateSub:
        if ( nValue > GetMoney() )
        { nValue = GetMoney(); }
        nValue = GetMoney() - nValue;
        break;
    default:
        return;
    }
	
	if (nValue < 0)
	{
		nValue = 0;
	}
    UpdateCountryData( CountryDefine::UpdateMoney, nValue );
}

template< class T >
void CountryInfo< T >::ProcessNoticeChange( unsigned int nPlayerID, const char* szNotice )
{
    SetNotice( szNotice );
    SetPlacardCount( GetPlacardCount() + 1 );

    SendNoticeChangeMessage( nPlayerID );
}
template< class T >
void CountryInfo< T >::AddCountryInfo(const char* szInfo,__int64 Time,int Value)
{
	SetCountryInfo(szInfo,Time,Value);//添加新的公告
	SendCountryInfoChangeMessage(szInfo,Time,Value);
}

template< class T >
void CountryInfo< T >::OperateCountryStrength( unsigned char uchType, unsigned int nValue )
{
    switch ( uchType )
    {
    case CountryDefine::OperateSet:
        break;
    case CountryDefine::OperateAdd:
        nValue += GetNowStrength();
        break;
    case CountryDefine::OperateSub:
        if ( nValue > GetNowStrength() )
        { nValue = GetNowStrength(); }
        nValue = GetNowStrength() - nValue;
        break;
    default:
        return;
    }

    UpdateCountryData( CountryDefine::UpdateNowStrength, nValue );
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////
template< class T > class GuildInfo;

class ClientPeer;
typedef CountryInfo< GuildInfo< ClientPeer > > CenterCountry;

class GamePlayer;
typedef CountryInfo< GuildInfo< GamePlayer > > GameCountry;
//////////////////////////////////////////////////////////////////////////////////////////////////////////

#endif