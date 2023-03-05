// NpcFileChange.cpp : implementation file
//

#include "stdafx.h"
#include "QuestEditor.h"
#include "NpcFileChange.h"
#include "NpcInfo.h"

#include "SlkReader.h"

// NpcFileChange dialog

IMPLEMENT_DYNAMIC(NpcFileChange, CDialog)

NpcFileChange::NpcFileChange(CWnd* pParent /*=NULL*/)
	: CDialog(NpcFileChange::IDD, pParent)
{

}

NpcFileChange::~NpcFileChange()
{
}

void NpcFileChange::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT10, m_editNpcSlk);
	DDX_Control(pDX, IDC_EDIT12, m_editNpcAction);
	DDX_Control(pDX, IDC_EDIT14,m_edotNpcSalute);
	DDX_Control(pDX, IDC_EDIT13, m_editNpcFight);
	DDX_Control(pDX, IDC_EDIT8, m_editNpcXml);
}


BEGIN_MESSAGE_MAP(NpcFileChange, CDialog)
	ON_BN_CLICKED(IDC_BUTTON19, &NpcFileChange::OnBnClickedButtonSlk)
	ON_BN_CLICKED(IDC_BUTTON20, &NpcFileChange::OnBnClickedButtonAction)
	ON_BN_CLICKED(IDC_BUTTON21, &NpcFileChange::OnBnClickedButtonFight)
	ON_BN_CLICKED(IDC_BUTTON22, &NpcFileChange::OnBnClickedButtonSalute)//����
	ON_BN_CLICKED(IDC_BUTTON18, &NpcFileChange::OnBnClickedButtonXml)
	ON_BN_CLICKED(IDOK2, &NpcFileChange::OnBnClickedOk)
END_MESSAGE_MAP()


// NpcFileChange message handlers

void NpcFileChange::OnBnClickedButtonSlk()
{
	// TODO: Add your control notification handler code here

	CFileDialog FileDlg(true, NULL, NULL, OFN_HIDEREADONLY, "Npc Slk(Npc.slk)|Npc.slk|");

	if (FileDlg.DoModal() == IDOK)
	{
		m_editNpcSlk.SetWindowText(FileDlg.GetPathName());		
	}

}

void NpcFileChange::OnBnClickedButtonAction()
{
	// TODO: Add your control notification handler code here

	CFileDialog FileDlg(true, NULL, NULL, OFN_HIDEREADONLY, "NpcAcion Slk(NpcAcion.slk)|NpcAcion.slk|");

	if (FileDlg.DoModal() == IDOK)
	{
		m_editNpcAction.SetWindowText(FileDlg.GetPathName());		
	}

}

void NpcFileChange::OnBnClickedButtonFight()
{
	// TODO: Add your control notification handler code here

	CFileDialog FileDlg(true, NULL, NULL, OFN_HIDEREADONLY, "NpcFight Slk(NpcFight.slk)|NpcFight.slk|");

	if (FileDlg.DoModal() == IDOK)
	{
		m_editNpcFight.SetWindowText(FileDlg.GetPathName());		
	}

}



void NpcFileChange::OnBnClickedButtonSalute()
{

	CFileDialog FileDlg(true, NULL, NULL, OFN_HIDEREADONLY, "NpcSalute Slk(NpcSalute.slk)|NpcSalute.slk|");

	if (FileDlg.DoModal() == IDOK)
	{
		m_edotNpcSalute.SetWindowText(FileDlg.GetPathName());		
	}
}

void NpcFileChange::OnBnClickedButtonXml()
{
	// TODO: Add your control notification handler code here


	CFileDialog FileDlg(true, NULL, NULL, OFN_HIDEREADONLY, "Npc Xml(Npc.xml)|Npc.xml| Npc.config");

	if (FileDlg.DoModal() == IDOK)
	{
		m_editNpcXml.SetWindowText(FileDlg.GetPathName());		
	}
}





