/*******************************************************************************
*  Copyright ZNWL (C) 2007 - All Rights Reserved
*
* File: 	ToolObject.h
* Date: 	03/20/2007
* Desc:
*
*******************************************************************************/
#ifndef _EDIT_TOOLOBJECT_H__
#define _EDIT_TOOLOBJECT_H__

////////////////////////////////////////////////////////////////////////////////
#include "BaseTool.h"

//added by zilong. 
namespace NHelper
{
typedef CPoint TPoint;

/*----------------------------------------------------------
desc	: 线段
----------------------------------------------------------*/
struct SLineSegment 
{
	TPoint pt1, pt2;
};

/*----------------------------------------------------------
desc	: 多边形
----------------------------------------------------------*/
typedef std::vector<TPoint> SPolygon;

void CopyPolygon(SPolygon &_destPolygon, const SPolygon &srcPolygon_);

/*----------------------------------------------
desc	: 选择屏幕坐标下的point转换到世界坐标系中的3维点，z值为改点的地表高度。
----------------------------------------------*/
bool ScreenToWorld(const CPoint &point_, Vector &_worldPos);
bool ScreenToWorld(const CPoint &point_, flt32 *_pos);

/*----------------------------------------------
desc	: 获取屏幕坐标下的point对应的地图上的chunk。
----------------------------------------------*/
CWorldChunk *GetWorldChunk(const CPoint &point_);

typedef std::vector<CWorldChunk *> TChunks;
/*----------------------------------------------
desc	: 选择屏幕坐标下的area_跨越（转换到世界坐标系的xy平面）的地图上的chunks。
return	: 返回被选择的chunks的数量。
----------------------------------------------*/
int SelectChunks(const RECT &area_, TChunks &_chunks);

/*----------------------------------------------
desc	: 判断point是否点中了model。
return	: true,点中；false,未选中。
----------------------------------------------*/
bool IsPickingModel(const CPoint &point_, const TObjectInfo &model_);

/*----------------------------------------------
desc	: 计算屏幕坐标下的area_对应的frustum。这个功能还没有做好！！！！！
----------------------------------------------*/
bool BuildFrustum(const RECT &area_, FrustumEx &_frustum);

/*----------------------------------------------
desc	: 画2维的非填充实线框矩形。
In		: area_, 屏幕的矩形坐标。
		  color_，线条颜色
out		:
return	: 
----------------------------------------------*/
void DrawRect(const RECT &area_, DWORD color_);

/*----------------------------------------------
desc	: 画3维的非填充实线框多边形。
In		: polygon_, 世界空间系的多边形坐标， z = 0。
		  color_，线条颜色
out		:
return	: 
----------------------------------------------*/
void DrawPolygon3D(const SPolygon &polygon_, DWORD color_);

/*----------------------------------------------
desc	: 讲一个矩形的坐标转换成顺时针坐标，即left = minX, top = minY, right = maxX, bottom = maxY
In		: 		  
out		:
return	: 
----------------------------------------------*/
void TransformRect(RECT &_area_);

/*----------------------------------------------------------
desc	: 计算叉乘 |P0P1| × |P0P2|
----------------------------------------------------------*/
int Multiply(CPoint p1_, CPoint p2_, CPoint p0_);

/*----------------------------------------------------------
desc	: 判断线段是否包含点point
----------------------------------------------------------*/
bool IsOnline(const TPoint &point_, const SLineSegment &line_);

/*----------------------------------------------------------
desc	: 判断线段相交
----------------------------------------------------------*/
bool Intersect(const SLineSegment &L1_, const SLineSegment &L2_);

/*----------------------------------------------------------
desc	: 判断点p与多边形polygon的位置关系，要求polygon为简单多边形，顶点逆时针排列。
return	: true, 在多边形内或者边上；
		  false, 在多边形外
----------------------------------------------------------*/
bool IsInPolygon(const SPolygon &polygon_, const TPoint &point_);

}

class CWorldChunk;
class CNdlStaticModelRes;
////////////////////////////////////////////////////////////////////////////////
class CToolObject	: public CBaseTool
{
protected:
	struct SSelectingModelInfo
	{
		SSelectingModelInfo(TObjectEditInfo *pModel_, sInt32 id_):
	pModel(pModel_),
		id(id_)
	{

	}

