// ManInfo.cpp : implementation file
//

#include "stdafx.h"
#include "ManInfo.h"

#pragma warning( push, 0 )
#pragma warning( disable : 4201 )
// ManInfo dialog

IMPLEMENT_DYNAMIC(ManInfo, CDialog)

ManInfo::ManInfo(CWnd* pParent /*=NULL*/)
	: CDialog(ManInfo::IDD, pParent)
{

}

ManInfo::~ManInfo()
{
}

void ManInfo::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT1, m_editBotID);
	DDX_Control(pDX, IDC_EDIT2, m_editAccount);
	DDX_Control(pDX, IDC_EDIT3, m_editName);
	DDX_Control(pDX, IDC_EDIT4, m_editLevel);
	DDX_Control(pDX, IDC_EDIT6, m_editNameFlag);
	DDX_Control(pDX, IDC_EDIT7, m_editMap);
	DDX_Control(pDX, IDC_EDIT8, m_editPosX);
	DDX_Control(pDX, IDC_EDIT9, m_editPosY);
	DDX_Control(pDX, IDC_EDIT10, m_editNowHp);
	DDX_Control(pDX, IDC_EDIT11, m_editNowMp);
	DDX_Control(pDX, IDC_EDIT33, m_editMaxHp);
	DDX_Control(pDX, IDC_EDIT34, m_editMaxMp);
	DDX_Control(pDX, IDC_EDIT12, m_editPower);
	DDX_Control(pDX, IDC_EDIT13, m_editTenacity);
	DDX_Control(pDX, IDC_EDIT14, m_editStamina);
	DDX_Control(pDX, IDC_EDIT15, m_editIntelligence);
	DDX_Control(pDX, IDC_EDIT16, m_editSpirit);
	DDX_Control(pDX, IDC_EDIT17, m_editPhysicsAttack);	
	DDX_Control(pDX, IDC_EDIT18, m_editPhysicsDefend);
	DDX_Control(pDX, IDC_EDIT19, m_editPhysicsCritical);
	DDX_Control(pDX, IDC_EDIT20, m_editMagicAttack);
	DDX_Control(pDX, IDC_EDIT21, m_editMagicDefend);
	DDX_Control(pDX, IDC_EDIT22, m_editMagicCritical);
	DDX_Control(pDX, IDC_EDIT23, m_editPhysicsCriticalDefend);
	DDX_Control(pDX, IDC_EDIT24, m_editMagicCriticalDefend);
	DDX_Control(pDX, IDC_EDIT25, m_editFireAttack);
	DDX_Control(pDX, IDC_EDIT26, m_editFireDefend);
	DDX_Control(pDX, IDC_EDIT27, m_editIceAttack);
	DDX_Control(pDX, IDC_EDIT28, m_editIceDefend);
	DDX_Control(pDX, IDC_EDIT29, m_editPoisonAttack);
	DDX_Control(pDX, IDC_EDIT30, m_editPoisonDefend);
	DDX_Control(pDX, IDC_EDIT31, m_editThunderAttack);
	DDX_Control(pDX, IDC_EDIT32, m_editThunderDefend);
	//DDX_Control(pDX, IDC_EDIT36, m_editTotalMsgCount);
	//DDX_Control(pDX, IDC_EDIT37, m_editTotalPosPackCount);
	//DDX_Control(pDX, IDC_EDIT38, m_editTotalPosMsgCount);
	//DDX_Control(pDX, IDC_EDIT39, m_editTotalEnemyPackCount);
	//DDX_Control(pDX, IDC_EDIT41, m_editBotTotalMsgCount);
	//DDX_Control(pDX, IDC_EDIT42, m_editBotPosPackCount);
	//DDX_Control(pDX, IDC_EDIT43, m_editBotPosMsgCount);
	//DDX_Control(pDX, IDC_EDIT44, m_editBotEnemyPackCount);
	//DDX_Control(pDX, IDC_EDIT45, m_editBotEnemyMsgCount);
	//DDX_Control(pDX, IDC_EDIT40, m_editTotalEnemyMsgCount);
	DDX_Control(pDX, IDC_EDIT5, m_editProfession);
	DDX_Control(pDX, IDC_EDIT48, m_editAgility);
	DDX_Control(pDX, IDC_EDIT49, m_editLuck);
	DDX_Control(pDX, IDC_EDIT35, m_editMoveSpeed);
	DDX_Control(pDX, IDC_EDIT50, m_editAttackSpeed);
}


