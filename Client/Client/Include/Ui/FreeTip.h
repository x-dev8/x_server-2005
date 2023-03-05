#pragma once

#include "MeUI/ControlIconDrag.h"
#include "ItemDetail.h"

typedef enum
{
	FS_INVALID = -1,

	FS_LBUTTON_DOWN,

	FS_MAX
} FreeTipState;

typedef enum
{
	POS_INVALID = -1,

	POS_MID,
	POS_RIGHT,
	POS_LEFT,

	POS_MAX
} FreeTipPos;

class FreeTip
{
public:
	FreeTip();
	virtual ~FreeTip();
	void ShowItemTip( bool bShow = true );
	bool IsVisible() const { return m_bShowTip; }
	void Render( int nFontIndex, int nFontSizeScaled, DWORD dwFontColor );
	void SetData( SCharItem* pItem, int nMouseX, int nMouseY, bool bCompare = false, bool isShowClose = true );	
	void SetSkillData(  /*SCharSkill* pSkill*/int skillId, /*ItemDefine::SItemSkill* pItemSKill*/int skillLvl,  int nMouseX, int nMouseY, bool bCompare = false, bool isShowClose = true );
	bool PtInCloseBtn( int nMouseX, int nMouseY );

	// �ж�ָ�����Ƿ���FreeTip�ľ�������
	bool			IsPtInArea( int x, int y );

	// ����״̬
	void			SetState( FreeTipState state );
	FreeTipState	GetState();

	// ����tipλ��ID���У��ң���
	void			SetPosId( FreeTipPos id );
	FreeTipPos		GetPosId() const;

	// ����tip��ʾ��
	void			SetTipPos( int x, int y );

	// �ƶ��¼�����
	void			MoveBeginProc( int x, int y );
	void			MoveProc( int x, int y );
	void			MoveEndProc( int x, int y );

	// �õ�tip�Ŀ�͸�
	int				GetFreeTipW() const;
	int				GetFreeTipH() const;


protected:
	bool RetrieveCompareItem( SCharItem* pItem );

protected:
	bool m_bShowTip;
	ControlIconDrag::S_ListImg* m_pkShowItemTip;	
	ControlIconDrag::S_ListImg* m_pkShowItemTipCompare;

	bool			m_bHaveCompareItem;
	int				m_nTipX;
	int				m_nTipY;
	RECT			m_rcLastRect;
	
	FreeTipState	mState;
	POINT			mNotePt;

	FreeTipPos		mId;
	bool			mIsShowClose;
	
};

inline bool FreeTip::IsPtInArea( int x, int y )
{
	if ( IsVisible()
		&& x > m_rcLastRect.left && x < m_rcLastRect.right 
		&& y > m_rcLastRect.top && y < m_rcLastRect.bottom )
	{
		return true;
	}

	return false;
}

inline void FreeTip::MoveProc( int x, int y )
{
	if ( IsVisible() )
	{
		int offsetX = x - mNotePt.x;
		int offsetY = y - mNotePt.y;

		m_nTipX = m_nTipX + offsetX;
		m_nTipY = m_nTipY + offsetY;

		mNotePt.x = x;
		mNotePt.y = y;
	}
}