	TObjectEditInfo *pModel;
	sInt32 id;
	};

	typedef std::list<SSelectingModelInfo> TModels;
	typedef std::vector<CWorldChunk *> TChunks;

	//鼠标拿着的model的信息。
	//如果是资源中的model，则保存的是id；如果是地图上的model，则保存的是指针
	union UPickedModelInfo
	{
		TObjectEditInfo *pModel;
		sInt32 id;
	};
	typedef std::list<UPickedModelInfo> TPickModels;

class IVisitor
{
public:
	IVisitor():m_pToolObject(NULL){};
	virtual ~IVisitor(){};
	void SetToolObject(CToolObject *pObject_){m_pToolObject = pObject_;}
	//virtual void Visit(void);

protected:
	CToolObject *m_pToolObject;
};

class CSelectingVisitor: public IVisitor
{
	friend class CToolObject;
	friend class CToolModel;
	friend class CPickingVisitor;
	friend class CTransformingVisitor;

public:
	CSelectingVisitor();
	~CSelectingVisitor();
	//virtual void Visit(void);

public:
	/*----------------------------------------------
	desc	: 根据屏幕矩形框选地图上的model，area_必须为顺时针矩形，否则结果不可预知。
	In		: bReset_, true, 重置并重新选择；
					   false，如果是点击，并且点击的目标已经存在于models中，
							  则视为去掉该model，否则视为加上该model。	  
	out		:
	return	: 返回已被选的model的个数。
	----------------------------------------------*/
	int SelectModels(const RECT &area_, bool bReset_ = true);
	int SelectModels(bool bReset_ = true);
	int ClickModels(const CPoint &point_);
	void CalPickResult( const TPickResult &pickResult);

	bool PushPickResult(TPickResult &_pickResult, const TPickResultInfo &info_);
	bool PopPickResult(TPickResult &_pickResult, sInt32 resultId_);

	bool PushSelectedModel(const SSelectingModelInfo &info_, const TPickResultInfo &resultInfo_);
	bool PushSelectedModel(const SSelectingModelInfo &info_);
	bool PopSelectedModel(TObjectEditInfo *pModel_);
	//bool PopSelectedModel(const SSelectingModelInfo &info_);

	/*----------------------------------------------
	desc	: 设置单个选择目标，并取消其他的选择目标
	In		: objIndex, model在容器中的序号
	----------------------------------------------*/
	bool SetSelectingModelIndex( sInt32 objIndex );
	/*----------------------------------------------
	desc	: 设置单个选择目标
	In		: modelID_, model的id
	----------------------------------------------*/
	bool SetSelectingModel(sInt32 modelID_, bool bSelected);

	//void PushModel(TObjectEditInfo *pModel_);
	//void PopModel(TObjectEditInfo *pModel_);

	void DeleteModel();
	bool ReplaceModel(sInt32 objIndex, LPCTSTR modelName);

	void Render();

	bool OnMouseMove( UINT nFlags, CPoint point );

	/*----------------------------------------------
	desc	: 释放选择的结果。
	----------------------------------------------*/
	void Reset(void);

	/*----------------------------------------------
	desc	: 判断存放当前选择的model的容器是否满了。
	----------------------------------------------*/
	bool IsFull(void);

	bool IsClickedModelsExist(void);
	void ClickedModels2SelectModels(bool bReplace = true);

	/*----------------------------------------------
	desc	: 用于对当前选择的model进行增选或者减选。
	----------------------------------------------*/
	void ReselectModels(const TModels &models_, const TPickResult &result_);

	/*----------------------------------------------
	desc	: 用于更新UI信息和坐标轴信息。
			  只要是被选择的model跟新了，都应该调用这个函数去更新相关信息。
	----------------------------------------------*/
	void UpdateInfo(TObjectEditInfo *pModel_);
public:
	//现状状态的维护--------------------------------------------
#define RectSelect_Can		0x01
#define RectSelect_Start	0x02
	void SetRectSelect(bool bFlag_)
	{
		if(bFlag_)
			m_bRectSelect = RectSelect_Can;
		else
			m_bRectSelect = 0;
	}
	void SetRectSelectStart(const CPoint &point_);
	void SetRectSelectStop(const CPoint &point_);

