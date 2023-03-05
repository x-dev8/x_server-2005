#include "GraphicCodeCheck.h"
#include "ShareData.h"
#include "CheckStateHandle.h"
#include "FuncPerformanceLog.h"
#include "ErrorLog.h"
#include "Configure.h"
#include "validate.h"
#include "ResourcePath.h"
#include "MeRTLibsServer.h"
#include "GamePlayer.h"

//const DWORD WAITCHECKINGTIME = 1000*60;          // 客户端允许十分钟内应答
//const DWORD SENDREQDELAYRANDMAXTIME = 1000*60*2; // 每次发送校验最大间隔时间
//const DWORD SENDREQDELAYRANDMINTIME = 1000*60*1; // 每次发送校验最小间隔时间

const DWORD WAITMAKEIMGTIME = 3000;                // 等待外部程序异步生成图片时间

#pragma warning( push )
#pragma warning( disable : 4311 )

//调用外部图片生成程序
bool ExecuteMakeImg(const char* pCode, const char* pFilePath)
{
    try
    {
        if (pCode == NULL || pFilePath == NULL)
        {
            return false;
        }

        _tstring strParam;
        strParam.Format("%s %s", pCode, pFilePath);

        //STARTUPINFO si;
        //PROCESS_INFORMATION pi;
        //ZeroMemory( &si, sizeof(si) );
        //si.cb = sizeof(si);
        //ZeroMemory( &pi, sizeof(pi) );

        _mkdir(g_Cfg.szTmpImageFolder);
        HINSTANCE hRet = ::ShellExecuteA(NULL, "open", g_Cfg.szCreateImgExePath, _tANSICHAR(strParam), NULL, NULL);
        //if (CreateProcess(NULL, // No module name (use command line). 
        //    (LPSTR)strPath.c_str(),  // Command line. 
        //    NULL,             // Process handle not inheritable. 
        //    NULL,             // Thread handle not inheritable. 
        //    FALSE,            // Set handle inheritance to FALSE. 
        //    0,                // No creation flags. 
        //    NULL,             // Use parent's environment block. 
        //    NULL,             // Use parent's starting directory. 
        //    &si,              // Pointer to STARTUPINFO structure.
        //    &pi)             // Pointer to PROCESS_INFORMATION structure.
        //)
        //{
        //    return true;
        //}

        //MSDN上规定ShellExecuteA返回值小于32则视为失败
        if (reinterpret_cast<int>(hRet) < 32)
        {
			GetErrorLog()->logString("Execute valedate cold program %s %s failed,errcode:%d", g_Cfg.szCreateImgExePath, _tANSICHAR(strParam), reinterpret_cast<int>(hRet));
            return false;
        }
        else
        {
            return true;
        }
    }
    catch (...)
    {
        return false;
    }
}

CGraphicCodeCheck::CGraphicCodeCheck() : m_dwStartFightTime(0), m_bIsFighting( false ), m_bUseSkill(false),
                                         nCurrentCheckFailCount_(0)
{
    m_state.state             = NOCHECK;
    m_state.dwFightStatusTime = 0;
    m_state.m_dwSendCheckTime = 0;
}

CGraphicCodeCheck::~CGraphicCodeCheck()
{
}

bool CGraphicCodeCheck::MakeReqGraphicCode(MsgReqGraphicCode &msg)
{
    //if (m_strlastimgpath.empty() || this->m_strlastCode.empty())
    //{
    //    m_state.state = CHECKERROR;
    //    return false;
    //}

    //std::fstream imgfile(_tUNICODECHAR(m_strlastimgpath), std::ios::in | std::ios::binary);
    //if (!imgfile.is_open())
    //{
    //    //如果服务器自身生成图片错误，则状态初始化
    //    m_state.state = NOCHECK;
    //    return false;
    //}

    //imgfile.seekg(0, std::ios::end);
    //unsigned int nSize = imgfile.tellg();
    //imgfile.seekg(0, std::ios::beg);

    //msg.nImgBuffSize = nSize;
    //imgfile.read(msg.szImgBuf, nSize);
    //imgfile.close();
    //remove(_tANSICHAR(m_strlastimgpath));
    //{
    //    m_state.m_dwSendCheckTime = HQ_TimeGetTime();
    //    msg.dwTime = g_Cfg.dwPlayerApplyTime;
    //}
    //msg.CalcLength();

    //m_state.state = WAITCHECKING;
    return true;
}

