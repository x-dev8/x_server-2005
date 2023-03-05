// NpcEditDlg.cpp : implementation file
//

#include "stdafx.h"
#include "NpcEditDlg.h"
#include "tstring.h"
#include "NpcInfo.h"
#include "MapConfig.h"
#include "RapidXml/MeRapidXml.h"
#include "Edit/NpcString.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


class MySort
{
public:
	MySort(){}
	~MySort()
	{

	}

	bool operator()(MapConfig::MapData _mapData1,MapConfig::MapData _mapData2)
	{
		if(_mapData1.Id < _mapData2.Id)
		  return true;
		return false;
	}
// 
// 	MapConfig::MapData m_MapData;
};

// CNpcEditDlg dialog

CNpcEditDlg::CNpcEditDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CNpcEditDlg::IDD, pParent)
	, m_mapID(0)
	, m_fPosX(0)
	, m_fPosY(0)
	, m_strNote(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_NpcID = -1;
}

void CNpcEditDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_TREE1, m_TreeCtrl);
	// 	DDX_Text(pDX, IDC_CHGMAPID, m_mapID);
	// 	DDV_MinMaxInt(pDX, m_mapID, 0, 120);
	// 	DDX_Text(pDX, IDC_XOFFSET, m_fPosX);
	// 	DDX_Text(pDX, IDC_YOFFSET, m_fPosY);

	//	DDX_Control(pDX, IDC_COMBO1, m_ComModelId);
	DDX_Text(pDX, IDC_STANOTE, m_strNote);
	DDX_Control(pDX, IDC_NPCMENU_STRINGID, m_NpcMenuStringID);
	//DDX_Control(pDX, IDC_LIST1, m_ListMenuContent);
	DDX_Control(pDX, IDC_NPCMENU_LIST, m_NpcMenuList);
	DDX_Control(pDX, IDC_TREE2, mEventActionTree);
}

BEGIN_MESSAGE_MAP(CNpcEditDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_QUERYFILE, &CNpcEditDlg::OnBnClickedQueryfile)
//	ON_BN_CLICKED(IDC_INSERT, &CNpcEditDlg::OnBnClickedInsert)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE1, &CNpcEditDlg::OnTvnSelchangedTree1)
/*	ON_BN_CLICKED(IDC_LOADXML, &CNpcEditDlg::OnBnClickedLoadxml)*/
//	ON_BN_CLICKED(IDC_NPCUPDATE, &CNpcEditDlg::OnBnClickedNpcupdate)
/*	ON_BN_CLICKED(IDC_NPCSAVE, &CNpcEditDlg::OnBnClickedNpcsave)*/
	ON_BN_CLICKED(IDC_TALKUPDATE, &CNpcEditDlg::OnBnClickedTalkupdate)
	ON_BN_CLICKED(IDC_TALKINSERT, &CNpcEditDlg::OnBnClickedTalkinsert)
	ON_BN_CLICKED(IDC_ACTIONUPDATE, &CNpcEditDlg::OnBnClickedActionupdate)
	ON_BN_CLICKED(IDC_ACTIONINSERT, &CNpcEditDlg::OnBnClickedActioninsert)
	ON_BN_CLICKED(IDC_ELAPINSERT, &CNpcEditDlg::OnBnClickedElapinsert)
	ON_BN_CLICKED(IDC_ELAPUPDATE, &CNpcEditDlg::OnBnClickedElapupdate)
//	ON_COMMAND(ID_SAVEXML, &CNpcEditDlg::OnSavexml)
	ON_BN_CLICKED(IDC_ADDPP, &CNpcEditDlg::OnBnClickedAddpp)
	ON_BN_CLICKED(IDC_DELPP, &CNpcEditDlg::OnBnClickedDelpp)
//	ON_BN_CLICKED(IDC_RECOVERY, &CNpcEditDlg::OnBnClickedRecovery)
	ON_WM_CLOSE()
	ON_WM_DESTROY()
	ON_BN_CLICKED(IDC_NPCMODIFY, &CNpcEditDlg::OnBnClickedNpcmodify)
    //ON_BN_CLICKED(IDC_DEL_NPCMENU, &CNpcEditDlg::OnDelNpcMenu)
    ON_BN_CLICKED(IDC_NPCMENU_UPDATE, &CNpcEditDlg::OnNpcMenuUpdate)
    ON_EN_CHANGE(IDC_NPCMENU_STRINGID, &CNpcEditDlg::OnChangeNpcMenuStringId)
    ON_BN_CLICKED(IDC_BUTTON2, &CNpcEditDlg::OnClickActScript)
	ON_CBN_SELCHANGE(IDC_COMRTYPE, &CNpcEditDlg::OnCbnSelchangeComrtype)
	ON_CBN_SELCHANGE(IDC_COMETYPE, &CNpcEditDlg::OnCbnSelchangeCometype)
	ON_BN_CLICKED(IDC_BNACTION_ADD, &CNpcEditDlg::OnBnClickedBnactionAdd)
	ON_BN_CLICKED(IDC_BNACTION_DELETE, &CNpcEditDlg::OnBnClickedBnactionDelete)
	ON_NOTIFY(TVN_SELCHANGED, IDC_TREE2, &CNpcEditDlg::OnTvnSelchangedTree2)
	ON_BN_CLICKED(IDC_BNREQUIRE_INSERT, &CNpcEditDlg::OnBnClickedBnrequireInsert)
	ON_BN_CLICKED(IDC_BNEVENT_INSERT, &CNpcEditDlg::OnBnClickedBneventInsert)
	ON_BN_CLICKED(IDC_BNREQUIRE_MODIFY, &CNpcEditDlg::OnBnClickedBnrequireModify)
	ON_BN_CLICKED(IDC_BNEVENT_MODIFY, &CNpcEditDlg::OnBnClickedBneventModify)
	ON_BN_CLICKED(IDC_Btn_Fight_Update, &CNpcEditDlg::OnBnClickedBtnFightUpdate)
END_MESSAGE_MAP()


// CNpcEditDlg message handlers
extern bool g_IsArtUsing ;

BOOL CNpcEditDlg::PreTranslateMessage(MSG* pMsg)
{
    if (WM_KEYFIRST <= pMsg->message && pMsg->message <= WM_KEYLAST) 
    {
        if(pMsg->wParam==VK_ESCAPE )
        {
            return TRUE;
        }
        if (pMsg->wParam == VK_F1)
        {
            OnInsertNewItem();
            return TRUE;
        }
        if (pMsg->wParam == VK_DELETE)
        {
            OnDelNpcMenu();
        }
    }
    return CDialog::PreTranslateMessage(pMsg);
}

BOOL CNpcEditDlg::OnInitDialog()
{
	CDialog::OnInitDialog();


	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon


	if (!g_IsArtUsing)
	{
		//初始化CComBox控件属性
		CComboBox *pBox = NULL;

		pBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMMAP));
		if((pBox != NULL)&&(!InitComboxData("..\\Data\\World\\Map.config","Map","Id",pBox)))
			::MessageBox(NULL,"Load Map.config failed!","Warnning",MB_OK);

		pBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMNPCSTR));
		if((pBox != NULL)&&(!InitComboxData("..\\Data\\Config\\Npc.string","String","Id",pBox)))
			::MessageBox(NULL,"Load Model.config failed!","Warnning",MB_OK);

		pBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMMTYPE));
		if((pBox != NULL)&&(!InitComboxData("..\\Data\\Config\\Minimap.config","Sort","Name",pBox)))
			::MessageBox(NULL,"Load Minimap.config failed!","Warnning",MB_OK);

		pBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMRTYPE));
		if ( (pBox != NULL) && (!InitComboxDataType( pBox, Req_Max )) )
		{
			::MessageBox(NULL,"Initial ReqType failed!","Warnning",MB_OK);
		}

		pBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMETYPE));
		if ( (pBox != NULL) && (!InitComboxDataType( pBox, Event_Max )) )
		{
			::MessageBox(NULL,"Initial EventType failed!","Warnning",MB_OK);
		}
		
		pBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMBONPCType));
		if ( (pBox != NULL) && (!InitComboxNpcType( pBox )) )
		{
			::MessageBox(NULL,"Initial NPCType failed!","Warnning",MB_OK);
		}

		OnCbnSelchangeComrtype();
		OnCbnSelchangeCometype();


		static_cast<CComboBox*>(GetDlgItem(IDC_COMNPCSTR))->SetCurSel(0);
	}

    // 预先载入Npc.string，载入进m_TalkSetForMenu容器
    if ( !theNpcStringForMenu.LoadConfigForMenu("..\\Data\\Config\\Npc.string") )
    {
        MessageBox(_T("载入Npc.string失败，请检查！"), "Warning", MB_OK);
    }

 	 //初始化控件值
     // InitGrapicsData();
//    
// 	 //创建CDlgNpcPosUpdate
// 	if(!m_DlgNpcPosUpdate.Create(CNpcPosUpdate::IDD,this))
// 	{
// 		return false;
// 	}
// 	//m_DlgNpcPosUpdate.ShowWindow(SW_SHOW);
// 	m_DlgNpcPosUpdate.EnableWindow(false);
//    
// 	//创建CDlgNpcString
// 	if(!m_DlgNpcString.Create(CDlgNpcString::IDD,this))
// 	{
// 		return false;
// 	}
// 	//m_DlgNpcString.ShowWindow(SW_SHOW);
// 	m_DlgNpcString.EnableWindow(false);