BEGIN_MESSAGE_MAP(ManInfo, CDialog)	
END_MESSAGE_MAP()


// ManInfo message handlers
BOOL ManInfo::PreTranslateMessage(MSG *pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		switch(pMsg->wParam)
		{
		case VK_RETURN:
		case VK_ESCAPE:
			return TRUE;
		}
	}

	return CDialog::PreTranslateMessage(pMsg);
}


void ManInfo::UpdateInformation( BaseRobot* pBot )
{
	if (pBot == NULL)
	{ return; }

	//////////////////////////////////////////////////////////////////////
	//theApp.SetEditText(m_editBotTotalMsgCount, "%d", pBot->m_nTotalMsgNum);
	//theApp.SetEditText(m_editBotPosPackCount, "%d", pBot->m_nTotalPosPack);
	//theApp.SetEditText(m_editBotPosMsgCount, "%d", pBot->m_nTotalPosMsg);
	//theApp.SetEditText(m_editBotEnemyPackCount, "%d", pBot->m_nTotalSightPack);
	//theApp.SetEditText(m_editBotEnemyMsgCount, "%d", pBot->m_nTotalSightMsg);

	//theApp.SetEditText(m_editTotalMsgCount, "%d", g_nTotalMsgNum);
	//theApp.SetEditText(m_editTotalPosPackCount, "%d", g_nTotalPosPack);
	//theApp.SetEditText(m_editTotalPosMsgCount, "%d", g_nTotalPosMsg);
	//theApp.SetEditText(m_editTotalEnemyPackCount, "%d", g_nTotalSightPack);
	//theApp.SetEditText(m_editTotalEnemyMsgCount, "%d", g_nTotalSightMsg);

	////////////////////////////////////////////////////////////////////////

	theApp.SetText(m_editBotID, "%d", pBot->GetBotID());	//id
	m_editAccount.SetWindowText(pBot->GetAccount());		//帐号	

	//不在游戏中 后面就不显示
	if (pBot->GetBotState() != State_Play)
	{
		m_editName.SetWindowText("");
		m_editLevel.SetWindowText("");
		m_editProfession.SetWindowText("");
		m_editMap.SetWindowText("");
		m_editPosX.SetWindowText("");
		m_editPosY.SetWindowText("");
		m_editNowHp.SetWindowText("");
		m_editMaxHp.SetWindowText("");
		m_editNowMp.SetWindowText("");
		m_editMaxMp.SetWindowText("");
		m_editPower.SetWindowText("");
		m_editTenacity.SetWindowText("");
		m_editStamina.SetWindowText("");
		m_editIntelligence.SetWindowText("");
		m_editSpirit.SetWindowText("");
		m_editAgility.SetWindowText("");
		m_editLuck.SetWindowText("");
		m_editPhysicsAttack.SetWindowText("");
		m_editPhysicsDefend.SetWindowText("");
		m_editPhysicsCritical.SetWindowText("");
		m_editMagicAttack.SetWindowText("");
		m_editMagicDefend.SetWindowText("");
		m_editMagicCritical.SetWindowText("");
		m_editPhysicsCriticalDefend.SetWindowText("");
		m_editMagicCriticalDefend.SetWindowText("");
		m_editIceAttack.SetWindowText("");
		m_editFireAttack.SetWindowText("");
		m_editThunderAttack.SetWindowText("");
		m_editPoisonAttack.SetWindowText("");
		m_editIceDefend.SetWindowText("");
		m_editFireDefend.SetWindowText("");
		m_editThunderDefend.SetWindowText("");
		m_editPoisonDefend.SetWindowText("");	

		return;
	}

	m_editName.SetWindowText(pBot->GetBotRoleName());		//名称	
	theApp.SetText(m_editLevel, "%d", pBot->m_CharInfo.baseinfo.liveinfo.ustLevel);		//等级

	//职业
	static char *s_pszProfession[] = {"戟", "剑", "枪", "舞", "刀",};
	static int nCount = sizeof(s_pszProfession) / sizeof(char*);
	int nIndex = pBot->m_CharInfo.baseinfo.aptotic.usProfession;
	if (nIndex > -1 && nIndex < nCount)
	{
		m_editProfession.SetWindowText(s_pszProfession[nIndex]);
	}

	//m_editNameFlag

	//地图
	m_editMap.SetWindowText( pBot->GetMapName() );

	//坐标
	theApp.SetText(m_editPosX, "%f", pBot->GetPosX());
	theApp.SetText(m_editPosY, "%f", pBot->GetPosY());

	//气血
	//theApp.SetText(m_editNowHp, "%d", pBot->m_CharInfo.baseinfo.TemporaryInfo.nHp);
	//theApp.SetText(m_editMaxHp, "%d", pBot->m_CharInfo.baseinfo.baseProperty.fight.iHpMax.final);

	//法力
	//theApp.SetText(m_editNowMp, "%d", pBot->m_CharInfo.baseinfo.TemporaryInfo.nMp);
	theApp.SetText(m_editMaxMp, "%d", pBot->m_CharInfo.baseinfo.baseProperty.fightAttr.mpMax.final);


	//一级属性
	static CEdit* s_pEdit[] = 
	{
		&m_editPower, &m_editTenacity, &m_editStamina, &m_editIntelligence, &m_editSpirit, &m_editAgility, &m_editLuck, 
	};
	static const int nAttrCount = sizeof(s_pEdit) / sizeof(CEdit*);
	for (int i = 0; i < nAttrCount; ++i)
	{
		theApp.SetText(*s_pEdit[i], "%f", pBot->GetBaseAttr().baseAttrValue[i].final );
	}

	//速度
	theApp.SetText(m_editMoveSpeed, "%f", pBot->GetFightAttr().moveSpeed.final );
	theApp.SetText(m_editAttackSpeed, "%d", pBot->GetFightAttr().attackSpeed.final);

	//攻
    theApp.SetText(m_editPhysicsAttack, "%f", pBot->GetFightAttr().attackPhysics.final);
	//theApp.SetText(m_editMagicAttack,   "%f", pBot->GetFightAttr().attackMagic.final);

    //防
    theApp.SetText(m_editPhysicsDefend, "%f", pBot->GetFightAttr().defendPhysics.final );
    theApp.SetText(m_editMagicDefend, "%f", pBot->GetFightAttr().defendMagic.final);

    //暴
    theApp.SetText(m_editPhysicsCritical, "%f", pBot->GetFightAttr().critical.final);
	theApp.SetText(m_editMagicCritical, "%f", pBot->GetFightAttr().critical.final);

    //暴抗
    theApp.SetText(m_editPhysicsCriticalDefend, "%f", pBot->GetFightAttr().criticalIntensity.final );
	theApp.SetText(m_editMagicCriticalDefend, "%f",   pBot->GetFightAttr().criticalIntensity.final );

	//元素属性
	static CEdit* s_pElementAttack[] = {&m_editIceAttack, &m_editFireAttack, &m_editThunderAttack, &m_editPoisonAttack, };
	static CEdit* s_pElementDefend[] = {&m_editIceDefend, &m_editFireDefend, &m_editThunderDefend, &m_editPoisonDefend, };

	static const int nElementCount = sizeof(s_pElementAttack) / sizeof(CEdit*);

	for (int i = 0; i < nElementCount; ++i)
	{
		//theApp.SetText(*s_pElementAttack[i], "%d", pBot->m_CharInfo.otherdataclient.elements[i].final_Att);
		//theApp.SetText(*s_pElementDefend[i], "%d", pBot->m_CharInfo.otherdataclient.elements[i].final_Def);
	}
}

#pragma warning( pop )
