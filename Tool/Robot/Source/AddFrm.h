#pragma once
#include "afxwin.h"
#include "mapstatic.h"
#include "afxcmn.h"
#include "MeRTLibsServer.h"

struct Error_Log_
{
	int nBotID;
	string strAccount;
	int nMsgType;
	int nMsgFlag;
	int nMsgLength;
	string strInfo;
	string strFile;
};

// CAddFrm �Ի���

class CAddFrm : public CDialog
{
	DECLARE_DYNAMIC(CAddFrm)

public:
	CAddFrm(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CAddFrm();

// �Ի�������
	enum { IDD = IDD_ADD_FORM };

public:
	vector<Error_Log_> m_vecErrorLog;

public:
	void AddErrorLog(Error_Log_ &stErrorLog);
	void ShowerrorLog(Error_Log_ &stErrorLog);
	void ShowEdit(CEdit &xEdit, int nValue);
	void ReadAllScript();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL PreTranslateMessage(MSG* pMsg);

	DECLARE_MESSAGE_MAP()
    
public:
    virtual BOOL OnInitDialog();

    afx_msg void OnBnClickedButtonAdd(); // ��ӻ�����
    afx_msg void OnBnClickedButtonOpenErrorFile();
    afx_msg void OnCbnSelchangeComboSelectErrorLog();
    afx_msg void OnStnDblclickStaticPoint();
    afx_msg void OnCbnSelchangeComboType();
    afx_msg void OnBnClickedButtonEditArea();
    afx_msg void OnNMRclickListMapInfo(NMHDR *pNMHDR, LRESULT *pResult);
    afx_msg void OnDisperse();
    afx_msg void OnBnClickedBtnAttack();

    CComboBox m_cmbIDStart;
    CComboBox m_cmbBotType;
    CComboBox m_cmbBotNum;
    CEdit m_editTime;
    CEdit m_editMoveStep;
	CEdit m_TolalRototNumber;
	CEdit m_totalOnlineNum;
	MapStatic m_MapPoint;
	CStatic m_Map;
	CComboBox m_ComboError;
	CEdit m_BotID;
	CEdit m_MsgType;
	CEdit m_MsgFlag;
	CEdit m_MsgLength;
	CEdit m_ErrorInfo;
	CEdit m_ErrorFile;	
	CEdit m_Account;	
	CEdit m_Count;
	CEdit m_NotInGame;
	CEdit m_AttackCount;
	CEdit m_MoveCount;
	CListCtrl m_listMapDistributing;
	CComboBox m_comboMapList;
	CEdit m_editPosX;
	CEdit m_editPosY;
	CEdit m_editRadius;
	CComboBox m_comboAddSpace; // ���������ʱ����
	CComboBox m_comboPerCount;
	CEdit m_editFlySpace;
	CComboBox m_comboCount;
	CComboBox m_comboScript;
    afx_msg void OnPauseAddbot();
    bool bPause;
    //CEdit m_BotSpace;    // �����˼��
    afx_msg void OnPlaySkill();
    bool bPlaySkill;
    CEdit m_BotMoveRange;    // �ƶ�����
    CComboBox m_cmbSkillID;    // ѡ����ID
    //bool bChangeBotSpace;
    //afx_msg void OnChangeBotSpace();//�ı�����˼��
    bool bBotMove;
    int nMoveRange;
    afx_msg void OnBotMoveRange();
    bool bPlayAttack;
    afx_msg void OnBotAttack();
    bool bRide;
    afx_msg void OnBotRide();
    afx_msg void OnBnClickedReloadLuascript();
    CComboBox m_cmbLuaFile;    // LuaScript·��
};
