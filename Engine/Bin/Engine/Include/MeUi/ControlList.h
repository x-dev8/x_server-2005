
#pragma once
#include <assert.h>
#include <vector>
#include "MeUi/ControlObject.h"
#include "MeUi/ControlScrollBar.h"
#include "MeUi/IconManager.h"
#include "UiDataParsing.h"

#define LIST_NOTSHOWBAR 0
#define LIST_SHOWBAR 1
#define ITEM_HYBER_MAX_CNT 3
#define ITEM_FADE_COUNT 20


class ControlList : public ControlObject
{
// 	typedef bool (*funcFindHyber_Player)(const std::wstring& wstrParse, std::wstring& wstrPlayer);
public:
// 	static funcFindHyber_Player ms_pfFindHyperPlayer;
public:
	struct S_List : public MeCommonAllocObj<ControlList::S_List>
	{
        enum EList_AlignMode
        {
            LIST_ALIGNMODE_LEFT     = 0,
            LIST_ALIGNMODE_MIDDLE,
            LIST_ALIGNMODE_RIGHT,
            LIST_ALIGNMODE_MAX
        };

		typedef struct STextData
		{
			friend ControlList;
			friend S_List;
			EKeyType		type;	// 类型
			DWORD			col;	// 颜色
			std::wstring	str;		// 文本内容
			int				nTextureID;	// 贴图ID 
			void*			pInfo;	// 表情动画数据
			RECT			rc;			// 有效区域
			STextData()
			{
				type = eKeyNormal;
				col = 0;
				nTextureID = -1;
				pInfo = NULL;
				m_callBackData = NULL;
			}
			bool			IsImgType(){return (type == eKeyImg )|| (type == eKeyChatExp );}
		private:
			UiCallbackDataBase*		m_callBackData;
		}STextData;
// 		EKeyType	GetTextData( const std::wstring& strString, unsigned int *pnOff,
// 			std::wstring* pstrText, DWORD *dwKey);
		void		ParseText( int& lineHeight,UiCallbackDataArr* pBase,DWORD	nSyntaxFlag);
// 		void		ParseTextOld( int& lineHeight); //yanli [2010-8-6]
		void		ParseTextNew( int& lineHeight,DWORD	nSyntaxFlag);//yanli [2010-8-6]
		bool		IsExistImg( );
		bool		CalculatePoint(int lineHeight,HDC dc, int nFontIndex=2); //## 增加, int nFontIndex
		void		Render(RECT &rect,int fontIndex,ControlList* pList);

