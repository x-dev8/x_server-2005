#include "string_hashmap.h"
#ifdef _USE_HAS_MAP
#ifdef WIN32
size_t _Hash_valuett(const char* _Begin, const char* _End)
{
	size_t _Val = 2166136261U;
	while(_Begin != _End)
		_Val = 16777619U * _Val ^ (size_t)*_Begin++;
	return (_Val);
}
size_t test_hash_value( const char *_Str )
{
	return ( _Hash_valuett( _Str, _Str + strlen(_Str) ) );
}
size_t charhasher::operator()(const char* _Keyval) const
{	// hash _Keyval to size_t value by pseudorandomizing transform
	ldiv_t _Qrem = ldiv((long)test_hash_value(_Keyval), 127773);
	_Qrem.rem = 16807 * _Qrem.rem - 2836 * _Qrem.quot;
	if (_Qrem.rem < 0)
		_Qrem.rem += 2147483647;
	_Qrem.rem %= 100000;
	return ((size_t)_Qrem.rem);
}
#endif
#endif


// 把此串变为小写。并回写此串
void strtolower( char *src )
{
	if( !src )
		return;
	char *begin = src;
	while( *begin !='\0' )
	{
		if( *begin >= 'A' && *begin <= 'Z' )
		{
			*begin += 32;
		}
		++begin;
	}
}

// 去掉此串右边的空格
void str_right (char *str, size_t len)
{
	while (len >= 1)
	{
		if (str[len-1] == ' ')
			str[len-1] = '\0';
		--len;
	}
}
