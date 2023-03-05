
#pragma once
#include <MeFoundation/MeFoundationPCH.h>
#include "Dxsdk/d3d9types.h"
#include "tstring.h"
#include "MapStrToID.h"

// modified, jiayi, [2010/1/8]
// 这里两个数值之前是90， 鉴于ui占用过大，这里改小，如果超过这个数
// 稍微改大即可。
#define MAX_ICON_INFO_EX_LINE_COUNT		50
#define MAX_ICON_OTHER_INFO_EX_LINE_COUNT	12
#define MAX_ICON_INFO_LINES_COUNT		10
#define MAX_ICON_OTHER_INFO_LINES_COUNT	2

/////////////////////////////////////////////////////////////////
#define TIP_FRAME_FILENAME	"./data/ui/common/TipFrame.dds"
#define TIP_FRAME_TOTALWIDTH 64
#define TIP_FRAME_TOTALHEIGHT 64
#define TIP_FRAME_GRIDWIDTH 7
#define TIP_FRAME_GRIDHEIGHT 7
/////////////////////////////////////////////////////////////////

//#define ICON_INFO_STRUCT S_IconInfoHero
enum eIconDrawState
{
	eIcon_Disable,
	eIcon_Enable,	
	eIcon_Shop,
	eIcon_Lock,
	eIcon_Max
};

enum eItemType
{
	eCharItem = 0,
	eTaskItem
};

// added, jiayi, [2009/8/8]
enum eTipFlag
{
	eTipFlag_Normal = 0,
	eTipFlag_SkillNoNextLevel,
	eTipFlag_SkillWithNextLevel,
	eTipFlag_SkillTree,
	eTipFlag_Status,
	eTipFlag_ShowMoney,
	eTipFlag_Event,
	eTipFlag_Count
};

// added, jiayi, [2009/10/13]
enum eColorFrame
{
	eColorFrame_None = 0,	// 没有边框
	eColorFrame_Level,		// 品质边框
	eColorFrame_Active,		// 激活边框
	eColorFrame_Select,		// 选中边框
	eColorFrame_Count		
};
#define MAX_SPARETIME	36000000	/*10小时*/

class ControlFrame;
class S_IconInfoBase : public MeCommonAllocObj<S_IconInfoBase>
{
public:
	typedef const char* (*funcGetItemName)( unsigned char* data );
	typedef int (*funcGetItemLevel)( unsigned char* data );
	typedef void (*funcGetReplacedName)(unsigned short ustLevel, Common::_tstring& tstrName );

