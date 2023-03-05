#pragma once

/*
 * 为AutoDesk-3dsMax的对象属性-自定义数据封装的类
 */
class AutoDesk3dsMaxObjProperties
{
public:
	enum AutoDesk3dsMaxPropType
	{
		IntegerType = 0,
		FloatingPointType,
		StringType
	};

	union AutoDesk3dsMaxPropData
	{
		int i;
		DWORD dw;
		float f;
		char buffer[MAX_PATH];
	};

	struct AutoDesk3dsMaxProp
	{
		char key[32];
		AutoDesk3dsMaxPropType valueType;
		AutoDesk3dsMaxPropData value;
	};

public:
	AutoDesk3dsMaxObjProperties();
	virtual ~AutoDesk3dsMaxObjProperties();

public:
	void Reset();

	void AddPropertyForExport(const char *key, int value);
	void AddPropertyForExport(const char *key, DWORD value);
	void AddPropertyForExport(const char *key, wxColour value);
	void AddPropertyForExport(const char *key, float value);
	void AddPropertyForExport(const char *key, const char *value);
	void AddPropertyForExport(const char *key, AutoDesk3dsMaxPropType valueType, AutoDesk3dsMaxPropData value);

	void ConvertTo3dsMaxPropString(wxArrayString &as);

private:
	std::vector<AutoDesk3dsMaxProp> mProperties;
};