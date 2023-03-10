#include <vector>
#include "gamemain.h"
#include "effect.h"
#include "Player.h"
#include "PlayerMgr.h"
#include "MotionBillBoard.h"
#include "globalvars.h"
#include "Me3d/MoreAction.h"
#include "Me3d\emitter.h"
#include "FuncPerformanceLog.h"
#include "Me3d/Engine/Engine.h"
#include "MathLib.h"
#include "Common.h"
#include "Me3d/Engine/TextureManager.h"
#include "GlobalVars.h"
#include "MeFont\NewFont\MeFontRender.h"
#include "MeFont\MeFontSystem.h"

#ifdef _DEBUG
#include "MeFont/MeFont.h"
#endif

extern const char* GetRootPath();
extern CHeroGame* theApp;

CFlyTextEffect*		g_pFlyTextEffect = NULL;
CPrintTextEffect *  g_pPrintTextEffect = NULL;

extern float g_fTheRoleBBoxHeight;

extern int GetDirByOffset( int dx, int dy );
extern float CalcUserZDepth( float fWorldY );
extern void	World2Screen( D3DXVECTOR3 vPos,int &x,int &y );
/////////////////////////////////////////////////////////////////

// //-----------------------------------------
// int xBaseOffset = 0; //x轴基准坐标偏移
// int yBaseOffset = 192;   //y轴基准坐标偏移
// int xMaxOffset = 128;  //x轴最大移动距离
// int yMaxOffset = 50;   //y轴最大移动距离
// int xStep      = 6;   //x的步长
// int yStep      = 3;   //y的步长
// float InitAlpha  = 0.0f;   //初始Alpha值
// float OverAlpha  = 1.0f;   //最终Alpha值
// //当多增加一个伤害时，调制之间字体漂移速度
// int  xAddStep  = 1;
// int  xMaxAddStep = 10;
// int  yAddDis  = 1;
// int  yMaxAddStep = 10;
// //时间差,t1表示什么时候开始放大，t1-t2之间表示一直维持这个大小，过t2之后开始缩小
// //0<t1<=t2<1
// float t1 = 0.05f;
// float t2 = 0.06f;
// 
// //最大缩放比例
// float fFontMaxOffset = 1.0f;  //必须大于0.3f
//-------------------------------------------------
I_PlayerEffect::I_PlayerEffect():
m_dwType(eOtherEffect)
{
	guardfunc;
	m_szName[0] = 0;
	m_bHasHitPoint = false;
	unguard;
}
I_PlayerEffect::~I_PlayerEffect()
{
	guardfunc;
	unguard;
}

CFlyTextEffect::CFlyTextEffect()
{
	guardfunc;
	m_TextNodeList.clear();
	InitConfig();
	unguard;
}

// 一个数字，先后出来，一起跳走，
// 先从正常大小，暴涨到最大，然后下蹲，
// 蹲下后站起，
// 停留片刻，
// 下蹲，
// 跳起

//这个的目的是为了飘数字
BOOL CFlyTextEffect::CreateParticle( int nType, int x, int y, int nNumber, SParticle* pParticle, int nAddNumber /* = 0 */, int nWordType /*= 0*/ )
{
	guardfunc;
	int nMainNumChar = 0;
	char s[32];
	if( nAddNumber > 0 )
	{
		sprintf( s, "%ld", nNumber );
		nMainNumChar = strlen( s );
		sprintf( s, "%ld:%ld", nNumber, nAddNumber );
	}
	else
	{
		sprintf( s, "%ld", nNumber );
		nMainNumChar = strlen( s );
	}

	SFlyConfig flyConfig;
	std::map<int,SFlyConfig>::iterator it = m_FlyEffectConfig.find(nType);
	if(it != m_FlyEffectConfig.end())
	{
		flyConfig = m_FlyEffectConfig[nType];
	}

	DWORD dwLift = flyConfig.nLifeTime;

	pParticle->nMainNumChar = nMainNumChar;   //实际伤害，不包括背袭击
	pParticle->nNumChar = strlen( s );     //总数字，实际伤害 + 背袭击的伤害
	pParticle->nXDistance = 0;
	pParticle->nYDistance = 0;
	//区分是打人还是被人打
	if ( ( nWordType == GlobalTexture::eCruelHit ) && nType != eNumberRed)
		pParticle->eAddType = eAddCruelHit;
	else if (nAddNumber > 0 && nType != eNumberRed)
		pParticle->eAddType = eAddBackAttack;
	else if( nWordType == GlobalTexture::eAddExp )
		pParticle->eAddType = eAddExp;
	else if( nWordType == GlobalTexture::eAddBangGong )
		pParticle->eAddType = eAddBangGong;
	else if( nWordType == GlobalTexture::eAddMingWang )
		pParticle->eAddType = eAddMingWang;
	else if( nWordType == GlobalTexture::eAddGongXun )
		pParticle->eAddType = eAddGongXun;
	else if( nWordType == GlobalTexture::eAddAreaReputation )
		pParticle->eAddType = eAddAreaReputation;
	else if( nWordType == GlobalTexture::eAddRongYu )
		pParticle->eAddType = eAddRongYu;
	else
		pParticle->eAddType = eAddNone;

	DWORD dwTime = HQ_TimeGetTime();
	int nLeft = x - nMainNumChar * 8;
	for( int nChar = 0; nChar < pParticle->nNumChar; nChar++ )
	{
		SChar* pChar = &pParticle->chars[nChar];
		pChar->c = s[nChar];
		pChar->alpha = 0.0f;
		pChar->fLastProgress = 0.0f;

		pChar->bExplosive = true;  //此时根本不区分是否为真正的暴击，随便瞎写的,根本没实际作用
		pChar->bLinkMiddleBottomLine = false;  //默认不贴底边
		pChar->fLastProgress  = 0;

		//这里是背袭之后的的数字
		if( nChar >= nMainNumChar )
		{
			pChar->bAddNumber = true;
#ifdef _3DMOVE
			pChar->nXOffset   = 0.0f;
			pChar->nYOffset   = 0.0f;
#else
			pChar->nXOffset   = 0;
			pChar->nYOffset   = 0;
			pChar->nXDistance = 0;
			pChar->nYDistance = 0;
#endif
			if( nWordType == GlobalTexture::eCruelHit )
			{
				pChar->fScaleOffset = 2.0f;
				pChar->dwLife = dwLift;
				pChar->dwBornTime = dwTime/* + 400*/;
				pChar->x = nLeft + nMainNumChar * 20 + (nChar-nMainNumChar)*18 + 18/2;

				pChar->bottom = y - 47;
				pChar->y = pChar->bottom;


				pChar->nWidth = 128;
				pChar->nHeight = 128;
				pChar->nBornWidth = 36;
				pChar->nBornHeight = 36;
			}
			else
			{
				pChar->fScaleOffset = 0.2f;
				pChar->dwLife = dwLift;
				pChar->dwBornTime = dwTime/* + 200*/;
				pChar->x = nLeft + nMainNumChar*16 + (nChar-nMainNumChar)*12 + 12/2;
				pChar->bottom = y - 42;
				pChar->y = pChar->bottom;
				pChar->nWidth = 24;
				pChar->nHeight = 24;
				pChar->nBornWidth = 24;
				pChar->nBornHeight = 24;
			}
		}
		else
		{
			pChar->bAddNumber = false;
			pChar->bottom = y - 35;
			pChar->y = pChar->bottom;
			pChar->nXOffset = 0;
			pChar->nYOffset = 0;
			pChar->nXDistance = 0;
			pChar->nYDistance = 0;

			if( nWordType == GlobalTexture::eCruelHit )
			{
				pChar->fScaleOffset = 2.0f;
				pChar->dwLife = dwLift;
				pChar->dwBornTime = dwTime;
				pChar->x = nLeft + nChar * 24 + 24/2;

				pChar->nWidth = 128;     //实际宽度
				pChar->nHeight = 128;

				pChar->nBornWidth = 36;   //出身宽度有什么用
				pChar->nBornHeight = 36;
			}
			else
			{
				pChar->fScaleOffset = 0.2f;
				pChar->dwLife = dwLift;
				pChar->dwBornTime = dwTime;
				pChar->x = nLeft + nChar*16 + 16/2;
				pChar->nWidth = 32;
				pChar->nHeight = 32;
				pChar->nBornWidth = 32;
				pChar->nBornHeight = 32;
			}
		}
		pChar->bSecond = false;
		pChar->dwSecondTime = 0;
	}

	GetBillBoard()->SetTipCounts(FRIST_FIGHT_BACKATTACK);
	return TRUE;
	unguard;
}
void CFlyTextEffect::Create( int nType, int x, int y, int nNumber, int nTextNodeID /*= -1*/, BOOL bNeedUpdatePos /*= FALSE*/, D3DXVECTOR3 vPos /*= D3DXVECTOR3( 0, 0, 0 )*/, int nAddNumber /*= 0*/, int nWordType /*= 0*/ )
{
	guardfunc;

	//如果是数字，但是伤害为0，则不显示
	if( nType != eDodge && nType != eMiss && nType != eBackAttck &&
		nType != eDefence && nType != eWard && nType != eResist &&
		nType != eMonsterWard && nType != eMonsterResist )
	{
		if (nNumber == 0)
		{
			return;
		}
	}

	SFlyConfig flyConfig;
	std::map<int,SFlyConfig>::iterator it = m_FlyEffectConfig.find(nType);
	if(it != m_FlyEffectConfig.end())
	{
		flyConfig = m_FlyEffectConfig[nType];
	}

	x += flyConfig.nXBaseOffset;
	y += flyConfig.nYBaseOffset;

	DWORD dwLift = flyConfig.nLifeTime;

	//????Particle  和数字坐标有什么区别----??
	BOOL bExistTextNode = FALSE;
	for( list<STextNode>::iterator it = m_TextNodeList.begin(); it != m_TextNodeList.end();	it++ )
	{
		STextNode& TextNode = *it;

		if( TextNode.nID == nTextNodeID ) //nTextNodeID为角色ID
		{
			bExistTextNode = TRUE;

			//TextNode.vPos = vPos;

			SParticle particle;
			particle.dwStartTime = HQ_TimeGetTime();
			particle.dwLastUpdateTime = particle.dwStartTime;
			particle.dwLife = dwLift;

			particle.nType = nType;
			particle.x = x;
			particle.y = y;
			particle.nBottom = 0;//y - 32;

			particle.nCol = 0;  //这个的作用是什么啊
			particle.bNeedUpdatePos = FALSE;   //这个也没什么实际作用。我晕
			particle.bShowInLeftLine = FALSE;
			particle.bShowInRightLine = FALSE;
			particle.bLinkBottomLine = FALSE;

			particle.vPos = vPos;
			particle.fAlpha = 0.0f;
			particle.dwColor = 0xffffffff;

			particle.nSrcWidth = 64;
			particle.nSrcHeight = 32;
			particle.nWidth = particle.nSrcWidth;
			particle.nHeight = particle.nSrcHeight;
			particle.nNumber = nNumber;

			//if(nWordType == GlobalTexture::eAddExp)
			{
				int nCount = 0;
				std::list<SParticle> &listSet = it->DynamicParticleList;
				for (std::list<SParticle>::iterator itList = listSet.begin(); itList != listSet.end();++itList)
				{
					if(itList->eAddType == nWordType/*eAddExp*/&&HQ_TimeGetTime() - itList->dwStartTime < 200)
						++nCount;
				}

				static int nLen = 18;

				particle.nBottom = nCount * nLen;
			}

			CreateParticle( nType, particle.x, particle.y, nNumber, &particle, nAddNumber, nWordType );

			// 			if( nWordType == GlobalTexture::eCruelHit )
			// 			{
			// 				TextNode.StaticParticleList.push_front( particle );
			// 			}
			// 			else
			{
				TextNode.DynamicParticleList.push_front( particle );
			}
		}
	}

	if( !bExistTextNode )
	{
		STextNode textnode;
		textnode.nID = nTextNodeID;
		//textnode.vPos = vPos;
		textnode.StaticParticleList.clear();
		textnode.DynamicParticleList.clear();

		SParticle particle;
		particle.dwStartTime = HQ_TimeGetTime();
		particle.dwLastUpdateTime = particle.dwStartTime;
		particle.dwLife = dwLift;
		particle.nType = nType;
		particle.x = x;
		particle.y = y;
		particle.nBottom = 0;//y - 32;
		particle.nCol = 0;
		particle.bNeedUpdatePos = FALSE;
		particle.bShowInLeftLine = FALSE;
		particle.bShowInRightLine = FALSE;
		particle.bLinkBottomLine = FALSE;
		particle.vPos = vPos;
		particle.fAlpha = 0.0f;
		particle.dwColor = 0xffffffff;
		particle.nSrcWidth = 64;
		particle.nSrcHeight = 32;
		particle.nWidth = particle.nSrcWidth;
		particle.nHeight = particle.nSrcHeight;
		particle.nNumber = nNumber;

		CreateParticle( nType, particle.x, particle.y, nNumber, &particle, nAddNumber, nWordType );

		textnode.DynamicParticleList.push_back( particle );
		m_TextNodeList.push_back( textnode );
	}
	unguard;
}

