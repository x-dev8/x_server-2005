#include "MeUi/ControlComboBox.h"
#include "MeUi/ControlFrame.h"

ControlComboBox::ControlComboBox(void)
{
	m_pOnChange = NULL;
	m_pOnShowList = NULL;

	_luaTableName.clear();
	_funOnChangeName.clear();
	_funOnShowListName.clear();
}

ControlComboBox::~ControlComboBox(void)
{
}

void ControlComboBox::Render()
{
	if ( IsNeedRender() )
	{
		ControlObject::Render();
		m_editInput.Render();
		m_listSelect.Render();
		m_btnSelect.Render();
	}
}

void ControlComboBox::InitUIData( IN ControlObject* pFather, IN S_BaseData* pData )
{
	ControlObject::InitUIData( pFather, pData );

	m_editInput.InitUIData( this, &((S_ComboBoxData*)pData)->m_stEdit );
	m_listSelect.InitUIData( this, &((S_ComboBoxData*)pData)->m_stList );
	m_btnSelect.InitUIData( this, &((S_ComboBoxData*)pData)->m_stButton );

	m_listSelect.SetVisable( false );

	OnChange();

#ifdef _DEBUG
	m_editInput.m_debug_bHasWarning = false;
	m_listSelect.m_debug_bHasWarning = false;
	m_btnSelect.m_debug_bHasWarning = false;
#endif
}

bool ControlComboBox::OnMouseWheel( bool bUp, const int nX, const int nY )
{
	if ( IsVisable() )
	{
		return m_listSelect.OnMouseWheel( bUp, nX, nY );
	}
	return false;
}

bool ControlComboBox::OnMouseMove( UINT nFlags, const int nX, const int nY )
{
	bool bResult = false;
	if ( IsVisable() )
	{
		ControlObject::OnMouseMove( nFlags, nX, nY );
		bResult |= m_editInput.OnMouseMove( nFlags, nX, nY );
		bResult |= m_listSelect.OnMouseMove( nFlags, nX, nY );
		bResult |= m_btnSelect.OnMouseMove( nFlags, nX, nY );
	}
	return bResult;
}

bool ControlComboBox::OnLButtonDown( UINT nFlags, const int nX, const int nY )
{
	if ( IsVisable() )
	{
		if ( m_editInput.OnLButtonDown( nFlags, nX, nY ) == true )
		{
			if ( m_editInput.IsReadOnly() )
			{
				bool b = !m_listSelect.IsVisable();
				m_listSelect.SetVisable( b );
				//if ( b )
				//{
				OnShowList();
				//}
			}
		}
		else if ( m_listSelect.OnLButtonDown( nFlags, nX, nY ) == true )
		{
			return true;
		}
		else if ( m_btnSelect.OnLButtonDown( nFlags, nX, nY ) == true )
		{
			bool b = !m_listSelect.IsVisable();
			m_listSelect.SetVisable( b );
			//if ( b )
			//{
			OnShowList();
			//}
		}
		else
		{
			if ( m_listSelect.IsVisable() )
			{
				m_listSelect.SetVisable( false );
			}
			return false;
		}
		return m_bMsgHoldup;
	}
	return false;
}

bool ControlComboBox::OnLButtonUp( UINT nFlags, const int nX, const int nY )
{
	if ( IsVisable() )
	{
		m_editInput.OnLButtonUp( nFlags, nX, nY );
		m_btnSelect.OnLButtonUp( nFlags, nX, nY );
		if (m_listSelect.OnLButtonUp( nFlags, nX, nY ))
		{
			// 只有在List控件里有效，其它的，如ScrollBar内都无效
			if ( m_listSelect.ControlObject::PtInObject(nX,nY,false) == true)
			{
				ControlList::S_List *pList = m_listSelect.GetCurSelItem();
				if (pList)
				{
					m_editInput.SetText(pList->m_szText);
				}
				m_listSelect.SetVisable(false);
				OnChange();
			}
			return true;
		}
		return PtInObject( nX, nY ,false);
	}
	return false;
}

bool ControlComboBox::OnChar( UINT nChar )
{
	if ( IsVisable() )
	{
		if( m_editInput.OnChar( nChar ) == true )
		{
			OnChange();
			return true;
		}
	}
	return false;
}

