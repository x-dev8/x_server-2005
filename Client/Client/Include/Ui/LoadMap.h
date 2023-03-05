/********************************************************************
	Created by UIEditor.exe
	FileName: E:\Code\RunTime\CLIENT\Data\UI\LoadMap.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"


#ifndef ID_FRAME_LoadMap
#define ID_FRAME_LoadMap		"ID_FRAME_LoadMap"
#endif  ID_FRAME_LoadMap
#ifndef ID_PROGRESS_LOAD
#define ID_PROGRESS_LOAD		"ID_PROGRESS_LOAD"
#endif  ID_PROGRESS_LOAD
#ifndef ID_PICTURE_BgMap
#define ID_PICTURE_BgMap		"ID_PICTURE_BgMap"
#endif ID_PICTURE_BgMap
#ifndef ID_Load_Picture
#define ID_Load_Picture			"ID_PICTURE_LoadPic"
#endif ID_Load_Picture

#ifndef ID_TEXT_TEXT
#define ID_TEXT_TEXT		"ID_TEXT_TEXT"
#endif ID_TEXT_TEXT

#include "UiBase.h"
class CUI_ID_FRAME_LoadMap :public CUIBase
{
public:
    CUI_ID_FRAME_LoadMap();
	struct SMapInfo
	{
		DWORD dwMapId;
		int x,y;
		DWORD	  nGameMapId;
		float fX,fY,fZ;
		float fDirX,fDirY;
	};
	struct SLoadPicture
	{
		int mapid;
		std::string picname;
	};

	// Frame
	bool OnFrameRun();
	bool OnFrameRender();

private:
	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable);			// 设置是否可视
public:


	void	LoadMap( DWORD dwMapId, int x, int y,float fDirX,float fDirY, DWORD nGameMapId = -1);
	bool	IsMapLoaded();
	void	SetProgress( int n );

	void    SetFloatX(float x);
	void    SetFloatY(float y);
	void    SetFloatZ(float z);

	void	randomLoginMap();
	void	SetLoadPicture();

    void    SetMapLoaded(bool bValue){m_bMapLoaded = bValue;}
    void    SetMapLoading(bool bValue){m_bMapLoading = bValue;}

    void    SetUIProcessValue(float fValue);
    float   GetProcessValue(){return m_fProgress;}
    void    SetProcessValue(float fValue){m_fProgress = fValue;}

    static int lastProgress;
    static bool m_canHideLoadMapUI;
    static float m_fAddSpeed;
    ControlFrame* GetFrame(){return m_pID_FRAME_LoadMap;}

	bool	IsMapLoading(){return m_bMapLoading;}
private:
    ControlFrame*	    m_pID_FRAME_LoadMap;
    ControlProgress*	m_pID_PROGRESS_LOAD;
    ControlPicture*		m_pID_Pic_BgMap;
	ControlPicture*		m_pID_Load_Pic;
    ControlText*		m_pID_text;
    float				m_fProgress;

    float               m_fTempX;
    float               m_fTempY;
    float               m_fTempZ;

    bool	            m_bMapLoaded;
    bool	            m_bMapLoading;

    std::vector<std::string>StringVector;
    SMapInfo m_stMapInfo;
    std::string         m_filename;

	std::vector<SLoadPicture> m_LoadPicVector;
};
extern CUI_ID_FRAME_LoadMap s_CUI_ID_FRAME_LoadMap;
