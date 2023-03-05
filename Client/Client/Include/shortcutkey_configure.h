
#ifndef AN_SHORTCUTKEY_CONFIGURE_H_
#define AN_SHORTCUTKEY_CONFIGURE_H_

#include <map>
#include <string>
#include "ActionManager.h"
// #include "Tinyxml/tinyxml.h"

namespace AN_Configure_ShortcutKey
{
	enum ShortCutKey_Configure
	{
		AN_SCKC_forward = 0,		//向前走
		AN_SCKC_backward,			//向后退
		AN_SCKC_leftRotate,			//向左转	
		AN_SCKC_rightRotate,		//向右转
		AN_SCKC_leftwalk,			//向左走
		AN_SCKC_rightwalk,			//向右走
		AN_SCKC_zoomoutCamera,		//拉近摄像机
		AN_SCKC_zoominCamera,		//拉远摄像机
		AN_SCKC_jump,				//跳跃

		AN_SCKC_changeModeName,		//切换npc 人物 怪物头顶上的名字
		AN_SCKC_switchOperateMode,	//鼠标模式 键盘模式切换
		AN_SCKC_switchCameraMode,	//锁定视角 自由视角切换
		AN_SCKC_changeTarget,		//目标的切换

		AN_SCKC_autoRun,				//开启自动跑步

		AN_SCKC_SelectMe,				//选择自己
		AN_SCKC_SelectTeamPlayer1,		//选择队友1
		AN_SCKC_SelectTeamPlayer2,		//选择队友2
		AN_SCKC_SelectTeamPlayer3,		//选择队友3
		AN_SCKC_SelectTeamPlayer4,		//选择队友4
		AN_SCKC_SelectTeamPlayer5,		//选择队友5

		AN_SCKC_PrintScreen,			//截图

		AN_SCKC_uiBeginChat,			//聊天框默认激活开始聊天

		AN_SCKC_ShowPlayer,				//显示/隐藏玩家

		AN_SCKC_HideUI,					//隐藏UI

		AN_SCKC_CallPrivteChat,			//回复密聊人

		AN_SCKC_PickAll,				//捡取所有物品
		


        AN_SCKC_ChangeSuit1,            //换装方案1
        AN_SCKC_ChangeSuit2,            //换装方案2
        AN_SCKC_ChangeSuit3,            //换装方案3
        AN_SCKC_ChangeSuit4,            //换装方案4
        AN_SCKC_ChangeSuit5,            //zhuxincong 9.15 改成了 挂机一键启动 换装方案5 

        AN_SCKC_uiGroup = 49,           //打开组队ui        
		AN_SCKC_uiCountry,			    //打开国家ui		added by zhuomeng.hu		[9/8/2010]		
		AN_SCKC_uiBaseProperty,			//打开属性ui
		AN_SCKC_uiPack,					//打开背包ui
		AN_SCKC_uiTask,					//打开任务ui
		AN_SCKC_uiSkill,				//打开技能ui
		AN_SCKC_uiGuild,				//打开公会ui
		AN_SCKC_uiOther,				//打开ui
		AN_SCKC_uiFriend,				//打开好友ui
		AN_SCKC_uiCompound,				//打开合成ui
		AN_SCKC_uiPet,					//打开帮助ui
		
							//
		AN_SCKC_uiHideOrSystem,			//关闭当前可以关闭的ui 如果没有则打开系统界面
		AN_SCKC_openBigMap,				//打开大地图
		AN_SCKC_openAreaMap,			//打开区域地图

		AN_SCKC_openTitle,				// 打开称号
		AN_SCKC_openEvent,				// 打开活动
		AN_SCKC_uiTrack = 65,			//打开追踪ui
		AN_SCKC_uiRank,					//排行榜
		AN_SCKC_uiShopCenter,			//商城
        AN_SCKC_uiAutoAttack,           //自动打怪
        AN_SCKC_uiChangeSuit,            //成就
		AN_SCKC_uiExpressionAction,		// 表情动作
		AN_SCKC_uiAchivement = 71, //成就
		AN_SCKC_uiEpic,					// 大史记
		AN_SCKC_uiWealthProtect,		// 财产保护
		AN_SCKC_uiSuAnimal, //宠物界面
		AN_SCKC_uiFamily,				//打开家族ui