bool CGraphicCodeCheck::OnAckGraphicCode(Msg* pMsg)
{
    //if (pMsg == NULL)
    //{
    //    m_state.state = CHECKERROR;
    //    return false;
    //}

    //MsgAckGraphicCode* pAck = static_cast<MsgAckGraphicCode*>(pMsg);
    //int nLength = strlen(pAck->szBuffer);
    //if (nLength > 0 && nLength < sizeof(pAck->szBuffer) && this->m_strlastCode == pAck->szBuffer)
    //{
    //    ResetCheckState();
    //    return true;
    //}

    //m_strlastCode.clear();
    ////发送空数据，更换图片
    //m_state.state = CHECKERROR;

    //IncrementCheckFailCount();
    //KickCheck();
    return false;
}

void CGraphicCodeCheck::KickCheck()
{
    if ( 0 == g_Cfg.nMaxCheckFailCount )
    { // 如果为0, 表示没有次数限制
        ResetCheckFailCount();
        return;
    }

    if ( GetCheckFailCount() >= g_Cfg.nMaxCheckFailCount )
    { // 踢掉玩家
        GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByName(strPlayerName);
        if ( pPlayer )
        {
            pPlayer->Log( "Exit By KickCheck" );
            pPlayer->ExitWorld(__FUNCTION__, __FILE__, __LINE__);
        }

        ResetCheckFailCount();
    }
}

bool CGraphicCodeCheck::IsCanMove()
{
    //超时的话不允许
    if ( m_state.m_dwSendCheckTime != 0 && GameTime::IsPassCurrentTime( m_state.m_dwSendCheckTime, g_Cfg.dwPlayerApplyTime ) )
    {
        KickCheck();
        return false;
    }

    return true;
}

bool CGraphicCodeCheck::IsCanSkill()
{
    //和能否移动判定一样
    return IsCanMove();
}

bool CGraphicCodeCheck::IsNeedSendReqMsg()
{
    switch (m_state.state)
    {
    case CHECKERROR:
        {
            //避免请求过多生成图片过快
            if ( !GameTime::IsPassCurrentTime( m_dwMakeImgTime, WAITMAKEIMGTIME ) )
            { return false; }

            //生成一个10000-99999之间的五位数验证码
            int nCode = theRand.rand32()%89999+10000;
            m_strlastCode.Format("%d", nCode);

            m_strlastimgpath.Format("%s/%d.png", g_Cfg.szCreateImgExePath, nCode);

            //生成图片
            m_state.state = WAITMAKEIMG;
            m_dwMakeImgTime = HQ_TimeGetTime();
            if (!ExecuteMakeImg(m_strlastCode.c_str(), m_strlastimgpath.c_str()))
            {
                m_state.state = NOCHECK;
                m_state.dwFightStatusTime = 0;
                m_state.m_dwSendCheckTime = 0;

                return false;
            }
            return false;
        }
        break;
    case WAITMAKEIMG:
        {
            //等待图片生成时间已到
            if ( GameTime::IsPassCurrentTime( m_dwMakeImgTime, WAITMAKEIMGTIME ) )
            {
                return true;
            }
        }
        break;

    //还未检测，需要判断战斗状态时间是否已达到检测标准
    case NOCHECK:
        {
            // DWORD dwTime = theRand.rand32()%(SENDREQDELAYRANDMAXTIME-SENDREQDELAYRANDMINTIME)+SENDREQDELAYRANDMINTIME;
            if ( 0 == g_Cfg.dwCheckWhenFightingTime )
            {
                ResetCheckState();
                return false;
            }

            if (m_state.dwFightStatusTime >= g_Cfg.dwCheckWhenFightingTime)
            {
                //生成一个10000-99999之间的五位数验证码
                int nCode = theRand.rand32()%89999+10000;
                m_strlastCode.Format("%d", nCode);

                m_strlastimgpath = g_Cfg.szCreateImgExePath;
                m_strlastimgpath.Format("%s/%d.png", g_Cfg.szTmpImageFolder, nCode);

                //生成图片
                m_state.state = WAITMAKEIMG;
                m_dwMakeImgTime = HQ_TimeGetTime();
                if (!ExecuteMakeImg(m_strlastCode.c_str(), m_strlastimgpath.c_str()))
                {
                    m_state.state = NOCHECK;
                    m_state.dwFightStatusTime = 0;
                    m_state.m_dwSendCheckTime = 0;
                }
            }
        }
        break;

    case WAITCHECKING:
        {
            return false;
        }
        break;

    default:
        return false;
        break;
    }
    return false;
}
    