		S_List()
		{
			m_pTipInfo = 0;			
			_hyberItemInfoRaw = 0;
// 			m_dwParseflag = 0xffffffff & (~eKeyColor);
            m_eAlignMode = LIST_ALIGNMODE_LEFT;
            m_nMargin = 0;
			m_colUrlMouseOn = 0xFFFF0000;
            m_nSyntaxUnderLine = 0xFFFFFFFF;
			clear();
		}
		~S_List()
		{
			delete [] _hyberItemInfoRaw;
			_hyberItemInfoRaw = 0;
			if( m_pTipInfo == theIconInfoMouseTip.GetIconInfo() )
				theIconInfoMouseTip.Clear();
			clear();
		}
		S_List& operator = (const S_List&);
		virtual void clear();
		void SetText( int nCount, ... );
		void SetData( IN const char* szText, int nID = 0, IN void* pData = NULL, D3DCOLOR col = 0, 
			char *szNote = NULL /*备用数据*/,char* hyberItemInfo=NULL, int hyberItemCnt = 0, int nItemSize = 0)
		{
			if( strlen(szText) >= sizeof(m_szText) )
			{
				assert(false);
			}
			strncpy( m_szText, szText, sizeof(m_szText) - 1 );

			if( szNote )
				strncpy( m_szNote, szNote, sizeof(m_szNote) - 1 );
			m_nID = nID;
			m_pData = pData;
			m_colTextCol = col;

			if( hyberItemCnt > 0 )
			{
				if( NULL != hyberItemInfo && nItemSize > 0 )
				{
					assert(nItemSize && "item size is 0?");
					delete[] _hyberItemInfoRaw;
					int nSize = min(nItemSize*hyberItemCnt, nItemSize*ITEM_HYBER_MAX_CNT) ;
					_hyberItemInfoRaw = new unsigned char[nSize];
					memcpy( _hyberItemInfoRaw, hyberItemInfo, nSize );
					m_nItemSize = nItemSize;
				}
			}
		}
        void SetAlignMode( EList_AlignMode eAlignMode )
        {
            m_eAlignMode = eAlignMode;
        }
        EList_AlignMode GetAlignMode()
        {
            return m_eAlignMode;
        }
        void SetMargin( int nMargin )       // 仅在左对齐和右对齐时有效
        {
            m_nMargin = nMargin;
        }
        int GetMargin()
        {
            return m_nMargin;
        }
		void setColor( D3DCOLOR col )
		{
			m_colTextCol = col;
		}
		void setTextCustomKey( const char* key )
		{
			std::string temp = m_szText;
			temp.erase( 17, temp.length()-17 );
			temp += key;

			memset( m_szText, 0, sizeof(m_szText));
			strncpy( m_szText, temp.c_str(), sizeof(m_szText)-1 );
		}
		void setTip( const char* tip, DWORD dwAlign )
		{
			if( NULL == tip )
				return ;
			if( !m_pTipInfo )
				m_pTipInfo = MeNew S_TextTipInfo();
			m_pTipInfo->SetInfo( tip, dwAlign );
		}
		void setTip( const char* tip )
		{
			if( NULL == tip )
				return;
			if( !m_pTipInfo )
				m_pTipInfo = MeNew S_TextTipInfo();
			m_pTipInfo->SetInfo( tip );
		}
		void setIsOnline(bool online)
		{
			_bOnline = online;
		}
		void setUrlMoveOnColor(DWORD dwColor)
		{
			m_colUrlMouseOn = dwColor;
		}
		void RemoveSyntaxFlag(DWORD val) { m_nSyntaxUnderLine &= (~val); }//取消下划线

		/*
		 * Author:	2012-8-14 wangshuai
		 * Desc: 	获取ListItem的实际文本
		 */
		std::wstring GetListItemRealText(const std::wstring &itemText)
		{
			std::wstring tempText = itemText;
			int pos = tempText.find_first_of(L'$');
			if (pos != std::wstring::npos && tempText.length() > 1)
				tempText = tempText.substr(0, pos);
			return tempText;
		}

		char m_szText[256];		// 文本(必要)
		char m_szNote[32];		//备注,备用
		int	 m_nID;				// ID
		void *m_pData;			// 数据
		int m_nItemSize;		// 单个数据的大小

		//SCharItem _hyberItemInfo[ITEM_HYBER_MAX_CNT];
		unsigned char* _hyberItemInfoRaw;
		D3DCOLOR m_colTextCol;
		bool			_bOnline;//是否在线
		S_TextTipInfo*   m_pTipInfo;	//tip显示

		std::vector<STextData> vtTextData;
		BOOL			UseSelColor;
		std::vector<S_List*> m_vtpChildItem;
		void		RemoveChild(S_List* pList);
		void SetHyberOtherColor(DWORD dwColor) { m_bUseHyberColor = true; m_colHyberOther = dwColor; }
		D3DCOLOR m_colHyberOther;
		bool m_bUseHyberColor;
		int		m_nHiberarchy;//默认-1,不绘制层次结构；0表示root,1表示展开的child
		bool	m_bCollapse;//collapse,这个变量同时标示这child里面指针的归属权，如果true，这负责释放这个指针，否则这个指针归属于控件。
		bool	m_bParseText;
		ControlList* m_pParentList;
		UiCallbackDataArr*			m_CurrCallbackDataArr;
		int				m_nCallbackDataArrIndex;
	private:
		//yanli[2010-8-6]--------------help function----------------
		void NoParse(const WCHAR* _wChar);
		void ParseHiberarchy();
// 		void ParseHyperPlayer(std::wstring& strText, int& offset,  std::wstring& player);

