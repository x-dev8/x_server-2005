#pragma once

#define MEXVIEWER_FILESIZE_1K					1024
#define MEXVIEWER_FILESIZE_1M					1024 * 1024

#define RIGHT_WND_MEXCONFIG_TREE_HEIGHT			200

#include "AutoDesk3dsMaxObjProperties.h"

typedef std::vector<MexCfgAvatarSetting *>::iterator AvatarSettingsIter;

/*
 * �ұߴ���, ������ʾ��༭����
 */
class AnimationWindow;
class AvatarWindow;
class ModelConfigWindow;
class RightWindow : public wxWindow
{
public:
	enum ChildWndType
	{
		ChildWnd_ModelInfo = 0,
		ChildWnd_Animation,
		ChildWnd_PartEdit,
		ChildWnd_Avatar,
		ChildWnd_ModelConfig,
	};

	enum MexConfigItem
	{
		ModelScale = 0,
		BodyRadius,
		SoundFilename,
		Range,
		Loop,
		Frequence,
		Intensity,
		Width,
		Height,
		Length,
		Lift,
		Skin,
		MexConfigItemMax
	};

public:
	RightWindow(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size);
	virtual ~RightWindow();

public:
	/*
	 * ���������Ӵ���
	 */
	void HideAllChildren();

	/*
	 * ��ʾָ�����Ӵ���
	 */
	void ShowChildByType(ChildWndType type);

	/*
	 * ����ָ���Ӵ��ڵ�����
	 */
	void UpdateInfoByChildType(ChildWndType type);

	/*
	 * ����ģ����ת�Ƕ�
	 */
	void UpdateModelInfoRotation();

	/*
	 * ��ȡ��ǰ���ӷ��������� 
	 */
	int GetCurrentParticleEmitter();

	/*
	 * ���µ�ǰ���ӷ���������
	 */
	bool SaveCurrentParticleEmitterParams();

	ModelConfigWindow * GetModelConfigWnd() {return m_ModeConfigWnd;}

protected:
	void CreateModelInfoChildWnds();
	void CreateParticleEditChildWnds();

protected:
	void OnModelInfoPropertyGridChange(wxPropertyGridEvent &event);
	void OnParticleEditPropertyGridChange(wxPropertyGridEvent &event);

	void OnParticleEmitterChoice(wxCommandEvent &WXUNUSED(event));
	void OnParticleEmitterParamExport(wxCommandEvent &WXUNUSED(event));

	void OnMexConfigTreeBeginLabelEdit(wxTreeEvent &event);
	void OnMexConfigTreeEndLabelEdit(wxTreeEvent &event);
	void OnMexConfigTreeRightClick(wxTreeEvent &event);
	void OnMexConfigTreeDoubleClick(wxTreeEvent &event);
	void OnMenuItemAddSkin(wxCommandEvent &WXUNUSED(event));
	void OnMenuItemSkinRename(wxCommandEvent &WXUNUSED(event));
	void OnMenuItemDelSkin(wxCommandEvent &WXUNUSED(event));

	void OnSize(wxSizeEvent &event);

	DECLARE_EVENT_TABLE()

protected:
	ChildWndType mCurChildType;

	// ������Ϣ
	wxPropertyGrid *mModelInfoPG;
	wxPropertyCategory *mBasicInfoCat;
	wxPropertyCategory *mControlCat;
	wxPropertyCategory *mSkinTexCat;
	wxTreeCtrl *mMexConfigTree;
	wxTreeItemId mMexConfigTreeItems[MexConfigItemMax];
	wxString mLabelBeforeEdit;
	wxMenu *mAddSkinMenu;
	wxMenu *mSkinEditMenu;

	// Animation
	AnimationWindow *mAnimationWnd;

	// ���ӱ༭
	wxStaticText *mParticleEmitterChoiceLabel;
	wxChoice *mParticleEmitterChoice;
	wxButton *mPartEmitterExportBtn;
	wxPropertyGrid *mPartEmitterEditPG;
	wxPropertyCategory *mEmitterCat;
	wxPropertyCategory *mParticleCat;
	wxPropertyCategory *mTimeCat;
	wxPropertyCategory *mPlaneCat;
	wxPropertyCategory *mTexCat;
	wxPropertyCategory *mOtherCat;
	wxPropertyCategory *mNewCat;
	AutoDesk3dsMaxObjProperties mAutoDeskObjProps;

	// ֽ����
	AvatarWindow *mAvatarWnd;

	ModelConfigWindow *m_ModeConfigWnd;
};