void CGraphicCodeCheck::ChangeFightState(bool IsFighting)
{
    if (!m_bIsFighting && IsFighting)
    { // 如果开始新一轮的战斗 开始设置起始时间
        this->m_dwStartFightTime = HQ_TimeGetTime();
        m_bIsFighting = true;
    }
    else if (m_bIsFighting && !IsFighting)
    { // 战斗结束了 
        //如果在战斗状态过程中施放了技能，这次战斗状态的持续时间才被算入需要检测的时间
#ifdef USESKILLCALC
        if (m_bUseSkill)
        {   
            m_bUseSkill = false;
            m_state.dwFightStatusTime += (HQ_TimeGetTime() - m_dwStartFightTime);
        }
#else
        m_state.dwFightStatusTime += (HQ_TimeGetTime() - m_dwStartFightTime);
        m_bUseSkill = false;
#endif
        m_bIsFighting = false;
    }
}

void CGraphicCodeCheck::OnSkill()
{
    m_bUseSkill = true;
}

void CGraphicCodeCheck::LoadCheckState(const char* pPlayerName)
{
    if (pPlayerName == NULL)
    {
        return;
    }
    GetCheckStateHandle().LoadCheckState(pPlayerName, m_state);
    strPlayerName = pPlayerName;

    if (this->m_state.state == WAITCHECKING)
    {
        m_state.state = CHECKERROR;
    }
}

void CGraphicCodeCheck::SaveCheckState()
{
    GetCheckStateHandle().SaveCheckState(strPlayerName.c_str(), m_state);
}

void CGraphicCodeCheck::ResetCheckState()
{
    m_strlastCode.clear();
    //战斗时间清零
    m_state.state = NOCHECK;
    m_state.dwFightStatusTime = 0;
    m_state.m_dwSendCheckTime = 0;
    m_state.onMapTime         = 0;
}

//////////////////////////////////////////////////////////////////////////
GraphicCodeMaker& GetGraphicCodeMaker()
{
    static GraphicCodeMaker instance;
    return instance;
}

GraphicCodeCheckCommunication& GetMyGraphicCodeCheckCommunication()
{
	static GraphicCodeCheckCommunication instance;
	return instance;
}

#define random(x) (theRand.rand32() % (x))
#define rangeRandom(x,y) ((x) + theRand.rand32()%((y+1)-(x))) 

