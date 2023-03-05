#ifndef _object_h
#define _object_h
#include <string.h>
class Object
{
public:
	typedef struct
	{
		unsigned long id[4];
	}GUID;
protected:
	GUID m_guid;
	char* m_pszName;
	bool m_bSelected;
public:
	Object()
	{
		m_guid.id[0] = 
		m_guid.id[1] = 
		m_guid.id[2] = 
		m_guid.id[3] = 0;

		m_pszName = 0;
	}
	virtual~ Object()
	{	if( m_pszName )
			delete []m_pszName;
		m_pszName = 0;
	}
}
	void SetGUID( const GUID guid )
	{
		m_guid.id[0] =  guid.id[0];
		m_guid.id[1] =  guid.id[1];
		m_guid.id[2] =  guid.id[2];
		m_guid.id[3] =  guid.id[3];
	}
	GUID& GetGUID()
	{
		return m_guid;
	}
	bool Goal( const GUID guid )
	{
		if( m_guid.id[0] == guid.id[0] &&
			m_guid.id[1] == guid.id[1] &&
			m_guid.id[2] == guid.id[2] &&
			m_guid.id[3] == guid.id[3] )
			return true;
		return false;
	}
	void SetName( const char* pszName )
	{
		if( m_pszName )
		{
			delete []m_pszName;
			m_pszName = 0;
		}
		int nLength = strlen( (char*)pszName );
		m_pszName = MeDefaultNew char[nLength+1];
		strcpy( m_pszName, (char*)pszName );
	}
	char* GetName()
	{
		return m_pszName;
	}
	void Selected( bool b ){ m_bSelected = b; }
	
	virtual bool Create() = 0;
	virtual void Destroy() = 0;
	virtual void Delete() = 0;

};

#endif