//	SetMaxNpcInfo();
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CNpcEditDlg::InitGrapicsData()
{
	ClearTalkProtery();
	ClearActionProtery();
	ClearElpaseProtery();
	ClearNpcProtery();

    InitNpcData(m_NpcID);
	InitTreeControlData(FILTER_NONE);

    this->SetFocus();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CNpcEditDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CNpcEditDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

bool CNpcEditDlg::SaveConfig(const char *pszPath)
{
    if (pszPath == NULL || *pszPath == 0)
    { return false;}

	UpdateActionsToNpc();	//更新条件触发事件到npc，准备写xml

 	MeXmlDocument xDoc;

    xDoc.InsertEndChild(MeXmlDeclaration("1.0", "UTF-8", "yes"));
    MeXmlElement* pRoot = xDoc.InsertEndChild("Project")->ToElement();
    if (pRoot == NULL)
    { return false;}

    MeXmlElement* pNpcs = pRoot->InsertEndChild("Npcs")->ToElement();
    if (pNpcs == NULL)
    { return false;}

	NpcInfo::Npcs::iterator iter = theNpcInfo.npcs_.begin();
	NpcInfo::Npcs::iterator end  = theNpcInfo.npcs_.end();

	for ( ; iter != end; ++iter)
	{
		MeXmlElement* pNpc = pNpcs->InsertEndChild(("Npc"))->ToElement();			
		pNpc->SetAttribute("Id", iter->second.id);

		Common::_tstring name = iter->second.name;		
		pNpc->SetAttribute("Name", name.toUTF8().c_str());


		if (iter->second.pinyin.length() != 0)
		{
			Common::_tstring pinYin = iter->second.pinyin;
			pNpc->SetAttribute("PinYin",pinYin.toUTF8().c_str());
		}
		if (iter->second.strSoundPath.length() != 0)
		{
			Common::_tstring SoundPath = iter->second.strSoundPath;
			pNpc->SetAttribute("SoundPath",SoundPath.toUTF8().c_str());
		}

		pNpc->SetAttribute("MapId", iter->second.mapId);
		pNpc->SetAttribute("Level", iter->second.level);
		pNpc->SetAttribute("Type", iter->second.type);
		pNpc->SetAttribute("ModelId", iter->second.modelId);
		pNpc->SetDoubleAttribute("PositionX", static_cast<double>(iter->second.x));
		pNpc->SetDoubleAttribute("PositionY", static_cast<double>(iter->second.y));

		int posZ = static_cast<int>(iter->second.z);
		if(posZ == 40000)
			pNpc->SetAttribute("PositionZ",posZ);
		else
		    pNpc->SetDoubleAttribute("PositionZ",iter->second.z);

		pNpc->SetAttribute("MovePath", iter->second.movePath);
		pNpc->SetAttribute("Direction", iter->second.direction);
		pNpc->SetAttribute("CanChangeDirection", static_cast<int>(iter->second.canChangeDirection));
		
		Common::_tstring scriptFile = iter->second.triggerScript;		
		pNpc->SetAttribute("ScriptFile", scriptFile.toUTF8().c_str());  // 触发脚本

        Common::_tstring actScriptFile = iter->second.actionScript;
        pNpc->SetAttribute("ActionScriptFile", actScriptFile.toUTF8().c_str()); // 动作脚本
		
		pNpc->SetAttribute("IsMiniShow", static_cast<int>(iter->second.isMiniShow));
		pNpc->SetAttribute("IsWorldShow",static_cast<int>(iter->second.isWorldShow));

		pNpc->SetAttribute("IsCollision", static_cast<int>(iter->second.isCollision));



		pNpc->SetAttribute("IsDynamicCollision", static_cast<int>(iter->second.isDynamicCollision));
		
		Common::_tstring title = iter->second.title;		
		pNpc->SetAttribute("Title", title.toUTF8().c_str());
		
		Common::_tstring npcTips = iter->second.tip;
        pNpc->SetAttribute("NpcTips",npcTips.toUTF8().c_str());

		Common::_tstring headPicture = iter->second.strHeadPicture;		
		pNpc->SetAttribute("HeadPicture", headPicture.toUTF8().c_str());			
		pNpc->SetDoubleAttribute("BodyScale", iter->second.bodyScale);

        pNpc->SetAttribute("Country", static_cast<unsigned char>(iter->second.uchCountryID));
        pNpc->SetAttribute("MenuId", iter->second.nTaskMenu);
		pNpc->SetAttribute("Phyle", iter->second.phyle );

		//保存 npc fightinfo的信息
		int fightInfoCount = (int)iter->second.fightData.size();
		for ( int i = 0; i < fightInfoCount; i ++ )
		{
			MeXmlElement *pFightInfo = pNpc->InsertEndChild(("FightInfo"))->ToElement();
			
			const NpcInfo::FightInfo& xFightInfo = iter->second.fightData[i];
			for (int i=0; i<3; ++i)
			{
				char szSkillId[20] = {0};
				sprintf_s(szSkillId, sizeof(szSkillId) - 1, "Skill%dId", i+1);
				pFightInfo->SetAttribute(szSkillId, xFightInfo.skills[i].skillId);

				char szSkillLevel[20] = {0};
				sprintf_s(szSkillLevel, sizeof(szSkillLevel) - 1, "Skill%dLevel", i+1);
				pFightInfo->SetAttribute(szSkillLevel, xFightInfo.skills[i].skillLevel);

				char szSkillRate[20] = {0};
				sprintf_s(szSkillRate, sizeof(szSkillRate) - 1, "Skill%dRate", i+1);
				pFightInfo->SetAttribute(szSkillRate, xFightInfo.skills[i].skillRate);
			}

			pFightInfo->SetDoubleAttribute("BodyLength", xFightInfo.bodyLength);

			pFightInfo->SetAttribute("Level", xFightInfo.level);


			pFightInfo->SetAttribute("HpMax", xFightInfo.hpMax);

			pFightInfo->SetAttribute("EnergyMax", xFightInfo.hpMax);

			pFightInfo->SetAttribute("Exact", xFightInfo.exact);

			pFightInfo->SetAttribute("Dodge", xFightInfo.dodge);

			pFightInfo->SetAttribute("AttackSpeed", xFightInfo.attackSpeed);

			pFightInfo->SetAttribute("Attack", xFightInfo.attackPhysics);

			pFightInfo->SetAttribute("Attack", xFightInfo.attackMagic);

			pFightInfo->SetDoubleAttribute("Critical", xFightInfo.critical);

			pFightInfo->SetAttribute("CriticalIntensity", xFightInfo.criticalIntensity);

			pFightInfo->SetAttribute("Tenacity", xFightInfo.tenacity);

			pFightInfo->SetDoubleAttribute("DefnedShort", xFightInfo.defendPhysics);

			pFightInfo->SetDoubleAttribute("DefendLong", xFightInfo.defendPhysics);

			pFightInfo->SetDoubleAttribute("DefnedMagic", xFightInfo.defendMagic);

			pFightInfo->SetAttribute("NormalAttackMin", xFightInfo.normalAttackMin);

			pFightInfo->SetAttribute("NormalAttackMax", xFightInfo.normalAttackMax);

			pFightInfo->SetAttribute("View", xFightInfo.view);

			pFightInfo->SetAttribute("FightView", xFightInfo.fightView);

			pFightInfo->SetAttribute("CatchTime", xFightInfo.catchTime);

			pFightInfo->SetDoubleAttribute("MoveSpeed", xFightInfo.moveSpeed);

			pFightInfo->SetDoubleAttribute("MoveStep", xFightInfo.moveStep);

			pFightInfo->SetDoubleAttribute("IdleMoveSpeed", xFightInfo.idleMoveSpeed);

			pFightInfo->SetDoubleAttribute("IdleMoveStep", xFightInfo.idleMoveStep);

			pFightInfo->SetAttribute("ReliveTime", xFightInfo.reliveTime);

			pFightInfo->SetAttribute("DeadScript", xFightInfo.deadScript.c_str());

			pFightInfo->SetAttribute("IsInitiative", xFightInfo.isInitiative);

			pFightInfo->SetAttribute("DisappearTime", xFightInfo.disappearTime);

			pFightInfo->SetAttribute("EnmityDecRate", xFightInfo.enmityDecRate);

			pFightInfo->SetAttribute("EnmityView", xFightInfo.enmityView);

			pFightInfo->SetAttribute("MaxRange", xFightInfo.maxRange);

			pFightInfo->SetAttribute("ChangePassive", xFightInfo.changePassive);

			pFightInfo->SetAttribute("PassiveTime", xFightInfo.passiveTime);

			pFightInfo->SetAttribute("BaseEnmityRange", xFightInfo.baseEnmityRange);

			pFightInfo->SetAttribute("Intergal", xFightInfo.integral);

			pFightInfo->SetAttribute("RouteId", xFightInfo.routeId);

		}

		int nSize = iter->second.vctActionData.size();
		for (int i = 0; i < nSize ;++i)
		{
			MeXmlElement *pElapseTime = pNpc->InsertEndChild(("ElapseTime"))->ToElement();
			pElapseTime->SetAttribute("Id",iter->second.vctActionData[i].shId);
			pElapseTime->SetAttribute("Time",iter->second.vctActionData[i].shElapseTime);
			pElapseTime->SetAttribute("NextTimeId",iter->second.vctActionData[i].shNextId);

			//保存Actions
			int nAmount = iter->second.vctActionData[i].vctActions.size();
			if(nAmount > 0)
			{
				//Insert Actions
				MeXmlElement *pXmlActions = pElapseTime->InsertEndChild(("Actions"))->ToElement();
				//Insert Action
				if(NULL !=pXmlActions)
				{
					for (int nAction = 0; nAction < nAmount ; ++nAction)
					{
						 //int num = iter->second.vctActionData[i].vctActions[nAction]
						MeXmlElement *pXmlAction = pXmlActions->InsertEndChild(("Action"))->ToElement();
						if(NULL != pXmlAction)
						{
							pXmlAction->SetAttribute("Name",iter->second.vctActionData[i].vctActions[nAction].strAnimName.c_str());
							pXmlAction->SetAttribute("Probability",iter->second.vctActionData[i].vctActions[nAction].shProbability);
						}
				    }
				}
			}

			//保存Talks
			nAmount = iter->second.vctActionData[i].vctTalks.size();
			if(nAmount > 0)
			{
				//Insert Talks
				MeXmlElement *pXmlTalks = pElapseTime->InsertEndChild(("Talks"))->ToElement();
				if(NULL != pXmlTalks)
				{
					for (int nTalk = 0; nTalk < nAmount ; ++nTalk)
					{
						MeXmlElement *pXmlTalk = pXmlTalks->InsertEndChild(("Talk"))->ToElement();
						if(pXmlTalk)
						{
							pXmlTalk->SetAttribute("StringId",iter->second.vctActionData[i].vctTalks[nTalk].shStringId);
							pXmlTalk->SetAttribute("Probability",iter->second.vctActionData[i].vctTalks[nTalk].shProbability);
						}
					}
				}
			}
		}

		//条件触发事件~
		MeXmlElement *pActions = pNpc->InsertEndChild("Actions")->ToElement();
		int actSize = iter->second.npcAct.GetSize();
		for ( int idx = 0; idx < actSize; idx ++ )
		{
			MeXmlElement *pAction = pActions->InsertEndChild("Action")->ToElement();
			Action* act = iter->second.npcAct.GetOneActionByIndex(idx);


		if(iter->second.fightData.size() > 0)
		{
			//战斗属性，如果有，只会有一个这样的节点。
			MeXmlElement *pFightData = pNpc->InsertEndChild(("FightInfo"))->ToElement();

			const NpcInfo::FightInfo &info = iter->second.fightData.front();
			pFightData->SetAttribute("View", info.view);
		}
			MeXmlElement* pRequires = pAction->InsertEndChild("Requires")->ToElement();
			int mustCount = (int)act->vecMustTerm.size();
			for ( int mustIdx = 0; mustIdx < mustCount; mustIdx ++ )
			{
				MeXmlElement* pRequire = pRequires->InsertEndChild("Require")->ToElement();
				pRequire->SetAttribute( "Type", (int)act->vecMustTerm[mustIdx].eType );
				if ( act->vecMustTerm[mustIdx].eType == Req_Dislen || act->vecMustTerm[mustIdx].eType == Req_Level )
				{
					pRequire->SetAttribute( "Min", (int)act->vecMustTerm[mustIdx].fMin );
					pRequire->SetAttribute( "Max", (int)act->vecMustTerm[mustIdx].fMax );
				}
				else if ( act->vecMustTerm[mustIdx].eType == Req_Sex )
				{
					pRequire->SetAttribute( "Sex", act->vecMustTerm[mustIdx].nSex );
				}
				else if ( act->vecMustTerm[mustIdx].eType == Req_Task )
				{
					pRequire->SetAttribute( "TaskID", act->vecMustTerm[mustIdx].nTaskID );
				}
				pRequire->SetAttribute( "Need", "1" );
			}

			int probCount = (int)act->vecProbilityTerm.size();
			for ( int probIdx = 0; probIdx < probCount; probIdx ++ )
			{
				MeXmlElement* pRequire = pRequires->InsertEndChild("Require")->ToElement();
				pRequire->SetAttribute( "Type", (int)act->vecProbilityTerm[probIdx].eType );
				if ( act->vecProbilityTerm[probIdx].eType == Req_Dislen || act->vecProbilityTerm[probIdx].eType == Req_Level )
				{
					pRequire->SetAttribute( "Min", (int)act->vecProbilityTerm[probIdx].fMin );
					pRequire->SetAttribute( "Max", (int)act->vecProbilityTerm[probIdx].fMax );
				}
				else if ( act->vecProbilityTerm[probIdx].eType == Req_Sex )
				{
					pRequire->SetAttribute( "Sex", act->vecProbilityTerm[probIdx].nSex );
				}
				else if ( act->vecProbilityTerm[probIdx].eType == Req_Task )
				{
					pRequire->SetAttribute( "TaskID", act->vecProbilityTerm[probIdx].nTaskID );
				}
				pRequire->SetAttribute( "Need", "0" );
			}

			MeXmlElement* pEvents = pAction->InsertEndChild("Events")->ToElement();
			if ( act->talk.nStringId > 0 )
			{
				MeXmlElement* pEvent = pEvents->InsertEndChild("Event")->ToElement();
				pEvent->SetAttribute( "Type", "1" );
				pEvent->SetAttribute( "StringId", act->talk.nStringId );
				pEvent->SetAttribute( "Probability", act->talk.nProbability );
				pEvent->SetAttribute( "DelayTime", act->talk.nDelayTime );
			}
			if ( act->anim.strType.empty() == false )
			{
				MeXmlElement* pEvent = pEvents->InsertEndChild("Event")->ToElement();
				pEvent->SetAttribute( "Type", "2" );
				pEvent->SetAttribute( "Name", act->anim.strType.c_str() );
				pEvent->SetAttribute( "Probability", act->anim.nProbability );
				pEvent->SetAttribute( "DelayTime", act->anim.nDelayTime );
			}
			if ( act->autoFace.bIsAutoFace == true )
			{
				MeXmlElement* pEvent = pEvents->InsertEndChild("Event")->ToElement();
				pEvent->SetAttribute( "Type", "3" );
				pEvent->SetAttribute( "AutoFace", "1" );
				pEvent->SetAttribute( "Probability", act->autoFace.nProbability );
				pEvent->SetAttribute( "DelayTime", act->autoFace.nDelayTime );
			}
		}

	}
	return xDoc.SaveFile(pszPath);
	//}
	//return false;
}


void CNpcEditDlg::OnBnClickedQueryfile()
{
	CFileDialog dlgFile(true);
	CString fileName;
	dlgFile.GetOFN().lpstrFile = fileName.GetBuffer(1024);
	dlgFile.GetOFN().nMaxFile  = 1024;
	dlgFile.GetOFN().lpstrFilter = "Script(*.script)\0*.script\0All File(*.*)\0*.*\0\0";

	INT_PTR nResult = dlgFile.DoModal();
	CWnd *pWindow = (CWnd*)GetDlgItem(IDC_ScriptFile);
	if(NULL != pWindow)
	{
		int nLeft = fileName.Find("Data");
		if(nLeft == -1)
		{
			::MessageBox(NULL,"路径错误!","Warnning",MB_OK);
			return;
		}
		CString subStr = fileName.GetBuffer();
		subStr = subStr.Right(subStr.GetLength() - nLeft);
//		int nLen = fileName.GetLength();
//		fileName = fileName.Right(fileName.GetLength() - nLeft);

		pWindow->SetWindowText(subStr.GetBuffer()/*fileName.GetBuffer(0)*/);
	}
	fileName.ReleaseBuffer();
}

void CNpcEditDlg::OnClickActScript()
{
    // 打开Npc动作脚本
    CFileDialog dlgFile(true);
    CString fileName;
    dlgFile.GetOFN().lpstrFile = fileName.GetBuffer(1024);
    dlgFile.GetOFN().nMaxFile = 1024;
    dlgFile.GetOFN().lpstrFilter = "Script(*.lua)\0*.lua\0*.LUA\0All File(*.*)\0*.*\0\0";

    INT_PTR nResult = dlgFile.DoModal();
    CWnd* pWnd = (CWnd*)GetDlgItem(IDC_ACTIONSCRIPT);
    if ( NULL != pWnd )
    {
        int nLeft = fileName.Find("Data");
        if (nLeft == -1)
        {
            ::MessageBox(NULL, "路径错误!", "Warnning", MB_OK | MB_ICONWARNING);
            return;
        }
        CString subStr = fileName.GetBuffer();
        subStr = subStr.Right(subStr.GetLength() - nLeft);
        pWnd->SetWindowText(subStr.GetBuffer());
    }
    fileName.ReleaseBuffer();
}


void CNpcEditDlg::OnBnClickedInsert()
{
	HTREEITEM hItem = m_TreeCtrl.GetSelectedItem();
	CString   cItemText = m_TreeCtrl.GetItemText(hItem);

	if(!IsNpcNode(cItemText))
	{
		::MessageBox(NULL,"请选择Npc!","Warnning",MB_OK);
		return;
	}
	int nNpcId = atoi(ParseString(cItemText));

	NpcInfo::Npc npc;
	if(GetNpcProtery(npc))
	{
		//npc.vctActionData.clear();

		NpcInfo::Npc *pNpc = theNpcInfo.GetNpcByStaticId(npc.id);
		if(pNpc != NULL)
		{
			::MessageBox(NULL,"NpcId重复!","Warnning",MB_OK);
			return;
		}

		HTREEITEM hParent = m_TreeCtrl.GetParentItem(hItem); //获得该父节点
		CString   cParentText = m_TreeCtrl.GetItemText(hParent);

		int  nLeft = static_cast<int>(cParentText.Find('[')) + 1;
		int  nRight = static_cast<int>(cParentText.Find(']'));
		cParentText = cParentText.Right(cParentText.GetLength() - nLeft);
		cParentText = cParentText.Left(nRight - nLeft);

		int mapID = atoi(cParentText.GetBuffer());
		if(mapID != npc.mapId)
		{
			::MessageBox(NULL,"NpcMapID不属于这个地图分组!","Warnning",MB_OK);
			return;
		}

		theNpcInfo.AddNpc(npc);

		char szWord[32];
		sprintf_s(szWord,sizeof(szWord),"%s(%d)",npc.name.c_str(),npc.id);
		m_TreeCtrl.InsertItem(szWord,hParent/*,TVI_ROOT,hItem*/);

		SetMaxNpcInfo();
	}
}

void CNpcEditDlg::OnTvnSelchangedTree1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	HTREEITEM hItem = m_TreeCtrl.GetSelectedItem();
	CString cItemText = m_TreeCtrl.GetItemText(hItem);
	
	if(IsElapseNode(cItemText))
	{
	   ParseString(cItemText);
	   int nElapseId = atoi(cItemText.GetBuffer());       //ElapseId

	   NpcInfo::Npc *pNpc = theNpcInfo.GetNpcByStaticId(m_NpcID);
	   if(NULL != pNpc)
	   {
		   int nSize = pNpc->vctActionData.size();
		   for (int i = 0;i < nSize;++i)
		   {
			   if(pNpc->vctActionData[i].shId == nElapseId)
			   {
				   SetElpaseTime(pNpc->vctActionData[i]);
				   break;
			   }
		   }
	   }
	}
	else if(IsActionNode(cItemText)/*cItemText.Find("Action") >= 0*/)
	{
		CString   cParentItemText;
		int nElapseId = -1;

		HTREEITEM hParentItem = m_TreeCtrl.GetParentItem(hItem);            //Elapse
		cParentItemText  = m_TreeCtrl.GetItemText(hParentItem);
		nElapseId = atoi(ParseString(cParentItemText));              //Elapse Id
		
		NpcInfo::Npc *pNpc = theNpcInfo.GetNpcByStaticId(m_NpcID);
		if(NULL != pNpc)
		{
			int nSize = pNpc->vctActionData.size();
			for(int i = 0;i < nSize;++i)
			{
				if(pNpc->vctActionData[i].shId == nElapseId)
				{
					int nAmount = pNpc->vctActionData[i].vctActions.size();
					const char *pszText = ParseString(cItemText);

					for (int nAction = 0; nAction < nAmount;++nAction)
					{
						if(pNpc->vctActionData[i].vctActions[nAction].strAnimName.compare(pszText) == 0)
						{
							SetActionProtery(pNpc->vctActionData[i].vctActions[nAction]);
							break;
						}
					}
					break;
				}
			}
		}

 		::OutputDebugString(cParentItemText.GetBuffer());
 		::OutputDebugString("  Action\n");
	}
	else if(IsTalkNode(cItemText)/*cItemText.Find("Talk") >= 0*/)
	{
		CString cParentItemText;
		int nElapseId = -1;
		HTREEITEM hParentItem = m_TreeCtrl.GetParentItem(hItem);           //Elapse
		cParentItemText = m_TreeCtrl.GetItemText(hParentItem);
		nElapseId = atoi(ParseString(cParentItemText));             //Elapse Id

		NpcInfo::Npc *pNpc = theNpcInfo.GetNpcByStaticId(m_NpcID);
		if(NULL != pNpc)
		{
			int nSize = pNpc->vctActionData.size();
			for(int i = 0;i < nSize;++i)
			{
				if(pNpc->vctActionData[i].shId == nElapseId)
				{
					int nAmount = pNpc->vctActionData[i].vctTalks.size();
					int nID = atoi(ParseString(cItemText));
					for (int nTalk = 0; nTalk < nAmount;++nTalk)
					{
						if(pNpc->vctActionData[i].vctTalks[nTalk].shStringId == nID)
						{
							SetTalkProtery(pNpc->vctActionData[i].vctTalks[nTalk]);
							break;
						}
					}
					break;
				}
			}
		}

		::OutputDebugString(cParentItemText.GetBuffer());
		::OutputDebugString("  Talk\n");
	}
	else if(IsMapNode(cItemText))
	{

	}
    else
    {

    }
}

void CNpcEditDlg::InitTreeControlData(HTREEITEM hSubItem,Filter eumValue,int nMapId,const char *pszNpcName/* = NULL*/)
{
	HTREEITEM rootItem = NULL,elapseItem = NULL,subItem = NULL;
	NpcInfo::Npcs::iterator iter = theNpcInfo.npcs_.begin();
	NpcInfo::Npcs::iterator end  = theNpcInfo.npcs_.end();

	for ( ; iter != end; ++iter)
	{
		bool bInsert = false;
		switch(eumValue)
		{
		case FILTER_NONE:
			bInsert = true;
			break;
		case FILTER_MAPID:
			{
				if(iter->second.mapId == nMapId/*atoi(pszValue)*/)
					bInsert = true;
			}
			break;
		case FILTER_NAME:
			{
				assert(pszNpcName != NULL);
				if((iter->second.name.compare(pszNpcName) == 0)&&(iter->second.mapId == nMapId))
					bInsert = true;
			}
			break;
		}

		if(bInsert)
		{
		 //插入Npc
		 char stritem[64];
		 sprintf_s(stritem,sizeof(stritem),"%s(%d)",iter->second.name.c_str(),iter->second.id);
		 rootItem = m_TreeCtrl.InsertItem(stritem,hSubItem/*TVI_ROOT*/);

		 //插入NpcActionData
		 int nSize = iter->second.vctActionData.size();
		 for (int i = 0 ;i < nSize; i++)
		 {
			 //Insert Elapse Time
			 sprintf_s(stritem,sizeof(stritem),"%s(%d)","Elapse",iter->second.vctActionData[i].shId);
			 elapseItem = m_TreeCtrl.InsertItem(stritem,rootItem);

			 //Insert Action Data
			 int nAmount = iter->second.vctActionData[i].vctActions.size();
			 for (int nAction = 0; nAction < nAmount; ++nAction)
			 {
				 sprintf_s(stritem,sizeof(stritem),"%s(%s)","Action",iter->second.vctActionData[i].vctActions[nAction].strAnimName.c_str());
				 subItem = m_TreeCtrl.InsertItem(stritem,elapseItem,subItem);
			 }

			 //Insert Talk
			 nAmount = iter->second.vctActionData[i].vctTalks.size();
			 for (int npcTalk = 0;npcTalk < nAmount ; ++ npcTalk)
			 {
				sprintf_s(stritem,sizeof(stritem),"%s(%d)","Talk",iter->second.vctActionData[i].vctTalks[npcTalk].shStringId);
				subItem = m_TreeCtrl.InsertItem(stritem,elapseItem,subItem);
			 }	
		 }

		 rootItem   = NULL;
		 elapseItem = NULL;
		 subItem    = NULL;
		}
	}
	
	return;
}

