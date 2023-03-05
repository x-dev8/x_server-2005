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
desc	: �߶�
----------------------------------------------------------*/
struct SLineSegment 
{
	TPoint pt1, pt2;
};

/*----------------------------------------------------------
desc	: �����
----------------------------------------------------------*/
typedef std::vector<TPoint> SPolygon;

void CopyPolygon(SPolygon &_destPolygon, const SPolygon &srcPolygon_);

/*----------------------------------------------
desc	: ѡ����Ļ�����µ�pointת������������ϵ�е�3ά�㣬zֵΪ�ĵ�ĵر�߶ȡ�
----------------------------------------------*/
bool ScreenToWorld(const CPoint &point_, Vector &_worldPos);
bool ScreenToWorld(const CPoint &point_, flt32 *_pos);

/*----------------------------------------------
desc	: ��ȡ��Ļ�����µ�point��Ӧ�ĵ�ͼ�ϵ�chunk��
----------------------------------------------*/
CWorldChunk *GetWorldChunk(const CPoint &point_);

typedef std::vector<CWorldChunk *> TChunks;
/*----------------------------------------------
desc	: ѡ����Ļ�����µ�area_��Խ��ת������������ϵ��xyƽ�棩�ĵ�ͼ�ϵ�chunks��
return	: ���ر�ѡ���chunks��������
----------------------------------------------*/
int SelectChunks(const RECT &area_, TChunks &_chunks);

/*----------------------------------------------
desc	: �ж�point�Ƿ������model��
return	: true,���У�false,δѡ�С�
----------------------------------------------*/
bool IsPickingModel(const CPoint &point_, const TObjectInfo &model_);

/*----------------------------------------------
desc	: ������Ļ�����µ�area_��Ӧ��frustum��������ܻ�û�����ã���������
----------------------------------------------*/
bool BuildFrustum(const RECT &area_, FrustumEx &_frustum);

/*----------------------------------------------
desc	: ��2ά�ķ����ʵ�߿���Ρ�
In		: area_, ��Ļ�ľ������ꡣ
		  color_��������ɫ
out		:
return	: 
----------------------------------------------*/
void DrawRect(const RECT &area_, DWORD color_);

/*----------------------------------------------
desc	: ��3ά�ķ����ʵ�߿����Ρ�
In		: polygon_, ����ռ�ϵ�Ķ�������꣬ z = 0��
		  color_��������ɫ
out		:
return	: 
----------------------------------------------*/
void DrawPolygon3D(const SPolygon &polygon_, DWORD color_);

/*----------------------------------------------
desc	: ��һ�����ε�����ת����˳ʱ�����꣬��left = minX, top = minY, right = maxX, bottom = maxY
In		: 		  
out		:
return	: 
----------------------------------------------*/
void TransformRect(RECT &_area_);

/*----------------------------------------------------------
desc	: ������ |P0P1| �� |P0P2|
----------------------------------------------------------*/
int Multiply(CPoint p1_, CPoint p2_, CPoint p0_);

/*----------------------------------------------------------
desc	: �ж��߶��Ƿ������point
----------------------------------------------------------*/
bool IsOnline(const TPoint &point_, const SLineSegment &line_);

/*----------------------------------------------------------
desc	: �ж��߶��ཻ
----------------------------------------------------------*/
bool Intersect(const SLineSegment &L1_, const SLineSegment &L2_);

