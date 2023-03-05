#include "ScriptManager.h"
#include "FightBot.h"
#include "ScriptBot.h"
#include "GmCommandRobot.h"

ScriptManager::ScriptManager() : _pLuaState( NULL )
{

}

ScriptManager::~ScriptManager()
{
    UnInit();
}



uint32 ScriptManager::Init()
{
    if (NULL == _pLuaState)
    {
        _pLuaState = lua_open();
        luaL_openlibs( _pLuaState );
        luabind::open( _pLuaState );
        luabind::set_pcall_callback( &GetExecuteErrorFileAndLine );
        return Bind();
    }
    return ER_Success;
}

uint32 ScriptManager::Bind()
{
    using namespace luabind;
    if (NULL == _pLuaState)
    {
        return ER_Failed;
    }
    module(_pLuaState)
        [
            class_<BaseRobot>("CBot")
                .enum_("BotType")
                [
                    value("Bot_Normal",Bot_Normal),
                    value("Bot_Attack",Bot_Attack),
                    value("Bot_Fly",Bot_Fly),
                    value("Bot_Fight",Bot_Fight),
                    value("Bot_Quest",Bot_Quest),
                    value("Bot_Script",Bot_Script),
                    value("Bot_Guild",Bot_Guild),
                    value("Bot_Client",Bot_Client),
                    value("Bot_Online",Bot_Online),
                    value("Bot_Team",Bot_Team),
                    value("Bot_Ectype",Bot_Ectype),
                    value("Bot_Brome",Bot_Brome),
                    value("Bot_Login",Bot_Login),
                    value("Bot_Business",Bot_Business),
                    value("Bot_Firend",Bot_Firend),
                    value("Bot_GMCommondTest",Bot_PlatformTest),
                    value("Bot_MatrixBot",Bot_MatrixBot)
                ]
                .enum_("ConstValue")
                [
                    value("ULONG_MAX",ULONG_MAX),
                    value("INT_MAX",INT_MAX),
                    value("SHRT_MAX",SHRT_MAX)
                ]
                .def(constructor<>())
                .def("GetBotRoleName", &BaseRobot::GetBotRoleName)
				.def("GetBotMoney", &BaseRobot::GetBotMoney)
				.def("GetBotDBID", &BaseRobot::GetBotDBID)
				.def("GetBotShortId", &BaseRobot::GetBotShortId)
				.def("GetBotHP", &BaseRobot::GetBotHP)
				.def("GetBotLevel", &BaseRobot::GetBotLevel)
				.def("GetMapID", &BaseRobot::GetMapID)
                .def("Say",&BaseRobot::Say)
                .def("SendMsg",&BaseRobot::SendMsg)
                .def("Move",&BaseRobot::Move)
                .def("FlyToMap",&BaseRobot::FlyToMap)
                .def("RandFly",&BaseRobot::RandFly)
                .def("GetType",&BaseRobot::GetType)
                .def("SetSleep",&BaseRobot::SetSleep)
                .def("SetTipsInfo",&BaseRobot::SetTipsInfo)
                .def("ReqLvlUp",&BaseRobot::ReqLvlUp)
                /*.def("",CBot::)*/
				.def("GetMapName",&BaseRobot::GetMapName),
            class_<CAttackBot,BaseRobot>("AttackBot")
                .def(constructor<>())
                .def("AttackEnemy",&CAttackBot::AttackEnemy)
                .def("LockTarget",&CAttackBot::LockTarget)
                .def("PlayAttack", &CAttackBot::PlayAttack),
            class_<CFightBot,CAttackBot>("FightBot")
                .def(constructor<>())
                .property("LastMapId",&CFightBot::GetLastMapId,&CFightBot::SetLastMapId)
                .def("LockTarget",&CFightBot::LockTarget),
            class_<CScriptBot,CAttackBot>("CScriptBot")
                .def(constructor<>())
                .property("bFlyOut",&CScriptBot::GetFlyOut,&CScriptBot::SetFlyOut)
                .property("bFlyIn",&CScriptBot::GetFlyIn,&CScriptBot::SetFlyIn)
                .def("FlyMap",&CScriptBot::FlyMap),
            class_<GmCommandRobot,BaseRobot>("PlatformBot")
                .def(constructor<>())
                .def("ReqAddItem",&GmCommandRobot::ReqAddItem),
            class_<ScriptManager>("ScriptManager")
                .enum_("LogMsgLevel")
                [
                    value("LogInfo",LOG_PRIORITY_INFO),
                    value("LogDebug",LOG_PRIORITY_DEBUG),
                    value("LogWarning",LOG_PRIORITY_WARNING),
                    value("LogError",LOG_PRIORITY_ERROR)
                ]
                .def("LogMsg",&ScriptManager::LogMsg)
                .def("LoadScript",&ScriptManager::LoadScript),
            class_<MessageBaseHeader>("MessageBaseHeader")
                .def(constructor<>())
                .def_readwrite("stID",&MessageBaseHeader::stID)
                //.def_readwrite("dwType",&MsgHeader::dwType)
                .def_readwrite("stLength",&MessageBaseHeader::stLength),
            class_<Msg>("Msg")
                .def(constructor<>())
                .def_readwrite("head",&Msg::header)
                .def("GetLength",&Msg::GetLength),
            class_<MsgChangePKFlag,Msg>("MsgChangePKFlag")
                .enum_("PKProtect")
                [
                    value("PKMode_Normal",PKMode_Normal),
                    value("PKMode_Fight",PKMode_Fight),
                    value("PKMode_Critical",PKMode_Critical)
                ]
                .def(constructor<>())
                .def_readwrite("shFlag",&MsgChangePKFlag::shFlag),
            def("GetScriptManage",&ScriptManager::GetInstance),
            def("HQ_TimeGetTime",&HQ_TimeGetTime)
        ];

    //luaL_loadfile( _pLuaState, ".\\Data\\RobotScript\\Bot.lua");
//     std::string filePath = theBotDataCenter.ScriptFilePath;
//     if (filePath.at(filePath.length()-1) != '\\'
//         && filePath.at(filePath.length()-1) != '/')
//     {
//         filePath += '\\';
//     }
//     filePath += theBotDataCenter.ScriptFileName;
//     return LoadScript(filePath.c_str());
    return ER_Success;
}

