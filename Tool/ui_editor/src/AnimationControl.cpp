#include "StdAfx.h"
#include "animationcontrol.h"
#include "PropertyDlg.h"
#include "UIObjectDlg.h"

CAnimationControl::CAnimationControl(void)
{
	m_nType = Type_Animation;

	m_nWidth = 24;
	m_nHeight = 24;
	m_strID.Format( "ID_ANIMATION_%d", rand() );

	m_nCInterval = 50;
	m_nCAutoStart.SetData( "False", "True|False|" );
	m_nInterval.SetItem( PIT_NUM, "时间间隔", &m_nCInterval );
	m_nAutoStart.SetItem( PIT_COMBO, "自动播放", &m_nCAutoStart );

	char tmp[32];
	for(int i=0;i<Item_Picture_Max;++i)
	{
		sprintf(tmp,"Frame%d",i);
		m_ProPicture[i].SetItem( PIT_DIALOG, tmp, &m_PictureDlg[i] );
	}
}

CAnimationControl::~CAnimationControl(void)
{
}

void CAnimationControl::AddToPropertyDlg()
{
	CBaseControl::AddToPropertyDlg();


	thePropertyDlg.AddItem( &m_nInterval );
	thePropertyDlg.AddItem( &m_nAutoStart );

	for( int n=0; n<Item_Picture_Max; n++ )
	{
		thePropertyDlg.AddItem( &m_ProPicture[n] );
	}
}
void CAnimationControl::AddToUIObjectDlg()
{
	CBaseControl::AddToUIObjectDlg();
	for(int i=0;i<Item_Picture_Max;++i)
	{
		theUIObjectDlg.AddPictuer( m_PictureDlg[i].GetCurSelPicName() );
	}
}

bool CAnimationControl::SetData( const S_BaseData* /*[In]*/pData )
{
	assert( pData );
	S_AnimationData *pAnimationControl = (S_AnimationData*)pData;

	m_nCInterval = pAnimationControl->m_nInterval;

	if(pAnimationControl->m_bAutoStart)
		m_nCAutoStart.m_curValue = "True";
	else
		m_nCAutoStart.m_curValue = "False";

	for(int i=0;i<Item_Picture_Max;++i)
	{
		m_PictureDlg[i].SetPicStruct( &pAnimationControl->m_stAnimationPic[i] );
	}

	return CBaseControl::SetData( pData );
}

bool CAnimationControl::GetData( S_BaseData* /*[Out]*/pData )
{
	assert( pData );
	S_AnimationData *pAnimationControl = (S_AnimationData*)pData;

	 pAnimationControl->m_nInterval = m_nCInterval;
	 if(m_nCAutoStart.m_curValue=="True")
		 pAnimationControl->m_bAutoStart = true;
	 else
		 pAnimationControl->m_bAutoStart = false;

	for(int i=0;i<Item_Picture_Max;++i)
	{
		pAnimationControl->m_stAnimationPic[i].SetPicStruct( m_PictureDlg[i].GetCurSelPicName(),
			&m_PictureDlg[i].GetFrameRect(),
			&m_PictureDlg[i].GetClientRect() );
	}

	return CBaseControl::GetData( pData );
}