	bool CanRectSelect()
	{
		return (m_bRectSelect & RectSelect_Can) != 0;
	}

	bool IsRectSelectStart()
	{
		return (m_bRectSelect & RectSelect_Start) != 0;
	}
	//------------------------------------------------------------

protected:
	TModels m_selectModels;		//选择的models
	TPickResult	m_pickResult;	//
	NHelper::SPolygon m_selectPolygon;	//框选区域在世界坐标系的xy平面上的投影。

	TModels m_clickedModels;
	TPickResult m_clickResult;

	//状态-------------------------------
	BYTE m_bRectSelect;		//是否框选
	RECT m_selectedArea;	//框选区域
};

class CPickingVisitor: public IVisitor
{
	friend class CToolObject;
	friend class CToolModel;

public:
	CPickingVisitor();
	~CPickingVisitor();

	//virtual void Visit(void);

	/*----------------------------------------------
	desc	: 拾取地图上选择的models。
	----------------------------------------------*/
	bool PickModels(const TModels &srcModels_);

	/*----------------------------------------------
	desc	: 拾取资源中的一个model
	in		: model的id号，这个id号只是当前加载的资源在数组中的序号
	----------------------------------------------*/
	bool PickModel(sInt32 id_);

	bool InsertModels(const CPoint &point_);

	void Render();

	void Reset();

	void SetPaste();
	bool IsToPaste();

	bool OnMouseMove( UINT nFlags, CPoint point );
	bool OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags);

private:
/*----------------------------------------------
desc	: 用于表示鼠标拾起model的状态
----------------------------------------------*/
class CPickStatus
{
public:
	CPickStatus():m_status(E_Model_Status_PickNothing){};
	~CPickStatus(){};

	void SetPickNothing(void)
	{
		m_status = E_Model_Status_PickNothing;
	}

	void SetPickFromResource(void)
	{
		m_status = E_Model_Status_PickFromResource;
	}

	bool IsPickFromResource(void)
	{
		return E_Model_Status_PickFromResource == m_status;
	}

	void SetPickFromSelect(void)
	{
		m_status = E_Model_Status_PickFromSelect;
	}

	bool IsPickFromSelect(void)
	{
		return E_Model_Status_PickFromSelect == m_status;
	}

	private:
		enum EModelStatus
		{
			E_Model_Status_PickNothing = 0,
			E_Model_Status_PickFromSelect,		//来自地图的模型
			E_Model_Status_PickFromResource,	//来自资源的模型
		};

		EModelStatus m_status;
	};

protected:
	CPickStatus m_pickStatus;	//指示当前鼠标拿的是什么类型的模型
	TPickModels m_pickedModels;		//鼠标拿着的models，这些models会跟随鼠标的移动
	bool m_bToPaste;	//标志是否粘帖，每当粘帖完就要重置该标志，选择粘帖命令后再置位;
};

class CTransformingVisitor: public IVisitor
{
	friend class CToolObject;
	friend class CToolModel;

	friend class CSelectingVisitor;
	friend class CPickingVisitor;

protected:
	enum Axis
	{
		enum_AxisX = 0,
		enum_AxisY,
		enum_AxisZ,
		enum_None,
	};

	enum ETransformType
	{
		e_trans_move = 0,
		e_trans_rotate,
		e_trans_scale,
		e_trans_none,
	};

	enum EAxis2XY
	{
		e_axis2XY_x = 0,
		e_axis2XY_y,
		e_axis2XY_x_neg,
		e_axis2XY_y_neg,
	};

public:
	CTransformingVisitor();
	~CTransformingVisitor();
	//virtual void Visit(void);

	bool Create();
	void Reset();
	void ResetAxis();

	void Render();

	int GetSelectedAxis();
	int SelectAxis(const CPoint &point_);
	void   SetAxisPos(const Vector &pos_);
	Vector GetAxisPos(Vector& minVec,Vector& maxVec);