void NpcFileChange::OnBnClickedOk()
{
	
	// TODO: Add your control notification handler code here

	CString strSlk = "";
	m_editNpcSlk.GetWindowText(strSlk);
	

	CString strXml = "";
	m_editNpcXml.GetWindowText(strXml);

	CString NpcActionSlk = "";
	m_editNpcAction.GetWindowText(NpcActionSlk);

	CString NpcSaluteSlk = "";
	m_edotNpcSalute.GetWindowText(NpcSaluteSlk);

	CString NpcFightSlk = "";
	m_editNpcFight.GetWindowText(NpcFightSlk);

	if (strSlk.IsEmpty() || strXml.IsEmpty() || NpcActionSlk.IsEmpty() || NpcSaluteSlk.IsEmpty() || NpcFightSlk.IsEmpty())
	{
		MessageBox("����ûѡ����ļ���");
		return;
	}

    //MessageBox("Npc.config���ڵ�ͼ�༭���б༭��");
	if (LoadFromSlk(strSlk.GetBuffer()))
	{
		if (LoadNpcActionSlk(NpcActionSlk.GetBuffer()))
		{
			if (LoadNpcSaluteSlk(NpcSaluteSlk.GetBuffer()))
			{
				if (LoadNpcFightSlk(NpcFightSlk.GetBuffer()))
				{
					if (theNpcInfo.SaveNpcConfig(strXml.GetBuffer()) == File_Success)
					{
						AfxMessageBox("ת���ɹ���");
					}
					else
					{
						AfxMessageBox("ת��ʧ�ܣ�");
					}
				}
				else
				{
					MessageBox("Load:NpcFightSlk����");
					return;
				}
			}
			else
			{
				MessageBox("Load:NpcSaluteSlk����");
				return;
			}
			
		}
		else
		{
			MessageBox("Load:NpcActionSlk����");
			return;
		}
	/*	if (theNpcInfo.SaveNpcConfig(strXml.GetBuffer()) == File_Success)
		{
			AfxMessageBox("ת���ɹ���");
		}*/

	}
	else
	{
		MessageBox("Load:NpcSlk����");
		return;
	}
}


