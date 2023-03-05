#ifndef ICONMGRBESTEQUIP_H
#define ICONMGRBESTEQUIP_H

#include "Ui\IconManagerClient.h"

const int MAX_STR_COUNT = 50;

enum BestEquipFlag
{
	FLAG_HIDEING,
	FLAG_SHOWING
};

class IconMgrBestEquip : public Singleton<IconMgrBestEquip>
{
public:

	enum
	{
		OFFSET_W = 5,
		OFFSET_H = 5,
		OFFSET_LINE = 5
	};

	~IconMgrBestEquip();

	void	SetData( EArmType CareerId, EEquipPartType PartId, int Level );

	void	SetVisable( bool isShow ){ mIsShow = isShow; }
	
	POINT	GetRenderPt(){ return mRenderPt; }
	void	SetRenderPt( POINT pt ){ mRenderPt = pt;}

	void	Clear();

	void	Render();

	void				SetFlag( BestEquipFlag flag ) { mFlag = flag; }
	BestEquipFlag		GetFlag() const { return mFlag; }

private:

	friend class Singleton<IconMgrBestEquip>;
	IconMgrBestEquip();

	bool	FullOneLine( const char* info, DWORD align, DWORD col );

	bool	ParseInfo( std::string& info, DWORD col );

	void	RenderMakeup( int fontIdx );

	bool	Check( int idx );

public:

	struct StrData
	{
		StrData()
		{
			mColor = 0xffffffff;
			mAlign = DT_NOCLIP;
		}
		void Clear()
		{
			mColor = 0xffffffff;
			mAlign = DT_NOCLIP;
			mStr.clear();
		}
		DWORD		mColor;
		DWORD		mAlign;
		RECT		mRect;
		std::string	mStr;
	};

private:

	StrData			mAllStr[MAX_STR_COUNT];
	int				mCurLine;
	POINT			mRenderPt;
	RECT			mRect;
	int				mFontId;

	BestEquipFlag	mFlag;

	bool			mIsShow;
	
};

inline bool IconMgrBestEquip::Check( int idx )
{
	if ( idx <= -1 || idx >= MAX_STR_COUNT )
	{
		return false;
	}
	return true;
}

#endif