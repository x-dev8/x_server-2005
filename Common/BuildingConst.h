#pragma once

namespace BuildingConst
{
	//��������������
	//�ڱ༭���б�ע�Ļ�����������
	enum enumBuildingBaseType
	{
		//�����Ϸ������в����ܳ���normal
		buildingbase_normal				= 0
		//������
		,buildingbase_jianzhudian
		//����
		,buildingbase_jinkuangdian
		//������
		,buildingbase_zhutadian
		//����
		,buildingbase_chengmen
	};

	enum enumConstSize
	{
		const_jianzhudian_wid		= 4
		,const_jianzhudian_hei		= 4
		,const_jinkuangdian_wid		= 4
		,const_jinkuangdian_hei		= 4
		,const_zhutadian_wid		= 6
		,const_zhutadian_hei		= 6
	};
};