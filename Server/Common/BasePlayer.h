/********************************************************************
    Filename:     BasePlayer.h
    MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GAMESERVER_BASEPLAYER_H__
#define __GAMESERVER_BASEPLAYER_H__

#include "BaseCharacter.h"
#include "ScriptVM.h"
#include "ItemBag.h"
#include "GraphicCodeCheck.h"
#include "Dxsdk/d3dx9math.h"

//#define PLAYERCHAR_MAX_VAR    4096

#define PLAYERCHAR_MAX_PET    4

#define CHECKMOVINGRATE 20

class BasePlayer;

extern void PlayerLogFunc(BasePlayer* pPlayer, const char* szFormat, ...);

class BasePlayer : public BaseCharacter
{ // ���������
//////////////////////////////////////////////////////////////////////////
// �ṹ��
protected:
    struct SPick
    {
        short stPickX;
        short stPickY;
        short stItemCharID;        
        bool  bSet; //�Ƿ���Ч
    };

//////////////////////////////////////////////////////////////////////////
// ����
public:    
    BasePlayer();
    virtual ~BasePlayer() {};

    // ����Ϣ����� ϵͳ�ұ߿����Ϣ
    virtual void ShowInfo( bool bTile, int type, const char* string, ... );
    virtual void ShowInfo( const char* string, bool bTile = false, int type = 282 );
    virtual void ShowInfo(  bool bTile, int type, unsigned short ustStringID, UnionParam* pParam = NULL, int nCount = 0 );
    static  void ShowInfoToWorld( bool bTile, int type, const char* string, ... );

    void SendChangeMapMessageToClient( DWORD dwMapId, short nTileX, short nTileY, BYTE byDir, float fDir ); // ��ͼ��ת
public:
    virtual bool ProcessMsg(Msg* pMsg);
    virtual void OnDeath(void);
    virtual bool IsCanSwitchStage(); 
    virtual Msg* FirstSightOnMe(char* szMsgBuffer, unsigned int nBuffSize);    
    virtual void SendVerifyPos(void); // ���ͽ���������Ϣ
    virtual void PlaySubSkill(short stSkillID, short* pSubSkill, short* pSubSkillLevel, int     * pSubcount);
    void SetDeathWaitForRelive( bool bFlag ) { m_bDeathAndWaitForRelive = bFlag; }
    virtual void TellClient( const char* string, ... );   
    virtual void TellClient( unsigned short ustStringID, UnionParam *pParam = NULL, int nCount = 0 );
    virtual void ShowFormatInfo( const char* szFormat, ... );
    virtual void ShowMsgBox( const char* string, ... );

    void Log     ( const char* szFormat, ...); // Log
    void DebugLog( const char* szFormat, ...); // Log

    void ShoppingLog( const char* szFormat, ...); // �̳ǹ�����־
    void DoAssaultMoving();                      // ���ڳ���ƶ�

    bool DoHitch( int nTrafficID, bool bBack, bool bGoOn );  // ���д���ƶ�
    void DoHitchMoving( int nTrafficID );        // ���д���ƶ�
    void CancelHitchMoving();                    // ��������ƶ�

    int  GetCurTrafficID();                      // ��ȡ��ǰ·�ߵ�ID    
    long TryRespondChangeStage();                // ������Ӧ�ͻ����г���ЧӦ

    void CheckCheatLog( const char* szFormat, ... );    // ���LOG

public:
    BOOL CheckMoving();                 // ����ƶ���Ϣ�ĺϷ���
    bool CheckPosRightful();            // ���λ�õ���ȷ��
    void CheckCredit();                 // �������ֵ�Ƿ���ȷ
    bool CheckMovingMsgSendTime( DWORD dwSendTime ); // ����ƶ���Ϣ�Ϸ�ʱ�����ȷ��
    void ResetCheckMoving();                         // ����Ҫ���Ե��ƶ���Ϣ(��ʼ��һ�ֵ��ƶ�����)
    void SendVerifyPos( float fx, float fy );        // ��������    
    bool IsNeedFixWorldCoordinate( int GridX, int nGridY); // �����µĸ������� �ж��Ƿ���Ҫ�����ͻ�����������ϵ���� float
    char* GetSessionKey(){ return _szSessionKey;}
    bool  SetSessionKey ( const char* szSessionKey );

    void IntonateInterrupt( int8 nType );           // �������

protected:
    // ��Ϣ
    void OnQueryMove();
    void OnQueryDisplayName(Msg *pMsg);
    void OnSeeAttack( Msg* pMsg );
    void OnWhoDie( Msg* pMsg );    
    void OnQueryAllGameProperty( Msg* pMsg );
    void OnAckAllGameProperty( Msg* pMsg );
    void OnGetLag();
    virtual void OnGetPlayerInfo(Msg*pMsg);     // �ͻ��˷�����������֪��Ī��npc������

    // ��������ƶ����߼�
    void OnMsgPlayerMovingPos( const Msg* pMsg );
    void OnMsgPlayerMovingPosToDir( const Msg* pMsg );
    void OnMsgPlayerPos( const Msg* pMsg );
    void OnMsgPlayerDir( const Msg* pMsg );
    void OnMsgPlayerPosAndDir( const Msg* pMsg );
    void OnMsgIntonateInterrupt( const Msg* pMsg );
    void OnMsgJump( const Msg* pMsg );
    void OnMsgDrawWeapon( const Msg* pMsg );
    void OnMsgDrawInWeapon( const Msg* pMsg );
    void OnMsgReadytoUseSpecialSkill();
    virtual void OnReqChangeDir( const Msg* pMsg );
    virtual void OnQueryCharAround( const Msg* pMsg );    
    virtual void OnPingMsg( const Msg* pMsg ); //�Կͻ��˷��͹�����PING��Ϣ�Ĵ���

    void SendRefreshChar();             //����
    void Dieing();                      // ����״̬ʱ�Ĵ������
    void LogOnlineInfo();

public:
    CGraphicCodeCheck m_graphiccodecheck;

//////////////////////////////////////////////////////////////////////////
// ��Ա����
protected:
    //D3DXVECTOR3 m_vLastSavedVerifyPos;         // ���һ�μ�¼�Ľ�������
    //D3DXVECTOR3 m_vLastSavedVerifyDir;         // ���һ�μ�¼�Ľ�������
    DWORD m_dwStartReadytoSendVerifyPosMsgTime;  // ��ʼ׼�����ͽ�����Ϣ��ʱ��
    DWORD m_dwLastSendHitchMoveMsgTime;          // �ϴη��ʹ���ƶ���Ϣ��ʱ��
    //DWORD m_dwLastSendPlayerMovingMsgTime;     // ������ƶ���Ϣ��ʱ��
    int   m_nCredit;                             // ��¼��ҵ�����ֵ
    bool  m_bPosDebugOpen;                       // �Լ���λ����ʾ����
    int   m_nKickCount;                          // ��¼�ߵĴ���
    DWORD m_dwEnterWorldClientTime;              // ��¼��ҽ�����Ϸ����Ŀͻ���ʱ��
    DWORD m_dwEnterWorldServerTime;              // ��¼��ҽ�����Ϸ����ķ����ʱ��
    DWORD m_dwClientLastSendMovingMsgTime;       // ��¼�ͻ�������͸��������ƶ���Ϣ��ʱ��
    DWORD m_dwClientLastSendMovingMsgServerTime; // �ͻ�������͸��������ƶ���Ϣ�ķ�����ʱ��
    bool  m_bHitchMoving;                        // ����ƶ�
    bool  m_bHitchBack;                          // �Ƿ�����·��˻���
    int   m_nTrafficID;                          // ���·�ߵ�ID
    DWORD m_dwRouteStep;                   
    short m_shCheckMovingCount;                  // ����ƶ���Ϣ�Ĵ���
    short m_shCheckMovingIndex;                  // ��Ȿ���ƶ�������
    bool  m_bAssaultMovingProcess;               // ��漼�ܵ����⴦��
    DWORD m_dwClientPassedTimePerCheck;          // ÿ�β���ʱ�� �ͻ����ۼƵľ�����ʱ�䳤��
    float m_fLastMoveSpeedPerCheck;              // ÿ�μ�Ᵽ�����һ�ε��ƶ��ٶȣ�Ϊ��� ���״̬���ٵ��ж�
    D3DXVECTOR3 m_vStartMovingPosPerCheck;       // ÿ�μ��ʱ��¼������
    D3DXVECTOR3 m_vMovingBufPerCheck;            // ÿ�ε��ƶ���������
    bool  m_bDeathAndWaitForRelive;              // �Ƿ��ɫ�Ѿ��������ȴ�����
    char  m_szLoginName[ dr_MaxNameString ];
    char  m_szLoginIP[ dr_MaxNameString ];
    char  m_cMoveSerial; //�ƶ����к�
    unsigned char m_ucCharStatus;
    bool          IsLoadAccountNameSucc;
    char          _szSessionKey[32+1];
};

//////////////////////////////////////////////////////////////////////////
// inline
inline bool BasePlayer::SetSessionKey ( const char* szSessionKey )
{
    if ( NULL == szSessionKey)
    { return false; }
    strncpy_s( _szSessionKey,sizeof(_szSessionKey),szSessionKey,sizeof(_szSessionKey)-1);
    return true;
}

#endif // __GAMESERVER_BASEPLAYER_H__