    private:
        EList_AlignMode m_eAlignMode;    // 对齐方式     added by zhuomeng.hu		[11/25/2010]
        int             m_nMargin;       // 边缘空白     added by zhuomeng.hu		[11/26/2010]
		DWORD			m_colUrlMouseOn; //鼠标移动颜色变化
		DWORD           m_nSyntaxUnderLine; //设置是否添加下滑线
		//---------------------------------------------------------
	};
	// added, jiayi, [2009/8/12]
	struct S_String_List : public S_List
	{
		struct S_String
		{
			std::string m_strFormat;
			std::string m_strString;
		};
		int m_nColumnCount;
		std::vector< S_String > m_vStrings;
		virtual void clear()
		{
			S_List::clear();
			m_vStrings.clear();
		}
		void Begin(){}
		
		/// 去掉字符串中空格
		void TrimString( std::string& strString )
		{
			std::string::size_type stPos = strString.find(" ");
			if( stPos != std::string::npos )
			{
				strString.erase( stPos );
				TrimString( strString );
			}
			else
				return;
		}
		void AddString( int nColumnWidth, unsigned short usString )
		{
			char szBuf[20];
			sprintf_s( szBuf, 20, "%d", usString );
			AddString( nColumnWidth, szBuf );
		}
		void AddString( int nColumnWidth, const char* pszString )
		{
			std::string strString( pszString );
			AddString( nColumnWidth, strString );
		}

		/// 添加字串
		void AddString ( int nColumnWidth, const std::string& strcString )
		{
			S_String SString;
			std::string strString = strcString;
			TrimString( strString );
			//nColumnWidth = ControlObject::UI_SCALE < 1.f ? nColumnWidth : nColumnWidth * ControlObject::UI_SCALE;
			nColumnWidth = nColumnWidth*ControlObjectGetSCALE(NULL);
			if( strString.size() < nColumnWidth ) // 居中
			{
				int nBlank = ( nColumnWidth - strString.size() ) / 2;
				if( nBlank > 0 )
				{
					char szBuf[256];
					sprintf_s( szBuf, 256, "%s", " " );
					for( int i = 1 ; i < nBlank ; ++ i )
					{
						sprintf_s( szBuf, 256, " %s", szBuf );
					}
					//插入空格
					strString = std::string( szBuf ) + strString;
					
				}				
			}
			char szBuf[256];
			sprintf_s( szBuf, 256, "%d", nColumnWidth );
			SString.m_strFormat = "%-" + std::string( szBuf ) + "s";
			SString.m_strString = strString;
			m_vStrings.push_back( SString );		
		}

		/// 设置到item中
		void End()
		{
			std::string strFinal;
			char szBuf[256];
			for( int i = 0 ; i < m_vStrings.size() ; ++ i )
			{
				//strFormat += m_vStrings[i].m_strFormat;
				sprintf_s( szBuf, 256, m_vStrings[i].m_strFormat.c_str(), m_vStrings[i].m_strString.c_str() );
				strFinal += szBuf;
			}
			SetData( strFinal.c_str() );
		}
	};