void CFlyTextEffect::Update()
{
	guardfunc;
	DWORD dwTime = HQ_TimeGetTime();
	list<STextNode>::iterator itNext;

	for( list<STextNode>::iterator it = m_TextNodeList.begin(); it != m_TextNodeList.end(); )
	{
		itNext = it;
		itNext++;

		STextNode& TextNode = *it;

		BOOL bNeedUpdatePos = FALSE;

		CPlayer* pPlayer = NULL;

		if( TextNode.nID >= 0 )
		{
			pPlayer = theHeroGame.GetPlayerMgr()->FindByID(TextNode.nID);

			bNeedUpdatePos = TRUE;
		}

		list<SParticle>::iterator itNextParticle;
		///////////////////////////////
		for( list<SParticle>::iterator itParticle = TextNode.DynamicParticleList.begin(); itParticle != TextNode.DynamicParticleList.end(); )
		{
			itNextParticle = itParticle;
			itNextParticle++;
			SParticle& Particle = *itParticle;

			if( dwTime - Particle.dwStartTime > Particle.dwLife )
			{
				TextNode.DynamicParticleList.erase( itParticle );
				itParticle = itNextParticle;
				continue;
			}

			//if( bFirstParticle )
			// 			{
			// 				if( bNeedUpdatePos )
			// 				{
			if (pPlayer)
			{
				Particle.vPos = pPlayer->GetPos();
				Particle.vPos.z += g_fTheRoleBBoxHeight;
				Particle.bNeedUpdatePos = TRUE;
			}

			World2Screen( Particle.vPos, Particle.x, Particle.y );
			//                     if(Particle.nType == eNumberAddEXP)
			//                         Particle.y += 190;
			// 				}
			// 			}

			switch( Particle.nType )
			{
			case	eMiss:				//未命中
			case	eDodge:				//躲避
			case	eMonsterWard:		//怪物招架
			case	eWard:				//招架
			case	eMonsterResist:		//怪物抵抗
			case	eResist:			//抵抗
				//case	eDefence:			//抵抗
				//case	eCruelHit:
				//case	eDeathHit:
				//case	eBackAttck:			//背击
				{
					UpdateTextParticle( Particle.x, Particle.y, &Particle);
				}
				break;
			case eNumberRed:
			case eNumberGreen:
			case eNumberBeAttackYellow:
				{
					UpdateHpData( Particle.x, Particle.y, &Particle);
				}
				break;
			case eNumberWhite:
			case eNumberYellow:
			case eNumberAttackWhite:
			case eNumberBlue:
			case eNumberAddEXP:
			case eNumberBangGong:
			case eNumberMingWang:
			case eNumberGongXun:
			case eNumberAreaReputation:
			case eNumberRongYu:
				{
					UpdateHpData( Particle.x, Particle.y, &Particle);
				}
				break;
			}

			itParticle = itNextParticle;
		}

		if( TextNode.DynamicParticleList.size() == 0 && TextNode.StaticParticleList.size() == 0 )
		{
			m_TextNodeList.erase( it );
		}
		it = itNext;
	}
	unguard;
}

