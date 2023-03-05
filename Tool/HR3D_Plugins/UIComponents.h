#pragma once

#include <WindowsX.h>

#include "defines.h"

#define MAX_VALUE_BUFFER		256
#define MAX_COMPONENT_NAME		80

class UIComponents
{
public:
	enum ValueType
	{
		eInt,
		eFloat,
		eString,
		eColor
	};

	enum CtrlType
	{
		eEditCtrl,
		eCheckCtrl,
		eButtonCtrl,
		eRadioCtrl,
		eSpinCtrl,
		eColorCtrl,
		eComboCtrl,
	};

	union Value
	{
		int i;
		DWORD dw;
		float f;
		DWORD color[3];
		char buffer[MAX_VALUE_BUFFER];
	};

	struct Component
	{
		char szName[MAX_COMPONENT_NAME];
		DWORD id;
		int valueType;
		Value value;

		int ctrlType;
		DWORD ctrlId;
	};
public:
	UIComponents(HWND hWnd);
	virtual ~UIComponents();

public:
	Component *GetComponentByName( const char* pszName );
	Component *GetComponentById( DWORD dwId );
	Component *GetComponentByCtrlId( DWORD dwCtrlId );

	void GetComponentValue( Component* c );
	void GetAllComponentValue();

	void RedrawComponentUI();

	BOOL Convert( const char* s, DWORD* value );

protected:
	void CreateComponent(
		const char *name,
		DWORD id,
		int valueType,
		Value *defaultValue,
		int ctrlType, DWORD ctrlId);

protected:
	
	HWND mhWnd;
	std::vector<Component> mComponents;
};