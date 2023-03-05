//////////////////////////////////////////////////////////////////////////
// added, jiayi, [2010/6/7]
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "Me3d/Engine/MeSorter.h"
#include "Me3d/Engine/MeCollector.h"
#include "Me3d/Engine/MeRenderObject.h"
#include "Singleton.h"

/** ������Ⱦ����
@desc: 
	�����Ⱦ������Ⱦ�б�������Ԥ�������ʽ����
��Ⱦ��
*/
class MeRenderManager : public Singleton< MeRenderManager >
{
public:
	/** ������Ⱦ��Ԫ
	@desc:
		��̬������Ⱦ��Ԫ����ֹ�������ݺ�ջ���
	*/
// 	static MeRenderObject* CreateRenderObject( MeRenderObject::ERenderObjectType eType );	
	
	/** ������Ⱦ��Ԫ
	*/
// 	static void DeleteAllRenderObjects();

public:
	~MeRenderManager();

	void OnDeviceLost();

	void Clear();

	WORD GetLastRenderTime() const { return m_dRenderTime; }
	WORD GetCollectorRenderTime() const { return m_dCollectorRenderTime; }

	void SetSorter( MeSorter* pkSorter );
	MeSorter* GetSorter() const;

	void AddCollector( MeCollector* pkCollector );
	//MeCollector* GetCollector() const;	
	
	bool AddObject( MeSorter::RenderableBasePtr pkObject );
	
	void DoRender(bool bPost);


	bool IsFreshObject( MeSorter::RenderableBasePtr pkObject );


protected:
	void DoRenderCollector();

	friend class Singleton< MeRenderManager >;
	/// hide ctor
	MeRenderManager(){m_dRenderTime = 0;m_dCollectorRenderTime = 0;}

	bool HaveCollectors() const;

	bool AddToCollector( MeSorter::RenderableBasePtr pkObject );

protected:
	MeSorterPtr m_spSorter;

	typedef std::vector< MeCollectorPtr > MeCollectorPtrs;
	typedef MeCollectorPtrs::iterator MeCollectorPtrsIter;
	MeCollectorPtrs m_aspCollectors; 
// 	static MeSorter::RenderableList ms_kItems;

	WORD				m_dRenderTime;
	WORD				m_dCollectorRenderTime;
};