bool NpcFileChange::LoadFromSlk( char* szFileName)
{
	CSlkReader reader;
	int iRet = 0;
	int iRow = 3;

	//theNpcInfo.npcs_.clear();

	if( !reader.ReadFromFile( szFileName ) )
		return false;

	std::string strFileName;
	std::string strNpcName, strImgPath;
	std::string strTitle = "";
	std::string strPinyin = "";
	std::string strNpcTips="";
	int			nNpcId = -1;
	int			nLevel = 1;
	int			nModelId = 0;
	int			nMapId = 0;
	float		fX,fY,fZ = 0.0f;
	float		fDir = 0;
	int			nWalkPath;
	int			nChangeDir, nShadow,WorldShow,IsDynamicCollision ,country,nTaskMenu,phyle= 0;
	int			nNpcType = 0;
	INT			nMask = 0;
	float		fBodyScale = 0.0f;
	std::string action_lua = "";
	std::string strSoundPath = "";
	int			ngutUIOffsetX = 0;
	int			ngutUIOffsetY = 0;
	float       fgutUIScale = 0;
	
	int			nActionDataid = 0;
	int			ntime = 0;
	int			nNextId = 0;
	std::string strActionName = "";
	int         nActionProbability = 0;
	int			nTalkStringid = 0;
	int			nTalkshProbability = 0;
	

	theNpcInfo.npcs_.clear();


	while ( CSlkReader::ret_readover != ( iRet = reader.GotoNextLine( iRow++ ) ) ) 
	{
		if( CSlkReader::ret_nothisline == iRet )
			continue;
		if( !reader.GetIntFieldByName( "Id", nNpcId ) )
		{
			return false;
		}

		if( !reader.GetStringFieldByName( "Name", strNpcName ) )
		{
			return false;
		}

		if( !reader.GetStringFieldByName( "PinYin", strPinyin ) )
		{
			return false;
		}

		if( !reader.GetIntFieldByName( "Level", nLevel ) )
		{
			return false;
		}

		if( !reader.GetIntFieldByName( "ModelId", nModelId ) )
		{
			nModelId = -1;
		}

		if( !reader.GetIntFieldByName( "MapId", nMapId ) )
		{
			return false;
		}

		if( !reader.GetFloatFieldByName( "PositionX", fX ) )
		{
			return false;
		}

		if( !reader.GetFloatFieldByName( "PositionY", fY ) )
		{
			return false;
		}
		if( !reader.GetFloatFieldByName( "PositionZ", fZ ) )
		{
			return false;
		}

		if( !reader.GetFloatFieldByName( "Direction", fDir ) )
		{
			return false;
		}

		if( !reader.GetIntFieldByName( "CanChangeDirection", nChangeDir ) )
		{
			return false;
		}

		if( !reader.GetIntFieldByName( "IsMiniShow", nShadow ) )
		{
			nShadow = -1;
		}

		if( !reader.GetIntFieldByName( "IsWorldShow", WorldShow ) )
		{
			WorldShow = -1;
		}

		if( !reader.GetIntFieldByName( "IsDynamicCollision", IsDynamicCollision ) )
		{
			IsDynamicCollision = -1;
		}

		if( !reader.GetIntFieldByName( "Type", nNpcType ) )
		{
			return false;
		}

		if ( !reader.GetIntFieldByName( "MovePath", nWalkPath) )
		{
			nWalkPath = -1 ;
		}

		if( !reader.GetStringFieldByName( "ScriptFile", strFileName ) )
		{
			strFileName = "";
		}

		if( !reader.GetStringFieldByName( "actionScript", action_lua ) )
		{
			action_lua = "";
		}

		if( !reader.GetStringFieldByName( "HeadPicture", strImgPath ) )
		{
			strImgPath = "";
		}

		if( !reader.GetStringFieldByName( "Title", strTitle ) )
		{
			strTitle = "";
		}

		if( !reader.GetStringFieldByName( "NpcTips", strNpcTips ) )
		{
			strNpcTips = "";
		}

		if( !reader.GetIntFieldByName( "IsCollision", nMask ) )
		{
			nMask = 0;
		}

		if( !reader.GetFloatFieldByName( "BodyScale", fBodyScale ) )
		{
			fBodyScale = 0.0f;
		}

		if( !reader.GetIntFieldByName( "Country", country ) )
		{
			country = 0;
		}

		if( !reader.GetIntFieldByName( "phyle", phyle ) )
		{
			phyle = 0;
		}

		if( !reader.GetIntFieldByName( "MenuId", nTaskMenu ) )
		{
			nTaskMenu = 0;
		}

		if( !reader.GetStringFieldByName( "SoundPath", strSoundPath ) )
		{
			strSoundPath = "";
		}

		if (!reader.GetFloatFieldByName("GutUIScale",fgutUIScale))
		{
			return false;
		}
		
		if( !reader.GetIntFieldByName( "GutUIOffsetX", ngutUIOffsetX ) )
		{
			return false;
		}

		if( !reader.GetIntFieldByName( "GutUIOffsetY", ngutUIOffsetY ) )
		{
			return false;
		}

	

		//if (!reader.GetIntFieldByName("ActionDataid",nActionDataid))
		//{
		//	return false;
		//}

		//if (!reader.GetIntFieldByName("time",ntime))
		//{
		//	return false;
		//}

		//if (!reader.GetIntFieldByName("NextId",nNextId))
		//{
		//	return false;
		//}

		//if (!reader.GetStringFieldByName("ActionName",strActionName))
		//{
		//	return false;
		//}

		//if (!reader.GetIntFieldByName("ActionProbability",nActionProbability))
		//{
		//	return false;
		//}

		//if (!reader.GetIntFieldByName("TalkStringid",nTalkStringid))
		//{
		//	return false;
		//}

		//if (!reader.GetIntFieldByName("TalkshProbability",nTalkshProbability))
		//{
		//	return false;
		//}


		NpcInfo::Npc stNpc;
		stNpc.id			= nNpcId;
		stNpc.name		= strNpcName;
		stNpc.pinyin		= strPinyin;
		stNpc.mapId		= nMapId;
		stNpc.level		= nLevel;
		stNpc.type		= nNpcType;
		stNpc.modelId		= nModelId;		
		stNpc.x			= fX;
		stNpc.y			= fY;
		stNpc.z			= fZ;
		stNpc.movePath = nWalkPath;
		stNpc.direction			= fDir;
		stNpc.canChangeDirection	= nChangeDir;
		stNpc.isMiniShow		= nShadow;
		stNpc.isDynamicCollision		= IsDynamicCollision;
		stNpc.isWorldShow		= WorldShow;
		stNpc.triggerScript	= strFileName;
		stNpc.actionScript	= action_lua;

		stNpc.isCollision = nMask;
		stNpc.title = strTitle;
		stNpc.tip = strNpcTips;
		stNpc.strHeadPicture = strImgPath;
		stNpc.bodyScale = fBodyScale;
		stNpc.uchCountryID = country;
		stNpc.phyle = phyle;
		stNpc.nTaskMenu = nTaskMenu;
		stNpc.strSoundPath = strSoundPath;

		stNpc.gutUIScale = fgutUIScale;
		stNpc.gutUIOffsetX = ngutUIOffsetX;
		stNpc.gutUIOffsetY = ngutUIOffsetY;

	/*	stNpc.ActionDataid = nActionDataid;
		stNpc.npctime = ntime;
		stNpc.NextId = nNpcId;
		stNpc.ActionName = strActionName;
		stNpc.ActionProbability = nActionProbability;
		stNpc.TalkStringid = nTalkStringid;
		stNpc.TalkshProbability = nTalkshProbability;*/
		theNpcInfo.AddNpc(stNpc);
	}



	return true;
}