void CFlyTextEffect::UpdateTextParticle( int x, int y, SParticle* pParticle)
{
	guardfunc;
	SFlyConfig flyConfig;
	std::map<int,SFlyConfig>::iterator it = m_FlyEffectConfig.find(pParticle->nType);
	if(it != m_FlyEffectConfig.end())
		flyConfig = m_FlyEffectConfig[pParticle->nType];

	//调整位置
	if(pParticle->bNeedUpdatePos)
	{
		pParticle->x += pParticle->nXDistance + flyConfig.nXBaseOffset;
		pParticle->y += pParticle->nYDistance + flyConfig.nYBaseOffset;
	}

	DWORD dwTime = HQ_TimeGetTime();
	float fAlpha = 1.0f;
	if( dwTime < pParticle->dwStartTime )
		return;


	int nPosX = 0,nPosY = 0;
	int nTimePassed = dwTime - pParticle->dwStartTime;
	//运动轨迹
	float fRate = ((float)nTimePassed)/flyConfig.fMoveTime;
	if(fRate >= 1.0f)
		return;

	//横向飞行
	if(flyConfig.nYMaxMoveDis != 0)
	{
		if(flyConfig.nYMaxMoveDis >= 0)
		{
			if(pParticle->nYDistance >= flyConfig.nYMaxMoveDis)
				return;
		}
		else
		{
			if(pParticle->nYDistance <= flyConfig.nYMaxMoveDis)
				return;
		}
	}

	//上下飞行
	if(flyConfig.nXMaxMoveDis != 0)
	{
		if(flyConfig.nXMaxMoveDis >= 0)
		{
			if(pParticle->nXDistance >= flyConfig.nXMaxMoveDis)
				return;
		}
		else
		{
			if(pParticle->nXDistance <= flyConfig.nXMaxMoveDis)
				return;
		}
	}


	//左右移动
	nPosX = flyConfig.nXMaxMoveDis/flyConfig.fMoveTime * 1000 + flyConfig.nAccel * nTimePassed /pParticle->dwLife;//flyConfig.nXMaxMoveDis * fRate;
	//上下移动
	nPosY = flyConfig.nYMaxMoveDis/flyConfig.fMoveTime * 1000 + flyConfig.nAccel * nTimePassed /pParticle->dwLife;	

	pParticle->nXDistance += nPosX;
	pParticle->nYDistance += nPosY;

	fAlpha = GetAlpha(flyConfig,pParticle->nXDistance,pParticle->nYDistance);

	pParticle->x += nPosX;
	pParticle->y += nPosY;

	pParticle->fAlpha = fAlpha;
	unguard;
}

extern void DrawNumberCharBitmap( int x, int y, int w, int h, int start_line, DWORD color, int nNumber, Simple2DVertex vertex[] );
void CFlyTextEffect::DrawParticle( SParticle* pParticle )
{
	guardfunc;
	static Simple2DVertex v[1024];
	DWORD dwTime = HQ_TimeGetTime();
	int nNumDrawChar = 0;

	int nTexId = GlobalTexture::GetTexture(GlobalTexture::eNumberRed  );
	int _iColor = 0;					//根据输入的颜色转换到相应的行数
	if ( pParticle->nType == eNumberRed)
	{
		_iColor = 2;
	}else if ( pParticle->nType == eNumberGreen) {
		_iColor = 3;
	}else if ( pParticle->nType == eNumberYellow) {
		_iColor = 1;
	}else if ( pParticle->nType == eNumberBlue) {
		_iColor = 0;
		nTexId = GlobalTexture::GetTexture(GlobalTexture::eNumber2  );
	}else if( pParticle->nType == eNumberBeAttackYellow){
		//被玩家攻击为红色字体
		_iColor = 2;
		nTexId = GlobalTexture::GetTexture(GlobalTexture::eNumber4);
	}
	else if( pParticle->nType == eNumberAttackWhite){
		//攻击玩家为黄色字体
		_iColor = 1;
		nTexId = GlobalTexture::GetTexture(GlobalTexture::eNumber4);
	}
	else if(pParticle->nType == eNumberAddEXP){
		_iColor = 0;
		nTexId = GlobalTexture::GetTexture(GlobalTexture::eNumber3);
	}
	else if(pParticle->nType == eNumberBangGong){
		_iColor = 1;
		nTexId = GlobalTexture::GetTexture(GlobalTexture::eNumber3);
	}
	else if(pParticle->nType == eNumberMingWang){
		_iColor = 1;
		nTexId = GlobalTexture::GetTexture(GlobalTexture::eNumber3);
	}
	else if(pParticle->nType == eNumberGongXun){
		_iColor = 1;
		nTexId = GlobalTexture::GetTexture(GlobalTexture::eNumber3);
	}
	else if(pParticle->nType == eNumberAreaReputation){
		_iColor = 1;
		nTexId = GlobalTexture::GetTexture(GlobalTexture::eNumber3);
	}
	else if( pParticle->nType == eNumberRongYu ){
		_iColor = 1;
		nTexId = GlobalTexture::GetTexture(GlobalTexture::eNumber3);
	}
	else if ( pParticle->nType == eNumberAddSkillEXP )
	{
		_iColor = 1;
		nTexId = GlobalTexture::GetTexture(GlobalTexture::eAddSkillExp);
	}

	else{
		_iColor = 0;
	}

	SFlyConfig flyConfig;
	std::map<int,SFlyConfig>::iterator it = m_FlyEffectConfig.find(pParticle->nType);
	if(it != m_FlyEffectConfig.end())
	{
		flyConfig = m_FlyEffectConfig[pParticle->nType];
		if(!flyConfig.strPicPath.empty())
			nTexId = GetTextureId(flyConfig.strPicPath);
	}

	DWORD alpha = 0;

	for( int nChar = 0; nChar < pParticle->nNumChar; nChar++ )
	{
		SChar* pChar = &pParticle->chars[nChar];
		if( dwTime < pChar->dwBornTime ||
			dwTime > pChar->dwBornTime+pChar->dwLife )
			continue;

		int nValue = pChar->alpha*255;
		if(nValue < 0)
			nValue = 0;
		if(nValue > 255)
			nValue = 255;
		alpha = (DWORD)nValue;

		//alpha = (DWORD)(pChar->alpha*255);
		//alpha = alpha<255?alpha:255;
		DrawNumberCharBitmap( 
			pChar->x-pChar->nWidth/2,
			pChar->y-pChar->nHeight,
			pChar->nWidth,
			pChar->nHeight,
			_iColor,						//1,		sbw_modify
			alpha<<24|0x00ffffff, 
			pChar->c - '0', 
			&v[nNumDrawChar*4] );
		nNumDrawChar++;
	}

	if(  nNumDrawChar > 0 )
	{
		GetEngine()->GetRenderer()->DirectPushSurface(
			nTexId,
			-1, 
			OBJECT2D_SHADER, 
			Simple2DVertex_FVF,
			sizeof( Simple2DVertex ), 
			(BYTE*)v,
			4*nNumDrawChar,
			(BYTE*)Emitter::GetCCWIndexBuffer(),
			2*nNumDrawChar, 
			eAlphaBlend|eLinearFilter );


		SParticle& Particle = *pParticle;

		if (Particle.eAddType == eAddNone)
			return;

		//获得纹理ID
		short idx = 0;
		if (Particle.eAddType == eAddBackAttack)
			idx = GlobalTexture::GetTexture( GlobalTexture::eBackAttck );
		else if (Particle.eAddType == eAddCruelHit)
			idx = GlobalTexture::GetTexture( GlobalTexture::eCruelHit );
		else if( Particle.eAddType == eAddExp )
			idx = GlobalTexture::GetTexture( GlobalTexture::eAddExp );
		else if( Particle.eAddType == eAddBangGong )
			idx = GlobalTexture::GetTexture( GlobalTexture::eAddBangGong );
		else if( Particle.eAddType == eAddMingWang )
			idx = GlobalTexture::GetTexture( GlobalTexture::eAddMingWang );
		else if( Particle.eAddType == eAddGongXun )
			idx = GlobalTexture::GetTexture( GlobalTexture::eAddGongXun );
		else if( Particle.eAddType == eAddAreaReputation )
			idx = GlobalTexture::GetTexture( GlobalTexture::eAddAreaReputation );
		else if( Particle.eAddType == eAddRongYu )
			idx = GlobalTexture::GetTexture( GlobalTexture::eAddRongYu );

		//设置顶点颜色 
		DWORD dwAlpha = (Particle.dwColor&0xff000000)>>24;
		dwAlpha = (DWORD)(dwAlpha*Particle.chars[0].alpha);
		if( dwAlpha > 255 )
			dwAlpha = 255; 
		DWORD dwColor = dwAlpha<<24|(Particle.dwColor&0x00ffffff);

		// #ifdef _DEBUG
		//     char szWord[256];
		//     sprintf_s(szWord,sizeof(szWord),"Alpha:%d",alpha);
		//     GetFontManager()->DrawText(szWord,300,200,DT_NOCLIP,0xffff0000,2);
		// #endif
		//设置矩形方框的大小
		//矩形方框定位的方法为:取顶点缓冲的第一个顶点为基准坐标 - 需要显示的数字宽度 - 字体的缩放(可能存在暴击的情况)
		//最终坐标 = 基准坐标 + 数字的偏移坐标

		RECT rect;
		//int nScaleOffset = 6.0f; //这里写成的是固定值不是很精确
		SChar* pChar = &pParticle->chars[0];
		int nScaleOffset = pChar->fScaleOffset;

		rect.right = v[0].p.x;
		rect.left  = rect.right - pParticle->nWidth - nScaleOffset; 
		rect.top   = v[1].p.y - nScaleOffset;
		rect.bottom = rect.top + pParticle->nHeight;

		Draw(rect,idx,dwColor);
	}
	unguard;
}
void CFlyTextEffect::Render()
{
	guardfunc;
	Simple2DVertex vertex[4];
	DWORD dwTime = HQ_TimeGetTime();
	list<STextNode>::iterator itNext;

	for( list<STextNode>::iterator it = m_TextNodeList.begin(); it != m_TextNodeList.end(); )
	{
		itNext = it;
		itNext++;
		STextNode& TextNode = *it;

		list<SParticle>::iterator itNextParticle;

		///////////////////////////////////////
		for( list<SParticle>::iterator itParticle = TextNode.StaticParticleList.begin(); itParticle != TextNode.StaticParticleList.end(); )
		{
			itNextParticle = itParticle;
			itNextParticle++;
			SParticle& Particle = *itParticle;

			if( dwTime - Particle.dwStartTime > Particle.dwLife )
			{
				TextNode.StaticParticleList.erase( itParticle );
				itParticle = itNextParticle;
				continue;
			}

			DWORD color = Particle.dwColor;

			switch( Particle.nType )
			{
			case eNumberWhite:
			case eNumberRed:
			case eNumberGreen:
			case eNumberYellow:
			case eNumberBlue:
			case eNumberBeAttackYellow:
			case eNumberAttackWhite:
				DrawParticle(&Particle);
				break;
			}
			itParticle = itNextParticle;
		}


		/////////////////////////////////////////
		//for( list<SParticle>::iterator itParticle = TextNode.DynamicParticleList.begin(); itParticle != TextNode.DynamicParticleList.end(); )
		list<SParticle>::reverse_iterator reIter;
		for (list<SParticle>::reverse_iterator itParticle = TextNode.DynamicParticleList.rbegin(); itParticle != TextNode.DynamicParticleList.rend();  )
		{
			SParticle& Particle = *itParticle;
			//itNextParticle = itParticle;
			//itNextParticle++;
			reIter = itParticle;
			reIter++;

			if( dwTime - Particle.dwStartTime > Particle.dwLife )
			{
				itParticle = list<SParticle>::reverse_iterator(TextNode.DynamicParticleList.erase( (++itParticle).base()/*itParticle*/ ));
				//itParticle = itNextParticle;
				continue;
			}

			DWORD color = Particle.dwColor;

			switch( Particle.nType )
			{
			case	eMiss:				//未命中aw
			case	eMonsterWard:		//怪物招架
			case	eMonsterResist:		//怪物抵抗
			case	eDodge:				//躲避
			case	eBackAttck:			//背击
			case	eDefence:			//抵抗
			case	eWard:				//招架
			case	eResist:
			case	eCruelHit:
			case	eDeathHit:
				{
					DrawText(Particle);
				}
				break;
			case eNumberWhite:
			case eNumberRed:
			case eNumberGreen:
			case eNumberYellow:
			case eNumberBlue:
			case eNumberAddEXP:
			case eNumberAddSkillEXP:
			case eNumberBangGong:
			case eNumberMingWang:
			case eNumberGongXun:
			case eNumberAreaReputation:
			case eNumberBeAttackYellow:
			case eNumberAttackWhite:
			case eNumberRongYu:
				DrawParticle(&Particle);
				break;
			}

			//++iter;// = reNextIter;
			itParticle = reIter;//itNextParticle;
		}

		if( TextNode.DynamicParticleList.size() == 0 && TextNode.StaticParticleList.size() == 0 )
		{
			m_TextNodeList.erase( it );
		}
		it = itNext;
	}
	unguard;
}

