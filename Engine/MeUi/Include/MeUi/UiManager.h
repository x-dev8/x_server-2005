
#pragma once

#include "MeUi/UiPicture.h"
#include "MeUi/ControlFrame.h"
#include "MeUi/ControlIconDrag.h"
#include "MeUi/ControlCheckBox.h"
#include "MeUi/ControlComboBox.h"
#include "MeUi/ControlScrollBarEx.h"
#include "MeUi/ControlText.h"
#include <windows.h>
#include <vector>
class CSmartAniManage;
enum UI_Render_Layer
{
	UI_Render_LayerFirst = 0,
	UI_Render_LayerSecond,
	UI_Render_LayerThree,
	UI_Render_LayerFour,
	UI_Render_LayerMax
};

class UiManager
{
public:
	typedef bool (*funPlaySound)( const char *name, D3DXVECTOR3* vPos ,bool bLoop);
	typedef void (*funLogInfo)( const char *name );
	typedef bool (*funRButtonUp)(int x, int y);
	typedef HWND (*funcCreateHelpWindow)();

public:
	struct S_UI : public MeCommonAllocObj<UiManager::S_UI>
	{
		S_UI();
		~S_UI();
		void Release()
		{
			if ( ( m_bNeedRelease == true ) && m_pUI )
			{
				m_pUI->ReleaseUI();
				delete m_pUI;
				m_pUI = NULL;
			}
		}

		std::string		m_strFileName;
		ControlFrame	*m_pUI;
		bool			m_bNeedRelease;
	};

public:
	// 与D3D框架接口一样
	/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
	void	FrameMove();
	void	Render();
	void	RenderTips();
	void	ReDrawAllFrame();
	//void	InitDeviceObjects( IN UiDrawer::funRegisterTexture pRegisterTexture,
	//							IN UiDrawer::funUnregisterTexture pUnregisterTexture,
	//							IN UiDrawer::funBlt pBlt,
	//							IN UiDrawer::funDrawRect2D pDrawRect2D,
	//							IN UiDrawer::funFillRect2DEx pFillRect2D,
	//							IN UiDrawer::funDrawProgressRect pDrawProgressRect,
	//							IN UI_FONT::funCreateFont pCreateFont,
	//							IN UI_FONT::funReleaseFonts pReleaseFonts,
	//							IN UI_FONT::funDrawTextARGB pDrawTextARGB,
	//							IN UI_FONT::funDrawTextARGBEx pDrawTextARGBEx );
	void	InitDeviceObjects( IN UiDrawer::funRegisterTexture pRegisterTexture,
//                                 IN UiDrawer::funRegisterTextureFromFileMem pRegisterTextureFromFileMem,
								IN UiDrawer::funUnregisterTexture pUnregisterTexture,
								IN UiDrawer::funBlt pBlt,
								IN UiDrawer::funDrawRect2D pDrawRect2D,
								IN UiDrawer::funFillRect2DEx pFillRect2D,
								IN UiDrawer::funDrawProgressRect pDrawProgressRect );
	void	InvalidateDeviceObjects();
	void	RestoreDeviceObjects();
	void	SetUIAdjustScale(float fScale);
	bool	MsgProc( HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam );
	/* =-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-= */
	void	SetPlaySoundFun( IN funPlaySound pFun );
	void	SetRButtonUp( IN funRButtonUp pFun );
	void	SetCreateHelpWindowFun( IN funcCreateHelpWindow pFun );

	void    SetPlaySoundFun_2lua( const char* luaTable, const char* funName );
	void	SetLogInfoFun_2lua( const char* luaTable, const char* funName );


	bool	PlaySound( std::string& strFileName );

	//DWORD	ReAddTopFrame();	//接口变了 要用这个函数 需实现新的
	DWORD	 AddFrame( IN const char* szFileName, bool bAllVisable = false, UI_Render_Layer layer = UI_Render_LayerFirst );
    DWORD	 AddFrame( IN const char* szZipFileName,IN const char* szFileName, bool bAllVisable = false, UI_Render_Layer layer = UI_Render_LayerFirst );
    bool	RemoveFrame( IN const char* szFileName );
	bool	AddFrame( IN ControlFrame* pObject, bool bAllVisable = false, UI_Render_Layer layer = UI_Render_LayerFirst );

	bool	RemoveFrame( IN const ControlFrame* pObject );
	ControlFrame*	AddFrameByIndex( IN const char* szFileName,int index= 0, bool bAllVisable = false, UI_Render_Layer layer = UI_Render_LayerFirst );

