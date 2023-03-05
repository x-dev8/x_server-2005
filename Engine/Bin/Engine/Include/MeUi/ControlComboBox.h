
#pragma once
#include "MeUi/ControlObject.h"
#include "MeUi/ControlButton.h"
#include "MeUi/ControlEdit.h"
#include "MeUi/ControlList.h"

class ControlComboBox : public ControlObject
{
public:
	typedef void (*funOnChange)( OUT ControlObject* pSender, OUT const char* szData );
	typedef void (*funOnShowList)( OUT ControlObject* pSender );

public:	/*Virtual Function*/
	void Render();
	void InitUIData( IN ControlObject* pFather, IN S_BaseData* pData );
	bool OnMouseMove( UINT nFlags, const int nX, const int nY );
	bool OnMouseWheel( bool bUp, const int nX, const int nY );
	bool OnLButtonDown( UINT nFlags, const int nX, const int nY );
	bool OnLButtonUp( UINT nFlags, const int nX, const int nY );
	bool OnChar( UINT nChar );

	ControlList&  GetListBox()
	{
		return m_listSelect;
	}
	ControlEdit& GetEditInput()
	{
		return m_editInput;
	}

	virtual bool IsChild( IN const ControlObject* pChild );

	virtual void SetEnable( bool b );

public:
	void SetChangeFun( IN funOnChange pFun )	{ m_pOnChange = pFun; }
	void SetChangeFun_2lua( const char* luaTable, const char* funName );
	void SetShowListFun( IN funOnShowList pFun ){ m_pOnShowList = pFun; }
	void SetShowListFun_2lua( const char* luaTable, const char* funName );

public:
	void	OnChange();
	void	OnShowList();

    // ½Ó¿ÚÀ©³ä     added by zhuomeng.hu    [5/12/2011]
    void    Clear( bool bClearCurSelIndex = true );
    bool    SetCurSelIndex( int nIndex );
    int     GetCurSelIndex();
    ControlList::S_List*    AddItem( const ControlList::S_List* pItem );

private:
	ControlEdit		m_editInput;
	ControlList		m_listSelect;
	ControlButton	m_btnSelect;
	funOnChange		m_pOnChange;
	funOnShowList	m_pOnShowList;


	std::string		_luaTableName;

	std::string		_funOnChangeName;
	std::string		_funOnShowListName;

public:
	ControlComboBox(void);
	~ControlComboBox(void);

	virtual void ResetDevice();
};