void  CFlyTextEffect::DrawText(SParticle& Particle)
{
	int nScaleOffset = 6.0f;
	RECT rect;
	rect.left   = Particle.x - Particle.nWidth/2 - nScaleOffset;
	rect.top    = Particle.y  - Particle.nHeight - nScaleOffset;
	rect.right  = Particle.x + Particle.nWidth/2 + nScaleOffset;
	rect.bottom = Particle.y + nScaleOffset;

	float z = 0.2f;
	Simple2DVertex vertex[4];
	DWORD dwColor = Particle.dwColor;
	DWORD dwAlpha = (dwColor&0xff000000)>>24;

	dwAlpha = (DWORD)(dwAlpha*Particle.fAlpha);
	if( dwAlpha > 255 )
		dwAlpha = 255;

	dwColor = dwAlpha<<24|(dwColor&0x00ffffff);

	short idx = 0;
	if ( Particle.nType == eMiss )
	{
		idx = GlobalTexture::GetTexture( GlobalTexture::eMiss );
	}
	else if( Particle.nType == eMonsterWard )
	{
		idx = GlobalTexture::GetTexture( GlobalTexture::eWard );
	}
	else if( Particle.nType == eMonsterResist )
	{
		idx = GlobalTexture::GetTexture( GlobalTexture::eResist );
	}
	else if( Particle.nType == eResist )
	{
		idx = GlobalTexture::GetTexture( GlobalTexture::eResist );
	}
	else if( Particle.nType == eDodge )
	{
		idx = GlobalTexture::GetTexture( GlobalTexture::eDodge );
	}
	else if( Particle.nType == eBackAttck )
	{
		idx = GlobalTexture::GetTexture( GlobalTexture::eBackAttck );
	}
	else if ( Particle.nType == eDefence )
	{
		idx = GlobalTexture::GetTexture( GlobalTexture::eDefence );
	}
	else if ( Particle.nType == eWard )
	{
		idx = GlobalTexture::GetTexture( GlobalTexture::eWard );
	}
	else if ( Particle.nType == eCruelHit )
	{
		idx = GlobalTexture::GetTexture( GlobalTexture::eCruelHit );
	}
	else if ( Particle.nType == eDeathHit )
	{
		idx = GlobalTexture::GetTexture( GlobalTexture::eDeathHit );
	}

	SFlyConfig flyConfig;
	std::map<int,SFlyConfig>::iterator it = m_FlyEffectConfig.find(Particle.nType);
	if(it != m_FlyEffectConfig.end())
	{
		flyConfig = m_FlyEffectConfig[Particle.nType];
		if(!flyConfig.strPicPath.empty())
			idx = GetTextureId(flyConfig.strPicPath);
	}

	Draw(rect,idx,dwColor);
}

void  CFlyTextEffect::Draw(RECT &rect,short textureID,DWORD dwColor)
{
	float z = 0.2f;
	Simple2DVertex vertex[4];
	static short index[] = { 0, 1, 2, 2, 1, 3 };

	vertex[0].p = D3DXVECTOR4( rect.left, rect.bottom, z, 1 );
	vertex[0].color = dwColor;
	vertex[0].u = 0;
	vertex[0].v = 1;

	vertex[1].p = D3DXVECTOR4( rect.left, rect.top, z, 1 );
	vertex[1].color = dwColor;
	vertex[1].u = 0;
	vertex[1].v = 0;

	vertex[2].p = D3DXVECTOR4( rect.right, rect.bottom, z, 1 );
	vertex[2].color = dwColor;
	vertex[2].u = 1;
	vertex[2].v = 1;

	vertex[3].p = D3DXVECTOR4( rect.right, rect.top, z, 1 );
	vertex[3].color = dwColor;
	vertex[3].u = 1;
	vertex[3].v = 0;

	GetEngine()->GetRenderer()->DirectPushSurface(
		textureID,
		-1, 
		OBJECT2D_SHADER, 
		Simple2DVertex_FVF,
		sizeof( Simple2DVertex ), 
		(BYTE*)vertex,
		4,
		(BYTE*)index,
		2, eAlphaBlend|eLinearFilter );
}

