//////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////

#include "MeTerrain/stdafx.h"
#include "GameSetting.h"
#include "../Player.h"
#include "GameMain.h"
#include "PlayerMgr.h"
#include "Pack.h"
#include "Group_Me.h"
#include "baseProperty.h"
#include "MeAudio/MeAudio.h"
#include "GameSettingUI.h"
#include "UserData.h"
#include "SystemSetting.h"
#include "wsCamera.h"
#include "RapidXml/MeRapidXml.h"
#include "Ui/Main.h"
#include "ui/exmain.h"
//----------------------------------------------------------------
#define FILENAME_XML_DEFAULTGAMESETTING "..\\Data\\ClientConfig\\UserSetting.config"
#define FILENAME_XML_CUSTOMGAMESETTING  "CustomGameSetting.config"
#define FILENAME_XML_CUSTOMGAMESETTING_OLD  "CustomGameSetting.xml"
#define XML_ROOT_NAME "Project"
#define XML_GAMESETTING_ROOT_NAME "GameSetting"
//----------------------------------------------------------------
extern CHeroGame* theApp;
extern BOOL g_bbshowItemName;
extern float g_fCamerFOV;
extern CUI_ID_FRAME_PACK s_CUI_ID_FRAME_PACK;
extern CPlayerRole thePlayerRole;
extern BOOL g_bMouseMoveMode; //鼠标移动模式
//extern BOOL g_bMouseRoleTurn; //智能转身

