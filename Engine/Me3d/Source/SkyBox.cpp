#include "Me3d/Me3d.h"
#include "Me3d/SkyBox.h"
#include "Me3d/Engine/EngineInstance.h"
#include "FuncPerformanceLog.h"
#include "Me3d/MathLib.h"
#include <math.h>
#include "TimeClock.h"
#include "3dsmax/gfloat.h"

#define SAFE_RELEASE(p)      { if(p) { (p)->Release(); (p)=NULL; } }
#ifndef V
#define V(x) x
#endif

const int DX[8] = { 0, 1, 1, 1, 0,-1,-1,-1};
const int DY[8] = {-1,-1, 0, 1, 1, 1, 0,-1};

#define D3DFVF_SKYBOXVERTEX ( D3DFVF_XYZ  | D3DFVF_DIFFUSE | D3DFVF_TEX1 )
#define D3DFVF_CLOUDSVERTEX ( D3DFVF_XYZ  | D3DFVF_DIFFUSE )

#define FILL_SKYBOXVERTEX( ver, ptx, pty, ptz, atu1, atv1 )  \
{   ver.pos.x = ptx;  ver.pos.y = pty;  ver.pos.z = ptz;  \
    ver.u = atu1;  ver.v = atv1;  \
}
#define hh 23.5//����ĻƳཻ����23.5��
#define S_ERRS D3DXVECTOR3(1,1,1)//revolution of the earth ������̫����ת���ٶ� PI2/T ���ڼ��ڱ仯
#define ERRS D3DXVECTOR3(1,1,1)//earth's rotation rad/s ������ת���ٶ�
#define E_MRRS D3DXVECTOR3(1,1,1)//revolution of the moon �����Ƶ���ת���ٶ�

struct SKYBOXVERTEX
{
	D3DXVECTOR3		pos;
	DWORD			color;
	float			u,v;
};

CSkyBox* GetSkyBox()
{
	guardfunc;
	static CSkyBox g_SkyBox;
	return &g_SkyBox;
	unguard;
};

CSkyBox::CSkyBox() : sizeH(2000.0f, 2000.0f, 2000.0f)
{
	guardfunc;

	m_pVB = NULL;
	m_pAmbientVB = NULL;
	m_pSunVB = NULL;
	m_pSunIB = NULL;
	m_pSunshineVB = NULL;

	m_pCloudsVB = NULL;
	m_pCloudsIB = NULL;

	m_nTxSky = -1;
	m_nTxSun = -1;
	m_nTxMoon = -1;

	// ��ɫ
	m_dwSunColor		= 0xFFFFFFFF;
	m_dwMoonColor		= 0xFFFFFFFF;
	m_dwCloudColor		= 0xFFFFFFFF;
	m_dwTopColor		= 0xFFFFA2C0;
	m_dwBaseColor		= 0xFFBBBBBB;
	m_dwAmbientColor	= 0xFF4488DD;

	m_bDisable			= false;

	m_bCanRender		= false;
	unguard;
}

CSkyBox::~CSkyBox()
{
	guardfunc;
	if( m_pSunVB )
	{
		m_pSunVB->Release();
		m_pSunVB = NULL;
	}

	if( m_pSunIB )
	{
		m_pSunIB->Release();
		m_pSunIB = NULL;
	}

	if( m_pSunshineVB )
	{
		m_pSunshineVB->Release();
		m_pSunshineVB = NULL;
	}

	if( m_pSunshineIB )
	{
		m_pSunshineIB->Release();
		m_pSunshineIB = NULL;
	}

	if( m_pVB )
	{
		m_pVB->Release();
		m_pVB = NULL;
	}

	if( m_pIB )
	{
		m_pIB->Release();
		m_pIB = NULL;
	}

	if( m_pFogVB )
	{
		m_pFogVB->Release();
		m_pFogVB = NULL;
	}

	if( m_pFogIB )
	{
		m_pFogIB->Release();
		m_pFogIB = NULL;
	}

	if( m_pAmbientVB )
	{
		m_pAmbientVB->Release();
		m_pAmbientVB = NULL;
	}

	if( m_pAmbientIB )
	{
		m_pAmbientIB->Release();
		m_pAmbientIB = NULL;
	}

	if( m_pCloudsVB )
	{
		m_pCloudsVB->Release();
		m_pCloudsVB = NULL;
	}

	if( m_pCloudsIB )
	{
		m_pCloudsIB->Release();
		m_pCloudsIB = NULL;
	}
	unguard;
}

void CSkyBox::deleteDeviceObjects()
{
	guardfunc;
	SAFE_RELEASE(m_pVB);
	unguard;
}


bool CSkyBox::restoreDeviceObjects()
{
	guardfunc;
	return true;
	unguard;
}

