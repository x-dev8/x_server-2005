// ColiCheck.cpp : implementation file
//

#include "stdafx.h"
#include "WorldEditor.h"
#include "ColiCheck.h"
#include "Me3d/Model/MexAnimCtrl.h"
#include "Me3d/Model/MexGeoChunk.h"
#include "MeTerrain/NdlGlobalResMgr.h"
// CColiCheck dialog

IMPLEMENT_DYNAMIC(CColiCheck, CDialog)

CColiCheck::CColiCheck(CWnd* pParent /*=NULL*/)
	: CDialog(CColiCheck::IDD, pParent)
{

}

CColiCheck::~CColiCheck()
{
}

void CColiCheck::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);

	DDX_Control(pDX, IDC_EDIT_Result, m_ColliResult);
}


BEGIN_MESSAGE_MAP(CColiCheck, CDialog)
END_MESSAGE_MAP()

void CColiCheck::DoColiCheck()
{
	CWorld* pWorld = SwGlobal::GetWorld();
	CWorldTile* tile = pWorld->GetWorldBuffer()->GetActiveTile( );
	if( NULL == tile )
		return ;

	if( !tile->IsLoad() )
		return ;
	std::string string;
	CNdlGlobalResMgr* pGlobalRes = pWorld->GetWorldBuffer()->GetGlobalResMgr();
	std::vector< CWorldRes* >& ModelRefList = tile->GetCResMgr()->GetStaticModelRefList();
	for(int i = 0; i < ModelRefList.size(); ++i)
	{
		CWorldRes* pRes = ModelRefList[i];
		if (!pRes)
		{
			continue;
		}
		CNdlStaticModelRes* pModelRes = pGlobalRes->FindRefStaticModel(pRes->GetName());
		if (!pModelRes )
		{
			continue;
		}
		IMex* pMex = pModelRes->GetModel()->GetMex();
		if (!pMex || strstr(pMex->GetFilename(),"null.mex") != NULL)
		{
			string += pRes->GetName();
			string+= "-------未能正确加载\r\n";
			m_ColliResult.SetWindowText(string.c_str());
			continue;
		}
		
		for (int nChunk = 0; nChunk < pMex->GetGeometry()->GetChunkCount(); ++nChunk)
		{
			IRenderable* pChunk = pMex->GetGeometry()->GetChunk(nChunk);
			if (!pChunk || 
				(pChunk->GetType() != Mex2GeoChunkProperty::eCollision
				&& pChunk->GetType() != Mex2GeoChunkProperty::eRCollision)
				)
			{
				continue;
			}
			CHelperGeoChunk* pColli = (CHelperGeoChunk*)pChunk;
			if(abs(pColli->GetMax()->x - pColli->GetMin()->x) < 0.5f
				|| abs(pColli->GetMax()->y - pColli->GetMin()->y) < 0.5f)
			{
				string += pRes->GetName();
				string+= "\r\n";
				m_ColliResult.SetWindowText(string.c_str());
			}
		}
	}
}

// CColiCheck message handlers
