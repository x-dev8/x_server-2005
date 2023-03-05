#pragma once

namespace BuildingConst
{
	//基本建筑物类型
	//在编辑器中标注的基本建筑类型
	enum enumBuildingBaseType
	{
		//基本上服务器中不可能出现normal
		buildingbase_normal				= 0
		//建筑点
		,buildingbase_jianzhudian
		//金矿点
		,buildingbase_jinkuangdian
		//主塔点
		,buildingbase_zhutadian
		//城门
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