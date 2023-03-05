#ifndef __GAMECOUNTRYDEFINE_H__
#define __GAMECOUNTRYDEFINE_H__

/************************************************************************
            ���ҽṹ���Զ���
            MaintenanceMan Mail: lori227@live.cn
************************************************************************/
#include "string.h"
#include "CountryConfig.h"

namespace CountryDefine
{
    enum EConstDefine
    {
        // ��������
        Country_Init = 0,        // �޹���
        Country_LouLan,          // ¥������(κ��)
        Country_KunLun,          // ��������(���)
        Country_DunHuang,        // �ػ�����(���)
        Country_Max,            

        // ְλ���� 
        Position_None = 0,       // ��ְλ
        Position_CaptorLeft,     // ������
        Position_CaptorRight,    // �����Ҳ�
        Position_CouncilorLeft,  // ��ة ̫ʦ
        Position_CouncilorRight, // ���� ̫ξ
        Position_General,        // �󽫾�
        Position_Queen,          // ����
        Position_King,           // ����
        Position_Max,          

        // Ȩ������
        Right_None                = 0,       // ��Ȩ��
        Right_Convene             = 0x1,     // �ټ�Ȩ
        Right_Placard             = 0x2,     // ����Ȩ
        Right_AppointKing         = 0x4,     // ��������Ȩ
        Right_AppointGeneral      = 0x8,     // �󽫾�����Ȩ
        Right_Raise               = 0x10,    // ļ��Ȩ
        Right_BanSpeak            = 0x20,    // ����Ȩ
        Right_Remit               = 0x40,    // ����Ȩ
        Right_Chain               = 0x80,    // ����Ȩ
        Right_QuestKing           = 0x100,   // ������������Ȩ   ( �������� ) ����
        Right_QuestGeneral        = 0x200,   // �󽫾���������Ȩ ( �������� ) ��̽
        Right_QuestCouncilorLeft  = 0x400,   // ��ة��������Ȩ   ( �������� ) ����
        Right_QuestCouncilorRight = 0x800,   // ���෢������Ȩ   ( ̽������ ) ����
        Right_WorldSpeak          = 0x1000,  // �������С���ȵ�Ȩ��
        Right_FlyToBorders        = 0x2000,  // �ɵ��������ֵص��Ȩ��
        Right_ChangeName          = 0x4000,  // �޸Ĺ������ֵ�Ȩ��
		Right_PK				  = 0x8000,	 // PK����PKֵ

		/*
		 *	Author 2013-1-4 zhuxincong
		 *	DESC: �޸ģ��߻�Ҫ�󣬹������ʺ󣬴󶼶�����ʹ���ټ�
		 */
        // ����Ȩ��
		Right_King = Right_PK | Right_ChangeName | Right_FlyToBorders | Right_WorldSpeak | Right_QuestCouncilorRight | Right_QuestCouncilorLeft | Right_QuestKing | Right_Chain | Right_Remit | Right_BanSpeak | Right_Raise | Right_Convene | Right_Placard | Right_AppointKing | Right_QuestGeneral,
        //Right_King = Right_PK | Right_Placard | Right_AppointKing | Right_Raise | Right_BanSpeak | Right_Remit | Right_Chain | Right_QuestKing | Right_WorldSpeak | Right_ChangeName | Right_Convene, 
        // ����Ȩ��
		//Right_Queen  = Right_Raise | Right_BanSpeak | Right_Remit | Right_Chain,
        Right_Queen = Right_WorldSpeak | Right_Convene,
        // �󽫾�Ȩ��
		//Right_General =  Right_PK | Right_AppointGeneral,
        Right_General = Right_PK | Right_AppointGeneral | Right_QuestGeneral | Right_Convene | Right_FlyToBorders | Right_WorldSpeak | Right_QuestKing,
        // ��ةȨ��
		//Right_CouncilorLeft =  Right_QuestGeneral | Right_QuestCouncilorRight,
        Right_CouncilorLeft = Right_QuestCouncilorLeft | Right_WorldSpeak,
        // ����Ȩ��
		//Right_CouncilorRight = Right_QuestKing | Right_QuestCouncilorLeft,
        Right_CouncilorRight = Right_QuestCouncilorRight | Right_WorldSpeak,
        // ������
		//Right_CaptorLeft = Right_PK,
        Right_CaptorLeft = Right_PK | Right_FlyToBorders | Right_WorldSpeak | Right_QuestCouncilorRight,
        // �����Ҳ�
		//Right_CaptorRight = Right_PK,
        Right_CaptorRight = Right_PK | Right_FlyToBorders | Right_WorldSpeak | Right_QuestCouncilorRight,