void CFlyTextEffect::UpdateHpData( int x, int y, SParticle* pParticle)
{
	DWORD dwTime = HQ_TimeGetTime();
	float fAlpha = 1.0f;
	int nBottomLine = 0;
	int nXOffset  = 0;
	int nYOffset = 0;
	int nMainNumChar = pParticle->nMainNumChar;

	SFlyConfig flyConfig;
	std::map<int,SFlyConfig>::iterator it = m_FlyEffectConfig.find(pParticle->nType);
	if(it != m_FlyEffectConfig.end())
	{
		flyConfig = m_FlyEffectConfig[pParticle->nType];
	}

	for( int nChar = 0; nChar < pParticle->nNumChar; nChar++ )
	{
		SChar* pChar = &pParticle->chars[nChar];

		float w = pChar->nBornWidth;
		float h = pChar->nBornHeight;

		if( dwTime < pChar->dwBornTime )
			continue;

		if(pParticle->bNeedUpdatePos)
		{
			int nLeft = x - nMainNumChar * 8;
			//这里是背袭之后的的数字
			if( nChar >= nMainNumChar )
			{
				if( pParticle->eAddType == GlobalTexture::eCruelHit )
				{
					pChar->x = nLeft + nMainNumChar * 20 + (nChar-nMainNumChar)*18 + 18/2 + flyConfig.nXBaseOffset + pChar->nXDistance;
					pChar->bottom = y - 47 + flyConfig.nYBaseOffset + pChar->nYDistance + pParticle->nBottom;
					pChar->y = pChar->bottom;
				}
				else
				{
					pChar->x = nLeft + nMainNumChar*16 + (nChar-nMainNumChar)*12 + 12/2 + flyConfig.nXBaseOffset + pChar->nXDistance;
					pChar->bottom = y - 42 + flyConfig.nYBaseOffset  + pChar->nYDistance + pParticle->nBottom;
					pChar->y = pChar->bottom;
				}
			}
			else
			{
				if( pParticle->eAddType == GlobalTexture::eCruelHit )
				{
					pChar->x = nLeft + nChar * 24 + 24/2 + flyConfig.nXBaseOffset + pChar->nXDistance;
					pChar->bottom = y - 47 + flyConfig.nYBaseOffset + pChar->nYDistance + pParticle->nBottom;
					pChar->y = pChar->bottom;
				}
				else
				{
					pChar->x = nLeft + nChar*16 + 16/2 +  flyConfig.nXBaseOffset + pChar->nXDistance;
					pChar->bottom = y - 35 + flyConfig.nYBaseOffset + pChar->nYDistance + pParticle->nBottom;
					pChar->y = pChar->bottom;
				}
			}
		}

		int nPosX = 0,nPosY = 0;
		int nTimePassed = dwTime - pChar->dwBornTime;
		//运动轨迹
		float fRate = ((float)nTimePassed)/flyConfig.fMoveTime;
		//if(nTimePassed < flyConfig.fMoveTime)
		if(fRate >= 1.0f)
			continue;

		if(pChar->bSecond)
		{
			int nPassed = HQ_TimeGetTime() - pChar->dwSecondTime;
			static int nStop = 300;
			if(nPassed < nStop)
				continue;
			else
			{
				static int nTotalTime = 1000;
				float fT = (float)(nPassed - nStop)/nTotalTime;
				static float fd = 1.5f;

				if(flyConfig.fInitAlpha == flyConfig.fOverAlpha)
				{


					pChar->alpha = 1-fT/fd;

					//pChar->alpha = 1 - fT;
					if(pChar->alpha < 0)
						pChar->alpha = 0;

					if(pChar->alpha > 1)
						pChar->alpha = 1;
				}

				static int nLen = 20;
				static int nMaxLen = 40;
				static float fR1 = 0.8;
				int nVOffset = nLen * fT;


				//				nVOffset = nMaxLen - fR1 *  fT;

				//  				nVOffset = nMaxLen * sinf(fT*D3DX_PI*0.5f); 
				//  				pChar->x -= nLen * fT;
				pChar->y -= nVOffset;

				if(flyConfig.nXMaxMoveDis != 0)
				{
					if(flyConfig.nXMaxMoveDis < 0)
						pChar->x -= nVOffset;
					else
						pChar->x += nVOffset;
				}

				if(flyConfig.nYMaxMoveDis != 0)
				{
					if(flyConfig.nYMaxMoveDis < 0)
						pChar->y -= nVOffset;
					else
						pChar->y += nVOffset;
				}
				continue;
			}
		}

		if(flyConfig.nYMaxMoveDis != 0)
		{
			if(flyConfig.nYMaxMoveDis >= 0)
			{
				if(pChar->nYDistance >= flyConfig.nYMaxMoveDis)
				{
					pChar->bSecond = true;
					pChar->dwSecondTime = HQ_TimeGetTime();
					continue;
				}
			}
			else
			{
				if(pChar->nYDistance <= flyConfig.nYMaxMoveDis)
				{
					pChar->bSecond = true;
					pChar->dwSecondTime = HQ_TimeGetTime();
					continue;
				}
			}
		}

		if(flyConfig.nXMaxMoveDis != 0)
		{
			if(flyConfig.nXMaxMoveDis >= 0)
			{
				if(pChar->nXDistance > flyConfig.nXMaxMoveDis)
				{
					pChar->bSecond = true;
					pChar->dwSecondTime = HQ_TimeGetTime();
					continue;
				}
			}
			else
			{
				if(pChar->nXDistance <= flyConfig.nXMaxMoveDis)
				{
					pChar->bSecond = true;
					pChar->dwSecondTime = HQ_TimeGetTime();
					continue;
				}
			}
		}

		//左右移动
		nPosX = flyConfig.nXMaxMoveDis/flyConfig.fMoveTime * 1000 + flyConfig.nAccel * (flyConfig.fMoveTime - nTimePassed) /1000;  //flyConfig.nXMaxMoveDis * fRate;//dwTimePassed / flyConfig.fMoveTime;
		//上下移动
		nPosY = flyConfig.nYMaxMoveDis/flyConfig.fMoveTime * 1000 + flyConfig.nAccel * (flyConfig.fMoveTime - nTimePassed) /1000;//flyConfig.nYMaxMoveDis * fRate;//dwTimePassed / flyConfig.fMoveTime;	

		//累计移动长度
		pChar->nXDistance += nPosX;
		pChar->nYDistance += nPosY;

		pChar->nXOffset = nPosX;
		pChar->nYOffset = nPosY;

		//获得Alpha
		pChar->alpha = GetAlpha(flyConfig,pChar->nXDistance,pChar->nYDistance);

		//缩放比例
		float t = ((float)nTimePassed)/pChar->dwLife;
		float fMaxOffset = pChar->fScaleOffset;
		//这里做个限制，禁止超过策划设置的最大值
		if(fMaxOffset > flyConfig.fMaxScale)
		{
			fMaxOffset = flyConfig.fMaxScale;
			pChar->fScaleOffset = flyConfig.fMaxScale;
		}


		if( false/*pChar->bAddNumber*/ )
		{
			/*
			pChar->alpha = fAlpha;
			if( fMaxOffset > 0.3 )
			{
			int nStep = 0;
			int nLeft = 0;

			// 出身
			if( t < flyConfig.fTime1 )
			{
			pChar->nHeight = h;
			pChar->nWidth  = w;

			nStep = w/2;
			nLeft = x + nMainNumChar * 48/2/2 + pChar->nXOffset;
			pChar->y = nBottomLine;
			pChar->x = nLeft + (nChar - nMainNumChar) * nStep + nStep/2 + nXOffset;
			}
			// 停留
			else if(t >= flyConfig.fTime1&&t < flyConfig.fTime2)
			{
			nStep = w/2 + w/2 * fMaxOffset;
			nLeft = x + nMainNumChar*48/2/2 + pChar->nXOffset;
			pChar->x = nLeft + (nChar - nMainNumChar) * nStep + nStep/2 + nXOffset;
			pChar->y = nBottomLine;

			pChar->nWidth = w + w * fMaxOffset;
			pChar->nHeight = h + h * fMaxOffset;
			}
			else //缩小
			{
			nLeft = x + nMainNumChar*48/2/2 + pChar->nXOffset;
			pChar->x = nLeft + (nChar - nMainNumChar) * w/2 + w/4 + nXOffset;
			pChar->y = nBottomLine;

			pChar->nWidth = w + w * cosf(t * D3DX_PI) * flyConfig.fFontMaxScale;
			pChar->nHeight = h + h * cosf(t * D3DX_PI) * flyConfig.fFontMaxScale;
			if(pChar->nWidth < w)
			pChar->nWidth = w;
			if(pChar->nHeight < h)
			pChar->nHeight = h;
			}

			if( t > 0.7f &&pChar->alpha >= flyConfig.fOverAlpha)
			{
			pChar->alpha = (1-t)/0.3f;
			}

			}
			else
			{
			pChar->nWidth = w;
			pChar->nHeight = h;
			pChar->alpha = fAlpha;
			pChar->y     = nBottomLine;
			pChar->x     += nXOffset;

			if( t > 0.6f&&pChar->alpha >= flyConfig.fOverAlpha)
			{
			pChar->alpha = (1-t)/0.4f;
			}
			}
			*/
		}
		else
		{
			//这是缩放比例
			if(fMaxOffset > 0.3)
			{
				/*
				int nStep = 0;
				int nLeft = 0;

				float segment[2] = {0.05f,0.4f};
				// 小于时间t1的时候，位置原大小
				if( t < segment[0] )
				{
				pChar->nHeight = h;
				pChar->nWidth  = w;

				nStep = w/2 + w/2 * flyConfig.fMaxScale;
				nLeft = x - nMainNumChar*nStep/2;

				}
				else if(t >= segment[0] && t <segment[1])//字体表达
				{
				pChar->nHeight = h + h * flyConfig.fMaxScale;
				pChar->nWidth  = w + w * flyConfig.fMaxScale;

				nStep = w/2 + w/2 * flyConfig.fMaxScale;
				nLeft = x - nMainNumChar*nStep/2;
				}
				else//开始缩小
				{
				nStep = w/2;
				nLeft = x - nMainNumChar*nStep/2;

				pChar->nWidth = w + w * cosf(t * D3DX_PI) * flyConfig.fMaxScale;
				pChar->nHeight = h + h * cosf(t * D3DX_PI) * flyConfig.fMaxScale;
				if(pChar->nWidth < w)
				pChar->nWidth = w;
				if(pChar->nHeight < h)
				pChar->nHeight = h;
				}

				if( t > 0.7f &&pChar->alpha >= flyConfig.fOverAlpha)
				{
				pChar->alpha = (1-t)/0.3f;
				}

				pChar->x = nLeft + nChar * nStep + nStep/2 + pChar->nXOffset;
				pChar->y += pChar->nYOffset;
				*/

				float segment[2] =
				{
					0.05f,
					0.4f,
				};

				if( t >= segment[0] && pChar->fLastProgress < segment[0] )
				{
					pChar->nHeight = h;
					pChar->nWidth = w;
					pChar->alpha = 1.0f;
				}

				if( t < segment[0] )
				{
					float k = 0.02f;
					if( t < k )
					{
						float d = t/k;
						pChar->nHeight = h + h*fMaxOffset;
						pChar->nWidth = w + w*fMaxOffset;
						//pChar->y = pChar->bottom - (( h - pChar->nHeight )/2);
						int nStep = w/2 + w/2*fMaxOffset;
						int nLeft = x - nMainNumChar*nStep/2;
						pChar->x = nLeft + nChar*nStep + nStep/2;
					}
					else
					{
						float d = (t-k)/(segment[0]-k);
						pChar->nHeight = h + h*cosf( d*D3DX_PI*0.5f )*fMaxOffset;
						pChar->nWidth = w + w*cosf( d*D3DX_PI*0.5f )*fMaxOffset;
						//pChar->y = pChar->bottom - (( h - pChar->nHeight )/2);
						int nStep = w/2 + w/2*cosf( d*D3DX_PI*0.5f )*fMaxOffset;
						int nLeft = x - nMainNumChar*nStep/2;
						pChar->x = nLeft + nChar*nStep + nStep/2;
					}
				}
				else if( t < segment[1] )
				{
					int nStep = w/2;
					int nLeft = x - nMainNumChar*nStep/2;
					pChar->x = nLeft + nChar*nStep + nStep/2;
					//pChar->y = pChar->bottom;
				}
				else
				{
					int nStep = w/2;
					int nLeft = x - nMainNumChar*nStep/2;
					pChar->x = nLeft + nChar*nStep + nStep/2;

					if( t > 0.7f )
					{
						pChar->alpha = (1-t)/0.3f;
					}
				}

				pChar->x += pChar->nXOffset;
				pChar->y += pChar->nYOffset;
			}
			else
			{
				pChar->nHeight = h;
				pChar->nWidth  = w;

				pChar->x += pChar->nXOffset;
				pChar->y += pChar->nYOffset;  
			}

			nBottomLine = pChar->y - 2;
			nXOffset = pChar->nXOffset;
			nYOffset = pChar->nYOffset;

			fAlpha = pChar->alpha;
		}
		pParticle->fAlpha = pChar->alpha;
	}
}