	static funcGetItemLevel ms_pfGetItemLevel;
	static funcGetItemName ms_pfGetItemName;
	static funcGetReplacedName ms_pfGetReplacedName;
public:
	// <#ffff0000=abcdefghij
	struct stIconInfo
	{
		stIconInfo()
		{
			Clear();
		}
		virtual ~stIconInfo(){Clear();}
		virtual void Clear()
		{
			m_col = 0;			
			m_bIconRightText = false;
			m_bRightText = false;
			m_dwTextAlign = DT_LEFT;	
			m_strInfo = "";
		}
		stIconInfo& operator=( const stIconInfo& iconInfo ){
			m_col = iconInfo.m_col;			
			m_bRightText = iconInfo.m_bRightText;
			m_bIconRightText = iconInfo.m_bIconRightText;
			m_dwTextAlign = iconInfo.m_dwTextAlign;
			m_strInfo = iconInfo.m_strInfo;			
			return *this;
		}
		D3DCOLOR	m_col;
		bool		m_bIconRightText;
		bool		m_bRightText;
		std::string m_strInfo;
		DWORD		m_dwTextAlign;
	};
	/** 支持tip里面显示图片，由于很多ui控件均支持tip，
	所以原先这个类会占用大部分内存控件并且无用处，
	所以现在淡出抽出来，会节省很多内存。
	*/
	struct stIconInfoEx : public stIconInfo
	{		
		virtual void Clear()
		{
			m_col = 0;
			m_bImage = false;
			m_bIcon = false;
			m_bGif = false;
            m_bLine = false;
			m_bNewLine = true;
			m_usImageWidth = 0;
            m_usImageHeight = 0;
            m_usDestWidth = 0;
            m_usDestHeight = 0;
			m_usImageRow = 0;
			m_usImageColumn = 0;
			m_nImageID = 0;
			m_ucRightRowCount = 0;
			m_bIconRightText = false;
			m_bRightText = false;
			m_dwTextAlign = DT_LEFT;			
		}
		stIconInfoEx& operator=( const stIconInfoEx& iconInfo ){
			m_col = iconInfo.m_col;
			m_bImage = iconInfo.m_bImage;
			m_bIcon = iconInfo.m_bIcon;
			m_bGif = iconInfo.m_bGif;
            m_bLine = iconInfo.m_bLine;
			m_bNewLine = iconInfo.m_bNewLine;
			m_usImageWidth = iconInfo.m_usImageWidth;
			m_usImageHeight = iconInfo.m_usImageHeight;
            m_usDestWidth = iconInfo.m_usDestWidth;
            m_usDestHeight = iconInfo.m_usDestHeight;
			m_usImageRow = iconInfo.m_usImageRow;
			m_usImageColumn = iconInfo.m_usImageColumn;
			m_nImageID = iconInfo.m_nImageID;
			m_ucRightRowCount = iconInfo.m_ucRightRowCount;
			m_bIconRightText = iconInfo.m_bIconRightText;
			m_bRightText = iconInfo.m_bRightText;
			m_dwTextAlign = iconInfo.m_dwTextAlign;
			m_strInfo = iconInfo.m_strInfo;
			m_eImageAlignMode = iconInfo.m_eImageAlignMode;
			m_usSrcX = iconInfo.m_usSrcX;
			m_usSrcY = iconInfo.m_usSrcY;
			m_strImage = iconInfo.m_strImage;
			return *this;
		}		
		/// added, jiayi, [2009/7/2]		
		enum eIconInfoImageAlignMode
		{
			eIIIA_Left,
			eIIIA_Middle,
			eIIIA_Right,
			eIIIA_Count
		};
		bool					m_bImage;			// 是否是图片	
		bool					m_bIcon;			// 是否是Icon
		bool					m_bGif;				// 是否是gif
        bool                    m_bLine;            // 是否是一条线
		std::string				m_strImage;			// 图片路径/gif缩写
		unsigned short			m_usImageWidth;		// 图片宽
		unsigned short			m_usImageHeight;	// 图片高
        unsigned short			m_usDestWidth;		// 绘制宽，为0时不缩放
        unsigned short			m_usDestHeight;		// 绘制高，为0时不缩放
		unsigned short			m_usImageRow;		// 对应图片第几行
		unsigned short			m_usImageColumn;	// 对应图片第几列
		eIconInfoImageAlignMode m_eImageAlignMode;	// 图片对齐方式
		bool					m_bNewLine;			// 后面是否换行
		int						m_nImageID;			// 图片ID,在配置文件中
		unsigned char			m_ucRightRowCount;	// 图标右边显示的字串行数
		unsigned short			m_usSrcX;			// 在图片中的坐标x
		unsigned short			m_usSrcY;			// 在图片中的坐标y
	};

	struct sShowGem
	{
		enum enumElement
		{
			eElement_Ice,//eElement_Bing = 0,
			eElement_Fire,//eElement_Huo,

			eElement_Thunder,//eElement_Lei,
			eElement_Poison,//eElement_Du,
			eElement_Max,
		};

		sShowGem()
		{
			nGemPhysicAtt = 0;
			nGemMagicAtt = 0;
			nGemPhysicDef =0;
			nGemAttSpeed = 0;
			nGemExact = 0;
			nGemDodge = 0;
			for (int n = 0; n < eElement_Max;n++)
			{
				nGemAtt[n] = 0;
				nGemDef[n] = 0;
			}
			nGemAddHp = 0;
			nGemAddMp = 0;
			nGemAddHpRestor = 0;
			nGemAddMpRestor = 0;
		}
		int nGemPhysicAtt;
		int nGemMagicAtt;
		int nGemPhysicDef;
		int nGemAttSpeed;
		int nGemExact ;
		int nGemDodge ;
		int nGemAtt[eElement_Max] ;
		int nGemDef[eElement_Max] ;
		int nGemAddHp ;
		int nGemAddMp ;
		int nGemAddHpRestor;
		int nGemAddMpRestor;
	};