void CSkyBox::Create(int nResolution, float fVertSweep, float fRadius, 
				float fHeightScale, const D3DXVECTOR3 &vOrigin)
{
	guardfunc;

	IRenderer* RI = GetEngine()->GetRenderer();
	LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)RI->GetRealDevice();

	HRESULT hr = 0;

	char filename[MAX_PATH];
	sprintf(filename, "%s/data/texture/star.tga", GetRootPath());
	m_nTxSky = GetEngine()->GetTextureManager()->RegisterTexture( filename,NULL,NULL);
	sprintf(filename, "%s/data/texture/sun.tga", GetRootPath());
	m_nTxSun = GetEngine()->GetTextureManager()->RegisterTexture( filename,NULL,NULL);
	sprintf(filename, "%s/DATA/data/texture/moon.tga", GetRootPath());
	m_nTxMoon = GetEngine()->GetTextureManager()->RegisterTexture( filename,NULL,NULL);
	//
	for ( int i = 0; i < NUM_STDFLAREIMGS; i++ )
	{
		char fname[FILENAME_MAX]; 
		sprintf(fname,"%s/data/texture/Lensflare/flare%d.tga", GetRootPath(), i);
		m_nFlareTexID[i] = GetEngine()->GetTextureManager()->RegisterTexture( fname,NULL,NULL);
	}
	
	m_LFVerts[0].u = 0.0f;
	m_LFVerts[0].v = 0.0f;
	m_LFVerts[1].u = 0.0f;
	m_LFVerts[1].v = 1.0f;
	m_LFVerts[2].u = 1.0f;
	m_LFVerts[2].v = 0.0f;
	m_LFVerts[3].u = 1.0f;
	m_LFVerts[3].v = 1.0f;

	SKYBOXVERTEX*	pVertices = NULL;


	m_nResolution = nResolution;
	m_fVertSweep = fVertSweep;
	m_fRadius = fRadius;
	m_fHeightScale = fHeightScale;
	m_vOrigin = vOrigin;


	// ���㶥�������
	m_nNumOfVertices =(1 + 4 * nResolution )* (nResolution+1);

	// ����Ԫ��
	m_nNumOfTriangles = nResolution * 4 *(nResolution * 2 - 1); //�����ϵ�����������*��������

	// �ж�����
	int nRowLength = nResolution * 4+1;

	//SAFE_RELEASE(m_pVB)
	//if(m_pVB!=NULL) { m_pVB->Release(); m_pVB=NULL; }

	// =============�������ܻ��Ƶ�����=============
	V(pDev->CreateVertexBuffer(m_nNumOfVertices * sizeof(SKYBOXVERTEX), D3DUSAGE_WRITEONLY,
		D3DFVF_SKYBOXVERTEX, D3DPOOL_MANAGED, &m_pVB,0));

    if( !m_pVB )
        return;

	m_pVB->Lock(0, 0, (void**)&pVertices, D3DLOCK_NOSYSLOCK);


	// ���ݴ�ֱ��չ���ڰ뾶 
	float fRadAngle = (90 - fVertSweep) / 180 * D3DX_PI;
	fRadius /= cos (fRadAngle);

	// ���� y���� ������adjustment
	float fYAdj = fRadius * sin (fRadAngle);

	// ������߸߶�
	m_fMaxHeight = (fRadius - fYAdj) * fHeightScale;
	//
	// ��պ��ӵ���ߵ� ����߶�
	for (int j = 0; j < nRowLength; j++)
	{
		pVertices[j].pos = D3DXVECTOR3(0, 0, m_fMaxHeight) + vOrigin;
		pVertices[j].color = 0xFFFFFFFF;
		//pVertices[j].u = (j-0.5)/(nResolution * 4);pVertices[j].v = 0.01;
		pVertices[j].u = 0.5;
		pVertices[j].v = 0.5;
	}

	// �ӷֱ���, ������պ�һƬ���нǶȵ���
	float fHorzSweep =D3DX_PI*0.5 / nResolution ;

	// ���ڴ�ֱ�ֱ���
	fVertSweep /= nResolution;

	// �Ӷ�����ʼ, ��ס�� with nResolution��������
	int nVertex = nResolution * 4+1;
	for (int i = 0; i < nResolution; i++)
	{
		// ����Χ����ת�γɻ��Ķ���
		D3DXVECTOR3 vPoint (sin(fVertSweep* (i + 1)/ 180 * D3DX_PI)*fRadius, 0, cos(fVertSweep* (i + 1)/ 180 * D3DX_PI)*fRadius);
		vPoint .z = (vPoint .z - fYAdj) * fHeightScale;

		
		DWORD dwColor = 0x00FFFFF;
		dwColor|=((nResolution-i-1)*255/nResolution)<<24;

		float fUVRadius = float(i+1)/(float)nResolution;
		// ���黷������
		for (int j = 0; j < nRowLength; j++)
		{
			pVertices[nVertex].pos = D3DXVECTOR3(cos(fHorzSweep * j)*vPoint.x, -sin(fHorzSweep * j)*vPoint.x, vPoint.z);
			pVertices[nVertex].pos += vOrigin;
			pVertices[nVertex].color = dwColor;
			//pVertices[nVertex].u = float(j)/(nResolution * 4.0f);pVertices[nVertex].v =float(i+1)/float(nResolution);

			pVertices[nVertex].u = cos(fHorzSweep * j)*fUVRadius*2+0.5f;
			pVertices[nVertex].v = -sin(fHorzSweep * j)*fUVRadius*2+0.5f;
			nVertex++;
		}
	}

	nVertex = nResolution * 4+1;
	for (int i = 0; i < nResolution; i++)
	{;
		//DWORD dwColor =D3DCOLOR_ARGB( (byte)(Color.a*255) , (byte)(Color.r*255) , (byte)(Color.g*255) , (byte)(Color.b*255) );
		//// ���黷������
		for (int j = 0; j < nRowLength; j++)
		{
			//pVertices[nVertex].color = pVertices[nVertex].color0xFFFFFFFF;
			nVertex++;
		}
	}
    if( m_pVB )
	    m_pVB->Unlock();

	// ��������
	V(pDev->CreateIndexBuffer(
		m_nNumOfTriangles*3* sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pIB,
		0));

	WORD* indices = 0;
    if( m_pIB )
	    m_pIB->Lock(0, 0, (void**)&indices, 0);


	for (int i = 0; i < nResolution; i++)
	{	
		for (int j = 0; j < nResolution * 4; j++)
		{
			if (i!=0)
			{
				*indices=(i+1)*nRowLength+j;
				indices++;
				*indices=i*nRowLength+j;
				indices++;
				*indices=i*nRowLength+j+1;
				indices++;
			}
			*indices=(i+1)*nRowLength+j;
			indices++;
			*indices=i*nRowLength+j+1;
			indices++;
			*indices=(i+1)*nRowLength+j+1;
			indices++;
		}
	}
    if( m_pIB )
	    m_pIB->Unlock();

	// ============================================

	int nAmbientRowLength = nResolution * 4;
	m_nNumOfAV = nAmbientRowLength * 3;
	m_nNumOfAT = nAmbientRowLength*4 + 2;
	// =============������ӷ������=============(ʹ��������Ⱦ)
	V(pDev->CreateVertexBuffer(m_nNumOfAV * sizeof(CloudsVB), D3DUSAGE_WRITEONLY,
		D3DFVF_CLOUDSVERTEX, D3DPOOL_MANAGED, &m_pFogVB,0));

	CloudsVB*	pAV = NULL;
    if( m_pFogVB )
	    m_pFogVB->Lock(0, 0, (void**)&pAV, D3DLOCK_NOSYSLOCK);

	for (int j = 0; j < nAmbientRowLength; j++)
	{//��Ȳ����|д�� ���� λ�ò���Ҫ
		pAV->x = cos(D3DX_PI*0.5 / nResolution * j)*m_fRadius;
		pAV->y = -sin(D3DX_PI*0.5 / nResolution * j)*m_fRadius;
		pAV->z = FOG_HEIGHT;
		pAV->dwColor = 0xFFFFFFFF;
		pAV++;
	}

	for (int j = 0; j < nAmbientRowLength; j++)
	{
		pAV->x = cos(D3DX_PI*0.5 / nResolution * j)*m_fRadius;
		pAV->y = -sin(D3DX_PI*0.5 / nResolution * j)*m_fRadius;
		pAV->z = 0;
		pAV->dwColor = 0xFFFFFFFF;
		pAV++;
	}

	for (int j = 0; j < nAmbientRowLength; j++)
	{
		pAV->x = cos(D3DX_PI*0.5 / nResolution * j)*0;
		pAV->y = -sin(D3DX_PI*0.5 / nResolution * j)*0;
		pAV->z = -2000;
		pAV->dwColor = 0xFFFFFFFF;
		pAV++;
	}
    if( m_pFogVB )
	    m_pFogVB->Unlock();

	// ��������
	V(pDev->CreateIndexBuffer(
		(nAmbientRowLength*4 + 4) * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pFogIB,
		0));

	indices = 0;
    if( m_pFogIB )
	    m_pFogIB->Lock(0, 0, (void**)&indices, 0);
	for (int i = 0; i < nAmbientRowLength; i++)
	{	
		*indices=i;
		indices++;
		*indices=nAmbientRowLength+i;
		indices++;
	}
	*indices=0;
	indices++;
	*indices=nAmbientRowLength;
	indices++;

	for (int i = 0; i < nAmbientRowLength; i++)
	{	
		*indices=nAmbientRowLength+i;
		indices++;
		*indices=nAmbientRowLength*2+i;
		indices++;
	}
	*indices=nAmbientRowLength;
	indices++;
	*indices=nAmbientRowLength*2;
	indices++;

    if( m_pFogIB )
	    m_pFogIB->Unlock();
	// ============================================
	// =============�������ܻ��Ƶ�����=============(ʹ��������Ⱦ)
	V(pDev->CreateVertexBuffer(m_nNumOfAV * sizeof(CloudsVB), D3DUSAGE_WRITEONLY,
		D3DFVF_CLOUDSVERTEX, D3DPOOL_MANAGED, &m_pAmbientVB,0));

	static float fP = 150;
	pAV = NULL;
    if( m_pAmbientVB )
	    m_pAmbientVB->Lock(0, 0, (void**)&pAV, D3DLOCK_NOSYSLOCK);

	for (int j = 0; j < nAmbientRowLength; j++)
	{//��Ȳ����|д�� ���� λ�ò���Ҫ
		pAV->x = cos(D3DX_PI*0.5 / nResolution * j)*100;
		pAV->y = -sin(D3DX_PI*0.5 / nResolution * j)*100;
		pAV->z = FOG_HEIGHT+fP;
		pAV->dwColor = 0x0;
		pAV++;
	}

	for (int j = 0; j < nAmbientRowLength; j++)
	{
		pAV->x = cos(D3DX_PI*0.5 / nResolution * j)*m_fRadius;
		pAV->y = -sin(D3DX_PI*0.5 / nResolution * j)*m_fRadius;
		pAV->z = FOG_HEIGHT;
		pAV->dwColor = 0xFFFFFFFF;
		pAV++;
	}

	for (int j = 0; j < nAmbientRowLength; j++)
	{
		pAV->x = cos(D3DX_PI*0.5 / nResolution * j)*m_fRadius;
		pAV->y = -sin(D3DX_PI*0.5 / nResolution * j)*m_fRadius;
		pAV->z = FOG_HEIGHT-60;
		pAV->dwColor = 0x0;
		pAV++;
	}
    if( m_pAmbientVB )
	    m_pAmbientVB->Unlock();

	// ��������
	V(pDev->CreateIndexBuffer(
		(nAmbientRowLength*4 + 4) * sizeof(WORD),
		D3DUSAGE_WRITEONLY,
		D3DFMT_INDEX16,
		D3DPOOL_MANAGED,
		&m_pAmbientIB,
		0));

	indices = 0;
    if( m_pAmbientIB )
	    m_pAmbientIB->Lock(0, 0, (void**)&indices, 0);
	for (int i = 0; i < nAmbientRowLength; i++)
	{	
		*indices=i;
		indices++;
		*indices=nAmbientRowLength+i;
		indices++;
	}
	*indices=0;
	indices++;
	*indices=nAmbientRowLength;
	indices++;

	for (int i = 0; i < nAmbientRowLength; i++)
	{	
		*indices=nAmbientRowLength+i;
		indices++;
		*indices=nAmbientRowLength*2+i;
		indices++;
	}
	*indices=nAmbientRowLength;
	indices++;
	*indices=nAmbientRowLength*2;
	indices++;

    if( m_pAmbientIB )
	    m_pAmbientIB->Unlock();
	// ============================================

	//////////////////////////////////////////////////////////////////////////
	// ����̫��
	V(pDev->CreateVertexBuffer(SUN_VB_SIZE * sizeof(SKYBOXVERTEX), D3DUSAGE_WRITEONLY, D3DFVF_SKYBOXVERTEX, D3DPOOL_MANAGED, &m_pSunVB,0));

	SKYBOXVERTEX*	pSV = NULL;
    if( m_pSunVB )
	    m_pSunVB->Lock(0, 0, (void**)&pSV, D3DLOCK_NOSYSLOCK);


	pSV[0].pos = D3DXVECTOR3( 0, 1000, 0);
	pSV[0].color = 0xFFFFFFFF;
	pSV[0].u = 0.5;
	pSV[0].v = 0.5;

	for (int j = 1; j < SUN_VB_SIZE ; j++)
	{
		pSV[j].pos = D3DXVECTOR3(cos(D3DX_PI*2 / SUN_SEGMENT * j)*150, 1000, -sin(D3DX_PI*2 / SUN_SEGMENT * j)*150);
		pSV[j].color = 0xFFFFFFFF;
		pSV[j].u = 0.5 + cos(D3DX_PI*2 / SUN_SEGMENT * j)*0.5;
		pSV[j].v = 0.5 - sin(D3DX_PI*2 / SUN_SEGMENT * j)*0.5;
	}
    if( m_pSunVB )
	    m_pSunVB->Unlock();


	V( pDev->CreateIndexBuffer( ( SUN_VB_SIZE + 1 ) * sizeof(unsigned short), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pSunIB, 0 ) );

	unsigned short* pSunIndices;
    if( m_pSunIB )
	    m_pSunIB->Lock( 0, 0, (void**)&pSunIndices, 0 );

	for( int i = 0; i < SUN_VB_SIZE; ++i )
	{
		pSunIndices[i] = i;
	}
	pSunIndices[SUN_VB_SIZE] = 1;

    if( m_pSunIB )
	    m_pSunIB->Unlock();


	// Sunshine
	V(pDev->CreateVertexBuffer(SUN_VB_SIZE * sizeof(CloudsVB), D3DUSAGE_WRITEONLY,
		D3DFVF_CLOUDSVERTEX, D3DPOOL_MANAGED, &m_pSunshineVB,0));

	CloudsVB* pSSV = NULL;
    if( m_pSunshineVB )
	    m_pSunshineVB->Lock(0, 0, (void**)&pSSV, D3DLOCK_NOSYSLOCK);

	pSSV[0].x= 0;
	pSSV[0].y= 1000;
	pSSV[0].z= 0;
	pSSV[0].dwColor = 0xFF000000;

	for (int j = 1; j < SUN_VB_SIZE ; j++)
	{
		pSSV[j].x = cos(D3DX_PI*2 / SUN_SEGMENT * j)*300;
		pSSV[j].y = 100;
		pSSV[j].z = -sin(D3DX_PI*2 / SUN_SEGMENT * j)*300;
		pSSV[j].dwColor = 0x000000;
	}
    if( m_pSunshineVB )
	    m_pSunshineVB->Unlock();


	V( pDev->CreateIndexBuffer( ( SUN_VB_SIZE + 1 ) * sizeof(unsigned short), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pSunshineIB, 0 ) );

	unsigned short* pSunshineIndices;
    if( m_pSunshineIB )
	    m_pSunshineIB->Lock( 0, 0, (void**)&pSunshineIndices, 0 );

	for( int i = 0; i < SUN_VB_SIZE; ++i )
	{
		pSunshineIndices[i] = i;
	}
	pSunshineIndices[SUN_VB_SIZE] = 1;

    if( m_pSunshineIB )
    	m_pSunshineIB->Unlock();



	////////////////////////////////////////////////////////////////////////////
	//// ����̫��
	//pDev->CreateVertexBuffer( CLOUDS_VB_SIZE*sizeof( CloudsVB ), D3DUSAGE_WRITEONLY|D3DUSAGE_DYNAMIC, D3DFVF_CLOUDSVERTEX, D3DPOOL_MANAGED, &m_pCloudsVB, 0 ) ;
	//pDev->CreateIndexBuffer( CLOUDS_IB_SIZE*sizeof(unsigned short), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &m_pCloudsIB, 0 ) ;
	////////////////////////////////////////////////////////////////////////////
	

	//InitClouds();

	unguard;
}
void CSkyBox::SetTime(DWORD dwTime)
{
	//if (dwTime<60*60*6-60*20)
	//{
	//	m_bIsDaytime = false;
	//}
	//else if (dwTime<60*60*18+60*20)
	//{
	//	m_bIsDaytime = true;
	//}else
	//{
	//	m_bIsDaytime = false;
	//}
}
void CSkyBox::SetSunPosition(const D3DXVECTOR3 vPosition)
{
	guardfunc;
	HRESULT hr = 0;
	m_vSunPos = vPosition;
	m_vSunPos.x *= 1000;
	m_vSunPos.y *= 1000;
	m_vSunPos.z *= 1000;
	D3DXVec3Normalize(&m_vSunNormal,&m_vSunPos);// ����̫������
	unguard;
}
void CSkyBox::SetMoonPosition(const D3DXVECTOR3 vPosition)
{
	guardfunc;
	HRESULT hr = 0;
	m_vMoonPos = vPosition;
	D3DXVec3Normalize(&m_vMoonNormal,&m_vMoonPos);// ����̫������
	unguard;
}