	// 是否有模式窗口
	bool	HasModalWindow(int layer);	//需要判断哪一层有没有modalwindow

	// Frame
	static bool OnFrameRun( IN const char *szFrameID, IN ControlFrame::funRun pFun );
	static bool OnFrameRender( IN const char *szFrameID,
								IN ControlFrame::funRender pFun,
								const bool bBeforeRender = false );
	static bool OnFrameRunIndexedFrame( IN const char *szFrameID, IN ControlFrame::funRunIndexedFrame pFunIndexedFrame );
	static bool OnFrameRenderIndexedFrame( IN const char *szFrameID,
		IN ControlFrame::funRenderIndexedFrame pFunIndexedFrame,
		const bool bBeforeRender = false );
	// Button
	static bool	OnButtonClick( IN const char *szFrameID, IN const char *szControlID,
		IN ControlButton::funOnButtonClick pFun );
	static bool	OnButtonMouseMove( IN const char *szFrameID, IN const char *szControlID,
		IN ControlButton::funOnMouseOn pFun );
	// Edit
	static bool OnEditEnter( IN const char *szFrameID, IN const char *szControlID,
									IN ControlEdit::funOnEnter pFun );
	// CheckBox
	static bool OnCheckBoxCheck( IN const char *szFrameID, IN const char *szControlID,
									IN ControlCheckBox::funOnCheck pFun );
	// List
	static bool OnListSelectChange( IN const char *szFrameID, IN const char *szControlID,
									IN ControlList::funSelectChange pFun );
	static bool OnListLDBClick( IN const char *szFrameID, IN const char *szControlID,
									IN ControlList::funMouseClick pFun );
	// ListImg / ListEx
	static bool OnIconDragOn( IN const char *szFrameID, IN const char *szControlID,
									IN ControlIconDrag::funDragOn pFun );
	static bool OnIconDisableDragOn( IN const char *szFrameID, IN const char *szControlID,
								IN ControlIconDrag::funDragOn pFun );
	static bool OnIconDisableDragOut( IN const char *szFrameID, IN const char *szControlID,
								IN ControlIconDrag::funDragOut pFun );
	//static bool OnIconDragOff( IN const char *szFrameID, IN const char *szControlID,
	//								IN ControlIconDrag::funDragOff pFun );
	static bool OnIconLDBClick( IN const char *szFrameID, IN const char *szControlID,
		IN ControlIconDrag::funLDBClick pFun );
	static bool OnIconButtonClick( IN const char *szFrameID, IN const char *szControlID,
		IN ControlIconDrag::funOnButtonClick pFun );
	static bool OnIconRButtonUp( IN const char *szFrameID, IN const char *szControlID,
		IN ControlIconDrag::funRButtonUp pFun );
	// ScrollBar
	static bool OnScrollBarUpdatePos( IN const char *szFrameID, IN const char *szControlID,
									IN ControlScrollBar::funUpdatePos pFun );
	// ScrollBar
	static bool OnScrollBarExUpdatePos( IN const char *szFrameID, IN const char *szControlID,
									IN ControlScrollBar::funUpdatePos pFun );
	// ComboBox
	static bool OnComboBoxChange( IN const char *szFrameID, IN const char *szControlID,
									IN ControlComboBox::funOnChange pFun );
	//text hyber click
	static bool OnTextHyberClick( IN const char *szFrameID, IN const char *szControlID,	IN ControlText::funHyberClick pFun);
	static ControlObject* FindControl( IN const char *szFrameID, IN const char *szControlID );
	static ControlObject* FindFrame( IN const char *szFrameID );

	//创建控件 目的用于 支持动态创建控件
	ControlObject* CreateWidget( S_BaseData* sBaseData, ControlObject* pFather);

public:
	void Compositor();									// 排序
	ControlObject* ToTop( IN const ControlObject* pObject, ControlObject* pObjectPos = NULL, int toIndex = 0 );
	ControlObject* ToBottom( IN const ControlObject* pObject );
	//
	bool IsMouseInUI(){ return m_bIsMouseInUI; }
	//
	ControlObject* GetFrameFocus();