		AN_SCKC_skillLeft1 = 101,		//技能快捷栏左1
		AN_SCKC_skillLeft2,				//技能快捷栏左2
		AN_SCKC_skillLeft3,				//技能快捷栏左3
		AN_SCKC_skillLeft4,				//技能快捷栏左4
		AN_SCKC_skillLeft5,				//技能快捷栏左5
		AN_SCKC_skillLeft6,				//技能快捷栏左6
		AN_SCKC_skillLeft7,				//技能快捷栏左7
		AN_SCKC_skillLeft8,				//技能快捷栏左8
		AN_SCKC_skillLeft9,				//技能快捷栏左9
		AN_SCKC_skillLeft10,			//技能快捷栏左10

		AN_SCKC_skillExLeft1 = 151,		//扩展技能快捷栏左1
		AN_SCKC_skillExLeft2,			//扩展技能快捷栏左2
		AN_SCKC_skillExLeft3,			//扩展技能快捷栏左3
		AN_SCKC_skillExLeft4,			//扩展技能快捷栏左4
		AN_SCKC_skillExLeft5,			//扩展技能快捷栏左5
		AN_SCKC_skillExLeft6,			//扩展技能快捷栏左6
		AN_SCKC_skillExLeft7,			//扩展技能快捷栏左7
		AN_SCKC_skillExLeft8,			//扩展技能快捷栏左8
		AN_SCKC_skillExLeft9,			//扩展技能快捷栏左9
		AN_SCKC_skillExLeft10,			//扩展技能快捷栏左10
		AN_SCKC_skillExLeft11,			//扩展技能快捷栏左11
		AN_SCKC_skillExLeft12,			//扩展技能快捷栏左12
		AN_SCKC_skillExLeft13,			//扩展技能快捷栏左13
		AN_SCKC_skillExLeft14,			//扩展技能快捷栏左14
		AN_SCKC_skillExLeft15,			//扩展技能快捷栏左15
		AN_SCKC_skillExLeft16,			//扩展技能快捷栏左16
		AN_SCKC_skillExLeft17,			//扩展技能快捷栏左17
		AN_SCKC_skillExLeft18,			//扩展技能快捷栏左18
		AN_SCKC_skillExLeft19,			//扩展技能快捷栏左19
		AN_SCKC_skillExLeft20,			//扩展技能快捷栏左20
		AN_SCKC_skillExLeft21,			//扩展技能快捷栏左21
		AN_SCKC_skillExLeft22,			//扩展技能快捷栏左22
		AN_SCKC_skillExLeft23,			//扩展技能快捷栏左23
		AN_SCKC_skillExLeft24,			//扩展技能快捷栏左24

		AN_SCKC_TeamRequest = 180,		//请求或邀请组队快捷键

		AN_SCKC_PetSkill1 = 201,		//召唤兽快捷栏1
		AN_SCKC_PetSkill2,				//召唤兽快捷栏2
		AN_SCKC_PetSkill3,				//召唤兽快捷栏3
		AN_SCKC_PetSkill4,				//召唤兽快捷栏4
		AN_SCKC_PetSkill5,				//召唤兽快捷栏5
		AN_SCKC_PetSkill6,				//召唤兽快捷栏6
		AN_SCKC_PetSkill7,				//召唤兽快捷栏7
		AN_SCKC_PetSkill8,				//召唤兽快捷栏8
		AN_SCKC_PetSkill9,				//召唤兽快捷栏9
		AN_SCKC_PetSkill10,				//召唤兽快捷栏10

		

		//AN_SCKC_openStoryBook	= 82,		//打开故事会
		//AN_SCKC_uiShopCenter	= 83,		//打开商城界面		

		//AN_SCKC_uiMainPageturn1 = 84,	//main.UI listIcon上下翻页到1
		//AN_SCKC_uiMainPageturn2 = 85,	//main.UI listIcon上下翻页到1
		//AN_SCKC_uiMainPageturn3 = 86,	//main.UI listIcon上下翻页到1
		//AN_SCKC_uiXITONGFU      = 87,   //打开系统快捷键 //zjj add 08.5 
		//AN_SCKC_uiAction        = 89,    //打开动作界面 zjj add[2008.7.8]

