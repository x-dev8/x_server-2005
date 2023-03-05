
#include "GameMain.h"
#include "WordParser.h"
#include "FuncPerformanceLog.h"

#include "ui/MiniMapUI.h"
#include "UI\Main.h"
#include "UI\ChatInfoBox.h"
#include "UI\Group_me.h"
#include "ui\TopInfo.h"

FGameState	GameState;

FGameState::FGameState()
{
	guardfunc;
	bRenderMiniMap = TRUE;
	RenderGroup = TRUE;
	UseDefPart = TRUE;
	unguard;
}

void FGameState::Init()
{
	guardfunc;

	unguard;
}

BOOL FGameState::DebugCommand( const char* pszCommand )
{
	guardfunc;
	if( pszCommand == NULL )
		return FALSE;

	if( pszCommand[0] == 0 )
		return FALSE;

	WordParser words;

	if( words.Parse( pszCommand ) == 0 )
		return FALSE;

	if( words.Compare(0, "RenderMiniMap"))
	{
		bRenderMiniMap = !bRenderMiniMap;
		return TRUE;
	}
	else if( words.Compare(0, "RenderGroup"))
	{
		RenderGroup = !RenderGroup;
		return TRUE;
	}
	else if( words.Compare(0, "Broken") )
	{
		INT Broken = 0;
		Broken = 10/Broken;
		return TRUE;
	}
	else if( words.Compare( 0, "MainUI" ) )
	{
		s_CUI_ID_FRAME_MAIN.SetVisable( !s_CUI_ID_FRAME_MAIN.IsVisable() );
	}
	else if( words.Compare( 0, "ChatUI" ) )
	{
		s_CUI_ChatInfoBox.SetVisable( !s_CUI_ChatInfoBox.IsVisable() );
	}
	else if( words.Compare( 0, "MiniUI" ) )
	{
		s_CUI_ID_FRAME_MiniMap.SetVisable( !s_CUI_ID_FRAME_MiniMap.IsVisable() );
	}
	else if( words.Compare( 0, "GroupUI" ) )
	{
		s_CUI_ID_FRAME_Group_Me.SetVisable( !s_CUI_ID_FRAME_Group_Me.IsVisable() );
	}

	return FALSE;
	unguard;
}