    enum eLineType
    {
        ELINE_TYPE_NONE             = 0,
        ELINE_TYPE_ICON,
        ELINE_TYPE_LEFT_IMAGE,
        ELINE_TYPE_RIGHT_IMAGE,
        ELINE_TYPE_GIF,
        ELINE_TYPE_LINE,
        ELINE_TYPE_ICON_RIGHT_TEXT,
        ELINE_TYPE_IMAGE_RIGHT_TEXT,
        ELINE_TYPE_NORMAL_TEXT,
        ELINE_TYPE_MAX
    };

public:
	typedef void (*funRetrieveTimeString)( char * szBuffer, COLORREF& colTime, int nDay, int nHour, int nMinute, int nSecond );

	static void SetRetrieveTimeString( funRetrieveTimeString pFun ){ ms_pFunRetrieveTimeString = pFun; }	

	static funRetrieveTimeString ms_pFunRetrieveTimeString;

	typedef S_IconInfoBase* (*funcCreateIconInfo)();

	// added, jiayi, [2010/4/13]
	static void SetCreateIconInfoFunc( funcCreateIconInfo pFun ){ ms_pFuncCreateIconInfo = pFun; }	

	// added, jiayi, [2010/4/13]
	static funcCreateIconInfo ms_pFuncCreateIconInfo;

public:// Virtual Function
    virtual void SetUsableEffEnable( bool bEnable ) {}      //added by zhuomeng.hu		[11/25/2010]
	virtual unsigned short& Id() = 0;
	virtual int& Count() = 0;
	virtual bool& IsLocked() = 0;
	virtual int&  IsItemLocked() = 0;
	virtual int& MaxCount() = 0;
	virtual DWORD& SpareTime() = 0;
	virtual DWORD GetSpareTime() = 0;
	virtual bool& IsNextLvl() = 0;
	virtual bool IsNull() = 0;
	virtual unsigned short GetItemId(){ return 0; }
	virtual __int64 GetOnlyId(){ return 0; }
	virtual void SetOnlyId( __int64 nGuid ){}
	virtual void* GetData(){ return 0; }
	virtual bool SetData( IN void* pData, 
		const bool bShowCount = false,
		const bool bNext = false,
		bool bCompareData = false,
		IN int nPlayerID = -1 ) = 0;

	virtual bool SetData( const int nId, 
		const int nCount, 
		const bool bShowCount = false,
		const bool bNext = false, 
		IN INT nCompareId = 0xffff,
		IN int nPlayerID = -1,
		const bool bIsBound = false ) = 0;
	virtual bool operator==( IN S_IconInfoBase& stIconInfoBase ) = 0;
	virtual bool PlaySound() = 0;
	// added, jiayi, [2009/8/8]
	virtual void SetFlag( eTipFlag eFlag ) = 0;
	// added, jiayi, [2009/10/14]
	virtual void RefreshColorFrameType() = 0;

	virtual void SetSpareTime(DWORD dwSpareTime, int nStartTime ){}

	virtual void Clone( S_IconInfoBase* pkInfo );
	

public:// Virtual Function
	virtual std::string& IconFileName() = 0;
	virtual std::string& DisableIconFileName() = 0;
	virtual std::string& ShopIconFileName() = 0;

	virtual stIconInfo* GetIconInfoByIndex( int nIndex ) = 0;
	virtual stIconInfo* GetOtherIconInfoByIndex( int nIndex ) = 0;
	virtual int Cost() = 0;
	virtual void SetCost( int nCost ){}
	virtual void Clear();

public:
	virtual void DisplayIcon( IN RECT* prcDst, COLORREF col, int nFontIndex, int nFontSize, COLORREF colFont,
                                eIconDrawState bEnable = eIcon_Enable,ControlFrame* pFatherFrame = NULL );
	void DisplayInfo( IN RECT *prc, const bool bIsShop,
						const int nFontIndex, const int nFontSize, const COLORREF col,
						const bool bFaveFrame = true, const bool bShowAllInfo = true );
	RECT DisplayInfo( const int nX, const int nY, const bool bIsShop,
						const int nFontIndex, const int nFontSize, const COLORREF col,
						const bool bFaveFrame = true, const bool bShowAllInfo = true );	

	void DisplayInfo_Gif( RECT& rcRightText, RECT &rcText, stIconInfoEx * pInfo );
	void DisplayInfo_Image( RECT& rcRightText, stIconInfoEx* pInfo, RECT &rcText, const int nFontSize, RECT * prc );
	void DisplayInfo_Icon( RECT &rcIconText, RECT &rcText, stIconInfoEx* pInfo, const int nFontSize, int &nIconLeftSize,
        int &nIconRightSize, int &nIconHeightIncrease );
    void DisplayInfo_Line( RECT& rcText, stIconInfoEx* pInfo, RECT* prc );     // added by zhuomeng.hu	[11/30/2010]

