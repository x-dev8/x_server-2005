#ifndef __EXPACTIONCONFIG_H__
#define __EXPACTIONCONFIG_H__

#include <map>
// #include "Tinyxml/tinyxml.h"
#include "RapidXml/MeRapidXml.h"

//表情动作
class ExpAction
{
public:
	enum ESex
	{
		SAll = 0,
		Male,
		Female
	};

	ExpAction() : ustId( 0 ), ustItemId( 0 ), strActionName( "" ), strCommand( "" ), strNoTargetChat( "" ), strSelfTargetChat( "" ),
	strOtherTargetChat( "" ), bOtherTargetSelfFront( 0 ), strSoundFileName( "" ), strLoopActionName( "" ) { }

	void SetId( unsigned short ustValue ) { ustId = ustValue; }
	void SetItemId( unsigned short ustValue ) { ustItemId = ustValue; }
	void SetActionName( const char* szValue ) { if( szValue ) strActionName = szValue; }
	void SetLoopActionName( const char* szValue ) { if( szValue ) strLoopActionName = szValue; }
	void SetCommand( const char* szValue ) { if( szValue ) strCommand = szValue; }
	void SetNoTargetChat( const char* szValue ) { if( szValue ) strNoTargetChat = szValue; }
	void SetSelfTargetChat( const char* szValue ) { if( szValue ) strSelfTargetChat = szValue; }
	void SetOtherTargetChat( const char* szValue ) { if( szValue ) strOtherTargetChat = szValue; }
	void SetOtherTargetSelfFront( bool bValue ) { bOtherTargetSelfFront = bValue; }
	void SetSound( const char* szValue ) { if( szValue ) strSoundFileName = szValue; }
	void SetSex( ESex sex ) { eSex = sex; }

	unsigned short GetId() const { return ustId; }
	unsigned short GetItemId() const { return ustItemId; }
	const char* GetActionName() const { return strActionName.c_str(); }
	const char* GetLoopActionName() const { return strLoopActionName.c_str(); }
	const char* GetCommand() const { return strCommand.c_str(); }
	const char* GetNoTargetChat() const { return strNoTargetChat.c_str(); }
	const char* GetSelfTargetChat() const { return strSelfTargetChat.c_str(); }
	const char* GetOtherTargetChat() const { return strOtherTargetChat.c_str(); }
	bool GetOtherTargetSelfFront() const { return bOtherTargetSelfFront; }
	const char* GetSound() const { return strSoundFileName.c_str(); }
	const ESex GetSex() const { return eSex; }

private:
	unsigned short ustId;			// 表情动作Id
	ESex eSex;						// 性别
	unsigned short ustItemId;		// 表情图标Icon
	std::string strActionName;		// 动作名
	std::string strLoopActionName;	// 持续动作名
	std::string strCommand;			// 动作命令，在聊天框中输入，以'/'打头
	std::string strNoTargetChat;	// 无目标的聊天显示
	std::string strSelfTargetChat;	// 目标为自己的聊天显示
	std::string strOtherTargetChat; // 有目标的聊天显示
	bool bOtherTargetSelfFront;		// 有目标的聊天显示，自己名字显示在前面
	std::string strSoundFileName;	// 声效文件
};

class ExpActionConfig
{
public:
	typedef std::map< unsigned short, ExpAction > ExpActionMap;
	typedef ExpActionMap::const_iterator ExpActionMapConstIter;

public:
	~ExpActionConfig() { m_mapExpAction.clear(); }

	static ExpActionConfig& Instance()
	{
		static ExpActionConfig s_xExpActionConfig;
		return s_xExpActionConfig;
	}

	const ExpAction* GetExpAction( unsigned short nId ) const
	{
		ExpActionMapConstIter iter = m_mapExpAction.find( nId );
		if( iter == m_mapExpAction.end() )
		{ return NULL; }

		return &( iter->second );
	}

	void SetExpActionCD( int nValue ) { m_nExpActionCD = nValue; }
	void SetTargetMaxDist( unsigned short ustValue ) { m_ustTargetMaxDist = ustValue; }

	int GetExpActionCD() const { return m_nExpActionCD; }
	unsigned short GetTargetMaxDist() const { return m_ustTargetMaxDist; }
	const ExpActionMap& GetExpActions() const { return m_mapExpAction; }
	int GetExpActionNum( ExpAction::ESex sex ) const
	{
		if( sex == ExpAction::Male )
			return m_nMaleExpActionNum;
		else
			return m_nFemaleExpActionNum;
	}

	bool LoadExpActionConfig( const char* szFile );

protected:
	ExpActionConfig() : m_nExpActionCD( 2000 ), m_ustTargetMaxDist( 10 ), m_nMaleExpActionNum( 0 ), m_nFemaleExpActionNum( 0 )
	{
		m_mapExpAction.clear();
	}

	bool AddExpAction( unsigned short nId, const ExpAction& xExpAction )
	{
		ExpActionMapConstIter iter = m_mapExpAction.find(nId);
		if (iter != m_mapExpAction.end())
			return false;
		m_mapExpAction[nId] = xExpAction;
		return true;
	}

	bool LoadActions( MeXmlElement* pElement, ExpAction::ESex sex );

private:
	int m_nExpActionCD;					// 播放CD，毫秒
	unsigned short m_ustTargetMaxDist;	// 与目标最大距离
	ExpActionMap m_mapExpAction;		// 表情动作表
	short m_nMaleExpActionNum;			// 男性表情动作个数
	short m_nFemaleExpActionNum;		// 女性表情动作个数
};

#define theExpActionConfig ExpActionConfig::Instance()

#endif
