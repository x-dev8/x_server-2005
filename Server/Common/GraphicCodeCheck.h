/********************************************************************
    Filename:     GraphicCodeCheck.h
    MaintenanceMan Mail: Luo_157@hotmail.com
    用于反脱机外挂的图形验证码识别
*********************************************************************/

#ifndef _H_GRAPHICCODECHECK_H
#define _H_GRAPHICCODECHECK_H

#include "MessageDefine.h"
#include "tstring.h"

using Common::_tstring;

enum ECheckState
{
    NOCHECK = 0,  // 在游戏未检测
    WAITCHECKING, // 等待检测
    WAITMAKEIMG,  // 等待图片生成（因为验证图片使用外部程序异步生成，因此需要等待一小段时间）
    CHECKERROR,   // 检测错误
};

struct SCheckState
{
    ECheckState state;
    uint32      dwFightStatusTime; // 战斗状态时间
    uint32      onMapTime;         // 在地图的时间 以后要做跨服同步
    uint32      m_dwSendCheckTime; // 图片发送到客户端时间
};

class CGraphicCodeCheck
{
public:
    CGraphicCodeCheck();
    virtual ~CGraphicCodeCheck();

public:
    bool MakeReqGraphicCode(MsgReqGraphicCode& msg);
    bool OnAckGraphicCode(Msg* pMsg);       // 返回是否通过验证

    bool IsCanMove();                       // 判断玩家是否通过了验证能否移动
    bool IsCanSkill();                      // 判断玩家是否通过了验证能否施放技能
    bool IsNeedSendReqMsg();                // 外部不停调用此函数得知是否需要发送验证请求
    void ChangeFightState(bool IsFighting); // 改变战斗状态
    void OnSkill();                         // 当玩家施放技能时则调用这个函数 只用于记录最后一次施放技能时间
    void LoadCheckState(const char* pPlayerName);
    void SaveCheckState();
    void ResetCheckState();


protected:
    void  IncrementCheckFailCount() { ++nCurrentCheckFailCount_;      }
    uint8 GetCheckFailCount()       { return nCurrentCheckFailCount_; }
    void  ResetCheckFailCount()     { nCurrentCheckFailCount_ = 0;    }
    void  KickCheck();

private:
    DWORD m_dwMakeImgTime;     // 开始生成图片时间
    DWORD m_dwStartFightTime;  // 战斗状态起始时间
    _tstring m_strlastCode;    // 最后一次发送的图形验证码
    _tstring m_strlastimgpath; // 图片文件路径

    bool m_bIsFighting;
    bool m_bUseSkill;

    SCheckState m_state;
    std::string strPlayerName; // 玩家名字

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
        ECD_UpdateTimeInterval = 1000, // 调用IsNeedSendReqMsg间隔时间
    };

public:
    GraphicCodeManager();
    ~GraphicCodeManager();
    
    void   SetOwner( GamePlayer* pGamePlayer ) { _pGamePlayer = pGamePlayer; }
    bool   IsNeedSendReqMsg();  // 是否有必要发验证码消息

    bool   MakeReqGraphicCode ( MsgReqGraphicCode& msg );  // 生成验证码消息
	bool   MakeReqGraphicCode ( MsgReqGraphicCode& msg, GraphicCodeMaker::SGraphicCode* pGraphicCode );  // 生成验证码消息
    bool   CheckAckGraphicCode( MsgAckGraphicCode* pMsg ); // 返回是否通过验证

    bool   MakeReqNumberCode ( MsgReqNumberCode& msg );    // 生成验证码消息
	bool   MakeReqNumberCode ( MsgReqNumberCode& msg, GraphicCodeMaker::SNumberCode* pNumberCode );    // 生成验证码消息
    bool   CheckAckNumberCode( MsgAckNumberCode* pMsg );   // 返回是否通过验证

    uint8  GetCheckFailCount(){ return _nCurrentCheckFailCount; } // 得到失败的次数
    void   SetFight( bool bFighting ){ _bIsFighting = bFighting;} // 改变战斗状态
    void   Update();                                              // Manager自身的Update
    void   ResetCheckState();                                     // 重置所有状态
    uint32 GetInFightTime() { return _state.dwFightStatusTime;}   // 得到在战斗状态的累积时间
    void   SetInFightTime( uint32 inFightTime ) { _state.dwFightStatusTime = inFightTime ; }
    
    void   OnEnterStage();
    void   OnLeaveStage();

    // For CharacterServer
    bool  IsHavePassCheck(){ return _bHaveCheck; }
    
private:
    SCheckState _state;
    int32       _index;
    uint8       _nCurrentCheckFailCount;
    uint32      _lastUpdateTime; // 最新一次调用Update时间    
    bool        _bIsFighting;    // 是否在战斗状态

    GamePlayer*  _pGamePlayer;
    // For CharacterServer
    bool         _bHaveCheck;    // 已经检测过
    bool         _bCalcOnMapTime;

	GraphicCodeMaker::SNumberCode*	_pNumberCode;	//最近一次图形验证码请求产生的数据
	GraphicCodeMaker::SGraphicCode*	_pGraphicCode;	//最近一次图形验证码请求产生的数据
};

//added by junyi.chen begin
#define theGraphicCodeCheckCommunication GetMyGraphicCodeCheckCommunication()
class GraphicCodeCheckCommunication
{
public:
	//验证类型
	enum ECheckType
	{
		ECT_GraphicCode,	//文字验证
		ECT_NumberCode,		//数字验证
	};

	//主逻辑线程发给验证码生成线程的验证请求消息
	struct SCheckReqMsg
	{
		uint32	nIDNeedToCheck;	//需要验证的玩家,ECT_GraphicCode时为AccountID,ECT_NumberCode时为PlayerDBID
		uint8	checkType;		//请求的验证类型
	};
	typedef std::vector<SCheckReqMsg>	CheckReqMsgQueue;
	typedef CheckReqMsgQueue::iterator	ItrCheckReqMsgQueue;

	//图形验证生成线程发回给主逻辑线程的消息
	struct SAckCheckMsg
	{
		uint32	nIDNeedToCheck;	//需要验证的玩家,ECT_GraphicCode时为AccountID,ECT_NumberCode时为PlayerDBID
		uint8	checkType;		//请求的验证类型
		void*	pData;			//生成的图形验证数据
	};
	typedef std::vector<SAckCheckMsg>	AckCheckMsgQueue;
	typedef AckCheckMsgQueue::iterator	ItrAckCheckMsgQueue;

	//图形验证码生产线程
	static void	CheckThreadFunc(void* pVoid);

	//发送图形验证码
	void Update();

	void AddCheckReqMsg(SCheckReqMsg &msg);
	void AddAckCheckMsg(SAckCheckMsg &msg);

private:
	//请求验证的消息队列
	CheckReqMsgQueue	_CheckReqMsgQueue;
	CSemiAutoIntLock	_lockCheckReqMsgQueue;

	//已生成的验证数据消息队列
	AckCheckMsgQueue	_AckCheckMsgQueue;
	CSemiAutoIntLock	_lockAckCheckMsgQueue;
};
GraphicCodeCheckCommunication& GetMyGraphicCodeCheckCommunication();
//end

#endif //_H_GRAPHICCODECHECK_H