extern GAME_STATE		g_GameState;
//----------------------------------------------------------------
GameSetting* GameSetting::ms_pThis = 0;
//----------------------------------------------------------------
GameSetting::GameSetting()
{
	memset( m_Settings, 0, sizeof( eGameSettingCategory ) * eGSC_TOTAL );
	memset( m_bDirty, 1, sizeof( bool ) * eGSC_TOTAL );

	m_SettingNames[eGSC_CHATFONTSIZE]		= "ChatFontSize";		//聊天字体大小
	m_SettingNames[eGSC_AUTOREPLYSECRET]	= "AutoReplySecret";	//自动回复密语
	m_SettingNames[eGSC_AUTOTURNAROUND]		= "AutoTurnAround";		//智能转身
	m_SettingNames[eGSC_AUTOMOUSE]			= "AutoMouse";			//智能鼠标
	m_SettingNames[eGSC_SHOWHELMET]			= "ShowHelmet";			//显示头盔
	m_SettingNames[eGSC_VERTICLEVIEW]		= "VerticleView";		//垂直视角锁定
	m_SettingNames[eGSC_SHOWNPCNAME]		= "ShowNPCName";		//显示NPC名字
	m_SettingNames[eGSC_SHOWITEMNAME]		= "ShowItemName";		//显示物品名字
	m_SettingNames[eGSC_SHOWPLAYERNAME]		= "ShowPlayerName";		//显示玩家名字
	m_SettingNames[eGSC_SHOWTITLE]			= "ShowTitle";			//显示称号
	m_SettingNames[eGSC_SHOWPLAYERNUMBER]	= "ShowPlayerNumber";	//同屏人数
	m_SettingNames[eGSC_FOV]				= "Fov";				//广角
	m_SettingNames[eGSC_MAXCAMERADISTANCE]	= "MaxCameraDistance";	//镜头最大距离
	m_SettingNames[eGSC_SHOWHPBARMP]		= "ShowHpMp";			//显示hp,mp
	m_SettingNames[eGSC_SHOWFP]				= "ShowFp";				//显示fp
	m_SettingNames[eGSC_45CAMERA]			= "Camera45";			//45锁定
	m_SettingNames[eGSC_FOLLOWCAMERA]		= "FollowCamera";		//相机跟踪
	m_SettingNames[eGSC_SAVECHATMESSAGE]	= "SaveChatMessage";	//保存聊天记录
	m_SettingNames[eGSC_SHOWHPBAR]			= "ShowHPBar";			//显示HP
	m_SettingNames[eGSC_SHOWMPBAR]			= "ShowMPBar";			//显示MP
	m_SettingNames[eGSC_SHOWFPBAR]			= "ShowFPBar";			//显示FP
	m_SettingNames[eGSC_SHOWCHATBACKGROUND]	= "ShowChatBackground";	//显示聊天窗口背景
	m_SettingNames[eGSC_MOUSESPEED]			= "MouseSpeed";			//显示FP
	m_SettingNames[eGSC_CAMERAROTATESPEED]	= "CameraRotateSpeed";	//显示聊天窗口背景
	m_SettingNames[eGSC_SelfName]			= "SelfName";			//自身姓名
	m_SettingNames[eGSC_SelfHp]				= "SelfHp";				//自身血条
	m_SettingNames[eGSC_SelfTitle]			= "SelfTitle";			//自身称号
	m_SettingNames[eGSC_SelfGuild]			= "SelfGuild";			//自身帮会
	m_SettingNames[eGSC_SelfTong]			= "SelfTong";			//自身堂名
	m_SettingNames[eGSC_SelfMp]				= "SelfMp"	;			//自身蓝条
	m_SettingNames[eGSC_SelfPetName]		= "SelfPetName";		//自身宠物姓名
	m_SettingNames[eGSC_SelfPetHp]			= "SelfPetHp"	;		//自身宠物血条
	m_SettingNames[eGSC_TeamPlayerName]		= "TeamPlayerName";		//队友头顶姓名
	m_SettingNames[eGSC_TeamPlayerHp]		= "TeamPlayerHp";		//队友头顶血条
	m_SettingNames[eGSC_TeamPlayerTitle]	= "TeamPlayerTitle";	//队友头顶称号
	m_SettingNames[eGSC_TeamPlayerGuild]	= "TeamPlayerGuild";	//队友头顶帮会
	m_SettingNames[eGSC_TeamPlayerTong]		= "TeamPlayerTong";		//队友头顶堂名
	m_SettingNames[eGSC_TeamPlayerPetName]	= "TeamPlayerPetName";	//队友召唤兽头顶姓名
	m_SettingNames[eGSC_TeamPlayerPetHp]	= "TeamPlayerPetHp";	//队友召唤兽头顶血条
	m_SettingNames[eGSC_OtherPlayerName]	= "OtherPlayerName";	//非队友头顶姓名
	m_SettingNames[eGSC_OtherPlayerHp]		= "OtherPlayerHp";		//非队友头顶血条
	m_SettingNames[eGSC_OtherPlayerTitle]	= "OtherPlayerTitle";	//非队友头顶称号
	m_SettingNames[eGSC_OtherPlayerGuild]	= "OtherPlayerGuild";	//非队友头顶帮会
	m_SettingNames[eGSC_OtherPlayerTong]	= "OtherPlayerTong";	//非队友头顶堂名
	m_SettingNames[eGSC_OtherPlayerPetName]	= "OtherPlayerPetName";	//非队友召唤兽头顶姓名
	m_SettingNames[eGSC_OtherPlayerPetHp]	= "OtherPlayerPetHp";	//非队友召唤兽头顶血条
	m_SettingNames[eGSC_FightFlyText]		= "FightFlyText";		//战斗飘字
	m_SettingNames[eGSC_RefuseStrangerMsg]	= "RefuseStrangerMsg";	//拒绝陌生人短消息
	m_SettingNames[eGSC_RefuseAllMsg]		= "RefuseAllMsg";		//拒绝所有人短消息
	m_SettingNames[eGSC_MiniMapTeam]		= "MiniMapTeam";		//小地图显示队友
	m_SettingNames[eGSC_MiniMapNpc]			= "MiniMapNpc";			//小地图显示Npc
	m_SettingNames[eGSC_MiniMapMonster]		= "MiniMapMonster";		//小地图显示Monster
	m_SettingNames[eGSC_MiniMapFriend]		= "MiniMapFriend";		//小地图显示好友
	m_SettingNames[eGSC_MiniMapGuild]		= "MiniMapGuild";		//小地图显示帮派
	m_SettingNames[eGSC_MiniMapEnemy]		= "MiniMapEnemy";		//小地图显示仇人
	m_SettingNames[eGSC_MiniMapOther]		= "MiniMapOther";		//小地图显示其他玩家	
	m_SettingNames[eGSC_ChatSelf]			= "ChatSelf";			//显示自身聊天泡泡
	m_SettingNames[eGSC_ChatTeam]			= "ChatTeam";			//显示队友聊天泡泡
	m_SettingNames[eGSC_ChatOther]			= "ChatOther";			//显示其他人聊天泡泡
	m_SettingNames[eGSC_NpcName]			= "NpcName";			//NPC姓名
	m_SettingNames[eGSC_NpcHp]				= "NpcHp";				//NPC血条
	m_SettingNames[eGSC_NpcTitle]			= "NpcTitle";			//NPC公会
	m_SettingNames[eGSC_MonsterName]		= "MonsterName";		//Monster姓名
	m_SettingNames[eGSC_MonsterHp]			= "MonsterHp";			//Monster血条
	m_SettingNames[eGSC_ItemName]			= "ItemName";			//掉落Item名字
	m_SettingNames[eGSC_SOUND]				= "Sound";				//声音大小
	m_SettingNames[eGSC_SOUNDEFFECT]		= "SoundEffect";		//环境音效
    m_SettingNames[eGSC_ChatNpc]			= "ChatNpc";			//显示NPC聊天泡泡
    m_SettingNames[eGSC_ChatMonster]		= "ChatMonster";		//显示怪物聊天泡泡
    m_SettingNames[eGSC_SelfPetTitle]		= "SelfPetTitle";		//自己宠物称号
    m_SettingNames[eGSC_TeamPetTitle]		= "TeamPetTitle";		//队友宠物称号
    m_SettingNames[eGSC_OtherPetTitle]			= "OtherPetTitle";		//非队友宠物称号
    m_SettingNames[eGSC_SelfEffect]				= "SelfEffect";		    //自身特效
    m_SettingNames[eGSC_TeamPlayerEffect]		= "TeamPlayerEffect";   //队友特效
    m_SettingNames[eGSC_TeamPlayerModel]		= "TeamPlayerModel";	//队友人物模型
    m_SettingNames[eGSC_OtherPlayerEffect]		= "OtherPlayerEffect";  //非队友特效
    m_SettingNames[eGSC_OtherPlayerModel]		= "OtherPlayerModel";   //非队友人物模型
    m_SettingNames[eGSC_RefuseAddFriendInFight]	= "RefuseAddFriendInFight"; //战斗中拒绝加好友邀请
    m_SettingNames[eGSC_RefuseAddTeamInFight]	= "RefuseAddTeamInFight";   //战斗中拒绝组队申请
    m_SettingNames[eGSC_RefuseAddGangInFight]	= "RefuseAddGangInFight";   //战斗中拒绝帮派邀请
    m_SettingNames[eGSC_RefuseDuelInFight]	    = "RefuseDuelInFight";      //战斗中拒绝比武邀请
    m_SettingNames[eGSC_RefuseBargainInFight]	= "RefuseBargainInFight";   //战斗中拒绝交易邀请
    m_SettingNames[eGSC_RefuseHugInFight]		= "RefuseHugInFight";   //战斗中拒绝拥抱邀请
    m_SettingNames[eGSC_RefuseAddFriend]		= "RefuseAddFriend";    //非战斗中拒绝加好友邀请
    m_SettingNames[eGSC_RefuseAddTeam]			= "RefuseAddTeam";      //非战斗中拒绝组队申请
    m_SettingNames[eGSC_RefuseAddGang]			= "RefuseAddGang";      //非战斗中拒绝帮派邀请
    m_SettingNames[eGSC_RefuseDuel]				= "RefuseDuel";         //非战斗中拒绝比武邀请
    m_SettingNames[eGSC_RefuseBargain]			= "RefuseBargain";      //非战斗中拒绝交易邀请
    m_SettingNames[eGSC_RefuseHug]				= "RefuseHug";          //非战斗中拒绝拥抱邀请
	m_SettingNames[eGSC_IntroductionEnable]	    = "Introduction";          //非战斗中拒绝拥抱邀请
	m_SettingNames[eGSC_ChatListWidth]	        = "ChatListWidth";          //聊天框的宽度
	m_SettingNames[eGSC_ChatListHeight]	        = "ChatListHeight";          //聊天框的高度
	
	m_SettingNames[eGSC_SellPrompt1] = "SellPrompt1";
	m_SettingNames[eGSC_SellPrompt2] = "SellPrompt2";
	m_SettingNames[eGSC_SellPrompt3] = "SellPrompt3";
	m_SettingNames[eGSC_SellPrompt4] = "SellPrompt4";
	m_SettingNames[eGSC_SellPrompt5] = "SellPrompt5";
	m_SettingNames[eGSC_SellPrompt6] = "SellPrompt6";

	m_SettingNames[eGSC_TabMe				]   = "TabMe";
	m_SettingNames[eGSC_TabMyPet			]   = "TabMyPet";
	m_SettingNames[eGSC_TabTeamPlayer		]   = "TabTeamPlayer";
	m_SettingNames[eGSC_TabTeamPlayerPet	]   = "TabTeamPlayerPet";
	m_SettingNames[eGSC_TabEnemyGuildPlayer	]   = "TabEnemyGuildPlayer";
	m_SettingNames[eGSC_TabEnemyGuildPlayerPet] = "TabEnemyGuildPlayerPet";
	m_SettingNames[eGSC_TabLeaguePlayer		]   = "TabLeaguePlayer";
	m_SettingNames[eGSC_TabLeaguePlayerPet	]   = "TabLeaguePlayerPet";
	m_SettingNames[eGSC_TabMyGuildPlayer	]   = "TabMyGuildPlayer";
	m_SettingNames[eGSC_TabMyGuildPlayerPet	]   = "TabMyGuildPlayerPet";
	m_SettingNames[eGSC_TabNormalPlayer		]   = "TabNormalPlayer";
	m_SettingNames[eGSC_TabNormalPlayerPet	]   = "TabNormalPlayerPet";
	m_SettingNames[eGSC_TabRedNamePlayer	]   = "TabRedNamePlayer";
	m_SettingNames[eGSC_TabRedNamePlayerPet	]   = "TabRedNamePlayerPet";
	m_SettingNames[eGSC_TabPKPlayer			]	= "TabPKPlayer";
	m_SettingNames[eGSC_TabPKPlayerPet		]	= "TabPKPlayerPet";
	m_SettingNames[eGSC_TabMonster			]	= "TabMonster";
	m_SettingNames[eGSC_TabOther			]	= "TabOther";
    m_SettingNames[eSSC_SKILLLOCK           ]   = "SkillLock";      //技能栏锁定
    m_SettingNames[eSSC_SKILLLOCK2          ]   = "SkillLock2";  //技能栏扩展锁定
    m_SettingNames[eSSC_CLOSE_AUTO_SELECT   ]   = "CloseAutoSelect";        

	m_Settings[eGSC_SHOWCHATBACKGROUND]		= 1;
	m_Settings[eGSC_MOUSESPEED]				= 10;
	m_Settings[eGSC_CAMERAROTATESPEED]		= 320;
	m_Settings[eGSC_IntroductionEnable]		= 1;
	m_Settings[eGSC_ChatListWidth]			= 353;
	m_Settings[eGSC_ChatListHeight]			= 161;
	m_Settings[eSSC_SKILLLOCK    ]			= 0;
    m_Settings[eSSC_SKILLLOCK2    ]			= 0;
    m_Settings[eSSC_CLOSE_AUTO_SELECT]      = 1;
 
// 	RemoveReadOnlyAttribute( FILENAME_XML_DEFAULTGAMESETTING );
	//RemoveReadOnlyAttribute( FILENAME_XML_CUSTOMGAMESETTING );
}
//----------------------------------------------------------------
GameSetting::~GameSetting(){}
//----------------------------------------------------------------
GameSetting* GameSetting::Instance()
{
	if( !ms_pThis )
		ms_pThis = new GameSetting;
	
	return ms_pThis;
}
//----------------------------------------------------------------
bool GameSetting::Destroy()
{
	SAFE_DELETE( ms_pThis );

	return true;
}
//----------------------------------------------------------------
void GameSetting::SetLevel( eGameSettingCategory eCategory, 
							  unsigned int uiValue )
{
	if( m_Settings[eCategory] == uiValue)
		return;
	m_Settings[eCategory] = uiValue;
	m_bDirty[eCategory] = true;	
}
//----------------------------------------------------------------
void GameSetting::CommitChanges()
{
	for( int i = 0 ; i < eGSC_TOTAL ; ++ i )
	{
		eGameSettingCategory eCategory = (eGameSettingCategory)i;
		ChangeSetting( eCategory, m_Settings[eCategory] );
	}
}

