#pragma once

/*
 * 用于实现纸娃娃换装的简化实现类
 */
class ModelObj;
class Avatar
{
public:
	enum ComponentType
	{
		Hair = 0,			// 头发
		Hat,				// 帽子/头饰
		Face,				// 脸
		Shoulder,			// 肩
		Armour,				// 衣服
		//WaistBand,
		LeftHand,			// 左手
		RightHand,			// 右手
		Glove,				// 手套
		//Shield,			// 盾牌
		//Trousers,
		Shoes				// 鞋子
	};

	enum
	{
		eItem_RBack				= 1<<0,
		eItem_LeftHand			= 1<<1,
		eItem_RightHand			= 1<<2,
		eItem_Ground			= 1<<3,
		eItem_Shield			= 1<<4,
		eItem_LBack				= 1<<5,
		eItem_BackShield		= 1<<6,
	};

public:
	/*
	 * Avatar组件
	 */
	class Component
	{
	public:
		Component();
		~Component();

	public:
		/*
		 * 重置
		 */
		void Reset();

	public:
		BOOL IsAttachment;

		ModelObj *ModelObject;
		MtlAnim *MtrlAnims;

		int SpecularTexID;
		graphics::Material Material;

		MexCfgAvatarSetting *AvatarSetting;
		MexReplaceableTextureProj ReplaceableTextureProj;
		MexReplaceableTextureProj LuminanceTextureProj;

		std::vector<IRenderable *> Chunks;
		std::vector<DWORD> Flags;
	};

public:
	Avatar(ModelObj *parent);
	virtual ~Avatar();

public:
	void ChangeAvatarComponent(ComponentType componentType, ModelObj *obj);

	void Render(MexAnimCtrl *parent);

protected:
	typedef std::map<int, Component *> AvatarComponents;
	typedef AvatarComponents::iterator AvatarComponentsIter;

	ModelObj *mParent;
	AvatarComponents mComponents;
	std::vector<IMexAttachment *> mAttachments;
};