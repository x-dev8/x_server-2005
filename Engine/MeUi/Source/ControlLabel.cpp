//#include "MeUi/ControlLabel.h"
//#include "MeUi/MouseManager.h"
//
//const DWORD HYBER_MOUSEON			= 0xFFFFFFFF;//0xFF008EBF;
//const DWORD HYBER_MOUSELEVEL		= 0xFF0000FF;
//
//ControlLabel::ControlLabel() : m_bHyber(false)
//{
//	memset( &m_rc, 0, sizeof(RECT));
//	m_strText.clear();
//}
//
//ControlLabel::~ControlLabel()
//{
//
//}
//
//bool ControlLabel::OnMouseMove( UINT nFlags, const int nX, const int nY )
//{
//	if(IsVisable())
//	{
//		if(m_bHyber)
//		{
//			//加入鼠标的变化 
//			if( PtInObject(nX, nY) == true )
//			{
//				//SetColor(HYBER_MOUSEON);
//				//theMouseManager.SetCursor(MouseManager::Type_Group);
//			}
//			else
//			{
//				SetColor(HYBER_MOUSELEVEL);
//				theMouseManager.SetCursor(MouseManager::Type_Arrow);
//			}
//		}
//	}
//	return true;
//}
//bool ControlLabel::OnLButtonDown( UINT nFlags, const int nX, const int nY )
//{
//	if(m_bHyber)
//	{//这里
//	}
//	return true;
//}
//
//void ControlLabel::Render()
//{
//	if(IsNeedRender())
//	{
//		ControlObject::Render();
//		
//		UI_FONT::DrawTextARGB( &m_rc, m_strText.c_str(), m_col, m_nFontIndex, 0, -1 );
//		//Text下面的横线
//	}
//}