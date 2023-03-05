/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Document\GameLogo\LoadSplash.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UiBase.h"
#include "MeFoundation/MeThread.h"

#ifndef ID_FRAME_LoadSplash
#define ID_FRAME_LoadSplash		"ID_FRAME_LoadSplash"
#endif  ID_FRAME_LoadSplash
#ifndef ID_PICTURE_BgMap
#define ID_PICTURE_BgMap		"ID_PICTURE_BgMap"
#endif  ID_PICTURE_BgMap
#ifndef ID_PROGRESS_LOAD
#define ID_PROGRESS_LOAD		"ID_PROGRESS_LOAD"
#endif  ID_PROGRESS_LOAD
#ifndef ID_TEXT_TEXT
#define ID_TEXT_TEXT		"ID_TEXT_TEXT"
#endif  ID_TEXT_TEXT

class CUI_ID_FRAME_LoadSplash :public CUIBase
{
public:
    enum ThreadType
    {
        Thread_None         = 0,
        Thread_Main,
        Thread_Skeleton,
        Thread_Config,
        Thread_Effect,
        Thread_Task,
        Thread_Max
    };

public:	
    CUI_ID_FRAME_LoadSplash();
    ~CUI_ID_FRAME_LoadSplash();

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();

	bool IsFinished(){ return m_nProgress >= 1000; }
    void DestroyMultiThread();
    void SetThreadLoadRate( int iThreadType, float fRate );
    bool ShouldUILoad();
	
private:
	virtual bool _LoadUI();				// ����UI
	bool DoControlConnect();	// �����ؼ�
	virtual bool _UnLoadUI();			// ж��UI
	virtual bool _IsVisable();			// �Ƿ�ɼ�
	virtual void _SetVisable( const bool bVisable );			// �����Ƿ����

protected:
    int m_nProgress;        // ��ǰ��ʾ����
    int m_lastProgress;     // �ϴν���
    int m_nDstProgress;     // Ŀ�����

    std::string m_strFileName; // ����ͼ
    std::vector<std::string> TipsString;

    ControlFrame*	m_pID_FRAME_LoadSplash;
    ControlPicture*	m_pID_PICTURE_BgMap;
    ControlProgress*	m_pID_PROGRESS_LOAD;
    ControlText*	m_pID_TEXT_TEXT;

private:
    CRITICAL_SECTION    m_LoadingCS;
    static MeThread*    m_pkLoadSklThread;          // �����߳�
    static MeThread*    m_pkLoadConfigThread;       // �����߳�
    static MeThread*    m_pkLoadEffectThread;       // ��Ч�߳�
    static MeThread*    m_pkLoadTaskDataThread;     // �����߳�
    float               m_fMainThreadRate;
    float               m_fSklLoadRate;
    float               m_fConfigLoadRate;
    float               m_fTaskLoadRate;
    float               m_fEffectLoadRate;
    bool                m_bUILoaded;
};
extern CUI_ID_FRAME_LoadSplash s_CUI_ID_FRAME_LoadSplash;