bool GraphicCodeMaker::GenerateImages( int32 imageCount )
{
    _graphicCodes.clear();

    SGraphicCode graphicCode;
    for ( int i=0; i<imageCount; ++i )
    {
        graphicCode.Reset();

        //for ( int i=0 ; i<ECD_NumberCount; ++i )
        //{ graphicCode.number[i] = theRand.rand32() % 10;}
        // 生成图片Buffer
        //if(!validateGlyph( graphicCode.number, GRAPHICCODE_BACKGROUNDDIR, GRAPHICCODE_NUMBERPICDIR, graphicCode.bitStream ))
        //{ return false; }
        
        graphicCode.index = random(6);
        if(!validateGlyph( GRAPHICCODE_BACKGROUNDDIR, graphicCode.index, graphicCode.bitStream, graphicCode.glyphBuf ))
        { return false; }

        if ( strlen(graphicCode.glyphBuf) == 0 )
        { 
            LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "validateGlyph 居然有空字符串生成" );
            continue; 
        }
        
        _graphicCodes.push_back( graphicCode );
    }
    return true;
}

bool GraphicCodeMaker::GenerateNumImages( int32 imageCount )
{
    _numberCodes.clear();
    SNumberCode numberCode;
    for ( int i=0; i<imageCount; ++i )
    {
        numberCode.Reset();

        numberCode.index = random(10000);
        if(!validate( numberCode.index, GRAPHICCODE_BACKGROUNDDIR, GRAPHICCODE_NUMBERPICDIR, numberCode.bitStream ))
        { return false; }

        _numberCodes.push_back( numberCode );
    }
    return true;
}

//////////////////////////////////////////////////////////////////////////
GraphicCodeManager::GraphicCodeManager() : _lastUpdateTime( 0 ), _bIsFighting( false ),_pGamePlayer( NULL )
{   
    _bHaveCheck = false;
	_pNumberCode			 = NULL;
	_pGraphicCode			 = NULL;
    ResetCheckState();
}

bool GraphicCodeManager::IsNeedSendReqMsg()
{
    switch ( _state.state)
    {
    case CHECKERROR:
        {
            if ( g_Cfg.nMaxCheckFailCount>0 && _nCurrentCheckFailCount>=g_Cfg.nMaxCheckFailCount  )
            { return false; } // 失败次数已够,会踢,不要再发验证码

            return true;
        }
        break;    
    case NOCHECK:
        { //还未检测 需要判断战斗状态时间是否已达到检测标准
            if ( g_Cfg.dwServerID == CHARACTERSERVERID )
            { // 角色服务器
                if ( !_bHaveCheck)
                { return true; }
            }
            else
            { // 游戏服务器
                // 累计的时间已经大于规定的时间
                if ( g_Cfg.nMaxCheckFailCount>0 && _nCurrentCheckFailCount>=g_Cfg.nMaxCheckFailCount )
                { return false;} // 失败次数已够,会踢,不要再发验证码

                if ( g_Cfg.dwCheckWhenFightingTime>0 && _state.dwFightStatusTime >= g_Cfg.dwCheckWhenFightingTime )
                { return true;}

                if ( g_Cfg.onMapLimitTime>0 && _state.onMapTime!=0 && _state.onMapTime >= g_Cfg.onMapLimitTime )
                { return true; }
            }
        }
        break;
    case WAITCHECKING:
        { return false;}
        break;
    }
    return false;
}

bool GraphicCodeManager::MakeReqGraphicCode( MsgReqGraphicCode& msg )
{
    int nIndexCount = GetGraphicCodeMaker().GetGraphicCodeCount();
    if ( nIndexCount == 0)
    { return false;}

    _index =  theRand.rand32() % nIndexCount;

    GraphicCodeMaker::SGraphicCode* pGraphicCode = GetGraphicCodeMaker().GetGraphicCode( _index );
    if ( pGraphicCode == NULL )
    { return false; }
    
    memcpy( msg.bitsstream, pGraphicCode->bitStream, sizeof( msg.bitsstream) );
    memcpy( msg.glyphBuf,   pGraphicCode->glyphBuf,  sizeof( msg.glyphBuf  ) );
    msg.dwTime               = g_Cfg.dwPlayerApplyTime;
    _state.state             = WAITCHECKING;
    _state.m_dwSendCheckTime = HQ_TimeGetTime();
    return true;
}

