
#pragma once
#include "MeUi/ControlObject.h"
#include "MeUi/IconManager.h"

class ControlButton : public ControlObject
{
public:
	typedef bool (*funOnButtonClick)( OUT ControlObject* pSender );
	typedef bool (*funOnLButtonDown)( INT nX, INT nY );
	typedef bool (*funOnLButtonUp)( INT nX, INT nY );
	typedef void (*funOnMouseOn)( OUT ControlObject* pSender );

public:	/*Virtual Function*/
	void Render();
	bool OnKeyDown( UINT nChar );
	bool OnKeyUp( UINT nChar );
	bool OnMouseMove( UINT nFlags, const int nX, const int nY );
	bool OnLButtonDown( UINT nFlags, const int nX, const int nY );
	bool OnLButtonUp( UINT nFlags, const int nX, const int nY );
	void InitUIData( IN ControlObject* pFather, IN S_BaseData* pData );

public:
	// ���ûص�����
	void SetButtonClickFun( void* pFun );
	void SetLButtonDownFun( funOnLButtonDown pFun );
	void SetLButtonUpFun( funOnLButtonUp pFun );
	void SetButtonClickFun_2lua( const char* luaTable, const char* funName );
	void SetButtonMouseOnFun( IN funOnMouseOn pFun);
	void SetButtonMouseOnFun_2lua( const char* luaTable, const char* funName );
	void SetFunOnMouseOn(funOnMouseOn val) { m_pFunOnMouseOn = val; }
	// ���ð���ʱͼƬ
	void SetPressPic();
	// ������ͨʱͼƬ
	void SetNormalPic();
	//������ͨ��ͨ�ýӿ�,true Ϊ��ͨʱ����Ƭ��falseΪ����ʱ����Ƭ��
	//�Ժ�˽ӿڿ�����չ�����ø����״̬,����: unsigned int;
	void SetBtnPicture(bool  Key_ = true) { Key_ == true ? SetNormalPic():SetPressPic() ; }
	// �Ƿ�������
	bool IsDrag(){ return m_bLButtonDrag; }
	void SetDrag(bool v) { m_bLButtonDrag = v; }
	// ����
	void Create( IN const char* szCaption, IN const RECT* pRect,
				IN funOnButtonClick pCallbackFun = NULL );
	//
	//void SetShowTip( const bool b ){ m_bShowTip = b; }
	//
	virtual void SetEnable( bool b );
	//
	bool IsPress(){ return m_bIsPress; }
	//�Ƿ���MouseMove��Ϣ
	void SetMouseMove(bool bMove);
	void SetCaption(const char* strObjName);
	const char* GetCaption( void ) { return m_strObjName.c_str(); }
	//�������tip
	const char* GetRealCaption(void){return GetData()->m_szCaption;}

	void		SetState(BtnState nState)	{ _State = nState;	}
	BtnState	GetState() const			{ return _State;	}

	S_ButtonData::S_Pic*	getMouseMovePic();
	S_ButtonData::S_Pic*	getMousePressPic();
	S_ButtonData::S_Pic*	getDisabledPic();
	S_ButtonData::S_Pic*	getBgPic();

	void		setMouseMovePic( S_ButtonData::S_Pic* pic );
	void		setMousePressPic( S_ButtonData::S_Pic* pic );
	void		setDisabledPic( S_ButtonData::S_Pic* pic );
	void		setBgPic( S_ButtonData::S_Pic* pic );

	void		SetShowTip(bool show = true) { _bIsShowTip = show; }
	void		setTip(const char* data);
    void        setFontCurrentColor( DWORD color ) { m_colFontCurr = color; }

	virtual void ResetDevice();

protected: // Tip ���
	virtual const S_IconInfoBase* GetTipPointer() const{ return &TipInfo; }

public:
	void OnButton(void);

public:
	std::string		m_strMoveOnSound;	// ����

private:
	bool	m_bLButtonDrag;
	bool	m_bMouseMoveOn;
	//bool	m_bShowTip;
	bool	m_bIsPress;
	bool	m_bMouseMove;
	funOnButtonClick	m_pFunOnButtonClick;
	funOnLButtonDown	m_pFunOnLButtonDown;
	funOnLButtonUp		m_pFunOnLButtonUp;
	funOnMouseOn		m_pFunOnMouseOn;
	std::string			m_strObjName;

	bool				_bIsShowTip;
	S_TextTipInfo		TipInfo;	//tip ��ʾ

	BtnState	_State;		//����״̬

	std::string		_luaTableName;

	std::string		_funBtnClickName;
	std::string		_funMouseOnName;

	int m_nFontIndexNormal;
	int m_nFontIndexMoveOn;
	int m_nFontIndexPressed;
	int m_nFontIndexDisabled;

	COLORREF m_colFontCurr;
	int m_nFontIndexCurr;

	int CreateFont(char* szFont, int nFontSize, COLORREF& col, BOOL isBold);
	void SetShowTips();
	
public:
	ControlButton(void);
	~ControlButton(void);
};