bool CFlyTextEffect::InitConfig()
{
	MeXmlDocument doc;
	char szWord[256] = {0};
	MeSprintf_s(szWord,sizeof(szWord),"%s\\Data\\ClientConfig\\GameSetting.config",GetRootPath());
	if( !doc.LoadFile(szWord) )
		return false;

	m_FlyEffectConfig.clear();

	MeXmlElement* pRoot = doc.FirstChildElement("Project")->FirstChildElement("FontFlyEffect");
	if(pRoot)
	{
		MeXmlElement* pSubElem = pRoot->FirstChildElement("FlyEffect");
		for (;pSubElem != NULL;pSubElem = pSubElem->NextSiblingElement())
		{
			SFlyConfig flyConfig;
#ifdef _3DMOVE
			pSubElem->QueryIntAttribute("FontType",&flyConfig.nFontType);
			pSubElem->QueryFloatAttribute("xBaseOffset",&flyConfig.nXBaseOffset);
			pSubElem->QueryFloatAttribute("yBaseOffset",&flyConfig.nYBaseOffset);
			pSubElem->QueryFloatAttribute("xMaxOffset",&flyConfig.nXMaxMoveDis);
			pSubElem->QueryFloatAttribute("yMaxOffset",&flyConfig.nYMaxMoveDis);
			pSubElem->QueryFloatAttribute("xStep",&flyConfig.nXStep);
			pSubElem->QueryFloatAttribute("yStep",&flyConfig.nYStep);
#else
			pSubElem->QueryIntAttribute("FontType",&flyConfig.nFontType);
			pSubElem->QueryIntAttribute("xBaseOffset",&flyConfig.nXBaseOffset);
			pSubElem->QueryIntAttribute("yBaseOffset",&flyConfig.nYBaseOffset);
			pSubElem->QueryIntAttribute("xMaxOffset",&flyConfig.nXMaxMoveDis);
			pSubElem->QueryIntAttribute("yMaxOffset",&flyConfig.nYMaxMoveDis);
#endif     
			pSubElem->QueryFloatAttribute("MoveTime",&flyConfig.fMoveTime);
			pSubElem->QueryIntAttribute("LifeTime",&flyConfig.nLifeTime);
			pSubElem->QueryFloatAttribute("InitAlpha",&flyConfig.fInitAlpha);
			pSubElem->QueryFloatAttribute("OverAlpha",&flyConfig.fOverAlpha);


			pSubElem->QueryFloatAttribute("NormalScale",&flyConfig.fNormalScale);
			pSubElem->QueryFloatAttribute("MaxScale",&flyConfig.fMaxScale);

			pSubElem->QueryIntAttribute("Acce",&flyConfig.nAccel);

			const char* var = pSubElem->Attribute("EffectPicPath");
			if(var)
				flyConfig.strPicPath = _tstring::toNarrowString(_tstring::UTF8towcs(var).c_str());

			m_FlyEffectConfig[flyConfig.nFontType] = flyConfig;
		}
	}
	return true;
}

int CFlyTextEffect::GetTextureId(std::string &strPic)
{
	if(strPic.empty())
		return 0;

	ITextureManager* pMgr = GetEngine()->GetTextureManager();
	if(!pMgr)
		return 0;

	int nTexId = 0;	
	char strFullName[MAX_PATH] = {0};
	sprintf(strFullName, "%s\\%s", GetRootPath(), strPic.c_str());
	nTexId = pMgr->RegisterTexture(strFullName,TRUE,FALSE);

	return nTexId;
}

void  CFlyTextEffect::CalMovePos(SFlyConfig &config,int nPosX,int nPosY,DWORD dwTime)
{

}


float CFlyTextEffect::GetAlpha(SFlyConfig &flyConfig,int nMoveX,int nMoveY)
{
	float fAlpha = 1.0f;
	float fDis = sqrt((float)(nMoveX * nMoveX + nMoveY * nMoveY));
	float fLen = sqrt((float)(flyConfig.nXMaxMoveDis * flyConfig.nXMaxMoveDis + flyConfig.nYMaxMoveDis * flyConfig.nYMaxMoveDis));

	float ff = 0;
	if(fLen == 0)
		ff = 1;
	else
		ff = fDis/fLen;

	ff = min(ff,1.0f);
	ff = max(0.0f,ff);

	//Alpha值设定
	fAlpha = flyConfig.fInitAlpha + ff * (flyConfig.fOverAlpha - flyConfig.fInitAlpha);
	if(flyConfig.fInitAlpha <= flyConfig.fOverAlpha)
	{
		if(fAlpha > flyConfig.fOverAlpha)
			fAlpha = flyConfig.fOverAlpha;
	}
	else
	{
		if(fAlpha < flyConfig.fOverAlpha)
			fAlpha = flyConfig.fOverAlpha;
	}

	return fAlpha;
}