void CSkyBox::RenderSunAndMoon( D3DXVECTOR3 vPos )
{
	guardfunc;
	if (!m_bIsDaytime)
	{
		return;
	}
	float alpha = (float(m_dwSunColor>>24)-64)/128.0f;

	if(alpha<0.0f)
		return;

	D3DXMATRIX mat,pMat,vMat;
	IRenderer* RI = GetEngine()->GetRenderer();

	vMat = GetMe3dConfig()->GetCamera()->GetViewMatrix();
	pMat = GetMe3dConfig()->GetCamera()->GetProjMatrix();

	vMat._41 = vMat._43 = 0.0f;
	vMat._42 *= 0.005f;

	D3DXVECTOR3	pt, tpt, ppt;
	D3DXVec3TransformCoord(&tpt, &m_vSunPos, &vMat);

	if(tpt.z < 100)
		return;
	D3DXVec3TransformCoord(&ppt, &tpt, &pMat);

	m_SunScreenPos.x = ppt.x;
	m_SunScreenPos.y = ppt.y;



	if(ppt.x<-1.2f || ppt.x>1.2f || ppt.y<-1.2f || ppt.y>1.2f)
		return;

	if(ppt.x<-1.0f)
		alpha += 5.0f*(1.0f+ppt.x);

	if(ppt.x>1.0f)
		alpha -= 5.0f*(ppt.x-1.0f);

	if(ppt.y<-1.0f)
		alpha += 5.0f*(1.0f+ppt.y);

	if(ppt.y>1.0f)
		alpha -= 5.0f*(ppt.y-1.0f);

	if(alpha<0.0f)
		return;


	D3DXMatrixIdentity(&mat);
	RI->SetTransform(D3DTS_VIEW, (float*)&mat);
	RI->SetTransform(D3DTS_PROJECTION, (float*)&mat);
	RI->SetRenderState( D3DRS_LIGHTING, TRUE );
	RI->SetRenderState( D3DRS_FOGENABLE, TRUE );

	alpha = 1.f;
	//DrawFlarePart(0.0f,  0,  0.5f,  1.0f,   1.0f,  1.0f,  alpha);
	//(float fPos, int nIndex, float fSize, float fRed, float fGreen, float fBlue, float fAlpha)

	float fSize = 1.f;

	D3DXVECTOR2 d = -m_SunScreenPos;
	D3DXVECTOR2 p = m_SunScreenPos;

	fSize *= 0.4f;
	float	dx = fSize,dy = fSize * 4.0f/3.0f;

	m_LFVerts[0].pos = D3DXVECTOR3(p.x-dx, p.y-dy,  1.f);
	m_LFVerts[1].pos = D3DXVECTOR3(p.x-dx, p.y+dy,  1.f);
	m_LFVerts[2].pos = D3DXVECTOR3(p.x+dx, p.y-dy,  1.f);
	m_LFVerts[3].pos = D3DXVECTOR3(p.x+dx, p.y+dy,  1.f);

	DWORD col = D3DCOLOR_COLORVALUE(alpha, alpha, alpha, alpha);
	RI->SetRenderState( D3DRS_TEXTUREFACTOR, m_dwSunColor);
	RI->SetRenderState( D3DRS_ZENABLE, true );
	RI->DirectPushSurface(m_nFlareTexID[9],-1,TERRAIN_SKYBOX, D3DFVF_SKYBOXVERTEX, sizeof( LF_VERTEX ),(BYTE*)m_LFVerts, 4, NULL, 2, eLightingDisable| eUseTextureColor | eAlphaBlend| eOpAdd| eZWriteDisable | eCullCCW, D3DPT_TRIANGLESTRIP );


	RI->SetTransform(D3DTS_VIEW, (FLOAT*)&GetMe3dConfig()->GetCamera()->GetViewMatrix());
	RI->SetTransform(D3DTS_PROJECTION, (FLOAT*)&GetMe3dConfig()->GetCamera()->GetProjMatrix());
	unguard;
}