bool GraphicCodeManager::MakeReqGraphicCode( MsgReqGraphicCode& msg, GraphicCodeMaker::SGraphicCode* pGraphicCode )
{
	delete _pGraphicCode;
	_pGraphicCode = pGraphicCode;
	memcpy( msg.bitsstream, pGraphicCode->bitStream, sizeof( msg.bitsstream) );
	memcpy( msg.glyphBuf,   pGraphicCode->glyphBuf,  sizeof( msg.glyphBuf  ) );
	msg.dwTime               = g_Cfg.dwPlayerApplyTime;
	_state.state             = WAITCHECKING;
	_state.m_dwSendCheckTime = HQ_TimeGetTime();
	return true;
}

bool GraphicCodeManager::CheckAckGraphicCode( MsgAckGraphicCode* pMsg )
{
//     if ( _index < 0)
//     { return false; }
// 
//     GraphicCodeMaker::SGraphicCode* pGraphicCode = GetGraphicCodeMaker().GetGraphicCode( _index );
//     if ( pGraphicCode == NULL )
//     { return false; }
	if ( NULL == _pGraphicCode )
		return false;
    if ( _pGraphicCode->index == pMsg->index )
    { 
        if ( g_Cfg.dwServerID == CHARACTERSERVERID )
        { // 角色服务器
            _bHaveCheck = true;
        }
        else
        { // 游戏服务器
            ResetCheckState();
        }
        return true;
    }

    _index = -1;
    _state.state = CHECKERROR;
    ++_nCurrentCheckFailCount;
    return false;
}

bool GraphicCodeManager::MakeReqNumberCode( MsgReqNumberCode& msg )
{
    int nIndexCount = GetGraphicCodeMaker().GetNumberCodeCount();
    if ( nIndexCount == 0)
    { return false;}

    _index =  theRand.rand32() % nIndexCount;

    GraphicCodeMaker::SNumberCode* pNumberCode = GetGraphicCodeMaker().GetNumberCode( _index );
    if ( pNumberCode == NULL )
    { return false; }

    memcpy( msg.bitsstream, pNumberCode->bitStream, sizeof( msg.bitsstream) );
    msg.dwTime               = g_Cfg.dwPlayerApplyTime;
    _state.state             = WAITCHECKING;
    _state.m_dwSendCheckTime = HQ_TimeGetTime();
    return true;
}

bool GraphicCodeManager::MakeReqNumberCode( MsgReqNumberCode& msg, GraphicCodeMaker::SNumberCode* pNumberCode )
{
	delete _pNumberCode;
	_pNumberCode = pNumberCode;
	memcpy( msg.bitsstream, pNumberCode->bitStream, sizeof( msg.bitsstream) );
	msg.dwTime               = g_Cfg.dwPlayerApplyTime;
	_state.state             = WAITCHECKING;
	_state.m_dwSendCheckTime = HQ_TimeGetTime();
	return true;
}

bool GraphicCodeManager::CheckAckNumberCode( MsgAckNumberCode* pMsg )
{
//     if ( _index < 0)
//     { return false; }
// 
//     GraphicCodeMaker::SNumberCode* pNumberCode = GetGraphicCodeMaker().GetNumberCode( _index );
//     if ( pNumberCode == NULL )
//     { return false; }
	if ( NULL == _pNumberCode )
		return false;
    if ( _pNumberCode->index == pMsg->index )
    { 
        if ( g_Cfg.dwServerID == CHARACTERSERVERID )
        { // 角色服务器
            _bHaveCheck = true;
        }
        else
        { // 游戏服务器
            ResetCheckState();
        }
        return true;
    }

    _index = -1;
    _state.state = CHECKERROR;
    ++_nCurrentCheckFailCount;
    return false;
}