        ErrorID = 0,             // ��Ч�����ID
        NoneID  = 0,             // ��Ч�Ĺ���ID
        MaxNoticeLength  = 101,  // ������󳤶� ( 50���� )
        MaxNameLength    = 33,   // �����ִ��ĳ���
        MaxCountryLength = 5,    // �����������2����

        // ����ս������
        Battle_None = 0,
        Battle_King,             // ��������ս
        Battle_Dragon,           // ��������ս
        Battle_Rosefinch,        // ��ȸ����ս
        Battle_MaxType,          // ���ս������

        // ս��ʤ����ʽ
        BattleWin_FistTime = 0,  // ��һ������ɹ�
        BattleWin_Guard,         // �ػ��ɹ� ( �ػ���ʤ�� )
        BattleWin_Challenge,     // ��ս�ɹ� ( ��ս��ʤ�� )

        // �ػ�����
        Guard_None = 0,
        Guard_Dragon,           // �����ػ�
        Guard_Rosefinch,        // ��ȸ�ػ�
        Guard_Max,

        // ���ҳƺ�
        Title_None = 0,          // û��
        Title_King,              // ����
        Title_General,           // �󽫾�
        Title_Queen,             // ����
        Title_CouncilorLeft,     // ��ة
        Title_CouncilorRight,    // ����
        Title_CaptorLeft,        // ��
        Title_CaptorRight,       // �Ҳ�
        Title_KingGuard,         // ��������
        Title_Dragon,            // ����֮��
        Title_DragonGuard,       // �����ػ�
        Title_Rosefinch,         // ��ȸ֮��
        Title_RosefinchGuard,    // ��ȸ�ػ�
		Title_QueenMale,		 // ����
        Title_GuildMaster,       // ����
        Title_ViceMaster,        // ������
        Title_FamilyMaster,      // ���峤
        Title_GuildMember,       // ��ͨ����
		

        // �������������
        QuestType_None = 0,
        QuestType_King,             // �������� ����
        QuestType_General,          // �������� ��̽
        QuestType_CouncilorLeft,    // �������� ����
        QuestType_CouncilorRight,   // ̽������ ����
        QuestType_Max,

        MountType_None = 0,
        MountType_King,             // ��������( �������� )
        MountType_Guard,            // �ػ�����( ���� �� ��ȸ )

        // ������Դ����
        Resource_None = 0,
        Resource_Money,     

        MaxBordersFightCount = 10,  // �߾�ս����¼����
        UpdateSpaceTime = 5000,     // ���¼��ʱ��
        LoadSpaceTime = 600000,     // 10��������һ��
        SaveKeepTime = 500000,      // 10���ӱ���һ��
        UpdateWarKillTime = 10000,  // 10�����һ�ι�ս��Դ
        ////////////////////////////////////////////////////////////////
        OperateAdd = 1,             // +
        OperateSub,                 // -
        OperateSet,                 // =
        ////////////////////////////////////////////////////////////////
        UpdateMoney = 1,        // ���¹��ҽ�Ǯ
		UpdateTribute,			// ���¹��ҹ�Ʒ     
        CancelKingGuild,        // ɾ��������
        UpdateKingGuild,        // ���¹�����
        CancelDragonGuild,      // ɾ��������
        UpdateDragonGuild,      // ����������
        CancelRosefinchGuild,   // ɾ����ȸ��
        UpdateRosefinchGuild,   // ������ȸ��
        UpdateLastStrength,     // ��������ʵ��
        UpdateNowStrength,      // ���±���ʵ��
        UpdateChangeName,       // �����޸Ĺ������ֱ���
        UpdateSortIndex,        // ���¹�սɱ������

        //////////////////////////////////////////////////////////////////
        // ����ս��״̬
        BattleStatusInit = 0,
        BattleStatusSignUp,
        BattleStatusEnter,
        BattleStatusFight,
        BattleStatusEnd,

        BattleDefaultRelive   = 0,  // Ĭ�ϸ����
        BattleGuardRelive     = 2,  // �ط������
        BattleChallengeRelive = 3,  // ���������
        /////////////////////////////////////////////////////////////////////
        WarStatusInit = 0,      // ����ս��ʼ״̬
        WarStatusPrepare,       // ����սǰ30����
        WarStatusFight,         // ����ս��ʼ
        WarStatusEnd,           // ����ս����
        /////////////////////////////////////////////////////////////////////

		MaxCountryInfoLength = 256,
		MaxMsgCountryInfoSum = 20,//����һ������20�� ѭ����������
		MaxCountryInfoSum	 = 7,
    };

    inline bool CheckEnmityCountry( int nFirst, int nSecond )
    {
        if ( nFirst == Country_Init || nSecond == Country_Init )
        { return false; }

        return nFirst != nSecond; 
    }

    // ������������ ��� ���Ӧ�ķ���Ȩ��
    inline unsigned int GetQuestRightByType( unsigned char uchType )
    {
        unsigned int nRight = Right_None;
        switch ( uchType )
        {
        case QuestType_King:
            nRight = Right_QuestKing;
            break;
        case QuestType_General:
            nRight = Right_QuestGeneral;
            break;
        case QuestType_CouncilorLeft:
            nRight = Right_QuestCouncilorLeft;
            break;
        case QuestType_CouncilorRight:
            nRight = Right_QuestCouncilorRight;
            break;
        default:
            break;
        }

        return nRight;
    }

    // ͨ�������Ĺ�ְ�������Ҫ��Ȩ��
    inline unsigned int GetAppointRightByPosition( unsigned char uchPosition )
    {
        unsigned int nRight = Right_None;
        switch ( uchPosition )
        {
        case Position_General:
        case Position_CouncilorLeft:
        case Position_CouncilorRight:
            nRight = Right_AppointKing;
            break;;
        case Position_CaptorLeft:
        case Position_CaptorRight:
            nRight = Right_AppointGeneral;
            break;
        default:
            break;
        }

        return nRight;
    }

    // ֪ͨ����Ȩ���ж��Ƿ���������Ĺ�ְ
    inline bool IsCanAppointPosition( unsigned char uchPositon, unsigned int nRight )
    {
        switch ( nRight )
        {
        case Right_AppointKing:
            {
                switch ( uchPositon )
                {
                case Position_General:
                case Position_CouncilorLeft:
                case Position_CouncilorRight:
                    return true;
                    break;
                default:
                    break;
                }
            }
            break;
        case Right_AppointGeneral:
            {
                switch( uchPositon )
                {
                case Position_CaptorLeft:
                case Position_CaptorRight:
                    return true;
                    break;
                default:
                    break;
                }
            }
        default:
            break;
        }

        return false;
    }

    // ��ù�ְ��Ȩ��
    inline unsigned int GetRightByPosition( unsigned char uchPosition )
    {
        unsigned int nRight = Right_None;
        switch ( uchPosition )
        {
        case Position_King:
            nRight = Right_King;
            break;
        case Position_General:
            nRight = Right_General;
            break;
        case Position_CouncilorLeft:
            nRight = Right_CouncilorLeft;
            break;
        case Position_CouncilorRight:
            nRight = Right_CouncilorRight;
            break;
        case Position_CaptorLeft:
            nRight = Right_CaptorLeft;
            break;
        case Position_CaptorRight:
            nRight = Right_CaptorRight;
            break;
        default:
            break;
        }

        return nRight;
    }