void CSkyBox::Render(D3DXVECTOR3 vPos)
{
	guardfunc;
	if(m_pVB==NULL)
		return;

	HRESULT hr = NULL;
	IRenderer* RI = GetEngine()->GetRenderer();
	LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)RI->GetRealDevice();
	RI->SetRenderState( D3DRS_FOGENABLE, FALSE );

	D3DXMATRIX	vMat=GetMe3dConfig()->GetCamera()->GetViewMatrix();

	static float fViewZ = -150.0f;
	D3DXMATRIX matView;
	vPos.x = 0;
	vPos.y = 0;
	vPos.z /= 1000;
	if (GetMe3dConfig()->GetCamera()->IsLeftHand())
	{
		D3DXMatrixLookAtLH( &matView, &vPos, &GetMe3dConfig()->GetCamera()->GetViewDir(), &D3DXVECTOR3(0,0,1) );
	}
	else
	{
		D3DXMatrixLookAtRH( &matView, &vPos, &GetMe3dConfig()->GetCamera()->GetViewDir(), &D3DXVECTOR3(0,0,1) );
	}
	RI->SetTransform(D3DTS_VIEW, (FLOAT*)&matView);

	D3DXMatrixIdentity(&matView);
	static float fz = -130.0f;
	matView._43  = fz;

	RI->SetTransform(D3DTS_WORLD, (FLOAT*)&matView);


	// �������ɫ
   	//RI->Clear( 0L, D3DCLEAR_TARGET|D3DCLEAR_ZBUFFER , m_dwBaseColor, 1.0f, 0L );
 
 	//// ��Ⱦ��տ��--��ɫ
 	//RI->SetRenderState( D3DRS_TEXTUREFACTOR, m_dwTopColor );
 	//RI->DirectPushSurface( m_nTxSky, -1, TERRAIN_SKYBOX, D3DFVF_SKYBOXVERTEX, sizeof( SKYBOXVERTEX ),(BYTE*)m_pVB,m_nNumOfVertices,(BYTE*)m_pIB,m_nNumOfTriangles,eUseVB|eUseIB|eLightingDisable|eUseTextureColor|eZDisable|eZWriteDisable);
	

	m_bIsDaytime = ((m_dwTopColor&0xFF000000)==0);


	//if (m_bIsDaytime)// ��Ⱦ̫��
	//{
	//	// ��Ⱦ����
	//	RenderSunshine(matView);

	//	RenderSun(matView);

	//}
	//else//��Ⱦ����
	//{
	//	RenderSunshine(matView);
	//	RenderMoon();
	//}



	/////���ƵĴ������˺ܴ��ʱ�䣬��������
	//{
	//	// ��Ⱦ�Ʋ�
// 		ComputeClouds();
// 		RI->SetRenderState( D3DRS_TEXTUREFACTOR,m_dwCloudColor);
// 
// 		CloudsVB* pClouds = NULL;
// 		m_pCloudsVB->Lock( 0, 0, (void**)&pClouds, D3DLOCK_NOSYSLOCK );
// 		memcpy( pClouds, m_CloudsVB, CLOUDS_VB_SIZE*sizeof( CloudsVB ) );
// 		m_pCloudsVB->Unlock();
// 
// 		unsigned short* pCloudsIndices;
// 		m_pCloudsIB->Lock( 0, 0, (void**)&pCloudsIndices, D3DLOCK_NOSYSLOCK );
// 		memcpy( pCloudsIndices, m_CloudsIB, CLOUDS_IB_SIZE*sizeof(unsigned short) );
// 		m_pCloudsIB->Unlock();
// 
// 		RI->DirectPushSurface( -1, -1, TERRAIN_SKYBOX, D3DFVF_CLOUDSVERTEX, sizeof( CloudsVB ), (BYTE*)m_pCloudsVB, CLOUDS_VB_SIZE, (BYTE*)m_pCloudsIB, CLOUDS_NUM_Of_TRIANGLES, eUseIB|eUseVB|eLightingDisable|eUseTextureColor|eZDisable|eZWriteDisable );
	//}




	//RI->DirectPushSurface(-1,-1,TERRAIN_SKYBOX, D3DFVF_CLOUDSVERTEX, sizeof( CloudsVB ),(BYTE*)&m_CloudsVB,CLOUDS_VB_SIZE,(BYTE*)&m_CloudsIB,CLOUDS_NUM_Of_TRIANGLES,eLightingDisable|eUseTextureColor|eZDisable|eZWriteDisable );
	
	//if(!m_bIsDaytime)// �����Ʋ��Ч��
	//{
	//	
	//}

	RestoreFog();
	// ��Ⱦ���Ʋ㣬��ʱע��[QL]
	RI->SetRenderState( D3DRS_TEXTUREFACTOR,m_dwAmbientColor);
	RI->SetRenderState( D3DRS_FOGENABLE, FALSE );

	RI->DirectPushSurface(-1,-1,TERRAIN_SKYBOX, D3DFVF_CLOUDSVERTEX, sizeof( CloudsVB ),(BYTE*)m_pAmbientVB,m_nNumOfAV,(BYTE*)m_pAmbientIB,m_nNumOfAT,
		eUseVB|eUseIB|eLightingDisable|eAlphaBlend|eZDisable|eZWriteDisable | eRenderSkyBox, D3DPT_TRIANGLESTRIP );

	RI->SetRenderState( D3DRS_LIGHTING, TRUE );
	RI->SetRenderState( D3DRS_FOGENABLE, TRUE );

	RI->SetTransform(D3DTS_VIEW, (FLOAT*)&vMat);
	unguard;
}


void CSkyBox::RenderSunInWater(D3DXVECTOR3 vPos)
{
	guardfunc;
	//if(m_pVB==NULL)
	//	return;
	//HRESULT hr = 0;

	//IRenderer* RI = GetEngine()->GetRenderer();
	//LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)RI->GetRealDevice();

	//RI->SetRenderState( D3DRS_FOGENABLE, FALSE );

	//D3DXMATRIX	vMat=GetMe3dConfig()->GetCamera()->GetViewMatrix();

	//D3DXMATRIX matView;
	//vPos.x = 0;
	//vPos.y = 0;
	//vPos.z /= 1000;

	//D3DXMatrixLookAtLH( &matView, &vPos, &GetMe3dConfig()->GetCamera()->GetViewDir(), &D3DXVECTOR3(0,0,1) );
	//RI->SetTransform(D3DTS_VIEW, (FLOAT*)&matView);

	//// ��Ⱦ̫��
	//BuildMatrixFromVectorToVector((float*)D3DXVECTOR3(0,1,0),(float*)D3DXVECTOR3(-m_vSunNormal.x,m_vSunNormal.y,-m_vSunNormal.z),(float*)&matView);

	//RI->SetTransform(D3DTS_WORLD, (FLOAT*)&matView);

	//RI->SetRenderState( D3DRS_TEXTUREFACTOR,m_dwSunColor);
	//RI->DirectPushSurface(-1,-1,TERRAIN_SKYBOX, D3DFVF_SKYBOXVERTEX, sizeof( SKYBOXVERTEX ),(BYTE*)m_pSunVB,SUN_VB_SIZE,(BYTE*)m_pSunIB,SUN_NUM_Of_TRIANGLES,eUseVB|eLightingDisable|eAlphaBlend,D3DPT_TRIANGLEFAN );

	//// ��Ⱦ����
	//RI->SetRenderState( D3DRS_TEXTUREFACTOR,m_dwSunColor);
	//RI->DirectPushSurface(-1,-1,TERRAIN_SKYBOX, D3DFVF_CLOUDSVERTEX, sizeof( CloudsVB ),(BYTE*)m_pSunshineVB,SUN_VB_SIZE,(BYTE*)m_pSunshineIB,SUN_NUM_Of_TRIANGLES,eUseVB|eLightingDisable|eAlphaBlend|eOpAdd,D3DPT_TRIANGLEFAN );

	//D3DXMatrixIdentity(&matView);
	//RI->SetTransform(D3DTS_WORLD, (FLOAT*)&matView);



	//RI->SetRenderState( D3DRS_LIGHTING, TRUE );

	//RI->SetTransform(D3DTS_VIEW, (FLOAT*)&vMat);
	unguard;
}


