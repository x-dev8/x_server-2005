/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\����\Tip.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UIBase.h"

#ifndef ID_FRAME_Tip
#define ID_FRAME_Tip		"ID_FRAME_Tip"
#endif  ID_FRAME_Tip
#ifndef ID_TEXT_SmallTip
#define ID_TEXT_SmallTip		"ID_TEXT_SmallTip"
#endif  ID_TEXT_SmallTip

class CUI_ID_FRAME_Tip : public CUIBase
{
public:
    struct TipEntrance
    {
        TipEntrance()
        {
            nCurrentId = -1;
            nBeginId = -1;
            dwBeginTime = 0;
            dwLastTime = 0;
            dwNextTime = 0;
            nLoopCount = 0;
            nLoopRemain = 0;
            bBegin = false;
            bShow = false;
        }
        int     nBeginId;               // ���߿�ʼ��Tip Id (����)
        int     nCurrentId;             // ���ߵ�ǰ��ʾ��Id
        int     nLastId;                // ��������Tip Id
        DWORD   dwBeginTime;            // ����Tip��ʼʱ�� (����)
        DWORD   dwLastTime;             // ����Tip��ʾʱ��
        DWORD   dwNextTime;             // ������Tip����ʱ��
        int     nLoopCount;             // ����Tipѭ������ (����)
        int     nLoopRemain;            // ʣ��ѭ������
        bool    bBegin;                 // �����Ƿ��ѿ�ʼ
        bool    bShow;                  // ����Tip�Ƿ�����ʾ״̬
    };
    
    struct Tip
    {
        Tip()
        {
            nDisplayType = -1;
            dwIntervalTime = 0;
            nStringId = -1;
            nNextTipId = -1;
        }
        void operator = ( const Tip& tip )
        {
            nDisplayType = tip.nDisplayType;
            dwIntervalTime = tip.dwIntervalTime;
            nStringId = tip.nStringId;
            nNextTipId = tip.nNextTipId;
        }

        int     nDisplayType;
        DWORD   dwIntervalTime;
        int     nStringId;
        int     nNextTipId;
    };

private:	
	 ControlFrame*	m_pID_FRAME_Tip;
	 ControlText*	m_pID_TEXT_SmallTip;

public:
    CUI_ID_FRAME_Tip();
	bool OnFrameRun();
	bool OnFrameRender();

	bool _LoadUI();				        // ����UI
	bool DoControlConnect();	        // �����ؼ�
	bool _UnLoadUI();			        // ж��UI
	bool _IsVisable();			        // �Ƿ�ɼ�
	void _SetVisable( const bool bVisable );	// �����Ƿ����

    virtual void InitializeAtEnterWorld();
    void SetShowTip( bool bShow );              // ����
    void SetTipShowTime( DWORD dwTime );        // ����ÿ��Tip��ʾʱ��

protected:
    void ResetMembers();
    void ResetTips();
    bool LoadTipConfig( std::string strFilePath );
    bool ChangeTipInfo( bool bShow = false, const std::string& strText = "" );  // ��������һ��Tip��Null��ʾ��������
    void UpdateTipShow();                                                       // ����Tip

private:
    bool                            m_bConfigLoaded;            // Tip���Ƿ��Ѽ���
    bool                            m_bShowTip;                 // Tip�Ƿ���ʾ
    DWORD                           m_dwShowTime;               // ÿ��Tip�ĳ���ʱ��
    std::map<int, Tip>              m_tipMap;                   // Tip�б�           (����ȡ��)
    std::vector<TipEntrance>        m_entranceVec;              // Tip���           (����ȡ��)

private:
    friend class CScreenInfoManager;
};

extern CUI_ID_FRAME_Tip s_CUI_ID_FRAME_Tip;