	//struct Catalog	//目录 用于类标分页		以后有时间再实现伸缩列表吧~~
	//{
	//	S_List*		_catalog;
	//	int			_nChlidCnt;	//孩子的数量
	//
	//};
// public:
// 	typedef void (*funcGlobalParseText)( ControlList::S_List::STextData& kTextData, const std::wstring& wstrOutText, EKeyType eType,
// 		int& nLineHeight, ControlList::S_List* pkThis );
// 	static funcGlobalParseText ms_pfGlobalParseText;
public:
	typedef void (*funSelectChange)( OUT ControlObject* pSender, OUT IN ControlList::S_List* pItem );
	typedef void (*funMouseClick)( OUT ControlObject* pSender, OUT IN ControlList::S_List* pItem );
// 	typedef void (*funShiftRBClick)( ControlObject* pSender, ControlList::S_List* pItem );
// 	typedef void (*funShiftLBClick)( ControlObject* pSender, ControlList::S_List* pItem );
	typedef void (*funOnCollapse)( ControlObject* pSender, ControlList::S_List* pItem );
	typedef void (*funOnShowTip)( ControlObject* pSender, ControlList::S_List* pItem );

	//暂时应用 不是最终解决方案
// 	typedef void (*funHyberClick)( ControlObject* pSender, const char* szName );
	typedef void (*funHyberRBtnDown)( ControlObject* pSender, const char* szName ,int nHyberType);
// 	typedef void (*funHyberItemClick)( ControlObject* pSender, unsigned char* pItem );
// 	typedef void (*funHyberOtherClick)( ControlObject* pSender, const std::string& content ,int nId);

public:	/*Virtual Function*/
	virtual void Render();
	virtual void		Run();
	virtual bool PtInObject( const int nX, const int nY ,bool bCheckMsgHold = true);
	virtual bool IsMouseInUI( const int nX, const int nY );
	void InitUIData( IN ControlObject* pFather, IN S_BaseData* pData );
	bool OnMouseMove( UINT nFlags, const int nX, const int nY );
	bool OnMouseWheel( bool bUp, const int nX, const int nY );
	bool OnLButtonDown( UINT nFlags, const int nX, const int nY );
    bool OnListLButtonDown( UINT nFlags, const int nX, const int nY );
	bool OnLButtonUp( UINT nFlags, const int nX, const int nY );

	bool OnLButtonDBClick( UINT nFlags, const int nX, const int nY );
	bool OnRButtonDown( UINT nFlags, const int nX, const int nY);
	bool OnRButtonUp( UINT nFlags, const int nX, const int nY);
	bool OnKeyDown( UINT nChar );
	bool OnKeyUp( UINT nChar );

public:
	// 添加单项
	S_List*	AddItem( IN const S_List* pItem,UiCallbackDataArr* pBase = NULL, const bool bMoveDonw = true );
	// 添加组项
	bool	AddArrayItem( IN const S_List* pItem, const int nItemCount, const bool bMoveDonw = true );
	// 重设组项,这个接口有可能导致内存泄露，没地方在用，先注掉
// 	bool	ResetItem( IN const S_List* pItem, const int nItemCount );
	// 取得当前选择项
	S_List* GetCurSelItem();
	S_List* GetOldCurSelItem();
	void	ParseText( S_List* pItem,UiCallbackDataArr* pBase);
	// 查找项
	S_List* FindItemByID( const int nID );
	void	setItemTip( int index, const char* tip );	//设置某个item的tip
	int		FindItemByItem( const char* item );			//返回-1即没有找到有这个字符串的item
	// 取得当前选项的索引
	int		GetCurSelIndex(){ return m_nCurSelIndex; }
	bool	SetCurSelIndex( const int nIndex );
    int     GetLastCurSelIndex(){ return m_nLastCurSel; }   // added by zhuomeng.hu		[11/8/2010]
    bool    SetLastCurSelIndex( const int nIndex );
	void ScrollToTheBegin();
	void ScrollToTheLast();