	bool ReSetWindowPosNoAllVisable(); //lyh++ ,处理控件在窗口边缘的时候，然后切换到小的分辨率，ui会显示在窗口外边
	bool HideAllDlgNoAllVisable();	//处理关闭所有正在显示的界面（不包括AllVisable界面）lyh++
	bool HideDlg();	//to zizi ： 这里处理esc关闭一个界面的操作 返回false说明没有界面可以关闭 则弹出system界面（不包括AllVisable界面）
	void SetFocus(ControlObject* pObj);
	ControlObject* GetFocus()	{ return m_pFocus; }

//     void SetCapture(ControlObject* capture) {
//         m_pCaptureObj = capture;
//     }
// 
//     ControlObject* GetCapture() {
//         return m_pCaptureObj;
//     }

	bool	isInUI( int x, int y );

	void SetJumpNextLButtonUp(bool val) { m_bJumpNextLButtonUp = val; }


public:
	void UpdataFrame( const int nX, const int nY );
	void Cover();

public:
	ControlObject				*m_pFatherFocus;
	POINT						m_ptMoust;

public:
	static std::string			m_strButtonClickSound;
	static std::string			m_strMoveOnSound;
	static std::string			m_strCheckBoxSound;
	static std::string			m_strIconDragSound;
	static std::string			m_strListSound;
	static std::string			m_strScrollBarSound;
	static std::string			m_strCloseSound;

	static funLogInfo			m_pLogInfoFun;
	static funRButtonUp			m_pRButtonUpFun;
	static funcCreateHelpWindow	m_pCreateHelpWindowFun;

	std::vector< std::vector<S_UI*> >&	getUIVec()
	{
		return m_vtUI;
	}
private:
	ControlObject*				m_pFocus;
//     ControlObject*              m_pCaptureObj;

	std::vector< std::vector<S_UI*> >	m_vtUI;
	//static std::vector<S_UI>	m_vtUI;		//初次设计为ui第一层渲染得dlgs
	//static std::vector<S_UI>	m_vtUI2;	//初次设计为ui第二层渲染得dlgs
	//static std::vector<S_UI>	m_vtUI3;	//初次设计为ui第三层渲染得dlgs


	bool						m_bDragFrame;
	bool						m_bIsMouseInUI;
	//
	funPlaySound				m_pPlaySoundFun;

	std::string		_luaTableName;

	std::string		_funPlaySoundName;
	std::string		_funLogInfoName;
	
	/* 补丁，RemoveFrame的时候不能release UI，因为退出到登陆界面时释放的UI没有被重新加载，
	所以把需要释放的资源保存在列表里，最后统一释放[QL]*/
	std::vector<S_UI*> m_vtNeedRelease;

	void InsertNewFrame( UI_Render_Layer layer, S_UI* stUI );

public:
	UiManager(void);
	~UiManager(void);
	void Destroy();
	void DestroyNeedRelease();


	// 设置对话框布局，达到界面互斥效果
public:
	void SetFrameLayout(int nLayoutIndex, ControlFrame* pFrame);
	void RemoveFrameLayout(ControlFrame* pFrame);

	void ShowFrame(ControlFrame* pFrame);

private:
	std::map<ControlFrame*, int>		m_FrameLayoutIndexSet;
	std::multimap<int, ControlFrame*>	m_LayoutIndexFrameSet;

	bool	m_bJumpNextLButtonUp;
};

extern UiManager theUiManager;


namespace irr
{
	UiManager*	UiManagerInstance();
};