bool CNpcEditDlg::GetNpcFightData(NpcInfo::Npc &npc)
{
	//视野
	CWnd* pWnd = GetDlgItem(IDC_fight_view);
	if(pWnd != NULL)
	{
		CString str;
		pWnd->GetWindowText(str);
		short view = _ttoi(str.operator LPCTSTR());
		if(view >= 0)
		{
			if(0 == npc.fightData.size())
			{
				npc.fightData.push_back(NpcInfo::FightInfo());
			}

			npc.fightData.begin()->view = view;
		}
		else
		{
			::MessageBox(NULL, _T("npc的视野不能小于0， 请重新填写！"), _T("Warning"), MB_OK);
			return false;
		}
	}

	return true;
}

bool CNpcEditDlg::SetNpcFightData(const NpcInfo::Npc &npc)
{
	//视野
	CWnd* pWnd = GetDlgItem(IDC_fight_view);
	if(pWnd != NULL)
	{
		if(npc.fightData.size() > 0)
		{
			CString str;
			str.Format(_T("%d"), npc.fightData.begin()->view);
			pWnd->SetWindowText(str);
		}
		else
		{
			pWnd->SetWindowText(_T(""));
		}
	}

	return true;
}

bool CNpcEditDlg::GetNpcProtery(NpcInfo::Npc &npc)
{
	const int SZT_SIZE = 64;
	CString text;
	npc.Clear();

	int nValue = 0;
	float fValue = 0.0f;
	GetDlgItem(IDC_ID)->GetWindowText(text);
	if (_sntscanf_s(text.GetBuffer(), text.GetLength(), "%d", &nValue/*&npc.id*/) != 1)
	{
		::MessageBox(NULL,"NpcID为空或者不是数字!","Warnning",MB_OK);
		return false;
	}
	npc.id = nValue;

	npc.dynamicId = 0;

	GetDlgItem(IDC_NAME)->GetWindowText(text);
	if(text.IsEmpty())
	{
		::MessageBox(NULL,"NpcName为空添加失败!","Warnning",MB_OK);
		return false;
	}
	npc.name = text;

    GetDlgItem(IDC_PINYIN)->GetWindowText(text);
    if(text.IsEmpty())
    {
		npc.pinyin.clear();
    }
	else
	{
		npc.pinyin = text;
	}
	GetDlgItem(IDC_SOUND)->GetWindowText(text);
	if(!text.IsEmpty())
	{
		npc.strSoundPath = text;
	}
	else
	{
		npc.strSoundPath.clear();
	}

    GetDlgItem(IDC_ISDYNAMICCOLLISION)->GetWindowText(text);
    if(text.IsEmpty())
    {
        ::MessageBox(NULL,"Npc IsDynamicCollision为空添加失败!","Warnning",MB_OK);
        return false;
    }
	else if(text[0]<'0' || text[0] > '1') {
		::MessageBox(NULL,"Npc IsDynamicCollision 必须填0或者1","Warnning",MB_OK);
		char text[32];
		CWnd *pWindow = NULL;
		pWindow = GetDlgItem(IDC_ISDYNAMICCOLLISION);
		if(pWindow)
		{
			sprintf_s(text,sizeof(text),"%d",npc.isDynamicCollision == true ? 1 : 0);
			pWindow->SetWindowText(text);
		}
	}
	if(text[0]=='0') npc.isDynamicCollision=false;
	else npc.isDynamicCollision=true;
	GetDlgItem(IDC_COMMAP)->GetWindowText(text);
	ParseString(text);
	//pBox->GetLBText(pBox->GetCurSel(),text);
	if(_sntscanf_s(text.GetBuffer(), text.GetLength(), "%d", &nValue/*npc.mapId*/) != 1)
	{
		::MessageBox(NULL,"MapId为空或者不是数字!","Warnning",MB_OK);
		return false;
	}
	npc.mapId = nValue;

	GetDlgItem(IDC_LEV)->GetWindowText(text);
	if(_sntscanf_s(text.GetBuffer(),text.GetLength(), "%d", &nValue/*npc.level*/) != 1)
	{
		::MessageBox(NULL,"Levl为空或不是数字!","Warnning",MB_OK);
		return false;
	}
	npc.level = nValue;

	npc.type = static_cast<CComboBox*>(GetDlgItem(IDC_COMMTYPE))->GetCurSel();
	npc.phyle = static_cast<CComboBox*>(GetDlgItem(IDC_COMBONPCType))->GetCurSel();
    // 加入
    //CString strType;
    //static_cast<CComboBox*>(GetDlgItem(IDC_COMMTYPE))->GetWindowText(strType);
    //npc.type = 

	GetDlgItem(IDC_MOVEPATH)->GetWindowText(text);
	if(_sntscanf_s(text.GetBuffer(), text.GetLength(), "%d", &nValue/*&npc.movePath*/) != 1)
	{
		::MessageBox(NULL,"MovePath为空或不是数字!","Warnning",MB_OK);
		return false;
	}
	npc.movePath = nValue;

	GetDlgItem(IDC_CCDIR)->GetWindowText(text);
	if(_sntscanf_s(text.GetBuffer(), text.GetLength(), "%d", &nValue/*&npc.canChangeDirection*/) != 1)
	{
		::MessageBox(NULL,"CanChangeDirection为空或不是数字!","Warnning",MB_OK);
		return false;
	}
	npc.canChangeDirection = static_cast<bool>(nValue);


	GetDlgItem(IDC_ScriptFile)->GetWindowText(text);
	if(text.IsEmpty())
	{
		npc.triggerScript.clear();
	}
	else
	{
		npc.triggerScript = text;
	}

    GetDlgItem(IDC_ACTIONSCRIPT)->GetWindowText(text);
    if (text.IsEmpty())
    {
		npc.actionScript.clear();
    }
	else
	{
		npc.actionScript = text;
	}
	GetDlgItem(IDC_BSHOW)->GetWindowText(text);
	if(_sntscanf_s(text.GetBuffer(), text.GetLength(), "%d", &nValue/*&npc.isMiniShow*/) != 1)
	{
		::MessageBox(NULL,"Show为空或不是数字!","Warnning",MB_OK);
		return false;
	}
	npc.isMiniShow = static_cast<bool>(nValue);

	GetDlgItem(IDC_BIGMAPSHOW)->GetWindowText(text);
	if(_sntscanf_s(text.GetBuffer(), text.GetLength(), "%d", &nValue/*&npc.isShow*/) != 1)
	{
		::MessageBox(NULL,"Show为空或不是数字!","Warnning",MB_OK);
		return false;
	}
	npc.isWorldShow = static_cast<bool>(nValue);

	GetDlgItem(IDC_BCOLLISION)->GetWindowText(text);
	if(_sntscanf_s(text.GetBuffer(), text.GetLength(), "%d", &nValue/*&npc.isCollision*/) != 1)
	{
		::MessageBox(NULL,"Collision为空或不是数字!","Warnning",MB_OK);
		return false;
	}
	npc.isCollision = static_cast<bool>(nValue);

	GetDlgItem(IDC_TITLE)->GetWindowText(text);
	//if(text.Find('<') == -1&&!text.IsEmpty())
	//{
	//	::MessageBox(NULL,"Title 格式不正确!","Warnning",MB_OK);
	//	return false;
	//}
	npc.title = text;

	GetDlgItem(IDC_NPCTISP)->GetWindowText(text);
	npc.tip = text;

	GetDlgItem(IDC_HEADPICTURE)->GetWindowText(text);
	npc.strHeadPicture = text;

	GetDlgItem(IDC_BODYSCALE)->GetWindowText(text);
	if(_sntscanf_s(text.GetBuffer(), text.GetLength(), "%f", &fValue/*&npc.bodyScale*/) != 1)
	{
		::MessageBox(NULL,"BodyScale为空或不是数字!","Wanning",MB_OK);
		return false;
	}
	npc.bodyScale = fValue;

    m_NpcMenuStringID.GetWindowText(text);
    if ( text.GetBuffer() == NULL )
    {
        ::MessageBox(NULL, _T("NpcMenu字串ID不能是空，如果没有，请填写0 ！"), _T("Warning"), MB_OK);
        return false;
    }
    npc.nTaskMenu = atoi(text.GetBuffer());

	return true;
}

bool CNpcEditDlg::SetNpcProtery(NpcInfo::Npc &npc)
{
	char text[32];
	CWnd *pWindow = NULL;
	pWindow = GetDlgItem(IDC_ID);
	if(pWindow)
	{
		sprintf_s(text,sizeof(text) ,"%d",npc.id);
		pWindow->SetWindowText(text);
	}

	pWindow = GetDlgItem(IDC_NAME);
	if(pWindow)
	{
		pWindow->SetWindowText(npc.name.c_str());
	}

    pWindow = GetDlgItem(IDC_PINYIN);
    if(pWindow)
    {
        pWindow->SetWindowText(npc.pinyin.c_str());
    }

	pWindow = GetDlgItem(IDC_SOUND);
	if(pWindow)
	{
		pWindow->SetWindowText(npc.strSoundPath.c_str());
	}

	//pWindow = GetDlgItem(IDC_MAPID);
	pWindow = GetDlgItem(IDC_COMMAP);
	if(pWindow)
	{
		sprintf_s(text,sizeof(text),"%d",npc.mapId);
		//pWindow->SetWindowText(text);
		CComboBox *pBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMMAP));
		int nCount = pBox->GetCount();
		for (int i = 0;i < nCount ;++i)
		{
			CString cItemText;
			pBox->GetLBText(i,cItemText);
			ParseString(cItemText);
			if(cItemText.Compare(text) == 0)
			{
				pBox->SetCurSel(i);
				break;
			}

		}
		//pBox->SetWindowText(text);

		//pBox->SetCurSel(1);
	}

	pWindow = GetDlgItem(IDC_LEV);
	if(pWindow)
	{
		sprintf_s(text,sizeof(text),"%d",npc.level);
		pWindow->SetWindowText(text);
	}

// 	pWindow = GetDlgItem(IDC_TYPE);
// 	if(pWindow)
// 	{
// 		sprintf_s(text,sizeof(text),"%d",npc.type);
// 		pWindow->SetWindowText(text);
// 	}

	static_cast<CComboBox*>(GetDlgItem(IDC_COMMTYPE))->SetCurSel(npc.type);

	static_cast<CComboBox*>(GetDlgItem(IDC_COMBONPCType))->SetCurSel(npc.phyle);

	pWindow = GetDlgItem(IDC_MOVEPATH);
	if(pWindow)
	{
		sprintf_s(text,sizeof(text),"%d",npc.movePath);
		pWindow->SetWindowText(text);
	}

// 	pWindow = GetDlgItem(IDC_DIRECT);
// 	if(pWindow)
// 	{
// 		sprintf_s(text,sizeof(text),"%d",npc.direction);
// 		pWindow->SetWindowText(text);
// 	}

	pWindow = GetDlgItem(IDC_CCDIR);
	if(pWindow)
	{
		sprintf_s(text,sizeof(text),"%d",npc.canChangeDirection);
		pWindow->SetWindowText(text);
	}

	pWindow = GetDlgItem(IDC_ScriptFile);
	if(pWindow)
		pWindow->SetWindowText(npc.triggerScript.c_str());

	pWindow = GetDlgItem(IDC_BSHOW);
	if(pWindow)
	{
		sprintf_s(text,sizeof(text),"%d",npc.isMiniShow);
		pWindow->SetWindowText(text);
	}

	pWindow = GetDlgItem(IDC_BIGMAPSHOW);
	if(pWindow)
	{
		sprintf_s(text,sizeof(text),"%d",npc.isWorldShow);
		pWindow->SetWindowText(text);
	}

	pWindow = GetDlgItem(IDC_BCOLLISION);
	if(pWindow)
	{
		sprintf_s(text,sizeof(text),"%d",npc.isCollision);
		pWindow->SetWindowText(text);
	}

	pWindow = GetDlgItem(IDC_TITLE);
	if(pWindow)
	{
		pWindow->SetWindowText(npc.title.c_str());
	}

	pWindow = GetDlgItem(IDC_NPCTISP);
	if(pWindow)
	{
		pWindow->SetWindowText(npc.tip.c_str());
	}

	pWindow = GetDlgItem(IDC_HEADPICTURE);
	if(pWindow)
		pWindow->SetWindowText(npc.strHeadPicture.c_str());

	pWindow = GetDlgItem(IDC_BODYSCALE);
	if(pWindow)
	{
		sprintf_s(text,sizeof(text),"%lf",npc.bodyScale);
		pWindow->SetWindowText(text);
	}
	pWindow = GetDlgItem(IDC_ISDYNAMICCOLLISION);
	if(pWindow)
	{
		sprintf_s(text,sizeof(text),"%d",npc.isDynamicCollision == true ? 1 : 0);
		pWindow->SetWindowText(text);
	}

    // Add For NpcMenu Begin [10/28/2010 pengbo.yang]
    sprintf_s(text, sizeof(text), "%d", npc.nTaskMenu);
    m_NpcMenuStringID.SetWindowText(text); // 设置MenuId

     // 设置字串前先清空ListBox中原来的内容
    m_NpcMenuList.ResetContent();

    CNpcString::npcTalk* pNpctalk = theNpcStringForMenu.GetDataByIDForMenu(atoi(text));
    if (pNpctalk == NULL)
    { return false;}
    CString strNpcMenuContent = static_cast<CString>(pNpctalk->m_strTalk.c_str());
    CString strToken;
    int nItem = 0;
    const int nSubItem = 0;
    int nStartPos = 0;
    int nCount = 0;
    strToken = strNpcMenuContent.Tokenize(" ", nStartPos);

    //CString strInsertNew = "请在此处右键单击填入新内容...";
    //m_NpcMenuList.InsertString(0, strInsertNew); // 每次进来时加入一行可编辑

    while( strToken.GetLength() > 0 )
    {
        m_NpcMenuList.InsertString(nCount++, strToken.GetBuffer());
        if (bIsSetScroll)
        {//此处为计算每一行的长度，比较，得到最长的，设置水平滚动条的长度
            CSize sz;
            int dx = 0;
            CDC* pDC = m_NpcMenuList.GetDC();
            for (int i=0; i<m_NpcMenuList.GetCount(); ++i)
            {
                m_NpcMenuList.GetText(i, strToken);
                sz = pDC->GetTextExtent(strToken);
                if (sz.cx > dx)
                {
                    dx = sz.cx;
                }
            }
            m_NpcMenuList.ReleaseDC(pDC);
            m_NpcMenuList.SetHorizontalExtent(dx); 
            bIsSetScroll = false;
        }
        strToken = strNpcMenuContent.Tokenize(" ", nStartPos);
    }
    // Add For NpcMenu End [10/28/2010 pengbo.yang]

	return true;
}

// void CNpcEditDlg::OnBnClickedLoadxml()
// {
// 	//初始化数据
// 	theNpcInfo.npcs_.clear();
// 	m_TreeCtrl.DeleteAllItems();
// 
// 	CFileDialog dlgFile(true);
// 	CString fileName;
// 	dlgFile.GetOFN().lpstrFile = fileName.GetBuffer(1024);
// 	dlgFile.GetOFN().nMaxFile  = 1024;
// 
// 	INT_PTR nResult = dlgFile.DoModal();
// 	if(nResult == IDCANCEL)
// 		return;
// 
// 	Common::_tstring strFileName = fileName.GetBuffer(0);
// 	int nRes = theNpcInfo.LoadConfig(fileName.GetBuffer(0));
// 
// 	switch(nRes)
// 	{
// 	case File_Success:
// 		InitTreeControlData();
// 		break;
// 	case File_Error:
// 		::MessageBox(NULL,TEXT("加载文件错误!"),TEXT("Error"),MB_OK);
// 		break;
// 	case Param_Error:
// 		::MessageBox(NULL,TEXT("文件参数错误!"),TEXT("Error"),MB_OK);
// 		break;
// 	case Attribute_Error:
// 		::MessageBox(NULL,TEXT("字段属性错误"),TEXT("Error"),MB_OK);
// 		break;
// 	}
// 
// 	fileName.ReleaseBuffer();
// }

