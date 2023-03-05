/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	NdlRes.h
* Create: 	10/06/2006
* Desc:		地表元素和模型数据的数据结构定义
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef _NDL_NDLEDITRES_H__
#define _NDL_NDLEDITRES_H__

#include "MeTerrain/NdlRes.h"
#include "NpcInfo.h"
#include "PositionInfo.h"

struct TBox2D;
class CNdlLiquidRes;
class CResEditMgr;
class CNdlGlobalResMgr;
class CNdlEditWorldPicker;
class CNdlWorldEditor;
class CWorldReadStream;
class CWorldWriteStream;
class CToolWorldFogDlg;
class Box;
struct SBBox;
class TObjectEditInfo;
class CNdlLineRes : public CWorldRes
{
	friend	CResEditMgr;
public:
	CNdlLineRes();
	~CNdlLineRes();
	void			Render();
	void setColor( DWORD color );
protected:
	//brush shape 's vertex definition
	struct swChunckLineVertex
	{
		enum
		{
			eFVF = D3DFVF_XYZ|D3DFVF_DIFFUSE|D3DFVF_TEX1
		};
		D3DXVECTOR3 p;
		DWORD		color;
		float		u,v;
	};
	//brush shape definition
	struct swChunckLine : public MeCommonAllocObj<swChunckLine>
	{
		swChunckLineVertex kVertex[2*WORLD_TILE_CHUNK_UNIT_NUM+1];
	};
	swChunckLine*	m_line;
};

const int MESH_SIZE = 2 *1024;
class CMeshLineRes
{
	friend	CResEditMgr;
public:
	CMeshLineRes();
	~CMeshLineRes();
	void			Render();
	void			Clean();

	D3DXVECTOR3 m_pVertex[MESH_SIZE];
	sInt32 m_nSize;
};

class CSoundPointEditRes : public CSoundPointRes
{
public:
	CSoundPointEditRes();
	virtual ~CSoundPointEditRes();


protected:
	TObjectEditInfo*		m_SoundPointPointModel;
public:
	void					ApplyTransform();
	TObjectEditInfo*			RetrievePointModel();
	TObjectEditInfo*			GetSoundPointPointModel() const { return m_SoundPointPointModel; }

	void					ShowSoundPointPoint(bool bShow);
	void					DetachModel();
};

class CRouteRes : public CWorldRes
{
public:
	CRouteRes();
	virtual ~CRouteRes();

	virtual				bool IsFlyRoute() = 0;

	flt32					GetPosX(int index) const;
	flt32					GetPosY(int index) const;
	flt32					GetPosZ(int index) const;
	void					SetPosX(int index,flt32 val) ;
	void					SetPosY(int index,flt32 val) ;
	void					SetPosZ(int index,flt32 val) ;

	void							SetRoutePoint(int index,float x,float y ,float z);
	virtual void							AddRoutePoint( float x,float y ,float z ,bool bShow);
	virtual	void							DeleteRoutePoint( int index );
	void							DeleteRoutePointModel( int index );
	virtual	void							ClearRoutePoint();
	void DetachModel();
	void ClearModel();
	TObjectEditInfo* RetrievePointModel();

	void ShowRoutePoint(bool bShow);

	size_t GetPointCount(void){return m_RoutePointList.size();}

	bool CreatePoint(float x_, float y_, float z_, Vector* &_point);
	//这里仅仅是将对象加入或者弹出容器，并不是真的创建或者删除对象
	bool PushPoint(int index_, Vector *pPoint_, bool bShow_);
	bool PopPoint(int index_);
	bool GetPoint(int index_, Vector* &_pPoint);

	std::vector<Vector*>&			GetRoutePointList(){return m_RoutePointList;}		
	std::vector<TObjectEditInfo*>&			GetRoutePointModelList(){return m_RoutePointModelList;}		
protected:
	std::vector<Vector* >			m_RoutePointList;
	std::vector<TObjectEditInfo*>		m_RoutePointModelList;

public:
	void					ApplyTransform(int index);
};

// class CFlyRouteRes : public CRouteRes
// {
// public:
// 	CFlyRouteRes();
// 	virtual ~CFlyRouteRes(){}
// 
// 	virtual				bool IsFlyRoute() {return true;}
// 
// 
// };