bool NpcFileChange::LoadNpcActionSlk( char* szFileName )
{
	CSlkReader reader;
	int iRet = 0;
	int iRow = 3;
	if( !reader.ReadFromFile( szFileName ) )
		return false;

	int nNpcID = 0;
	int nCycleId = 0;
	int ntime = 0;
	int nNextID = 0;
	std::string strActionName = "NULL";
	int nActionProbability = 0;
	int nTalkStringid = 0;
	int nTalkshProbability = 0;

	while(CSlkReader::ret_readover != (iRet = reader.GotoNextLine(iRow++)))
	{
		if (CSlkReader::ret_nothisline == iRet)
		{
			continue;
		}

		if (!reader.GetIntFieldByName("npcid",nNpcID))
		{
			return false;
		}
			
		if (!reader.GetIntFieldByName("Id",nCycleId))
		{
			return false;
		}

		if (!reader.GetIntFieldByName("time",ntime))
		{
			return false;
		}

		if (!reader.GetIntFieldByName("NextTimeId",nNextID))
		{
			return false;
		}

		if (!reader.GetStringFieldByName("Name",strActionName))
		{
			return false;
		}

		if (!reader.GetIntFieldByName("Probability",nActionProbability))
		{
			return false;
		}

		if (!reader.GetIntFieldByName("Stringid",nTalkStringid))
		{
			return false;
		}

		if (!reader.GetIntFieldByName("Probability",nTalkshProbability))
		{
			return false;
		}

		NpcInfo::ActionData ac;
		ac.strAnimName = strActionName;
		ac.shProbability = nActionProbability;

		NpcInfo::TalkData Shuohua;
		Shuohua.shStringId = nTalkStringid;
		Shuohua.shProbability = nTalkshProbability;
		
		NpcInfo::NpcsIter finder = theNpcInfo.npcs_.find(nNpcID);
		if (finder != theNpcInfo.npcs_.end())
		{
			NpcInfo::NpcActionData actionData;
			actionData.shId = nNpcID ;
			actionData.CycleId = nCycleId;
			actionData.shElapseTime = ntime;
			actionData.shNextId = nNextID;         // ��ɺ��¸�NpcActionData��ӦshId
			actionData.vctActions.push_back(ac);
			actionData.vctTalks.push_back(Shuohua);

			finder->second.vctActionData.push_back(actionData);
		}
	}

	return true;
}



