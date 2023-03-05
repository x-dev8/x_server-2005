/********************************************************************
	Filename: 	PosChangePackage.h
	MaintenanceMan Mail: Luo_157@hotmail.com
*********************************************************************/

#ifndef __GATESERVER_POSCHANGE_PACKAGE_H__
#define __GATESERVER_POSCHANGE_PACKAGE_H__

#include "GlobalDef.h"
#include "MessageDefine.h"

struct SPosChangeInfo
{
    enum EOptimizeType
    { // �Ż�����
        Optimize_None = 0           , // û���Ż�
        Optimize_Pos                , // �����Ż�
        Optimize_Dir                , // �����Ż�
        Optimize_PosAndDir          , // ����ͳ����Ż�
        Optimize_MovingPos          , // �ƶ������Ż�
        Optimize_MovingPosAndDir    , // �ƶ�����ͳ����Ż�
        Optimize_ClosingToLockTarget, // ����Ŀ����Ż�
        Optimize_End,
    };

    SPosChangeInfo()
    {
        memset( this, 0, sizeof(*this) );
        chOptimize = Optimize_None;
    }

    GameObjectId      nID       ; // ����λ�ñ仯��Id
    GameObjectId      nTargetID ; // ������Ŀ���Id
    uint8			   nType     ; // ��ɴ���Ϣ��Դ��ϢЭ��
    D3DXVECTOR3		   vPos      ; // ����λ��
    D3DXVECTOR3		   vEndPos   ; // Ҫ����λ��
	char               chDirX    ; // X�ķ������
	char			   chDirY    ; // X�ķ������
	char			   chDirZ    ; // Y�ķ������
    uint8			   chOptimize; // �Ż�����
};

class CPosChangePackage
{
public:
    //����Ϣ���Ӧ������
    enum EMoveType
    {
        PACK_MSG_PLAYERMOVINGPOS             = 0,
        PACK_MSG_PLAYERMOVINGPOSANDDIR          ,
        PACK_MSG_PLAYERPOS                      ,
        PACK_MSG_PLAYERDIR                      ,
        PACK_MSG_PLAYERPOSANDDIR                ,
        PACK_MSG_PLAYERVERIFYPOS                ,
        PACK_MSG_UNPLAYERMOVINGTOPOS            ,
        PACK_MSG_UNPLAYERVERIFYPOS              ,
        PACK_MSG_UNPLAYERCLOSINGTOLOCKTARGET    ,
    };

    CPosChangePackage();
    virtual ~CPosChangePackage();

    bool            MakePackMsg( MsgPosChange& msg ); // ����һ����Ϣ��
    bool            LoadPackMsg( MsgPosChange& msg ); // ����һ����Ϣ��

    bool            PushPosChangeInfo( const SPosChangeInfo& info );
    SPosChangeInfo* PopPosChangeInfo();

    void            SetMaxSize(unsigned int nSize);
    void            Clear();

protected:
    std::vector<SPosChangeInfo> m_msglist;
    unsigned int                m_nMaxSize;

private:
#pragma pack(push, 1)
    struct SMoveUnitHead
    {
        GameObjectId shID;
        uint8  chType;
        uint8  chOptimize;
    };

    struct tagPACK_MSG_PLAYERMOVINGPOS
    { // �ƶ���λ��
        D3DXVECTOR3 vPos;
    };

    struct tagPACK_MSG_PLAYERMOVINGPOSANDDIR
    { // �ƶ���λ�� ����
        char chDirX;
        char chDirY;
        char chDirZ;
        D3DXVECTOR3 vPos;
    };

    struct tagPACK_MSG_PLAYERPOS
    { // ��ֹ��λ��
        D3DXVECTOR3 vPos;
    };

    struct tagPACK_MSG_PLAYERDIR
    { // ��ֹ�ķ���
        char chDirX;
        char chDirY;
        char chDirZ;
    };

    struct tagPACK_MSG_PLAYERPOSANDDIR
    { // ��ֹ��λ�úͷ���
        char chDirX;
        char chDirY;
        char chDirZ;
        D3DXVECTOR3 vPos;
    };

    struct tagPACK_MSG_PLAYERVERIFYPOS
    { // ��֤λ��
        D3DXVECTOR3 vPos;
    };

    struct tagPACK_MSG_UNPLAYERMOVINGTOPOS
    { // ����ҿ�ʼ�ͽ���λ��
	    D3DXVECTOR3 vStartPos;
	    D3DXVECTOR3 vEndPos;
    };

    struct tagPACK_MSG_UNPLAYERVERIFYPOS
    { // �������֤λ���뷽��
        char chDirX;
        char chDirY;
        char chDirZ;
        D3DXVECTOR3 vPos;
    };
    struct tagPACK_MSG_UNPLAYERCLOSINGTOLOCKTARGET
    { // ����ҽ�������Ŀ��
        D3DXVECTOR3   vPos;
        GameObjectId shTargetID;
    };
#pragma pack(pop)
};

#endif // __GATESERVER_POSCHANGE_PACKAGE_H__