    // ��ù�ְ�Ĺ��ҳƺ�
    inline unsigned char GetCountryTitleByPosition( unsigned char uchPosition )
    {
        unsigned char uchTitle = Title_None;
        switch ( uchPosition )
        {
        case Position_King:
            uchTitle = Title_King;
            break;
        case Position_General:
            uchTitle = Title_General;
            break;
        case Position_CouncilorLeft:
            uchTitle = Title_CouncilorLeft;
            break;
        case Position_CouncilorRight:
            uchTitle = Title_CouncilorRight;
            break;
        case Position_CaptorLeft:
            uchTitle = Title_CaptorLeft;
            break;
        case Position_CaptorRight:
            uchTitle = Title_CaptorRight;
            break;
        case Position_Queen:
            uchTitle = Title_Queen;
            break;
        default:
            break;
        }

        return uchTitle;
    }

    // �ɳƺŻ�ù���Ȩ��
    inline unsigned int GetCountryRightByTitle( unsigned short ustTitle )
    {
        unsigned int nRight = Right_None;
        switch ( ustTitle )
        {
        case Title_King:
            nRight = Right_King;
            break;
        case Title_General:
            nRight = Right_General;
            break;
        case Title_Queen:
		case Title_QueenMale:
            nRight = Right_Queen;
            break;
        case Title_CouncilorLeft:
            nRight = Right_CouncilorLeft;
            break;
        case Title_CouncilorRight:
            nRight = Right_CouncilorRight;
            break;
        case Title_CaptorLeft:
            nRight = Right_CaptorLeft;
            break;
        case Title_CaptorRight:
            nRight = Right_CaptorRight;
            break;
        default:
            break;
        }

        return nRight;
    }

    // �ɳƺŻ�ù���ְλ
    inline unsigned char GetCountryPositionByTitle( unsigned short ustTitle )
    {
        switch ( ustTitle )
        {
        case Title_King:
            return Position_King;
            break;
        case Title_General:
            return Position_General;
            break;
        case Title_Queen:
            return Position_Queen;
            break;
        case Title_CouncilorLeft:
            return Position_CouncilorLeft;
            break;
        case Title_CouncilorRight:
            return Position_CouncilorRight;
            break;
        case Title_CaptorLeft:
            return Position_CaptorLeft;
            break;
        case Title_CaptorRight:
            return Position_CaptorRight;
            break;
        default:
            break;
        }

        return Position_None;
    }
}


// ���ҹ�Ա����
class OfficialInfo
{
public:
    OfficialInfo() : dwPlayerID( CountryDefine::ErrorID ), uchPosition( CountryDefine::Position_None ), dwRight( CountryDefine::Right_None ),sexID(-1),faceID(-1),headerID(-1),professionID(-1)
    {
        memset( szPlayerName, 0, sizeof( szPlayerName ) );
    }

    void SetID( unsigned int nValue )    { dwPlayerID = nValue; }
    void SetName( const char* szName )   { strncpy_s( szPlayerName, sizeof( szPlayerName ), szName, sizeof( szPlayerName ) - 1 ); }
    void SetRight( unsigned int nValue ) { dwRight = nValue; } 
    void SetPosition( unsigned char uchValue ) { uchPosition = uchValue; }

    unsigned int GetID() const           { return dwPlayerID; }
    const char* GetName() const          { return szPlayerName; }
    unsigned int GetRight() const        { return dwRight; }
    unsigned char GetPosition() const    { return uchPosition; }