CPrintTextEffect::CPrintTextEffect()
{
	guardfunc;
	m_PrintNodeList.clear();
	bool OK = InitConfig();
	assert(OK && "PrintTextEffect OK");

	for (int i = 0 ; i < PRINTMAX ; i++)
	{
		m_SortInfo[i].clear();
	}
	unguard;
}

bool CPrintTextEffect::InitConfig()
{
	MeXmlDocument doc;
	char szWord[256] = {0};
	MeSprintf_s(szWord,sizeof(szWord),"%s\\Data\\ClientConfig\\GameSetting.config",GetRootPath());
	if( !doc.LoadFile(szWord) )
		return false;

	m_PrintConfigVec.clear();

	MeXmlElement* pRoot = doc.FirstChildElement("Project")->FirstChildElement("PrintTextEffect");
	if(pRoot)
	{
		MeXmlElement* pSubElem = pRoot->FirstChildElement("PrintEffect");
		for (;pSubElem != NULL;pSubElem = pSubElem->NextSiblingElement())
		{
			PrintTextconfig flyConfig;
			pSubElem->QueryIntAttribute("PrintTextType",&flyConfig.Type);	
			int ScreenX, ScreenY ,TextureW , TextureH ,XOffset,YOffset ,LifeTime, NumW, NumH, Offset = 0;
			pSubElem->QueryIntAttribute("ScreenX",&ScreenX);
			pSubElem->QueryIntAttribute("ScreenY",&ScreenY);
			pSubElem->QueryIntAttribute("TextureW",&TextureW);
			pSubElem->QueryIntAttribute("TextureH",&TextureH);
			pSubElem->QueryIntAttribute("NumTextOffsetX",&XOffset);
			pSubElem->QueryIntAttribute("NumTextOffsetY",&YOffset);
			pSubElem->QueryIntAttribute("LifeTime",&LifeTime);
			pSubElem->QueryIntAttribute("NumW",&NumW);
			pSubElem->QueryIntAttribute("NumH",&NumH);
			pSubElem->QueryIntAttribute("NumOffsetCol",&Offset);

			flyConfig.BackTextScreenPos.left = ScreenX;
			flyConfig.BackTextScreenPos.top = ScreenY;
			flyConfig.BackTextScreenPos.right = flyConfig.BackTextScreenPos.left + TextureW;
			flyConfig.BackTextScreenPos.bottom = flyConfig.BackTextScreenPos.top + TextureH;
			flyConfig.NumOffsetByBackTextScreenPos.x = XOffset;
			flyConfig.NumOffsetByBackTextScreenPos.y = YOffset;
			flyConfig.LifeTime = LifeTime;

			flyConfig.NumCharW = NumW;             
			flyConfig.NumCharH = NumH;             
			flyConfig.NumCharOffset = Offset;    

			pSubElem->QueryIntAttribute("NumColorRow",&flyConfig.ColorRow);
			pSubElem->QueryIntAttribute("AlphaChangeTime",&flyConfig.AlphaChangeTime);

			pSubElem->QueryIntAttribute("PicRowCnt",&flyConfig.PicRowCnt);
			pSubElem->QueryIntAttribute("PicColCnt",&flyConfig.PicColCnt);
			pSubElem->QueryIntAttribute("LoopType",&flyConfig.LoopType);
			pSubElem->QueryIntAttribute("RenderNumFrameCnt" ,&flyConfig.RnerNumFrameCnt);
			pSubElem->QueryIntAttribute("RenderSpeed",&flyConfig.RenderSpeed);

			const char* var = pSubElem->Attribute("PrintTextPicPath");
			if(var)
				flyConfig.strBackPicPath = _tstring::toNarrowString(_tstring::UTF8towcs(var).c_str());

			const char* var1 = pSubElem->Attribute("PrintNumPicPath");
			if(var)
				flyConfig.strNumPicPath = _tstring::toNarrowString(_tstring::UTF8towcs(var1).c_str());

			m_PrintConfigVec.insert(std::make_pair(flyConfig.Type,flyConfig));
		}
	}
	return true;

}

//创建。
bool CPrintTextEffect::Create(int Num , PRINTTEXTYPE _type)
{
	/*
	以下配置根据配置文件来配置
	*/
	PRINTTEXT_INFO _temp;
	_temp.Reset();

	_temp.BornTime = timeGetTime();
	_temp.Dead = false;
	_temp.LifeTime = 2000;
	_temp.PrintType = _type;
	_temp.Num = Num;
	_temp.dwColor = 0xffffffff;

	std::map<int ,PrintTextconfig>::iterator it = m_PrintConfigVec.find(_type);
	if(it == m_PrintConfigVec.end()) return false;

	_temp.LifeTime = it->second.LifeTime;
	memcpy(&_temp._DesRect,&(it->second.BackTextScreenPos),sizeof(RECT));
	memcpy(&_temp._NumOffsetXY,&(it->second.NumOffsetByBackTextScreenPos),sizeof(POINT));

	//=====================================================
	_temp.LoopTYpe = (PRINTTEXTLOOPMODE)it->second.LoopType;
	_temp.LastFrameTime = timeGetTime();
	_temp.LastFrameRow = 0;
	_temp.LastFrameCol = 0;
	_temp.bStopLoop = false;
	_temp.bRenderNum = false;

	m_PrintNodeList.push_back( _temp );
	return false;
}

//分类
void CPrintTextEffect::Sort()
{
	if(!m_PrintNodeList.size())
		return;

	TEXTNODELIST::iterator it = m_PrintNodeList.begin();
	for (; it != m_PrintNodeList.end(); it++)
	{
		switch(it->PrintType)
		{
		case PRINTTEXTYPE::KILLTARGET:
			m_SortInfo[KILLTARGET].push_back(*it);
			break;
		default:
			break;
		}
	}
	m_PrintNodeList.clear();

}

//更新当前节点的 透明度
void CPrintTextEffect::UpdateAlpha()
{
	for(int i = 0 ; i < PRINTTEXTYPE::PRINTMAX ; i++)
	{
		if(m_CurPrintInfo[i].Dead)  //死亡不更新
			continue;

		std::map<int ,PrintTextconfig>::iterator it = m_PrintConfigVec.find(i);
		if(it == m_PrintConfigVec.end()) return ;

      if(timeGetTime() - m_CurPrintInfo[i].BornTime  > (m_CurPrintInfo[i].LifeTime - it->second.AlphaChangeTime) )
	  {
		 float _s = 1.0f - ((float)(timeGetTime() - m_CurPrintInfo[i].BornTime) / (float)m_CurPrintInfo[i].LifeTime); 
		 int Alpha = _s*255.f;
		 DWORD color =  Alpha<<24|0x00ffffff;
		 m_CurPrintInfo[i].dwColor = color;

	  }
	}
}


//更新当前正在绘制的节点。
void CPrintTextEffect::Update()
{
    //分类
	Sort();

	//为当前绘制赋值
	for (int i = 0 ; i < PRINTMAX ; i++)
	{
		if(!m_SortInfo[i].size()) continue;
		{
			int LastFrameRow = m_CurPrintInfo[i].LastFrameRow;
			int LastFrameCol = m_CurPrintInfo[i].LastFrameCol;

			//如果是循环的 则保留上一个节点的一些相关属性
			switch (m_CurPrintInfo[i].LoopTYpe)
			{
			case STATICPRINT:
				memcpy(&m_CurPrintInfo[i],&m_SortInfo[i][m_SortInfo[i].size() - 1],sizeof(PRINTTEXT_INFO)); //只取头，头是最后一个被压进去的。
				break;

			case ONCEPLAYPRINT:
			case LOOPPLAYPRINT:
				{
					memcpy(&m_CurPrintInfo[i],&m_SortInfo[i][m_SortInfo[i].size() - 1],sizeof(PRINTTEXT_INFO));
						m_CurPrintInfo[i].LastFrameRow = LastFrameRow;
						m_CurPrintInfo[i].LastFrameCol = LastFrameCol;
				}
				break;

			default:
				memcpy(&m_CurPrintInfo[i],&m_SortInfo[i][m_SortInfo[i].size() - 1],sizeof(PRINTTEXT_INFO)); //只取头，头是最后一个被压进去的。
				break;

			}
		

			
		}
		
	}

	for (int i = 0 ; i < PRINTMAX ; i++)
	{
		m_SortInfo[i].clear();
	}

	//节点死亡判断
	for(int i = 0 ; i < PRINTTEXTYPE::PRINTMAX ; i++)
	{
		if (timeGetTime() - m_CurPrintInfo[i].BornTime >= m_CurPrintInfo[i].LifeTime)
		{
			m_CurPrintInfo[i].Reset(); //当前类型节点重置
		}
	}	
	//更新 透明度
	UpdateAlpha();
}


