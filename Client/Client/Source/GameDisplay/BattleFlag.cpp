#include "FuncPerformanceLog.h"
#include "tga.h"
#include "MeUi/UIPicture.h"
#include "gamemain.h"
#include "Player.h"
#include "playermgr.h"
#include "CfgFileLoader.h"
#include <math.h>
#include <vector>
#include "BattleFlag.h" 

CBattleFlag::CBattleFlag(void)
{
    m_nGuardTexture = -1;
    m_nAttackTexture = -1;
}

CBattleFlag::~CBattleFlag(void)
{
    UnRegisterTexture();
}

void CBattleFlag::RegisterTexture()
{
    m_nAttackTexture = GetEngine()->GetTextureManager()->RegisterTexture( "data\\ui\\ICON\\Maniple\\Att.dds", FALSE ,TRUE);
    m_nGuardTexture = GetEngine()->GetTextureManager()->RegisterTexture( "data\\ui\\ICON\\Maniple\\Def.dds", FALSE ,TRUE);
}

void CBattleFlag::UnRegisterTexture()
{
    if(m_nAttackTexture != -1)
    {
        GetEngine()->GetTextureManager()->UnRegisterTexture(m_nAttackTexture);
        m_nAttackTexture = -1;
    }
    if(m_nGuardTexture != -1)
    {
        GetEngine()->GetTextureManager()->UnRegisterTexture(m_nGuardTexture);
        m_nGuardTexture = -1;
    }
}

void CBattleFlag::Render(int x, int y, short shFlag)
{
    RECT rDraw = {x, y, x+64, y+32};
    RECT rSrc = {0, 0, 64, 32};

    if(shFlag == 1)
    {
        GetDrawer()->Blt(m_nGuardTexture, &rDraw, &rSrc, 64, 32, 0, 0xffffffff, 0);
    }
    if(shFlag == 2)
    {
        GetDrawer()->Blt(m_nAttackTexture, &rDraw, &rSrc, 64, 32, 0, 0xffffffff, 0);
    }
}