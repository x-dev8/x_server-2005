#include "MeUi/ControlPicture.h"
#include "FuncPerformanceLog.h"

ControlPicture::ControlPicture(void)
{
	m_pFunOnButtonClick = NULL;
	m_pFunOnRButtonUp = NULL;
	m_pFunOnRButtonClick = NULL;
	m_pFunMouseOn = NULL;
	m_pFunMouseLeave = NULL;
	m_pFunLDBClick = NULL;
    _bIsShowTip = false;

	_luaTableName.clear();
	_funOnButtonClickName.clear();
	_funOnMouseOnName.clear();
	_funOnMouseLeaveName.clear();
	_funOnLDBClickName.clear();
}

ControlPicture::~ControlPicture(void)
{
}

void ControlPicture::InitUIData(ControlObject *pFather, S_BaseData *pData)
{
	ControlObject::InitUIData(pFather, pData);

	if (strlen(pData->m_szCaption) > 0)
	{
		setShowTip(true);
		setTip(pData->m_szCaption);
	}
}

void ControlPicture::Create( ControlFrame* pFather,S_BaseData* pData,const char* pProcessName )
{
	ReleaseUI();
	S_BaseData *pPicture = MeNew S_BaseData;
	m_bNeedRelease = true;
	memcpy_s(pPicture,sizeof(S_BaseData),pData,sizeof(S_BaseData));
	InitUIData( (ControlObject*)pFather, pPicture );
	strcpy_s(pPicture->m_szID,64,pProcessName);

}
bool ControlPicture::OnMouseMove( UINT nFlags, const int nX, const int nY )
{
    guardfunc;
    if(IsVisable())
    {
        if( PtInObject(nX, nY,false) )
        {
            if( IsShowTip() )
            {
                theIconInfoMouseTip.SetDisplayInfo( &TipInfo,
                    nX, nY, false,
                    m_nFontIndex, m_pstData->m_nFontSize * ControlObjectGetREAL_SCALE(this),
                    m_pstData->m_colFont,
                    false );
            }

			if( NULL != state.Get() && _luaTableName.length() > 0 && _funOnMouseOnName.length() > 0 )
			{
				try
				{
					LuaObject table1Obj = state->GetGlobal( _luaTableName.c_str() );
					if( table1Obj.IsTable() )
					{
						LuaFunction<void> function_( table1Obj[_funOnMouseOnName.c_str()] );
						function_();
					}
				}
				catch (LuaPlus::LuaException &e)
				{
					char szErr[256] = {0};
					_snprintf(szErr, sizeof(szErr)-1, "%s.lua[%s函数调用出错]: %s", _luaTableName.c_str(), _funOnMouseOnName.c_str(), e.GetErrorMessage());
					print_error( szErr );
				}
			}
			else
			{
				if( m_pFunMouseOn )
				{
					m_pFunMouseOn( this );
				}
			}

        }
    }
    return false;
    unguard;
}
bool ControlPicture::OnMouseLeave( UINT nFlags, const int nX, const int nY )
{
	guardfunc;
	if( !PtInObject( nX, nY,false) )
	{
		if( NULL != state.Get() && _luaTableName.length() > 0 && _funOnMouseLeaveName.length() > 0 )
		{
			try
			{
				LuaObject table1Obj = state->GetGlobal( _luaTableName.c_str() );
				if( table1Obj.IsTable() )
				{
					LuaFunction<void> function_( table1Obj[_funOnMouseLeaveName.c_str()] );
					function_();
				}
			}
			catch (LuaPlus::LuaException &e)
			{
				char szErr[256] = {0};
				_snprintf(szErr, sizeof(szErr)-1, "%s.lua[%s函数调用出错]: %s", _luaTableName.c_str(), _funOnMouseLeaveName.c_str(), e.GetErrorMessage());
				print_error( szErr );
			}
		}
		else
		{
			if( m_pFunMouseLeave )
			{
				m_pFunMouseLeave( this );
				return true;
			}
		}

	}
	return false;
	unguard;
}
bool ControlPicture::OnLButtonDBClick( UINT nFlags, const int nX, const int nY )
{
	guardfunc;
	if( IsVisable() )
	{
		if( PtInObject( nX, nY ,true) == true )
		{
			if( NULL != state.Get() && _luaTableName.length() > 0 && _funOnLDBClickName.length() > 0 )
			{
				try
				{
					LuaObject table1Obj = state->GetGlobal( _luaTableName.c_str() );
					if( table1Obj.IsTable() )
					{
						LuaFunction<void> function_( table1Obj[_funOnLDBClickName.c_str()] );
						function_();
					}
				}
				catch (LuaPlus::LuaException &e)
				{
					char szErr[256] = {0};
					_snprintf(szErr, sizeof(szErr)-1, "%s.lua[%s函数调用出错]: %s", _luaTableName.c_str(), _funOnLDBClickName.c_str(), e.GetErrorMessage());
					print_error( szErr );
				}
				return true;
			}
			else
			{
				if( m_pFunLDBClick )
				{
					m_pFunLDBClick( this );
					return true;
				}
			}

		}
	}
    return false;
    unguard;
}
bool ControlPicture::OnLButtonDown( UINT nFlags, const int nX, const int nY )
{
	if ( IsVisable() )
	{
		if ( PtInObject(nX,nY,true) == true )
		{
			return OnClick();
		}
	}
	return false;
}

