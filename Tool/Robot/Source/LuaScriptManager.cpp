#include "LuaScriptManager.h"
#include "MatrixBot.h"
#include "RapidXml/MeRapidXml.h"    // Xml加载
#include "tstring.h"

#if defined(Lua_Bind)

LuaBindManager::LuaBindManager()
{
    Init();
}

LuaBindManager::~LuaBindManager()
{
    UnInit();
}

unsigned long LuaBindManager::Init()
{
    _pLuaState = lua_open();
    luaL_openlibs( _pLuaState );
    luabind::open( _pLuaState );

    return 0;
}

unsigned long LuaBindManager::Bind()
{
    using namespace luabind;
    module(_pLuaState)
        [
            class_<CMatrixBot>("CMatrixBot")
            .def(constructor<>())
            .def( "InitPlayGame",      &CMatrixBot::InitPlayGame                                    )
            .def( "PlaySkill",         &CMatrixBot::PlaySkill                                       )
            .def( "LearnSkill",        (void(CMatrixBot::*)(int))&CMatrixBot::LearnSkill            )
            .def( "ReqItem",           (void(CMatrixBot::*)(unsigned int))&CMatrixBot::ReqItem      )
            .def( "EquipItem",         (void(CMatrixBot::*)(void))&CMatrixBot::EquipItem            )
            .def( "GetSelfProfession", &CMatrixBot::GetSelfProfession                               )
            .def( "ergodicItemBag",    (bool(CMatrixBot::*)(int))&CMatrixBot::ergodicItemBag        )
            .def( "SetSleep",          (void(CMatrixBot::*)(DWORD))&CMatrixBot::SetSleep            )
            .def( "GetAccount",        (char*(CMatrixBot::*)(void))&CMatrixBot::GetAccount          )
            .def( "FlyToMap",          &CMatrixBot::FlyToMap                                        )
            .def( "DecideVisualSuit",  (bool(CMatrixBot::*)(void))&CMatrixBot::DecideVisualSuit     )
        ];

    return 0;
}

unsigned long LuaBindManager::LoadLuaScript(const char* szFileName)
{
    if (szFileName == NULL || GetLuaState() == NULL)
    { return ER_Failed;}

    int nResult = 0;
    try
    {
        nResult = luaL_dofile(_pLuaState, szFileName); // 返回值为0表示Lua文件加载成功，没有语法错误
    }
    catch(luabind::error& e)
    {
        std::string luaErrorInfo = lua_tostring(_pLuaState, -1);
        LOG_MESSAGE(LogObject, LOG_PRIORITY_ERROR, "Call Function[luaL_dofile] error:%s Desc:%s", e.what(), luaErrorInfo.c_str());
        return ER_Failed;
    }
    return ER_Success;
}

unsigned long LuaBindManager::UnInit()
{
    lua_close(_pLuaState);
    return 0;
}

#elif defined(Lua_Plus)

LuaPlusManager::LuaPlusManager():m_LuaScript(false)
{
}

LuaPlusManager::~LuaPlusManager()
{
    m_LuaScript->PushNil;
}

void LuaPlusManager::LoadLuaScript(const char* LuaFileName)
{
    if (LuaFileName == NULL)
    {
        LOG_MESSAGE(LogObject, LOG_PRIORITY_ERROR, "文件[%s]不存在，请检查！", LuaFileName);
        return;
    }

    try
    {
        LuaObject metaTableObj;
        metaTableObj = m_LuaScript->GetGlobals().CreateTable("MultiObjectMetaTable");
        metaTableObj.SetObject("__index", metaTableObj);

        metaTableObj.RegisterObjectDirect( "InitPlayGame",              (CMatrixBot*)0, &CMatrixBot::InitPlayGame       );
        metaTableObj.RegisterObjectDirect( "PlaySkill",                 (CMatrixBot*)0, &CMatrixBot::PlaySkill          );
        metaTableObj.RegisterObjectDirect( "LearnSkill",                (CMatrixBot*)0, &CMatrixBot::LearnSkill         );
        metaTableObj.RegisterObjectDirect( "ReqItem",                   (CMatrixBot*)0, &CMatrixBot::ReqItem            );
        metaTableObj.RegisterObjectDirect( "EquipItem",                 (CMatrixBot*)0, &CMatrixBot::EquipItem          );
        metaTableObj.RegisterObjectDirect( "GetSelfProfession",         (CMatrixBot*)0, &CMatrixBot::GetSelfProfession  );
        metaTableObj.RegisterObjectDirect( "ergodicItemBag",            (CMatrixBot*)0, &CMatrixBot::ergodicItemBag     );
        metaTableObj.RegisterObjectDirect( "SetSleep",                  (CMatrixBot*)0, &CMatrixBot::SetSleep           );
        metaTableObj.RegisterObjectDirect( "GetAccount",                (CMatrixBot*)0, &CMatrixBot::GetAccount         );
        metaTableObj.RegisterObjectDirect( "FlyToMap",                  (CMatrixBot*)0, &CMatrixBot::FlyToMap           );

        CMatrixBot MatrixBot;
        LuaObject RobotCoreObject = m_LuaScript->BoxPointer(*MatrixBot); // 暂时先使用矩阵机器人
        RobotCoreObject.SetMetaTable(metaTableObj);
        m_LuaScript->GetGlobals().SetObject( "robot", RobotCoreObject );

        if( !m_LuaScript->DoFile( LuaFileName ) )   // 执行LuaFileName文件
        {
            m_bLuaScriptLoaded = true;
            m_LuaScript->Call( 0, 0 );
        }
    }
    catch (LuaPlus::LuaException& e)
    {
        LOG_MESSAGE(LogObject, LOG_PRIORITY_ERROR, "Robot Script [%s] failed : Error[%s]", LuaFileName, e.GetErrorMessage());
    }
}
#endif
 
