#pragma once
#include <windows.h>
#include <vector>
#include <map>
class MexCfg;
class ActionConfig
{
public:
	struct Keyframe
	{
		DWORD	dwFrame;
		int		nHit;
		char	szWavFilename[MAX_PATH];
		int		nSrcEffect;
		int		nDstEffect;
		Keyframe();
	};

	struct Action 
	{
		DWORD	dwId;
		char	szIntro[64];
		char	szName[64];
		DWORD	dwModelId;
		DWORD	dwStartFrame;
		DWORD	dwEndFrame;
		std::vector<Keyframe*> vectorKeyframe;
		
		Action();
		~Action();
		BOOL	DeleteKeyframe( Keyframe* pKeyframe );
	};
	struct Model
	{
		DWORD	dwId;
		char	szFilename[MAX_PATH];
	};
public:
	ActionConfig(void);
	~ActionConfig(void);

	Model* GetModel( DWORD dwModelId );
	MexCfg* CreateMexCfg( DWORD dwModelId );
	BOOL	LoadActionFromSlk( const char* pszFilename );
	BOOL	LoadModelFromSlk( const char* pszFilename );
	BOOL	LoadKeyframes( Action* action );
	BOOL	SaveToFile( const char* pszFilename );
	BOOL	LoadFromFile( const char* pszFilename );

	BOOL	DeleteAction( Action* pAction );


	std::vector<Action*> m_vectorAction;
	std::vector<Model*> m_vectorModel;
	std::map<DWORD,MexCfg*> m_mapMexCfg;

};

extern ActionConfig	g_actCfg;
