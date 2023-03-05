#include "StdAfx.h"
#include "picturecontrol.h"
#include "PropertyDlg.h"

CPictureControl::CPictureControl(void)
{
	m_nType = Type_Picture;

	m_nWidth = 100;
	m_nHeight = 100;
	m_strID.Format( "ID_PICTURE_%d", rand() );

	m_ProPicture[Item_Picture_Comments_Event].SetItem( PIT_COMMENTS, "<Event>", NULL );
	m_ProPicture[Item_Picture_OnClick].SetItem( PIT_EDIT, "OnClick", &m_OnClickName );
	m_ProPicture[Item_Picture_MouseOn].SetItem( PIT_EDIT, "MouseOn", &m_MouseOnName );
	m_ProPicture[Item_Picture_MouseLeave].SetItem( PIT_EDIT, "MouseLeave", &m_MouseLeaveName );
	m_ProPicture[Item_Picture_LDBClick].SetItem( PIT_EDIT, "LDBClick", &m_LDBClickName );
}

CPictureControl::~CPictureControl(void)
{
}

void CPictureControl::AddToPropertyDlg()
{
	CBaseControl::AddToPropertyDlg();
	for( int n=0; n<Item_Picture_Max; n++ )
	{
		thePropertyDlg.AddItem( &m_ProPicture[n] );
	}
}
void CPictureControl::GetData_Event( int index )
{
	stUIData.SetEventFunName( index, EET_Picture_OnClick, m_OnClickName.GetBuffer() );
	stUIData.SetEventFunName( index, EET_Picture_MouseOn, m_MouseOnName.GetBuffer() );
	stUIData.SetEventFunName( index, EET_Picture_MouseLeave, m_MouseLeaveName.GetBuffer() );
	stUIData.SetEventFunName( index, EET_Picture_LDBClick, m_LDBClickName.GetBuffer() );
}