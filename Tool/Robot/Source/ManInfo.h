#pragma once
#include "../Resource/resource.h"
#include "BaseInfo.h"
#include "afxwin.h"

// ManInfo dialog
class ManInfo : public CDialog, public BaseInfo
{
	DECLARE_DYNAMIC(ManInfo)

public:
	ManInfo(CWnd* pParent = NULL);   // standard constructor
	virtual ~ManInfo();

// Dialog Data
	enum { IDD = IDD_DIALOG_MANINFO };

public:
	//virtual void InitInformation();
	virtual void UpdateInformation(BaseRobot *pBot);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
public:
	CEdit m_editBotID;
	CEdit m_editAccount;
	CEdit m_editName;
	CEdit m_editLevel;
	CEdit m_editNameFlag;
	CEdit m_editMap;
	CEdit m_editPosX;
	CEdit m_editPosY;
	CEdit m_editNowHp;
	CEdit m_editNowMp;
	CEdit m_editMaxHp;
	CEdit m_editMaxMp;
	CEdit m_editPower;
	CEdit m_editTenacity;
	CEdit m_editStamina;
	CEdit m_editIntelligence;
	CEdit m_editSpirit;
	CEdit m_editPhysicsAttack;
	CEdit m_editPhysicsDefend;
	CEdit m_editPhysicsCritical;
	CEdit m_editMagicAttack;
	CEdit m_editMagicDefend;
	CEdit m_editMagicCritical;
	CEdit m_editPhysicsCriticalDefend;
	CEdit m_editMagicCriticalDefend;
	CEdit m_editFireAttack;
	CEdit m_editFireDefend;
	CEdit m_editIceAttack;
	CEdit m_editIceDefend;
	CEdit m_editPoisonAttack;
	CEdit m_editPoisonDefend;
	CEdit m_editThunderAttack;
	CEdit m_editThunderDefend;	
	CEdit m_editProfession;
	CEdit m_editAgility;
	CEdit m_editLuck;
	CEdit m_editMoveSpeed;
	CEdit m_editAttackSpeed;


	//CEdit m_editTotalMsgCount;
	//CEdit m_editTotalPosPackCount;
	//CEdit m_editTotalPosMsgCount;
	//CEdit m_editTotalEnemyPackCount;
	//CEdit m_editBotTotalMsgCount;
	//CEdit m_editBotPosPackCount;
	//CEdit m_editBotPosMsgCount;
	//CEdit m_editBotEnemyPackCount;
	//CEdit m_editBotEnemyMsgCount;
	//CEdit m_editTotalEnemyMsgCount;
};
