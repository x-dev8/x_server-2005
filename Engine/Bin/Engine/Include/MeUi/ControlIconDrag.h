#pragma once
#include "MeUi/IconManager.h"
#include <assert.h>
#include "MeUi/ControlObject.h"
#include "MeUi/ControlScrollBar.h"
//#include "MeUi/GridMap.h"
class CSmartAnimation;
class CSmartAniManage;
class ControlIconDrag : public ControlObject
{
public:
	struct S_ListImg 
	{
		S_ListImg();
		~S_ListImg();
		S_ListImg( const S_ListImg& v );

		S_ListImg& operator=(const S_ListImg& v);

		void Clear();
		bool IsNull()
		{
			if( !m_pkIconInfo )
				return false;
			return m_pkIconInfo->IsNull();
		}
		void ChangeCount( const bool bAdd/*Add or Remove*/, const int nCount )
		{
			if( !m_pkIconInfo )
				return;
			assert( m_pkIconInfo->Count() > 0 );
			if ( bAdd == true )
			{
				m_pkIconInfo->Count() += nCount;
			}
			else
			{
				m_pkIconInfo->Count() -= nCount;
				if ( m_pkIconInfo->Count() <= 0 )
				{
					Clear();
				}
			}
		}
		void SetData( IN void* pData , eIconDrawState eEnable=eIcon_Enable, eTipFlag eFlags = eTipFlag_Normal, IN bool bCompareData = false, int nPlayerID = -1 )
		{
			if( !m_pkIconInfo )
				return;

			m_pkIconInfo->SetFlag( eFlags );
			m_pkIconInfo->SetData( pData, false, false, bCompareData, nPlayerID );			
			m_eEnable = eEnable;
		}
		void SetData( int nID, int nCount, eIconDrawState eEnable=eIcon_Enable, bool bShowCount=false,  eTipFlag eFlags = eTipFlag_Normal,
			bool bNext = false, bool bBound = false )
		{
			if( !m_pkIconInfo )
				return;

			m_pkIconInfo->SetFlag( eFlags );
			m_pkIconInfo->SetData( nID, nCount, bShowCount, bNext, 0xffff, -1, bBound );			
			m_eEnable = eEnable;
			//if( m_bEnable )
			//{
			//	m_dwColor = 0xffffffff;
			//}
			//else
			//{
			//	m_dwColor = 0x7fffffff;
			//}
		}
		void SetFlags( DWORD Flags )
		{
			m_dwFlags = Flags;
		}
		void SetTime( DWORD dwStartTime, DWORD dwPeriod )
		{
			m_dwStartTime = dwStartTime;
			m_dwPeriod = dwPeriod;
		}
		DWORD GetCDStartTime() const{ return m_dwStartTime; }
		DWORD GetCDPeriod() const{ return m_dwPeriod; }
		void SetOtherInfo( const char* szInfo )
		{
			if( m_pkIconInfo )
				m_pkIconInfo->SetOtherInfo( szInfo );
		}
		void SetCol( const COLORREF& col )
		{
			m_col = col;
			m_bUseCol = true;
		}
		void SetEnable( eIconDrawState eEnable )
		{
			m_eEnable = eEnable;
		}

        // 闪烁接口     added by zhuomeng.hu		[11/11/2010]
        void SetSparkEnable( bool bEnable )
        {
            if( !m_bSpark && bEnable )
                m_dwStartTime = HQ_TimeGetTime();
            else if( m_bSpark && !bEnable )
                m_dwStartTime = 0;

            m_bSpark = bEnable;
        }

		eIconDrawState m_eEnable;
		//ICON_INFO_STRUCT	m_stIcon;
		S_IconInfoBase* m_pkIconInfo;
		DWORD	m_dwFlags;		//附加信息
		COLORREF m_dwColor;		//自身的颜色
		//
		DWORD	m_dwStartTime;
		DWORD	m_dwPeriod;

        //------------------------ 背包内新物品特效 -----------------------------
        bool                m_bSpark;                       //是否播闪光动画
        DWORD               m_dwSparkBeginTime;
        CSmartAnimation*    m_pSparkAnimation;
        CSmartAnimation*    GetSparkAni() const { return m_pSparkAnimation; }
        CSmartAnimation*    GetSparkAniNotNULL( CSmartAniManage* pAniManage );
        //-----------------------------------------------------------------------

		CSmartAnimation*			m_pCoolDownAni;
		CSmartAnimation*			GetCoolDownAni() const { return m_pCoolDownAni; }
		CSmartAnimation*			GetCoolDownAniNotNULL(CSmartAniManage* pAniManage) ;
		//
		COLORREF m_col;
		bool	m_bUseCol;