	// 清除
	void	Clear(bool bClearCurrSelectedIndex = true);
	// 设置回调函数
	void	SetSelectChangeFun( IN funSelectChange pFun )	{ m_pFunSelectChange = pFun; }
	void	SetRBClickFun( IN funMouseClick pFun )	{ m_pFunRBClick = pFun; }
	void	SetLBtnDownFun( IN funMouseClick pFun )	{ m_pFunLBtnDown = pFun; }
    void	SetLBtnUpFun( IN funMouseClick pFun )	{ m_pFunLBtnUp = pFun; }

// 	void	SetShiftRBClickFun( funShiftRBClick pFun )	{ m_pFunShiftRBClick = pFun; }
// 	void	SetShiftLBClickFun( funShiftLBClick pFun )	{ m_pFunShiftLBClick = pFun; }
	void	SetOnCollapseFun( funOnCollapse pFun )	{ m_pFunOnCollapse = pFun; }
	void	SetOnShowTipFun( funOnShowTip pFun )	{ m_pFunOnShowTip = pFun; }
	void	SetLDBClickFun( IN funMouseClick pFun )	{ m_pFunLDBClick = pFun; }
// 	void	SetHyberClickFun( funHyberClick pFun )	{ m_pFunHyberClick = pFun; }
	void	SetHyberRBtnDown( funHyberRBtnDown pFun)	{ m_pFunHyberRBtnDown = pFun; }
// 	void	SetHyberItemClick( funHyberItemClick pFun )	{ m_pFunHyberItemClick = pFun; }
// 	void	SetHyberOtherClick( funHyberOtherClick pFun )	{ m_pFunHyberOtherClick = pFun; }

	void	SetSelectChangeFun_2lua( const char* luaTable, const char* funName );
	void	SetRBClickFun_2lua( const char* luaTable, const char* funName );
// 	void	SetShiftRBClickFun_2lua( const char* luaTable, const char* funName );
// 	void	SetShiftLBClickFun_2lua( const char* luaTable, const char* funName );
	void	SetLDBClickFun_2lua( const char* luaTable, const char* funName );
// 	void	SetHyberClickFun_2lua( const char* luaTable, const char* funName );
	void	SetHyberRBtnDown_2lua( const char* luaTable, const char* funName );
// 	void	SetHyberItemClick_2lua( const char* luaTable, const char* funName );
	// 创建
	void	Create( IN const RECT* pRect, const D3DCOLOR colBack = 0,
		IN funSelectChange pSelectChangeFun = NULL,
		IN funMouseClick pLDBClickFun = NULL );
	void	HaveSelBar( const bool b, const bool bShow = LIST_SHOWBAR ) { m_bHaveSelBar = b;  m_bSelShow = bShow; }
	void	SetScrollPos( const int nX, const int nY );
	void	SetItemMaxCount( const DWORD dw ) { m_dwItemMaxCount = dw; }
	int		GetItemMaxCount()				  { return m_dwItemMaxCount; }
	void    SetItemShowCount( const int nCount ) { m_nShowMaxCount = nCount; }
	int     GetItemShowCount() { return m_nShowMaxCount; }
	int     GetListItemHeight();// { return (S_ListData*)m_pstData->m_nItemHeight; };
	void    SetUIScrollBlend( const int nBlend ) 
	{	
		m_UIScroll.SetUIScrollBarBlend( nBlend );
	}
	void	SetScrollHeight( const int nHeight )
	{
		m_UIScroll.SetScrollHeight( nHeight );	
	}
	void	SetScrollValue(int nValue);
	int		GetShowStartHeight() const				{ return m_nShowStartHeight; }
	void	SetShowStartHeight(int val);
	int		GetStartIndex()							{ return m_nShowStartHeight/m_nDefaultItemHeight;}
	void	SetStartIndex(int nStartIndex);			/*{ m_nShowStartHeight = nStartIndex*m_nDefaultItemHeight; }*/
	void	SetScrollVisable( bool bShow = true )		{ m_UIScroll.SetVisable(bShow); }
	void	SetScrollBarEnable( bool bEnable = true )		{ m_bOldScrollBarEnabled = bEnable; m_UIScroll.SetEnable(bEnable); }
	void    SetRBSelectEnable( bool bEnable = true ) { m_bRbCanSelect = bEnable; }
	void	SetSelBarOffset( int nOffset ){ m_nSelBarOffset = nOffset; }