	virtual void SetInfo( IN const char* szInfo, IN DWORD dwAlign = DT_CENTER | DT_VCENTER );
	void ClearOtherInfo();
	void SetOtherInfo( IN const char* szInfo, DWORD dwAlign = DT_LEFT );
	void SetFontSize(int size)	{ m_nFontSize = size; }
	int  CaculateWidthHeight( const int nFontSize, int nInfoFontIndex = -1 );
	void SetColorFrameType( eColorFrame eType ){ m_eColorFrameType = eType; }
	eColorFrame GetColorFrameType() const { return m_eColorFrameType; }
    virtual void EnableStatusBottomTime( bool bShow ){ m_bShowBottomTime = bShow; }  // added by zhuomeng.hu		[12/7/2010]
	

protected:
	// item level
	int		m_nItemLevel;
	eColorFrame m_eColorFrameType;  // 边框类型

	int		m_nIconPicId;
	int		m_nDisableIconPicId;
	int		m_nShopPicId;	        //在商店里面显示的Pic
	int     m_nIconLockId;
	int     m_nIconUnLockId;
	int		m_nNineGridPic;
    eLineType   m_eLastLineType;    // 上一行显示的类型，用于绘制右侧图片         added by zhuomeng.hu		[11/29/2010]
    stIconInfoEx* m_pLastPicInfo;   // 上一次显示图片的信息                       added by zhuomeng.hu		[11/29/2010]
    bool    m_bShowBottomTime;      // Buf底部是否显示持续时间                    added by zhuomeng.hu		[12/7/2010]

public:
	unsigned char  m_ucIconInfoLine;
	unsigned char  m_ucIconLine;    // icon在第几个	
	unsigned char  m_ucIconOtherInfoLine;
	unsigned short m_usByteMaxWidthCount;
	unsigned short m_usByteOtherInfoMaxWidthCount;
	bool m_bShowCount;

	unsigned short	m_usWidth;
	unsigned short	m_usHeight;
	int m_nFontSize;
	std::string m_strHotKey;

public:
	S_IconInfoBase();
	virtual ~S_IconInfoBase(){};

	std::string m_strIconBigImageFilename;
	unsigned char m_ucIconSize;
	unsigned short m_usIconImageRow;
	unsigned short m_usIconImageColumn;

	/// icon使用大图
	void SetIconImageInfo(std::string image, int iconSize, int row, int column)
	{
		m_strIconBigImageFilename = image;
		m_ucIconSize = iconSize;
		m_usIconImageRow = row;
		m_usIconImageColumn = column;
	}

private:
	void SetTextRect(int, int, RECT*);
};

//////////////////////////////////////////////////////////
class CIconInfoMouseTip
{
public:
	typedef void (*funRetrieveSpareTimeString)( S_IconInfoBase* pTip );

	static void SetRetrieveSpareTimeString( funRetrieveSpareTimeString pFun ){ ms_pFunRetrieveSpareTimeString = pFun; }	

	static funRetrieveSpareTimeString ms_pFunRetrieveSpareTimeString;

	void Render();
	void Clear();
	void SetDisplayInfo( S_IconInfoBase* pIconInfo,
						const int nX, const int nY,
						const bool bShowPrice,
						const int nFontIndex,
						const int nFontSize,
						const COLORREF col,
						const bool bShowAllInfo,
						S_IconInfoBase* pCompareIconInfo = 0 ,
						DWORD dwBeginShowTime = 0,
						int nDelayTime = 0,
						bool bForce = false,
						S_IconInfoBase* pSecondCompareIconInfo = NULL  //用于戒指，手镯比较
						);
	S_IconInfoBase*	GetCompareIconInfo(){ return m_pCompareIconInfo; }
	void SetSpareTimeToTip( S_IconInfoBase* pTip );

	S_IconInfoBase* GetIconInfo() const{ return m_pIconInfo; }

public:
	bool	m_bShopOpen;

private:
	// IconInfo
	S_IconInfoBase* m_pIconInfo;
	S_IconInfoBase* m_pCompareIconInfo;
	S_IconInfoBase* m_pSecondCompareIconInfo;
	S_IconInfoBase* m_pLastIconInfo;
	int		m_nInfoX;
	int		m_nInfoY;
	bool	m_bIsShop;
	int		m_nInfoFontIndex;
	int		m_nInfoFontSize;
	COLORREF m_colInfo;
	bool	m_bShowAllInfo;
	DWORD	m_dwBeginShowTime;
	int		m_nDelayTime;
	bool	m_bRedraw;

public:
	CIconInfoMouseTip(void);
};
extern CIconInfoMouseTip theIconInfoMouseTip;