bool NpcFileChange::LoadNpcSaluteSlk(char* szFileName)
{
	CSlkReader reader;
	int iRet = 0;
	int iRow = 3;
	if( !reader.ReadFromFile( szFileName ) )
		return false;

	int nNpcID = 0;
	int nType1 = 0;
	int nMin   = 0;
    int nMax   = 0;
	int nNeed  = 0;
	int nType2 = 0;
	std::string strName = "";
	int nProbability = 0;
	int nDelayTime = 0;
	int nView  = 0;

	while(CSlkReader::ret_readover != (iRet = reader.GotoNextLine(iRow++)))
	{
		if (CSlkReader::ret_nothisline == iRet)
		{
			continue;
		}

		if (!reader.GetIntFieldByName("npcid",nNpcID))
		{
			return false;
		}

		if (!reader.GetIntFieldByName("Type1",nType1))
		{
			return false;
		}

		if (!reader.GetIntFieldByName("Min",nMin))
		{
			return false;
		}

		if (!reader.GetIntFieldByName("Max",nMax))
		{
			return false;
		}

		if (!reader.GetIntFieldByName("Need",nNeed))
		{
			return false;
		}

		if (!reader.GetIntFieldByName("Type2",nType2))
		{
			return false;
		}

		if (!reader.GetStringFieldByName("Name",strName))
		{
			return false;
		}

		if (!reader.GetIntFieldByName("Probability",nProbability))
		{
			return false;
		}

		if (!reader.GetIntFieldByName("DelayTime",nDelayTime))
		{
			return false;
		}

		if (!reader.GetIntFieldByName("View",nView))
		{
			return false;
		}
		
		NpcInfo::NpcsIter finder = theNpcInfo.npcs_.find(nNpcID);
		if (finder != theNpcInfo.npcs_.end())
		{
			NpcInfo::SaluteData salutedata;
			salutedata.shId = nNpcID;
			salutedata.shType1 = nType1;
			salutedata.shMin = nMin;
			salutedata.shMax = nMax;
			salutedata.shNeed = nNeed;
			salutedata.shType2 = nType2;
			salutedata.strSaluteName = strName;
			salutedata.shProbability = nProbability;
			salutedata.shDelayTime = nDelayTime;
			salutedata.shView = nView;
			finder->second.vctSaluteData.push_back(salutedata);

		}

	}

	return true;
}