bool ControlPicture::OnRButtonUp( UINT nFlags, const int nX, const int nY )
{
	if ( IsVisable() )
	{
		if ( PtInObject(nX,nY,true) == true )
		{
			if ( m_pFunOnRButtonUp )
			{
				return m_pFunOnRButtonUp( nX,nY );
			}
		}
	}
	return false;
}

bool ControlPicture::OnRButtonDown( UINT nFlags, const int nX, const int nY )
{
	if ( IsVisable() )
	{
		if ( PtInObject(nX,nY,true) == true )
		{
			if ( m_pFunOnRButtonClick )
			{
				return m_pFunOnRButtonClick( nX,nY );
			}
		}
	}
	return false;
}

bool ControlPicture::OnClick(void)
{
	if( NULL != state.Get() && _luaTableName.length() > 0 && _funOnButtonClickName.length() > 0 )
	{
		try
		{
			LuaObject table1Obj = state->GetGlobal( _luaTableName.c_str() );
			if( table1Obj.IsTable() )
			{
				LuaFunction<void> function_( table1Obj[_funOnButtonClickName.c_str()] );
				function_();
			}
		}
		catch (LuaPlus::LuaException &e)
		{
			char szErr[256] = {0};
			_snprintf(szErr, sizeof(szErr)-1, "%s.lua[%s函数调用出错]: %s", _luaTableName.c_str(), _funOnButtonClickName.c_str(), e.GetErrorMessage());
			print_error( szErr );
		}
	}
	else
	{
		if ( m_pFunOnButtonClick )
		{
			return m_pFunOnButtonClick( this );
		}
	}
	return false;
}
void ControlPicture::setTip(const char* data,DWORD dwAlign /*= DT_CENTER | DT_VCENTER*/ )
{
    guardfunc;
    if( NULL == data )
        return;

    TipInfo.SetInfo( data, dwAlign );
    unguard;
}

void ControlPicture::SetPicClickFun_2lua( const char* luaTable, const char* funName )
{
	guardfunc;
	_luaTableName = luaTable;
	_funOnButtonClickName = funName;
	unguard;
}
void ControlPicture::SetOnMouseOn_2lua( const char* luaTable, const char* funName )
{
	guardfunc;
	_luaTableName = luaTable;
	_funOnMouseOnName = funName;
	unguard;
}
void ControlPicture::SetOnMouseLeave_2lua( const char* luaTable, const char* funName )
{
	guardfunc;
	_luaTableName = luaTable;
	_funOnMouseLeaveName = funName;
	unguard;
}
void ControlPicture::SetOnLDBClickFun_2lua( const char* luaTable, const char* funName )
{
	guardfunc;
	_luaTableName = luaTable;
	_funOnLDBClickName = funName;
	unguard;
}

