
#ifndef AN_COMPOUNDINFO_CONFIGURE_H_
#define AN_COMPOUNDINFO_CONFIGURE_H_

#include <map>
#include <vector>

using namespace std;

struct compoundInfo_item
{
	int			_compoundid;
	int			_itemid;
	string		_descriptionName;
	int			_type;
	string		_npcName;
};

class CCompoundInfo_configure
{
public:
	CCompoundInfo_configure();
	~CCompoundInfo_configure();

public:
	void	 load();
	compoundInfo_item*	getCompoundInfo( int id );
	compoundInfo_item*	getCompoundInfoByItemId( int itemid );
	vector<int>			getVecItemId( int type );	//ͨ�����õ�type���͵õ� ���ڴ����͵�item����
	int					getCompoundId( int itemid );	//ͨ��itemid �õ��䷽id

	map<int, compoundInfo_item>&	getCompoundInfoMap()
	{
		return map_compoundInfoConfigure;
	}

private:
	map<int, compoundInfo_item>		map_compoundInfoConfigure;
};

extern CCompoundInfo_configure g_compoundInfo_configure;

#endif