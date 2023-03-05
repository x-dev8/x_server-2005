
#pragma once

#include "MeUi/MeUi.h"
#include "Singleton.h"
class CxImage;
class CExpressionUpdater;
class ExpressionManager:public Singleton<ExpressionManager>
{
	friend CExpressionUpdater;
public:
	typedef struct ExpressionData : public MeCommonAllocObj<ExpressionManager::ExpressionData>
	{
		friend ExpressionManager;
	private:
		int					m_textureId;
		CxImage*			m_pImage;
	public:
		int					m_X8textureId;
		std::string			m_Tip;
		DWORD				dTime;
		std::string			m_strGroupName;
		std::string			m_strFullPath;
		int					m_nImageType;
		int					m_nWidth;
		int					m_nHeight;
		bool				m_bUseInChat;
		int					GetTextureId();
		ExpressionData(const char* pFullName,const char* pTip, const char* pszGroupName = 0);
		~ExpressionData();
	}ExpressionData;
	typedef std::map<std::string, ExpressionData*> ExpressionInfos;

	ExpressionManager();
	~ExpressionManager();

	
	static ExpressionManager& GetInstance();

	bool LoadFromSlk();
	void			TestRender();
	int			AddExpressionAni(std::string&  str,int nMaxExpression = 100,bool bUseInChat = false);
	void			DrawExpression( const std::string&  str, RECT& rcDst, float fZ = 0 );
	void			DrawExpression(ExpressionData* pInfo, RECT& rcDst, float fZ = 0 );

	void		UpdateExpression( ExpressionData* pInfo );
	void			SetCurrentFrameTime( DWORD dwTime ){ m_dwCurrentFrameTime = dwTime; }	
	ExpressionData* GetExpressionInfo(const std::string&  str,bool bUseInChat = false)
	{
		ExpressionInfos::iterator it = m_expressionSets.find(str);
		if (it != m_expressionSets.end())
		{
			if (bUseInChat && !it->second->m_bUseInChat)
			{
				return NULL;
			}
			if (it->second->GetTextureId() != -1)
			{
				return it->second;
			}
		}
		return 0;
	}
	const char*			GetExpressionKeyFromInfo(ExpressionData* pInfo);	
	std::vector<ExpressionData*>& GetExpressionList()  { return m_expressionList; }

	std::vector<unsigned short>& GetChatExpressionListIndex(){return m_expressionListIndex;}

	void			ToNextFrame();

protected:
	void AddFrameInfo( ExpressionData* pData );

private:

	std::vector<ExpressionData*>	m_expressionList;
	std::vector<unsigned short>		m_expressionListIndex;//聊天表情在m_expressionList中的下标集合
	ExpressionInfos					m_expressionSets;
	DWORD							m_dwCurrentFrameTime;
	// added, jiayi, [2009/10/14]
	// 记录当前游戏帧数时的gif的当前帧,用于同步帧数相同的gif
	typedef struct _tagFrameInfo
	{		
		long	lFrame;
		DWORD	dwDelayTime;
		long	lTotalFrame;
		bool	bRender;
		DWORD	dwLastTime;
	}FrameInfo;
	std::map< std::string, FrameInfo > m_mapSyncFrame;
};

class CExpressionUpdater
{
public:
	CExpressionUpdater();
	~CExpressionUpdater();
	void				Clear()
	{
		m_ActiveExpr.clear();
	}
	void				AddExpress(ExpressionManager::ExpressionData* pData);
	void				Update();
private:
	std::list<ExpressionManager::ExpressionData*>		m_ActiveExpr;
};