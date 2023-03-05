/********************************************************************
    Filename:     GraphicCodeCheck.h
    MaintenanceMan Mail: Luo_157@hotmail.com
    ���ڷ��ѻ���ҵ�ͼ����֤��ʶ��
*********************************************************************/

#ifndef _H_GRAPHICCODECHECK_H
#define _H_GRAPHICCODECHECK_H

#include "MessageDefine.h"
#include "tstring.h"

using Common::_tstring;

enum ECheckState
{
    NOCHECK = 0,  // ����Ϸδ���
    WAITCHECKING, // �ȴ����
    WAITMAKEIMG,  // �ȴ�ͼƬ���ɣ���Ϊ��֤ͼƬʹ���ⲿ�����첽���ɣ������Ҫ�ȴ�һС��ʱ�䣩
    CHECKERROR,   // ������
};

struct SCheckState
{
    ECheckState state;
    uint32      dwFightStatusTime; // ս��״̬ʱ��
    uint32      onMapTime;         // �ڵ�ͼ��ʱ�� �Ժ�Ҫ�����ͬ��
    uint32      m_dwSendCheckTime; // ͼƬ���͵��ͻ���ʱ��
};

class CGraphicCodeCheck
{
public:
    CGraphicCodeCheck();
    virtual ~CGraphicCodeCheck();

public:
    bool MakeReqGraphicCode(MsgReqGraphicCode& msg);
    bool OnAckGraphicCode(Msg* pMsg);       // �����Ƿ�ͨ����֤

    bool IsCanMove();                       // �ж�����Ƿ�ͨ������֤�ܷ��ƶ�
    bool IsCanSkill();                      // �ж�����Ƿ�ͨ������֤�ܷ�ʩ�ż���
    bool IsNeedSendReqMsg();                // �ⲿ��ͣ���ô˺�����֪�Ƿ���Ҫ������֤����
    void ChangeFightState(bool IsFighting); // �ı�ս��״̬
    void OnSkill();                         // �����ʩ�ż���ʱ������������ ֻ���ڼ�¼���һ��ʩ�ż���ʱ��
    void LoadCheckState(const char* pPlayerName);
    void SaveCheckState();
    void ResetCheckState();


protected:
    void  IncrementCheckFailCount() { ++nCurrentCheckFailCount_;      }
    uint8 GetCheckFailCount()       { return nCurrentCheckFailCount_; }
    void  ResetCheckFailCount()     { nCurrentCheckFailCount_ = 0;    }
    void  KickCheck();

private:
    DWORD m_dwMakeImgTime;     // ��ʼ����ͼƬʱ��
    DWORD m_dwStartFightTime;  // ս��״̬��ʼʱ��
    _tstring m_strlastCode;    // ���һ�η��͵�ͼ����֤��
    _tstring m_strlastimgpath; // ͼƬ�ļ�·��

    bool m_bIsFighting;
    bool m_bUseSkill;

    SCheckState m_state;
    std::string strPlayerName; // �������

public:
    unsigned char nCurrentCheckFailCount_;
};

//////////////////////////////////////////////////////////////////////////
class GraphicCodeMaker
{
public:
    enum EConstDefine
    {
        ECD_BistreamMaxSize = 960,
        ECD_GlyphBufMaxSize = 48,
        ECD_GlyphCount      = 500,
    };

    struct SGraphicCode
    {
        SGraphicCode()
        { Reset();}

        void Reset()
        {
            index = -1;
            memset( bitStream, 0, sizeof( bitStream ));
            memset( glyphBuf, 0, sizeof( glyphBuf ));
        }
        int32 index;
        uint8 bitStream[ECD_BistreamMaxSize];
        int8  glyphBuf[ECD_GlyphBufMaxSize];
    };

    struct SNumberCode
    {
        SNumberCode()
        { Reset();}

        void Reset()
        {
            index = -1;
            memset( bitStream, 0, sizeof( bitStream ));
        }
        int32 index;
        uint8 bitStream[ECD_BistreamMaxSize];
    };

public:
    bool          GenerateImages   ( int32 imageCount );
    uint32        GetGraphicCodeCount(){ return (uint32)_graphicCodes.size(); }
    SGraphicCode* GetGraphicCode( int32 index );

    bool          GenerateNumImages( int32 imageCount );
    uint32        GetNumberCodeCount(){ return (uint32)_numberCodes.size(); }
    SNumberCode*  GetNumberCode( int32 index );

private:
    typedef std::vector<SGraphicCode> GraphicCodeContainer;
    GraphicCodeContainer _graphicCodes;

    typedef std::vector<SNumberCode>  NumberCodeContainer;
    NumberCodeContainer _numberCodes;
};

inline 
GraphicCodeMaker::SGraphicCode* GraphicCodeMaker::GetGraphicCode( int32 index )
{
    if ( index < 0 || index >= (int32)_graphicCodes.size())
    { return NULL; }

    return &_graphicCodes[index];
}
inline 
GraphicCodeMaker::SNumberCode* GraphicCodeMaker::GetNumberCode( int32 index )
{
    if ( index < 0 || index >= (int32)_numberCodes.size())
    { return NULL; }

    return &_numberCodes[index];
}

