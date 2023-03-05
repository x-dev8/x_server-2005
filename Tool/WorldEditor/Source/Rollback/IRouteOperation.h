#pragma once
#include "rollback\baseoperation.h"
#include "MeTerrain\SwType.h"

class CToolRoute;
class CRouteRes;

namespace NRouteTool
{
/*----------------------------------------------------------
desc	: 改变Route操作的接口类。
author	: zilong
version	: 1.0
date	: 2011-04-08

revision:
----------------------------------------------------------*/

class IRouteOperation: public IBaseOperation
{
public:
	IRouteOperation(CToolRoute *receiver_);
	virtual ~IRouteOperation(void);

protected:
	CToolRoute *m_pReceiver;
};

//增加路径
//由这个命令来回收和释放对象，删除命令就不用管了
class CAddRoute: public IRouteOperation
{
public:
	CAddRoute(CToolRoute *receiver_);
	virtual ~CAddRoute();

	virtual bool Excute(void);

	void SetData(CRouteRes *pRes_);

private:
	CRouteRes *m_pRes;
};

//删除路径
class CDeleteRoute: public IRouteOperation
{
public:
	CDeleteRoute(CToolRoute *receiver_);
	virtual ~CDeleteRoute();

	virtual bool Excute(void);

	void SetData(CRouteRes *pRes_);

private:
	CRouteRes *m_pRes;
};

//生成或者取消闭合路线
class CGenerateCloseRoute: public IRouteOperation
{
public:
	CGenerateCloseRoute(CToolRoute *receiver_);
	virtual ~CGenerateCloseRoute();

	virtual bool Excute(void);

	void SetData(CRouteRes *pRes_, bool bShow_, bool bGenerate_);

private:
	CRouteRes *m_pRes;
	bool m_bShow;	//
	bool m_bGenerate;	//标志是生成还是取消
};

//改变线路的某些属性
class CChangeRouteProperty: public IRouteOperation
{
public:
	CChangeRouteProperty(CToolRoute *receiver_);
	virtual ~CChangeRouteProperty();

	virtual bool Excute(void);

	void SetData(CNPCRouteRes *_pRes_, const char *name_, sInt32 nextMapId_, sInt32 nextRouteId_);

private:
	CRouteRes *m_pRes;
	std::string m_name;
	sInt32 m_nextMapId;
	sInt32 m_nextRouteId;
};

//在路线中增加一个点
//由这个命令来回收和释放对象，删除命令就不用管了
class CAddRoutePoint: public IRouteOperation
{
public:
	CAddRoutePoint(CToolRoute *receiver_);
	virtual ~CAddRoutePoint();

	virtual bool Excute(void);

	void SetData(CRouteRes *pRes_, int index_, CNPCRouteRes::SNpcRoutePoint *pNpcPoint_, Vector *pPoint_, bool bShow_);

private:
	CRouteRes *m_pRes;
	int m_index;
	CNPCRouteRes::SNpcRoutePoint *m_pNpcPoint;
	Vector *m_pPoint;
	bool m_bShow;
};

//在路线中删除一个点
class CDeleteRoutePoint: public IRouteOperation
{
public:
	CDeleteRoutePoint(CToolRoute *receiver_);
	virtual ~CDeleteRoutePoint();

	virtual bool Excute(void);

	void SetData(CRouteRes *pRes_, int index_);

private:
	CRouteRes *m_pRes;
	int m_index;
};

//改变点的位置
class CChangeRoutePointPosition: public IRouteOperation
{
public:
	CChangeRoutePointPosition(CToolRoute *receiver_);
	virtual ~CChangeRoutePointPosition();

	virtual bool Excute(void);

	void SetData(CRouteRes *pRes_, int index_, flt32 x_, flt32 y_, flt32 z_);

private:
	CRouteRes *m_pRes;
	int m_index;
	flt32 m_x, m_y, m_z;
};

//偷懒了，这里把几个原子操作集合到一起了
class CChangeRoutePointProperty: public IRouteOperation
{
public:
	CChangeRoutePointProperty(CToolRoute *receiver_);
	virtual ~CChangeRoutePointProperty();

	virtual bool Excute(void);

	void SetData(CRouteRes *pRes_, int index_, const CNPCRouteRes::SNpcRoutePoint &npcPoint_);

private:
	CRouteRes *m_pRes;
	int m_index;
	CNPCRouteRes::SNpcRoutePoint m_npcPoint;
};

}
