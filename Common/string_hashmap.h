#ifndef _H_T_STRING_HASHMAP_T_H_
#define _H_T_STRING_HASHMAP_T_H_
#define _USE_HAS_MAP
#ifndef _USE_HAS_MAP
#include <string.h>
#include <assert.h>
#include <map>

class CmpString
{
public:
	char *m_pString;
	CmpString(char*p)
	{
		assert(p != NULL);
		static char strnull[]="";
		if (p)
			m_pString = p;
		else
			m_pString = strnull;

	}
	CmpString(const char*p)
	{
		assert(p != NULL);
		static char strnull[]="";
		if (p)
			m_pString = (char*)p;
		else
			m_pString = strnull;
	}
	bool operator < (const CmpString& str)const
	{
		assert(m_pString != NULL);
		assert(str.m_pString != NULL);
		return strcmp(m_pString, str.m_pString) < 0;
	}
	CmpString operator = (const char *data)
	{
		CmpString temp((char*)data);
		return temp;
	}
};




template<class _data >
class string_hash:public std::map<CmpString, _data, std::less<CmpString> >
{

};
#else
#ifdef WIN32
#include <hash_map>
using namespace stdext;
class charhasher
{
public:
	enum
	{	// parameters for hash table
		bucket_size = 4,	// 0 < bucket_size
		min_buckets = 8};	// min_buckets = 2 ^^ N, 0 < N
	size_t operator()(const char* _Keyval) const;
	bool operator() (const char *s1,const char *s2)const
	{
		if( strcmp( s1, s2 ) < 0 )
			return true;
		return false;
	}

};
template<class _data >
class string_hash:public hash_map<const char*, _data, charhasher >
{

};
#else
#include <ext/hash_map>
using namespace __gnu_cxx;
struct compare_str
{
	bool operator()(const char* p1, const char*p2) const
	{
		return strcmp(p1,p2)==0;
	}
};
template<class _data >
class string_hash:public hash_map<const char*, _data, hash<const char*>, compare_str>
{

};
#endif
#endif
// 把此串变为小写。并回写此串
void strtolower( char *src );
// 去掉此串右边的空格
void str_right (char *str, size_t len);
#endif