void CNpcEditDlg::OnBnClickedNpcupdate()
{
	HTREEITEM hItem = m_TreeCtrl.GetSelectedItem();
	CString   cItemText = m_TreeCtrl.GetItemText(hItem);

	if(!IsNpcNode(cItemText))
	{
		::MessageBox(NULL,"请选择Npc!","Warnning",MB_OK);
		return;
	}
	int nNpcId = atoi(ParseString(cItemText));

	NpcInfo::Npc *pNpc = theNpcInfo.GetNpcByStaticId(nNpcId);

	if(NULL != pNpc)
	{
		NpcInfo::Npc npc;
		if(GetNpcProtery(npc))
		{
			HTREEITEM hParent = m_TreeCtrl.GetParentItem(hItem); //获得该父节点
			CString   cParentText = m_TreeCtrl.GetItemText(hParent);

			int  nLeft = static_cast<int>(cParentText.Find('[')) + 1;
			int  nRight = static_cast<int>(cParentText.Find(']'));
			cParentText = cParentText.Right(cParentText.GetLength() - nLeft);
			cParentText = cParentText.Left(nRight - nLeft);

			int mapID = atoi(cParentText.GetBuffer());
			if(mapID != npc.mapId)
			{
				::MessageBox(NULL,"NpcMapID不属于这个地图分组!","Warnning",MB_OK);
				return;
			}

			pNpc->id = npc.id;						
			pNpc->dynamicId = 0;				
			pNpc->name = npc.name;	
			pNpc->mapId = npc.mapId;					
			pNpc->level =npc.level;					
			pNpc->type = npc.type;					
			pNpc->modelId = npc.modelId;				
			pNpc->x = npc.x;					
			pNpc->y = npc.y;					
			pNpc->z = npc.z;                    
			pNpc->movePath = npc.movePath;				
			pNpc->direction = npc.direction;				
			pNpc->canChangeDirection = npc.canChangeDirection;	
			pNpc->triggerScript = npc.triggerScript;
            pNpc->actionScript = npc.actionScript;
			pNpc->isMiniShow = npc.isMiniShow;
			pNpc->isWorldShow = npc.isWorldShow;
			pNpc->isCollision = npc.isCollision;			
			pNpc->title = npc.title;
			pNpc->tip = npc.tip;
			pNpc->strHeadPicture = npc.strHeadPicture;	
			pNpc->bodyScale = npc.bodyScale;

			pNpc->isDynamicCollision=npc.isDynamicCollision;
			char szWord[32];
			sprintf_s(szWord,sizeof(szWord),"%s(%d)",npc.name.c_str(),npc.id);
			m_TreeCtrl.SetItemText(m_TreeCtrl.GetSelectedItem(),szWord);

			bool bResult = false;
#ifdef _DEBUG
			bResult = SaveConfig("Npc.config");
#else
			bResult = SaveConfig(".\\Data\\Config\\Npc.config");
#endif
			if(bResult)
			{
				char szTipInfo[64];
				sprintf_s(szTipInfo,sizeof(szTipInfo),"%s(%d)保存成功!",npc.name.c_str(),npc.id);
				SetTipInfo(szTipInfo);
				SetMaxNpcInfo();
			}
		}
	}
}

// void CNpcEditDlg::OnBnClickedNpcsave()
// {
// 	CFileDialog dlgFile(false);
// 	CString fileName;
// 	dlgFile.GetOFN().lpstrFile = fileName.GetBuffer(1024);
// 	dlgFile.GetOFN().nMaxFile  = 1024;
// 	//dlgFile.GetOFN().lpstrFilter = "*.xml;*.config";
// 
// 	INT_PTR nResult = dlgFile.DoModal();
// 	if(nResult == IDCANCEL)
// 		return;
// 
// 	SaveConfig(fileName.GetBuffer());
// 	fileName.ReleaseBuffer();
// }

const char*  CNpcEditDlg::ParseString(CString& strData)
{
	int  nLeft = static_cast<int>(strData.Find('(')) + 1;
	int  nRight = static_cast<int>(strData.Find(')'));
	strData = strData.Right(strData.GetLength() - nLeft);
	strData = strData.Left(nRight - nLeft);
 
	return strData.GetBuffer();
}

bool CNpcEditDlg::GetElpaseTime(NpcInfo::NpcActionData &Elpase)
{
	CString cWord; 
	int nValue = 0;
	GetDlgItem(IDC_ElAPID)->GetWindowText(cWord);
	//if(cWord.GetLength() <= 0)
	if(_sntscanf_s(cWord.GetBuffer(),cWord.GetLength(),"%d",&nValue) != 1)
	{
		::MessageBox(NULL,"ElapseId为空或不是数字!","Warnning",MB_OK);
		return false;
	}
	Elpase.shId = static_cast<short>(nValue/*atoi(cWord.GetBuffer())*/);

	GetDlgItem(IDC_ELAPTIME)->GetWindowText(cWord);
	//if(cWord.GetLength() <= 0)
	if(_sntscanf_s(cWord.GetBuffer(),cWord.GetLength(),"%d",&nValue) != 1)
	{
		::MessageBox(NULL,"ElapseTime为空或不是数字!","Warnning",MB_OK);
		return false;
	}
	Elpase.shElapseTime = static_cast<short>(nValue/*atoi(cWord.GetBuffer())*/);

	GetDlgItem(IDC_ELAPNEXT)->GetWindowText(cWord);
	//if(cWord.GetLength() <= 0)
	if(_sntscanf_s(cWord.GetBuffer(),cWord.GetLength(),"%d",&nValue) != 1)
	{
		::MessageBox(NULL,"ElapseNextId为空或不是数字!","Warnning",MB_OK);
		return false;
	}
	Elpase.shNextId = static_cast<short>(nValue/*atoi(cWord.GetBuffer())*/);
	return true;
}

bool CNpcEditDlg::SetElpaseTime(NpcInfo::NpcActionData &Elpase)
{
	char szText[64];

	sprintf_s(szText,"%d",Elpase.shId);
	GetDlgItem(IDC_ElAPID)->SetWindowText(szText);

	sprintf_s(szText,"%d",Elpase.shElapseTime);
	GetDlgItem(IDC_ELAPTIME)->SetWindowText(szText);

	sprintf_s(szText,"%d",Elpase.shNextId);
	GetDlgItem(IDC_ELAPNEXT)->SetWindowText(szText);

	return true;
}

bool CNpcEditDlg::GetActionProtery(NpcInfo::ActionData &actionData)
{
	CString cWord;
	GetDlgItem(IDC_ACTIONNAME)->GetWindowText(cWord);
	if(cWord.IsEmpty())
	{
		::MessageBox(NULL,"Action Name can't null!","Warnning",MB_OK);
		return false;
	}
	actionData.strAnimName = cWord.GetBuffer();

	GetDlgItem(IDC_ACTIONPRO)->GetWindowText(cWord);
// 	if(cWord.IsEmpty())
// 	{
// 		::MessageBox(NULL,"Action Probability can't null!","Warnning",MB_OK);
// 		return false;
// 	}
	int nValue = 0;
	if(_sntscanf_s(cWord.GetBuffer(),cWord.GetLength(),"%d",&nValue) != 1)
	{
		::MessageBox(NULL,"Action Probability为空或不是数字!","Warnning",MB_OK);
		return false;
	}
	if(nValue > 100)
	{
		::MessageBox(NULL,"Action Probability不可能超过100!","Warnning",MB_OK);
		return false;
	}
	actionData.shProbability = static_cast<short>(nValue);
	return true;
}

bool CNpcEditDlg::SetActionProtery(NpcInfo::ActionData &actionData)
{
	char szText[64];

	GetDlgItem(IDC_ACTIONNAME)->SetWindowText(actionData.strAnimName.c_str());

	sprintf_s(szText,"%d",actionData.shProbability);
	GetDlgItem(IDC_ACTIONPRO)->SetWindowText(szText);
	return true;
}

bool CNpcEditDlg::GetTalkProtery(NpcInfo::TalkData &talk)
{
	CString cWord;
	GetDlgItem(IDC_COMNPCSTR/*IDC_STRINGID*/)->GetWindowText(cWord);
	if(cWord.IsEmpty())
	{
		::MessageBox(NULL, "Talk stringId can't null!","Warnning",MB_OK);
		return false;
	}
	talk.shStringId = atoi(cWord.GetBuffer());

	int nValue = 0;
	GetDlgItem(IDC_TALKPRO)->GetWindowText(cWord);
	if(_sntscanf_s(cWord.GetBuffer(),cWord.GetLength(),"%d",&nValue) != 1)
	{
		::MessageBox(NULL,"Talk Probability为空或不是数字!","Warnning",MB_OK);
		return false;
	}
	if(nValue > 100)
	{
		::MessageBox(NULL,"Talk Probability不可能超过100!","Warnning",MB_OK);
		return false;
	}
	talk.shProbability = static_cast<short>(nValue);

	return true;
}

bool CNpcEditDlg::SetTalkProtery(NpcInfo::TalkData &talk)
{
	char szText[64];

	sprintf_s(szText,sizeof(szText),"%d",talk.shStringId);
	//GetDlgItem(IDC_STRINGID)->SetWindowText(szText);
	CComboBox *pBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMNPCSTR));
	int nCount = pBox->GetCount();
	for (int i = 0;i < nCount ;++i)
	{
		CString cItemText;
		pBox->GetLBText(i,cItemText);
		if(cItemText.Compare(szText) == 0)
		{
			pBox->SetCurSel(i);
			break;
		}
	}

	sprintf_s(szText,sizeof(szText),"%d",talk.shProbability);
	GetDlgItem(IDC_TALKPRO)->SetWindowText(szText);
	return true;
}


void CNpcEditDlg::OnBnClickedTalkupdate()
{
	HTREEITEM hItem = m_TreeCtrl.GetSelectedItem();
	CString   cItemText = m_TreeCtrl.GetItemText(hItem);

	if(!IsTalkNode(cItemText))
	{
		::MessageBox(NULL,"请选择Talk节点!","Warnning",MB_OK);
 		return;
	}

	CString cParentItemText;
	int nElapseId = -1,nStringID = -1;
	HTREEITEM hParentItem = m_TreeCtrl.GetParentItem(hItem);           //Elapse
	cParentItemText = m_TreeCtrl.GetItemText(hParentItem);
	nElapseId = atoi(ParseString(cParentItemText));             //Elapse Id

	nStringID = atoi(ParseString(cItemText));


	NpcInfo::TalkData *pTalkData = GetTalkData(m_NpcID,nElapseId,nStringID);

	if(pTalkData != NULL)
	{
		NpcInfo::TalkData npcTalkData;
		if(GetTalkProtery(npcTalkData))
		{
			char szError[128];
			//数据有效性检测
			if(!IsValidTalkData(m_NpcID,nElapseId,*pTalkData,szError,true,&npcTalkData))
			{
				::MessageBox(NULL,szError,"Warnning",MB_OK);
				return;
			}

			pTalkData->shStringId = npcTalkData.shStringId;
			pTalkData->shProbability = npcTalkData.shProbability;

			char szText[32];
			sprintf_s(szText,sizeof(szText),"%s(%d)","Talk",npcTalkData.shStringId);
			m_TreeCtrl.SetItemText(m_TreeCtrl.GetSelectedItem(),szText);

			bool bResult = true;
//			bool bResult = false;
// #ifdef _DEBUG
// 			bResult = SaveConfig("Npc.config");
// #else
// 			bResult = SaveConfig(".\\Data\\Config\\Npc.config");
// #endif
			if(bResult)
			{
				char szWord[64];
				sprintf_s(szWord,sizeof(szWord),"Talk %d保存成功！",npcTalkData.shStringId);
				SetTipInfo(szWord);
			}
		}
	}
}

void CNpcEditDlg::OnBnClickedTalkinsert()
{
	HTREEITEM hItem = m_TreeCtrl.GetSelectedItem();
	CString   cItemText = m_TreeCtrl.GetItemText(hItem);

	if(!IsElapseNode(cItemText))
	{
  		::MessageBox(NULL,"请选择Elapse节点!","Warnning",MB_OK);
		return;
	}

	CString cParentItemText;
	int nElapseId = -1,nStringID = -1;
	
    nElapseId = atoi(ParseString(cItemText));                          //nElapseId

	NpcInfo::NpcActionData *pNpcActionData = GetNpcActionData(m_NpcID,nElapseId);
	if(NULL != pNpcActionData)
	{
		NpcInfo::TalkData npcTalkData;
		if(GetTalkProtery(npcTalkData))
		{
			char szError[128];
			if(!IsValidTalkData(m_NpcID,nElapseId,npcTalkData,szError))  //有效性数据检测
			{
				::MessageBox(NULL,szError,"Warnning",MB_OK);
				return;
			}

			pNpcActionData->vctTalks.push_back(npcTalkData);
			char szWord[32];
			sprintf_s(szWord,sizeof(szWord),"Talk(%d)",npcTalkData.shStringId);
			m_TreeCtrl.InsertItem(szWord,hItem);
		}
	}
}



void CNpcEditDlg::OnBnClickedActionupdate()
{
	HTREEITEM hItem = m_TreeCtrl.GetSelectedItem();
	CString cItemText = m_TreeCtrl.GetItemText(hItem); //Action

	if(!IsActionNode(cItemText))
	{
 		::MessageBox(NULL,"请选择Action节点!","Warnning",MB_OK);
		return;
	}

	int nElapseId = -1,nStringID = -1;
    CString cActionStr = ParseString(cItemText);

	hItem = m_TreeCtrl.GetParentItem(hItem);  //Elapse
	cItemText = m_TreeCtrl.GetItemText(hItem);
	nElapseId = atoi(ParseString(cItemText));


	NpcInfo::ActionData *pActionData = GetActionData(m_NpcID,nElapseId,cActionStr);
	if(NULL != pActionData)
	{
		NpcInfo::ActionData npcActionData;
		if(GetActionProtery(npcActionData))
		{
			char szError[128];
			//数据有效性检测
			if(!IsValidActionData(m_NpcID,nElapseId,*pActionData,szError,true,&npcActionData))
			{
				::MessageBox(NULL,szError,"Warnning",MB_OK);
				return;
			}


			pActionData->strAnimName = npcActionData.strAnimName;
			pActionData->shProbability = npcActionData.shProbability;

			char szWord[32];
			sprintf_s(szWord,sizeof(szWord),"%s(%s)","Action",npcActionData.strAnimName.c_str());
			m_TreeCtrl.SetItemText(m_TreeCtrl.GetSelectedItem(),szWord);

			bool bResult = true;
//			bool bResult = false;
// #ifdef _DEBUG
// 			bResult = SaveConfig("Npc.config");
// #else
// 			bResult = SaveConfig(".\\Data\\Config\\Npc.config");
// #endif
			if(bResult)
			{
			   //char szWord[64];
			   sprintf_s(szWord,sizeof(szWord),"Action %s 保存成功!",npcActionData.strAnimName.c_str());

			   SetTipInfo(szWord);
			}
		}
	}
}

void CNpcEditDlg::OnBnClickedActioninsert()
{
	HTREEITEM hItem = m_TreeCtrl.GetSelectedItem();
	CString   cItemText = m_TreeCtrl.GetItemText(hItem);

	if(!IsElapseNode(cItemText))
	{
		::MessageBox(NULL,"请选择Elapse节点!","Warnning",MB_OK);
		return;
	}

	CString cParentItemText;
	int nElapseId = -1,nStringID = -1;

	nElapseId = atoi(ParseString(cItemText));                          //nElapseId

	NpcInfo::NpcActionData *pNpcActionData = GetNpcActionData(m_NpcID,nElapseId);
	if(NULL != pNpcActionData)
	{
		NpcInfo::ActionData npcActionData;
		if(GetActionProtery(npcActionData))
		{
			char szError[128];
			if(!IsValidActionData(m_NpcID,nElapseId,npcActionData,szError))  //有效性数据检测
			{
				::MessageBox(NULL,szError,"Warnning",MB_OK);
				return;
			}

			pNpcActionData->vctActions.push_back(npcActionData);
			char szWord[32];
			sprintf_s(szWord,"%s(%s)","Action",npcActionData.strAnimName.c_str());
			m_TreeCtrl.InsertItem(szWord,hItem);
		}
	}
}

void CNpcEditDlg::OnBnClickedElapupdate()
{
	if(m_NpcID == 0)
		return;

	HTREEITEM hItem = m_TreeCtrl.GetSelectedItem();
	CString  cItemText = m_TreeCtrl.GetItemText(hItem);

	if(!IsElapseNode(cItemText))
	{
 		::MessageBox(NULL,"请选择Elapse节点!","Warnning",MB_OK);
		return;
	}

	int nElapseID = -1;
	nElapseID = atoi(ParseString(cItemText));

	NpcInfo::NpcActionData *pNpcActionData = GetNpcActionData(m_NpcID,nElapseID);
	if(NULL != pNpcActionData)
	{
		NpcInfo::NpcActionData npcElapseTime;
		if(GetElpaseTime(npcElapseTime))
		{
			pNpcActionData->shId = npcElapseTime.shId;
			pNpcActionData->shElapseTime = npcElapseTime.shElapseTime;
			pNpcActionData->shNextId = npcElapseTime.shNextId;

			char szText[32];
			sprintf_s(szText,sizeof(szText),"%s(%d)","Elapse",npcElapseTime.shId);

			m_TreeCtrl.SetItemText(m_TreeCtrl.GetSelectedItem(),szText);

// 			bool bResult = false;
// #ifdef _DEBUG
// 			bResult = SaveConfig("Npc.config");
// #else
// 			bResult = SaveConfig(".\\Data\\Config\\Npc.config");
// #endif
// 			if(bResult)
// 			{
// 				sprintf_s(szText,sizeof(szText),"Elapse %d 保存成功!",npcElapseTime.shId);
// 				SetTipInfo(szText);
// 			}
		}
	}
}

