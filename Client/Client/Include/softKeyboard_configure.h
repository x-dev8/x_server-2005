
#ifndef AN_DRAGOONAPP_SOFTKEYBOARD_H_
#define AN_DRAGOONAPP_SOFTKEYBOARD_H_

#include "shortcutkey_configure.h"
#include <map>

struct uiBtns_Info
{
	std::string		_value;
	std::string		_valueCaps;
};
class CSoftKeyboard_configure
{
public:
	CSoftKeyboard_configure();
	virtual ~CSoftKeyboard_configure();

	void load();
	
	std::map<int, std::string>&		getKeyInfoMap()
	{
		return _keyInfoMap;
	}
	inline int	getKeyMaxCnt() const
	{
		return _keyInfoMap.size();
	}
	std::map<std::string, uiBtns_Info>&		getUIBtnsIndexMap()
	{
		return _uiBtnsIndexMap;
	}
	inline int	getUIBtnsMaxCnt() const
	{
		return _uiBtnsIndexMap.size();
	}

private:
	
	std::map<int, std::string>	_keyInfoMap;
	std::map<std::string, uiBtns_Info>	_uiBtnsIndexMap;

};

extern CSoftKeyboard_configure g_SoftKeyboard_configure;

#endif