//////////////////////////////////////////////////////////////////////////
//
#define MAP_FRAME_RUN( classname, fun )									\
bool classname##fun()													\
{																		\
	return classname.fun();												\
}
//
#define MAP_FRAME_RENDER( classname, fun )								\
bool classname##fun()													\
{																		\
	return classname.fun();												\
}
//
#define MAP_FRAME_RUN_INDEX( classname, fun )									\
	bool classname##fun(int index)													\
{																		\
	return classname.fun(index);												\
}
//
#define MAP_FRAME_RENDER_INDEX( classname, fun )								\
	bool classname##fun(int index)													\
{																		\
	return classname.fun(index);												\
}
//
#define MAP_BUTTON_CLICK_CALLBACK(classname,fun)						\
bool classname##fun( OUT ControlObject* pSender )						\
{																		\
	return classname.fun( pSender );									\
}
//
#define MAP_EDIT_ENTER_CALLBACK( classname, fun )						\
void classname##fun( OUT ControlObject* pSender,						\
					OUT const char *szData )							\
{																		\
	classname.fun( pSender, szData );									\
}
//
#define MAP_CHECK_BOX_CHECK_CALLBACK( classname, fun )					\
void classname##fun( OUT ControlObject* pSender,						\
					OUT IN bool* pbChecked )							\
{																		\
	classname.fun( pSender, pbChecked );								\
}
//
#define MAP_LIST_SELECT_CHANGE_CALLBACK( classname, fun )				\
void classname##fun( OUT ControlObject* pSender,						\
					OUT IN ControlList::S_List* pItem )					\
{																		\
	classname.fun( pSender, pItem );									\
}
//
#define MAP_LIST_LDB_CLICK_CALLBACK( classname, fun )					\
void classname##fun( OUT ControlObject* pSender,						\
					OUT IN ControlList::S_List* pItem )					\
{																		\
	classname.fun( pSender, pItem );									\
}
//
#define MAP_ICON_DRAG_ON_CALLBACK( classname, fun )						\
bool classname##fun( OUT ControlObject* pSender,						\
					OUT ControlObject* pMe,								\
					OUT IN ControlIconDrag::S_ListImg* pItemDrag,		\
					OUT IN ControlIconDrag::S_ListImg* pItemSrc )		\
{																		\
	return classname.fun( pSender, pMe, pItemDrag, pItemSrc);			\
}
//
#define MAP_ICON_DRAG_OFF_CALLBACK( classname, fun )					\
bool classname##fun( OUT ControlObject* pSender,						\
					OUT ControlObject* pMe,								\
					OUT IN ControlIconDrag::S_ListImg* pItem )			\
{																		\
	return classname.fun( pSender, pMe, pItem );						\
}

#define MAP_ICON_DRAG_DISABLE_ON_CALLBACK( classname, fun )								\
bool classname##fun( OUT ControlObject* pSender,						\
					OUT ControlObject* pMe,								\
					OUT IN ControlIconDrag::S_ListImg* pItemDrag,		\
					OUT IN ControlIconDrag::S_ListImg* pItemSrc )		\
{																		\
	return classname.fun( pSender, pMe, pItemDrag, pItemSrc);			\
}

#define MAP_ICON_DRAG_DISABLE_OUT_CALLBACK( classname, fun )			\
bool classname##fun( OUT ControlObject* pSender,						\
					 OUT IN ControlIconDrag::S_ListImg* pItem )		    \
{																		\
	return classname.fun( pSender, pItem );			\
}


#define MAP_ICON_DRAG_DISABLE_OFF_CALLBACK( classname, fun )							\
bool classname##fun( OUT ControlObject* pSender,						\
					OUT ControlObject* pMe,								\
					OUT IN ControlIconDrag::S_ListImg* pItemDrag,		\
					OUT IN ControlIconDrag::S_ListImg* pItemSrc )		\
{																		\
	return classname.fun( pSender, pMe, pItemDrag, pItemSrc);			\
}
//
#define MAP_ICON_LDB_CLICK_CALLBACK( classname, fun )					\
bool classname##fun( OUT ControlObject* pSender,						\
					OUT IN ControlIconDrag::S_ListImg* pItem )			\
{																		\
	return classname.fun( pSender, pItem );								\
}
//
#define MAP_ICON_RBUTTON_UP_CALLBACK( classname, fun )					\
bool classname##fun( OUT ControlObject* pSender,						\
					OUT IN ControlIconDrag::S_ListImg* pItem )			\
{																		\
	return classname.fun( pSender, pItem );								\
}
//
#define MAP_ICON_BUTTON_CLICK_CALLBACK( classname, fun )				\
	bool classname##fun( OUT ControlObject* pSender,					\
	OUT IN ControlIconDrag::S_ListImg* pItem )							\
{																		\
	return classname.fun( pSender, pItem );								\
}
//
#define MAP_SCROLL_BAR_UPDATE_POS_CALLBACK( classname, fun )			\
void classname##fun( OUT ControlObject* pSender, int n )				\
{																		\
	classname.fun( pSender, n );										\
}
//
#define MAP_SCROLL_BAREX_UPDATE_POS_CALLBACK( classname, fun )			\
void classname##fun( OUT ControlObject* pSender, int n )				\
{																		\
	classname.fun( pSender, n );										\
}
//
#define MAP_COMBO_BOX_CHANGE_CALLBACK( classname, fun )					\
void classname##fun( OUT ControlObject* pSender,						\
					OUT const char* szData )							\
{																		\
	classname.fun( pSender, szData );									\
}
#define MAP_TEXT_HYBER_CLICKBACK( classname, fun)						\
void classname##fun( OUT ControlObject* pSender,						\
					OUT const char* szData )							\
{																		\
	classname.fun( pSender, szData);									\
}