void CNpcEditDlg::OnBnClickedElapinsert()
{	
	NpcInfo::Npc* pNpc = theNpcInfo.GetNpcByStaticId(m_NpcID);

	if(NULL != pNpc)
	{
		NpcInfo::NpcActionData npcElapseTime;
		if(GetElpaseTime(npcElapseTime))
		{
			npcElapseTime.vctActions.clear();
			npcElapseTime.vctTalks.clear();
			pNpc->vctActionData.push_back(npcElapseTime);

			char szWord[32];
			sprintf_s(szWord,sizeof(szWord),"%s(%d)","Elapse",npcElapseTime.shId);
			m_TreeCtrl.InsertItem(szWord,TVI_ROOT);
		}	
	}
}

NpcInfo::NpcActionData* CNpcEditDlg::GetNpcActionData(int nNpcID,int nElapseID)
{
	NpcInfo::Npc *pNpc = theNpcInfo.GetNpcByStaticId(nNpcID);
	if(NULL != pNpc)
	{
		int nSize = pNpc->vctActionData.size();
		for (int i = 0;i < nSize;++i)
		{
			if(pNpc->vctActionData[i].shId == nElapseID)
			{
				return &pNpc->vctActionData[i];
			}
		}
	}
	return NULL;
}

NpcInfo::ActionData*  CNpcEditDlg::GetActionData(int nNpcID,int nElapseID,CString &cAnimStr)
{
	NpcInfo::Npc *pNpc = theNpcInfo.GetNpcByStaticId(nNpcID);
	if(NULL != pNpc)
	{
		int nSize = pNpc->vctActionData.size();
		for(int i = 0;i < nSize;++i)
		{
			if(pNpc->vctActionData[i].shId == nElapseID)
			{
				int nAmount = pNpc->vctActionData[i].vctActions.size();
				for (int nAction = 0; nAction < nAmount;++nAction)
				{
					if(pNpc->vctActionData[i].vctActions[nAction].strAnimName.compare(cAnimStr.GetBuffer()) == 0)
					{
						return &pNpc->vctActionData[i].vctActions[nAction];
					
					}
				}
			}
		}
	}
    return NULL;
}

NpcInfo::TalkData* CNpcEditDlg::GetTalkData(int nNpcID,int nElapseID,int nStringID)
{
	NpcInfo::Npc *pNpc = theNpcInfo.GetNpcByStaticId(nNpcID);
	if(NULL != pNpc)
	{
		int nSize = pNpc->vctActionData.size();
		for(int i = 0;i < nSize;++i)
		{
			if(pNpc->vctActionData[i].shId == nElapseID)
			{
				int nAmount = pNpc->vctActionData[i].vctTalks.size();
				for (int nTalk = 0; nTalk < nAmount;++nTalk)
				{
					if(pNpc->vctActionData[i].vctTalks[nTalk].shStringId == nStringID)					
						return &pNpc->vctActionData[i].vctTalks[nTalk];
				}
			}
		}
	}
	return NULL;
}

bool CNpcEditDlg::IsValidActionData(int nNpcID,int nElapseID,NpcInfo::ActionData &Data,char *pszError,bool bUpdate /*= false*/,NpcInfo::ActionData *DataNew /*= NULL*/)
{
	return true;
	//NpcActionData
	NpcInfo::NpcActionData* pNpcActionData = GetNpcActionData(nNpcID,nElapseID);
	if(NULL != pNpcActionData)
	{
		int nSize = pNpcActionData->vctActions.size();
		int nTotal = 0;
		for (int nAction = 0;nAction < nSize; ++nAction)
		{
            if(bUpdate)
			{
				//用于Update时检测
				if(pNpcActionData->vctActions[nAction].strAnimName.compare(Data.strAnimName.c_str()) != 0) 
					continue;                                 //替换的数据不需要进行比较
				else
				{
					nTotal += pNpcActionData->vctActions[nAction].shProbability;
					if(pNpcActionData->vctActions[nAction].strAnimName.compare(DataNew->strAnimName.c_str()) != 0)
					{
						strcpy(pszError,"Action Name有重复!");
						return false;
					}
				}
			}
			else
			{
			    //概率检测
			    nTotal += pNpcActionData->vctActions[nAction].shProbability;
                //重复性检测
			    if(pNpcActionData->vctActions[nAction].strAnimName.compare(Data.strAnimName.c_str()) != 0)
			    {
				   strcpy(pszError,"Action name有重复!");
				   return false;
			    }
			}
		}
		if(bUpdate)
			nTotal += DataNew->shProbability;
		else
		    nTotal += Data.shProbability;
		if(nTotal != 100)
		{
			strcpy(pszError,"Action概率不为100");
			return false;
		}
	}
   return true;
}

bool CNpcEditDlg::IsValidTalkData(int nNpcID,int nElapseID,NpcInfo::TalkData &Data,char *pszError,bool bUpdate/* = false*/,NpcInfo::TalkData *DataNew/* = NULL*/)        //TalkData数据是否正确
{
	return true; //去除检测
	//NpcActionData
	NpcInfo::NpcActionData* pNpcActionData = GetNpcActionData(nNpcID,nElapseID);
	if(NULL != pNpcActionData)
	{
		int nSize = pNpcActionData->vctTalks.size();
		int nTotal = 0;

		for (int nTalk = 0; nTalk < nSize; ++nTalk)
		{
			if(bUpdate)
			{
				//用于Update时检测
				if(Data.shStringId == pNpcActionData->vctTalks[nTalk].shStringId)
					continue;                                 //替换的数据不需要进行比较
				else
				{
					nTotal += pNpcActionData->vctTalks[nTalk].shProbability;
					if(pNpcActionData->vctTalks[nTalk].shStringId == DataNew->shStringId)
					{
						strcpy(pszError,"Talk StringID有重复!");
						return false;
					}
				}
			}
			else
			{
			   //概率检测
			   nTotal += pNpcActionData->vctTalks[nTalk].shProbability;
			   //重复性检测
			   if(pNpcActionData->vctTalks[nTalk].shStringId == Data.shStringId)
			   {
				  strcpy(pszError,"Talk StringID有重复!");
				   return false;
			    }
			}
		}
		if(bUpdate)
			nTotal += DataNew->shProbability;
		else
		   nTotal += Data.shProbability;

		if(nTotal != 100)
		{
			strcpy(pszError,"Talk概率不为100");
			return false;
		}
	}
	return true;
}


bool CNpcEditDlg::IsValidElpaseData(int nNpcID,char *pszError)
{
	NpcInfo::Npc *pNpc = theNpcInfo.GetNpcByStaticId(nNpcID);
	if(NULL != pNpc)
	{
		int nSize = pNpc->vctActionData.size();
		for (int i = 0;i < nSize;++i)
		{
 			if(pNpc->vctActionData[i].shId != i)
			{
				char szWord[128];
				sprintf_s(szWord,sizeof(szWord),"Elpase第%d节点shId错误",i);
				strcpy(pszError,szWord);
				return false;
			}

			if(((i + 1 < nSize) &&(pNpc->vctActionData[i].shNextId != i + 1))
				||((i + 1 >= nSize)&&(pNpc->vctActionData[i].shNextId != 0) ))
			{
				char szWord[128];
				sprintf_s(szWord,sizeof(szWord),"Elpase第%d节点shNextId错误",i);
				strcpy(pszError,szWord);
				return false;
			}

// 			if((i + 1 >= nSize)&&(pNpc->vctActionData[i].shNextId != 0) )
// 				return false;
		}
	}
	return true;
}


bool CNpcEditDlg::IsNpcNode(CString &cText)
{
	if(cText.GetLength() <= 0 || cText.Find("Elapse") >= 0 || cText.Find("Action") >= 0 ||cText.Find("Talk") >= 0 || cText.Find("[") >= 0)
		return false;
    return  true;
}

bool CNpcEditDlg::IsElapseNode(CString &cText)
{
    return (cText.Find("Elapse") >= 0);
}

bool CNpcEditDlg::IsActionNode(CString &cText)
{
	return (cText.Find("Action") >= 0);
}

bool CNpcEditDlg::IsTalkNode(CString &cText)
{
	return (cText.Find("Talk") >= 0);
}

bool CNpcEditDlg::IsMapNode(CString &cText)
{
	return (cText.Find("[") >= 0);
}

bool CNpcEditDlg::IsActionsNode(CString &cText)
{
	return (cText.Find("Action") >= 0);
}

bool CNpcEditDlg::IsRequireNode(CString &cText)
{
	return (cText.Find("Require") >= 0); 
}
bool CNpcEditDlg::IsEventNode(CString &cText)
{
	return (cText.Find("Event") >= 0);
}
bool CNpcEditDlg::IsEventTalkNode(CString &cText)
{
	return (cText.Find("Event(1") >= 0);
}
bool CNpcEditDlg::IsEventAnimNode(CString &cText)
{
	return (cText.Find("Event(2") >= 0);
}
bool CNpcEditDlg::IsEventFaceToNode(CString &cText)
{
	return (cText.Find("Event(3") >= 0);
}


void CNpcEditDlg::OnSavexml()
{
	CFileDialog dlgFile(false);
	CString fileName;
	dlgFile.GetOFN().lpstrFile = fileName.GetBuffer(1024);
	dlgFile.GetOFN().nMaxFile  = 1024;
	dlgFile.GetOFN().lpstrFilter = "Config(*.config)\0*.config\0All File(*.*)\0*.*\0\0";

	INT_PTR nResult = dlgFile.DoModal();
	if(nResult == IDCANCEL)
		return;

	SaveConfig(fileName.GetBuffer());
	fileName.ReleaseBuffer();
}

void CNpcEditDlg::OnBnClickedAddpp()
{	
	NpcInfo::Npc* pNpc = theNpcInfo.GetNpcByStaticId(m_NpcID);  //获得Npc

	if(NULL != pNpc)
	{
		NpcInfo::NpcActionData npcElapseTime;
		if(GetElpaseTime(npcElapseTime))
		{
			npcElapseTime.vctActions.clear();
			npcElapseTime.vctTalks.clear();

			NpcInfo::ActionData npcActionData;  //Action
			NpcInfo::TalkData npcTalkData;      //Talk
            bool bResult = true;

            bResult &= GetActionProtery(npcActionData);  //GetActionData
			bResult &= GetTalkProtery(npcTalkData);      //Get

			if(bResult)
			{
				npcElapseTime.vctActions.push_back(npcActionData);
				npcElapseTime.vctTalks.push_back(npcTalkData);
				pNpc->vctActionData.push_back(npcElapseTime);

				HTREEITEM hItem;

				//Insert Item
				char szWord[32];
				sprintf_s(szWord,sizeof(szWord),"%s(%d)","Elapse",npcElapseTime.shId);
				hItem = m_TreeCtrl.InsertItem(szWord,TVI_ROOT);  //Elapse(ID)
			    
				sprintf_s(szWord,"%s(%s)","Action",npcActionData.strAnimName.c_str());
				m_TreeCtrl.InsertItem(szWord,hItem);

				sprintf_s(szWord,sizeof(szWord),"Talk(%d)",npcTalkData.shStringId);
				m_TreeCtrl.InsertItem(szWord,hItem);
// 				bool bResult = false;
// #ifdef _DEBUG
// 				bResult = SaveConfig("Npc.config");
// #else
// 				bResult = SaveConfig(".\\Data\\Config\\Npc.config");
// #endif
// 				if(bResult)
// 				   SetTipInfo("气泡 保存成功!");
			}
		}	
	}	
}

void CNpcEditDlg::OnBnClickedDelpp()
{
	HTREEITEM hItem = m_TreeCtrl.GetSelectedItem();
	CString  cItemText = m_TreeCtrl.GetItemText(hItem);

	if(!IsElapseNode(cItemText))
	{
		::MessageBox(NULL,"请选择Elapse节点!","Warnning",MB_OK);
		return;
	}

	int nElapseID = -1;
	nElapseID = atoi(ParseString(cItemText));

	NpcInfo::Npc* pNpc = theNpcInfo.GetNpcByStaticId(m_NpcID);

	if(NULL != pNpc)
	{
	    std::vector<NpcInfo::NpcActionData>::iterator iter = pNpc->vctActionData.begin();
		std::vector<NpcInfo::NpcActionData>::iterator end  = pNpc->vctActionData.end();

		for (;iter != end;++iter)
		{
			if(iter->shId == nElapseID)
			{
				pNpc->vctActionData.erase(iter);
	            m_TreeCtrl.DeleteItem(m_TreeCtrl.GetSelectedItem());

				SetTipInfo("提示:气泡 删除成功!");
				return;
			}
		}
	}
}

bool CNpcEditDlg::InitComboxData(CString strData,const char *pszKeyWord,const char *pszAttribute,CComboBox* comBox)
{
	assert(comBox != NULL);
	assert(pszKeyWord != NULL);

	if(NULL == comBox || NULL == pszKeyWord)
		return false;

	MeXmlDocument xTiDoc;
	if(!xTiDoc.LoadFile(strData.GetBuffer(),1))
		return false;

	MeXmlElement *pSubElem = NULL;
	pSubElem = xTiDoc.FirstChildElement("Project");
	if(NULL == pSubElem)
		return false;

	pSubElem = pSubElem->FirstChildElement();
	if(NULL == pSubElem)
		return false;
	
	while(pSubElem != NULL)
	{
		//查询该节点下的子节点
		MeXmlElement *pTeamElem = pSubElem;
		for (;pTeamElem != NULL;pTeamElem = pTeamElem->FirstChildElement())
		{
			::OutputDebugString(pTeamElem->name());
			::OutputDebugString("\n");
			if(strcmp(pTeamElem->name(),pszKeyWord) == 0)
			{
				for (;pTeamElem != NULL;pTeamElem = pTeamElem->NextSiblingElement())
				{
					if(strcmp(pszKeyWord,"Map") == 0)
					{
						Common::_tstring strMap;
						strMap.fromUTF8(pTeamElem->Attribute("MapName"));
						if(strMap.length() > 0)
						{
							int mapId;
							pTeamElem->Attribute(pszAttribute,&mapId);
							char szWord[32];
							sprintf_s(szWord,sizeof(szWord),"(%d)",mapId);
							strMap += szWord;
							comBox->AddString(strMap.c_str());
						}
					}
					else if(strcmp(pszKeyWord,"Model") == 0)
					{
						Common::_tstring strModel;
						strModel.fromUTF8(pTeamElem->Attribute("Description"));
						int modelId;
						pTeamElem->Attribute(pszAttribute,&modelId);
						char szWord[32];
						sprintf_s(szWord,sizeof(szWord),"(%d)",modelId);
						strModel += szWord;
						comBox->AddString(strModel.c_str());
					}
					else
					{
						Common::_tstring strId;
						strId.fromUTF8(pTeamElem->Attribute(pszAttribute));
						if(strId.length() > 0)
							comBox->AddString(strId.c_str());
					}
				}
				return true;
			}
		}

		pSubElem = pSubElem->NextSiblingElement();   //查询同一层次节点
	}

	return false;
}

bool CNpcEditDlg::InitComboxDataType( CComboBox* comBox, int maxID )
{
	if ( comBox )
	{
		for ( int idx = 1; idx < maxID; idx ++ )
		{
			char szWord[32] = {0};
			sprintf_s(szWord,sizeof(szWord),"%d",idx);
			comBox->AddString(szWord);
		}
		comBox->SetCurSel(0);
		return true;
	}
	return false;
}

bool CNpcEditDlg::InitComboxNpcType( CComboBox* comBox )
{
	if ( comBox )
	{
		comBox->AddString( _T("人类") );
		comBox->AddString( _T("机器") );
		comBox->AddString( _T("兽类") );
		comBox->AddString( _T("仙") );
		comBox->AddString( _T("鬼") );
		comBox->AddString( _T("妖") );
		comBox->AddString( _T("神") );
		comBox->AddString( _T("魔") );
		comBox->SetCurSel(0);
		return true;
	}
	return false;
}

void CNpcEditDlg::SetRequiresEnabled( BOOL bValue )
{
	GetDlgItem(IDC_EDIT_R_MIN)->EnableWindow(bValue);
	GetDlgItem(IDC_EDIT_R_MAX)->EnableWindow(bValue);
	GetDlgItem(IDC_EDIT_R_SEX)->EnableWindow(bValue);
	GetDlgItem(IDC_EDIT_R_TASKID)->EnableWindow(bValue);
}

void CNpcEditDlg::ClearRequiresValue()
{
	GetDlgItem(IDC_EDIT_R_MIN)->SetWindowText("");
	GetDlgItem(IDC_EDIT_R_MAX)->SetWindowText("");
	GetDlgItem(IDC_EDIT_R_SEX)->SetWindowText("");
	GetDlgItem(IDC_EDIT_R_TASKID)->SetWindowText("");
}