class CNPCRouteRes : public CRouteRes
{
public:
	CNPCRouteRes();
	virtual ~CNPCRouteRes();
	virtual				bool IsFlyRoute() {return m_bFlyRoute;}
	typedef struct SNpcRoutePoint
	{
		float				mWalkSpeed;
		float				mWalkLenght;
		sInt32				mStayTime;
		sInt32				mStayAction;
		sInt32				mSceneID;

		SNpcRoutePoint()
		{
			mWalkSpeed = 0.85;
			mWalkLenght = 0.9;
			mStayTime = 1000;
			mStayAction = -1;
			mSceneID = 0;
		}
	}SNpcRoutePoint;
	virtual void							AddRoutePoint( float x,float y ,float z ,bool bShow);
	virtual	void							DeleteRoutePoint( int index );
	virtual	void							ClearRoutePoint();
	float					GetWalkSpeed(int index) const;
	void					SetWalkSpeed(int index,float val);
	float					GetWalkLength(int index) const;
	void					SetWalkLength(int index,float val);
	sInt32					GetStayTime(int index) const;
	void					SetStayTime(int index,sInt32 val);
	sInt32					GetStayAction(int index) const;
	void					SetStayAction(int index,sInt32 val);
	sInt32					GetSceneID(int index);
	void					SetSceneID(int index, sInt32 val);

	void SetNpcRoutePoint(int index_, const SNpcRoutePoint &npcPoint_);
	SNpcRoutePoint *GetRoutePoint(int index_);

	sInt32					GetNextMapID() const { return m_nNextMapID; }
	void					SetNextMapID(sInt32 val) { m_nNextMapID = val; }
	sInt32					GetNextRouteID() const { return m_nNextRouteID; }
	void					SetNextRouteID(sInt32 val) { m_nNextRouteID = val; }
	void					SetFlyRoute(bool val) { m_bFlyRoute = val; }

	//added by zilong. 2011-04-08. ------------------------------------------------
	//这两个接口放在这里实际上不太合理，因为他们原本不应该是这个类该有的功能。
	//但是为了方便，目前就放到这里吧。
	//生成闭合路线
	bool GenerateCloseRoute(bool bShow_);
	//撤消闭合路线，即还原到生成闭合路线前的路线
	bool CancelCloseRoute();
	//added by zilong. end. -------------------------------------------------------

	bool CreatePoint(float x_, float y_, float z_, SNpcRoutePoint* &_npcPoint, Vector* &_point);
	bool PushPoint(int index_, SNpcRoutePoint *pNpcPoint_, Vector *pPoint_, bool bShow_);
	bool PopPoint(int index_);
	bool GetPoint(int index_, SNpcRoutePoint* &_pNpcPoint, Vector* &_pPoint);

protected:
	sInt32							m_nNextMapID;
	sInt32							m_nNextRouteID;
	bool							m_bFlyRoute;
protected:
	std::vector<SNpcRoutePoint* >			m_NpcRoutePointList;
};






class CTransportEditRes : public CTransportRes
{
public:
	CTransportEditRes();
	~CTransportEditRes();

public:
	virtual void					ApplyTransform();
	virtual TObjectInfo*	GetModel();
	virtual void							AttachModel();
	virtual void							DetachModel();
protected:
	TObjectInfo* m_model;
};

class CTargetEditRes :public CTargetRes	
{

public:
	CTargetEditRes();
	CTargetEditRes(bool bRelive);	
	~CTargetEditRes();
	virtual void					ApplyTransform();
	virtual TObjectInfo*	GetModel();
	virtual void							AttachModel();
	virtual void							DetachModel();
protected:
	TObjectInfo* m_model;
};



class CNpcRes : public CWorldRes
{
public:
	CNpcRes();
	~CNpcRes();

	sInt32 GetNpcId(){return m_npc->id;}
	flt32 GetPosX();
	void  SetPosX(flt32 fValue);

	void  SetModelId(sInt32 id);

	const char* GetNpcName();


	flt32 GetPosY();
	void SetPosY(flt32 fValue);

	flt32 GetPosZ();
	void SetPosZ(flt32 fValue);

	flt32 GetMapId();

	int GetDirection();
	void SetDirection(int nvalue);

	flt32 GetBodyScale();
	void  SetScale(flt32 fValue);

	void AttachModel();
	void DetachModel();
	bool LoadModel(const char* pszFileName);
	int  GetModelId(){return m_npc->modelId;}

	void  DrawAABB();
	//added by zilong. 2011-03-15. ---------------------------------------
	void DrawView(void);
	//added by zilong. end. ----------------------------------------------
	void  DrawFindPointer();

