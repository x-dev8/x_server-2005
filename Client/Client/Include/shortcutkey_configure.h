
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
		AN_SCKC_forward = 0,		//��ǰ��
		AN_SCKC_backward,			//�����
		AN_SCKC_leftRotate,			//����ת	
		AN_SCKC_rightRotate,		//����ת
		AN_SCKC_leftwalk,			//������
		AN_SCKC_rightwalk,			//������
		AN_SCKC_zoomoutCamera,		//���������
		AN_SCKC_zoominCamera,		//��Զ�����
		AN_SCKC_jump,				//��Ծ

		AN_SCKC_changeModeName,		//�л�npc ���� ����ͷ���ϵ�����
		AN_SCKC_switchOperateMode,	//���ģʽ ����ģʽ�л�
		AN_SCKC_switchCameraMode,	//�����ӽ� �����ӽ��л�
		AN_SCKC_changeTarget,		//Ŀ����л�

		AN_SCKC_autoRun,				//�����Զ��ܲ�

		AN_SCKC_SelectMe,				//ѡ���Լ�
		AN_SCKC_SelectTeamPlayer1,		//ѡ�����1
		AN_SCKC_SelectTeamPlayer2,		//ѡ�����2
		AN_SCKC_SelectTeamPlayer3,		//ѡ�����3
		AN_SCKC_SelectTeamPlayer4,		//ѡ�����4
		AN_SCKC_SelectTeamPlayer5,		//ѡ�����5

		AN_SCKC_PrintScreen,			//��ͼ

		AN_SCKC_uiBeginChat,			//�����Ĭ�ϼ��ʼ����

		AN_SCKC_ShowPlayer,				//��ʾ/�������

		AN_SCKC_HideUI,					//����UI

		AN_SCKC_CallPrivteChat,			//�ظ�������

		AN_SCKC_PickAll,				//��ȡ������Ʒ
		


        AN_SCKC_ChangeSuit1,            //��װ����1
        AN_SCKC_ChangeSuit2,            //��װ����2
        AN_SCKC_ChangeSuit3,            //��װ����3
        AN_SCKC_ChangeSuit4,            //��װ����4
        AN_SCKC_ChangeSuit5,            //zhuxincong 9.15 �ĳ��� �һ�һ������ ��װ����5 

        AN_SCKC_uiGroup = 49,           //�����ui        
		AN_SCKC_uiCountry,			    //�򿪹���ui		added by zhuomeng.hu		[9/8/2010]		
		AN_SCKC_uiBaseProperty,			//������ui
		AN_SCKC_uiPack,					//�򿪱���ui
		AN_SCKC_uiTask,					//������ui
		AN_SCKC_uiSkill,				//�򿪼���ui
		AN_SCKC_uiGuild,				//�򿪹���ui
		AN_SCKC_uiOther,				//��ui
		AN_SCKC_uiFriend,				//�򿪺���ui
		AN_SCKC_uiCompound,				//�򿪺ϳ�ui
		AN_SCKC_uiPet,					//�򿪰���ui
		
							//
		AN_SCKC_uiHideOrSystem,			//�رյ�ǰ���Թرյ�ui ���û�����ϵͳ����
		AN_SCKC_openBigMap,				//�򿪴��ͼ
		AN_SCKC_openAreaMap,			//�������ͼ

		AN_SCKC_openTitle,				// �򿪳ƺ�
		AN_SCKC_openEvent,				// �򿪻
		AN_SCKC_uiTrack = 65,			//��׷��ui
		AN_SCKC_uiRank,					//���а�
		AN_SCKC_uiShopCenter,			//�̳�
        AN_SCKC_uiAutoAttack,           //�Զ����
        AN_SCKC_uiChangeSuit,            //�ɾ�
		AN_SCKC_uiExpressionAction,		// ���鶯��
		AN_SCKC_uiAchivement = 71, //�ɾ�
		AN_SCKC_uiEpic,					// ��ʷ��
		AN_SCKC_uiWealthProtect,		// �Ʋ�����
		AN_SCKC_uiSuAnimal, //�������
		AN_SCKC_uiFamily,				//�򿪼���ui

		AN_SCKC_skillLeft1 = 101,		//���ܿ������1
		AN_SCKC_skillLeft2,				//���ܿ������2
		AN_SCKC_skillLeft3,				//���ܿ������3
		AN_SCKC_skillLeft4,				//���ܿ������4
		AN_SCKC_skillLeft5,				//���ܿ������5
		AN_SCKC_skillLeft6,				//���ܿ������6
		AN_SCKC_skillLeft7,				//���ܿ������7
		AN_SCKC_skillLeft8,				//���ܿ������8
		AN_SCKC_skillLeft9,				//���ܿ������9
		AN_SCKC_skillLeft10,			//���ܿ������10

		AN_SCKC_skillExLeft1 = 151,		//��չ���ܿ������1
		AN_SCKC_skillExLeft2,			//��չ���ܿ������2
		AN_SCKC_skillExLeft3,			//��չ���ܿ������3
		AN_SCKC_skillExLeft4,			//��չ���ܿ������4
		AN_SCKC_skillExLeft5,			//��չ���ܿ������5
		AN_SCKC_skillExLeft6,			//��չ���ܿ������6
		AN_SCKC_skillExLeft7,			//��չ���ܿ������7
		AN_SCKC_skillExLeft8,			//��չ���ܿ������8
		AN_SCKC_skillExLeft9,			//��չ���ܿ������9
		AN_SCKC_skillExLeft10,			//��չ���ܿ������10
		AN_SCKC_skillExLeft11,			//��չ���ܿ������11
		AN_SCKC_skillExLeft12,			//��չ���ܿ������12
		AN_SCKC_skillExLeft13,			//��չ���ܿ������13
		AN_SCKC_skillExLeft14,			//��չ���ܿ������14
		AN_SCKC_skillExLeft15,			//��չ���ܿ������15
		AN_SCKC_skillExLeft16,			//��չ���ܿ������16
		AN_SCKC_skillExLeft17,			//��չ���ܿ������17
		AN_SCKC_skillExLeft18,			//��չ���ܿ������18
		AN_SCKC_skillExLeft19,			//��չ���ܿ������19
		AN_SCKC_skillExLeft20,			//��չ���ܿ������20
		AN_SCKC_skillExLeft21,			//��չ���ܿ������21
		AN_SCKC_skillExLeft22,			//��չ���ܿ������22
		AN_SCKC_skillExLeft23,			//��չ���ܿ������23
		AN_SCKC_skillExLeft24,			//��չ���ܿ������24

		AN_SCKC_TeamRequest = 180,		//�����������ӿ�ݼ�

		AN_SCKC_PetSkill1 = 201,		//�ٻ��޿����1
		AN_SCKC_PetSkill2,				//�ٻ��޿����2
		AN_SCKC_PetSkill3,				//�ٻ��޿����3
		AN_SCKC_PetSkill4,				//�ٻ��޿����4
		AN_SCKC_PetSkill5,				//�ٻ��޿����5
		AN_SCKC_PetSkill6,				//�ٻ��޿����6
		AN_SCKC_PetSkill7,				//�ٻ��޿����7
		AN_SCKC_PetSkill8,				//�ٻ��޿����8
		AN_SCKC_PetSkill9,				//�ٻ��޿����9
		AN_SCKC_PetSkill10,				//�ٻ��޿����10

		

		//AN_SCKC_openStoryBook	= 82,		//�򿪹��»�
		//AN_SCKC_uiShopCenter	= 83,		//���̳ǽ���		

		//AN_SCKC_uiMainPageturn1 = 84,	//main.UI listIcon���·�ҳ��1
		//AN_SCKC_uiMainPageturn2 = 85,	//main.UI listIcon���·�ҳ��1
		//AN_SCKC_uiMainPageturn3 = 86,	//main.UI listIcon���·�ҳ��1
		//AN_SCKC_uiXITONGFU      = 87,   //��ϵͳ��ݼ� //zjj add 08.5 
		//AN_SCKC_uiAction        = 89,    //�򿪶������� zjj add[2008.7.8]

		//AN_SCKC_moveleftCamera,		//����ƽ�������
		//AN_SCKC_moverightCamera,	//����ƽ�������
		//AN_SCKC_moveupCamera = 10,	//�����������
		//AN_SCKC_movedownCamera,		//�����������

		//AN_SCKC_rbMenuShowMode,		//ģ���ϴ򿪲�������

		AN_SCKC_useSkill_operator,		//ʹ�ü���
		An_SCK_Other,                            //������չ����
		AN_SCK_Gam,								//�罻����
		AN_SCK_SuAnimalCard,				//����ͼ��
		AN_SCK_SuAnimalHole,				//���
		AN_SCK_SuAnimalStar,				//
		AN_SCK_SuAnimalGemUp,				//
		AN_SCK_SuAnimalGem,				//
		AN_SCK_GoldTrade,				//����
		AN_SCK_SuAnimalTransferStar,	//ת��
		AN_SCK_SuAnimalGemRemove,		//��ʯ�Ƴ�
		AN_SCK_UNBIND  = 223,			//���
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
	//Ӧ���ڳ�����...
	const char* getValueString( AN_Configure_ShortcutKey::ShortCutKey_Configure type );
	const char* getDiscription( AN_Configure_ShortcutKey::ShortCutKey_Configure type );
	int			getValueCharInput(AN_Configure_ShortcutKey::ShortCutKey_Configure type);
	int			getValueCharWin32(AN_Configure_ShortcutKey::ShortCutKey_Configure type);
	void		dealwithHotkey(CActionManager::SGameActionOperation action);

	bool		hasKey(int key, AN_Configure_ShortcutKey::ShortCutKey_Configure type);

	//Ӧ����ͨ���� ͨ�� VK_BACK ȡ "backspace"
	const char* getStringKeyWin32( int key );	//key win32�� ������ʮ������ֵ ��:a �� 65

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