void CNpcEditDlg::ExpandNode(DWORD_PTR data)
{
	HTREEITEM hRoot = mEventActionTree.GetRootItem();
	while ( hRoot )
	{
		if ( mEventActionTree.GetItemData(hRoot) == data )
		{
			mEventActionTree.Expand( hRoot, TVE_EXPAND );
			return;
		}
		hRoot = mEventActionTree.GetNextSiblingItem(hRoot);
	}
}

void CNpcEditDlg::UpdateActionsToNpc()
{
	if(!CURRENTTILE)
		return;

	int mapId = CURRENTTILE->GetMapId();
	NpcInfo::Npc *pNpc = theNpcInfo.GetNpc(m_NpcID,mapId);
	if ( pNpc )
	{
		int tmpCount = (int)m_ActSetPtr.size();
		pNpc->npcAct.Clear();
		for ( int i = 0; i < tmpCount; i ++ )
		{
			pNpc->npcAct.AddAction(*m_ActSetPtr[i]);
		}
	}
}

void CNpcEditDlg::OnClose()
{
// 	int nResult = ::MessageBox(NULL,"你确定要退出吗!","Warnning",MB_OKCANCEL);
// 	if(nResult == IDCANCEL)
// 		return;

	CDialog::OnClose();
}

void CNpcEditDlg::OnDestroy()
{
	DeleteNpcActions();
	CDialog::OnDestroy();
}

void CNpcEditDlg::OnOK()
{
	return;
	//CDialog::OnOK();
}

void CNpcEditDlg::OnCancel()
{
// 	int nResult = ::MessageBox(NULL,"你确定要退出吗!","Warnning",MB_OKCANCEL);
// 	if(nResult == IDCANCEL)
// 		return;

	CDialog::OnCancel();
}



void CNpcEditDlg::InitTreeControlData(Filter eumValue,const char* pszValue/* = NULL*/)
{
	if(m_NpcID == 0)
		return;

    if(!CURRENTTILE)
        return;

    int mapID = CURRENTTILE->GetMapId();

	m_TreeCtrl.DeleteAllItems();

	HTREEITEM rootItem = NULL,elapseItem = NULL,subItem = NULL;
	NpcInfo::Npcs::iterator iter = theNpcInfo.npcs_.begin();
	NpcInfo::Npcs::iterator end  = theNpcInfo.npcs_.end();

	for ( ; iter != end; ++iter)
	{
		if(iter->second.id == m_NpcID&&iter->second.mapId == mapID) 
		{
		    //插入NpcActionData
		    int nSize = iter->second.vctActionData.size();
			for (int i = 0 ;i < nSize; i++)
			{
				 //Insert Elapse Time
				 char stritem[128];
				 sprintf_s(stritem,sizeof(stritem),"%s(%d)","Elapse",iter->second.vctActionData[i].shId);
				 elapseItem = m_TreeCtrl.InsertItem(stritem,rootItem);

				 //Insert Action Data
				 int nAmount = iter->second.vctActionData[i].vctActions.size();
				 for (int nAction = 0; nAction < nAmount; ++nAction)
				 {
					 sprintf_s(stritem,sizeof(stritem),"%s(%s)","Action",iter->second.vctActionData[i].vctActions[nAction].strAnimName.c_str());
					 subItem = m_TreeCtrl.InsertItem(stritem,elapseItem,subItem);
				 }

				 //Insert Talk
				 nAmount = iter->second.vctActionData[i].vctTalks.size();
				 for (int npcTalk = 0;npcTalk < nAmount ; ++ npcTalk)
				 {
					 sprintf_s(stritem,sizeof(stritem),"%s(%d)","Talk",iter->second.vctActionData[i].vctTalks[npcTalk].shStringId);
					 subItem = m_TreeCtrl.InsertItem(stritem,elapseItem,subItem);
				 }	
			 }
		}		
	}
	InitNpcActions(m_NpcID);
	//mEventActionTree.InsertItem("TestNode",NULL);
	//mEventActionTree.InsertItem("TestNode",NULL);
	//mEventActionTree.InsertItem("TestNode",NULL);
}

LRESULT CNpcEditDlg::WindowProc(UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
	case CB_ADDSTRING:
		::OutputDebugStr("AddString");
		break;
	case WM_MY_MESSAGE:
		OnSavexml();
		break;
	case WM_COMMAND:

		break;
	}
	return CDialog::WindowProc(message, wParam, lParam);
}




bool CNpcEditDlg::SavePositionConfig(const char *pszPath)
{
// 	const char *pDoc = 
//         "<?xml version=\"1.0\" encoding=\"utf-8\" standalone=\"yes\"?>"
// 		//"<?PositionXml version=\"1.0\" encoding=\"utf-8\" standalone=\"PositionYes\" ?>"
// 		"<Project Type=\"Npc\" Value=\"2000-10-11 21:20:20\" Count=\"0\">"
// 		"<!--<Type 0 无, <1 NPC>,<2 怪>,<3 采集物>-->"
// 		"<Positions>"
// 		"</Positions>"
// 		"</Project>";

//	Common::_tstring common = pDoc;


	//xDoc.Parse((char*)common.toUTF8().c_str()/*pDoc*/);
	{
		MeXmlDocument xDoc;
		xDoc.InsertEndChild(MeXmlDeclaration("1.0", "UTF-8", "yes"));
		MeXmlElement* pXmlProject = xDoc.InsertEndChild("Project")->ToElement();
		if (pXmlProject == NULL)
		{ 
			return false;
		}


// 		MeXmlElement *pXmlProject = xDoc.FirstChildElement("Project")->ToElement();
// 		if(NULL == pXmlProject) return false;

		char forTime[64];
		SYSTEMTIME sys;
		::GetLocalTime(&sys);
		sprintf_s(forTime,sizeof(forTime),"%d-%d-%d %d:%d:%d" ,sys.wYear,sys.wMonth,sys.wDay,sys.wHour,sys.wMinute,sys.wSecond);
		pXmlProject->SetAttribute("Value",forTime);
		pXmlProject->SetAttribute("Count",thePositionInfo.GetPositonCount());

		MeXmlElement *pXmlNpcs = pXmlProject->InsertEndChild("Positions")->ToElement();
		if(NULL == pXmlNpcs)
			return false;

		PositionInfo::Positions::iterator iter = thePositionInfo.positions_.begin();
		PositionInfo::Positions::iterator end  = thePositionInfo.positions_.end();

		for ( ; iter != end; ++iter)
		{
			MeXmlElement* pNpc = pXmlNpcs->InsertEndChild(("Position"))->ToElement();			
			pNpc->SetAttribute("Type", iter->second.type);

			pNpc->SetAttribute("TargetId",iter->second.id);

			Common::_tstring name = iter->second.name;
// 			::OutputDebugStr(name.toUTF8().c_str());
//			::OutputDebugStr("\n");
//			::OutputDebugStr(iter->second.name.c_str());

			pNpc->SetAttribute("Name",name.toUTF8().c_str());

			pNpc->SetDoubleAttribute("PositionX",static_cast<double>(iter->second.x));
			pNpc->SetDoubleAttribute("PositionY",static_cast<double>(iter->second.y));

			pNpc->SetAttribute("MapID",iter->second.mapId);
			pNpc->SetAttribute("IsShow",iter->second.isShow);
		}
		return xDoc.SaveFile(pszPath);
	}
	return false;
}


void CNpcEditDlg::ClearTalkProtery()
{
	//TalkData属性设置
	NpcInfo::TalkData talkData;
	talkData.shStringId = 0;
	talkData.shProbability = 100;
	SetTalkProtery(talkData);
}

void CNpcEditDlg::ClearActionProtery()
{
	//Action属性设置
	NpcInfo::ActionData actionData;
	actionData.strAnimName = "";
	actionData.shProbability = 100;
	SetActionProtery(actionData);
}

void CNpcEditDlg::ClearElpaseProtery()
{
	//Elapse属性设置
	NpcInfo::NpcActionData npcActionData;
	npcActionData.shId = 0;
	npcActionData.shElapseTime = 1;
	npcActionData.shNextId = 0;
	SetElpaseTime(npcActionData);
}

void CNpcEditDlg::ClearNpcProtery()
{
	//Npc属性设置
	NpcInfo::Npc npc;
	memset(&npc,0L,sizeof(npc));
	npc.level = 1;
	npc.type  = 0;
	npc.movePath = -1;
	npc.canChangeDirection = 1;
	npc.isMiniShow = 1;
	npc.isWorldShow = 1;
	npc.isCollision = 0;
	npc.bodyScale = 1.0f;
	SetNpcProtery(npc);
}


void CNpcEditDlg::SetTipInfo(const char* pszTip)
{
	m_strNote = pszTip;
	UpdateData(false);
}

bool CNpcEditDlg::SetMaxNpcInfo()
{
	char szNpcInfo[64];

	NpcInfo::Npcs::reverse_iterator iter = theNpcInfo.npcs_.rbegin();
		
    if(iter != theNpcInfo.npcs_.rend())
	     sprintf_s(szNpcInfo,sizeof(szNpcInfo),"%s ID = %d",iter->second.name.c_str(),iter->second.id);
	
	else
		 sprintf_s(szNpcInfo,sizeof(szNpcInfo),"%s","无");

	GetDlgItem(IDC_MAXNPCINFO)->SetWindowText(szNpcInfo);
	return true;
}


bool CNpcEditDlg::InitArrayData(CString strData,const char *pszKeyWord,const char *pszAttribute,CStringArray& arrayStr)
{
	assert(pszKeyWord != NULL);

	if(NULL == pszKeyWord)
		return false;

	MeXmlDocument xTiDoc;
	if(!xTiDoc.LoadFile(strData.GetBuffer(),1))
		return false;

	MeXmlElement *pSubElem = NULL;
	pSubElem = xTiDoc.FirstChildElement("Project");
	if(NULL == pSubElem)
		return false;

	pSubElem = pSubElem->FirstChildElement();
	if(NULL == pSubElem)
		return false;

	while(pSubElem != NULL)
	{
		//查询该节点下的子节点
		MeXmlElement *pTeamElem = pSubElem;
		for (;pTeamElem != NULL;pTeamElem = pTeamElem->FirstChildElement())
		{
			if(strcmp(pTeamElem->name(),pszKeyWord) == 0)
			{
				for (;pTeamElem != NULL;pTeamElem = pTeamElem->NextSiblingElement())
				{
					Common::_tstring strId;
					strId.fromUTF8(pTeamElem->Attribute(pszAttribute));
					if(strId.length() > 0)
						arrayStr.Add(strId.c_str());
				}
				return true;
			}
		}
		pSubElem = pSubElem->NextSiblingElement();   //查询同一层次节点
	}
	return false;
}

void CNpcEditDlg::InitNpcData(int npcId)
{
    if(!CURRENTTILE)
        return;

    bIsSetScroll = true;
    int mapId = CURRENTTILE->GetMapId();
    NpcInfo::Npc *pNpc = theNpcInfo.GetNpc(npcId,mapId);

	//NpcInfo::Npc *pNpc = theNpcInfo.GetNpcByStaticId(m_NpcID); 
	if(NULL != pNpc)
	{
		SetNpcProtery(*pNpc);
		SetNpcFightData(*pNpc);
	}

}

void CNpcEditDlg::InitNpcActions(int npcId)
{
	if(!CURRENTTILE)
		return;

	int mapId = CURRENTTILE->GetMapId();
	NpcInfo::Npc *pNpc = theNpcInfo.GetNpc(npcId,mapId);
	if ( pNpc )
	{
		DeleteNpcActions();
		int count = pNpc->npcAct.GetSize();
		for ( int i = 0; i < count; i ++ )
		{
			Action* act = pNpc->npcAct.GetOneActionByIndex(i);
			Action* actCpy = new Action();
			*actCpy = *act;
			m_ActSetPtr.push_back(actCpy);
		}
		RefreshNpcActionUI();
	}
}

void CNpcEditDlg::RefreshNpcActionUI()
{
	mEventActionTree.DeleteAllItems();
	if ( m_ActSetPtr.size() > 0 )
	{
		int count = (int)m_ActSetPtr.size();
		for ( int i = 0; i < count; i ++ )
		{
			HTREEITEM hAction = mEventActionTree.InsertItem("Action", NULL);
			mEventActionTree.SetItemData( hAction, (DWORD_PTR)m_ActSetPtr[i] );
			Action* act = (Action*)mEventActionTree.GetItemData(hAction);

			int mtCount = (int)((Action*)m_ActSetPtr[i])->vecMustTerm.size();
			for ( int j = 0; j < mtCount; j ++ )
			{
				Require* rq = &(((Action*)m_ActSetPtr[i])->vecMustTerm[j]);
				char rStr[128] = {0};
				if ( rq->eType == Req_Dislen || rq->eType == Req_Level )
				{
					sprintf_s( rStr, sizeof(rStr), "Require(%d,%f,%f,%d)", rq->eType, rq->fMin, rq->fMax, 1 );
				}
				else if ( rq->eType == Req_Sex )
				{
					sprintf_s( rStr, sizeof(rStr), "Require(%d,%d,%d)", rq->eType, rq->nSex, 1 );
				}
				else if ( rq->eType == Req_Task )
				{
					sprintf_s( rStr, sizeof(rStr), "Require(%d,%d,%d)", rq->eType, rq->nTaskID, 1 );
				}
				
				HTREEITEM hRequire = mEventActionTree.InsertItem(rStr, hAction);
				mEventActionTree.SetItemData( hRequire, (DWORD_PTR)rq );
			}

			int prCount = (int)((Action*)m_ActSetPtr[i])->vecProbilityTerm.size();
			for ( int j = 0; j < prCount; j ++ )
			{
				Require* rq = &(((Action*)m_ActSetPtr[i])->vecProbilityTerm[j]);
				char rStr[128] = {0};
				if ( rq->eType == Req_Dislen || rq->eType == Req_Level )
				{
					sprintf_s( rStr, sizeof(rStr), "Require(%d,%f,%f,%d)", rq->eType, rq->fMin, rq->fMax, 0 );
				}
				else if ( rq->eType == Req_Sex )
				{
					sprintf_s( rStr, sizeof(rStr), "Require(%d,%d,%d)", rq->eType, rq->nSex, 0 );
				}
				else if ( rq->eType == Req_Task )
				{
					sprintf_s( rStr, sizeof(rStr), "Require(%d,%d,%d)", rq->eType, rq->nTaskID, 0 );
				}

				HTREEITEM hRequire = mEventActionTree.InsertItem(rStr, hAction);
				mEventActionTree.SetItemData( hRequire, (DWORD_PTR)rq );
			}

			if( ((Action*)m_ActSetPtr[i])->talk.nStringId > 0 )
			{
				char rStr[128] = {0};
				sprintf_s( rStr, sizeof(rStr), "Event(%d,%d,%d,%d)", 1, ((Action*)m_ActSetPtr[i])->talk.nStringId, ((Action*)m_ActSetPtr[i])->talk.nProbability, ((Action*)m_ActSetPtr[i])->talk.nDelayTime );
				HTREEITEM hItem = mEventActionTree.InsertItem( rStr, hAction );
				mEventActionTree.SetItemData( hItem, (DWORD_PTR)&((Action*)m_ActSetPtr[i])->talk );
			}

			if ( ((Action*)m_ActSetPtr[i])->anim.strType.empty() == false )
			{
				char rStr[128] = {0};
				sprintf_s( rStr, sizeof(rStr), "Event(%d,%s,%d,%d)", 2, ((Action*)m_ActSetPtr[i])->anim.strType.c_str(), ((Action*)m_ActSetPtr[i])->anim.nProbability, ((Action*)m_ActSetPtr[i])->anim.nDelayTime );
				HTREEITEM hItem = mEventActionTree.InsertItem( rStr, hAction );
				mEventActionTree.SetItemData( hItem, (DWORD_PTR)&((Action*)m_ActSetPtr[i])->anim );
			}

			if ( ((Action*)m_ActSetPtr[i])->autoFace.bIsAutoFace == true )
			{
				char rStr[128] = {0};
				sprintf_s( rStr, sizeof(rStr), "Event(%d,%d,%d,%d)", 3, (int)((Action*)m_ActSetPtr[i])->autoFace.bIsAutoFace, ((Action*)m_ActSetPtr[i])->autoFace.nProbability, ((Action*)m_ActSetPtr[i])->autoFace.nDelayTime );
				HTREEITEM hItem = mEventActionTree.InsertItem( rStr, hAction );
				mEventActionTree.SetItemData( hItem, (DWORD_PTR)&((Action*)m_ActSetPtr[i])->autoFace );
			}
		}
	}
}

void CNpcEditDlg::ClearNpcActionUI()
{
	GetDlgItem(IDC_EDIT_R_MIN)->SetWindowText("");
	GetDlgItem(IDC_EDIT_R_MAX)->SetWindowText("");
	GetDlgItem(IDC_EDIT_R_SEX)->SetWindowText("");
	GetDlgItem(IDC_EDIT_R_TASKID)->SetWindowText("");
	GetDlgItem(IDC_EDIT_E_VALUE)->SetWindowText("");
	GetDlgItem(IDC_EDIT_E_PROB)->SetWindowText("");
	GetDlgItem(IDC_EDIT_E_DELAYTIME)->SetWindowText("");

	CComboBox* pBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMRTYPE));
	if ( pBox )
	{
		pBox->SetCurSel(0);
	}
	pBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMETYPE));
	if ( pBox )
	{
		pBox->SetCurSel(0);
	}

	OnCbnSelchangeComrtype();
	OnCbnSelchangeCometype();

}