void ControlComboBox::OnShowList()
{
	if( NULL != state.Get() && _luaTableName.length() > 0 && _funOnShowListName.length() > 0  )
	{
		try
		{
			LuaObject table1Obj = state->GetGlobal( _luaTableName.c_str() );
			if( table1Obj.IsTable() )
			{
				LuaFunction<void> function_( table1Obj[_funOnShowListName.c_str()] );
				function_( );
			}
		}
		catch (LuaPlus::LuaException &e)
		{
			char szErr[256] = {0};
			_snprintf(szErr, sizeof(szErr)-1, "%s.lua[%s函数调用出错]: %s", _luaTableName.c_str(), _funOnShowListName.c_str(), e.GetErrorMessage());
			print_error( szErr );
		}
	}
	else
	{
        // 底层实现点击下拉框时关闭其他的下拉框     added by zhuomeng.hu    [5/19/2011]
        ControlFrame* pFrame = GetFrameFather();
        if( pFrame )
        {
            const std::vector< ControlObject* >* pChildren = pFrame->GetChildControlVec();
            if( pChildren )
            {
                std::vector< ControlObject* >::const_iterator it = pChildren->begin();
                for( ; it != pChildren->end(); ++it )
                {
                    if( ( *it )->GetControlType() == Type_ComboBox )
                    {
                        ControlComboBox* pComboBox = ( ControlComboBox* )( *it );
                        if( pComboBox && pComboBox != this )
                        {
                            pComboBox->GetListBox().SetVisable( false );
                        }
                    }
                }
            }
        }

		if ( m_pOnShowList )
		{
			m_pOnShowList(&m_editInput);
		}
	}

}

void ControlComboBox::OnChange()
{
	if( NULL != state.Get() && _luaTableName.length() > 0 && _funOnChangeName.length() > 0  )
	{
		try
		{
			LuaObject table1Obj = state->GetGlobal( _luaTableName.c_str() );
			if( table1Obj.IsTable() )
			{
				LuaFunction<void> function_( table1Obj[_funOnChangeName.c_str()] );
				function_( m_editInput.GetText() );
			}
		}
		catch (LuaPlus::LuaException &e)
		{
			char szErr[256] = {0};
			_snprintf(szErr, sizeof(szErr)-1, "%s.lua[%s函数调用出错]: %s", _luaTableName.c_str(), _funOnChangeName.c_str(), e.GetErrorMessage());
			print_error( szErr );
		}
	}
	else
	{
		if ( m_pOnChange )
		{
			m_pOnChange( this, m_editInput.GetText() );
		}
	}

#ifdef _DEBUG
	if ( m_debug_bHasWarning )
	{
		char szDebug[128];
		char szFatherID[128] = "";
		if ( m_pFather )
		{
			strcpy( szFatherID, m_pFather->GetControlID() );
		}
		sprintf(szDebug,"[%s]::[%s] OnChange() not defend!!\r\n", szFatherID, GetControlID() );
		//OutputDebugString(szDebug);
	}
#endif
}

void ControlComboBox::SetChangeFun_2lua( const char* luaTable, const char* funName )
{
	_luaTableName = luaTable;
	_funOnChangeName = funName;
}

void ControlComboBox::SetShowListFun_2lua( const char* luaTable, const char* funName )
{
	_luaTableName = luaTable;
	_funOnShowListName = funName;
}

void ControlComboBox::SetEnable( bool b )
{
	ControlObject::SetEnable(b);
	m_editInput.SetEnable(b);
	m_listSelect.SetEnable(b);
	m_btnSelect.SetEnable(b);
}

void ControlComboBox::ResetDevice()
{
	ControlObject::ResetDevice();
	m_editInput.ResetDevice();
	m_listSelect.ResetDevice();
	m_btnSelect.ResetDevice();
}

bool ControlComboBox::IsChild( IN const ControlObject* pChild )
{
	if (pChild == &m_editInput)
	{
		return true;
	}
	return false;
}

void ControlComboBox::Clear( bool bClearCurSelIndex )
{
    m_listSelect.Clear( bClearCurSelIndex );
    m_editInput.SetText( "" );
}

ControlList::S_List* ControlComboBox::AddItem( const ControlList::S_List* pItem )
{
    return m_listSelect.AddItem( pItem, NULL, false );
}

bool ControlComboBox::SetCurSelIndex( int nIndex )
{
    if( !m_listSelect.SetCurSelIndex( nIndex ) )
    {
        m_editInput.SetText( "" );
        return false;
    }

    ControlList::S_List *pList = m_listSelect.GetCurSelItem();
    if( pList )
    {
        m_editInput.SetText( pList->m_szText );
    }
    return true;
}

int ControlComboBox::GetCurSelIndex()
{
    return m_listSelect.GetCurSelIndex();
}