/*----------------------------------------------------------
desc	: �жϵ�p������polygon��λ�ù�ϵ��Ҫ��polygonΪ�򵥶���Σ�������ʱ�����С�
return	: true, �ڶ�����ڻ��߱��ϣ�
		  false, �ڶ������
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

	//������ŵ�model����Ϣ��
	//�������Դ�е�model���򱣴����id������ǵ�ͼ�ϵ�model���򱣴����ָ��
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
	desc	: ������Ļ���ο�ѡ��ͼ�ϵ�model��area_����Ϊ˳ʱ����Σ�����������Ԥ֪��
	In		: bReset_, true, ���ò�����ѡ��
					   false������ǵ�������ҵ����Ŀ���Ѿ�������models�У�
							  ����Ϊȥ����model��������Ϊ���ϸ�model��	  
	out		:
	return	: �����ѱ�ѡ��model�ĸ�����
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
	desc	: ���õ���ѡ��Ŀ�꣬��ȡ��������ѡ��Ŀ��
	In		: objIndex, model�������е����
	----------------------------------------------*/
	bool SetSelectingModelIndex( sInt32 objIndex );
	/*----------------------------------------------
	desc	: ���õ���ѡ��Ŀ��
	In		: modelID_, model��id
	----------------------------------------------*/
	bool SetSelectingModel(sInt32 modelID_, bool bSelected);

	//void PushModel(TObjectEditInfo *pModel_);
	//void PopModel(TObjectEditInfo *pModel_);

	void DeleteModel();
	bool ReplaceModel(sInt32 objIndex, LPCTSTR modelName);

	void Render();

	bool OnMouseMove( UINT nFlags, CPoint point );

	/*----------------------------------------------
	desc	: �ͷ�ѡ��Ľ����
	----------------------------------------------*/
	void Reset(void);

	/*----------------------------------------------
	desc	: �жϴ�ŵ�ǰѡ���model�������Ƿ����ˡ�
	----------------------------------------------*/
	bool IsFull(void);

	bool IsClickedModelsExist(void);
	void ClickedModels2SelectModels(bool bReplace = true);

	/*----------------------------------------------
	desc	: ���ڶԵ�ǰѡ���model������ѡ���߼�ѡ��
	----------------------------------------------*/
	void ReselectModels(const TModels &models_, const TPickResult &result_);

	/*----------------------------------------------
	desc	: ���ڸ���UI��Ϣ����������Ϣ��
			  ֻҪ�Ǳ�ѡ���model�����ˣ���Ӧ�õ����������ȥ���������Ϣ��
	----------------------------------------------*/
	void UpdateInfo(TObjectEditInfo *pModel_);
public:
	//��״״̬��ά��--------------------------------------------
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
	TModels m_selectModels;		//ѡ���models
	TPickResult	m_pickResult;	//
	NHelper::SPolygon m_selectPolygon;	//��ѡ��������������ϵ��xyƽ���ϵ�ͶӰ��

	TModels m_clickedModels;
	TPickResult m_clickResult;

	//״̬-------------------------------
	BYTE m_bRectSelect;		//�Ƿ��ѡ
	RECT m_selectedArea;	//��ѡ����
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
	desc	: ʰȡ��ͼ��ѡ���models��
	----------------------------------------------*/
	bool PickModels(const TModels &srcModels_);

	/*----------------------------------------------
	desc	: ʰȡ��Դ�е�һ��model
	in		: model��id�ţ����id��ֻ�ǵ�ǰ���ص���Դ�������е����
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
desc	: ���ڱ�ʾ���ʰ��model��״̬
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
			E_Model_Status_PickFromSelect,		//���Ե�ͼ��ģ��
			E_Model_Status_PickFromResource,	//������Դ��ģ��
		};

		EModelStatus m_status;
	};

protected:
	CPickStatus m_pickStatus;	//ָʾ��ǰ����õ���ʲô���͵�ģ��
	TPickModels m_pickedModels;		//������ŵ�models����Щmodels����������ƶ�
	bool m_bToPaste;	//��־�Ƿ�ճ����ÿ��ճ�����Ҫ���øñ�־��ѡ��ճ�����������λ;
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
	//sInt16 m_pickAxis;    //ʰȡ��: x,y,z
	TObjectEditInfo *m_Axis[3];
	bool m_bPickedAxis[3];
	ETransformType m_tranType;	//�任������
	//EAxis2XY m_axis2XY[3];	//false��Ϊx��true��Ϊy

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

	bool m_bRightDragMove;	//��ʾ�ڰ�ס�Ҽ�ʱ�Ƿ��϶���
};

#endif	// _EDIT_TOOLOBJECT_H__