void CNpcEditDlg::DeleteNpcActions()
{
	if ( m_ActSetPtr.size() > 0 )
	{
		int count = (int)m_ActSetPtr.size();
		for ( int i = 0; i < count; i ++ )
		{
			delete m_ActSetPtr[i];
		}
		mEventActionTree.DeleteAllItems();
		m_ActSetPtr.clear();
	}
}

bool CNpcEditDlg::ValidateRequire()
{
	CComboBox* pBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMRTYPE));
	if ( pBox )
	{
		CString tmpStr;
		int idx = pBox->GetCurSel() + 1;
		if ( idx == Req_Dislen )
		{
			GetDlgItem(IDC_EDIT_R_MIN)->GetWindowText(tmpStr);
			if ( tmpStr.IsEmpty() )
			{
				::MessageBox( NULL, "距离最小值不能为空！", "Warning", 0 );
				return false;
			}
			GetDlgItem(IDC_EDIT_R_MAX)->GetWindowText(tmpStr);
			if ( tmpStr.IsEmpty() )
			{
				::MessageBox( NULL, "距离最大值不能为空！", "Warning", 0 );
				return false;
			}

		}
		else if ( idx == Req_Sex )
		{
			GetDlgItem(IDC_EDIT_R_SEX)->GetWindowText(tmpStr);
			if ( tmpStr.IsEmpty() )
			{
				::MessageBox( NULL, "性别不能为空！", "Warning", 0 );
				return false;
			}
			
		}
		else if ( idx == Req_Task )
		{
			GetDlgItem(IDC_EDIT_R_TASKID)->GetWindowText(tmpStr);
			if ( tmpStr.IsEmpty() )
			{
				::MessageBox( NULL, "任务ID不能为空！", "Warning", 0 );
				return false;
			}
		}
		else if ( idx == Req_Level )
		{
			GetDlgItem(IDC_EDIT_R_MIN)->GetWindowText(tmpStr);
			if ( tmpStr.IsEmpty() )
			{
				::MessageBox( NULL, "最低等级不能为空！", "Warning", 0 );
				return false;
			}
			GetDlgItem(IDC_EDIT_R_MAX)->GetWindowText(tmpStr);
			if ( tmpStr.IsEmpty() )
			{
				::MessageBox( NULL, "最高等级不能为空！", "Warning", 0 );
				return false;
			}
		}
		return true;
	}
	return false;
}
bool CNpcEditDlg::ValidateEvent()
{
	//CComboBox* pBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMETYPE));
	//if ( pBox )
	//{

	//}
	CString tmpStr;
	GetDlgItem(IDC_EDIT_E_VALUE)->GetWindowText(tmpStr);
	if ( tmpStr.IsEmpty() )
	{
		::MessageBox( NULL, "动作名称或说话字符串不能为空！", "Warning", 0 );
		return false;
	}
	GetDlgItem(IDC_EDIT_E_DELAYTIME)->GetWindowText(tmpStr);
	if ( tmpStr.IsEmpty() )
	{
		::MessageBox( NULL, "延时时间不能为空！", "Warning", 0 );
		return false;
	}
	GetDlgItem(IDC_EDIT_E_DELAYTIME)->GetWindowText(tmpStr);
	if ( tmpStr.IsEmpty() )
	{
		::MessageBox( NULL, "延时时间不能为空！", "Warning", 0 );
		return false;
	}

	return true;
}



void CNpcEditDlg::DeleteOneAction(Action* action)
{

	for ( std::vector<Action*>::iterator it = m_ActSetPtr.begin(); it != m_ActSetPtr.end(); it ++ )
	{
		if(  *it == action )
		{
			m_ActSetPtr.erase(it);
			RefreshNpcActionUI();
			return;
		}
	}
}

void CNpcEditDlg::OnBnClickedNpcmodify()
{
	if(m_NpcID <= 0)
		return;

    // 得到相同Id的Npc
	NpcInfo::Npc *pNpc = theNpcInfo.GetNpcByStaticId(m_NpcID);

	if(NULL != pNpc)
	{
		NpcInfo::Npc npc;
		if(GetNpcProtery(npc))
		{
			//pNpc->mapId = npc.mapId;
//			pNpc->modelId = npc.modelId;				
// 			pNpc->x = npc.x;					
// 			pNpc->y = npc.y;					
// 			pNpc->z = npc.z;                    
			
//			pNpc->direction = npc.direction;				

//			pNpc->bodyScale = npc.bodyScale;
            //pNpc->nTaskMenu = npc.nTaskMenu;
            // 每个国家的NPCMenu是一样的
            NpcInfo::FourNpc* FNpc = theNpcInfo.GetFourNpc(m_NpcID);
            for (int i=0; i<4; ++i)
            {
                if (FNpc->FourCountryNpc[i] == NULL)
                { continue;}

                FNpc->FourCountryNpc[i]->id = npc.id;
                FNpc->FourCountryNpc[i]->type = npc.type;   // Npc类型
                FNpc->FourCountryNpc[i]->dynamicId = 0;
                FNpc->FourCountryNpc[i]->name = npc.name;	
                FNpc->FourCountryNpc[i]->pinyin = npc.pinyin;
                FNpc->FourCountryNpc[i]->level =npc.level;					
                FNpc->FourCountryNpc[i]->movePath = npc.movePath;				
                FNpc->FourCountryNpc[i]->canChangeDirection = npc.canChangeDirection;	
                FNpc->FourCountryNpc[i]->triggerScript = npc.triggerScript;    // 触发脚本
                FNpc->FourCountryNpc[i]->actionScript = npc.actionScript;  // 动作脚本
                FNpc->FourCountryNpc[i]->isMiniShow = npc.isMiniShow;
                FNpc->FourCountryNpc[i]->isWorldShow = npc.isWorldShow;
                FNpc->FourCountryNpc[i]->isCollision = npc.isCollision;			
                FNpc->FourCountryNpc[i]->title = npc.title;
                FNpc->FourCountryNpc[i]->tip = npc.tip;
                FNpc->FourCountryNpc[i]->strHeadPicture = npc.strHeadPicture;
                FNpc->FourCountryNpc[i]->isDynamicCollision=npc.isDynamicCollision;
                FNpc->FourCountryNpc[i]->nTaskMenu = npc.nTaskMenu;
                FNpc->FourCountryNpc[i]->uchCountryID = i; // 国家ID从0，1，2，3
				FNpc->FourCountryNpc[i]->phyle = npc.phyle;
            }

			//char szWord[32];
			//sprintf_s(szWord,sizeof(szWord),"%s(%d)",npc.name.c_str(),npc.id);
			//m_TreeCtrl.SetItemText(m_TreeCtrl.GetSelectedItem(),szWord);

			{
				char szTipInfo[64];
				sprintf_s(szTipInfo,sizeof(szTipInfo),"%s(%d)保存成功!",npc.name.c_str(),npc.id);
				SetTipInfo(szTipInfo);
				SetMaxNpcInfo();
			}
		}
	}
	else
	   MessageBox("Npc未找到!");
}

void CNpcEditDlg::OnDelNpcMenu() // 删除NPCMenu内容的某一项
{
    // TODO: Add your control notification handler code here
    int nIndex = m_NpcMenuList.GetCurSel();
    m_NpcMenuList.DeleteString(nIndex);
}

void CNpcEditDlg::OnNpcMenuUpdate()
{
    // TODO: Add your control notification handler code here
    CString strNpcMenuID;
    m_NpcMenuStringID.GetWindowText(strNpcMenuID);
    CNpcString::npcTalk* pNpcTalk = theNpcStringForMenu.GetDataByIDForMenu(atoi(strNpcMenuID));
    strNpcMenuID += "的NPC菜单字串ID不存在或者为0，请检查！";
    if (pNpcTalk == NULL)
    {

        MessageBox(strNpcMenuID, _T("Warning"), MB_OK);
        return;
    }
    else
    {
        string strNpcMenuContent = "";
        int nSubItem = 1;
        CString strNewMenu = "请在此处右键单击填入新内容...";
        for (int i=0; i<m_NpcMenuList.GetCount(); ++i)
        {
            CString strNpcMenu;
            m_NpcMenuList.GetText(i, strNpcMenu);
            if ( strNpcMenu.GetLength() <= 0 ) // 如果取得某一行的字串为空
            { continue;}

            if (strNpcMenu == strNewMenu) // 如果点击了新增又没有编辑
            { 
                strNpcMenu = ""; 
            }
            else
            { 
                strNpcMenu += " ";
            }

            strNpcMenuContent += strNpcMenu.GetBuffer();
        }
        pNpcTalk->m_strTalk = strNpcMenuContent.c_str();
    }
}

void CNpcEditDlg::OnChangeNpcMenuStringId()
{
    // TODO:  If this is a RICHEDIT control, the control will not
    // send this notification unless you override the CDialog::OnInitDialog()
    // function and call CRichEditCtrl().SetEventMask()
    // with the ENM_CHANGE flag ORed into the mask.

    // TODO:  Add your control notification handler code here
    CString strMenuID;
    m_NpcMenuStringID.GetWindowText(strMenuID);
    int nMenuID = atoi(strMenuID);
    if (nMenuID <= 200000) // string ID 从200001开始
    { return;}

    CNpcString::npcTalk* pNpcTalk = theNpcStringForMenu.GetDataByIDForMenu(nMenuID);
    if (pNpcTalk == NULL) // 如果找不到该字串的NpcTalk
    { return;}
    else
    {
        m_NpcMenuList.ResetContent();//清空所有数据

        CString strNpcMenuContent = static_cast<CString>(pNpcTalk->m_strTalk.c_str());
        CString strToken;
        int nItem = 0;
        const int nSubItem = 0;
        int nStartPos = 0;
        int nCount = 0;
        strToken = strNpcMenuContent.Tokenize(" ", nStartPos);
        while( strToken.GetLength() > 0 )
        {
            m_NpcMenuList.InsertString(nCount++, strToken.GetBuffer());
            strToken = strNpcMenuContent.Tokenize(" ", nStartPos);
        }
    }
}

void CNpcEditDlg::OnInsertNewItem()
{
    // TODO: Add your command handler code here
    int nCount = m_NpcMenuList.GetCurSel();
    if (nCount == LB_ERR)
    {
        nCount = m_NpcMenuList.GetCount();
    }
    else
    {
        nCount += 1;
    }

    CString strNewMenu = "请在此处右键单击填入新内容...";
    for (int i=0; i<m_NpcMenuList.GetCount(); ++i)
    {
        CString strItem;
        m_NpcMenuList.GetText(i, strItem);
        if (strNewMenu == strItem)
        {
            return;
        }
    }
    m_NpcMenuList.InsertString(nCount, strNewMenu);
    m_NpcMenuList.SetCurSel(nCount);
}
void CNpcEditDlg::OnCbnSelchangeComrtype()
{
	// TODO: Add your control notification handler code here
	CComboBox* pBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMRTYPE));
	if ( pBox )
	{
		ClearRequiresValue();
		SetRequiresEnabled(FALSE);
		int idx = pBox->GetCurSel() + 1;
		if ( idx == Req_Dislen )
		{
			GetDlgItem(IDC_EDIT_R_MIN)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_R_MAX)->EnableWindow(TRUE);

			GetDlgItem(IDC_EDIT_R_MIN)->SetFocus();
		}
		else if ( idx == Req_Sex )
		{
			GetDlgItem(IDC_EDIT_R_SEX)->EnableWindow(TRUE);

			GetDlgItem(IDC_EDIT_R_SEX)->SetFocus();
		}
		else if ( idx == Req_Task )
		{
			GetDlgItem(IDC_EDIT_R_TASKID)->EnableWindow(TRUE);

			GetDlgItem(IDC_EDIT_R_TASKID)->SetFocus();
		}
		else if ( idx == Req_Level )
		{
			GetDlgItem(IDC_EDIT_R_MIN)->EnableWindow(TRUE);
			GetDlgItem(IDC_EDIT_R_MAX)->EnableWindow(TRUE);

			GetDlgItem(IDC_EDIT_R_MIN)->SetFocus();
		}
	}
}

void CNpcEditDlg::OnCbnSelchangeCometype()
{
	// TODO: Add your control notification handler code here
	CComboBox* pBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMETYPE));
	
	if ( pBox )
	{
		int idx = pBox->GetCurSel() + 1;
		if ( idx == Event_Talk )
		{
			GetDlgItem(IDC_STATIC_VALUE)->SetWindowText("StringId");
		}
		else if ( idx == Event_Anim )
		{
			GetDlgItem(IDC_STATIC_VALUE)->SetWindowText("Name");
		}
		else if ( idx == Event_AutoFace )
		{
			GetDlgItem(IDC_STATIC_VALUE)->SetWindowText("AutoFace");
		}
		
	}
}

void CNpcEditDlg::OnBnClickedBnactionAdd()
{
	// TODO: Add your control notification handler code here
	//添加一个条件事件
	if ( ValidateEvent() && ValidateRequire() )
	{
		Action* act = new Action();

		CComboBox* pBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMRTYPE));
		if ( pBox )
		{
			Require req;
			int idx = pBox->GetCurSel() + 1;
			if ( idx == Req_Dislen )
			{
				req.eType = Req_Dislen;
				CString strMin;
				CString strMax;
				GetDlgItem(IDC_EDIT_R_MIN)->GetWindowText(strMin);
				GetDlgItem(IDC_EDIT_R_MAX)->GetWindowText(strMax);
				req.fMin = atof(strMin.GetBuffer(strMin.GetLength()));
				req.fMax = atof(strMax.GetBuffer(strMax.GetLength()));
			}
			else if ( idx == Req_Sex )
			{
				req.eType = Req_Sex;
				CString strSex;
				GetDlgItem(IDC_EDIT_R_SEX)->GetWindowText(strSex);
				req.nSex = atoi(strSex.GetBuffer(strSex.GetLength()));
			}
			else if ( idx == Req_Task )
			{
				req.eType = Req_Task;
				CString strTask;
				GetDlgItem(IDC_EDIT_R_TASKID)->GetWindowText(strTask);
				req.nTaskID = atoi(strTask.GetBuffer(strTask.GetLength()));
			}
			else if ( idx == Req_Level )
			{
				req.eType = Req_Level;
				CString strMin;
				CString strMax;
				GetDlgItem(IDC_EDIT_R_MIN)->GetWindowText(strMin);
				GetDlgItem(IDC_EDIT_R_MAX)->GetWindowText(strMax);
				req.fMin = atof(strMin.GetBuffer(strMin.GetLength()));
				req.fMax = atof(strMax.GetBuffer(strMax.GetLength()));

			}

			if( ((CButton*)GetDlgItem(IDC_CHECK_NEED))->GetCheck() == 1 )
			{
				act->vecMustTerm.push_back(req);
			}
			else
			{
				act->vecProbilityTerm.push_back(req);
			}
		}

		pBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMETYPE));

		if ( pBox )
		{
			int idx = pBox->GetCurSel() + 1;
			if ( idx == Event_Talk )
			{
				CString talk;
				GetDlgItem(IDC_EDIT_E_VALUE)->GetWindowText(talk);
				act->talk.nStringId = atoi(talk.GetBuffer(talk.GetLength()));
				CString dt;
				GetDlgItem(IDC_EDIT_E_DELAYTIME)->GetWindowText(dt);
				act->talk.nDelayTime = atoi(dt.GetBuffer(dt.GetLength()));
				CString prob;
				GetDlgItem(IDC_EDIT_E_PROB)->GetWindowText(prob);
				act->talk.nProbability = atoi(prob.GetBuffer(prob.GetLength()));
			}
			else if ( idx == Event_Anim )
			{
				CString aniType;
				GetDlgItem(IDC_EDIT_E_VALUE)->GetWindowText(aniType);
				act->anim.strType = std::string(aniType.GetBuffer(aniType.GetLength()));
				CString dt;
				GetDlgItem(IDC_EDIT_E_DELAYTIME)->GetWindowText(dt);
				act->anim.nDelayTime = atoi(dt.GetBuffer(dt.GetLength()));
				CString prob;
				GetDlgItem(IDC_EDIT_E_PROB)->GetWindowText(prob);
				act->anim.nProbability = atoi(prob.GetBuffer(prob.GetLength()));
			}
			else if ( idx == Event_AutoFace )
			{

				CString autoface;
				GetDlgItem(IDC_EDIT_E_VALUE)->GetWindowText(autoface);
				act->autoFace.bIsAutoFace = ( atoi(autoface.GetBuffer(autoface.GetLength())) == 0 ) ? false : true;
				CString dt;
				GetDlgItem(IDC_EDIT_E_DELAYTIME)->GetWindowText(dt);
				act->autoFace.nDelayTime = atoi(dt.GetBuffer(dt.GetLength()));
				CString prob;
				GetDlgItem(IDC_EDIT_E_PROB)->GetWindowText(prob);
				act->autoFace.nProbability = atoi(prob.GetBuffer(prob.GetLength()));
			}

		}
		
		m_ActSetPtr.push_back(act);

		mEventActionTree.DeleteAllItems();
		RefreshNpcActionUI();
	}


}

