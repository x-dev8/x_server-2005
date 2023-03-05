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
extern BOOL g_bMouseMoveMode; //����ƶ�ģʽ
//extern BOOL g_bMouseRoleTurn; //����ת��

extern GAME_STATE		g_GameState;
//----------------------------------------------------------------
GameSetting* GameSetting::ms_pThis = 0;
//----------------------------------------------------------------
GameSetting::GameSetting()
{
	memset( m_Settings, 0, sizeof( eGameSettingCategory ) * eGSC_TOTAL );
	memset( m_bDirty, 1, sizeof( bool ) * eGSC_TOTAL );

	m_SettingNames[eGSC_CHATFONTSIZE]		= "ChatFontSize";		//���������С
	m_SettingNames[eGSC_AUTOREPLYSECRET]	= "AutoReplySecret";	//�Զ��ظ�����
	m_SettingNames[eGSC_AUTOTURNAROUND]		= "AutoTurnAround";		//����ת��
	m_SettingNames[eGSC_AUTOMOUSE]			= "AutoMouse";			//�������
	m_SettingNames[eGSC_SHOWHELMET]			= "ShowHelmet";			//��ʾͷ��
	m_SettingNames[eGSC_VERTICLEVIEW]		= "VerticleView";		//��ֱ�ӽ�����
	m_SettingNames[eGSC_SHOWNPCNAME]		= "ShowNPCName";		//��ʾNPC����
	m_SettingNames[eGSC_SHOWITEMNAME]		= "ShowItemName";		//��ʾ��Ʒ����
	m_SettingNames[eGSC_SHOWPLAYERNAME]		= "ShowPlayerName";		//��ʾ�������
	m_SettingNames[eGSC_SHOWTITLE]			= "ShowTitle";			//��ʾ�ƺ�
	m_SettingNames[eGSC_SHOWPLAYERNUMBER]	= "ShowPlayerNumber";	//ͬ������
	m_SettingNames[eGSC_FOV]				= "Fov";				//���
	m_SettingNames[eGSC_MAXCAMERADISTANCE]	= "MaxCameraDistance";	//��ͷ������
	m_SettingNames[eGSC_SHOWHPBARMP]		= "ShowHpMp";			//��ʾhp,mp
	m_SettingNames[eGSC_SHOWFP]				= "ShowFp";				//��ʾfp
	m_SettingNames[eGSC_45CAMERA]			= "Camera45";			//45����
	m_SettingNames[eGSC_FOLLOWCAMERA]		= "FollowCamera";		//�������
	m_SettingNames[eGSC_SAVECHATMESSAGE]	= "SaveChatMessage";	//���������¼
	m_SettingNames[eGSC_SHOWHPBAR]			= "ShowHPBar";			//��ʾHP
	m_SettingNames[eGSC_SHOWMPBAR]			= "ShowMPBar";			//��ʾMP
	m_SettingNames[eGSC_SHOWFPBAR]			= "ShowFPBar";			//��ʾFP
	m_SettingNames[eGSC_SHOWCHATBACKGROUND]	= "ShowChatBackground";	//��ʾ���촰�ڱ���
	m_SettingNames[eGSC_MOUSESPEED]			= "MouseSpeed";			//��ʾFP
	m_SettingNames[eGSC_CAMERAROTATESPEED]	= "CameraRotateSpeed";	//��ʾ���촰�ڱ���
	m_SettingNames[eGSC_SelfName]			= "SelfName";			//��������
	m_SettingNames[eGSC_SelfHp]				= "SelfHp";				//����Ѫ��
	m_SettingNames[eGSC_SelfTitle]			= "SelfTitle";			//����ƺ�
	m_SettingNames[eGSC_SelfGuild]			= "SelfGuild";			//������
	m_SettingNames[eGSC_SelfTong]			= "SelfTong";			//��������
	m_SettingNames[eGSC_SelfMp]				= "SelfMp"	;			//��������
	m_SettingNames[eGSC_SelfPetName]		= "SelfPetName";		//�����������
	m_SettingNames[eGSC_SelfPetHp]			= "SelfPetHp"	;		//�������Ѫ��
	m_SettingNames[eGSC_TeamPlayerName]		= "TeamPlayerName";		//����ͷ������
	m_SettingNames[eGSC_TeamPlayerHp]		= "TeamPlayerHp";		//����ͷ��Ѫ��
	m_SettingNames[eGSC_TeamPlayerTitle]	= "TeamPlayerTitle";	//����ͷ���ƺ�
	m_SettingNames[eGSC_TeamPlayerGuild]	= "TeamPlayerGuild";	//����ͷ�����
	m_SettingNames[eGSC_TeamPlayerTong]		= "TeamPlayerTong";		//����ͷ������
	m_SettingNames[eGSC_TeamPlayerPetName]	= "TeamPlayerPetName";	//�����ٻ���ͷ������
	m_SettingNames[eGSC_TeamPlayerPetHp]	= "TeamPlayerPetHp";	//�����ٻ���ͷ��Ѫ��
	m_SettingNames[eGSC_OtherPlayerName]	= "OtherPlayerName";	//�Ƕ���ͷ������
	m_SettingNames[eGSC_OtherPlayerHp]		= "OtherPlayerHp";		//�Ƕ���ͷ��Ѫ��
	m_SettingNames[eGSC_OtherPlayerTitle]	= "OtherPlayerTitle";	//�Ƕ���ͷ���ƺ�
	m_SettingNames[eGSC_OtherPlayerGuild]	= "OtherPlayerGuild";	//�Ƕ���ͷ�����
	m_SettingNames[eGSC_OtherPlayerTong]	= "OtherPlayerTong";	//�Ƕ���ͷ������
	m_SettingNames[eGSC_OtherPlayerPetName]	= "OtherPlayerPetName";	//�Ƕ����ٻ���ͷ������
	m_SettingNames[eGSC_OtherPlayerPetHp]	= "OtherPlayerPetHp";	//�Ƕ����ٻ���ͷ��Ѫ��
	m_SettingNames[eGSC_FightFlyText]		= "FightFlyText";		//ս��Ʈ��
	m_SettingNames[eGSC_RefuseStrangerMsg]	= "RefuseStrangerMsg";	//�ܾ�İ���˶���Ϣ
	m_SettingNames[eGSC_RefuseAllMsg]		= "RefuseAllMsg";		//�ܾ������˶���Ϣ
	m_SettingNames[eGSC_MiniMapTeam]		= "MiniMapTeam";		//С��ͼ��ʾ����
	m_SettingNames[eGSC_MiniMapNpc]			= "MiniMapNpc";			//С��ͼ��ʾNpc
	m_SettingNames[eGSC_MiniMapMonster]		= "MiniMapMonster";		//С��ͼ��ʾMonster
	m_SettingNames[eGSC_MiniMapFriend]		= "MiniMapFriend";		//С��ͼ��ʾ����
	m_SettingNames[eGSC_MiniMapGuild]		= "MiniMapGuild";		//С��ͼ��ʾ����
	m_SettingNames[eGSC_MiniMapEnemy]		= "MiniMapEnemy";		//С��ͼ��ʾ����
	m_SettingNames[eGSC_MiniMapOther]		= "MiniMapOther";		//С��ͼ��ʾ�������	
	m_SettingNames[eGSC_ChatSelf]			= "ChatSelf";			//��ʾ������������
	m_SettingNames[eGSC_ChatTeam]			= "ChatTeam";			//��ʾ������������
	m_SettingNames[eGSC_ChatOther]			= "ChatOther";			//��ʾ��������������
	m_SettingNames[eGSC_NpcName]			= "NpcName";			//NPC����
	m_SettingNames[eGSC_NpcHp]				= "NpcHp";				//NPCѪ��
	m_SettingNames[eGSC_NpcTitle]			= "NpcTitle";			//NPC����
	m_SettingNames[eGSC_MonsterName]		= "MonsterName";		//Monster����
	m_SettingNames[eGSC_MonsterHp]			= "MonsterHp";			//MonsterѪ��
	m_SettingNames[eGSC_ItemName]			= "ItemName";			//����Item����
	m_SettingNames[eGSC_SOUND]				= "Sound";				//������С
	m_SettingNames[eGSC_SOUNDEFFECT]		= "SoundEffect";		//������Ч
    m_SettingNames[eGSC_ChatNpc]			= "ChatNpc";			//��ʾNPC��������
    m_SettingNames[eGSC_ChatMonster]		= "ChatMonster";		//��ʾ������������
    m_SettingNames[eGSC_SelfPetTitle]		= "SelfPetTitle";		//�Լ�����ƺ�
    m_SettingNames[eGSC_TeamPetTitle]		= "TeamPetTitle";		//���ѳ���ƺ�
    m_SettingNames[eGSC_OtherPetTitle]			= "OtherPetTitle";		//�Ƕ��ѳ���ƺ�
    m_SettingNames[eGSC_SelfEffect]				= "SelfEffect";		    //������Ч
    m_SettingNames[eGSC_TeamPlayerEffect]		= "TeamPlayerEffect";   //������Ч
    m_SettingNames[eGSC_TeamPlayerModel]		= "TeamPlayerModel";	//��������ģ��
    m_SettingNames[eGSC_OtherPlayerEffect]		= "OtherPlayerEffect";  //�Ƕ�����Ч
    m_SettingNames[eGSC_OtherPlayerModel]		= "OtherPlayerModel";   //�Ƕ�������ģ��
    m_SettingNames[eGSC_RefuseAddFriendInFight]	= "RefuseAddFriendInFight"; //ս���оܾ��Ӻ�������
    m_SettingNames[eGSC_RefuseAddTeamInFight]	= "RefuseAddTeamInFight";   //ս���оܾ��������
    m_SettingNames[eGSC_RefuseAddGangInFight]	= "RefuseAddGangInFight";   //ս���оܾ���������
    m_SettingNames[eGSC_RefuseDuelInFight]	    = "RefuseDuelInFight";      //ս���оܾ���������
    m_SettingNames[eGSC_RefuseBargainInFight]	= "RefuseBargainInFight";   //ս���оܾ���������
    m_SettingNames[eGSC_RefuseHugInFight]		= "RefuseHugInFight";   //ս���оܾ�ӵ������
    m_SettingNames[eGSC_RefuseAddFriend]		= "RefuseAddFriend";    //��ս���оܾ��Ӻ�������
    m_SettingNames[eGSC_RefuseAddTeam]			= "RefuseAddTeam";      //��ս���оܾ��������
    m_SettingNames[eGSC_RefuseAddGang]			= "RefuseAddGang";      //��ս���оܾ���������
    m_SettingNames[eGSC_RefuseDuel]				= "RefuseDuel";         //��ս���оܾ���������
    m_SettingNames[eGSC_RefuseBargain]			= "RefuseBargain";      //��ս���оܾ���������
    m_SettingNames[eGSC_RefuseHug]				= "RefuseHug";          //��ս���оܾ�ӵ������
	m_SettingNames[eGSC_IntroductionEnable]	    = "Introduction";          //��ս���оܾ�ӵ������
	m_SettingNames[eGSC_ChatListWidth]	        = "ChatListWidth";          //�����Ŀ��
	m_SettingNames[eGSC_ChatListHeight]	        = "ChatListHeight";          //�����ĸ߶�
	
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
    m_SettingNames[eSSC_SKILLLOCK           ]   = "SkillLock";      //����������
    m_SettingNames[eSSC_SKILLLOCK2          ]   = "SkillLock2";  //��������չ����
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

		// ���ݾɵ��ļ�
		if( !bRet )	// ���ɵ��ļ���ʽ
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

		//lyh++ ������Ҳ����д浵������ϷĬ����ʾ�������
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

	// ɾ�����ļ���ʽ
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
        /*if( theHeroGame.GetPlayerMgr() )//lyh-- �������������ݲ���Ҫд�ļ�
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
    // ȡ������ת�����ã�Ĭ�Ϲر�
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
		//���½���
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
	theHeroGame.GetPlayerMgr()->SetPlayerRenderLimit( uiValue );//�趨��50
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
	if( !getwsCamera()->GetLock45DegreeCameraMode() )    // 2.5D�ӽ�
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
    else                                // 3D�ӽ�
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
	if (uiValue == 0) // Ĭ��Ϊ10
	{
		SystemParametersInfo(SPI_GETMOUSESPEED, 0, &uiValue, 0);
	}
	m_Settings[eGSC_MOUSESPEED] = uiValue;
}
//----------------------------------------------------------------
void GameSetting::SetCameraRotateSpeed(unsigned int uiValue)
{
	//if (uiValue == 0) // Ĭ��Ϊ320
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