void CSkyBox::RenderSun(const D3DXMATRIX &vMat)
{
	guardfunc;
	IRenderer* RI = GetEngine()->GetRenderer();
	LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)RI->GetRealDevice();

	D3DXMATRIX matView;
	BuildMatrixFromVectorToVector((float*)D3DXVECTOR3(0,1,0),(float*)D3DXVECTOR3(-m_vSunNormal.x,m_vSunNormal.y,-m_vSunNormal.z),(float*)&matView);

	RI->SetTransform(D3DTS_WORLD, (FLOAT*)&matView);

	RI->SetRenderState( D3DRS_TEXTUREFACTOR,m_dwSunColor);
	RI->DirectPushSurface(m_nTxSun,-1,TERRAIN_SKYBOX, D3DFVF_SKYBOXVERTEX, sizeof( SKYBOXVERTEX ),(BYTE*)m_pSunVB,SUN_VB_SIZE,(BYTE*)m_pSunIB,SUN_NUM_Of_TRIANGLES,
		eUseIB|eUseVB|eLightingDisable|eUseTextureColor|eAlphaBlend|eZDisable|eZWriteDisable,D3DPT_TRIANGLEFAN );

	D3DXMatrixIdentity(&matView);
	RI->SetTransform(D3DTS_WORLD, (FLOAT*)&matView);
	unguard;
}

void CSkyBox::RenderMoon()
{
	guardfunc;
	IRenderer* RI = GetEngine()->GetRenderer();
	LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)RI->GetRealDevice();

	D3DXMATRIX matView;
	BuildMatrixFromVectorToVector((float*)D3DXVECTOR3(0,1,0),(float*)D3DXVECTOR3(-m_vMoonNormal.x,m_vMoonNormal.y,-m_vMoonNormal.z),(float*)&matView);

	RI->SetTransform(D3DTS_WORLD, (FLOAT*)&matView);

	RI->SetRenderState( D3DRS_TEXTUREFACTOR,m_dwMoonColor);
	RI->DirectPushSurface(m_nTxMoon,-1,TERRAIN_SKYBOX, D3DFVF_SKYBOXVERTEX, sizeof( SKYBOXVERTEX ),(BYTE*)m_pSunVB,SUN_VB_SIZE,(BYTE*)m_pSunIB,SUN_NUM_Of_TRIANGLES,
		eUseIB|eUseVB|eLightingDisable|eUseTextureColor|eAlphaBlend|eZDisable|eZWriteDisable,D3DPT_TRIANGLEFAN );
	D3DXMatrixIdentity(&matView);
	RI->SetTransform(D3DTS_WORLD, (FLOAT*)&matView);
	unguard;
}


void CSkyBox::RenderSunshine(const D3DXMATRIX &vMat)
{
	guardfunc;
	IRenderer* RI = GetEngine()->GetRenderer();
	LPDIRECT3DDEVICE9 pDev = (LPDIRECT3DDEVICE9)RI->GetRealDevice();

	D3DXMATRIX matView;
	BuildMatrixFromVectorToVector((float*)D3DXVECTOR3(0,1,0),(float*)D3DXVECTOR3(-m_vSunNormal.x,m_vSunNormal.y,-m_vSunNormal.z),(float*)&matView);

	RI->SetTransform(D3DTS_WORLD, (FLOAT*)&matView);

	RI->SetRenderState( D3DRS_TEXTUREFACTOR,m_dwSunColor);
	RI->DirectPushSurface(-1,-1,TERRAIN_SKYBOX, D3DFVF_CLOUDSVERTEX, sizeof( CloudsVB ),(BYTE*)m_pSunshineVB,SUN_VB_SIZE,(BYTE*)m_pSunshineIB,SUN_NUM_Of_TRIANGLES,
		eUseIB|eUseVB|eLightingDisable|eAlphaBlend|eZDisable|eZWriteDisable|eOpAdd,D3DPT_TRIANGLEFAN );

	D3DXMatrixIdentity(&matView);
	RI->SetTransform(D3DTS_WORLD, (FLOAT*)&matView);
	unguard;
}