void GameSetting::CommitChanges(eGameSettingCategory eCategory)
{
	ChangeSetting( eCategory, m_Settings[eCategory] );
}

//----------------------------------------------------------------
unsigned int GameSetting::GetLevel( eGameSettingCategory eCategory )
{
	return m_Settings[eCategory];
}
//----------------------------------------------------------------
const char* GameSetting::GetCustomSettingDirectory()
{
	return FILENAME_XML_CUSTOMGAMESETTING;
}
//----------------------------------------------------------------
bool GameSetting::LoadSetting( const char* pszFileName /* = NULL */ )
{
	MeXmlDocument GameSettingXMLDocument;
	bool bRet;
    bool bDefault = false;
	MeXmlElement* pRoot = NULL;
	if( !pszFileName )
	{
		bRet = GameSettingXMLDocument.LoadFile( 
		FILENAME_XML_DEFAULTGAMESETTING );
		if( !bRet )
			return false;
	}
	else
	{
		bRet = GameSettingXMLDocument.LoadFile( 
		pszFileName );

		// 兼容旧的文件
		if( !bRet )	// 读旧的文件格式
		{
			char szSetting[MAX_PATH] = {0};
			MeSprintf_s( szSetting, sizeof(szSetting)/sizeof(char) - 1, "%s%s", CUserData::Instance()->GetUserDataPath(), FILENAME_XML_CUSTOMGAMESETTING_OLD );
			bRet = GameSettingXMLDocument.LoadFile( szSetting );
		}

	}
	//if there is no custom setting, load the default one.
	if( pszFileName && !bRet )
	{		
		bRet = GameSettingXMLDocument.LoadFile( 
			FILENAME_XML_DEFAULTGAMESETTING );

		if( !bRet )
			return false;
        
        bDefault = true;
	}
	//load root
	pRoot = GameSettingXMLDocument.FirstChildElement( 
		XML_ROOT_NAME );
	if( !pRoot )
		return false;
	
	pRoot = pRoot->FirstChildElement( XML_GAMESETTING_ROOT_NAME );
	if( !pRoot )
		return false;

	//load settings
	int nLevel;
	for( int i = 0 ; i < eGSC_TOTAL ; ++ i )
	{
        nLevel = 0;
		if( i == eGSC_45CAMERA )
		{
			nLevel = 1 - CUserData::Instance()->GetViewSet();/*SystemSetting::Instance()->GetLevel( SystemSetting::eSSC_VIEWSET )*/
            SetLevel( ( eGameSettingCategory )i, 0/*nLevel*/ );
		}
		else
		{
			int ret = pRoot->QueryIntAttribute( m_SettingNames[i].c_str(), &nLevel );
            if( bDefault || ret != MEXML_NO_ATTRIBUTE)
                SetLevel( ( eGameSettingCategory )i, nLevel );
		}		
	}

	return true;
}
//----------------------------------------------------------------
bool GameSetting::SaveSetting( const char* pszFileName )
{
	MeXmlDocument GameSettingXMLDocument;
	//header
	GameSettingXMLDocument.InsertEndChild(
		MeXmlDeclaration( "1.0","utf-8","yes" ) );

	//root
	MeXmlElement* pRootNode = GameSettingXMLDocument.InsertEndChild( 
		( XML_ROOT_NAME ) );
	if( !pRootNode )
		return false;

	pRootNode = pRootNode->InsertEndChild( 
		( XML_GAMESETTING_ROOT_NAME ) );
	if( !pRootNode )
		return false;

	MeXmlElement* pRoot = pRootNode->ToElement();

	//save settings
	for( int i = 0 ; i < eGSC_TOTAL ; ++ i )
	{
		if( i == eGSC_45CAMERA  )
			continue;

		//lyh++ 隐藏玩家不进行存档，进游戏默认显示所有玩家
		if (i==eGSC_OtherPlayerEffect || i == eGSC_OtherPlayerModel)
		{
			pRoot->SetAttribute( m_SettingNames[i].c_str(), 1);
			continue;
				
		}

		pRoot->SetAttribute( m_SettingNames[i].c_str(), 
			GetLevel( ( eGameSettingCategory )i ) );
	}
	CUserData::Instance()->WriteViewSet();
	//save file
	bool bRet = GameSettingXMLDocument.SaveFile( 
		pszFileName );

	// 删除旧文件格式
	char szSetting[MAX_PATH] = {0};
	MeSprintf_s( szSetting, sizeof(szSetting)/sizeof(char) - 1, "%s%s", CUserData::Instance()->GetUserDataPath(), FILENAME_XML_CUSTOMGAMESETTING_OLD );
	::DeleteFile(szSetting);

	return bRet;
}
//----------------------------------------------------------------
bool GameSetting::IsLaterChange( eGameSettingCategory eCategory )
{	
	return false;
}
//----------------------------------------------------------------
void GameSetting::RemoveReadOnlyAttribute( const char* pszFilename )
{
	WIN32_FIND_DATAA data;
	HANDLE hFind = FindFirstFileA( pszFilename,&data );
	bool bFind = ( hFind != INVALID_HANDLE_VALUE );
	if ( bFind )
	{
		DWORD dwAttrs = GetFileAttributes( pszFilename );		
		dwAttrs &= ~FILE_ATTRIBUTE_READONLY;
		SetFileAttributes( pszFilename, dwAttrs ); 			
	}
}
//----------------------------------------------------------------
void GameSetting::ChangeSetting( eGameSettingCategory eCategory, 
								  unsigned int uiValue )
{
	if( !m_bDirty[eCategory] )
		return;

	m_bDirty[eCategory] = false;


	switch( eCategory )
	{	
	case eGSC_CHATFONTSIZE:
		SetChatFontSize( uiValue );
		break;
	case eGSC_AUTOREPLYSECRET:
		SetAutoReplySecret( uiValue );
		break;
	case eGSC_AUTOTURNAROUND:
		SetAutoTurnAround( uiValue );
		break;
	case eGSC_AUTOMOUSE:
		SetAutoMouse( uiValue );
		break;
	case eGSC_SHOWHELMET:
		SetShowHelmet( uiValue );
		break;
	case eGSC_VERTICLEVIEW:
		SetVerticleView( uiValue );
		break;
	case eGSC_SHOWNPCNAME:
		SetShowNPCName( uiValue );
		break;
	case eGSC_SHOWITEMNAME:
		SetShowItemName( uiValue );
		break;
	case eGSC_SHOWPLAYERNAME:
		SetShowPlayerName( uiValue );
		break;
	case eGSC_SHOWTITLE:
		SetShowTitle( uiValue );
		break;
	case eGSC_SHOWPLAYERNUMBER:
		SetShowPlayerNumber( uiValue );
		break;
	case eGSC_FOV:
		SetFOV( uiValue );
		break;
	case eGSC_MAXCAMERADISTANCE:
		SetMaxCameraDistance( uiValue );
		break;
	case eGSC_SHOWHPBARMP:
		ShowHpMp( uiValue );
		break;	
	case eGSC_SHOWFP:
		ShowFp( uiValue );
		break;
	case eGSC_45CAMERA:
		Set45Camera( uiValue );
		break;
	case eGSC_FOLLOWCAMERA:
		SetFollowCamera( uiValue );
		break;
	case eGSC_SHOWHPBAR:
		ShowHPBar( uiValue );
		break;
	case eGSC_SHOWMPBAR:
		ShowMPBar( uiValue );
		break;
	case eGSC_SHOWFPBAR:
		ShowFPBar( uiValue );
		break;
	case eGSC_SHOWCHATBACKGROUND:
		ShowChatBackground( uiValue );
		break;
	case eGSC_SOUND:
		SetSound( uiValue );
		break;
	case eGSC_SOUNDEFFECT:
		SetSoundEffect( uiValue );
		break;
	case eGSC_MOUSESPEED:
		SetMouseSpeed( uiValue );
		break;
	case eGSC_CAMERAROTATESPEED:
		SetCameraRotateSpeed( uiValue );
		break;
    case eGSC_TeamPlayerModel:
        if( theHeroGame.GetPlayerMgr() )
        {
            if( (bool)uiValue )
                theHeroGame.GetPlayerMgr()->AddPlayerRenderFlag(CPlayerMgr::EPRF_TEAM);
            else
                theHeroGame.GetPlayerMgr()->RemovePlayerRenderFlag(CPlayerMgr::EPRF_TEAM);
        }
        SetBool( eCategory, (bool)uiValue );
        break;
    case eGSC_OtherPlayerModel:
        /*if( theHeroGame.GetPlayerMgr() )//lyh-- 隐藏玩家这个数据不需要写文件
        {
            if( (bool)uiValue )
                theHeroGame.GetPlayerMgr()->AddPlayerRenderFlag(CPlayerMgr::EPRF_OTHERS);
            else
                theHeroGame.GetPlayerMgr()->RemovePlayerRenderFlag(CPlayerMgr::EPRF_OTHERS);
        }*/
        SetBool( eCategory, (bool)uiValue );
        break;
	case eGSC_SelfName:
	case eGSC_TeamPlayerName:
	case eGSC_OtherPlayerName:	
	{
		SetShowPlayerName(uiValue);
	}
	break;
	case eGSC_SelfHp:
	case eGSC_SelfMp:
	case eGSC_OtherPlayerHp:	
		{
			ShowHpMp(uiValue);
		}
		break;
	case eGSC_SelfPetName:
	case eGSC_TeamPlayerPetName:	
	case eGSC_OtherPlayerPetName:
	case eGSC_NpcName:
		{
			SetShowNPCName(uiValue);
		}
		break;
	case eGSC_RefuseAllMsg:
	case eGSC_RefuseStrangerMsg:
	case eGSC_FightFlyText:
	case eGSC_SelfTitle:
	case eGSC_SelfGuild:
	case eGSC_SelfTong:
	case eGSC_SelfPetHp:
	case eGSC_TeamPlayerHp:
	case eGSC_TeamPlayerTitle:	
	case eGSC_TeamPlayerGuild:
	case eGSC_TeamPlayerTong:	
	case eGSC_TeamPlayerPetHp:
	case eGSC_OtherPlayerTitle:
	case eGSC_OtherPlayerGuild:
	case eGSC_OtherPlayerTong:
	case eGSC_OtherPlayerPetHp:
	case eGSC_MiniMapTeam:
	case eGSC_MiniMapNpc:	
	case eGSC_MiniMapMonster:	
	case eGSC_MiniMapFriend:	
	case eGSC_ChatSelf:
	case eGSC_ChatTeam:		
	case eGSC_ChatOther:
	case eGSC_NpcHp:				
	case eGSC_NpcTitle:			
	case eGSC_MonsterName:		
	case eGSC_MonsterHp:			
	case eGSC_ItemName:
	case eGSC_MiniMapGuild:
	case eGSC_MiniMapEnemy:
	case eGSC_MiniMapOther:
    case eGSC_ChatNpc:
    case eGSC_ChatMonster:
    case eGSC_SelfPetTitle:
    case eGSC_TeamPetTitle:
    case eGSC_OtherPetTitle:
    case eGSC_SelfEffect:
    case eGSC_TeamPlayerEffect:
    case eGSC_OtherPlayerEffect:
    case eGSC_RefuseAddFriendInFight:
    case eGSC_RefuseAddTeamInFight:
    case eGSC_RefuseAddGangInFight:
    case eGSC_RefuseDuelInFight:
    case eGSC_RefuseBargainInFight:
    case eGSC_RefuseHugInFight:
    case eGSC_RefuseAddFriend:
    case eGSC_RefuseAddTeam:
    case eGSC_RefuseAddGang:
    case eGSC_RefuseDuel:
    case eGSC_RefuseBargain:
    case eGSC_RefuseHug:
	case eGSC_IntroductionEnable:
	case eGSC_SellPrompt1:
	case eGSC_SellPrompt2:
	case eGSC_SellPrompt3:
	case eGSC_SellPrompt4:
	case eGSC_SellPrompt5:
	case eGSC_SellPrompt6:
		SetBool( eCategory, (bool)uiValue );
		break;
    case eSSC_CLOSE_AUTO_SELECT:
		m_Settings[eCategory] = 1;
		//SetBool( eCategory, 1/*(bool)uiValue*/ );
		break;
	case eGSC_ChatListWidth:
		m_Settings[eGSC_ChatListWidth] = uiValue;
		break;
	case eSSC_SKILLLOCK:
		s_CUI_ID_FRAME_MAIN.SetHotKeyListImageDrag(uiValue == 0);
		m_Settings[eSSC_SKILLLOCK] = uiValue;
// 		break;
// 	case eSSC_SKILLLOCK2:
		if (s_CUI_ID_FRAME_Exmain.IsUILoad())
		{
			ControlListImage *pListImage = s_CUI_ID_FRAME_Exmain.GetpIDListImageExmain1();
			assert(pListImage != NULL);
			if(pListImage != NULL)
				pListImage->SetEnableDrag(uiValue == 0);
		}
		m_Settings[eSSC_SKILLLOCK2] = uiValue;
		break;
	default:
		break;
	}
}
//----------------------------------------------------------------
void GameSetting::SetChatFontSize( unsigned int uiValue )
{

}
//----------------------------------------------------------------
void GameSetting::SetAutoReplySecret( unsigned int uiValue )
{

}
//----------------------------------------------------------------
void GameSetting::SetAutoTurnAround( unsigned int uiValue )
{
    // 取消智能转身设置，默认关闭
	//g_bMouseRoleTurn = (bool)uiValue;
}
//----------------------------------------------------------------
void GameSetting::SetAutoMouse( unsigned int uiValue )
{
	g_bMouseMoveMode = (bool)uiValue;
}
//----------------------------------------------------------------
void GameSetting::SetShowHelmet( unsigned int uiValue )
{
	CPlayer* me = theHeroGame.GetPlayerMgr()->GetMe();
	if( me )
	{
		me->ShowHelmetAndSendMsg( (bool)uiValue );
		me->ChangeSkeletonAndEquipAllItem( me->HasFightFlag( eFighting ) );

		//s_CUI_ID_FRAME_PACK.RefeashEquip();
		s_CUI_ID_FRAME_BaseProperty.RefreshEquip();
		//更新界面
		thePlayerRole.UpdateUI();
	}
	else if( g_GameState == G_MAIN )
	{
		MsgShowHelmet msg;
		msg.showHelmet = (bool)uiValue;
		GettheNetworkInput().SendMsg(&msg);
	}
}
//----------------------------------------------------------------
void GameSetting::SetVerticleView( unsigned int uiValue )
{
	getwsCamera()->SetLockCameraMode( (bool)uiValue );
}
//----------------------------------------------------------------
void GameSetting::SetShowNPCName( unsigned int uiValue )
{
	if( m_Settings[eGSC_SHOWPLAYERNAME] && uiValue )
		Config::SetShowPlayerInfo( eALL_NameLvl );
	else if( uiValue )
		Config::SetShowPlayerInfo( eAllNpcMonster_NameLvl );
	else if( m_Settings[eGSC_SHOWPLAYERNAME] )
		Config::SetShowPlayerInfo( eAllPlayer_NameLvl );
	else
		Config::SetShowPlayerInfo( eClose_NameLvl );
}
//----------------------------------------------------------------
void GameSetting::SetShowItemName( unsigned int uiValue )
{
	g_bbshowItemName = (bool)uiValue;
}
//----------------------------------------------------------------
void GameSetting::SetShowPlayerName( unsigned int uiValue )
{
	if( m_Settings[eGSC_SHOWNPCNAME] && uiValue )
		Config::SetShowPlayerInfo( eALL_NameLvl );
	else if( uiValue )
		Config::SetShowPlayerInfo( eAllPlayer_NameLvl );
	else if( m_Settings[eGSC_SHOWNPCNAME] )
		Config::SetShowPlayerInfo( eAllNpcMonster_NameLvl );
	else
		Config::SetShowPlayerInfo( eClose_NameLvl );
}
//----------------------------------------------------------------
void GameSetting::SetShowTitle( unsigned int uiValue )
{

}
//----------------------------------------------------------------
void GameSetting::SetShowPlayerNumber( unsigned int uiValue )
{
	uiValue = uiValue / 4 + 20;//[20 - 280]
	theHeroGame.GetPlayerMgr()->SetPlayerRenderLimit( uiValue );//设定到50
}
//----------------------------------------------------------------
void GameSetting::SetFOV( unsigned int uiValue )
{
	uiValue /= 40;
	g_fCamerFOV = D3DX_PI / 180 * ( 45 + uiValue );
}
//----------------------------------------------------------------
void GameSetting::SetMaxCameraDistance( unsigned int uiValue )
{
	float f1 = (float)( uiValue / 1000.f );
	float fCameraZoomInLimit = getwsCamera()->GetCameraZoomInLimit();
    float fCameraZoomOutLimit = (getwsCamera()->GetCameraDefaultZoomOutLimit()-fCameraZoomInLimit) * f1 * 1.5f + fCameraZoomInLimit;
	float f45DegreeDefaultZoomOutLimit = getwsCamera()->Get45DegreeDefaultCameraZoomOutLimit();
	float f45DegreeCameraZoomOutLimit = getwsCamera()->Get45DegreeCameraZoomOutLimit();
	getwsCamera()->SetCameraZoomOutLimit(fCameraZoomOutLimit); 

	getwsCamera()->Set45DegreeCameraZoomOutLimit( (f45DegreeDefaultZoomOutLimit-fCameraZoomInLimit) * f1 *1.5f + fCameraZoomInLimit );

	float fCurCameraZoom = getwsCamera()->GetCurCameraZoom();
	if( !getwsCamera()->GetLock45DegreeCameraMode() )    // 2.5D视角
    {
        if( fCurCameraZoom > fCameraZoomOutLimit )
        {
			getwsCamera()->SetCurCameraZoom( fCameraZoomOutLimit );
        }
		else if (fCurCameraZoom >=0)
		{
			getwsCamera()->SetCurCameraZoom((f45DegreeDefaultZoomOutLimit-fCameraZoomInLimit) * f1 *1.5f + fCameraZoomInLimit);
		}
		getwsCamera()->Update45DegreeCameraRotate();
    }
    else                                // 3D视角
    {
        if( fCurCameraZoom > f45DegreeCameraZoomOutLimit )
        {
			getwsCamera()->SetCurCameraZoom( f45DegreeCameraZoomOutLimit );
        }
		getwsCamera()->Update45DegreeCameraRotate();
    }
}

