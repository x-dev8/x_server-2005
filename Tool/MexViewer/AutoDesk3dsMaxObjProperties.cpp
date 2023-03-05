#include "StdAfx.h"
#include "AutoDesk3dsMaxObjProperties.h"

AutoDesk3dsMaxObjProperties::AutoDesk3dsMaxObjProperties()
{

}

AutoDesk3dsMaxObjProperties::~AutoDesk3dsMaxObjProperties()
{

}

void AutoDesk3dsMaxObjProperties::Reset()
{
	mProperties.clear();
}

void AutoDesk3dsMaxObjProperties::AddPropertyForExport(const char *key, int value)
{
	AutoDesk3dsMaxPropData data;
	data.i = value;
	AddPropertyForExport(key, IntegerType, data);
}

void AutoDesk3dsMaxObjProperties::AddPropertyForExport(const char *key, DWORD value)
{
	AutoDesk3dsMaxPropData data;
	data.dw = value;
	AddPropertyForExport(key, IntegerType, data);
}

void AutoDesk3dsMaxObjProperties::AddPropertyForExport(const char *key, wxColour value)
{
	unsigned char red = value.Red();
	unsigned char green = value.Green();
	unsigned char blue = value.Blue();

	DWORD color = (DWORD) ((red << 16) | (green << 8) | blue);
	this->AddPropertyForExport(key, color);
}

void AutoDesk3dsMaxObjProperties::AddPropertyForExport(const char *key, float value)
{
	AutoDesk3dsMaxPropData data;
	data.f = value;
	AddPropertyForExport(key, FloatingPointType, data);
}

void AutoDesk3dsMaxObjProperties::AddPropertyForExport(const char *key, const char *value)
{
	AutoDesk3dsMaxPropData data;
	strcpy_s(data.buffer, MAX_PATH - 1, value);
	AddPropertyForExport(key, StringType, data);
}

void AutoDesk3dsMaxObjProperties::AddPropertyForExport(const char *key, AutoDesk3dsMaxPropType valueType, AutoDesk3dsMaxPropData value)
{
	AutoDesk3dsMaxProp property;
	strcpy_s(property.key, 32 - 1, key);
	property.valueType = valueType;
	property.value = value;
	mProperties.push_back(property);
}

void AutoDesk3dsMaxObjProperties::ConvertTo3dsMaxPropString(wxArrayString &as)
{
	AutoDesk3dsMaxProp *prop = NULL;
	for (int i = 0; i < mProperties.size(); ++i)
	{
		prop = &mProperties[i];
		switch (prop->valueType)
		{
		case IntegerType:
			as.Add(wxString::Format(wxT("%s = %d\n"), prop->key, prop->value.i));
			break;

		case FloatingPointType:
			as.Add(wxString::Format(wxT("%s = %f\n"), prop->key, prop->value.f));
			break;

		case StringType:
			as.Add(wxString::Format(wxT("%s = %s\n"), prop->key, prop->value.buffer));
			break;
		}
	}
}