#pragma once

/*
 * ����ʵ��ֽ���޻�װ�ļ�ʵ����
 */
class ModelObj;
class Avatar
{
public:
	enum ComponentType
	{
		Hair = 0,			// ͷ��
		Hat,				// ñ��/ͷ��
		Face,				// ��
		Shoulder,			// ��
		Armour,				// �·�
		//WaistBand,
		LeftHand,			// ����
		RightHand,			// ����
		Glove,				// ����
		//Shield,			// ����
		//Trousers,
		Shoes				// Ь��
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
	 * Avatar���
	 */
	class Component
	{
	public:
		Component();
		~Component();

	public:
		/*
		 * ����
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