    bool HaveRight( unsigned int nValue ) { return ( dwRight & nValue ) != 0; }         // �Ƿ���Ȩ��
    bool HigherPosition( unsigned char uchValue ) { return uchPosition > uchValue; }    // �Ƿ��Ǹ��ߵ�ְλ
    bool IsEmpty() const { return dwPlayerID == CountryDefine::ErrorID; }               // �Ƿ�����ҵ��δ�ְλ
    void ClearOfficial()
    {
        dwPlayerID = CountryDefine::ErrorID;
        memset( szPlayerName, 0 , sizeof( szPlayerName ) );
        dwRight = CountryDefine::Right_None;

		faceID = 0;
		headerID = 0;
		sexID = 0;
		professionID = 0;
    }

	unsigned char GetSexID() const {return sexID;}
	void SetSexID(unsigned char value ){sexID = value;}

	unsigned short GetFaceID() const {return faceID;}
	void SetFaceID(unsigned short value ){faceID = value;}

	unsigned short GetHeaderID() const {return headerID;}
	void SetHeaderID(unsigned short value ){headerID = value;}

	unsigned short GetProfessionID() {return professionID;}
	void SetProfessionID(unsigned short value){professionID = value;}
private:
    unsigned int dwPlayerID;                                // ��ԱDBID
    char szPlayerName[ CountryDefine::MaxNameLength ];      // ��Ա����
    unsigned char uchPosition;                              // ��Աְλ
    unsigned int dwRight;                                   // ��Ӧ��Ȩ��
	unsigned short faceID;
	unsigned short headerID;
	unsigned char  sexID;
	unsigned short professionID;
};

// ʱ���ڲ�����������
class OperateTime
{
public:
    OperateTime() : n64StartTime( 0 ), uchOperateCount( 0 )
    {
    }

    unsigned char GetCount() const { return uchOperateCount; }
    void SetCount( unsigned char uchValue ) { uchOperateCount = uchValue; }
    __int64 GetStartTime() const { return n64StartTime; }

    void SetStartTime( __int64 nValue ) { n64StartTime = nValue; }
private:
    __int64 n64StartTime;           // ��ʼʱ��
    unsigned char uchOperateCount;  // �������� 
};

// ��������
class CountryData 
{
public:
	CountryData() : uchID( CountryDefine::Country_Init ), nMoney( 0 ), nTribute(InitTribute),
		nKingGuildID( CountryDefine::NoneID ), nDragonGuildID( CountryDefine::NoneID ), nRosefinchGuildID( CountryDefine::NoneID ), 
        nRecordTime( 0 ), uchChainCount( 0 ), uchPlacardCount( 0 ), uchConveneCount( 0 ), uchRaiseCount( 0 ), uchBanSpeakCount( 0 ), uchRemitCount( 0 ), nLastStrength( 0 ), nNowStrength( 0 ), bChangeName( false ),
        m_uchSorIndex( 0 ), m_nKillCount( 0 ), m_nDeathCount( 0 ) , nDoneQuestStrength(0) ,nCountryPlayerSum(0)
    {
        memset( szNotice, 0, sizeof( szNotice ) );
        memset( szName, 0, sizeof( szName ) );

        for ( int i = CountryDefine::Position_None; i < CountryDefine::Position_Max; ++i )
        {
            xOfficial[ i ].SetPosition( i );
        }

		for(int i =CountryDefine::QuestType_None;i<CountryDefine::QuestType_Max;++i)
		{
			nQuestSum[i] = 0;
		}
    }