		DWORD m_dwCooldownFinishStartTime;
		bool m_bCooldownStart;
		CSmartAniManage* m_pAniManage;
	};

public:
	// tip所用
	typedef bool (*funcGlobalOnMouseMove)( S_ListImg* pImg, bool bEnableCompare, const RECT& rcItem, ControlIconDrag* pThis );
	static void SetGlobalOnMouseMove( funcGlobalOnMouseMove pFun ){ ms_pFuncBlobalOnMouseMove = pFun; }

    // 鼠标悬浮于闪烁装备时回调     added by ZhuoMeng.Hu		[11/12/2010]
    typedef bool (*funcSparkOnMouseMove)( S_ListImg* pImg, ControlIconDrag* pThis );

protected:
	static funcGlobalOnMouseMove ms_pFuncBlobalOnMouseMove;

public:
	typedef bool (*funOnButtonClick)( OUT ControlObject* pSender,
		OUT IN ControlIconDrag::S_ListImg* pItem );
	typedef void (*funOnShiftLBClick)( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	typedef bool (*funDragOn)( OUT ControlObject* pSender, OUT ControlObject* pMe, 
		OUT IN ControlIconDrag::S_ListImg* pItemDrag,
		OUT IN ControlIconDrag::S_ListImg* pItemSrc );
	typedef bool (*funLDBClick)( OUT ControlObject* pSender, OUT IN ControlIconDrag::S_ListImg* pItem );
	typedef bool (*funRButtonUp)( OUT ControlObject* pSender, OUT IN ControlIconDrag::S_ListImg* pItem );
	typedef void (*funOnMouseMove)( UINT nFlags, const int nX, const int nY );
	typedef bool (*funDragOut)( ControlObject* pSender, ControlIconDrag::S_ListImg* pItem );
	virtual void SetVisable( const bool bVisable);

public:	/*Virtual Function by ControlObject*/
	virtual void Run();
	virtual bool OnMouseMove( UINT nFlags, const int nX, const int nY );
	virtual bool OnMouseWheel( bool bUp, const int nX, const int nY );
	virtual bool OnLButtonDown( UINT nFlags, const int nX, const int nY );
	virtual bool OnLButtonUp( UINT nFlags, const int nX, const int nY );
	virtual bool OnRButtonDown( UINT nFlags, const int nX, const int nY );
	virtual bool OnRButtonUp( UINT nFlags, const int nX, const int nY );
	virtual bool OnLButtonDBClick( UINT nFlags, const int nX, const int nY );
	virtual bool OnKeyDown( UINT nChar );
	virtual bool OnKeyUp( UINT nChar );

	virtual void FocusOut() { m_nPressItemIndex = -1; }

public:
	virtual int	 GetIconSize() = 0;
	virtual bool GetTilePt( const int nX, const int nY, OUT POINT *ptTile ) = 0;
	virtual bool CanbePick() = 0;
	virtual void SetCanbePick( const bool b ) = 0;

	void	RefreshTipShow(const int nX, const int nY);
public:
	bool OnDragOn( const int nX, const int nY, OUT IN S_ListImg* pItem, IN ControlObject* pSender );
	bool OnDragDisableOn( const int nX, const int nY, OUT IN S_ListImg* pItem, IN ControlObject* pSender );
	bool OnDragDisableOut( IN ControlObject* pSender,OUT IN S_ListImg* pItem );
public:
	bool SetItem( IN S_ListImg *pItem,const int nIndex = -1, bool reverse = false);	
	// 移除指定坐标项
	bool RemoveItemById( const int nItemID, const int nCount );
	bool RemoveItemByIndex( int nIndex );
	// 清除
	void	Clear( bool bChangeStartIndex = false );
	// 取得项
	S_ListImg* GetItem( const unsigned int nX, const unsigned int nY );
	S_ListImg* GetCompareItem();
	S_ListImg* GetSecondCompareItem();
	S_ListImg* GetCurSelItem();
	S_ListImg* GetItemByIndex( const unsigned int nIndex );
	S_ListImg* GetLastIndex( int index );
	S_ListImg* GetItemById( const int nId );
	int GetItemWidth()
	{
		S_ListImgData *pListImgData = (S_ListImgData*)m_pstData;		
		int nIconWidth = (pListImgData->m_nIconSize + pListImgData->m_nOffsetWidth) *ControlObjectGetSCALE(this);
		return nIconWidth;

	}
	int GetItemHeight()
	{
		S_ListImgData *pListImgData = (S_ListImgData*)m_pstData;		
		int nIconHeight = (pListImgData->m_nIconSize + pListImgData->m_nOffsetHeight) *ControlObjectGetSCALE(this);
		return nIconHeight;
	}

	void GetItemRect( unsigned int nX, unsigned int nY, RECT& outRC ) 
	{
		RECT rc;
		GetRealRect( &rc );
		int w = nX - rc.left;
		int h = nY - rc.top;
		float nIconWidth,nIconHeight;
		nIconWidth = GetItemWidth();
		nIconHeight = GetItemHeight();

		// 所在格子的索引
		int xi = w / nIconWidth;
		int yi = h / nIconHeight;
		if (xi >= m_nWidthShowMaxCount || yi >= m_nHeightShowMaxCount)
			return ;

		// 所在格子的x, y
		int x = rc.left + xi * nIconWidth + 0.5f;
		int y = rc.top + yi * nIconHeight + 0.5f;
		outRC.left = x;
		outRC.top = y;
		outRC.right = x + nIconWidth;
		outRC.bottom = y + nIconHeight;
	}
	void GetItemRect( unsigned int nIndex, RECT& outRC )
	{
		RECT rcReal;
		GetRealRect( &rcReal );

		int nX = nIndex%m_nWidthShowMaxCount;
		int nY = nIndex/m_nWidthShowMaxCount;

		S_ListImgData *pListImgData = (S_ListImgData*)m_pstData;
		int nIconWidth,nIconHeight;
		nIconWidth = GetItemWidth();
		nIconHeight = GetItemHeight();

		outRC.left = rcReal.left +  pListImgData->m_nOffsetWidth *ControlObjectGetSCALE(this)/2 + nX*nIconWidth;
		outRC.top = rcReal.top + pListImgData->m_nOffsetHeight *ControlObjectGetSCALE(this)/2 + (nY*nIconHeight-m_nShowStartHeight);
		outRC.right = outRC.left + pListImgData->m_nIconSize *ControlObjectGetSCALE(this) - 1;
		outRC.bottom = outRC.top + pListImgData->m_nIconSize *ControlObjectGetSCALE(this) - 1;
	}
	//
	//	int GetMaxCount();
	// 取得该项的索引 to zizi ： 应该放到逻辑层，不应该放到这里。
	int	 GetItemIndex( IN const S_ListImg *pItem );
	//取得一个空位置 如果没有则 返回-1  to zizi ： 应该放到逻辑层，不应该放到这里。
	int	 GetNullItem( bool reverse = false );
	//
	void SetIsShop( const bool b ){ m_bIsShop = b; }
	bool GetIsShop() const{ return m_bIsShop; }
	//
	void SetShowAllInfo( const bool b){ m_bShowAllInfo = b; }
	bool GetShowAllInfo() const {return m_bShowAllInfo; }
	// 设置处理函数
	void SetDragOnFun( IN funDragOn pFun )	{ m_pFunDragOn = pFun; }
	void SetDragDisableOnFun( IN funDragOn pFun )	{ m_pFunDragDisableOn = pFun; }
	void SetDragDisableOutFun( IN funDragOut pFun )	{ m_pFunDragDisableOut = pFun; }
	//void SetDragOffFun( IN funDragOff pFun )	{ m_pFunDragOff = pFun; }
	void SetLDBClickFun( IN funLDBClick pFun )	{ m_pFunLDBClick = pFun; }
	void SetRButtonUpFun( IN funRButtonUp pFun )	{ m_pFunRButtonUp = pFun; }
	void SetButtonClickFun( IN funOnButtonClick pFun )	{ m_pFunButtonClick = pFun; }
	void SetShiftLBClickFun( funOnShiftLBClick pFun )	{ m_pFunShiftLBClick = pFun; }
	void SetOnMouseMoveFun( funOnMouseMove pFun ){ m_pFunOnMouseMove = pFun; }

    // added by ZhuoMeng.Hu		[11/12/2010]
    void SetSparkOnMouseMoveFun( funcSparkOnMouseMove pFun ){ m_pFunSparkOnMouseMove = pFun; } 

	int  GetItemCnt()									{  return m_vtItem.size();}
	void SetSpareTime( int nIndex, DWORD dwTime, int nStartTime, bool bShowBottomTime = false );
	int	 GetShowStartHeight() const							{ return m_nShowStartHeight; }

	void SetScrollVisable( bool bShow = true );
	void SetShowStartHeight(int nStartIndex)			{ m_nShowStartHeight = nStartIndex; }

	void SetScrollBarEnable( bool bEnable = true)		{ m_UIScroll.SetEnable(bEnable); }

	bool IsDisableCanbePick(){ return m_bDisableCanbePick; }
	void SetDisableCanbePick( bool b ){ m_bDisableCanbePick = b; }

	int GetHeightShowMaxCnt( ) { return m_nHeightShowMaxCount; }
	void SetHeightShowMaxCnt( int max )
	{
		m_nHeightShowMaxCount = max;
		if (m_nMaxHeightCount - m_nHeightShowMaxCount > 0)
			m_UIScroll.SetMaxValue((m_nMaxHeightCount - m_nHeightShowMaxCount)*GetItemHeight());
	}
	int GetHeightMaxCnt( ) { return m_nMaxHeightCount; }
	void SetHeightMaxCnt( int max )
	{ 
		m_nMaxHeightCount = max;
		if (m_nMaxHeightCount * m_nWidthShowMaxCount > m_vtItem.size())
			m_vtItem.resize(m_nMaxHeightCount * m_nWidthShowMaxCount);
		if (m_nMaxHeightCount - m_nHeightShowMaxCount > 0)
			m_UIScroll.SetMaxValue((m_nMaxHeightCount - m_nHeightShowMaxCount)*GetItemHeight());
	}

	int GetRowItemCnt() { return m_nWidthShowMaxCount; }

	void SetEnableRowCnt( int cnt );
	void SetEnableCnt( int cnt );
	int  GetEnableCnt() { return m_nEnbaleCnt == -1 ? m_vtItem.size() : m_nEnbaleCnt; }

	void SetNotMsgClick( bool b = true)	{ m_bNotMsgClick = b; }

	void SetEnableDrag( bool b ){ m_bEnableDragIn = b; m_bEnableDragOut = b;}

	bool IsEnableDragIn() const { return m_bEnableDragIn; }
	void SetEnableDragIn(bool b) { m_bEnableDragIn = b; }

	bool IsEnableDragOut() const { return m_bEnableDragOut; }
	void SetEnableDragOut(bool b) { m_bEnableDragOut = b; }

	bool EnableCompare(){ return m_bEnableCompare; }
	void SetEnableCompare( bool bEnableCompare ){ m_bEnableCompare = bEnableCompare; }

	void SetDelayTime( int nTime ){ m_nDelayTime = nTime; }
	int	 GetDelayTime(){ return m_nDelayTime; }

	//POINT getCurItemPos()	{ return m_ptCurSel; }

	void SetPressItemIndex(int n) { m_nPressItemIndex = n; }
	void ShowPressEffect(bool b) { m_bShowPressEffect = b; }
	void SetSelect(int n) { m_nSelectItemIndex = n; }//设置选中

	S_TextTipInfo* GetTipInfo() { return &TipInfo; }

protected: // Tip 相关
	virtual const S_IconInfoBase* GetTipPointer() const{ return &TipInfo; }

public:
	bool OnLDBClick( const int nX, const int nY, OUT IN S_ListImg* pItem, IN ControlObject* pSender );
	int Refeash();
	void InitItemDate();

	void SetShowCursorOnFrameOnNULLItem(bool val) { m_bShowCursorOnFrameOnNULLItem = val; }

protected:
	std::vector<S_ListImg>	m_vtItem;
	// added, jiayi, [2009/7/1]
	std::map<int, S_ListImg>	m_mapCompareItem;
	S_ListImg m_TempCompareItem;
	S_ListImg m_SecondTempCompareItem;
	//
	int		m_nWidthShowMaxCount;
	int		m_nHeightShowMaxCount;
	int		m_nMaxHeightCount;
	int		m_nShowStartHeight;
	bool	m_bIsShop;
	POINT	m_ptCurSel;
	POINT	m_ptMouseOnSel;
	bool	m_bShowAllInfo;
	bool	m_bDisableCanbePick;

	int		m_nEnbaleRowCnt;	//可用行数的数量
	int		m_nEnbaleCnt;	//可用行数的数量

	bool	m_bNotMsgClick;		//可以被点穿
	bool	m_bEnableCompare;	//可显示比较的装备

	ControlScrollBar	m_UIScroll;
	D3DCOLOR			m_colSel;
	D3DCOLOR			m_colMouseOn;

	funDragOn			m_pFunDragOn;
	funDragOn			m_pFunDragDisableOn;
	funDragOut			m_pFunDragDisableOut;
	funLDBClick			m_pFunLDBClick;
	funRButtonUp		m_pFunRButtonUp;
	funOnButtonClick	m_pFunButtonClick;
	funOnShiftLBClick	m_pFunShiftLBClick;
	funOnMouseMove      m_pFunOnMouseMove;
    funcSparkOnMouseMove      m_pFunSparkOnMouseMove;

	bool	m_bShiftDown;
	bool	m_bKeyDown;
	bool    m_bLClick;

	bool	m_bEnableDragIn;	// 可以进来
	bool	m_bEnableDragOut;	// 可以出去
	int		m_nDelayTime;		// 延迟多少毫秒

	int m_nPressItemIndex;
	int m_nSelectItemIndex;
	bool m_bShowPressEffect;
	bool m_bShowCursorOnFrameOnNULLItem;
	S_TextTipInfo		TipInfo;	//tip 显示

public:
	ControlIconDrag(void);
	virtual ~ControlIconDrag(void);
};