void GraphicCodeManager::Update()
{    
    // 控制更新频率
    if ( _lastUpdateTime == 0)
    { _lastUpdateTime = HQ_TimeGetTime(); }

    if ( !GameTime::IsPassCurrentTime( _lastUpdateTime, ECD_UpdateTimeInterval ) )
    { return; }

    _lastUpdateTime = HQ_TimeGetTime();

    // 客户端响应时间
    if ( _state.m_dwSendCheckTime != 0)
    {
        if ( GameTime::IsPassCurrentTime( _state.m_dwSendCheckTime, g_Cfg.dwPlayerApplyTime ) )
        { 
            _pGamePlayer->ProcessBeBlock( MsgNotifyBeKick::EKT_GraphicCodeTimeOut, 0 );
            _state.m_dwSendCheckTime = 0;
            return;
        }
    }
    
    if ( g_Cfg.dwServerID == CHARACTERSERVERID)
    { return; }

     // For GameServer
    if ( _pGamePlayer->GetBuffManager()->IsDisableCallGraphic() )
    { return; }

    if ( _pGamePlayer->IsBeginVigorOfflineFight() )
    { return; }

    // 累加时间 死亡状态不累加
    if ( _bIsFighting )
    { _state.dwFightStatusTime += ECD_UpdateTimeInterval; }

    if ( _bCalcOnMapTime )
    { _state.onMapTime += ECD_UpdateTimeInterval; }

    // 是否需要发验证码
    if ( IsNeedSendReqMsg() )
    {
        if ( !_pGamePlayer->IsDead() )
        {
//             MsgReqGraphicCode msg;
//             bool bResult = MakeReqGraphicCode(msg);
//             if ( bResult )
//             { GettheServer().SendMsgToSingle(&msg, _pGamePlayer);}
			GraphicCodeCheckCommunication::SCheckReqMsg msg;
			msg.checkType = GraphicCodeCheckCommunication::ECT_GraphicCode;
			msg.nIDNeedToCheck = _pGamePlayer->GetDBCharacterID();
			theGraphicCodeCheckCommunication.AddCheckReqMsg(msg);
        }
    }
}

void GraphicCodeManager::ResetCheckState()
{
    _state.state = NOCHECK;
    _state.dwFightStatusTime = 0;
    _state.m_dwSendCheckTime = 0;
    _state.onMapTime         = 0;
    _index                   = -1;
    _nCurrentCheckFailCount  = 0;
    _bCalcOnMapTime          = false;

	delete _pNumberCode;
	_pNumberCode			 = NULL;
	delete _pGraphicCode;
	_pGraphicCode			 = NULL;
}

#define NEEDCALC_MAPID 3
void GraphicCodeManager::OnEnterStage()
{ // 此版本只为淮南做在线时间
    if ( _pGamePlayer == NULL )
    { return; }

    uint32 mapId = EctypeId2MapId( _pGamePlayer->GetMapID() );
    if ( mapId == NEEDCALC_MAPID )
    {
        _bCalcOnMapTime = true;
    }
}

void GraphicCodeManager::OnLeaveStage()
{
    _bCalcOnMapTime = false;
}

GraphicCodeManager::~GraphicCodeManager()
{
	delete _pNumberCode;
	delete _pGraphicCode;
}

#pragma warning( pop )

