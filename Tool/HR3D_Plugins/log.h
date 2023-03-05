#ifndef _log_h
#define _log_h
#include <vector>
#include <string>
class CLog
{
public:
	void	Print( const char* string, ... );
	void	Reset(){ m_strings.clear(); }
	std::vector<std::string> m_strings;
};

extern CLog g_log;

#endif