    void SetID( unsigned char uchValue ) { uchID = uchValue; }
    void SetName( const char* szValue ) { strncpy_s( szName, sizeof( szName ), szValue, sizeof( szName ) - 1 ); } 
    void SetMoney( int nValue ) { if ( nValue < 0 ) { nValue = 0; } nMoney = nValue; }
	void SetTribute( int nValue) { if (nValue < 0 ) { nValue = 0; } nTribute = nValue; }
    void SetNotice( const char* szValue ) { strncpy_s( szNotice, sizeof( szNotice ), szValue, sizeof( szNotice ) - 1 ); }
    void SetKingGuild( unsigned int nValue ) { nKingGuildID = nValue; }
    void SetDragonGuild( unsigned int nValue ) { nDragonGuildID = nValue; }
    void SetRosefinchGuild( unsigned int nValue ) { nRosefinchGuildID = nValue; }
    void SetRecordTime( unsigned int nValue ) { nRecordTime = nValue; }
    void SetPlacardCount( unsigned char uchValue ) { uchPlacardCount = uchValue; }
    void SetConveneCount( unsigned char uchValue ) { uchConveneCount = uchValue; }
    void SetRaiseCount( unsigned char uchValue ) { uchRaiseCount = uchValue; }
    void SetBanSpeakCount( unsigned char uchValue ) { uchBanSpeakCount = uchValue; }
    void SetRemitCount( unsigned char uchValue ) { uchRemitCount = uchValue; }
    void SetChainCount( unsigned char uchValue ) { uchChainCount = uchValue; }
    void SetLastStrength( unsigned int nValue ) { nLastStrength = nValue; }
    void SetNowStrength( unsigned int nValue ) { nNowStrength = nValue; }
    void SetChangeName( bool bValue ) { bChangeName = bValue; }

    void SetSortIndex( unsigned char uchValue ) { m_uchSorIndex = uchValue; }
    void SetKillCount( unsigned int nValue ) { m_nKillCount = nValue; }
    void AddKillCount( unsigned int nValue ) { m_nKillCount += nValue; }
    void SetDeathCount( unsigned int nValue ) { m_nDeathCount = nValue; }
    void AddDeathCount( unsigned int nValue ) { m_nDeathCount += nValue; }

    unsigned char GetID() const { return uchID; }
    const char* GetName() const { return szName; }
    bool HaveName() const { return szName[0] != 0; }
	unsigned int GetMoney() const { return nMoney; }
	unsigned int GetTribute() const {return nTribute;}
    unsigned int GetKingGuild() const { return nKingGuildID; }
    const char* GetNotice() const { return szNotice; }
    unsigned int GetDragonGuild() const { return nDragonGuildID; }
    unsigned int GetRosefinchGuild() const { return nRosefinchGuildID; }

    unsigned int GetRecordTime() const { return nRecordTime; }
    unsigned char GetPlacardCount() const { return uchPlacardCount; }
    unsigned char GetConveneCount() const { return uchConveneCount; }
    unsigned char GetRaiseCount() const { return uchRaiseCount; }
    unsigned char GetBanSpeakCount() const { return uchBanSpeakCount; }
    unsigned char GetRemitCount() const { return uchRemitCount; }
    unsigned char GetChainCount() const { return uchChainCount; }
    unsigned int GetLastStrength() const { return nLastStrength; }
    unsigned int GetNowStrength() const { return nNowStrength; }
    bool GetChangeName() const { return bChangeName; }

    unsigned char GetSortIndex() const { return m_uchSorIndex; }
    unsigned int GetKillCount() const { return m_nKillCount; }
    unsigned int GetDeathCount() const { return m_nDeathCount; }

    bool AddOfficial( const OfficialInfo& xValue );
    OfficialInfo* GetOfficial( unsigned char uchPosition );
    OperateTime* GetQuestOperate( unsigned char uchType );

	
	void SetAddDoneQuestStrength(unsigned int Sum) {nDoneQuestStrength += Sum;}
	unsigned int GetDoneQuestAddStrength(){return nDoneQuestStrength;}
	void SetDoneQuestStrength(unsigned int Sum){nDoneQuestStrength = Sum;}

	void SetCountryPlayerSum(unsigned int Sum){ nCountryPlayerSum = Sum;}
	unsigned int GetCountryPlayerSum() {return nCountryPlayerSum;}