		//AN_SCKC_moveleftCamera,		//向左平移摄像机
		//AN_SCKC_moverightCamera,	//向右平移摄像机
		//AN_SCKC_moveupCamera = 10,	//向上拉摄像机
		//AN_SCKC_movedownCamera,		//向下拉摄像机

		//AN_SCKC_rbMenuShowMode,		//模型上打开操作界面

		AN_SCKC_useSkill_operator,		//使用技能
		An_SCK_Other,                            //其他扩展功能
		AN_SCK_Gam,								//社交功能
		AN_SCK_SuAnimalCard,				//宠物图鉴
		AN_SCK_SuAnimalHole,				//打孔
		AN_SCK_SuAnimalStar,				//
		AN_SCK_SuAnimalGemUp,				//
		AN_SCK_SuAnimalGem,				//
		AN_SCK_GoldTrade,				//寄售
		AN_SCK_SuAnimalTransferStar,	//转星
		AN_SCK_SuAnimalGemRemove,		//宝石移除
		AN_SCK_UNBIND  = 223,			//解绑
		AN_SCKC_MAX
	};

	struct shortcutKeyValue
	{
		std::string		_szValue;
		std::string		_szDiscription;
		bool			_alt;
		bool			_ctrl;
		bool			_shift;

		shortcutKeyValue() { _alt = _ctrl = _shift = false; }
	};

	struct win32String
	{
		std::string		_szValue;
		std::string		_szHex;
		std::string		_szTip;
	};

	enum HotkeyState
	{
		ON_KEY_NONE,
		ON_KEY_DOWN
	};
}


class CShortCutKey_Configure
{
public:
	CShortCutKey_Configure();
	virtual ~CShortCutKey_Configure();

public:
	//应用于程序中...
	const char* getValueString( AN_Configure_ShortcutKey::ShortCutKey_Configure type );
	const char* getDiscription( AN_Configure_ShortcutKey::ShortCutKey_Configure type );
	int			getValueCharInput(AN_Configure_ShortcutKey::ShortCutKey_Configure type);
	int			getValueCharWin32(AN_Configure_ShortcutKey::ShortCutKey_Configure type);
	void		dealwithHotkey(CActionManager::SGameActionOperation action);

	bool		hasKey(int key, AN_Configure_ShortcutKey::ShortCutKey_Configure type);

	//应用于通用性 通过 VK_BACK 取 "backspace"
	const char* getStringKeyWin32( int key );	//key win32中 按键的十进制数值 如:a 即 65

	void	load();
	void	loadDefault();
	void	write();
	void	initHotkey();

	void		setHotkeyState(int actionId, AN_Configure_ShortcutKey::HotkeyState state );
	void		hasChangeCustomKey();

	std::map<int, AN_Configure_ShortcutKey::shortcutKeyValue>&	getCustomkeyMap()
	{
		return customKeyMap;
	}
	std::map<int, AN_Configure_ShortcutKey::win32String>& getShortcutKeyMap()
	{
		return shortcutMap;
	}
	std::map<int, AN_Configure_ShortcutKey::shortcutKeyValue>&	getDefaultCustomkeyMap()
	{
		return defaultCustomKeyMap;
	}

	const std::map<std::string, std::vector<int> >& getTypeIdMap() { return typeIdMap; }
	const std::vector<std::string>& getTypes() { return types; }

private:
	
	std::map<int, AN_Configure_ShortcutKey::shortcutKeyValue>	customKeyMap;
	std::map<int, AN_Configure_ShortcutKey::shortcutKeyValue>	defaultCustomKeyMap;
	std::map<int, AN_Configure_ShortcutKey::win32String>	shortcutMap;
	std::map<std::string, std::vector<int> >	typeIdMap;
	std::vector<std::string> types;
	std::string		_description;

	int	hotkeyState[AN_Configure_ShortcutKey::AN_SCKC_MAX];

	static const std::string version;
};

extern CShortCutKey_Configure g_shortcutKey_configure;

#endif