void CNpcEditDlg::OnBnClickedBnactionDelete()
{
	// TODO: Add your control notification handler code here
	//删除一个条件事件
	HTREEITEM hItem = mEventActionTree.GetSelectedItem();
	CString  cItemText = mEventActionTree.GetItemText(hItem);

	if(!IsActionNode(cItemText))
	{
		::MessageBox(NULL,"请选择Action节点!","Warnning",MB_OK);
		return;
	}
	Action* act = (Action*)mEventActionTree.GetItemData(hItem);
	DeleteOneAction(act);
	

}

void CNpcEditDlg::OnTvnSelchangedTree2(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMTREEVIEW pNMTreeView = reinterpret_cast<LPNMTREEVIEW>(pNMHDR);
	// TODO: Add your control notification handler code here
	*pResult = 0;

	HTREEITEM hItem = mEventActionTree.GetSelectedItem();
	CString cItemText = mEventActionTree.GetItemText(hItem);

	ClearNpcActionUI();
	if ( IsActionsNode(cItemText) )
	{
		//do nothing...
	}
	else if ( IsRequireNode(cItemText) )
	{
		Require* rq = (Require*)mEventActionTree.GetItemData(hItem);
		CComboBox* pBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMRTYPE));
		if ( pBox )
		{
			pBox->SetCurSel(rq->eType - 1);
			OnCbnSelchangeComrtype();
			int idx = pBox->GetCurSel() + 1;
			if ( idx == Req_Dislen )
			{
				CString tmpStr;
				tmpStr.Format("%f",rq->fMin);
				GetDlgItem(IDC_EDIT_R_MIN)->SetWindowText(tmpStr);
				tmpStr.Format("%f",rq->fMax);
				GetDlgItem(IDC_EDIT_R_MAX)->SetWindowText(tmpStr);
			}
			else if ( idx == Req_Sex )
			{
				CString tmpStr;
				tmpStr.Format("%d",rq->nSex);
				GetDlgItem(IDC_EDIT_R_SEX)->SetWindowText(tmpStr);
			}
			else if ( idx == Req_Task )
			{
				CString tmpStr;
				tmpStr.Format("%d",rq->nTaskID);
				GetDlgItem(IDC_EDIT_R_TASKID)->SetWindowText(tmpStr);
			}
			else if ( idx == Req_Level )
			{
				CString tmpStr;
				tmpStr.Format("%f",rq->fMin);
				GetDlgItem(IDC_EDIT_R_MIN)->SetWindowText(tmpStr);
				tmpStr.Format("%f",rq->fMax);
				GetDlgItem(IDC_EDIT_R_MAX)->SetWindowText(tmpStr);
			}
		}
		
	}
	else if ( IsEventTalkNode(cItemText) )
	{
		EventTalk* evt = (EventTalk*)mEventActionTree.GetItemData(hItem);
		CComboBox* pBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMETYPE));
		if ( pBox )
		{
			pBox->SetCurSel(0);
			CString tmpStr;
			tmpStr.Format("%d", evt->nStringId);
			GetDlgItem(IDC_EDIT_E_VALUE)->SetWindowText(tmpStr);
			tmpStr.Format("%d", evt->nProbability);
			GetDlgItem(IDC_EDIT_E_PROB)->SetWindowText(tmpStr);
			tmpStr.Format("%d", evt->nDelayTime);
			GetDlgItem(IDC_EDIT_E_DELAYTIME)->SetWindowText(tmpStr);
		}
	}
	else if ( IsEventAnimNode(cItemText) )
	{
		EventAnim* evt = (EventAnim*)mEventActionTree.GetItemData(hItem);
		CComboBox* pBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMETYPE));
		if ( pBox )
		{
			pBox->SetCurSel(1);
			CString tmpStr;
			tmpStr.Format("%s", evt->strType.c_str());
			GetDlgItem(IDC_EDIT_E_VALUE)->SetWindowText(tmpStr);
			tmpStr.Format("%d", evt->nProbability);
			GetDlgItem(IDC_EDIT_E_PROB)->SetWindowText(tmpStr);
			tmpStr.Format("%d", evt->nDelayTime);
			GetDlgItem(IDC_EDIT_E_DELAYTIME)->SetWindowText(tmpStr);
		}
	}
	else if ( IsEventFaceToNode(cItemText) )
	{
		EventAutoFace* evt = (EventAutoFace*)mEventActionTree.GetItemData(hItem);
		CComboBox* pBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMETYPE));
		if ( pBox )
		{
			pBox->SetCurSel(2);
			CString tmpStr;
			tmpStr.Format("%d", evt->bIsAutoFace ? 1 : 0);
			GetDlgItem(IDC_EDIT_E_VALUE)->SetWindowText(tmpStr);
			tmpStr.Format("%d", evt->nProbability);
			GetDlgItem(IDC_EDIT_E_PROB)->SetWindowText(tmpStr);
			tmpStr.Format("%d", evt->nDelayTime);
			GetDlgItem(IDC_EDIT_E_DELAYTIME)->SetWindowText(tmpStr);
		}
	}
 
}

void CNpcEditDlg::OnBnClickedBnrequireInsert()
{
	// TODO: Add your control notification handler code here
	//添加一个条件
	HTREEITEM hItem = mEventActionTree.GetSelectedItem();
	CString  cItemText = mEventActionTree.GetItemText(hItem);

	if(!IsActionNode(cItemText))
	{
		::MessageBox(NULL,"请选择Action节点!","Warnning",MB_OK);
		return;
	}
	Action* act = (Action*)mEventActionTree.GetItemData(hItem);
	if ( ValidateRequire() )
	{
		CComboBox* pBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMRTYPE));
		if ( pBox )
		{
			Require req;
			int idx = pBox->GetCurSel() + 1;
			if ( idx == Req_Dislen )
			{
				req.eType = Req_Dislen;
				CString strMin;
				CString strMax;
				GetDlgItem(IDC_EDIT_R_MIN)->GetWindowText(strMin);
				GetDlgItem(IDC_EDIT_R_MAX)->GetWindowText(strMax);
				req.fMin = atof(strMin.GetBuffer(strMin.GetLength()));
				req.fMax = atof(strMax.GetBuffer(strMax.GetLength()));
			}
			else if ( idx == Req_Sex )
			{
				req.eType = Req_Sex;
				CString strSex;
				GetDlgItem(IDC_EDIT_R_SEX)->GetWindowText(strSex);
				req.nSex = atoi(strSex.GetBuffer(strSex.GetLength()));
			}
			else if ( idx == Req_Task )
			{
				req.eType = Req_Task;
				CString strTask;
				GetDlgItem(IDC_EDIT_R_TASKID)->GetWindowText(strTask);
				req.nTaskID = atoi(strTask.GetBuffer(strTask.GetLength()));
			}
			else if ( idx == Req_Level )
			{
				req.eType = Req_Level;
				CString strMin;
				CString strMax;
				GetDlgItem(IDC_EDIT_R_MIN)->GetWindowText(strMin);
				GetDlgItem(IDC_EDIT_R_MAX)->GetWindowText(strMax);
				req.fMin = atof(strMin.GetBuffer(strMin.GetLength()));
				req.fMax = atof(strMax.GetBuffer(strMax.GetLength()));

			}

			if( ((CButton*)GetDlgItem(IDC_CHECK_NEED))->GetCheck() == 1 )
			{
				act->vecMustTerm.push_back(req);
			}
			else
			{
				act->vecProbilityTerm.push_back(req);
			}
		}
		RefreshNpcActionUI();
		ExpandNode((DWORD_PTR)act);
	}

}

void CNpcEditDlg::OnBnClickedBneventInsert()
{
	// TODO: Add your control notification handler code here
	//添加一个事件，注意这里还要判断是否加重复
	HTREEITEM hItem = mEventActionTree.GetSelectedItem();
	CString  cItemText = mEventActionTree.GetItemText(hItem);

	if(!IsActionNode(cItemText))
	{
		::MessageBox(NULL,"请选择Action节点!","Warnning",MB_OK);
		return;
	}
	Action* act = (Action*)mEventActionTree.GetItemData(hItem);

	CComboBox* pBox  = static_cast<CComboBox*>(GetDlgItem(IDC_COMETYPE));


	if ( ValidateEvent() )
	{
		if ( pBox )
		{
			int idx = pBox->GetCurSel() + 1;
			if ( idx == Event_Talk )
			{
				if ( act->talk.nStringId > 0 )
				{
					::MessageBox(NULL,"已经存在Talk节点，不能再添加了!","Warnning",MB_OK);
					return;
				}
				CString talk;
				GetDlgItem(IDC_EDIT_E_VALUE)->GetWindowText(talk);
				act->talk.nStringId = atoi(talk.GetBuffer(talk.GetLength()));
				CString dt;
				GetDlgItem(IDC_EDIT_E_DELAYTIME)->GetWindowText(dt);
				act->talk.nDelayTime = atoi(dt.GetBuffer(dt.GetLength()));
				CString prob;
				GetDlgItem(IDC_EDIT_E_PROB)->GetWindowText(prob);
				act->talk.nProbability = atoi(prob.GetBuffer(prob.GetLength()));
			}
			else if ( idx == Event_Anim )
			{
				if ( act->anim.strType.empty() == false )
				{
					::MessageBox(NULL,"已经存在Animation节点，不能再添加了!","Warnning",MB_OK);
					return;
				}
				CString aniType;
				GetDlgItem(IDC_EDIT_E_VALUE)->GetWindowText(aniType);
				act->anim.strType = std::string(aniType.GetBuffer(aniType.GetLength()));
				CString dt;
				GetDlgItem(IDC_EDIT_E_DELAYTIME)->GetWindowText(dt);
				act->anim.nDelayTime = atoi(dt.GetBuffer(dt.GetLength()));
				CString prob;
				GetDlgItem(IDC_EDIT_E_PROB)->GetWindowText(prob);
				act->anim.nProbability = atoi(prob.GetBuffer(prob.GetLength()));
			}
			else if ( idx == Event_AutoFace )
			{
				if ( act->autoFace.bIsAutoFace == true )
				{
					::MessageBox(NULL,"已经存在AutoFace节点，不能再添加了!","Warnning",MB_OK);
					return;
				}
				CString autoface;
				GetDlgItem(IDC_EDIT_E_VALUE)->GetWindowText(autoface);
				act->autoFace.bIsAutoFace = ( atoi(autoface.GetBuffer(autoface.GetLength())) == 0 ) ? false : true;
				CString dt;
				GetDlgItem(IDC_EDIT_E_DELAYTIME)->GetWindowText(dt);
				act->autoFace.nDelayTime = atoi(dt.GetBuffer(dt.GetLength()));
				CString prob;
				GetDlgItem(IDC_EDIT_E_PROB)->GetWindowText(prob);
				act->autoFace.nProbability = atoi(prob.GetBuffer(prob.GetLength()));
			}
		}
		RefreshNpcActionUI();
		ExpandNode((DWORD_PTR)act);
	}

}

void CNpcEditDlg::OnBnClickedBnrequireModify()
{
	// TODO: Add your control notification handler code here
	//条件修改
	HTREEITEM hItem = mEventActionTree.GetSelectedItem();
	CString  cItemText = mEventActionTree.GetItemText(hItem);

	if(!IsRequireNode(cItemText))
	{
		::MessageBox(NULL,"请选择Require节点!","Warnning",MB_OK);
		return;
	}

	HTREEITEM hParent = mEventActionTree.GetParentItem(hItem); 
	Action* act = (Action*)mEventActionTree.GetItemData( hParent );
	
	if ( ValidateRequire() )
	{
		CComboBox* pBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMRTYPE));
		if ( pBox )
		{
			Require& req = *(Require*)mEventActionTree.GetItemData(hItem);
			int idx = pBox->GetCurSel() + 1;
			if ( idx == Req_Dislen )
			{
				req.eType = Req_Dislen;
				CString strMin;
				CString strMax;
				GetDlgItem(IDC_EDIT_R_MIN)->GetWindowText(strMin);
				GetDlgItem(IDC_EDIT_R_MAX)->GetWindowText(strMax);
				req.fMin = atof(strMin.GetBuffer(strMin.GetLength()));
				req.fMax = atof(strMax.GetBuffer(strMax.GetLength()));
			}
			else if ( idx == Req_Sex )
			{
				req.eType = Req_Sex;
				CString strSex;
				GetDlgItem(IDC_EDIT_R_SEX)->GetWindowText(strSex);
				req.nSex = atoi(strSex.GetBuffer(strSex.GetLength()));
			}
			else if ( idx == Req_Task )
			{
				req.eType = Req_Task;
				CString strTask;
				GetDlgItem(IDC_EDIT_R_TASKID)->GetWindowText(strTask);
				req.nTaskID = atoi(strTask.GetBuffer(strTask.GetLength()));
			}
			else if ( idx == Req_Level )
			{
				req.eType = Req_Level;
				CString strMin;
				CString strMax;
				GetDlgItem(IDC_EDIT_R_MIN)->GetWindowText(strMin);
				GetDlgItem(IDC_EDIT_R_MAX)->GetWindowText(strMax);
				req.fMin = atof(strMin.GetBuffer(strMin.GetLength()));
				req.fMax = atof(strMax.GetBuffer(strMax.GetLength()));

			}

			//if( ((CButton*)GetDlgItem(IDC_CHECK_NEED))->GetCheck() == 1 )
			//{
			//	act->vecMustTerm.push_back(req);
			//}
			//else
			//{
			//	act->vecProbilityTerm.push_back(req);
			//}

			RefreshNpcActionUI();
			if ( act )
			{
				ExpandNode((DWORD_PTR)act);
			}
		}
	}

}

void CNpcEditDlg::OnBnClickedBneventModify()
{
	// TODO: Add your control notification handler code here
	//事件修改
	HTREEITEM hItem = mEventActionTree.GetSelectedItem();
	CString  cItemText = mEventActionTree.GetItemText(hItem);

	if(!IsEventNode(cItemText))
	{
		::MessageBox(NULL,"请选择Event节点!","Warnning",MB_OK);
		return;
	}

	CComboBox* pBox = static_cast<CComboBox*>(GetDlgItem(IDC_COMETYPE));

	HTREEITEM hParent = mEventActionTree.GetParentItem(hItem); 
	Action* act = (Action*)mEventActionTree.GetItemData( hParent );

	if ( pBox && act )
	{
		int idx = pBox->GetCurSel() + 1;
		if ( idx == Event_Talk )
		{
			CString talk;
			GetDlgItem(IDC_EDIT_E_VALUE)->GetWindowText(talk);
			act->talk.nStringId = atoi(talk.GetBuffer(talk.GetLength()));
			CString dt;
			GetDlgItem(IDC_EDIT_E_DELAYTIME)->GetWindowText(dt);
			act->talk.nDelayTime = atoi(dt.GetBuffer(dt.GetLength()));
			CString prob;
			GetDlgItem(IDC_EDIT_E_PROB)->GetWindowText(prob);
			act->talk.nProbability = atoi(prob.GetBuffer(prob.GetLength()));
		}
		else if ( idx == Event_Anim )
		{
			CString aniType;
			GetDlgItem(IDC_EDIT_E_VALUE)->GetWindowText(aniType);
			act->anim.strType = std::string(aniType.GetBuffer(aniType.GetLength()));
			CString dt;
			GetDlgItem(IDC_EDIT_E_DELAYTIME)->GetWindowText(dt);
			act->anim.nDelayTime = atoi(dt.GetBuffer(dt.GetLength()));
			CString prob;
			GetDlgItem(IDC_EDIT_E_PROB)->GetWindowText(prob);
			act->anim.nProbability = atoi(prob.GetBuffer(prob.GetLength()));
		}
		else if ( idx == Event_AutoFace )
		{

			CString autoface;
			GetDlgItem(IDC_EDIT_E_VALUE)->GetWindowText(autoface);
			act->autoFace.bIsAutoFace = ( atoi(autoface.GetBuffer(autoface.GetLength())) == 0 ) ? false : true;
			CString dt;
			GetDlgItem(IDC_EDIT_E_DELAYTIME)->GetWindowText(dt);
			act->autoFace.nDelayTime = atoi(dt.GetBuffer(dt.GetLength()));
			CString prob;
			GetDlgItem(IDC_EDIT_E_PROB)->GetWindowText(prob);
			act->autoFace.nProbability = atoi(prob.GetBuffer(prob.GetLength()));
		}

		RefreshNpcActionUI();
		ExpandNode((DWORD_PTR)act);
	}

}

void CNpcEditDlg::OnBnClickedBtnFightUpdate()
{
	if(m_NpcID <= 0)
		return;

	// 得到相同Id的Npc
	NpcInfo::Npc *pNpc = theNpcInfo.GetNpcByStaticId(m_NpcID);

	if(NULL == pNpc)
	{
		MessageBox("Npc未找到!");
		return;
	}

	NpcInfo::Npc npc;
	if(GetNpcFightData(npc))
	{
		pNpc->fightData = npc.fightData;
		return;
	}
	else
	{

	}
}
