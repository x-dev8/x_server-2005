///********************************************************************
//created:	2006/06/22
//purpose:	初衷用于超连接的对象控件 
//Describe:	能显示文字的UI控件无非Text和List，别的先不考虑处理
//			Text 和 List 的 S_List对象用 ControlLabel代替 可以显示超连接
//problem:	List想不到好的处理方法 聊天框用List控件 换行问题。
//*********************************************************************/
//
//#include "MeUi/ControlObject.h"
//
//class ControlLabel : public ControlObject
//{
//public://
//	ControlLabel();
//	~ControlLabel();
//
//	//typedef bool (*funOnButtonClick)( OUT ControlObject* pSender );
//
//public://operator function
//	virtual bool OnMouseMove( UINT nFlags, const int nX, const int nY );
//	virtual bool OnLButtonDown( UINT nFlags, const int nX, const int nY );
//	// 设置回调函数
//	//void SetButtonClickFun( IN funOnButtonClick pFun )	{ m_pFunOnButtonClick = pFun; }
//
//	void Render();
//
//public://storage function
//	void		SetText(const char* szText)			{ m_strText = szText;}
//	void		SetHyber(bool bHyber)				{ m_bHyber = bHyber; }
//	void		SetColor(const D3DCOLOR col = 0)	{ m_col = col; }
//	void		SetRect(const RECT& pRect)			{ m_rc = pRect; }
//
//	bool		IsHyber()	const					{ return m_bHyber;	}
//	const char* GetText()	const					{ return m_strText.c_str(); }	
//	const RECT&	GetRect()	const					{ return m_rc; }
//	const COLORREF&	GetColor()	const				{ return m_col; }
//	
//
//
//private:
//	//funOnButtonClick	m_pFunOnButtonClick;
//
//	RECT			m_rc;			//存储渲染得位置
//	bool			m_bHyber;		//这个Label是否超连接对象
//	std::string		m_strText;		//存储要显示的文字
//	COLORREF		m_col;			//颜色
//
//};