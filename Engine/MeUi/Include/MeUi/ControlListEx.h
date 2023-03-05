#pragma once
#include "MeUi/ControlObject.h"
#include "MeUi/ControlIconDrag.h"

class ControlListEx : public ControlIconDrag
{
public:
	typedef bool (*funDrawInfo)( OUT RECT* pRC, OUT const S_ListImg* pListItem );

public:	/*Virtual Function by ControlObject*/
	void Render();
	void InitUIData( IN ControlObject* pFather, IN S_BaseData* pData );

public:	/*Virtual Function by ControlIconDrag*/
	// 取得指定坐标的格子坐标
	bool GetTilePt( const int nX, const int nY, OUT POINT *ptTile );
	int	 GetIconSize()	{ return ((S_ListExData*)m_pstData)->m_nItemHeight; }
	bool CanbePick(){ return ((S_ListExData*)m_pstData)->m_bCanbePick; }
	void SetCanbePick( const bool b ){ ((S_ListExData*)m_pstData)->m_bCanbePick = b; }

public:
	void SetDrawInfoFun( IN funDrawInfo fun ){ m_pFunDrawInfo = fun; }
	void SetDrawInfoFun_2lua( const char* luaTable, const char* funName );


	void SetHaveSelFrame( bool b ){ m_bHaveSelFrame = b; }
	void SetOnlyIcon( bool b )		{ m_bOnlyIconActive = b; }

	POINT getCurItemPos();

private:
	bool	m_bHaveSelFrame;
	bool	m_bOnlyIconActive;
	funDrawInfo	m_pFunDrawInfo;

	std::string		_luaTableName;
	std::string		_funDrawInfo;

	int m_nItemWidth;
	int m_nItemHeight;
	int m_nOffsetWidth; 
	int m_nOffsetHeight;

public:
	ControlListEx(void);
	~ControlListEx(void);

	virtual void ResetDevice();
};
