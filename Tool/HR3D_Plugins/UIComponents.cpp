#include "UIComponents.h"

UIComponents::UIComponents(HWND hWnd)
	: mhWnd(hWnd)
{

}

UIComponents::~UIComponents()
{

}

UIComponents::Component *UIComponents::GetComponentByName(const char* pszName)
{
	for( int i = 0; i < mComponents.size(); i++ )
	{
		if (stricmp( mComponents[i].szName, pszName ) == 0)
			return &mComponents[i];
	}
	return NULL;
}

UIComponents::Component *UIComponents::GetComponentById( DWORD id )
{
	for( int i = 0; i < mComponents.size(); i++ )
	{
		if( mComponents[i].id == id )
			return &mComponents[i];
	}
	return NULL;
}

UIComponents::Component *UIComponents::GetComponentByCtrlId( DWORD ctrlId )
{
	for( int i = 0; i < mComponents.size(); i++ )
	{
		if( mComponents[i].ctrlId == ctrlId )
			return &mComponents[i];
	}
	return NULL;
}

void UIComponents::GetComponentValue( UIComponents::Component* c )
{
	HWND hItem = GetDlgItem( mhWnd, c->ctrlId );
	switch( c->ctrlType )
	{
	case eEditCtrl:
		{
			char s[256];
			GetWindowText( hItem, s, 256 );
			switch( c->valueType )
			{
			case eInt:
				c->value.i = atoi( s );
				break;
			case eFloat:
				c->value.f = atof( s );
				break;
			case eString:
				strcpy( c->value.buffer, s );
				break;
			};
		}
		break;
	case eCheckCtrl:
		{
			c->value.i = Button_GetCheck( hItem );
		}
		break;
	case eComboCtrl:
		{
			int nSelId = ComboBox_GetCurSel( hItem );
			if( nSelId != -1 )
			{
				ComboBox_GetLBText( hItem, nSelId, c->value.buffer );
			}
		}
		break;
	case eSpinCtrl:
		break;
	case eColorCtrl:
		break;
	};
}

void UIComponents::GetAllComponentValue()
{
	for( int i = 0; i < mComponents.size(); i++ )
	{
		GetComponentValue( &mComponents[i] );
	}
}


void UIComponents::RedrawComponentUI()
{
	for( int i = 0; i < mComponents.size(); i++ )
	{
		UIComponents::Component* c = &mComponents[i];
		if( c->ctrlType != eColorCtrl )continue;
		HWND hItem = GetDlgItem( mhWnd, c->ctrlId );
		PAINTSTRUCT ps;
		HDC hDC = BeginPaint( hItem, &ps );

		HPEN hBlackPen = CreatePen( PS_SOLID, 1, RGB( 0, 0, 0 ) );
		HPEN hOldPen = (HPEN)SelectObject( hDC, hBlackPen );
		RECT rc = { 0, 0, 20, 20 };
		SetBkColor( hDC, RGB( c->value.color[0], c->value.color[1], c->value.color[2]  ) );
		ExtTextOut( hDC, 0, 0, ETO_OPAQUE, &rc, NULL, 0, NULL);
		SelectObject( hDC, hOldPen );
		DeleteObject( hBlackPen );
		EndPaint( hItem, &ps );

	}
}

void UIComponents::CreateComponent(const char *name, DWORD id, int valueType, Value *defaultValue, int ctrlType, DWORD ctrlId)
{
	if( GetComponentByName(name))
	{
		assert( false && "same name" );
		return;
	}
	else if( GetComponentById(id ) )
	{
		assert( false && "same id" );
		return;
	}
	else if( GetComponentByCtrlId(ctrlId ) )
	{
		assert( false && "same ctrl id" );
		return;
	}

	UIComponents::Component c;
	strcpy( c.szName, name );
	c.id = id;
	c.valueType = valueType;
	memcpy(&c.value, defaultValue, sizeof( c.value ) );

	c.ctrlType = ctrlType;
	c.ctrlId = ctrlId;

	mComponents.push_back( c );
}