GraphicCodeMaker& GetGraphicCodeMaker();

//////////////////////////////////////////////////////////////////////////
class GamePlayer;

class GraphicCodeManager
{
public:
    enum EConstDefine
    {
        ECD_UpdateTimeInterval = 1000, // ����IsNeedSendReqMsg���ʱ��
    };

public:
    GraphicCodeManager();
    ~GraphicCodeManager();
    
    void   SetOwner( GamePlayer* pGamePlayer ) { _pGamePlayer = pGamePlayer; }
    bool   IsNeedSendReqMsg();  // �Ƿ��б�Ҫ����֤����Ϣ

    bool   MakeReqGraphicCode ( MsgReqGraphicCode& msg );  // ������֤����Ϣ
	bool   MakeReqGraphicCode ( MsgReqGraphicCode& msg, GraphicCodeMaker::SGraphicCode* pGraphicCode );  // ������֤����Ϣ
    bool   CheckAckGraphicCode( MsgAckGraphicCode* pMsg ); // �����Ƿ�ͨ����֤

    bool   MakeReqNumberCode ( MsgReqNumberCode& msg );    // ������֤����Ϣ
	bool   MakeReqNumberCode ( MsgReqNumberCode& msg, GraphicCodeMaker::SNumberCode* pNumberCode );    // ������֤����Ϣ
    bool   CheckAckNumberCode( MsgAckNumberCode* pMsg );   // �����Ƿ�ͨ����֤

    uint8  GetCheckFailCount(){ return _nCurrentCheckFailCount; } // �õ�ʧ�ܵĴ���
    void   SetFight( bool bFighting ){ _bIsFighting = bFighting;} // �ı�ս��״̬
    void   Update();                                              // Manager�����Update
    void   ResetCheckState();                                     // ��������״̬
    uint32 GetInFightTime() { return _state.dwFightStatusTime;}   // �õ���ս��״̬���ۻ�ʱ��
    void   SetInFightTime( uint32 inFightTime ) { _state.dwFightStatusTime = inFightTime ; }
    
    void   OnEnterStage();
    void   OnLeaveStage();

    // For CharacterServer
    bool  IsHavePassCheck(){ return _bHaveCheck; }
    
private:
    SCheckState _state;
    int32       _index;
    uint8       _nCurrentCheckFailCount;
    uint32      _lastUpdateTime; // ����һ�ε���Updateʱ��    
    bool        _bIsFighting;    // �Ƿ���ս��״̬

    GamePlayer*  _pGamePlayer;
    // For CharacterServer
    bool         _bHaveCheck;    // �Ѿ�����
    bool         _bCalcOnMapTime;

	GraphicCodeMaker::SNumberCode*	_pNumberCode;	//���һ��ͼ����֤���������������
	GraphicCodeMaker::SGraphicCode*	_pGraphicCode;	//���һ��ͼ����֤���������������
};

//added by junyi.chen begin
#define theGraphicCodeCheckCommunication GetMyGraphicCodeCheckCommunication()
class GraphicCodeCheckCommunication
{
public:
	//��֤����
	enum ECheckType
	{
		ECT_GraphicCode,	//������֤
		ECT_NumberCode,		//������֤
	};

	//���߼��̷߳�����֤�������̵߳���֤������Ϣ
	struct SCheckReqMsg
	{
		uint32	nIDNeedToCheck;	//��Ҫ��֤�����,ECT_GraphicCodeʱΪAccountID,ECT_NumberCodeʱΪPlayerDBID
		uint8	checkType;		//�������֤����
	};
	typedef std::vector<SCheckReqMsg>	CheckReqMsgQueue;
	typedef CheckReqMsgQueue::iterator	ItrCheckReqMsgQueue;

	//ͼ����֤�����̷߳��ظ����߼��̵߳���Ϣ
	struct SAckCheckMsg
	{
		uint32	nIDNeedToCheck;	//��Ҫ��֤�����,ECT_GraphicCodeʱΪAccountID,ECT_NumberCodeʱΪPlayerDBID
		uint8	checkType;		//�������֤����
		void*	pData;			//���ɵ�ͼ����֤����
	};
	typedef std::vector<SAckCheckMsg>	AckCheckMsgQueue;
	typedef AckCheckMsgQueue::iterator	ItrAckCheckMsgQueue;

	//ͼ����֤�������߳�
	static void	CheckThreadFunc(void* pVoid);

	//����ͼ����֤��
	void Update();

	void AddCheckReqMsg(SCheckReqMsg &msg);
	void AddAckCheckMsg(SAckCheckMsg &msg);

private:
	//������֤����Ϣ����
	CheckReqMsgQueue	_CheckReqMsgQueue;
	CSemiAutoIntLock	_lockCheckReqMsgQueue;

	//�����ɵ���֤������Ϣ����
	AckCheckMsgQueue	_AckCheckMsgQueue;
	CSemiAutoIntLock	_lockAckCheckMsgQueue;
};
GraphicCodeCheckCommunication& GetMyGraphicCodeCheckCommunication();
//end

#endif //_H_GRAPHICCODECHECK_H