#if defined(Lua_Bind)
bool LuaBindManager::LoadScriptConfig(const char* szFileName)
#elif defined(Lua_Plus)
bool LuaPlusManager::LoadScriptConfig(const char* szFileName)
#endif
{
    if (szFileName == NULL)
    { return false; }

    MeXmlDocument MeXmlDoc;
    if ( !MeXmlDoc.LoadFile(szFileName) )
    { return false;}

    MeXmlElement* pRoot = MeXmlDoc.FirstChildElement("Project")->ToElement();
    if (pRoot == NULL)
    { return false;}

    MeXmlElement* pBotTypes = pRoot->FirstChildElement("Robots")->ToElement();
    if (pBotTypes == NULL)
    { return false;}

    MeXmlElement* pBotType = pBotTypes->FirstChildElement("Robot")->ToElement();
    if (pBotType == NULL)
    { return false;}

    while (pBotType != NULL)
    {
        LuaScriptConfig* pLuaConfig = new LuaScriptConfig;

        int id = 0;
        pBotType->Attribute("Id", &id);
        pLuaConfig->nID = id;

        Common::_tstring strBotName;
        strBotName.fromUTF8(pBotType->Attribute("Name"));
        pLuaConfig->RobotName = strBotName;

        Common::_tstring strScriptPath;
        strScriptPath.fromUTF8(pBotType->Attribute("LuaPath"));
        pLuaConfig->ScriptPath = strScriptPath;

        m_ScriptVector.push_back(pLuaConfig);
        pBotType = pBotType->NextSiblingElement();
    }
    return true;
}

#if defined(Lua_Bind)
bool LuaBindManager::SaveScriptConfig(const char* szFileName)
#elif defined(Lua_Plus)
bool LuaPlusManager::SaveScriptConfig(const char* szFileName)
#endif
{
    if (szFileName == NULL)
    { return false;}

    MeXmlDocument MeXmlDoc;
    MeXmlDoc.InsertEndChild(MeXmlDeclaration("1.0","utf-8","yes"));

    MeXmlElement* pRoot = MeXmlDoc.InsertEndChild("Project")->ToElement();
    if (pRoot == NULL)
    { return false;}

    MeXmlElement* pBotElements = pRoot->InsertEndChild("Robots")->ToElement();
    if (pBotElements == NULL)
    { return false;}

    std::vector<LuaScriptConfig*>::iterator iterBegin = m_ScriptVector.begin();
    std::vector<LuaScriptConfig*>::iterator iterEnd   = m_ScriptVector.end();
    for (; iterBegin != iterEnd; ++iterBegin)
    {
        if ((*iterBegin) == NULL)
        { continue;}

        MeXmlElement* pBotElement = pBotElements->InsertEndChild("Robot")->ToElement();
        if (pBotElement == NULL)
        { continue;}

        pBotElement->SetAttribute("Id", (*iterBegin)->nID);
        
        Common::_tstring strBotName = (*iterBegin)->RobotName;
        pBotElement->SetAttribute("Name", strBotName.toUTF8().c_str());

        Common::_tstring strLuaPath = (*iterBegin)->ScriptPath;
        pBotElement->SetAttribute("LuaPath", strLuaPath.toUTF8().c_str());
    }

    return MeXmlDoc.SaveFile(szFileName);
}
#if defined(Lua_Bind)
LuaBindManager::LuaScriptConfig* LuaBindManager::GetLuaScriptById(int nID)
#elif defined(Lua_Plus)
LuaPlusManager::LuaScriptConfig* LuaPlusManager::GetLuaScriptById(int nID)
#endif
{
    if (nID < 0 || 17 < nID) // 机器人类型最小为0， 最大为17
    {
        return NULL;
    }

    return m_ScriptVector[nID];
}