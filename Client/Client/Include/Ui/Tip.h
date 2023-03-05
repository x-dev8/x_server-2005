/********************************************************************
	Created by UIEditor.exe
	FileName: C:\Documents and Settings\zhuomeng.hu\桌面\Tip.h
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
        int     nBeginId;               // 此线开始的Tip Id (读表)
        int     nCurrentId;             // 此线当前显示的Id
        int     nLastId;                // 此线上条Tip Id
        DWORD   dwBeginTime;            // 此轮Tip开始时间 (读表)
        DWORD   dwLastTime;             // 上条Tip显示时间
        DWORD   dwNextTime;             // 至下条Tip所需时间
        int     nLoopCount;             // 此轮Tip循环次数 (读表)
        int     nLoopRemain;            // 剩余循环次数
        bool    bBegin;                 // 此轮是否已开始
        bool    bShow;                  // 此条Tip是否处于显示状态
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

	bool _LoadUI();				        // 载入UI
	bool DoControlConnect();	        // 关连控件
	bool _UnLoadUI();			        // 卸载UI
	bool _IsVisable();			        // 是否可见
	void _SetVisable( const bool bVisable );	// 设置是否可视

    virtual void InitializeAtEnterWorld();
    void SetShowTip( bool bShow );              // 开关
    void SetTipShowTime( DWORD dwTime );        // 设置每条Tip显示时间

protected:
    void ResetMembers();
    void ResetTips();
    bool LoadTipConfig( std::string strFilePath );
    bool ChangeTipInfo( bool bShow = false, const std::string& strText = "" );  // 更换至下一条Tip，Null表示更换至空
    void UpdateTipShow();                                                       // 更新Tip

private:
    bool                            m_bConfigLoaded;            // Tip表是否已加载
    bool                            m_bShowTip;                 // Tip是否显示
    DWORD                           m_dwShowTime;               // 每条Tip的持续时间
    std::map<int, Tip>              m_tipMap;                   // Tip列表           (读表取得)
    std::vector<TipEntrance>        m_entranceVec;              // Tip入口           (读表取得)

private:
    friend class CScreenInfoManager;
};

extern CUI_ID_FRAME_Tip s_CUI_ID_FRAME_Tip;