	void  AddFindPointer(flt32 x,flt32 y);
	void AddFindPointer(const PositionInfo::Position &position_);
	bool  DestroyPointer();
	int GetNpcResId(){return m_NpcResID;}

	TObjectEditInfo* GetObjectInfo();

	bool   UpdateFindPointer(int nType,flt32 x,flt32 y,bool bShow);
	bool   DelFindPointer();

	void  SetResId(int Id){m_NpcResID = Id;}

	void SetNpc(NpcInfo::Npc *pNpc);

	void SetNpcPosition();

private:
	int   m_NpcResID;          //NpcResID
	TObjectEditInfo* m_model;
	NpcInfo::Npc *m_npc;

	TObjectEditInfo *pPosModel;    //Npc寻路点模型
	PositionInfo::Position *pPosition;
};

class CNdlNpcLineRes : public CWorldRes
{
public:
	CNdlNpcLineRes();
	~CNdlNpcLineRes();

	void CreateLine(CWorldTile* pTile); 

	void Render();

	struct swLineVertex
	{
		enum
		{
			eFVF = D3DFVF_XYZ|D3DFVF_DIFFUSE
		};
		D3DXVECTOR3 p;
		DWORD		color;
	};

	struct swChunckLine : public MeCommonAllocObj<CNdlNpcLineRes::swChunckLine>
	{
		swLineVertex kVertex[2 * 15 + 1];
	};
private:
	std::vector<swChunckLine*> m_LineSet; 
};

class CMonsterQuadRes : public CWorldRes
{
public:
	struct AutoTalk {};

public:
	CMonsterQuadRes();
	~CMonsterQuadRes();

	CMonsterQuadRes * Clone(void)
	{
		CMonsterQuadRes *pClone = MeNew CMonsterQuadRes;
		*pClone = *this;

		//以下需要改写
		pClone->m_model = NULL;

		return pClone;
	}

public:
	const char * GetZoneName() const { return m_szZoneName; }
	void SetZoneName(const char *val) { strcpy_s(m_szZoneName, val); }

	float GetPosX() { return (m_fLeft + m_fRight) / 2; }
	float GetPosY() { return (m_fTop + m_fBottom) / 2; }

	float GetWidth() { return m_fRight - m_fLeft; }
	float GetHeight() { return m_fTop - m_fBottom; }

	void Update(float x, float y, float w = 0, float h = 0);

	const char * GetEnterScript() const { return m_szEnterScript; }
	void SetEnterScript(const char *val) { strcpy_s(m_szEnterScript, val); }

	const char * GetLeaveScript() const { return m_szLeaveScript; }
	void SetLeaveScript(const char *val) { strcpy_s(m_szLeaveScript, val); }

public:
	void ApplyTransform();
	TObjectEditInfo* GetModel();

	void AttachModelToNdlHelper();
	void DetachModelFromNdlHelper();

	void UpdateMonsterModel();
	void RenderMonsterModel();

	void DrawView(float radius);

public:
	/// Zone Info
	char m_szZoneName[RES_NAME_LEN];

	float m_fLeft;
	float m_fTop;
	float m_fRight;
	float m_fBottom;

	int m_nAIStep;			/// AIStep
	int m_nPKMode;			/// 能否Pk
	bool m_bCanStall;		/// 能否摆摊
	bool m_bCanDuel;		/// 能否摆摊

	char m_szEnterScript[RES_NAME_LEN];
	char m_szLeaveScript[RES_NAME_LEN];

public:
	/// Monster Group Info
	bool m_bRandRange;		/// 是否随机范围

	int m_nDir;				/// 朝向
	int m_nMonsterId;		/// Monster Id
	int m_nNumber;			/// 数量
	int m_nRelife;			/// 刷新时间
	int m_nCountry;			/// 国家

	bool m_bEnable;			/// 是否开启
	bool m_bHide;			/// 是否隐藏

	char m_szDeadScript[RES_NAME_LEN];
	char m_szAIScript[RES_NAME_LEN];

	int m_nAIValue;			/// 思考的时间
	int m_nCamp;			/// 阵营
	int m_nForce;			/// 势力

	int m_nPath;			/// 寻路点ID

	/// 仅编辑器使用，当这个标记为真的时候渲染朝向箭头和刷怪点仅中间一点
	bool m_bIsOnePoint;
	
protected:

	TObjectEditInfo *m_model;
	TObjectEditInfo *mMonsterModel;
};

#endif	// _NDL_NDLEDITRES_H__
