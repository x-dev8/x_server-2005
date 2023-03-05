
#pragma once
#include "MeUi/ControlObject.h"
#include "MeUi/IconManager.h"

class ControlPicture : public ControlObject
{
public:
	typedef bool (*funOnButtonClick)( OUT ControlObject* pSender );
	typedef void (*funOnMouseOn) ( ControlObject* pSender );
	typedef void (*funOnMouseLeave)( ControlObject* pSender );
	typedef bool (*funOnLDBClick)( ControlObject* pSender );
	typedef bool (*funOnLButtonUpDown)( INT nX, INT nY );

public:
	// 初始化数据
	virtual void InitUIData( IN ControlObject* pFather, IN S_BaseData* pData );

	bool OnLButtonDown( UINT nFlags, const int nX, const int nY );
	bool OnRButtonUp( UINT nFlags, const int nX, const int nY );
    bool OnMouseMove( UINT nFlags, const int nX, const int nY );
	bool OnMouseLeave( UINT nFlags, const int nX, const int nY );
	bool OnLButtonDBClick( UINT nFlags, const int nX, const int nY );
	// 鼠标右键按下消息
	virtual bool OnRButtonDown( UINT nFlags, const int nX, const int nY );

	void	Create( ControlFrame* pFather,S_BaseData* pData,const char* pProcessName);

public:
	// 设置回调函数
	void SetButtonClickFun( IN funOnButtonClick pFun )	{ m_pFunOnButtonClick = pFun; }
	void SetFunOnRButtonUp(IN funOnLButtonUpDown val) { m_pFunOnRButtonUp = val; }
	void SetRClickFun( IN funOnLButtonUpDown pFun )	{ m_pFunOnRButtonClick = pFun; }
	void SetOnMouseOn( funOnMouseOn pFun )				{ m_pFunMouseOn = pFun;	}
	void SetOnMouseLeave( funOnMouseLeave pFun )		{ m_pFunMouseLeave = pFun; }
	void SetOnLDBClickFun( funOnLDBClick pFun )			{ m_pFunLDBClick = pFun; }

	void SetPicClickFun_2lua( const char* luaTable, const char* funName );
	void SetOnMouseOn_2lua( const char* luaTable, const char* funName );
	void SetOnMouseLeave_2lua( const char* luaTable, const char* funName );
	void SetOnLDBClickFun_2lua( const char* luaTable, const char* funName );

    void setTip(const char* data, DWORD dwAlign = DT_CENTER | DT_VCENTER);
    void setShowTip(bool show = true) { _bIsShowTip = show; }
    bool IsShowTip() const			  { return _bIsShowTip; }	
public:
	bool OnClick(void);

protected: // Tip 相关
	virtual const S_IconInfoBase* GetTipPointer() const{ return &TipInfo; }

private:
	funOnButtonClick	m_pFunOnButtonClick;
	funOnLButtonUpDown	m_pFunOnRButtonUp;
	funOnLButtonUpDown	m_pFunOnRButtonClick;
	funOnMouseOn		m_pFunMouseOn;
	funOnMouseLeave		m_pFunMouseLeave;
	funOnLDBClick		m_pFunLDBClick;

    S_TextTipInfo		TipInfo;	//tip 显示
    bool                _bIsShowTip;

	std::string		_luaTableName;

	std::string		_funOnButtonClickName;
	std::string		_funOnMouseOnName;
	std::string		_funOnMouseLeaveName;
	std::string		_funOnLDBClickName;

public:
	ControlPicture(void);
	~ControlPicture(void);
};