void CSkyBox::RenderFlare()
{	
	guardfunc;
	if (!m_bIsDaytime)
	{
		return;
	}
	float alpha = (float(m_dwSunColor>>24)-64)/128.0f;

	if(alpha<0.0f)
		return;

	D3DXMATRIX mat,pMat,vMat;
	IRenderer* RI = GetEngine()->GetRenderer();

	vMat = GetMe3dConfig()->GetCamera()->GetViewMatrix();
	pMat = GetMe3dConfig()->GetCamera()->GetProjMatrix();

	vMat._41 = vMat._43 = 0.0f;
	vMat._42 *= 0.005f;

	D3DXVECTOR3	pt, tpt, ppt;
	D3DXVec3TransformCoord(&tpt, &m_vSunPos, &vMat);

	if(tpt.z < 100)
		return;
	D3DXVec3TransformCoord(&ppt, &tpt, &pMat);

	m_SunScreenPos.x = ppt.x;
	m_SunScreenPos.y = ppt.y;

	

	if(ppt.x<-1.2f || ppt.x>1.2f || ppt.y<-1.2f || ppt.y>1.2f)
		return;

	if(ppt.x<-1.0f)
		alpha += 5.0f*(1.0f+ppt.x);

	if(ppt.x>1.0f)
		alpha -= 5.0f*(ppt.x-1.0f);

	if(ppt.y<-1.0f)
		alpha += 5.0f*(1.0f+ppt.y);

	if(ppt.y>1.0f)
		alpha -= 5.0f*(ppt.y-1.0f);

	if(alpha<0.0f)
		return;


	D3DXMatrixIdentity(&mat);
	RI->SetTransform(D3DTS_VIEW, (float*)&mat);
	RI->SetTransform(D3DTS_PROJECTION, (float*)&mat);

	alpha = 1.f;
	//DrawFlarePart(0.0f,  4,  0.8f,   0.7f,   0.4f,  0.4f,  alpha);
	DrawFlarePart(0.0f,  0,  0.5f,  1.0f,   1.0f,  1.0f,  alpha);
	//DrawFlarePart(0.0f,  1,  1.0f,   0.3f,   0.1f,  0.0f,  alpha);
	//DrawFlarePart(0.4f,  2,  0.2f,   0.07f,  0.07f, 0.10f, alpha);
// 	DrawFlarePart(0.32f, 5,  0.05f,  0.07f,  0.07f, 0.10f, alpha);
// 	DrawFlarePart(0.46f, 5,  0.1f,   0.07f,  0.07f, 0.10f, alpha);
// 	DrawFlarePart(0.8f,  2,  0.06f,  0.30f,  0.20f, 0.13f, alpha);
// 	DrawFlarePart(0.98f, 6,  0.01f,  0.50f,  1.00f, 0.50f, alpha);
// 	DrawFlarePart(1.15f, 4,  0.3f,  0.50f,  1.00f, 0.50f, alpha);
// 	DrawFlarePart(1.3f,  3,  0.2f,   0.30f,  0.20f, 0.13f, 1.0f*alpha);
// 	DrawFlarePart(1.25f, 3,  0.1f,   0.30f,  0.20f, 0.13f, 0.7f*alpha);
// 	DrawFlarePart(1.32f, 5,  0.05f,  0.30f,  0.20f, 0.13f, 0.7f*alpha);
// 	DrawFlarePart(1.38f, 5,  0.05f,  0.10f,  0.20f, 0.10f, 0.5f*alpha);
// 	DrawFlarePart(1.5f,  7,  0.3f,   0.10f,  0.20f, 0.10f, 0.4f*alpha);
// 	DrawFlarePart(1.7f,  8,  0.5f,   0.10f,  0.20f, 0.10f, 0.4f*alpha);

	RI->SetTransform(D3DTS_VIEW, (FLOAT*)&GetMe3dConfig()->GetCamera()->GetViewMatrix());
	RI->SetTransform(D3DTS_PROJECTION, (FLOAT*)&GetMe3dConfig()->GetCamera()->GetProjMatrix());
	unguard;
}

void CSkyBox::DrawFlarePart(float fPos, int nIndex, float fSize, float fRed, float fGreen, float fBlue, float fAlpha)
{
	guardfunc;
	D3DXVECTOR2 d = -m_SunScreenPos;
	D3DXVECTOR2 p = m_SunScreenPos + fPos * d;

	fSize *= 0.4f;
	float	dx = fSize,dy = fSize * 4.0f/3.0f;

	m_LFVerts[0].pos = D3DXVECTOR3(p.x-dx, p.y-dy,  0.8f);
	m_LFVerts[1].pos = D3DXVECTOR3(p.x-dx, p.y+dy,  0.8f);
	m_LFVerts[2].pos = D3DXVECTOR3(p.x+dx, p.y-dy,  0.8f);
	m_LFVerts[3].pos = D3DXVECTOR3(p.x+dx, p.y+dy,  0.8f);

	IRenderer* RI = GetEngine()->GetRenderer();

	DWORD col = D3DCOLOR_COLORVALUE(fRed*fAlpha, fGreen*fAlpha, fBlue*fAlpha, fAlpha);
	RI->SetRenderState( D3DRS_TEXTUREFACTOR, col);
	RI->DirectPushSurface(m_nFlareTexID[nIndex],-1,TERRAIN_SKYBOX, D3DFVF_SKYBOXVERTEX, sizeof( LF_VERTEX ),(BYTE*)m_LFVerts, 4, NULL, 2, eLightingDisable| eUseTextureColor | eAlphaBlend|eZDisable| eOpAdd|eZWriteDisable | eCullCCW, D3DPT_TRIANGLESTRIP );

	unguard;
}
void CSkyBox::InitClouds()
{
	guardfunc;
	srand((unsigned)HQ_TimeGetTime());
	WORD *indices = m_CloudsIB;
	//  ����������
	for (int i = 0; i <CLOUDS_HEIGHT-1; i++)
	{	
		for (int j = 0; j < CLOUDS_WIDTH-1; j++)
		{
			int nId = i*CLOUDS_WIDTH+j;
			*indices = nId;
			indices++;
			*indices = nId+1;
			indices++;
			*indices = nId+1+CLOUDS_WIDTH;
			indices++;
			*indices = nId;
			indices++;
			*indices = nId+1+CLOUDS_WIDTH;
			indices++;
			*indices = nId+CLOUDS_WIDTH;
			indices++;
		}
	}

	// ������ʼ��!
	for (int i = -CLOUDS_HEIGHT/2; i <CLOUDS_HEIGHT/2; i++)
	{	
		for (int j = -CLOUDS_WIDTH/2; j < CLOUDS_WIDTH/2; j++)
		{
			int nId = (i+CLOUDS_HEIGHT/2)*CLOUDS_WIDTH+(j+CLOUDS_WIDTH/2);
			m_Clouds[nId].nDensity = 0;
			m_Clouds[nId].nPressure = MAX_PRESSURE/2;

			m_CloudsVB[nId].x = j*(m_fRadius/CLOUDS_WIDTH);
			m_CloudsVB[nId].y = i*(m_fRadius/CLOUDS_HEIGHT);

			float fSqrR = pow(float(abs(j)),2)+pow(float(abs(i)),2);
			float fSqrH = ( 1.0f - fSqrR / pow(float(CLOUDS_WIDTH/2),2) ) * pow((m_fMaxHeight*0.8f),2) ;
				
			if (fSqrH>0)
			{
				m_CloudsVB[nId].z = Sqrt(fSqrH);
			}
			else
			{
				m_CloudsVB[nId].z = 0;
			}

			m_CloudsVB[nId].z -= 100;//+= m_vOrigin.z;
			

			m_CloudsVB[nId].dwColor = 0xFFFFFFFF;
		}
	}

	// ����ѹ��ͼ
	for (int i = 0; i <100; i++)
	{
		SetupCloudsPressure();
	}

	// ��ʼ���� ��ѹ -> ��ѹ
	for (int i = 0; i <200; i++)
	{
		SetupCloudsDensity();
	}

	// ������������


	// ������ɫ
	for (int i = 0; i <CLOUDS_HEIGHT; i++)
	{	
		for (int j = 0; j < CLOUDS_WIDTH; j++)
		{
			int nId = i*CLOUDS_WIDTH+j;
			Cloud * myCloud = &m_Clouds[nId];
			DWORD dwD = myCloud->nDensity * 260 / MAX_PRESSURE;
			if (dwD>=0)
			{
				if ( dwD < 256 )
				{
					m_CloudsVB[nId].dwColor = 0x00FFFFFF|(dwD<<24);

				}
				else
				{
					dwD = 511 - dwD;
					m_CloudsVB[nId].dwColor = 0xFF000000|dwD|(dwD<<8)|(dwD<<16);
				}
			}

		}
	}
	unguard;
}