//获得图片id
int  CPrintTextEffect:: GetTextureId(std::string &strPic)
{
	if(!g_pFlyTextEffect)
		return -1;

	return g_pFlyTextEffect->GetTextureId(strPic);
}


//绘制数字
void CPrintTextEffect::RenderNum(PRINTTEXTYPE _type)
{
	static Simple2DVertex v[1024];

	int nNumDrawChar = 0;
	int CharLen = 0;
	int nNumber = m_CurPrintInfo[_type].Num;
	char s[32] = {0};
	sprintf( s, "%ld", nNumber );
	CharLen = strlen( s ); //char 的个数。

	//首个字母的位置
	int NumPosX = m_CurPrintInfo[_type]._DesRect.left + m_CurPrintInfo[_type]._NumOffsetXY.x;
	int NumPosY = m_CurPrintInfo[_type]._DesRect.top + m_CurPrintInfo[_type]._NumOffsetXY.y;

	std::map<int ,PrintTextconfig>::iterator it = m_PrintConfigVec.find(_type);
	if(it == m_PrintConfigVec.end()) return ;

	//配置需求每个字符的宽度 和 高度
	int NumW = it->second.NumCharW;
	int NumH = it->second.NumCharH;
	int ColOffset = it->second.NumCharOffset;	 
	//字的颜色
	int  NumColorType = it->second.ColorRow;

	int _RenderNumPosX = (CharLen - 1) * ( ColOffset/* NumW*/ );

	for(int i = 0 ; i <  CharLen ; i++)
	{

		DrawNumberCharBitmap( 
			NumPosX - _RenderNumPosX + nNumDrawChar * ColOffset,
			NumPosY,
			NumW,
			NumH,
			NumColorType,						//1,		sbw_modify
			m_CurPrintInfo[_type].dwColor, 
			s[i] - '0', 
			&v[nNumDrawChar*4] );
		nNumDrawChar++;
	}

	if(  nNumDrawChar > 0 )
	{

		int TexId =  GetTextureId(it->second.strNumPicPath);

		GetEngine()->GetRenderer()->DirectPushSurface(
			TexId,
			-1, 
			OBJECT2D_SHADER, 
			Simple2DVertex_FVF,
			sizeof( Simple2DVertex ), 
			(BYTE*)v,
			4*nNumDrawChar,
			(BYTE*)Emitter::GetCCWIndexBuffer(),
			2*nNumDrawChar, 
			eAlphaBlend|eLinearFilter );
	}

}


#define PICSIZE 8.0f
//绘制 背景 和 数字
void CPrintTextEffect::Render()
{
	if(!g_pFlyTextEffect) return;

	for(int i = 0 ; i < PRINTTEXTYPE::PRINTMAX ; i++)
	{
		if(m_CurPrintInfo[i].Dead) 
			continue;

		//绘制底层
		std::map<int ,PrintTextconfig>::iterator it = m_PrintConfigVec.find(i);
		if(it == m_PrintConfigVec.end()) return ;
        
		//静态的
		switch(m_CurPrintInfo[i].LoopTYpe)
		{
		case STATICPRINT:
			{
				g_pFlyTextEffect->Draw(m_CurPrintInfo[i]._DesRect,GetTextureId(it->second.strBackPicPath),m_CurPrintInfo[i].dwColor);
				RenderNum((PRINTTEXTYPE)i);
			}
			break;
		case ONCEPLAYPRINT:
			{
                 RenderPrintLoop((PRINTTEXTYPE)i,it->second.strBackPicPath,true);
				 if( m_CurPrintInfo[i].bRenderNum) //一遍播放完了 才进行数字的绘制
				 RenderNum((PRINTTEXTYPE)i);
			}
			break;
       
		case LOOPPLAYPRINT: //循环播放 2
			{
			
				RenderPrintLoop((PRINTTEXTYPE)i,it->second.strBackPicPath);
				RenderNum((PRINTTEXTYPE)i);
             
			}
			break;

		 default:  //默认的只有静态
			{
			g_pFlyTextEffect->Draw(m_CurPrintInfo[i]._DesRect,GetTextureId(it->second.strBackPicPath),m_CurPrintInfo[i].dwColor);
			RenderNum((PRINTTEXTYPE)i);
			}
           break;
		}
		


		
	}

}

/*

*/
void CPrintTextEffect::RenderPrintLoop(PRINTTEXTYPE type,std::string PicPtch, bool Once)
{
	std::map<int ,PrintTextconfig>::iterator it = m_PrintConfigVec.find(type);
	if(it == m_PrintConfigVec.end()) return ;

	 

	 if(Once)
	 { 
 
		 if((m_CurPrintInfo[type].LastFrameRow ) *( it->second.PicColCnt ) + m_CurPrintInfo[type].LastFrameCol  >= it->second.RnerNumFrameCnt)
		 {
            m_CurPrintInfo[type].bRenderNum = true;
		 }
		

		 if (m_CurPrintInfo[type].LastFrameCol >= (it->second.PicColCnt - 1) &&
			 m_CurPrintInfo[type].LastFrameRow >= (it->second.PicRowCnt - 1)) 
		 {
			 m_CurPrintInfo[type].LastFrameCol = it->second.PicColCnt - 1;
			  m_CurPrintInfo[type].LastFrameRow = (it->second.PicRowCnt - 1);
			 m_CurPrintInfo[type].bStopLoop = true;	
		 }
	 }

 Draw(m_CurPrintInfo[type]._DesRect,GetTextureId(PicPtch),m_CurPrintInfo[type].dwColor,m_CurPrintInfo[type].LastFrameRow,m_CurPrintInfo[type].LastFrameCol,it->second.PicRowCnt,it->second.PicColCnt);
	 
	if(!m_CurPrintInfo[type].bStopLoop)
	if(timeGetTime() - m_CurPrintInfo[type].LastFrameTime > it->second.RenderSpeed)
	{
		m_CurPrintInfo[type].LastFrameTime = timeGetTime();

		if (m_CurPrintInfo[type].LastFrameCol < it->second.PicColCnt)
		{
			m_CurPrintInfo[type].LastFrameCol++;
		}
		else
		{
			m_CurPrintInfo[type].LastFrameCol = 0;

			if(m_CurPrintInfo[type].LastFrameRow < it->second.PicRowCnt)
			{
				m_CurPrintInfo[type].LastFrameRow++;
			}else
			{
				m_CurPrintInfo[type].LastFrameRow = 0;
			}

		}
	}






	
}



/*
这里暂时定为 一张图有64帧，8行8列 512的图 顺序从左到右 ，从上到下
*/
void  CPrintTextEffect::Draw(RECT &rect,short textureID,DWORD dwColor ,int Row, int Col ,int TotalRow, int TotalCol)
{

	float z = 0.2f;
	Simple2DVertex vertex[4];
	static short index[] = { 0, 1, 2, 2, 1, 3 };

	vertex[0].p = D3DXVECTOR4( rect.left, rect.bottom, z, 1 );
	vertex[0].color = dwColor;
	vertex[0].u = (float)Col / TotalCol;  // 0	
	vertex[0].v = (float)(Row + 1) / TotalRow;  // 1

	vertex[1].p = D3DXVECTOR4( rect.left, rect.top, z, 1 );
	vertex[1].color = dwColor;
	vertex[1].u = (float)Col / TotalCol; //0
	vertex[1].v = (float)Row / TotalRow; //0

	vertex[2].p = D3DXVECTOR4( rect.right, rect.bottom, z, 1 );
	vertex[2].color = dwColor;
	vertex[2].u = (float)(Col + 1) / TotalCol;    //1
	vertex[2].v = (float)(Row + 1) / TotalRow;    //1

	vertex[3].p = D3DXVECTOR4( rect.right, rect.top, z, 1 );
	vertex[3].color = dwColor;
	vertex[3].u = (float)(Col + 1) / TotalCol; //1
	vertex[3].v = (float)(Row) / TotalRow;     //0

	GetEngine()->GetRenderer()->DirectPushSurface(
		textureID,
		-1, 
		OBJECT2D_SHADER, 
		Simple2DVertex_FVF,
		sizeof( Simple2DVertex ), 
		(BYTE*)vertex,
		4,
		(BYTE*)index,
		2, eAlphaBlend|eLinearFilter );
}