#pragma once

class ChatChannelConfig
{
public:
	typedef struct _tagChatChannelInfo
	{
		std::string m_strChannelName;
		DWORD		m_dwChannelType;
		DWORD		m_dwChannelColor;
        DWORD       m_dwDefChannelType;
	}ChatChannelInfo;

	typedef std::vector< ChatChannelInfo > ChatChannelInfoList;

public:
	/// ~ctor
	~ChatChannelConfig(){}

	/// load config
	bool Load( const char* pszFilename );
	 
	/// save config
	bool Save( const char* pszFilename );

	/// get list
	const ChatChannelInfoList& GetChatChannelList() const{ return m_ChatChannelInfoList; }

	/// set list
	void SetChatChannelList( ChatChannelInfoList& chatList ){ m_ChatChannelInfoList = chatList; }

public:
	static ChatChannelConfig* Instance();

protected:
	/// ctor
	ChatChannelConfig(){ m_ChatCommandInfo.clear(); }

protected:
	/// chat channel list
	ChatChannelInfoList m_ChatChannelInfoList;

	// º”‘ÿ¡ƒÃÏ∆µµ¿√¸¡Ó
	///////////////////////////////////////////////////////////
public:
	struct ChatTypeInfo
	{
		std::string strType;
		std::string strCommandCn;
		std::string strCommandEn;
	};
	typedef std::vector< ChatTypeInfo > ChatCommandInfo;

	bool LoadCommandConfig();

	const ChatCommandInfo& GetChatCommandInfo() { return m_ChatCommandInfo; }

protected:
	ChatCommandInfo m_ChatCommandInfo;
};