	void SetAddQuestCount(unsigned char QuestType);
	unsigned int GetAllQuestSum();
	unsigned int GetQuestSumByType(unsigned char QuestType);
	void SetQuestSumBytype(unsigned char QuestType,unsigned char num);
protected:
    unsigned char uchID;                                            // ����ID
    char szName[ CountryDefine::MaxCountryLength ];                 // ��������
    unsigned int nMoney;                                            // ������Դ
	unsigned int nTribute;											// ���ҹ�Ʒ
    unsigned int nKingGuildID;                                      // ����Ȩ�������Ĺ���
    char szNotice[ CountryDefine::MaxNoticeLength ];                // ���ҹ���
    OfficialInfo xOfficial[ CountryDefine::Position_Max ];          // ���ҵĹ�Ա�б�
    unsigned int nDragonGuildID;                                    // �����ػ����
    unsigned int nRosefinchGuildID;                                 // ��ȸ�ػ����

    unsigned int nRecordTime;                                       // ��¼����
    unsigned char uchPlacardCount;                                  // �������
    unsigned char uchConveneCount;                                  // �ټ�����
    unsigned char uchRaiseCount;                                    // ļ������
    unsigned char uchBanSpeakCount;                                 // ���Բ���
    unsigned char uchRemitCount;                                    // �������
    unsigned char uchChainCount;                                    // ����Ȩ��
    OperateTime xOperate[ CountryDefine::QuestType_Max ];           // ���񷢲�
    unsigned int nLastStrength;                                     // ���ܹ���ʵ��
    unsigned int nNowStrength;                                      // ���ܹ���ʵ��
    bool bChangeName;                                               // �Ƿ��Ѿ��ı��������
 
	unsigned char nQuestSum[CountryDefine::QuestType_Max];			// ���ҷ����������ܵļ��� ���ܵ�
	unsigned int  nDoneQuestStrength;								// �������������ӵĹ���ֵ ���ܵ�
	unsigned int  nCountryPlayerSum;								// ��ǰ�������� ���洢�����ݿ�

    // ��սɱ�˼�¼
    unsigned char m_uchSorIndex;    // ����
    unsigned int m_nKillCount;      // ɱ�˼���
    unsigned int m_nDeathCount;     // ��������                       
};
inline void CountryData::SetAddQuestCount(unsigned char QuestType)
{
	if(QuestType < CountryDefine::QuestType_None || QuestType >= CountryDefine::QuestType_Max)
		return;
	++nQuestSum[QuestType];
}
inline unsigned int CountryData::GetQuestSumByType(unsigned char QuestType)
{
	if(QuestType < CountryDefine::QuestType_None || QuestType >= CountryDefine::QuestType_Max)
		return -1;
	return nQuestSum[QuestType];
}
inline void CountryData::SetQuestSumBytype(unsigned char QuestType,unsigned char num)
{
	if(QuestType < CountryDefine::QuestType_None || QuestType >= CountryDefine::QuestType_Max)
		return ;
	nQuestSum[QuestType] = num;
}
inline unsigned int CountryData::GetAllQuestSum()
{
	unsigned int Sum =0;
	for(int i =CountryDefine::QuestType_None;i<CountryDefine::QuestType_Max;++i)
	{
		Sum += nQuestSum[i];
	}
	return Sum;
}
inline bool CountryData::AddOfficial( const OfficialInfo& xValue )
{
    if ( xValue.GetPosition() >= CountryDefine::Position_Max )
    { return false; }

    xOfficial[ xValue.GetPosition() ] = xValue; 
    return true;
}

inline OfficialInfo* CountryData::GetOfficial( unsigned char uchPosition )
{
    if ( uchPosition >= CountryDefine::Position_Max )
    { return NULL; }

    return &xOfficial[ uchPosition ];
}

inline OperateTime* CountryData::GetQuestOperate( unsigned char uchType )
{
    if ( uchType >= CountryDefine::QuestType_Max )
    { return NULL; }

    return &( xOperate[ uchType ] );
}


///////////////////////////////////////////////////////////////////////////////////////////////
#endif