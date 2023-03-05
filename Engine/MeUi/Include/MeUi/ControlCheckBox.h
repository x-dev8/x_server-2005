
#pragma once
#include "MeUi/ControlObject.h"
#include "MeUi/ControlButton.h"

class ControlCheckBox : public ControlObject
{
public:
	typedef void (*funOnCheck)( OUT ControlObject* pSender, OUT IN bool* pbChecked );

public:	/*Virtual Function*/
	void Render();
	void InitUIData( IN ControlObject* pFather, IN S_BaseData* pData );
	bool OnLButtonDown( UINT nFlags, const int nX, const int nY );
	bool OnLButtonUp( UINT nFlags, const int nX, const int nY );

	bool OnMouseMove( UINT nFlags, const int nX, const int nY);

public:
	//	添加了设置状态图片的接口			added by zhuomeng.hu		[8/24/2010]
	void SetCheckPic( const char* szPath, const RECT* prcFrame, const RECT* prcClient );
	void SetUnCheckPic( const char* szPath, const RECT* prcFrame, const RECT* prcClient );
	void SetDisablePic( const char* szPath, const RECT* prcFrame, const RECT* prcClient );
	void SetMoveOnPic( const char* szPath, const RECT* prcFrame, const RECT* prcClient );

	// 设置回调函数
	void SetCheckFun( IN funOnCheck pFun )	{ m_pFunOnCheck = pFun; }
	void SetCheckFun_2lua( const char* luaTable, const char* funName );
	// 是否选中
	bool IsChecked() { return ((S_CheckBoxData*)m_pstData)->m_bChecked; }
	// 设置是否被选中
	void SetCheck( const bool bCheck );

	void SetShowTip(bool bShow = true)		{ m_bShowTip = bShow; }
	bool GetShowTip()						{ return m_bShowTip;  }
	void SetCaption( const char* szText );
    const char* GetCaption();
    void SetCaptionColor( DWORD dwColor );
    DWORD GetCaptionColor();

	virtual void SetEnable( bool b );

	virtual void ResetDevice();

protected: // Tip 相关
	virtual const S_IconInfoBase* GetTipPointer() const{ return &TipInfo; }

public:
	void OnCheck();

private:
	bool	m_bMouseMoveOn;
	bool	m_bShowTip;

	ControlButton	m_CheckButton;
	ControlButton	m_CheckMoveOnButton;
	funOnCheck		m_pFunOnCheck;

	std::string		_luaTableName;
	std::string		_funOnClickName;
	S_TextTipInfo		TipInfo;	//tip 显示
	void setTip(const char* data);
	void SetShowTips();
public:
	ControlCheckBox(void);
	~ControlCheckBox(void);
};

class ControlRadioGroup : public ControlGroup
{
public:
	ControlRadioGroup();
	virtual ~ControlRadioGroup();

	virtual void Clear();
	void AddRadio(ControlCheckBox* pControl);
	void ToggleRadio(ControlCheckBox* pControl);
	ControlCheckBox* GetSelectRadio() { return m_pSelectRadio; }

private:
	std::vector<ControlCheckBox*> m_vecRadioGroup;
	ControlCheckBox* m_pSelectRadio;
};