uint32 ScriptManager::LoadScript(const char *szScriptFileName)
{
    if (NULL == szScriptFileName||NULL == _pLuaState)
    {
        return ER_Failed;
    }
    try 
    {
        luaL_dofile( _pLuaState, szScriptFileName);
    }
    catch(luabind::error &e)
    {
        std::string luaErrorInfo = lua_tostring(_pLuaState,-1);
        LOG_MESSAGE(LogObject,LOG_PRIORITY_ERROR,"Load %s Script Faild. Error Description:%s,\
                                                 Error Info: %s.",szScriptFileName,e.what(),
                                                 luaErrorInfo.c_str());
        return ER_Failed;
    }
    return ER_Success;
}

void ScriptManager::LogMsg(int Level,const char *szMsg)
{
    if (   LOG_PRIORITY_ERROR != Level
        && LOG_PRIORITY_INFO != Level
        && LOG_PRIORITY_DEBUG != Level
        && LOG_PRIORITY_WARNING != Level)
    {
        return;
    }
    LOG_MESSAGE(LogObject,LOG_PRIORITY_ERROR,szMsg);
}

uint32 ScriptManager::UnInit()
{
    if (_pLuaState)
    {
        lua_close( _pLuaState );
    }
    return ER_Success;
}

// template <class Param1 >
// void ScriptManager::ScriptFunctionVoid( const std::string& funName, Param1 p1 )
// {
//     if (NULL == _pLuaState)
//     { return; }
// 
//     try
//     {
//         luabind::call_function<void>( _pLuaState, funName.c_str(),p1);
//     }
//     catch (luabind::error& e)
//     {
//         LOG_MESSAGE(LogObject,LOG_PRIORITY_ERROR,"Call %s Function Error : %s.",funName.c_str(),e.what());
//     }
// }

bool ScriptManager::ScriptFunctionVoid( const std::string& funName )
{
    if (NULL == _pLuaState)
    {
        return false;
    }

    try
    {
        luabind::call_function<void>( _pLuaState, funName.c_str());
        return true;
    }
    catch (luabind::error& e)
    {
        std::string luaErrorInfo = lua_tostring(_pLuaState,-1);
        LOG_MESSAGE(LogObject,LOG_PRIORITY_ERROR,"Call %s Function Error : %s.\
                                                 Description: %s.",funName.c_str(),e.what(),
                                                 luaErrorInfo.c_str());
    }
    return false;
}

int GetExecuteErrorFileAndLine(lua_State* pLuaState)
{
    if (NULL == pLuaState)
    {
        return -1;
    }
    lua_Debug Debug;
    memset(&Debug,0,sizeof(lua_Debug));
    lua_getstack(pLuaState,1,&Debug);
    lua_getinfo(pLuaState,"Sln",&Debug);
    std::string err = lua_tostring(pLuaState, -1);
#ifdef _DEBUG
    std::string OtherErrorInfo = lua_tostring(pLuaState, 1);
#endif
    lua_pop(pLuaState, 1);
    std::stringstream msg;
    msg << Debug.short_src << ":" << Debug.currentline;

    if (Debug.name != NULL)
    {
        msg << "(" << Debug.namewhat << " " << Debug.name << ")";
    }
    msg << " " << err;
    lua_pushstring(pLuaState, msg.str().c_str());
    return 1;
}

ScriptManager& ScriptManager::GetInstance()
{
    static ScriptManager scriptManager;
    return scriptManager;
}