	bool OnMouseMove( UINT nFlags, CPoint point);
	bool OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags);
	void Move(Axis axis_, flt32 offset_);
	void Rotate(Axis axis_, flt32 offset_);
	void Scale(Axis axis_, flt32 offset_);

	void UpdateModel();



	void UpdateInfo(const TObjectEditInfo *pModel_);

	void ApplyTransform( CNdlStaticModelRes* modelRes);

	void SetTransformType(ETransformType type_);
	ETransformType GetTransformType(void){return m_tranType;}
	bool IsTransformed(void){return m_tranType != e_trans_none;}

	void UpdateMousePosition(const flt32 *pos_);

	void UpdateAxisInfo();

protected:
	//sInt16 m_pickAxis;    //拾取轴: x,y,z
	TObjectEditInfo *m_Axis[3];
	bool m_bPickedAxis[3];
	ETransformType m_tranType;	//变换的类型
	//EAxis2XY m_axis2XY[3];	//false则为x，true则为y

	flt32 m_position[3];
	flt32 m_offset[3];
	flt32 m_rotate[3];
	flt32 m_scale[3];

	flt32 m_mousePos[3];
	flt32 m_delta[3];
};

	friend class CToolModel;
	friend class CSelectingVisitor;
	friend class CPickingVisitor;
	friend class CTransformingVisitor;

public:
	CToolObject();
	virtual					~CToolObject();

	virtual bool			Create( CToolManager* toolMgr );
	void					Reset();
	virtual ToolID			GetToolId()	{ return TOOL_OBJECT; };
	void					Bind( CToolModel* modelDlg );
	
	virtual bool			OnLMouseDown( UINT nFlags, CPoint point );

	void					CalPickResult( const TPickResult &pickResult );
	bool					SetSelectingModelIndex( sInt32 objIndex );
	void					RefreshUIShow( TObjectEditInfo* objInfo );
	void					ShowPmpModel( );
	virtual bool			OnLMouseUp( UINT nFlags, CPoint point );
	virtual bool			OnLMouseDblClk( UINT nFlags, CPoint point );
	virtual bool			OnRMouseDown( UINT nFlags, CPoint point );
	virtual bool			OnRMouseUp( UINT nFlags, CPoint point );
	virtual bool			OnMouseMove( UINT nFlags, CPoint point );
	virtual bool			OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	virtual bool			OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );

	virtual void			Render();

	void					SetModelId( LPCTSTR fullModelName );

	CNdlStaticModelRes*		GetModelFromId( sInt32 modelId );
	
	sInt32					FindModelName( const char* modelName );
	sInt32					PushModelName( const char* modelName );

	void					EnumFile( LPCTSTR strDir, bool isRecursion );
	void					SyncOffset2WorldPos();
	void					LockHeight(bool bFlag);
	bool					IsLockHeight();
	bool					ReplaceModel(sInt32 objIndex,LPCTSTR modelName);

    //sInt16                  GetSelectAxis(CPoint point);
protected:
	//void					ApplyTransform( CNdlStaticModelRes* node );
	//void					ApplyTransform(TObjectEditInfo *_pModel, const flt32 *position_);
	void					RefreshUI();

	void SetOldPos(const CPoint &point_){m_oldPos = point_;}
	const CPoint &GetOldPos(void){return m_oldPos;}
protected:
	CToolModel*				m_wndModelDlg;
	//bool					m_isPickObj;
	bool					m_isLock;
	bool					m_isShowPreview;
// 	flt32					m_lastPos[3];
// 
// 	sInt32					m_selModelId;
// 
// 	
// 	//TObjectEditInfo*			m_selObject;
// 	
// 	sInt32					m_objIndex;							
	TObjectEditInfo*			m_selPmpModel;
	
	
	std::vector<CNdlStaticModelRes*>	m_modelList;

	CSelectingVisitor m_selectingVisitor;
	CPickingVisitor m_pickingVisitor;
	CTransformingVisitor m_transformingVisitor;

	bool m_bRightDragMove;	//表示在按住右键时是否拖动过
};

#endif	// _EDIT_TOOLOBJECT_H__