	std::vector<S_List*> GetListItem() { return m_vtpItem; }
	void	RemoveListItem(int index);
	int		GetListItemCnt()		   { return m_vtpItem.size(); }
	ControlScrollBar* GetScrollBar()	{ return &m_UIScroll; }
	S_List*				GetListItem(int nIndex) {return m_vtpItem[nIndex];}
	EKeyType	PtInHyber( const int nX, const int nY );
// 	void	UpdataLine2D();

// 	EKeyType findHyber_player( int index, int x, int y );
// 	EKeyType findHyber_item( int index, int x = -1, int y = -1 );

	void			RemoveSyntaxFlag(DWORD val) { m_nSyntaxFlag &= (~val); }

	void setShowTip(bool show = true) { _bIsShowTip = show; }
	bool IsShowTip() const			  { return _bIsShowTip; }

	void BeginUpdate();
	void EndUpdate();

	void SetAutoSetCurIndex( bool b )	{ m_bAutoSetCurIndex = b; }

	void ShowScrollBar(int b) { m_bShowScrollBar = b; }
	void SetLeftScrollBar(bool b);


	void EnableShortcutKey(bool b) { m_bEnableShortcutKey = b; }

	virtual void SetRealRect( IN const RECT* prc );

	void EnableAlwaysProcessRButtonMsg(bool b) { m_bAlwaysProcessRButtonMsg = b; }

public:
	void	OnSelectChange( IN S_List* pItem );
	void	OnLDBClick( IN S_List* pItem );
	int		Refeash();
	void	OnRBDown( IN S_List* pItem );
// 	void	OnShiftRBDown( IN S_List* pItem );
// 	void	OnShiftLBDown( IN S_List* pItem );
	void	SetEnablePathFinding(bool val) { m_bEnablePathFinding = val; }
	void	SetOnlyLeafCanBeSelected(bool val) { m_bOnlyLeafCanBeSelected = val; }
	bool    InListContextRect(int nCol,int nX,int nY);  //鼠标是否在这行List的文字上边
    void    SetIgnoreLBtnDown( bool bIgnore );
    bool    IsIgnoreLBtnDown();

// Select bar & MouseHover bar operation.
public:
	static void	SetSelectBar( const RECT& rcBar, const std::string& strFile );
	static void	SetMouseHoverBar( const RECT& rcBar, const std::string& strFile );

protected: // Tip 相关
	virtual const S_IconInfoBase* GetTipPointer() const{ return &TipInfo; }


private:
	bool			CheckDrawMode(S_List* pList);
	bool			MoveTextDataPos( S_List* pList, int nOffsetX, int nOffsetY );
	S_List*			GetParentList( IN int nHiberarchy,int nStartIndex = -1);
	void			InterInsertList(S_List*	pList,int nInsertIndex);
	void			CalCurSelByMouse(const int nX , const int nY );
	void			OnlyLeafCanBeSelected();
	S_List*			PtOnCollapse( const int nX, const int nY ,int * pnIndex = NULL);
	int				GetTotalHeight(){return m_vtpItem.size()*m_nDefaultItemHeight;}

	// 控制渐变
	typedef struct _tagSelItemFade
	{
		DWORD m_dwBeginTime;
		int	  m_nIndex;
	}SelItemFade;

	D3DCOLOR m_colBar;
	D3DCOLOR m_colFrame;

	ControlScrollBar	m_UIScroll;
	std::vector<S_List*> m_vtpItem;
	SelItemFade m_vFadeList[ITEM_FADE_COUNT];

	S_TextTipInfo		TipInfo;	//tip 显示
	bool	_bIsShowTip;			//是否显示tip
	
