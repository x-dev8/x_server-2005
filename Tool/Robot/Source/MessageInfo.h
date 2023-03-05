#pragma once
#include "../Resource/resource.h"
#include "afxwin.h"
#include "MsgStatistician.h"
#include "afxcmn.h"
#include "HistogramCtrl/HistogramCtrl.h"
// MessageInfo dialog

class MessageInfo : public CDialog
{
	DECLARE_DYNAMIC(MessageInfo)

public:
	MessageInfo(CWnd* pParent = NULL);   // standard constructor
	virtual ~MessageInfo();

// Dialog Data
	enum { IDD = IDD_DIALOG_MSGINFO };

public:
	void  InitInformation();	
	void  UpdataInformation( MsgStatistician &xMsgStatistican );
	void  UpdateConnectInfo(const char* ip, WORD port, int nState, DWORD dwError, bool bConnect);
	void  ShowAllMessageInformantion(map<DWORD, MsgStatistician::Msg_Info_> &mapMsgInfo, CListCtrl &xListCtrl, int64 dwMaxMsgCount);
	char* GetMessageType(DWORD dwType);
	int   GetShowType() { return m_nShowType; }
	void  SetBotID(int nBotID) { m_nBotID = nBotID;}
    void  UpdatePingChart(DWORD time);
    void  ResetChartMap();

private:
	bool m_bInit;

	bool m_bCreateMonster;											//���ƴ��������˵Ŀ��� luo.qin 3.18
	bool m_bChangeEquip;
	bool m_bRandRide;
	bool m_bCountryFight;

	int m_nShowType;
	int m_nBotID;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL PreTranslateMessage(MSG* pMsg);

    afx_msg void OnBnClickedRadioSingle();
    afx_msg void OnBnClickedRadioTotal();
    afx_msg void OnBnClickedButtonOpenFile();
    afx_msg void OnBnClickedButtonSaveLog();
	afx_msg void OnBnCreateMonster();								//��ʼ�������� luo.qin 3.18
	afx_msg void OnBnClickedChangeEquip();							//��ʼ��װ�� luo.qin 3.21
	afx_msg void OnBnClickedButtonRandride();						//��ʼ������� luo.qin 3.21
	afx_msg void OnPreparesuit();									//׼����װ luo.qin 4.2
	afx_msg void OnBnClickedButtonFight();							//��ʼ��ս luo.qin 4.2

protected:
	DECLARE_MESSAGE_MAP()

public:
	CEdit          m_editRunTime;
	CEdit          m_editUpdataCount;
	CEdit          m_editLoopCountPerSecond;
	CEdit          m_editSendCount;
	CEdit          m_editSendCountPerSecond;
	CEdit          m_editSendSizePerSecond;
	CEdit          m_editSendSize;
	CEdit          m_editRecvCount;
	CEdit          m_editRecvSize;
	CEdit          m_editRecvCountPerSecond;
	CEdit          m_editRecvSizePerSecond;
	CEdit          m_editMinSendCount;
	CEdit          m_editMaxSendCount;
	CEdit          m_editMinRecvCount;
	CEdit          m_editMaxRecvCount;
	CEdit          m_editMinSendSize;
	CEdit          m_editMaxSendSize;
	CEdit          m_editMinRecvSize;
	CEdit          m_editMaxRecvSize;
	CEdit		   m_editMonsterNum;
	CEdit		   m_editTotalMonsterNum;
    CEdit          m_editFile;
    CEdit          m_editState;
    CEdit          m_editIp;
	CListCtrl      m_listMinSend;
	CListCtrl      m_listMaxSend;
	CListCtrl      m_listMinRecv;
	CListCtrl      m_listMaxRecv;
	CListCtrl      m_listAllSendMsg;
	CListCtrl      m_listAllRecvMsg;		
	CButton        m_buttonLog;
	CButton		   m_buttonCreateMonster;
	CButton		   m_buttonChangeEquip;
	CButton		   m_buttonRandRide;
	CButton		   m_buttonCountryFight;
    CHistogramCtrl m_Histogram; //���������˵�Pingͼ��
};