class S_TextTipInfo : public S_IconInfoBase
{
public:
	virtual unsigned short& Id()	{ return m_nId;}
	virtual int& Count()			{ return m_nCount;}	
	virtual bool& IsLocked()		{ return m_bLocked;}
	virtual int&  IsItemLocked()    { return m_bItemLocked;}
	virtual int& MaxCount()			{ return m_nMaxCount;}
	virtual DWORD& SpareTime()		{ return m_dwSpareTime;}
	virtual DWORD GetSpareTime()		{ return 0; }
	virtual bool& IsNextLvl()		{ return m_bNextLvl;}
	virtual bool IsNull()			{ return true;}
	virtual bool SetData( IN void* pData, 
		const bool bShowCount = false,
		const bool bNext = false,
		bool bCompareData = false,
		IN int nPlayerID = -1 ) { return false;}

	virtual bool SetData( const int nId, 
		const int nCount, 
		const bool bShowCount = false,
		const bool bNext = false, 
		IN INT nCompareId = 0xffff,
		IN int nPlayerID = -1, 
		const bool bIsBound = false ) { return false;}
	virtual bool operator==( IN S_IconInfoBase& stIconInfoBase ) { return false;}
	virtual stIconInfo* GetIconInfoByIndex( int nIndex ){
		if( nIndex >= 0 && nIndex < m_stInfo.size() )
			return &m_stInfo[nIndex];
		return 0;
	}
	virtual stIconInfo* GetOtherIconInfoByIndex( int nIndex ){
// 			if( nIndex >= 0 && nIndex < m_stOtherInfo.size() )
// 				return &m_stOtherInfo[nIndex];
			return 0;
	}

	virtual bool PlaySound()	{ return false;}

	virtual void SetFlag( eTipFlag eFlag ){}
	virtual void SetInfo( IN const char* szInfo, IN DWORD dwAlign = DT_CENTER | DT_VCENTER );
	void RefreshColorFrameType(){}

public:// Virtual Function
	virtual std::string& IconFileName()		{ return m_strIconFileName; }
	virtual std::string& DisableIconFileName()	{ return  m_strDisableIconFileName; }
	virtual std::string& ShopIconFileName()		{ return m_strShopIconFileName; }
	virtual int Cost()	{ return m_nCost; }

public:
	S_TextTipInfo();
	void Clear();

	typedef std::vector<stIconInfo> IconInfoVector; 
	IconInfoVector m_stInfo;
	//IconInfoVector m_stOtherInfo;
// 	stIconInfo	m_stInfo[MAX_ICON_INFO_LINES_COUNT];
// 	stIconInfo	m_stOtherInfo[MAX_ICON_OTHER_INFO_LINES_COUNT];

	unsigned short m_nId;
	int m_nCount;	
	bool m_bLocked;
	int  m_bItemLocked;
	int m_nMaxCount;
	std::string m_strIconFileName;
	std::string m_strDisableIconFileName;
	std::string m_strShopIconFileName;
	std::string m_strSoundName;
	int m_nCost;
	DWORD	m_dwSpareTime;
	bool m_bNextLvl;
};
//////////////////////////////////////////////////////////


class IconManager
{
public:
	struct IconInfo
	{
		IconInfo()
		{
			itemId = 0;
			iconSize = 0;
			row = 0;
			column = 0;
		}

		int				itemId;
		std::string		image;		// icon使用的图片
		int				iconSize;	// icon的大小
		int				row;		// 对应图片的第几行，行高，列宽为iconSize
		int				column;		// 对应图片的第几列，行高，列宽为iconSize
	};
	typedef std::map<int, IconInfo> IconInfos;

	~IconManager() {}

	static IconManager& Get()
	{
		static IconManager s;
		return s;
	}

	bool Load(const std::string& filename);

	const IconInfo* GetIconInfo(int itemId)
	{
		IconInfos::iterator it = m_iconSets.find(itemId);
		if (it != m_iconSets.end())
			return &it->second;
		return 0;
	}

	std::map<int, IconInfo> m_iconSets;
	CMapStrToIDMgr			m_ImageFinder;

private:
	IconManager();
};
