#pragma once
#include "rollback\baseoperation.h"
#include "MeTerrain\SwType.h"

class CToolRoute;
class CRouteRes;

namespace NRouteTool
{
/*----------------------------------------------------------
desc	: �ı�Route�����Ľӿ��ࡣ
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

//����·��
//��������������պ��ͷŶ���ɾ������Ͳ��ù���
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

//ɾ��·��
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

//���ɻ���ȡ���պ�·��
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
	bool m_bGenerate;	//��־�����ɻ���ȡ��
};

//�ı���·��ĳЩ����
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

//��·��������һ����
//��������������պ��ͷŶ���ɾ������Ͳ��ù���
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

//��·����ɾ��һ����
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

//�ı���λ��
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

//͵���ˣ�����Ѽ���ԭ�Ӳ������ϵ�һ����
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
