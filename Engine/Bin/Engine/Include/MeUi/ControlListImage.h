
#pragma once
#include "MeUi/ControlObject.h"
#include "MeUi/ControlIconDrag.h"

class ControlListImage : public ControlIconDrag
{
public:
	INT m_nCurLvl;
	INT m_nMaxLvl;

	bool	_bOrder;	//排列顺序 从右向左 还是从左右向 默认false从左向右添加。

	bool m_bOnlyShowItemIcon;

public:	/*Virtual Function by ControlObject*/
	void Run();
	void Render();
	void InitUIData( IN ControlObject* pFather, IN S_BaseData* pData );
//     virtual void SetVisable( const bool bVisable );

public: /*Virtual Function by ControlIconDrag*/
	// 取得Icon的大小
	int	 GetIconSize(){ return ((S_ListImgData*)m_pstData)->m_nIconSize * ControlObjectGetSCALE(NULL); }
	// 取得指定坐标的格子坐标
	bool GetTilePt( const int nX, const int nY, OUT POINT *ptTile );
	bool CanbePick(){ return ((S_ListImgData*)m_pstData)->m_bCanbePick; }
	void SetCanbePick( const bool b ){ ((S_ListImgData*)m_pstData)->m_bCanbePick = b; }

	void SetLvlInfo( INT nCurLvl, INT nMaxLvl );

	void SetScrollValue(int nValue);
	int  GetScrollValue() { return m_UIScroll.GetValue(); }

	void setOrderType(bool bBeginRight) { _bOrder = bBeginRight; }

	void SetOnlyShowItemIcon(bool b);
	bool GetOnlyShowItemIcon() { return m_bOnlyShowItemIcon; }

	//added by zilong. 2011-03-07. ------------------------------------
	/*--------------------------------------------------------------
	Desc	: 使空的Item有淡入淡出效果。
	--------------------------------------------------------------*/
	void SetNullItemFadeInAndOut(bool enable_);
	void InitFadeParam4NullItem();
	//added by zilong. end. -------------------------------------------

private:
    // 为创建动画帧封装一个函数，只支持单行横向序列帧       added by zhuomeng.hu		[11/11/2010]
    void CreateAnimation(int& nPic, S_ListImg* pListImg, const RECT& iconRect, std::string strPicPath, DWORD dwCurTime, bool bRepeat, float fSrcXParamA, float fSrcXParamB, float fSrcXParamC,
        int32 iSrcXParamT, float fSrcY , float fSrcWidth , float fScrHeight ,DWORD dwElapsedTime );

public:
	// 移除指定坐标项
	//	bool RemoveItem( const int nIndex, const int nCount );				// nCount为'-1'时全删
	// 取得鼠标所在项格子坐标
	POINT GetMouseOnSel(){ return m_ptMouseOnSel; }

public:
	ControlListImage(void);
	~ControlListImage(void);

	virtual void ResetDevice();

private:
	//added by zilong. 2011-03-07. ------------------------------------
	bool	m_bFadeInorFadeOut4NullItem;
	bool	m_bInFade4NullItem;
	int		m_nFadeCurColorA4NullItem;
	DWORD	m_dwFadeLastTime4NullItem;
	//added by zilong. end. -------------------------------------------

};

extern int g_ControlListImageLongDelayTime;
extern int g_ControlListImageShortDelayTime;