void GraphicCodeCheckCommunication::CheckThreadFunc( void* pVoid )
{
	GraphicCodeCheckCommunication* pManager = static_cast<GraphicCodeCheckCommunication*>(pVoid);
	CheckReqMsgQueue tempQueue;
	{
		CSALocker lock(pManager->_lockCheckReqMsgQueue);
		tempQueue = pManager->_CheckReqMsgQueue;
		pManager->_CheckReqMsgQueue.clear();
	}

	ItrCheckReqMsgQueue itr = tempQueue.begin();
	for ( ; itr != tempQueue.end(); ++itr )
	{
		if ( itr->checkType == ECT_GraphicCode )
		{
			GraphicCodeMaker::SGraphicCode *graphicCode = new GraphicCodeMaker::SGraphicCode;
			graphicCode->index = random(6);
			if( validateGlyph( GRAPHICCODE_BACKGROUNDDIR, graphicCode->index, graphicCode->bitStream, graphicCode->glyphBuf ) )
			{
				if ( strlen(graphicCode->glyphBuf) == 0 )
				{
					LOG_MESSAGE( SYSTEMOBJECT, LOG_PRIORITY_WARNING, "validateGlyph 居然有空字符串生成" );
					delete graphicCode;
				}
				else
				{
					SAckCheckMsg ackMsg;
					ackMsg.checkType = itr->checkType;
					ackMsg.nIDNeedToCheck = itr->nIDNeedToCheck;
					ackMsg.pData = graphicCode;
					pManager->AddAckCheckMsg(ackMsg);
				}
			}
			else
			{
				delete graphicCode;
			}
		}
		else if ( itr->checkType == ECT_NumberCode )
		{
			GraphicCodeMaker::SNumberCode *numberCode = new GraphicCodeMaker::SNumberCode;
			numberCode->index = random(10000);
			if( validate( numberCode->index, GRAPHICCODE_BACKGROUNDDIR, GRAPHICCODE_NUMBERPICDIR, numberCode->bitStream ) )
			{
				SAckCheckMsg ackMsg;
				ackMsg.checkType = itr->checkType;
				ackMsg.nIDNeedToCheck = itr->nIDNeedToCheck;
				ackMsg.pData = numberCode;
				pManager->AddAckCheckMsg(ackMsg);
			}
			else
			{
				delete numberCode;
			}
		}
	}

	static const int nSleepTime = 1; //g_Cfg.m_bSleepTime;
	Sleep( nSleepTime );
}

void GraphicCodeCheckCommunication::Update()
{
	DECLARE_TIME_TEST
	BEGIN_TIME_TEST( "GraphicCodeCheckCommunication[1]" );
	AckCheckMsgQueue tempQueue;
	{
		CSALocker lock(_lockAckCheckMsgQueue);
		tempQueue = _AckCheckMsgQueue;
		_AckCheckMsgQueue.clear();
	}
	END_TIME_TEST_1( "GraphicCodeCheckCommunication[1]",100 );
	BEGIN_TIME_TEST( "GraphicCodeCheckCommunication[2]" );
	ItrAckCheckMsgQueue itr = tempQueue.begin();
	for ( ; itr != tempQueue.end(); ++itr )
	{
		DECLARE_TIME_TEST
		BEGIN_TIME_TEST( "GraphicCodeCheckCommunication[3]" );
		switch ( itr->checkType )
		{
		case ECT_GraphicCode:
			{
				GamePlayer* pPlayer = theRunTimeData.GetGamePlayerByDBID(itr->nIDNeedToCheck);
				if (pPlayer)
				{
					MsgReqGraphicCode msg;
					pPlayer->_graphicCodeManager.MakeReqGraphicCode(msg, (GraphicCodeMaker::SGraphicCode *)itr->pData);
					GettheServer().SendMsgToSingle(&msg, pPlayer);
				}
			}
			break;
		case ECT_NumberCode:
			{
				GamePlayer* pPlayer = theRunTimeData.GetCharacterByAccountID(itr->nIDNeedToCheck);
				if (pPlayer)
				{
					MsgReqNumberCode msg;
					pPlayer->_graphicCodeManager.MakeReqNumberCode(msg, (GraphicCodeMaker::SNumberCode *)itr->pData);
					GettheServer().SendMsgToSingle(&msg, pPlayer);
				}
			}
			break;
		}
		END_TIME_TEST_1( "GraphicCodeCheckCommunication[3]",100 );
	}
	END_TIME_TEST_1( "GraphicCodeCheckCommunication[2]",100 );
}

void GraphicCodeCheckCommunication::AddCheckReqMsg( SCheckReqMsg &msg )
{
	CSALocker lock(_lockCheckReqMsgQueue);
	_CheckReqMsgQueue.push_back(msg);
}

void GraphicCodeCheckCommunication::AddAckCheckMsg( SAckCheckMsg &msg )
{
	CSALocker lock(_lockAckCheckMsgQueue);
	_AckCheckMsgQueue.push_back(msg);
}
