#ifndef __SERVERCOMMON_OBJECTCOUNTER_H__
#define __SERVERCOMMON_OBJECTCOUNTER_H__

// 统计游戏中Monster NPC Itemchar 个数 
struct ObjectCount
{
	ObjectCount()
	{ memset( this, 0, sizeof(*this)); }

	const DWORD GetID() const { return dwID; }
	const char* GetName() const { return szName; }
	const DWORD GetCount() const { return dwCount; }

	void SetID( DWORD dwValue ) { dwID  = dwValue; }
	void SetName( const char* szValue ) { strncpy_s( szName, sizeof( szName ), szValue, sizeof( szName ) - 1 ); }
	void SetCount( DWORD dwValue ) { dwCount = dwValue; }

	DWORD dwID;						// id
	char  szName[dr_MaxPlayerName]; // 名字
	DWORD dwCount;					// 数量
};

typedef std::vector<ObjectCount> ObjectCountContainer;
typedef ObjectCountContainer::iterator ItrObjectCountContainer;

struct GreaterCount : public std::unary_function< ObjectCount, bool >
{
	bool operator() ( const ObjectCount& xLeft, const ObjectCount& xRight )
	{
		return xLeft.GetCount() > xRight.GetCount();
	}
};

#endif __SERVERCOMMON_OBJECTCOUNTER_H__