//----------------------------------------------------------------
void GameSetting::ShowHpMp( unsigned int uiValue )
{	
	s_CUI_ID_FRAME_Group_Me.SetShowHp((bool)uiValue);
	s_CUI_ID_FRAME_Group_Me.SetShowMp((bool)uiValue);
}
//----------------------------------------------------------------
void GameSetting::ShowFp( unsigned int uiValue )
{
	s_CUI_ID_FRAME_Group_Me.SetShowFp((bool)uiValue);
}
//----------------------------------------------------------------
void GameSetting::Set45Camera( unsigned int uiValue )
{
	CUserData::Instance()->SetViewSet( 1 - uiValue );
	//SystemSetting::Instance()->SetLevel( SystemSetting::eSSC_VIEWSET, 1 - uiValue );
	getwsCamera()->Set45DegreeCameraMode( (bool)uiValue );
}
//----------------------------------------------------------------
void GameSetting::SetFollowCamera( unsigned int uiValue )
{
	getwsCamera()->SetFollowCameraMode( (bool)uiValue );
}
//----------------------------------------------------------------
void GameSetting::ShowHPBar(unsigned int uiValue)
{
	s_CUI_ID_FRAME_GameSetup.SetShowHp((bool)uiValue);//.ShowHP = (bool)uiValue;
}
//----------------------------------------------------------------
void GameSetting::ShowMPBar(unsigned int uiValue)
{
	s_CUI_ID_FRAME_GameSetup.SetShowMp((bool)uiValue);//.ShowMP = (bool)uiValue;
}
//----------------------------------------------------------------
void GameSetting::ShowFPBar(unsigned int uiValue)
{
	s_CUI_ID_FRAME_GameSetup.SetShowFp((bool)uiValue);//.ShowFP = (bool)uiValue;
}
//----------------------------------------------------------------
void GameSetting::ShowChatBackground(unsigned int uiValue)
{
	m_Settings[eGSC_SHOWCHATBACKGROUND] = uiValue;
}
//----------------------------------------------------------------
void GameSetting::SetSound( unsigned int uiValue )
{
	int nActValue = 0;
	bool bSilence = false;
	GetSoundValue( uiValue, nActValue, bSilence );
	if (theHeroGame.IsWindowActive())
	{
		GMusic.SetVolume( ( nActValue * ( 1 - (int)bSilence ) )/4000.f );
	}
	else
	{
		theHeroGame.SetMusicVolume((nActValue * ( 1 - (int)bSilence ) )/4000.f);
	}
}
//----------------------------------------------------------------
void GameSetting::SetSoundEffect( unsigned int uiValue )
{
	int nActValue = 0;
	bool bSilence = false;
	GetSoundValue( uiValue, nActValue, bSilence );
	if (theHeroGame.IsWindowActive())
	{
		GSound.SetVolume( ( nActValue * ( 1 - (int)bSilence  ) )/4000.f );
	}
	else
	{
		theHeroGame.SetSoundVolume(( nActValue * ( 1 - (int)bSilence  ) )/4000.f);
	}
}
//----------------------------------------------------------------
void GameSetting::SetMouseSpeed(unsigned int uiValue)
{
	if (uiValue == 0) // 默认为10
	{
		SystemParametersInfo(SPI_GETMOUSESPEED, 0, &uiValue, 0);
	}
	m_Settings[eGSC_MOUSESPEED] = uiValue;
}
//----------------------------------------------------------------
void GameSetting::SetCameraRotateSpeed(unsigned int uiValue)
{
	//if (uiValue == 0) // 默认为320
	//{
	//	uiValue = 320;
	//}
	m_Settings[eGSC_CAMERAROTATESPEED] = uiValue;
}
//----------------------------------------------------------------
void GameSetting::SetBool( eGameSettingCategory eCategory, 
						  bool bValue )
{
	m_Settings[eCategory] = bValue;
}
//----------------------------------------------------------------
int GameSetting::MakeSoundValue( int nValue, bool bSilence )
{
	int nFinalValue = nValue << 1 | (char)bSilence;
	return nFinalValue;
}
//----------------------------------------------------------------
void GameSetting::GetSoundValue( int nFinalValue, int& nValue, bool& bSilence )
{
	nValue = nFinalValue >> 1;
	bSilence = nFinalValue & 1;
}
//----------------------------------------------------------------