bool NpcFileChange::LoadNpcFightSlk( char* szFileName )
{
	CSlkReader reader;
	int iRet = 0;
	int iRow = 3;
	if( !reader.ReadFromFile( szFileName ) )
		return false;

	int			nNpcId = 0;
	float       bodyLength = 0.0f           ; // �������ʹ�С
	int			level = 0                 ; // ����
	//////////////////////////////////////////////////////////////////////////
	// ����ս������
	int         hpMax = 0               ; // HP����
	int         mpMax = 0               ; // MP����
	float       attackPhysics = 0.0f       ; // ��������
	float       attackMagic = 0.0f          ; // ħ�������� 
	float       defendPhysics = 0.0f        ; // �������
	float       defendMagic = 0.0f          ; // ħ������
	float       attackSpeed = 0.0f          ; // �����ٶ�
	float       moveSpeed = 0.0f            ; // �ƶ��ٶ�
	float       hpRestore = 0.0f            ; // HP�ָ�
	float       mpRestore = 0.0f            ; // MP�ָ�
	int       exact = 0                ; // ������
	int       dodge = 0                ; // ������
	int       critical = 0             ; // ������
	int       tenacity = 0             ; // ����
	int       criticalIntensity = 0    ; // �����˺�
	int       backStrike = 0           ; // �����˺�
	int       backStrikeResist = 0     ; // ��������
	int       breakStrike = 0          ; // �Ƽ��˺�
	int       stabStrike = 0           ; // �ᴩ�˺�
	int       elementStrike = 0        ; // Ԫ���˺�
	int       toxinStrike = 0          ; // �����˺�
	int       spiritStrike = 0         ; // �����˺�
	int       breakResist = 0          ; // �Ƽ׿���
	int       stabResist = 0           ; // �ᴩ����
	int       elementResist = 0        ; // Ԫ�ؿ���
	int       toxinResist = 0          ; // ���ؿ���
	int       spiritResist = 0         ; // ������
	//////////////////////////////////////////////////////////////////////////
	int      normalAttackMin = 0       ; // ��ͨ������Сϵ��
	int      normalAttackMax = 0       ; // ��ͨ�������ϵ��
	int       view = 0                  ; // ��Ұ
	int       fightView = 0             ; // ս����Ұ
	int      catchTime = 0             ; // ׷��ʱ��
	float       moveStep = 0.0f              ; // �ܲ�����
	float       idleMoveSpeed = 0.0f         ; // ����ʱ�ƶ��ٶ�
	float       idleMoveStep = 0.0f          ; // ���߲���
	int         reliveTime = 0            ; // ����ʱ��
	std::string deadScript            ; // ���������ű���ַ
	int        isInitiative = 0          ; // �Ƿ�������
	int      disappearTime = 0         ; // ��ʧʱ��
	int         enmityDecRate = 0         ; // ���˥������
	int         enmityView = 0            ; // ���
	int         maxRange = 0              ; // �����Χ
	int         changePassive = 0         ; // ս��ʱ�Ƿ��Ϊ������
	int         passiveTime = 0           ; // ��������ʱ��
	int         baseEnmityRange = 0       ; // ������ޱ�������
	int      integral = 0              ; // ����
	int      routeId = 0               ; // ·��Id
	int		 skillId1 = 0				;//����
	int		 skillLevel1 = 0			;
	int		 skillRate1 = 0				;
	int		 skillId2 = 0				;//����
	int		 skillLevel2 = 0			;
	int		 skillRate2 = 0				;
	int		 skillId3 = 0				;//����
	int		 skillLevel3 = 0			;
	int		 skillRate3 = 0				;
	int		 fightType					; // ����Ŀ�����ͣ�0 ֻ���ˣ� 1 ������֣����������ˣ� 2 ����
	int		 fightCamp					; // ��Ӫ

	while(CSlkReader::ret_readover != (iRet = reader.GotoNextLine(iRow++)))
	{
		if (CSlkReader::ret_nothisline == iRet)
		{
			continue;
		}

		if (!reader.GetIntFieldByName("Id",nNpcId))
		{
			return false;
		}

		if (!reader.GetFloatFieldByName("BodyLength",bodyLength))
		{
			bodyLength = 0.0f;
		}

		if (!reader.GetIntFieldByName("Level",level))
		{
			level = 0;
		}

		if (!reader.GetIntFieldByName("HpMax",hpMax))
		{
			hpMax = 0;
		}

		if (!reader.GetIntFieldByName("MpMax",mpMax))
		{
			mpMax = 0;
		}

		if (!reader.GetFloatFieldByName("PhyAttack",attackPhysics))
		{
			attackPhysics = 0.0f;
		}

		if (!reader.GetFloatFieldByName("MagAttack",attackMagic))
		{
			attackMagic = 0.0f;
		}

		if (!reader.GetFloatFieldByName("DefnedPhysics",defendPhysics))
		{
			defendPhysics = 0.0f;
		}

		if (!reader.GetFloatFieldByName("DefnedMagic",defendMagic))
		{
			defendMagic = 0.0f;
		}

		if (!reader.GetFloatFieldByName("AttackSpeed",attackSpeed))
		{
			attackSpeed = 0.0f;
		}

		if (!reader.GetFloatFieldByName("MoveSpeed",moveSpeed))
		{
			moveSpeed = 0.0f;
		}

		if (!reader.GetFloatFieldByName("HpRestore",hpRestore))
		{
			hpRestore = 0.0f;
		}

		if (!reader.GetFloatFieldByName("MpRestore",mpRestore))
		{
			mpRestore = 0.0f;
		}

		if (!reader.GetIntFieldByName("Exact",exact))
		{
			exact = 0;
		}

		if (!reader.GetIntFieldByName("Dodge",dodge))
		{
			dodge = 0;
		}

		if (!reader.GetIntFieldByName("Critical",critical))
		{
			critical = 0;
		}

		if (!reader.GetIntFieldByName("Tenacity",tenacity))
		{
			tenacity = 0;
		}

		if (!reader.GetIntFieldByName("CriticalIntensity",criticalIntensity))
		{
			criticalIntensity = 0;
		}

		if (!reader.GetIntFieldByName("BackStrike",backStrike))
		{
			backStrike = 0;
		}

		if (!reader.GetIntFieldByName("BackStrikeResist",backStrikeResist))
		{
			backStrikeResist = 0;
		}

		if (!reader.GetIntFieldByName("BreakStrike",breakStrike))
		{
			breakStrike = 0;
		}

		if (!reader.GetIntFieldByName("StabStrike",stabStrike))
		{
			stabStrike = 0;
		}

		if (!reader.GetIntFieldByName("ElementStrike",elementStrike))
		{
			elementStrike = 0;
		}

		if (!reader.GetIntFieldByName("ToxinStrike",toxinStrike))
		{
			toxinStrike = 0;
		}

		if (!reader.GetIntFieldByName("SpiritStrike",spiritStrike))
		{
			spiritStrike = 0;
		}

		if (!reader.GetIntFieldByName("BreakResist",breakResist))
		{
			breakResist = 0;
		}

		if (!reader.GetIntFieldByName("StabResist",stabResist))
		{
			stabResist = 0;
		}

		if (!reader.GetIntFieldByName("ElementResist",elementResist))
		{
			elementResist = 0;
		}

		if (!reader.GetIntFieldByName("ToxinResist",toxinResist))
		{
			toxinResist = 0;
		}

		if (!reader.GetIntFieldByName("SpiritResist",spiritResist))
		{
			spiritResist = 0;
		}

		if (!reader.GetIntFieldByName("NormalAttackMin",normalAttackMin))
		{
			normalAttackMin = 0;
		}

		if (!reader.GetIntFieldByName("NormalAttackMax",normalAttackMax))
		{
			normalAttackMax = 0;
		}

		if (!reader.GetIntFieldByName("View",view))
		{
			view = 0;
		}

		if (!reader.GetIntFieldByName("FightView",fightView))
		{
			fightView = 0;
		}

		if (!reader.GetIntFieldByName("CatchTime",catchTime))
		{
			catchTime = 0;
		}

		if (!reader.GetFloatFieldByName("MoveStep",moveStep))
		{
			moveStep = 0.0f;
		}

		if (!reader.GetFloatFieldByName("IdleMoveSpeed",idleMoveSpeed))
		{
			idleMoveSpeed = 0.0f;
		}

		if (!reader.GetFloatFieldByName("IdleMoveStep",idleMoveStep))
		{
			idleMoveStep = 0.0f;
		}

		if (!reader.GetIntFieldByName("ReliveTime",reliveTime))
		{
			reliveTime = 0;
		}

		if (!reader.GetStringFieldByName("DeadScript",deadScript))
		{
			deadScript = "";
		}

		if (!reader.GetIntFieldByName("IsInitiative",isInitiative))
		{
			isInitiative = 0;
		}

		if (!reader.GetIntFieldByName("DisappearTime",disappearTime))
		{
			disappearTime = 0;
		}

		if (!reader.GetIntFieldByName("EnmityDecRate",enmityDecRate))
		{
			enmityDecRate = 0;
		}

		if (!reader.GetIntFieldByName("EnmityView",enmityView))
		{
			enmityView = 0;
		}

		if (!reader.GetIntFieldByName("MaxRange",maxRange))
		{
			maxRange = 0;
		}

		if (!reader.GetIntFieldByName("ChangePassive",changePassive))
		{
			changePassive = 0;
		}

		if (!reader.GetIntFieldByName("PassiveTime",passiveTime))
		{
			passiveTime = 0;
		}

		if (!reader.GetIntFieldByName("BaseEnmityRange",baseEnmityRange))
		{
			baseEnmityRange = 0;
		}

		if (!reader.GetIntFieldByName("Intergal",integral))
		{
			integral = 0;
		}

		if (!reader.GetIntFieldByName("RouteId",routeId))
		{
			routeId = 0;
		}

		if (!reader.GetIntFieldByName("Skill1Id",skillId1))
		{
			skillId1 = 0;
		}

		if (!reader.GetIntFieldByName("Skill1Level",skillLevel1))
		{
			skillLevel1 = 0;
		}

		if (!reader.GetIntFieldByName("Skill1Rate",skillRate1))
		{
			skillRate1 = 0;
		}

		if (!reader.GetIntFieldByName("Skill2Id",skillId2))
		{
			skillId2 = 0;
		}

		if (!reader.GetIntFieldByName("Skill2Level",skillLevel2))
		{
			skillLevel2 = 0;
		}

		if (!reader.GetIntFieldByName("Skill2Rate",skillRate2))
		{
			skillRate2 = 0;
		}

		if (!reader.GetIntFieldByName("Skill3Id",skillId3))
		{
			skillId3 = 0;
		}

		if (!reader.GetIntFieldByName("Skill3Level",skillLevel3))
		{
			skillLevel3 = 0;
		}

		if (!reader.GetIntFieldByName("Skill3Rate",skillRate3))
		{
			skillRate3 = 0;
		}

		if (!reader.GetIntFieldByName("FightType", fightType))
		{
			fightType = 0;
		}

		if (!reader.GetIntFieldByName("FightCamp", fightCamp))
		{
			fightCamp = 0;
		}

		NpcInfo::NpcsIter finder = theNpcInfo.npcs_.find(nNpcId);
		if (finder != theNpcInfo.npcs_.end())
		{
			NpcInfo::FightInfo fightInfo;
			fightInfo.npcId = nNpcId;

			fightInfo.bodyLength = bodyLength;
			fightInfo.level = level;
			fightInfo.hpMax = hpMax;
			fightInfo.mpMax = mpMax;
			fightInfo.attackPhysics = attackPhysics;

			fightInfo.attackMagic = attackMagic;
			fightInfo.defendPhysics = defendPhysics;
			fightInfo.defendMagic = defendMagic;
			fightInfo.attackSpeed = attackSpeed;
			fightInfo.moveSpeed = moveSpeed;

			fightInfo.hpRestore = hpRestore;
			fightInfo.mpRestore = mpRestore;
			fightInfo.exact = exact;
			fightInfo.dodge = dodge;
			fightInfo.critical = critical;

			fightInfo.tenacity = tenacity;
			fightInfo.criticalIntensity = criticalIntensity;
			fightInfo.backStrike = backStrike;
			fightInfo.backStrikeResist = backStrikeResist;
			fightInfo.breakStrike = breakStrike;

			fightInfo.stabStrike = stabStrike;
			fightInfo.elementStrike = elementStrike;
			fightInfo.toxinStrike = toxinStrike;
			fightInfo.spiritStrike = spiritStrike;
			fightInfo.breakResist = breakResist;

			fightInfo.stabResist = stabResist;
			fightInfo.elementResist = elementResist;
			fightInfo.toxinResist = toxinResist;
			fightInfo.spiritResist = spiritResist;
			fightInfo.normalAttackMin = normalAttackMin;

			fightInfo.normalAttackMax = normalAttackMax;
			fightInfo.view = view;
			fightInfo.fightView = fightView;
			fightInfo.catchTime = catchTime;
			fightInfo.moveStep = moveStep;

			fightInfo.idleMoveSpeed = idleMoveSpeed;
			fightInfo.idleMoveStep = idleMoveStep;
			fightInfo.reliveTime = reliveTime;
			fightInfo.deadScript = deadScript;
			fightInfo.isInitiative = isInitiative;

			fightInfo.disappearTime = disappearTime;
			fightInfo.enmityDecRate = enmityDecRate;
			fightInfo.enmityView = enmityView;
			fightInfo.maxRange = maxRange;
			fightInfo.changePassive = changePassive;

			fightInfo.passiveTime = passiveTime;
			fightInfo.baseEnmityRange = baseEnmityRange;
			fightInfo.integral = integral;
			fightInfo.routeId = routeId;
			fightInfo.skills[0].skillId = skillId1;

			fightInfo.skills[0].skillLevel = skillLevel1;
			fightInfo.skills[0].skillRate = skillRate1;
			fightInfo.skills[1].skillId = skillId2;
			fightInfo.skills[1].skillLevel = skillLevel2;
			fightInfo.skills[1].skillRate = skillRate2;

			fightInfo.skills[2].skillId = skillId3;
			fightInfo.skills[2].skillLevel = skillLevel3;
			fightInfo.skills[2].skillRate = skillRate3;

			fightInfo.fightType = fightType;
			fightInfo.fightCamp = fightCamp;

			finder->second.fightData.push_back(fightInfo);
		}

	}

	return true;
}