/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	NdlHelper.h
* Create: 	11/04/08
* Desc:		
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/

#ifndef _NDL_NDLHELPER_H__
#define _NDL_NDLHELPER_H__

////////////////////////////////////////////////////////////////////////////////
enum znHelperType
{
	HT_Axis			= 0,
	HT_Plane,
	HT_ChunkBox,
	HT_TileBox,
	HT_Transport,
	HT_Target,
	HT_FlyRoute,
	HT_MonsterQuad,
	HT_MonsterPoint,
	HT_Flag,			//用于在实际地图上显示导航地图的点击点
	HT_SoundPoint,
	HT_Flight,
	HT_VertLable,
    HT_ModelAxis,  //模型坐标轴
	HT_COUNT
};

//brush shape 's vertex definition
struct swVertLabelVertex
{
	enum
	{
		eFVF = D3DFVF_XYZ|D3DFVF_DIFFUSE
	};
	D3DXVECTOR3 p;
	DWORD		color;
};
//brush shape definition
struct swVertLabel{
	swVertLabelVertex kVertex[ 5 ];
};
//helper obj type
struct HelperObject
{
	TObjectEditInfo* pObject;
	swVertLabel VertLabel;
	bool		bCull;
	//ctor
	HelperObject(){
		pObject		= 0;
		bCull		= false;//show
	}
	//~ctor
	~HelperObject(){
		if(!pObject)
			return;
		SAFE_DELETE(pObject);
	}
	//update, only valid for mex model
	void Update( float fTime){
		if(bCull)
			return;
		if(!pObject)
			return;
		pObject->Update( fTime );				
	}
	//render
	void Render(float fAlpha = 1.f){
		if(bCull)
			return;
		if(pObject){
			pObject->Render( fAlpha );
		}
		else {//for vert label type	
			IRenderer* r = GetEngine()->GetRenderer();
			r->DirectPushSurface(
				-1,				
				-1,				
				-1,
				D3DFVF_XYZ|D3DFVF_DIFFUSE,
				sizeof( swVertLabelVertex ),
				(BYTE*)(&VertLabel.kVertex),
				5,
				0,
				1,eLightingDisable, D3DPT_LINELIST );
		}
	}
	//set position
	void SetPosition(float fX, float fY, float fZ)
	{
		if(bCull)
			return;
		if(pObject){
			pObject->model->SetPosition(fX, fY, fZ);
		}
		else{//for vert label type
			D3DXVECTOR3 v3(fX, fY, fZ);
			VertLabel.kVertex[0].p	= D3DXVECTOR3(  0.0f, 0.0f, 0.0f ) + v3;
			VertLabel.kVertex[1].p	= D3DXVECTOR3(  0.0f, 0.0f, 0.2f ) + v3;
			VertLabel.kVertex[2].p	= D3DXVECTOR3(  0.0f, 0.0f, 0.4f ) + v3;
			VertLabel.kVertex[3].p	= D3DXVECTOR3(  0.0f, 0.0f, 0.6f ) + v3;
			VertLabel.kVertex[4].p	= D3DXVECTOR3(  0.0f, 0.0f, 1.0f ) + v3;
		}
	}
	//set rotation
	void SetRotation(float fAngleX, float fAngleY, float fAngleZ)
	{
		if(bCull)
			return;
		if(pObject){
			pObject->model->SetRotationX(fAngleX);
			pObject->model->SetRotationY(fAngleY);
			pObject->model->SetRotationZ(fAngleZ);
		}
	}
	//this func only for VertLabel type
	void SetNormal(Vector& normal)
	{		
		D3DXVECTOR3 d3dNormal(normal.x, normal.y, normal.z);
		VertLabel.kVertex[1].p	= VertLabel.kVertex[0].p + d3dNormal;
		VertLabel.kVertex[2].p	= VertLabel.kVertex[1].p + d3dNormal;	
		VertLabel.kVertex[3].p	= VertLabel.kVertex[2].p + d3dNormal;	
		VertLabel.kVertex[4].p	= VertLabel.kVertex[3].p + d3dNormal;	
	}
};

////////////////////////////////////////////////////////////////////////////////
class CNdlHelper	/*: public NiRefObject*/
{
public:	
				CNdlHelper();
	virtual		~CNdlHelper();

	bool		Create();
	void		Render(float fAlpha = 1.0f);
	void		Update(float fTime);

	void PushSelModel(TObjectEditInfo *pModel_);
	void PopModel(TObjectEditInfo *pModel_);
	void ClearSelModel(void);
	bool IsSelectingModel(const TObjectEditInfo *pModel);

#ifdef ST_EDITOR_Helper
	NiNode*		GetNode();
	NiNode*		GetHelper( znHelperType helpType );
	void		AttachHelper(NiNodePtr pNode);
	void		DetachHelper(NiNodePtr pNode);
#endif
	HelperObject*		GetHelper( znHelperType helpType );
	void				AttachHelper(TObjectEditInfo* pNode);
	void				DetachHelper(TObjectEditInfo* pNode);
protected:
	bool		LoadHelperByType(znHelperType eType);
	bool		LoadPlane();
	bool		LoadAxis();
	bool		LoadChunkBox();
	bool		LoadTileBox();
	bool		LoadLightDir();
	bool		LoadTransport();
	bool		LoadFlyRoute();
	bool		LoadTarget();
	bool		LoadMonster();
	bool		LoadFlag();
	bool		LoadSoundPoint();
	bool		CreateVertLable();
    bool        LoadModelAxis();

protected:
#ifdef ST_EDITOR_Helper
	NiNodePtr		m_rootNode;
	NiNodePtr		m_helper[HT_Flight];
#endif	
	
	//helper objects
	HelperObject *m_helper[HT_COUNT];
	CString m_aHelperNames[HT_COUNT];

	std::vector<TObjectEditInfo*> m_attachedHelper;

	// 用于特殊显示被选中的model
	typedef std::vector<TObjectEditInfo *> TSelModels;
	TSelModels m_selModels;
};

#endif	// _NDL_NDLHELPER_H__