	bool	m_bOnlyLeafCanBeSelected;
	DWORD	m_dwItemMaxCount;
	int		m_nOldCurSel;	//保存久的 为了效率改变单个颜色
	int		m_nCurSelIndex;
	int		m_nLastCurSel;
	int		m_nMouseOnSel;
	S_List::STextData		*m_nMouseOnTextData;
	EKeyType m_eHyberType;
	int		m_nLastMouseOnSel;
	int		m_nShowStartHeight;
	int		m_nLastStartHeight;
	int		m_nShowMaxCount;
	bool	m_bHaveSelBar;
	int		m_nSelBarOffset;
	bool	m_bSelShow;
	bool    m_bRbCanSelect;
	DWORD			m_nSyntaxFlag;

	std::string m_szHyberPlayerName;
	unsigned char* CurHyberItem;
	//std::string m_szHyberItemName;
// 	RECT	m_rcMouseOnHyber;
// 	bool	m_bMouseOnHyber;
	bool	m_bEnablePathFinding;

	bool	m_bAutoSetCurIndex;

	funSelectChange		m_pFunSelectChange;
	funMouseClick		m_pFunLDBClick;
	funMouseClick		m_pFunRBClick;
	funMouseClick		m_pFunLBtnDown;
    funMouseClick       m_pFunLBtnUp;
// 	funShiftRBClick		m_pFunShiftRBClick;
	funOnCollapse		m_pFunOnCollapse;
	funOnShowTip		m_pFunOnShowTip;
// 	funShiftLBClick		m_pFunShiftLBClick;
// 	funHyberClick		m_pFunHyberClick;
	funHyberRBtnDown	m_pFunHyberRBtnDown;
// 	funHyberItemClick	m_pFunHyberItemClick;
// 	funHyberOtherClick  m_pFunHyberOtherClick;


	std::string		_luaTableName;

	std::string		_funSelectChangeName;
	std::string		_funLDBClickName;
	std::string		_funLRBClickName;
// 	std::string		_funShiftRBClickName;
// 	std::string		_funShiftLBClickName;
// 	std::string		_funHyberClickName;
	std::string		_funHyberRBtnDownName;
// 	std::string		_funHyberItemClickName;

	int m_nDefaultItemHeight;
	bool m_bOldScrollBarEnabled;

	bool m_bShowScrollBar;

	bool m_bShiftDown;

	std::string m_strHyberClickContent;

	bool m_bEnableShortcutKey;

	bool m_bAlwaysProcessRButtonMsg; // 总是接受右键消息

	bool m_bRecalRect;

    bool m_bIgnoreLBtnDown;         // 是否不响应左键按下消息，用来做能拖动的按钮
    int  m_nLBtnDownPosX;           // 鼠标左键按下时的位置
    int  m_nLBtnDownPosY;           // 鼠标左键按下时的位置

	////////////////////////////////////
	// select bar infomation
	static RECT ms_rcSelectBar;
	static RECT ms_rcMouseHoverBar;

	static std::string ms_strSelectBar;
	static std::string ms_strMouseHoverBar;

public:
	DWORD GetDrawFlags() const { return m_dwDrawFlags; }
	void SetDrawFlags(DWORD val) { m_dwDrawFlags = val; }
	void SetChangeColor(bool bValue){m_bChangeColor = bValue;}
	void SetCanLDB(bool bvalue){m_bCanLDB = bvalue;}
private:
	DWORD				m_dwDrawFlags;
	bool                m_bChangeColor;
	bool                m_bCanLDB;
public:
	ControlList(void);
	~ControlList(void);

	virtual void ResetDevice();
	static DWORD	s_LISTSELECTON_COLOR;
	static DWORD	s_CHAT_HYBER_DOWNLINE_COLOR;
	static DWORD	s_PathFindLinker_COLOR;
	static DWORD	s_CHAT_PLAYERNAME_COLOR;
};
