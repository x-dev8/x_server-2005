/********************************************************************
	Created by UIEditor.exe
	FileName: E:\work\YiQiDangQian\Program\trunk\Bin\Client\Data\Ui\Hole.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"

#include "EquipEvolve.h"
class GemBaseUI : public EquipEvolveUI
{
	// Member
public:	
	 GemBaseUI();
	 ControlPicture*	m_pID_PICTURE_Open1;
	 ControlPicture*	m_pID_PICTURE_Open2;
	 ControlPicture*	m_pID_PICTURE_Open3;
	 ControlPicture*	m_pID_PICTURE_Open4;
	 ControlListImage*	m_pID_LISTIMG_Hole1;
	 ControlListImage*	m_pID_LISTIMG_Hole2;
	 ControlListImage*	m_pID_LISTIMG_Hole3;
	 ControlListImage*	m_pID_LISTIMG_Hole4;
	 ControlPicture*	m_pID_PICTURE_Lock1;
	 ControlPicture*	m_pID_PICTURE_Lock2;
	 ControlPicture*	m_pID_PICTURE_Lock3;
	 ControlPicture*	m_pID_PICTURE_Lock4;


protected:
	static	const int   m_nMaxHoleNum = SCharItem::EConstDefine_GemHoleMaxCount - 2; //打孔数2个，lrt


	virtual void ResetUIObjects();
	virtual void ClearEquip();
	virtual void _RefreshEquipInfo( ControlIconDrag::S_ListImg*  pListImg );

	virtual void RefreshDragEnable( SCharItem* pItem, int index );
	void InitializeGemBase();
	bool _IsFullHole( ControlIconDrag::S_ListImg * pImg );

	ControlPicture*		m_UnHolePic[m_nMaxHoleNum];
	ControlPicture*		m_HoledPic[m_nMaxHoleNum];
	ControlListImage*	m_pID_LISTIMG_Hole[m_nMaxHoleNum];

	short				m_GemHoleIndex; //宝石已经镶嵌的位置

};

void		FillGemInfoInList(uint16 gemId,ControlList* pList);