// �������һ��ѹ��
void CSkyBox:: SetupCloudsPressure()
{
	guardfunc;
	int nRandW = rand() % CLOUDS_WIDTH;
	int nRandH = rand() % CLOUDS_HEIGHT;

	while (pow(float(nRandW-CLOUDS_WIDTH/2),2)+pow(float(nRandH-CLOUDS_HEIGHT/2),2)>CLOUDS_WIDTH*CLOUDS_HEIGHT/4)
	{
		nRandW = rand() % CLOUDS_WIDTH;
		nRandH = rand() % CLOUDS_HEIGHT;
	}
	int nId = nRandW+nRandH*CLOUDS_WIDTH;
	int nM = rand()%(MAX_PRESSURE); // ����
	int nR = 4+(rand()%(CLOUDS_HEIGHT/16));

	int nCount = rand()%20;
	for (int j = 0; j <nCount; j++)
	{
		nId = nId+((rand()%(nR*2))-nR)*CLOUDS_WIDTH+((rand()%(nR*2))-nR);
		for (int ny = -nR; ny <nR; ny++)
			for (int nx = -nR; nx <nR; nx++)
			{
				int nId1 = nId+ny*CLOUDS_WIDTH+nx;
				while (nId1<0)// ��ֹԽ��
				{
					nId1 += CLOUDS_SIZE;
				}
				nId1 %= CLOUDS_SIZE;

				float fRate = 1.0f -( (float)( nx*nx +ny*ny) ) / ( (float)(nR*nR));
				if ( fRate>0.0f )
				{
					m_Clouds[nId1].nPressure = m_Clouds[nId1].nPressure*(1.0f-fRate) + nM * fRate;//* m_Clouds[nId1].nPressure / MAX_PRESSURE;

					if (m_Clouds[nId1].nPressure>MAX_PRESSURE)
					{
						m_Clouds[nId1].nPressure=MAX_PRESSURE+(m_Clouds[nId1].nDensity)/MAX_PRESSURE;
					}
				}
			}
	}
	unguard;
}

// �������һ����
void CSkyBox:: SetupCloudsDensity()
{
	guardfunc;

	int nId = (rand() % CLOUDS_WIDTH)+(rand() % CLOUDS_HEIGHT)*CLOUDS_WIDTH;
	int nM = rand()%(MAX_PRESSURE/4);
	int nR = 2+(rand()%(CLOUDS_HEIGHT/32));

	int nCount = rand()%32;
	for (int j = 0; j <nCount; j++)
	{
		nId = nId+((rand()%(nR*2))-nR)*CLOUDS_WIDTH+((rand()%(nR*2))-nR);
		for (int ny = -nR; ny <nR; ny++)
			for (int nx = -nR; nx <nR; nx++)
			{
				int nId1 = nId+ny*CLOUDS_WIDTH+nx;
				while (nId1<0)
				{
					nId1 += CLOUDS_SIZE;
				}
				nId1 %= CLOUDS_SIZE;
				float fRate = 1.0f -( (float)( nx*nx +ny*ny) ) / ( (float)(nR*nR));
				if ( fRate>0.0f )
				{
					m_Clouds[nId1].nDensity += nM * fRate* m_Clouds[nId1].nPressure / MAX_PRESSURE;

					if (m_Clouds[nId1].nDensity>MAX_PRESSURE)
					{
						m_Clouds[nId1].nDensity=MAX_PRESSURE+(m_Clouds[nId1].nDensity)/MAX_PRESSURE;
					}
				}
			}
	}
	unguard;
}

void CSkyBox:: ComputeClouds()
{
	guardfunc;

	// �������

	//ѹ������
	static DWORD dwTime = HQ_TimeGetTime();
	if (HQ_TimeGetTime()-dwTime>3000)
	{
		dwTime = HQ_TimeGetTime();
		SetupCloudsPressure();
	}

	srand((unsigned)HQ_TimeGetTime());
	for (int i = 0; i <256; i++)
	{
		int nId = (rand() % CLOUDS_WIDTH)+(rand() % CLOUDS_HEIGHT)*CLOUDS_WIDTH;
		Cloud * myCloud = &m_Clouds[nId];

		if ( myCloud->nDensity>0 )
		{
			int nSelf = myCloud->nDensity; // �ø��� �����Ƶ�������ʧ
			for ( int n = 0; n < 8; n+=2 )// �ж���ѹ �������ܶ�
			{
				int nId1 = nId+DY[n]*CLOUDS_WIDTH+DX[n];
				while (nId1<0)
				{
					nId1 += CLOUDS_SIZE;
				}
				nId1 %= CLOUDS_SIZE;
				Cloud * myCloud2 = &m_Clouds[nId1];
				float fP = (float)(myCloud->nPressure+myCloud->nDensity-myCloud2->nPressure-myCloud2->nDensity)/4.0f/(float)MAX_PRESSURE;
				fP = max(fP, 0.0f);
				fP = min(fP, 0.05f);// �ƵĹ��� 0-0.05�����仯 ���~
				int nP = myCloud->nDensity*fP;
				nSelf -= nP;
				myCloud2->nDensity+=nP;// ���±�Ե�����ܶ�

				// ���±�Ե����ɫ
				DWORD dwD = myCloud2->nDensity * 260 / MAX_PRESSURE;
				if ( dwD < 256 )
				{
					m_CloudsVB[nId1].dwColor = 0x00FFFFFF|(dwD<<24);

				}
				else
				{
					dwD = 511 - dwD;
					m_CloudsVB[nId1].dwColor = 0xFF000000|dwD|(dwD<<8)|(dwD<<16);
				}
			}
			myCloud->nDensity = nSelf;// �����Լ����ܶ�

			// �����Լ�����ɫ
			DWORD dwD = myCloud->nDensity * 260 / MAX_PRESSURE;
			if ( dwD < 256 )
			{
				m_CloudsVB[nId].dwColor = 0x00FFFFFF|(dwD<<24);

			}
			else
			{
				dwD = 511 - dwD;
				m_CloudsVB[nId].dwColor = 0xFF000000|dwD|(dwD<<8)|(dwD<<16);
			}

		}
	}

	unguard;
}