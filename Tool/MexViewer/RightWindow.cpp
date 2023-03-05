#include "StdAfx.h"
#include "RightWindow.h"

#include "ModelObj.h"
#include "MainFrame.h"
#include "MiddleWindow.h"
#include "RenderHelper.h"
#include "Utility.h"
#include "AnimationWindow.h"
#include "AvatarWindow.h"
#include "CopyableMessageDialog.h"
#include "ModelConfigWindow.h"

static const DWORD ParticleTypes[3] =
{
	MEX2_PARTICLE_EMITTER_HEAD, MEX2_PARTICLE_EMITTER_TAIL, MEX2_PARTICLE_EMITTER_BOTH
};

static const DWORD TexBlendMode[5] =
{
	MEX2_ADD, MEX2_ALPHAKEY, MEX2_BLEND, MEX2_MODULATE, MEX2_MODULATE2X
};

static const char * BindPartName[5] =
{
	"", "LeftHand", "RightHand", "LeftBack", "RightBack"
};

BEGIN_EVENT_TABLE(RightWindow, wxWindow)
	EVT_PG_CHANGED(IDC_MODEL_INFO_PG, RightWindow::OnModelInfoPropertyGridChange)
	EVT_PG_CHANGED(IDC_PARTICLE_EDIT_PG, RightWindow::OnParticleEditPropertyGridChange)

	EVT_CHOICE(IDC_RIGHT_WND_PARTICLES_CHOICE, RightWindow::OnParticleEmitterChoice)
	EVT_BUTTON(IDC_RIGHT_WND_PART_EMITTER_EXPORT_BTN, RightWindow::OnParticleEmitterParamExport)

	EVT_TREE_BEGIN_LABEL_EDIT(IDC_MODEL_INFO_MEXCONF_TREE, RightWindow::OnMexConfigTreeBeginLabelEdit)
	EVT_TREE_END_LABEL_EDIT(IDC_MODEL_INFO_MEXCONF_TREE, RightWindow::OnMexConfigTreeEndLabelEdit)
	EVT_TREE_ITEM_RIGHT_CLICK(IDC_MODEL_INFO_MEXCONF_TREE, RightWindow::OnMexConfigTreeRightClick)
	EVT_TREE_ITEM_ACTIVATED(IDC_MODEL_INFO_MEXCONF_TREE, RightWindow::OnMexConfigTreeDoubleClick)

	EVT_MENU(IDC_MODEL_INFO_ADD_SKIN, RightWindow::OnMenuItemAddSkin)
	EVT_MENU(IDC_MODEL_INFO_SKIN_RENAME, RightWindow::OnMenuItemSkinRename)
	EVT_MENU(IDC_MODEL_INFO_DEL_SKIN, RightWindow::OnMenuItemDelSkin)

	EVT_SIZE(RightWindow::OnSize)
END_EVENT_TABLE()

RightWindow::RightWindow(wxWindow *parent, wxWindowID id, const wxPoint &pos, const wxSize &size)
	: wxWindow(parent, id, pos, size)
{
	mCurChildType = ChildWnd_ModelInfo;

	this->CreateModelInfoChildWnds();
	mAnimationWnd = new AnimationWindow(this, wxID_ANY, wxPoint(0, 0), size);
	this->CreateParticleEditChildWnds();
	mAvatarWnd = new AvatarWindow(this, wxID_ANY, wxPoint(0, 0), size);

	m_ModeConfigWnd = new ModelConfigWindow(this,wxID_ANY,wxPoint(0,0),size);
}

RightWindow::~RightWindow()
{

}

void RightWindow::HideAllChildren()
{
	mModelInfoPG->Hide();
	mMexConfigTree->Hide();

	mAnimationWnd->Hide();

	mParticleEmitterChoiceLabel->Hide();
	mParticleEmitterChoice->Hide();
	mPartEmitterExportBtn->Hide();
	mPartEmitterEditPG->Hide();

	mAvatarWnd->Hide();
	m_ModeConfigWnd->Hide();
}

void RightWindow::ShowChildByType(ChildWndType type)
{
	this->HideAllChildren();

	// ��ʾChild����
	switch (type)
	{
	case ChildWnd_ModelInfo:
		{
			mModelInfoPG->Show();
			mMexConfigTree->Show();
		}
		break;

	case ChildWnd_Animation:
		mAnimationWnd->Show();
		break;

	case ChildWnd_PartEdit:
		{
			mParticleEmitterChoiceLabel->Show();
			mParticleEmitterChoice->Show();
			mPartEmitterExportBtn->Show();
			mPartEmitterEditPG->Show();
		}
		break;

	case ChildWnd_Avatar:
		mAvatarWnd->Show();
		break;
	case ChildWnd_ModelConfig:
		m_ModeConfigWnd->Show();
		break;
	}
	mCurChildType = type;

	// ����Child��������
	UpdateInfoByChildType(type);
}

void RightWindow::UpdateInfoByChildType(ChildWndType type)
{
	ModelObj *obj = gMainFrame->GetCurrentModel();
	if (obj == NULL)
		return;

	IMex *mex = obj->model->GetMex();
	if (mex == NULL)
		return;

	switch (type)
	{
	case ChildWnd_ModelInfo:
		{
			MexCfg *mexCfg = obj->model->GetMexCfg();
			if (mexCfg == NULL)
				break;

			// ������Ϣ
			mModelInfoPG->GetPropertyByLabel(wxT("�汾"))->SetValueFromInt(mex->GetVersion());
			mModelInfoPG->GetPropertyByLabel(wxT("������"))->SetValueFromInt(mex->GetVertexCount());
			mModelInfoPG->GetPropertyByLabel(wxT("����"))->SetValueFromInt(mex->GetFaceCount());
			mModelInfoPG->GetPropertyByLabel(wxT("������"))->SetValueFromInt(mex->GetSkeleton()->GetBoneCount());
			mModelInfoPG->GetPropertyByLabel(wxT("֡��"))->SetValueFromInt(obj->model->GetFrameCount());
			mModelInfoPG->GetPropertyByLabel(wxT("��ͼ��"))->SetValueFromInt(mex->GetTextures()->GetTextureCount());

			IMexParticleEmitters *part_emitters = mex->GetParticleEmitters();
			mModelInfoPG->GetPropertyByLabel(wxT("���ӷ�����"))->SetValueFromInt(part_emitters != NULL ? part_emitters->GetEmitterCount() : 0);

			IMexRibbonEmitters *ribbon_emitters = mex->GetRibbonEmitters();
			mModelInfoPG->GetPropertyByLabel(wxT("����������"))->SetValueFromInt(ribbon_emitters != NULL ? ribbon_emitters->GetEmitterCount() : 0);

			DWORD fileSizeInBytes = mexCfg->GetFileSize();
			wxString fileSizeInM;
			if (fileSizeInBytes < MEXVIEWER_FILESIZE_1K)
				fileSizeInM = wxString::Format(wxT("%d B"), fileSizeInBytes);
			else if (fileSizeInBytes < MEXVIEWER_FILESIZE_1M)
				fileSizeInM = wxString::Format(wxT("%.2f KB"), fileSizeInBytes * 0.001f);
			else
				fileSizeInM = wxString::Format(wxT("%.2f MB"), fileSizeInBytes * 0.000001f);
			mModelInfoPG->GetPropertyByLabel(wxT("�ļ���С"))->SetValueFromString(fileSizeInM);

			// ��С����ת�����ſ���
			D3DXVECTOR3 scale;
			obj->model->GetScaleXYZ(scale.x, scale.y, scale.z);
			mModelInfoPG->SetPropertyValue(wxT("����"), scale.x);

			D3DXVECTOR3 roration;
			obj->model->GetRotation(roration.x, roration.y, roration.z);
			mModelInfoPG->SetPropertyValue(wxT("��תX"), (int) roration.x);
			mModelInfoPG->SetPropertyValue(wxT("��תY"), (int) roration.y);
			mModelInfoPG->SetPropertyValue(wxT("��תZ"), (int) roration.z);
			mSkinTexCat->DeleteChildren();
			mModelInfoPG->Refresh();

			// MexConfig
			{
				mMexConfigTree->SetItemText(mMexConfigTreeItems[ModelScale],
					wxString::Format(wxT("ModelScale: %d"), mexCfg->m_mdlScale.m_npScale.GetNumber()));
				mMexConfigTree->SetItemText(mMexConfigTreeItems[BodyRadius],
					wxString::Format(wxT("BodyRadius: %d"), mexCfg->m_BodyRadius.m_npRadius.GetNumber()));

				// SoundEffect
				mMexConfigTree->SetItemText(mMexConfigTreeItems[SoundFilename],
					wxString::Format(wxT("SoundFilename: %s"), mexCfg->m_soundEffect.m_spSoundFilename.GetString()));
				mMexConfigTree->SetItemText(mMexConfigTreeItems[Range],
					wxString::Format(wxT("Range: %d"), mexCfg->m_soundEffect.m_npRange.GetNumber()));
				mMexConfigTree->SetItemText(mMexConfigTreeItems[Loop],
					wxString::Format(wxT("Loop: %d"), mexCfg->m_soundEffect.m_npLoopFlag.GetNumber()));
				mMexConfigTree->SetItemText(mMexConfigTreeItems[Frequence],
					wxString::Format(wxT("Frequence: %d"), mexCfg->m_soundEffect.m_npFrequence.GetNumber()));
				mMexConfigTree->SetItemText(mMexConfigTreeItems[Intensity],
					wxString::Format(wxT("Intensity: %d"), mexCfg->m_soundEffect.m_npIntensity.GetNumber()));

				// BoundingObject
				mMexConfigTree->SetItemText(mMexConfigTreeItems[Width],
					wxString::Format(wxT("Width: %d"), mexCfg->m_BObj.m_npBBoxWidth.GetNumber()));
				mMexConfigTree->SetItemText(mMexConfigTreeItems[Height],
					wxString::Format(wxT("Height: %d"), mexCfg->m_BObj.m_npBBoxHeight.GetNumber()));
				mMexConfigTree->SetItemText(mMexConfigTreeItems[Length],
					wxString::Format(wxT("Length: %d"), mexCfg->m_BObj.m_npBBoxLength.GetNumber()));
				mMexConfigTree->SetItemText(mMexConfigTreeItems[Lift],
					wxString::Format(wxT("Lift: %d"), mexCfg->m_BObj.m_npBBoxLift.GetNumber()));

				// AvatarSetting(Skin)
				mMexConfigTree->DeleteChildren(mMexConfigTreeItems[Skin]);
				for (int i = 0; i < mexCfg->m_AvatarSettings.m_vectorSetting.size(); ++i)
				{
					wxString settingName = mexCfg->m_AvatarSettings.m_vectorSetting[i]->m_spName.GetString();
					mMexConfigTree->AppendItem(mMexConfigTreeItems[Skin], settingName);
				}
				mMexConfigTree->Expand(mMexConfigTreeItems[Skin]);
			}
		}
		break;

	case ChildWnd_Animation:
		{
			mAnimationWnd->UpdateAnimationList();
		}
		break;

	case ChildWnd_PartEdit:
		{
			ModelObj *obj = gMainFrame->GetCurrentModel();
			if (obj == NULL)
				break;

			IMex *mex = obj->model->GetMex();
			if (mex == NULL)
				break;

			int oldSel = mParticleEmitterChoice->GetSelection();
			mParticleEmitterChoice->Clear();
			if (mex->GetParticleEmitters() == NULL || mex->GetParticleEmitters()->GetEmitterCount() < 1)
			{
				return;
			}

			for (int i = 0; i < mex->GetParticleEmitters()->GetEmitterCount(); ++i)
			{
				Mex2ParticleEmitter *e = (Mex2ParticleEmitter *) mex->GetParticleEmitters()->GetEmitter(i);
				if (e != NULL)
				{
					mParticleEmitterChoice->AppendString(e->GetSetting()->szName);
				}
			}

			if (oldSel < mex->GetParticleEmitters()->GetEmitterCount())
				mParticleEmitterChoice->SetSelection(oldSel);
			else
				mParticleEmitterChoice->SetSelection(-1);
		}
		break;

	case ChildWnd_Avatar:
		{
			
		}
	case ChildWnd_ModelConfig:
		{

		}
		break;
	}
}

void RightWindow::UpdateModelInfoRotation()
{
	ModelObj *obj = gMainFrame->GetCurrentModel();
	if (obj == NULL)
		return;

	D3DXVECTOR3 roration;
	obj->model->GetRotation(roration.x, roration.y, roration.z);
	mModelInfoPG->SetPropertyValue(wxT("��תX"), (int) D3DXToDegree(roration.x));
	mModelInfoPG->SetPropertyValue(wxT("��תY"), (int) D3DXToDegree(roration.y));
	mModelInfoPG->SetPropertyValue(wxT("��תZ"), (int) D3DXToDegree(roration.z));
}

int RightWindow::GetCurrentParticleEmitter()
{
	return mParticleEmitterChoice->GetSelection();
}

bool RightWindow::SaveCurrentParticleEmitterParams()
{
	// ���浱ǰ���ӷ���������
	ModelObj *obj = gMainFrame->GetCurrentModel();
	if (obj == NULL)
		return false;

	IMex *mex = obj->model->GetMex();
	if (mex == NULL)
		return false;

	if (mex->GetParticleEmitters() == NULL
		|| mex->GetParticleEmitters()->GetEmitterCount() < 1
		|| this->GetCurrentParticleEmitter() == -1)
	{
		wxMessageBox("��ģ��û�����ӷ���������δѡ���κ����ӷ�����");
		return false;
	}

	Mex2ParticleEmitter *e = (Mex2ParticleEmitter *) mex->GetParticleEmitters()->GetEmitter(this->GetCurrentParticleEmitter());
	bool tempBool = false;
	int selection = -1;
	wxColour tempClr = *wxWHITE;

	mAutoDeskObjProps.Reset();

	// ������ѡ��
	{
		e->GetSetting()->nCount = mPartEmitterEditPG->GetPropertyValueAsInt(wxT("����"));
		mAutoDeskObjProps.AddPropertyForExport("Count", e->GetSetting()->nCount);

		e->GetSetting()->fSpeed = mPartEmitterEditPG->GetPropertyValueAsDouble(wxT("�ٶ�"));
		mAutoDeskObjProps.AddPropertyForExport("Speed", e->GetSetting()->fSpeed);

		e->GetSetting()->fVariation = mPartEmitterEditPG->GetPropertyValueAsDouble(wxT("�ٶ������"));
		mAutoDeskObjProps.AddPropertyForExport("Variation", e->GetSetting()->fVariation);

		e->GetSetting()->fConeAngle = mPartEmitterEditPG->GetPropertyValueAsDouble(wxT("����н�"));
		mAutoDeskObjProps.AddPropertyForExport("ConeAngle", e->GetSetting()->fConeAngle);

		e->GetSetting()->fGravity = mPartEmitterEditPG->GetPropertyValueAsDouble(wxT("����"));
		mAutoDeskObjProps.AddPropertyForExport("Gravity", e->GetSetting()->fGravity);
	}

	// ʱ��ѡ��
	{
		e->GetSetting()->fLifeSpan = mPartEmitterEditPG->GetPropertyValueAsDouble(wxT("��������"));
		mAutoDeskObjProps.AddPropertyForExport("Life", e->GetSetting()->fLifeSpan);

		e->GetSetting()->fEmissionRate = mPartEmitterEditPG->GetPropertyValueAsDouble(wxT("ÿ�뷢������"));
		mAutoDeskObjProps.AddPropertyForExport("Parts", e->GetSetting()->fEmissionRate);

		tempBool = mPartEmitterEditPG->GetPropertyValueAsBool(wxT("ȫ���緢"));
		mAutoDeskObjProps.AddPropertyForExport("Squirt", tempBool);
		if (tempBool)
			e->GetSetting()->dwFlag |= MEX2_PARTICLE_EMITTER_SQUIRT;
		else
			e->GetSetting()->dwFlag &= ~MEX2_PARTICLE_EMITTER_SQUIRT;
	}

	// ����ƽ��ѡ��
	{
		e->GetSetting()->fWidth = mPartEmitterEditPG->GetPropertyValueAsDouble(wxT("ƽ���"));
		mAutoDeskObjProps.AddPropertyForExport("Width", e->GetSetting()->fWidth);

		e->GetSetting()->fHeight = mPartEmitterEditPG->GetPropertyValueAsDouble(wxT("ƽ���"));
		mAutoDeskObjProps.AddPropertyForExport("fHeight", e->GetSetting()->fHeight);
	}

	// ����ѡ��
	{
		selection = mPartEmitterEditPG->GetProperty(wxT("��������"))->GetChoiceSelection();
		e->GetSetting()->dwPart = ParticleTypes[selection];
		if (selection == 0)
			mAutoDeskObjProps.AddPropertyForExport("ParticlePart", "Head");
		else if (selection == 1)
			mAutoDeskObjProps.AddPropertyForExport("ParticlePart", "Tail");
		else
			mAutoDeskObjProps.AddPropertyForExport("ParticlePart", "Both");

		e->GetSetting()->fTailLength = mPartEmitterEditPG->GetPropertyValueAsDouble(wxT("��β����"));
		mAutoDeskObjProps.AddPropertyForExport("TailLength", e->GetSetting()->fTailLength);

		e->UseTimeBasedCell() = mPartEmitterEditPG->GetPropertyValueAsBool(wxT("ʱ������֡"));
		mAutoDeskObjProps.AddPropertyForExport("UseTimeBasedCell", e->UseTimeBasedCell());

		e->GetSetting()->dwUVAnimFps = mPartEmitterEditPG->GetPropertyValueAsInt(wxT("����֡FPS"));
		mAutoDeskObjProps.AddPropertyForExport("UVAnimFps", e->GetSetting()->dwUVAnimFps);

		e->TimeBasedCellLoopTimes() = mPartEmitterEditPG->GetPropertyValueAsInt(wxT("����֡ѭ������"));
		mAutoDeskObjProps.AddPropertyForExport("SeqLoopTimes", e->TimeBasedCellLoopTimes());

		e->GetSetting()->fMiddleTime = mPartEmitterEditPG->GetPropertyValueAsDouble(wxT("ʱ��仯.Middle"));
		mAutoDeskObjProps.AddPropertyForExport("Middle", e->GetSetting()->fMiddleTime);
		{
			tempClr = wxANY_AS(mPartEmitterEditPG->GetPropertyValue(wxT("��ɫ�仯.Start")).GetAny(), wxColour);
			e->GetSetting()->nSegmentColor[0][0] = tempClr.Red();
			e->GetSetting()->nSegmentColor[0][1] = tempClr.Green();
			e->GetSetting()->nSegmentColor[0][2] = tempClr.Blue();
			mAutoDeskObjProps.AddPropertyForExport("ColorStart", tempClr);

			tempClr = wxANY_AS(mPartEmitterEditPG->GetPropertyValue(wxT("��ɫ�仯.Middle")).GetAny(), wxColour);
			e->GetSetting()->nSegmentColor[1][0] = tempClr.Red();
			e->GetSetting()->nSegmentColor[1][1] = tempClr.Green();
			e->GetSetting()->nSegmentColor[1][2] = tempClr.Blue();
			mAutoDeskObjProps.AddPropertyForExport("ColorMiddle", tempClr);

			tempClr = wxANY_AS(mPartEmitterEditPG->GetPropertyValue(wxT("��ɫ�仯.End")).GetAny(), wxColour);
			e->GetSetting()->nSegmentColor[2][0] = tempClr.Red();
			e->GetSetting()->nSegmentColor[2][1] = tempClr.Green();
			e->GetSetting()->nSegmentColor[2][2] = tempClr.Blue();
			mAutoDeskObjProps.AddPropertyForExport("ColorEnd", tempClr);
		}
		e->GetSetting()->nAlpha[0] = mPartEmitterEditPG->GetPropertyValueAsInt(wxT("Alpha�仯.Start"));
		e->GetSetting()->nAlpha[1] = mPartEmitterEditPG->GetPropertyValueAsInt(wxT("Alpha�仯.Middle"));
		e->GetSetting()->nAlpha[2] = mPartEmitterEditPG->GetPropertyValueAsInt(wxT("Alpha�仯.End"));
		mAutoDeskObjProps.AddPropertyForExport("AlphaStart", e->GetSetting()->nAlpha[0]);
		mAutoDeskObjProps.AddPropertyForExport("AlphaMiddle", e->GetSetting()->nAlpha[1]);
		mAutoDeskObjProps.AddPropertyForExport("AlphaEnd", e->GetSetting()->nAlpha[2]);

		e->GetSetting()->fParticleScaling[0] = mPartEmitterEditPG->GetPropertyValueAsDouble(wxT("��С�仯.Start"));
		e->GetSetting()->fParticleScaling[1] = mPartEmitterEditPG->GetPropertyValueAsDouble(wxT("��С�仯.Middle"));
		e->GetSetting()->fParticleScaling[2] = mPartEmitterEditPG->GetPropertyValueAsDouble(wxT("��С�仯.End"));
		mAutoDeskObjProps.AddPropertyForExport("ScaleStart", e->GetSetting()->fParticleScaling[0]);
		mAutoDeskObjProps.AddPropertyForExport("ScaleMiddle", e->GetSetting()->fParticleScaling[1]);
		mAutoDeskObjProps.AddPropertyForExport("ScaleEnd", e->GetSetting()->fParticleScaling[2]);
		
		e->GetSetting()->dwLifeSpanHeadUVAnim[0] = mPartEmitterEditPG->GetPropertyValueAsInt(wxT("LifeSpan Head UV Anim.Start"));
		e->GetSetting()->dwLifeSpanHeadUVAnim[1] = mPartEmitterEditPG->GetPropertyValueAsInt(wxT("LifeSpan Head UV Anim.Middle"));
		e->GetSetting()->dwLifeSpanHeadUVAnim[2] = mPartEmitterEditPG->GetPropertyValueAsInt(wxT("LifeSpan Head UV Anim.Repeat"));
		mAutoDeskObjProps.AddPropertyForExport("LifeSpanHeadUVAnimStart", e->GetSetting()->dwLifeSpanHeadUVAnim[0]);
		mAutoDeskObjProps.AddPropertyForExport("LifeSpanHeadUVAnimEnd", e->GetSetting()->dwLifeSpanHeadUVAnim[1]);
		mAutoDeskObjProps.AddPropertyForExport("LifeSpanHeadUVAnimRepeat", e->GetSetting()->dwLifeSpanHeadUVAnim[2]);

		e->GetSetting()->dwDecayHeadUVAnim[0] = mPartEmitterEditPG->GetPropertyValueAsInt(wxT("Decay Head UV Anim.Start"));
		e->GetSetting()->dwDecayHeadUVAnim[1] = mPartEmitterEditPG->GetPropertyValueAsInt(wxT("Decay Head UV Anim.Middle"));
		e->GetSetting()->dwDecayHeadUVAnim[2] = mPartEmitterEditPG->GetPropertyValueAsInt(wxT("Decay Head UV Anim.Repeat"));
		mAutoDeskObjProps.AddPropertyForExport("DecayHeadUVAnimStart", e->GetSetting()->dwDecayHeadUVAnim[0]);
		mAutoDeskObjProps.AddPropertyForExport("DecayHeadUVAnimEnd", e->GetSetting()->dwDecayHeadUVAnim[1]);
		mAutoDeskObjProps.AddPropertyForExport("DecayHeadUVAnimRepeat", e->GetSetting()->dwDecayHeadUVAnim[2]);

		e->GetSetting()->dwLifeSpanTailUVAnim[0] = mPartEmitterEditPG->GetPropertyValueAsInt(wxT("LifeSpan Tail UV Anim.Start"));
		e->GetSetting()->dwLifeSpanTailUVAnim[1] = mPartEmitterEditPG->GetPropertyValueAsInt(wxT("LifeSpan Tail UV Anim.Middle"));
		e->GetSetting()->dwLifeSpanTailUVAnim[2] = mPartEmitterEditPG->GetPropertyValueAsInt(wxT("LifeSpan Tail UV Anim.Repeat"));
		mAutoDeskObjProps.AddPropertyForExport("LifeSpanTailUVAnimStart", e->GetSetting()->dwLifeSpanTailUVAnim[0]);
		mAutoDeskObjProps.AddPropertyForExport("LifeSpanTailUVAnimEnd", e->GetSetting()->dwLifeSpanTailUVAnim[1]);
		mAutoDeskObjProps.AddPropertyForExport("LifeSpanTailUVAnimRepeat", e->GetSetting()->dwLifeSpanTailUVAnim[2]);

		e->GetSetting()->dwDecayTailUVAnim[0] = mPartEmitterEditPG->GetPropertyValueAsInt(wxT("Decay Tail UV Anim.Start"));
		e->GetSetting()->dwDecayTailUVAnim[1] = mPartEmitterEditPG->GetPropertyValueAsInt(wxT("Decay Tail UV Anim.Middle"));
		e->GetSetting()->dwDecayTailUVAnim[2] = mPartEmitterEditPG->GetPropertyValueAsInt(wxT("Decay Tail UV Anim.Repeat"));
		mAutoDeskObjProps.AddPropertyForExport("DecayTailUVAnimStart", e->GetSetting()->dwDecayTailUVAnim[0]);
		mAutoDeskObjProps.AddPropertyForExport("DecayTailUVAnimEnd", e->GetSetting()->dwDecayTailUVAnim[1]);
		mAutoDeskObjProps.AddPropertyForExport("DecayTailUVAnimRepeat", e->GetSetting()->dwDecayTailUVAnim[2]);
	}

	// ��ͼѡ��
	{
		selection = mPartEmitterEditPG->GetProperty(wxT("���ѡ��"))->GetChoiceSelection();
		e->GetSetting()->dwBlendMode = TexBlendMode[selection];
		switch (selection)
		{
		case 0:
			mAutoDeskObjProps.AddPropertyForExport("BlendMode", "Add"); break;
		case 1:
			mAutoDeskObjProps.AddPropertyForExport("BlendMode", "AlphaKey"); break;
		case 2:
			mAutoDeskObjProps.AddPropertyForExport("BlendMode", "Blend"); break;
		case 3:
			mAutoDeskObjProps.AddPropertyForExport("BlendMode", "Modulate"); break;
		case 4:
			mAutoDeskObjProps.AddPropertyForExport("BlendMode", "Mod2X"); break;
		}

		wxString texFullPath = mPartEmitterEditPG->GetPropertyValueAsString(wxT("������ͼ"));
		if (!texFullPath.empty())
		{
			if (mex->GetTextures() != NULL)
			{
				int texId = e->GetSetting()->nTextureId;
				if (texId <= mex->GetTextures()->GetTextureCount() - 1)
				{
					// ȥ��·��, ֻ���ļ���
					wxFileName fn(texFullPath.c_str());					
					wxString texFile = fn.GetName() + wxT(".") + fn.GetExt();
					mex->GetTextures()->GetTexture(texId)->SetName(texFile.mb_str());
				}
				mAutoDeskObjProps.AddPropertyForExport("TextureFilename", texFullPath.mb_str());
			}
		}
		e->GetSetting()->nCol = mPartEmitterEditPG->GetPropertyValueAsInt(wxT("Col(����)"));
		mAutoDeskObjProps.AddPropertyForExport("Col", e->GetSetting()->nCol);

		e->GetSetting()->nRow = mPartEmitterEditPG->GetPropertyValueAsInt(wxT("Row(����)"));
		mAutoDeskObjProps.AddPropertyForExport("Row", e->GetSetting()->nRow);
	}

	// ����ѡ��
	{
		/*tempBool = mPartEmitterEditPG->GetPropertyValueAsBool(wxT("���ݾ�������"));
		if (tempBool)
			e->GetSetting()->dwFlag |= MEX2_SORTBYFARZ;
		else
			e->GetSetting()->dwFlag &= ~MEX2_SORTBYFARZ;*/

		// ����ѡ��
		tempBool = mPartEmitterEditPG->GetPropertyValueAsBool(wxT("��ģ�Ϳռ��˶�"));
		if (tempBool)
			e->GetSetting()->dwFlag |= MEX2_PARTICLE_EMITTER_PARTICLEINMODELSPACE;
		else
			e->GetSetting()->dwFlag &= ~MEX2_PARTICLE_EMITTER_PARTICLEINMODELSPACE;
		mAutoDeskObjProps.AddPropertyForExport("ParticlesInModelSpace", tempBool);

		tempBool = mPartEmitterEditPG->GetPropertyValueAsBool(wxT("����������"));
		if (tempBool)
			e->GetSetting()->dwFlag |= MEX2_PARTICLE_EMITTER_LOCKEMITTER;
		else
			e->GetSetting()->dwFlag &= ~MEX2_PARTICLE_EMITTER_LOCKEMITTER;
		mAutoDeskObjProps.AddPropertyForExport("LockEmitter", tempBool);

		tempBool = mPartEmitterEditPG->GetPropertyValueAsBool(wxT("����XYƽ��"));
		if (tempBool)
			e->GetSetting()->dwFlag |= MEX2_PARTICLE_EMITTER_XYQUAD;
		else
			e->GetSetting()->dwFlag &= ~MEX2_PARTICLE_EMITTER_XYQUAD;
		mAutoDeskObjProps.AddPropertyForExport("XYQuad", tempBool);

		e->RotateParticle() = mPartEmitterEditPG->GetPropertyValueAsBool(wxT("��ת����"));
		mAutoDeskObjProps.AddPropertyForExport("Rotate", e->RotateParticle());

		e->Rotate360DegreeCostTime() = mPartEmitterEditPG->GetPropertyValueAsInt(wxT("��ת360����ʱ"));
		mAutoDeskObjProps.AddPropertyForExport("RotateCost", e->Rotate360DegreeCostTime());

		e->RandomDir() = mPartEmitterEditPG->GetPropertyValueAsBool(wxT("�������"));
		mAutoDeskObjProps.AddPropertyForExport("RandomDir", e->RandomDir());

		e->RotNotFollowEmitter() = !mPartEmitterEditPG->GetPropertyValueAsBool(wxT("���淢�����任"));
		mAutoDeskObjProps.AddPropertyForExport("FollowEmitter", !e->RotNotFollowEmitter());

		int pos = mPartEmitterEditPG->GetProperty(wxT("�󶨲�λ"))->GetChoiceSelection();
		e->SetBindPartName(BindPartName[pos]);
		mAutoDeskObjProps.AddPropertyForExport("BindPartName", BindPartName[pos]);
	}

	// ����ѡ��
	{
		e->GetSetting()->fLifeSpanMax = mPartEmitterEditPG->GetPropertyValueAsDouble(wxT("����������ֵ"));
		mAutoDeskObjProps.AddPropertyForExport("LifeMax", e->GetSetting()->fLifeSpanMax);

		e->GetSetting()->fScaleRateMin = mPartEmitterEditPG->GetPropertyValueAsDouble(wxT("��С�����Сֵ"));
		mAutoDeskObjProps.AddPropertyForExport("ScaleMin", e->GetSetting()->fScaleRateMin);

		e->GetSetting()->fScaleRateMax = mPartEmitterEditPG->GetPropertyValueAsDouble(wxT("��С������ֵ"));
		mAutoDeskObjProps.AddPropertyForExport("ScaleMax", e->GetSetting()->fScaleRateMax);

		e->GetSetting()->bContraryColor = mPartEmitterEditPG->GetPropertyValueAsBool(wxT("����ɫȡ��"));
		mAutoDeskObjProps.AddPropertyForExport("VertexColorInv", e->GetSetting()->bContraryColor);

		e->GetSetting()->bAngleChangeByCone = mPartEmitterEditPG->GetPropertyValueAsBool(wxT("�淢�䷽����ת"));
		mAutoDeskObjProps.AddPropertyForExport("RotateFollowDir", e->GetSetting()->bAngleChangeByCone);

		e->GetSetting()->bTailLengthChange = mPartEmitterEditPG->GetPropertyValueAsBool(wxT("��β���ȱ仯"));
		mAutoDeskObjProps.AddPropertyForExport("TailChange", e->GetSetting()->bAngleChangeByCone);

		e->GetSetting()->fTailLengthChange[0] = mPartEmitterEditPG->GetPropertyValueAsDouble(wxT("��β���ȱ仯��ֵ.Start"));
		e->GetSetting()->fTailLengthChange[1] = mPartEmitterEditPG->GetPropertyValueAsDouble(wxT("��β���ȱ仯��ֵ.Middle"));
		e->GetSetting()->fTailLengthChange[2] = mPartEmitterEditPG->GetPropertyValueAsDouble(wxT("��β���ȱ仯��ֵ.End"));
		mAutoDeskObjProps.AddPropertyForExport("TailChangeStart", e->GetSetting()->fTailLengthChange[0]);
		mAutoDeskObjProps.AddPropertyForExport("TailChangeMiddle", e->GetSetting()->fTailLengthChange[1]);
		mAutoDeskObjProps.AddPropertyForExport("TailChangeEnd", e->GetSetting()->fTailLengthChange[2]);

		e->UVRandomFirstCell() = mPartEmitterEditPG->GetPropertyValueAsBool(wxT("UV������1֡���"));
		mAutoDeskObjProps.AddPropertyForExport("RandomFirstCell", e->UVRandomFirstCell());

		e->XYQuadLaydownInWorld() = mPartEmitterEditPG->GetPropertyValueAsBool(wxT("XYQuad�������з�ƽ"));
		mAutoDeskObjProps.AddPropertyForExport("LaydownInWorld", e->XYQuadLaydownInWorld());
	}
	return true;
}

void RightWindow::CreateModelInfoChildWnds()
{
	mModelInfoPG = new wxPropertyGrid(this, IDC_MODEL_INFO_PG, wxPoint(0, 0),
		GetClientSize(), wxPG_BOLD_MODIFIED, wxT("ģ����ϢPG"));
	mModelInfoPG->SetExtraStyle(wxPG_EX_MODE_BUTTONS);

	mBasicInfoCat = new wxPropertyCategory(wxT("������Ϣ"), wxT("BasicInfoCategory"));
	mBasicInfoCat->SetExpanded(true);
	mModelInfoPG->Append(mBasicInfoCat);
	{
		mBasicInfoCat->AppendChild(new wxIntProperty(wxT("�汾"), wxPG_LABEL, 105))->Enable(false);
		mBasicInfoCat->AppendChild(new wxIntProperty(wxT("������"), wxPG_LABEL, 8875))->Enable(false);
		mBasicInfoCat->AppendChild(new wxIntProperty(wxT("����"), wxPG_LABEL, 12563))->Enable(false);
		mBasicInfoCat->AppendChild(new wxIntProperty(wxT("֡��"), wxPG_LABEL, 820))->Enable(false);
		mBasicInfoCat->AppendChild(new wxIntProperty(wxT("������"), wxPG_LABEL, 36))->Enable(false);
		mBasicInfoCat->AppendChild(new wxIntProperty(wxT("��ͼ��"), wxPG_LABEL, 36))->Enable(false);
		mBasicInfoCat->AppendChild(new wxIntProperty(wxT("���ӷ�����"), wxPG_LABEL, 0))->Enable(false);
		mBasicInfoCat->AppendChild(new wxIntProperty(wxT("����������"), wxPG_LABEL, 0))->Enable(false);
		mBasicInfoCat->AppendChild(new wxStringProperty(wxT("�ļ���С"), wxPG_LABEL, wxT("0M")))->Enable(false);
	}

	mControlCat = new wxPropertyCategory(wxT("����"), wxT("ControlCategory"));
	mControlCat->SetExpanded(true);
	mModelInfoPG->Append(mControlCat);
	{
		mControlCat->AppendChild(new wxFloatProperty(wxT("����"), wxPG_LABEL, 1.0));
		Utility_SetPropertyToSpinCtrl(mModelInfoPG, wxT("����"), 0.1, 1000, 1, true);

		mControlCat->AppendChild(new wxIntProperty(wxT("��תX"), wxPG_LABEL, 0));
		Utility_SetPropertyToSpinCtrl(mModelInfoPG, wxT("��תX"), -100000, 100000, 10, true);

		mControlCat->AppendChild(new wxIntProperty(wxT("��תY"), wxPG_LABEL, 0));
		Utility_SetPropertyToSpinCtrl(mModelInfoPG, wxT("��תY"), -100000, 100000, 10, true);

		mControlCat->AppendChild(new wxIntProperty(wxT("��תZ"), wxPG_LABEL, 0));
		Utility_SetPropertyToSpinCtrl(mModelInfoPG, wxT("��תZ"), -100000, 100000, 10, true);
	}

	mSkinTexCat = new wxPropertyCategory(wxT("Skin��ͼ"), wxT("SkinTexCategory"));
	mModelInfoPG->Append(mSkinTexCat);

	mMexConfigTree = new wxTreeCtrl(this, IDC_MODEL_INFO_MEXCONF_TREE, wxDefaultPosition, wxDefaultSize,
		wxTR_DEFAULT_STYLE | wxTR_SINGLE | wxTR_ROW_LINES | wxTR_EDIT_LABELS | wxVSCROLL);
	wxTreeItemId root = mMexConfigTree->AddRoot(wxT("MexConfig"));

	mMexConfigTreeItems[ModelScale] = mMexConfigTree->AppendItem(root, wxT("ModelScale:1"));
	mMexConfigTreeItems[BodyRadius] = mMexConfigTree->AppendItem(root, wxT("BodyRadius:1"));

	wxTreeItemId tempId = mMexConfigTree->AppendItem(root, wxT("SoundEffect"));
	{
		mMexConfigTreeItems[SoundFilename] = mMexConfigTree->AppendItem(tempId, wxT("SoundFilename:"));
		mMexConfigTreeItems[Range] = mMexConfigTree->AppendItem(tempId, wxT("Range: 0"));
		mMexConfigTreeItems[Loop] = mMexConfigTree->AppendItem(tempId, wxT("Loop: 0"));
		mMexConfigTreeItems[Frequence] = mMexConfigTree->AppendItem(tempId, wxT("Frequence: 0"));
		mMexConfigTreeItems[Intensity] = mMexConfigTree->AppendItem(tempId, wxT("Intensity: 0"));
		mMexConfigTree->Collapse(tempId);
	}

	tempId = mMexConfigTree->AppendItem(root, wxT("BoundingObject"));
	{
		mMexConfigTreeItems[Width] = mMexConfigTree->AppendItem(tempId, wxT("Width:"));
		mMexConfigTreeItems[Height] = mMexConfigTree->AppendItem(tempId, wxT("Height:"));
		mMexConfigTreeItems[Length] = mMexConfigTree->AppendItem(tempId, wxT("Length:"));
		mMexConfigTreeItems[Lift] = mMexConfigTree->AppendItem(tempId, wxT("Lift:"));
		mMexConfigTree->Collapse(tempId);
	}

	mMexConfigTreeItems[Skin] = mMexConfigTree->AppendItem(root, wxT("AvatarSetting"));
	mMexConfigTree->Expand(root);

	mAddSkinMenu = new wxMenu;
	mAddSkinMenu->Append(IDC_MODEL_INFO_ADD_SKIN, wxT("���Skin"));

	mSkinEditMenu = new wxMenu;
	mSkinEditMenu->Append(IDC_MODEL_INFO_SKIN_RENAME, wxT("������"));
	mSkinEditMenu->AppendSeparator();
	mSkinEditMenu->Append(IDC_MODEL_INFO_DEL_SKIN, wxT("ɾ��"));
}

void RightWindow::CreateParticleEditChildWnds()
{
	mParticleEmitterChoiceLabel = new wxStaticText(this, wxID_ANY, wxT("���ӷ�����:"));
	mParticleEmitterChoice = new wxChoice(this, IDC_RIGHT_WND_PARTICLES_CHOICE);
	mPartEmitterExportBtn = new wxButton(this, IDC_RIGHT_WND_PART_EMITTER_EXPORT_BTN, wxT("����"));

	mPartEmitterEditPG = new wxPropertyGrid(this, IDC_PARTICLE_EDIT_PG,
		wxDefaultPosition, wxDefaultSize, wxPG_BOLD_MODIFIED | wxPG_SPLITTER_AUTO_CENTER, wxT("���ӱ༭PG"));
	mPartEmitterEditPG->SetExtraStyle(wxPG_EX_MODE_BUTTONS);
	mPartEmitterEditPG->Enable(false);

	mEmitterCat = new wxPropertyCategory(wxT("������ѡ��"), wxT("BasicInfoCategory"));
	mEmitterCat->SetExpanded(true);
	mPartEmitterEditPG->Append(mEmitterCat);
	{
		mEmitterCat->AppendChild(new wxIntProperty(wxT("����"), wxPG_LABEL, 1))->Enable(true);
		Utility_SetPropertyToSpinCtrl(mPartEmitterEditPG, wxT("����"), 1, 10000, 1, true);

		mEmitterCat->AppendChild(new wxFloatProperty(wxT("�ٶ�"), wxPG_LABEL, 0.0))->Enable(true);
		Utility_SetPropertyToSpinCtrl(mPartEmitterEditPG, wxT("�ٶ�"), -10000.0, 10000.0, 1.0f, true);

		mEmitterCat->AppendChild(new wxFloatProperty(wxT("�ٶ������"), wxPG_LABEL, 0.0))->Enable(true);
		Utility_SetPropertyToSpinCtrl(mPartEmitterEditPG, wxT("�ٶ������"), 0, 1000.0, 1.0f, true);

		mEmitterCat->AppendChild(new wxFloatProperty(wxT("����н�"), wxPG_LABEL, 0.0))->Enable(true);
		Utility_SetPropertyToSpinCtrl(mPartEmitterEditPG, wxT("����н�"), -1000.0, 1000.0, 1.0f, true);

		mEmitterCat->AppendChild(new wxFloatProperty(wxT("����"), wxPG_LABEL, 0.0))->Enable(true);
		Utility_SetPropertyToSpinCtrl(mPartEmitterEditPG, wxT("����"), -1000.0, 1000.0, 1.0f, true);
	}

	mTimeCat = new wxPropertyCategory(wxT("ʱ��ѡ��"), wxT("TimeCategory"));
	mTimeCat->SetExpanded(true);
	mPartEmitterEditPG->Append(mTimeCat);
	{
		mTimeCat->AppendChild(new wxFloatProperty(wxT("��������"), wxPG_LABEL, 0.1f));
		Utility_SetPropertyToSpinCtrl(mPartEmitterEditPG, wxT("��������"), 0.1f, 10000.0f, 1.0f, true);

		mTimeCat->AppendChild(new wxFloatProperty(wxT("ÿ�뷢������"), wxPG_LABEL, 0.1f));
		Utility_SetPropertyToSpinCtrl(mPartEmitterEditPG, wxT("ÿ�뷢������"), 1, 10000.0f, 1.0f, true);

		mTimeCat->AppendChild(new wxBoolProperty(wxT("ȫ���緢"), wxPG_LABEL, false));
		Utility_SetPropertyToBoolWithCheckBox(mPartEmitterEditPG, wxT("ȫ���緢"), true);
	}

	mPlaneCat = new wxPropertyCategory(wxT("����ƽ��ѡ��"), wxT("PlaneCategory"));
	mPlaneCat->SetExpanded(true);
	mPartEmitterEditPG->Append(mPlaneCat);
	{
		mPlaneCat->AppendChild(new wxFloatProperty(wxT("ƽ���"), wxPG_LABEL, 10.0f));
		Utility_SetPropertyToSpinCtrl(mPartEmitterEditPG, wxT("ƽ���"), 0.01f, 10000.0f, 1.0f, true);

		mPlaneCat->AppendChild(new wxFloatProperty(wxT("ƽ���"), wxPG_LABEL, 10));
		Utility_SetPropertyToSpinCtrl(mPartEmitterEditPG, wxT("ƽ���"), 0.01f, 10000.0f, 1.0f, true);
	}

	mParticleCat = new wxPropertyCategory(wxT("����ѡ��"), wxT("ParticleCategory"));
	mParticleCat->SetExpanded(true);
	mPartEmitterEditPG->Append(mParticleCat);
	{
		wxArrayString partTypes;
		partTypes.Add(wxT("Head"));
		partTypes.Add(wxT("Tail"));
		partTypes.Add(wxT("Both"));
		mParticleCat->AppendChild(new wxEnumProperty(wxT("��������"), wxPG_LABEL, partTypes));

		mParticleCat->AppendChild(new wxFloatProperty(wxT("��β����"), wxPG_LABEL, 10));
		Utility_SetPropertyToSpinCtrl(mPartEmitterEditPG, wxT("��β����"), 0.1f, 10000.0f, 1.0f, true);

		mParticleCat->AppendChild(new wxBoolProperty(wxT("ʱ������֡"), wxPG_LABEL, false));
		Utility_SetPropertyToBoolWithCheckBox(mPartEmitterEditPG, wxT("ʱ������֡"), true);

		mParticleCat->AppendChild(new wxIntProperty(wxT("����֡FPS"), wxPG_LABEL, 5));
		Utility_SetPropertyToSpinCtrl(mPartEmitterEditPG, wxT("����֡FPS"), 1, 1000, 1, true);

		mParticleCat->AppendChild(new wxIntProperty(wxT("����֡ѭ������"), wxPG_LABEL, 1));
		Utility_SetPropertyToSpinCtrl(mPartEmitterEditPG, wxT("����֡ѭ������"), 1, 1000, 1, true);

		wxPGProperty *tempProp = NULL;
		wxPGProperty *timeChangeProp = new wxStringProperty(wxT("ʱ��仯"), wxPG_LABEL, wxT("<composed>"));
		timeChangeProp->SetExpanded(true);
		mParticleCat->AppendChild(timeChangeProp);
		{
			// ʱ��(Start): Ĭ��Ϊ���ӷ���ʱ��
			// ʱ��(End): Ĭ��Ϊ��������ʱ��
			tempProp = mPartEmitterEditPG->AppendIn(timeChangeProp, new wxFloatProperty(wxT("Middle"), wxPG_LABEL, 0.0f));
			Utility_SetPropertyToSpinCtrl(tempProp, 0.0f, 1.0f, 0.1f, true);
		}

		wxPGProperty *colorChangeProp = new wxStringProperty(wxT("��ɫ�仯"), wxPG_LABEL, wxT("<composed>"));
		mParticleCat->AppendChild(colorChangeProp);
		{
			mPartEmitterEditPG->AppendIn(colorChangeProp, new wxColourProperty(wxT("Start"), wxPG_LABEL, *wxWHITE));
			mPartEmitterEditPG->AppendIn(colorChangeProp, new wxColourProperty(wxT("Middle"), wxPG_LABEL, *wxWHITE));
			mPartEmitterEditPG->AppendIn(colorChangeProp, new wxColourProperty(wxT("End"), wxPG_LABEL, *wxWHITE));
		}

		wxPGProperty *alphaChangeProp = new wxStringProperty(wxT("Alpha�仯"), wxPG_LABEL, wxT("<composed>"));
		mParticleCat->AppendChild(alphaChangeProp);
		{
			tempProp = mPartEmitterEditPG->AppendIn(alphaChangeProp, new wxIntProperty(wxT("Start"), wxPG_LABEL, 0.0f));
			Utility_SetPropertyToSpinCtrl(tempProp, 0, 255, 10, true);

			tempProp = mPartEmitterEditPG->AppendIn(alphaChangeProp, new wxIntProperty(wxT("Middle"), wxPG_LABEL, 0.0f));
			Utility_SetPropertyToSpinCtrl(tempProp, 0, 255, 10, true);

			tempProp = mPartEmitterEditPG->AppendIn(alphaChangeProp, new wxIntProperty(wxT("End"), wxPG_LABEL, 0.0f));
			Utility_SetPropertyToSpinCtrl(tempProp, 0, 255, 10, true);
		}

		wxPGProperty *scaleChangeProp = new wxStringProperty(wxT("��С�仯"), wxPG_LABEL, wxT("<composed>"));
		mParticleCat->AppendChild(scaleChangeProp);
		{
			tempProp = mPartEmitterEditPG->AppendIn(scaleChangeProp, new wxFloatProperty(wxT("Start"), wxPG_LABEL, 0.0f));
			Utility_SetPropertyToSpinCtrl(tempProp, 0.0f, 1000.0f, 1.0f, true);

			tempProp = mPartEmitterEditPG->AppendIn(scaleChangeProp, new wxFloatProperty(wxT("Middle"), wxPG_LABEL, 0.0f));
			Utility_SetPropertyToSpinCtrl(tempProp, 0.0f, 1000.0f, 1.0f, true);

			tempProp = mPartEmitterEditPG->AppendIn(scaleChangeProp, new wxFloatProperty(wxT("End"), wxPG_LABEL, 0.0f));
			Utility_SetPropertyToSpinCtrl(tempProp, 0.0f, 1000.0f, 1.0f, true);
		}

		wxPGProperty *lifeSpanHeadUVAnimProp = new wxStringProperty(wxT("LifeSpan Head UV Anim"), wxPG_LABEL, wxT("<composed>"));
		mParticleCat->AppendChild(lifeSpanHeadUVAnimProp);
		{
			tempProp = mPartEmitterEditPG->AppendIn(lifeSpanHeadUVAnimProp, new wxIntProperty(wxT("Start"), wxPG_LABEL, 0));
			Utility_SetPropertyToSpinCtrl(tempProp, 0, 10000, 5, true);

			tempProp = mPartEmitterEditPG->AppendIn(lifeSpanHeadUVAnimProp, new wxIntProperty(wxT("Middle"), wxPG_LABEL, 0));
			Utility_SetPropertyToSpinCtrl(tempProp, 0, 10000, 5, true);

			tempProp = mPartEmitterEditPG->AppendIn(lifeSpanHeadUVAnimProp, new wxIntProperty(wxT("Repeat"), wxPG_LABEL, 1));
			Utility_SetPropertyToSpinCtrl(tempProp, 0, 10000, 5, true);
		}

		wxPGProperty *decayHeadUVAnimProp = new wxStringProperty(wxT("Decay Head UV Anim"), wxPG_LABEL, wxT("<composed>"));
		mParticleCat->AppendChild(decayHeadUVAnimProp);
		{
			tempProp = mPartEmitterEditPG->AppendIn(decayHeadUVAnimProp, new wxIntProperty(wxT("Start"), wxPG_LABEL, 0));
			Utility_SetPropertyToSpinCtrl(tempProp, 0, 10000, 5, true);

			tempProp = mPartEmitterEditPG->AppendIn(decayHeadUVAnimProp, new wxIntProperty(wxT("Middle"), wxPG_LABEL, 0));
			Utility_SetPropertyToSpinCtrl(tempProp, 0, 10000, 5, true);

			tempProp = mPartEmitterEditPG->AppendIn(decayHeadUVAnimProp, new wxIntProperty(wxT("Repeat"), wxPG_LABEL, 1));
			Utility_SetPropertyToSpinCtrl(tempProp, 0, 10000, 5, true);
		}

		wxPGProperty *lifeSpanTailUVAnimProp = new wxStringProperty(wxT("LifeSpan Tail UV Anim"), wxPG_LABEL, wxT("<composed>"));
		lifeSpanTailUVAnimProp->SetExpanded(false);
		mParticleCat->AppendChild(lifeSpanTailUVAnimProp);
		{
			tempProp = mPartEmitterEditPG->AppendIn(lifeSpanTailUVAnimProp, new wxIntProperty(wxT("Start"), wxPG_LABEL, 0));
			Utility_SetPropertyToSpinCtrl(tempProp, 0, 10000, 5, true);

			tempProp = mPartEmitterEditPG->AppendIn(lifeSpanTailUVAnimProp, new wxIntProperty(wxT("Middle"), wxPG_LABEL, 0));
			Utility_SetPropertyToSpinCtrl(tempProp, 0, 10000, 5, true);

			tempProp = mPartEmitterEditPG->AppendIn(lifeSpanTailUVAnimProp, new wxIntProperty(wxT("Repeat"), wxPG_LABEL, 1));
			Utility_SetPropertyToSpinCtrl(tempProp, 0, 10000, 5, true);
		}

		wxPGProperty *decayTailUVAnimProp = new wxStringProperty(wxT("Decay Tail UV Anim"), wxPG_LABEL, wxT("<composed>"));
		decayTailUVAnimProp->SetExpanded(false);
		mParticleCat->AppendChild(decayTailUVAnimProp);
		{
			tempProp = mPartEmitterEditPG->AppendIn(decayTailUVAnimProp, new wxIntProperty(wxT("Start"), wxPG_LABEL, 0));
			Utility_SetPropertyToSpinCtrl(tempProp, 0, 10000, 5, true);

			tempProp = mPartEmitterEditPG->AppendIn(decayTailUVAnimProp, new wxIntProperty(wxT("Middle"), wxPG_LABEL, 0));
			Utility_SetPropertyToSpinCtrl(tempProp, 0, 10000, 5, true);

			tempProp = mPartEmitterEditPG->AppendIn(decayTailUVAnimProp, new wxIntProperty(wxT("Repeat"), wxPG_LABEL, 1));
			Utility_SetPropertyToSpinCtrl(tempProp, 0, 10000, 5, true);
		}
	}

	mTexCat = new wxPropertyCategory(wxT("��ͼѡ��"), wxT("TexCategory"));
	mTexCat->SetExpanded(true);
	mPartEmitterEditPG->Append(mTexCat);
	{
		wxArrayString blendLabels;
		blendLabels.Add(wxT("Add"));
		blendLabels.Add(wxT("AlphaKey"));
		blendLabels.Add(wxT("Blend"));
		blendLabels.Add(wxT("Modulate"));
		blendLabels.Add(wxT("Mod2X"));
		mTexCat->AppendChild(new wxEnumProperty(wxT("���ѡ��"), wxPG_LABEL, blendLabels));

		mTexCat->AppendChild(new wxFileProperty(wxT("������ͼ"), wxPG_LABEL));
		mPartEmitterEditPG->SetPropertyAttribute(wxT("������ͼ"), wxPG_FILE_DIALOG_TITLE, wxT("��ѡ��������ͼ"));
		mPartEmitterEditPG->SetPropertyAttribute(wxT("������ͼ"), wxPG_FILE_WILDCARD, wxT("DDS Files (*.dds)|*.dds|TGA Files (*.tga)|*.tga"));
		mPartEmitterEditPG->SetPropertyAttribute(wxT("������ͼ"), wxPG_FILE_SHOW_FULL_PATH, false);

		mTexCat->AppendChild(new wxIntProperty(wxT("Col(����)"), wxPG_LABEL, 1));
		Utility_SetPropertyToSpinCtrl(mPartEmitterEditPG, wxT("Col(����)"), 1, 100, 1, true);

		mTexCat->AppendChild(new wxIntProperty(wxT("Row(����)"), wxPG_LABEL, 1));
		Utility_SetPropertyToSpinCtrl(mPartEmitterEditPG, wxT("Row(����)"), 1, 100, 1, true);
		
		//mTexCat->AppendChild(new wxBoolProperty(wxT("���ݾ�������"), wxPG_LABEL, false));
		//Utility_SetPropertyToBoolWithCheckBox(mPartEmitterEditPG, wxT("���ݾ�������"), true);
	}

	mOtherCat = new wxPropertyCategory(wxT("����ѡ��"), wxT("OtherCategory"));
	mOtherCat->SetExpanded(true);
	mPartEmitterEditPG->Append(mOtherCat);
	{
		mOtherCat->AppendChild(new wxBoolProperty(wxT("��ģ�Ϳռ��˶�"), wxPG_LABEL, false));
		Utility_SetPropertyToBoolWithCheckBox(mPartEmitterEditPG, wxT("��ģ�Ϳռ��˶�"), true);

		mOtherCat->AppendChild(new wxBoolProperty(wxT("����������"), wxPG_LABEL, false));
		Utility_SetPropertyToBoolWithCheckBox(mPartEmitterEditPG, wxT("����������"), true);

		mOtherCat->AppendChild(new wxBoolProperty(wxT("����XYƽ��"), wxPG_LABEL, false));
		Utility_SetPropertyToBoolWithCheckBox(mPartEmitterEditPG, wxT("����XYƽ��"), true);

		// �¼ӵĲ���, ֻ��ģ�Ͳ鿴���пɱ༭
		{
			mOtherCat->AppendChild(new wxBoolProperty(wxT("��ת����"), wxPG_LABEL, false));
			Utility_SetPropertyToBoolWithCheckBox(mPartEmitterEditPG, wxT("��ת����"), true);

			mOtherCat->AppendChild(new wxIntProperty(wxT("��ת360����ʱ"), wxPG_LABEL, 1000));
			Utility_SetPropertyToSpinCtrl(mPartEmitterEditPG, wxT("��ת360����ʱ"), 1, 100000, 100, true);

			mOtherCat->AppendChild(new wxBoolProperty(wxT("�������"), wxPG_LABEL, false));
			Utility_SetPropertyToBoolWithCheckBox(mPartEmitterEditPG, wxT("�������"), true);

			mOtherCat->AppendChild(new wxBoolProperty(wxT("���淢�����任"), wxPG_LABEL, false));
			Utility_SetPropertyToBoolWithCheckBox(mPartEmitterEditPG, wxT("���淢�����任"), true);
		}

		wxArrayString bindParts;
		for (int i = 0; i < 5; ++i)
			bindParts.Add(BindPartName[i]);
		wxEnumProperty *bindPartProp = new wxEnumProperty(wxT("�󶨲�λ"), wxPG_LABEL, bindParts);
		bindPartProp->SetChoiceSelection(0);
		mOtherCat->AppendChild(bindPartProp);
	}

	// �¼ӵ�ѡ��
	mNewCat = new wxPropertyCategory(wxT("����ѡ��"), wxT("NewOptionCategory"));
	mNewCat->SetExpanded(true);
	mPartEmitterEditPG->Append(mNewCat);
	{
		// Mex2ParticleEmitterSetting3��������
		{
			mNewCat->AppendChild(new wxFloatProperty(wxT("����������ֵ"), wxPG_LABEL, false));
			Utility_SetPropertyToSpinCtrl(mPartEmitterEditPG, wxT("����������ֵ"), 0.0, 1000.0, 1.0, true);

			mNewCat->AppendChild(new wxFloatProperty(wxT("��С�����Сֵ"), wxPG_LABEL, false));
			Utility_SetPropertyToSpinCtrl(mPartEmitterEditPG, wxT("��С�����Сֵ"), 0.0, 1000.0, 1.0, true);

			mNewCat->AppendChild(new wxFloatProperty(wxT("��С������ֵ"), wxPG_LABEL, false));
			Utility_SetPropertyToSpinCtrl(mPartEmitterEditPG, wxT("��С������ֵ"), 0.0, 1000.0, 1.0, true);

			mNewCat->AppendChild(new wxBoolProperty(wxT("����ɫȡ��"), wxPG_LABEL, false));
			Utility_SetPropertyToBoolWithCheckBox(mPartEmitterEditPG, wxT("����ɫȡ��"), true);
		}

		// Mex2ParticleEmitterSetting4��������
		{
			mNewCat->AppendChild(new wxBoolProperty(wxT("�淢�䷽����ת"), wxPG_LABEL, false));
			Utility_SetPropertyToBoolWithCheckBox(mPartEmitterEditPG, wxT("�淢�䷽����ת"), true);

			mNewCat->AppendChild(new wxBoolProperty(wxT("��β���ȱ仯"), wxPG_LABEL, false));
			Utility_SetPropertyToBoolWithCheckBox(mPartEmitterEditPG, wxT("��β���ȱ仯"), true);

			wxPGProperty *tailChangeProp = new wxStringProperty(wxT("��β���ȱ仯��ֵ"), wxPG_LABEL, wxT("<composed>"));
			tailChangeProp->SetExpanded(true);
			mNewCat->AppendChild(tailChangeProp);
			{
				wxPGProperty *tempProp = mPartEmitterEditPG->AppendIn(tailChangeProp, new wxFloatProperty(wxT("Start"), wxPG_LABEL, 0));
				Utility_SetPropertyToSpinCtrl(tempProp, 0.0, 1000.0, 1.0, true);

				tempProp = mPartEmitterEditPG->AppendIn(tailChangeProp, new wxFloatProperty(wxT("Middle"), wxPG_LABEL, 0));
				Utility_SetPropertyToSpinCtrl(tempProp, 0.0, 1000.0, 1.0, true);

				tempProp = mPartEmitterEditPG->AppendIn(tailChangeProp, new wxFloatProperty(wxT("End"), wxPG_LABEL, 1));
				Utility_SetPropertyToSpinCtrl(tempProp, 0.0, 1000.0, 1.0, true);
			}
		}

		mNewCat->AppendChild(new wxBoolProperty(wxT("UV������1֡���"), wxPG_LABEL, false));
		Utility_SetPropertyToBoolWithCheckBox(mPartEmitterEditPG, wxT("UV������1֡���"), true);

		mNewCat->AppendChild(new wxBoolProperty(wxT("XYQuad�������з�ƽ"), wxPG_LABEL, false));
		Utility_SetPropertyToBoolWithCheckBox(mPartEmitterEditPG, wxT("XYQuad�������з�ƽ"), true);
	}
}

void RightWindow::OnModelInfoPropertyGridChange(wxPropertyGridEvent &event)
{
	wxPGProperty *prop = event.GetProperty();

	wxAny value = prop->GetValue();
	if (value.IsNull())
		return;

	ModelObj *obj = gMainFrame->GetCurrentModel();
	if (obj == NULL)
		return;

	const wxString &name = prop->GetName();
	if (name == wxT("����"))
	{
		float scale = wxANY_AS(value, float);
		obj->SetScale(scale);
		obj->ApplyTransform();
	}
	else if (name == wxT("��תX"))
	{
		float rot_x = wxANY_AS(value, int);
		obj->model->SetRotationX(D3DXToRadian(rot_x));
		obj->ApplyTransform();
	}
	else if (name == wxT("��תY"))
	{
		float rot_y = wxANY_AS(value, int);
		obj->model->SetRotationY(D3DXToRadian(rot_y));
		obj->ApplyTransform();
	}
	else if (name == wxT("��תZ"))
	{
		float rot_z = wxANY_AS(value, int);
		obj->model->SetRotationZ(D3DXToRadian(rot_z));
		obj->ApplyTransform();
	}

	// Skin�����Item
	if (name.Find(wxT("��ͼ")) != -1)
	{
		int index = -1;
		if (sscanf(name.mb_str(), "��ͼ%d", &index) > 0)
		{
			--index;

			// ��ȡ��ǰѡ�е�Setting
			wxTreeItemId curSel = mMexConfigTree->GetSelection();
			if (curSel == NULL)
				return;

			wxString curSelSetting = mMexConfigTree->GetItemText(curSel);
			if (curSelSetting == wxT("Default"))
				return;

			MexCfgAvatarSetting *avatarSetting = obj->model->GetMexCfg()->m_AvatarSettings.FindByName(curSelSetting);
			if (avatarSetting == NULL)
				return;

			int count = avatarSetting->m_vectorReplaceableTexture.size();
			if (index >= 0 && index <= count - 1)
			{
				MexCfgAvatarSetting::ReplaceableTexture &tex = avatarSetting->m_vectorReplaceableTexture[index];
				MexReplaceableTextureProj *texProj = dynamic_cast<MexReplaceableTextureProj *> (obj->model->GetReplaceableTextureProj());

				wxString texName = wxANY_AS(value, wxString);
				wxFileName texNameFN(texName);
				strcpy(tex.szFileName, texNameFN.GetName() + wxT(".") + texNameFN.GetExt());

				// ����Ani
				Utility_SaveAni(obj);
				obj->model->ChangeAvatarSetting(curSelSetting.mb_str());
			}
		}
	}
}

void RightWindow::OnParticleEditPropertyGridChange(wxPropertyGridEvent &event)
{
	wxPGProperty *prop = event.GetProperty();

	wxAny value = prop->GetValue();
	if (value.IsNull())
		return;

	ModelObj *obj = gMainFrame->GetCurrentModel();
	if (obj == NULL)
		return;

	IMex *mex = obj->model->GetMex();
	if (mex == NULL)
		return;

	if (!obj->HasParticleEmitters() || mParticleEmitterChoice->GetSelection() == -1)
		return;

	Mex2ParticleEmitter *e = (Mex2ParticleEmitter *) mex->GetParticleEmitters()->GetEmitter(this->GetCurrentParticleEmitter());

	const wxString &name = prop->GetName();
	if (name == wxT("������ͼ"))
	{
		wxString texFullPath = wxANY_AS(value, wxString);
		if (texFullPath.empty())
			return;

		wxFileName fn(texFullPath.c_str());
		fn.SetPath(obj->GetFileFolder());
		if (!wxFileExists(fn.GetFullPath()))
		{
			// ������·��ѡ����ͼ, mex�ļ�ͬ��Ŀ¼�²�����ѡ�е���ͼ, �򿽱���ȥ
			wxCopyFile(texFullPath, fn.GetFullPath(), true);
		}
	}

	SaveCurrentParticleEmitterParams();
	obj->model->RefreshParticleEmitters();
}

void RightWindow::OnParticleEmitterChoice(wxCommandEvent &WXUNUSED(event))
{
	ModelObj *obj = gMainFrame->GetCurrentModel();
	if (obj == NULL)
		return;

	IMex *mex = obj->model->GetMex();
	if (mex == NULL)
		return;

	// �������ӷ���������
	int cur = this->GetCurrentParticleEmitter();
	if (cur == -1)
		return;

	if (!obj->HasParticleEmitters())
		return;

	Mex2ParticleEmitter *e = (Mex2ParticleEmitter *) mex->GetParticleEmitters()->GetEmitter(cur);
	if (e == NULL)
		return;

	wxColour tempClr = *wxWHITE;
	int selection = -1;
	bool tempBool = false;

	// ����
	mPartEmitterEditPG->Enable(true);

	// ������ѡ��
	mPartEmitterEditPG->SetPropertyValue(wxT("����"), e->GetSetting()->nCount);
	mPartEmitterEditPG->SetPropertyValue(wxT("�ٶ�"), e->GetSetting()->fSpeed);
	mPartEmitterEditPG->SetPropertyValue(wxT("�ٶ������"), e->GetSetting()->fVariation);
	mPartEmitterEditPG->SetPropertyValue(wxT("����н�"), e->GetSetting()->fConeAngle);
	mPartEmitterEditPG->SetPropertyValue(wxT("����"), e->GetSetting()->fGravity);

	// ʱ��ѡ��
	mPartEmitterEditPG->SetPropertyValue(wxT("��������"), e->GetSetting()->fLifeSpan);
	mPartEmitterEditPG->SetPropertyValue(wxT("ÿ�뷢������"), e->GetSetting()->fEmissionRate);
	tempBool = e->GetSetting()->dwFlag & MEX2_PARTICLE_EMITTER_SQUIRT;
	mPartEmitterEditPG->SetPropertyValue(wxT("ȫ���緢"), tempBool);

	// ����ƽ��ѡ��
	mPartEmitterEditPG->SetPropertyValue(wxT("ƽ���"), e->GetSetting()->fWidth);
	mPartEmitterEditPG->SetPropertyValue(wxT("ƽ���"), e->GetSetting()->fHeight);

	// ����ѡ��
	for (int i = 0; i < 3; ++i)
	{
		if (e->GetSetting()->dwPart == ParticleTypes[i])
		{
			selection = i;
			break;
		}
	}
	mPartEmitterEditPG->GetProperty(wxT("��������"))->SetChoiceSelection(selection);
	mPartEmitterEditPG->SetPropertyValue(wxT("��β����"), e->GetSetting()->fTailLength);
	tempBool = e->UseTimeBasedCell();
	mPartEmitterEditPG->SetPropertyValue(wxT("ʱ������֡"), tempBool);
	mPartEmitterEditPG->SetPropertyValue(wxT("����֡FPS"), (int) e->GetSetting()->dwUVAnimFps);
	mPartEmitterEditPG->SetPropertyValue(wxT("����֡ѭ������"), e->TimeBasedCellLoopTimes());
	mPartEmitterEditPG->SetPropertyValue(wxT("ʱ��仯.Middle"), e->GetSetting()->fMiddleTime);
	tempClr.Set(
		(unsigned char) e->GetSetting()->nSegmentColor[0][0],
		(unsigned char) e->GetSetting()->nSegmentColor[0][1],
		(unsigned char) e->GetSetting()->nSegmentColor[0][2]);
	mPartEmitterEditPG->SetPropertyValue(wxT("��ɫ�仯.Start"), tempClr);
	tempClr.Set(
		(unsigned char) e->GetSetting()->nSegmentColor[1][0],
		(unsigned char) e->GetSetting()->nSegmentColor[1][1],
		(unsigned char) e->GetSetting()->nSegmentColor[1][2]);
	mPartEmitterEditPG->SetPropertyValue(wxT("��ɫ�仯.Middle"), tempClr);
	tempClr.Set(
		(unsigned char) e->GetSetting()->nSegmentColor[2][0],
		(unsigned char) e->GetSetting()->nSegmentColor[2][1],
		(unsigned char) e->GetSetting()->nSegmentColor[2][2]);
	mPartEmitterEditPG->SetPropertyValue(wxT("��ɫ�仯.End"), tempClr);
	mPartEmitterEditPG->SetPropertyValue(wxT("Alpha�仯.Start"), e->GetSetting()->nAlpha[0]);
	mPartEmitterEditPG->SetPropertyValue(wxT("Alpha�仯.Middle"), e->GetSetting()->nAlpha[1]);
	mPartEmitterEditPG->SetPropertyValue(wxT("Alpha�仯.End"), e->GetSetting()->nAlpha[2]);
	mPartEmitterEditPG->SetPropertyValue(wxT("��С�仯.Start"), e->GetSetting()->fParticleScaling[0]);
	mPartEmitterEditPG->SetPropertyValue(wxT("��С�仯.Middle"), e->GetSetting()->fParticleScaling[1]);
	mPartEmitterEditPG->SetPropertyValue(wxT("��С�仯.End"), e->GetSetting()->fParticleScaling[2]);
	{
		mPartEmitterEditPG->SetPropertyValue(wxT("LifeSpan Head UV Anim.Start"), (int) e->GetSetting()->dwLifeSpanHeadUVAnim[0]);
		mPartEmitterEditPG->SetPropertyValue(wxT("LifeSpan Head UV Anim.Middle"), (int) e->GetSetting()->dwLifeSpanHeadUVAnim[1]);
		mPartEmitterEditPG->SetPropertyValue(wxT("LifeSpan Head UV Anim.Repeat"), (int) e->GetSetting()->dwLifeSpanHeadUVAnim[2]);

		mPartEmitterEditPG->SetPropertyValue(wxT("Decay Head UV Anim.Start"), (int) e->GetSetting()->dwDecayHeadUVAnim[0]);
		mPartEmitterEditPG->SetPropertyValue(wxT("Decay Head UV Anim.Middle"), (int) e->GetSetting()->dwDecayHeadUVAnim[1]);
		mPartEmitterEditPG->SetPropertyValue(wxT("Decay Head UV Anim.Repeat"), (int) e->GetSetting()->dwDecayHeadUVAnim[2]);

		mPartEmitterEditPG->SetPropertyValue(wxT("LifeSpan Tail UV Anim.Start"), (int) e->GetSetting()->dwLifeSpanTailUVAnim[0]);
		mPartEmitterEditPG->SetPropertyValue(wxT("LifeSpan Tail UV Anim.Middle"), (int) e->GetSetting()->dwLifeSpanTailUVAnim[1]);
		mPartEmitterEditPG->SetPropertyValue(wxT("LifeSpan Tail UV Anim.Repeat"), (int) e->GetSetting()->dwLifeSpanTailUVAnim[2]);

		mPartEmitterEditPG->SetPropertyValue(wxT("Decay Tail UV Anim.Start"), (int) e->GetSetting()->dwDecayTailUVAnim[0]);
		mPartEmitterEditPG->SetPropertyValue(wxT("Decay Tail UV Anim.Middle"), (int) e->GetSetting()->dwDecayTailUVAnim[1]);
		mPartEmitterEditPG->SetPropertyValue(wxT("Decay Tail UV Anim.Repeat"), (int) e->GetSetting()->dwDecayTailUVAnim[2]);
	}

	// ��ͼѡ��
	for (int i = 0; i < 5; ++i)
	{
		if (e->GetSetting()->dwBlendMode == TexBlendMode[i])
		{
			selection = i;
			break;
		}
	}
	mPartEmitterEditPG->GetProperty(wxT("���ѡ��"))->SetChoiceSelection(selection);

	IMexTexture *texture = mex->GetTextures()->GetTexture(e->GetSetting()->nTextureId);
	mPartEmitterEditPG->SetPropertyValue(wxT("������ͼ"), texture != NULL ? texture->GetName() : "");
	mPartEmitterEditPG->SetPropertyValue(wxT("Col(����)"), e->GetSetting()->nCol);
	mPartEmitterEditPG->SetPropertyValue(wxT("Row(����)"), e->GetSetting()->nRow);

	//tempBool = e->GetSetting()->dwFlag & MEX2_SORTBYFARZ;
	//mPartEmitterEditPG->SetPropertyValue(wxT("���ݾ�������"), tempBool);

	// ����ѡ��
	tempBool = e->GetSetting()->dwFlag & MEX2_PARTICLE_EMITTER_PARTICLEINMODELSPACE;
	mPartEmitterEditPG->SetPropertyValue(wxT("��ģ�Ϳռ��˶�"), tempBool);

	tempBool = e->GetSetting()->dwFlag & MEX2_PARTICLE_EMITTER_LOCKEMITTER;
	mPartEmitterEditPG->SetPropertyValue(wxT("����������"), tempBool);

	tempBool = e->GetSetting()->dwFlag & MEX2_PARTICLE_EMITTER_XYQUAD;
	mPartEmitterEditPG->SetPropertyValue(wxT("����XYƽ��"), tempBool);

	tempBool = e->RotateParticle();
	mPartEmitterEditPG->SetPropertyValue(wxT("��ת����"), tempBool);
	mPartEmitterEditPG->SetPropertyValue(wxT("��ת360����ʱ"), e->Rotate360DegreeCostTime());

	tempBool = e->RandomDir();
	mPartEmitterEditPG->SetPropertyValue(wxT("�������"), tempBool);

	tempBool = e->RotNotFollowEmitter();
	mPartEmitterEditPG->SetPropertyValue(wxT("���淢�����任"), !tempBool);

	const char *bp = e->GetBindPartName();
	for (int i = 0; i < 5; ++i)
	{
		if (strlen(e->GetBindPartName()) > 0)
		{
			if (strcmp(e->GetBindPartName(), BindPartName[i]) == 0)
			{
				selection = i;
				break;
			}
		}
		else
		{
			selection = i;
			break;
		}
	}
	mPartEmitterEditPG->GetProperty(wxT("�󶨲�λ"))->SetChoiceSelection(selection);

	// ����ѡ��
	mPartEmitterEditPG->SetPropertyValue(wxT("����������ֵ"), e->GetSetting()->fLifeSpanMax);
	mPartEmitterEditPG->SetPropertyValue(wxT("��С�����Сֵ"), e->GetSetting()->fScaleRateMin);
	mPartEmitterEditPG->SetPropertyValue(wxT("��С������ֵ"), e->GetSetting()->fScaleRateMax);
	mPartEmitterEditPG->SetPropertyValue(wxT("����ɫȡ��"), e->GetSetting()->bContraryColor);

	mPartEmitterEditPG->SetPropertyValue(wxT("�淢�䷽����ת"), e->GetSetting()->bAngleChangeByCone);
	mPartEmitterEditPG->SetPropertyValue(wxT("��β���ȱ仯"), e->GetSetting()->bTailLengthChange);
	mPartEmitterEditPG->SetPropertyValue(wxT("��β���ȱ仯��ֵ.Start"), e->GetSetting()->fTailLengthChange[0]);
	mPartEmitterEditPG->SetPropertyValue(wxT("��β���ȱ仯��ֵ.Middle"), e->GetSetting()->fTailLengthChange[1]);
	mPartEmitterEditPG->SetPropertyValue(wxT("��β���ȱ仯��ֵ.End"), e->GetSetting()->fTailLengthChange[2]);

	mPartEmitterEditPG->SetPropertyValue(wxT("UV������1֡���"), e->UVRandomFirstCell());
	mPartEmitterEditPG->SetPropertyValue(wxT("XYQuad�������з�ƽ"), e->XYQuadLaydownInWorld());	
}

void RightWindow::OnParticleEmitterParamExport(wxCommandEvent &WXUNUSED(event))
{
	ModelObj *obj = gMainFrame->GetCurrentModel();
	if (obj == NULL)
		return;

	if (!obj->HasParticleEmitters())
	{
		wxMessageBox(wxT("�޷��������Ӳ���, ��ģ��û�����ӷ�����!"));
		return;
	}

	if (!this->SaveCurrentParticleEmitterParams())
		return;

	wxArrayString as;
	mAutoDeskObjProps.ConvertTo3dsMaxPropString(as);
	
	CopyableMessageDialog dlg(gMainFrame, wxID_ANY, wxT("�������ӷ�����������3ds Max 2011"), wxSize(800, 600), as);
	if (dlg.ShowModal() == wxID_OK)
	{
		wxMessageBox(wxT("OK"));
	}
}

void RightWindow::OnMexConfigTreeBeginLabelEdit(wxTreeEvent &event)
{
	mLabelBeforeEdit = event.GetLabel();
}

void RightWindow::OnMexConfigTreeEndLabelEdit(wxTreeEvent &event)
{
	ModelObj *obj = gMainFrame->GetCurrentModel();
	if (obj == NULL)
		return;

	MexCfg *mexCfg = obj->model->GetMexCfg();
	if (mexCfg == NULL)
		return;

	wxTreeItemId curItem = event.GetItem();

	wxString valueStr = event.GetLabel();
	if (valueStr.IsEmpty())
		return;

	long valueLong = 0;
	valueStr.ToLong(&valueLong);
	
	if (Utility_Strnicmp(mLabelBeforeEdit.mb_str(), "ModelScale"))
	{
		mexCfg->m_mdlScale.m_npScale.SetNumber(valueLong);
		mMexConfigTree->SetItemText(curItem, wxString::Format(wxT("ModelScale: %d"), valueLong));
	}
	else if (Utility_Strnicmp(mLabelBeforeEdit.mb_str(), "BodyRadius"))
	{
		mexCfg->m_BodyRadius.m_npRadius.SetNumber(valueLong);
		mMexConfigTree->SetItemText(curItem, wxString::Format(wxT("BodyRadius: %d"), valueLong));
	}

	// SoundEffect
	else if (Utility_Strnicmp(mLabelBeforeEdit.mb_str(), "SoundFilename"))
	{
		mexCfg->m_soundEffect.m_spSoundFilename.SetString(valueStr.mb_str());
		mMexConfigTree->SetItemText(curItem, wxString::Format(wxT("SoundFilename: %s"), valueStr));
	}
	else if (Utility_Strnicmp(mLabelBeforeEdit.mb_str(), "Range"))
	{
		mexCfg->m_soundEffect.m_npRange.SetNumber(valueLong);
		mMexConfigTree->SetItemText(curItem, wxString::Format(wxT("Range: %d"), valueLong));
	}
	else if (Utility_Strnicmp(mLabelBeforeEdit.mb_str(), "Loop"))
	{
		mexCfg->m_soundEffect.m_npLoopFlag.SetNumber(valueLong);
		mMexConfigTree->SetItemText(curItem, wxString::Format(wxT("Loop: %d"), valueLong));
	}
	else if (Utility_Strnicmp(mLabelBeforeEdit.mb_str(), "Frequence"))
	{
		mexCfg->m_soundEffect.m_npFrequence.SetNumber(valueLong);
		mMexConfigTree->SetItemText(curItem, wxString::Format(wxT("Frequence: %d"), valueLong));
	}
	else if (Utility_Strnicmp(mLabelBeforeEdit.mb_str(), "Intensity"))
	{
		mexCfg->m_soundEffect.m_npIntensity.SetNumber(valueLong);
		mMexConfigTree->SetItemText(curItem, wxString::Format(wxT("Intensity: %d"), valueLong));
	}

	// BoundingObject
	else if (Utility_Strnicmp(mLabelBeforeEdit.mb_str(), "Width"))
	{
		mexCfg->m_BObj.m_npBBoxWidth.SetNumber(valueLong);
		mMexConfigTree->SetItemText(curItem, wxString::Format(wxT("Width: %d"), valueLong));
	}
	else if (Utility_Strnicmp(mLabelBeforeEdit.mb_str(), "Height"))
	{
		mexCfg->m_BObj.m_npBBoxHeight.SetNumber(valueLong);
		mMexConfigTree->SetItemText(curItem, wxString::Format(wxT("Height: %d"), valueLong));
	}
	else if (Utility_Strnicmp(mLabelBeforeEdit.mb_str(), "Length"))
	{
		mexCfg->m_BObj.m_npBBoxLength.SetNumber(valueLong);
		mMexConfigTree->SetItemText(curItem, wxString::Format(wxT("Length: %d"), valueLong));
	}
	else if (Utility_Strnicmp(mLabelBeforeEdit.mb_str(), "Lift"))
	{
		mexCfg->m_BObj.m_npBBoxLift.SetNumber(valueLong);
		mMexConfigTree->SetItemText(curItem, wxString::Format(wxT("Lift: %d"), valueLong));
	}

	// ����Ani
	Utility_SaveAni(obj);

	// ���¼���ģ��
	gMainFrame->ReloadCurrentModel();

	// ��ֹ�ı�TreeItem��Label
	event.Veto();
}

void RightWindow::OnMexConfigTreeRightClick(wxTreeEvent &event)
{
	wxPoint pos;
	wxTreeItemId hitItem;
	Utility_TreeCtrlHitTest(mMexConfigTree, pos, hitItem);
	if (hitItem.IsOk())
	{
		// ��ѡ������Item
		mMexConfigTree->SelectItem(hitItem);

		wxString itemText = mMexConfigTree->GetItemText(hitItem);
		if (itemText == wxT("AvatarSetting"))
		{
			mMexConfigTree->PopupMenu(mAddSkinMenu, pos.x, pos.y);
		}
		else if (itemText == wxT("MexConfig") || itemText == wxT("SoundEffect")
			|| itemText == wxT("BoundingObject") || itemText == wxT("Default"))
		{
			return;
		}

		for (int i = 0; i < MexConfigItemMax; ++i)
		{
			if (hitItem == mMexConfigTreeItems[i])
				return;
		}

		mMexConfigTree->PopupMenu(mSkinEditMenu, pos.x, pos.y);
	}
}

void RightWindow::OnMexConfigTreeDoubleClick(wxTreeEvent &event)
{
	ModelObj *obj = gMainFrame->GetCurrentModel();
	if (obj == NULL)
		return;

	wxTreeItemId item = event.GetItem();
	for (int i = 0; i < MexConfigItemMax; ++i)
	{
		if (item == mMexConfigTreeItems[i])
			return;
	}

	wxString settingName = mMexConfigTree->GetItemText(item);
	if (settingName == wxT("MexConfig") || settingName == wxT("SoundEffect") || settingName == wxT("BoundingObject"))
		return;

	obj->model->ChangeAvatarSetting(settingName);

	// ����AvatarSettingˢ����ͼ�б�
	MexCfgAvatarSetting *avatarSetting = obj->model->GetMexCfg()->m_AvatarSettings.FindByName(settingName.mb_str());
	if (avatarSetting == NULL)
		return;

	mSkinTexCat->DeleteChildren();
	for (int i = 0; i < avatarSetting->m_vectorReplaceableTexture.size(); ++i)
	{
		wxString texLabel = wxString::Format(wxT("��ͼ%d"), i + 1);
		mSkinTexCat->AppendChild(new wxFileProperty(texLabel, wxPG_LABEL));
		mModelInfoPG->SetPropertyAttribute(texLabel, wxPG_FILE_DIALOG_TITLE, wxT("��ѡ�����������ͼ"));
		mModelInfoPG->SetPropertyAttribute(texLabel, wxPG_FILE_WILDCARD, wxT("DDS Files (*.dds)|*.dds|TGA Files (*.tga)|*.tga"));
		mModelInfoPG->SetPropertyAttribute(texLabel, wxPG_FILE_SHOW_FULL_PATH, false);
		mModelInfoPG->SetPropertyAttribute(texLabel, wxPG_FILE_INITIAL_PATH, obj->GetFileFolder());
		mModelInfoPG->SetPropertyValue(texLabel, avatarSetting->m_vectorReplaceableTexture[i].szFileName);
	}
	mModelInfoPG->Refresh();
}

void RightWindow::OnMenuItemAddSkin(wxCommandEvent &WXUNUSED(event))
{
	ModelObj *obj = gMainFrame->GetCurrentModel();
	if (obj == NULL)
		return;

	wxTextEntryDialog dlg(this, wxT("������Skin������"), wxT("�½�Skin"));
	if (dlg.ShowModal() == wxID_OK)
	{
		if (dlg.GetValue().IsEmpty())
		{
			wxMessageBox(wxT("Skin���ֲ���Ϊ��!"));
			return;
		}

		MexCfgAvatarSetting *avatarSetting = obj->model->GetMexCfg()->m_AvatarSettings.FindByName(dlg.GetValue().mb_str());
		if (avatarSetting != NULL)
		{
			wxMessageBox(wxT("Skin�����ظ�!"));
			return;
		}

		MexCfgAvatarSetting *defaultSetting = obj->model->GetMexCfg()->m_AvatarSettings.FindByName("Default");
		assert(defaultSetting != NULL);

		MexCfgAvatarSetting *newSetting = MeNew MexCfgAvatarSetting;
		newSetting->m_spName.SetString(dlg.GetValue());
		for (int i = 0; i < defaultSetting->m_vectorSubsetFlag.size(); ++i)
			newSetting->m_vectorSubsetFlag.push_back(defaultSetting->m_vectorSubsetFlag[i]);

		for (int i = 0; i < defaultSetting->m_vectorReplaceableTexture.size(); ++i)
			newSetting->m_vectorReplaceableTexture.push_back(defaultSetting->m_vectorReplaceableTexture[i]);
		obj->model->GetMexCfg()->m_AvatarSettings.m_vectorSetting.push_back(newSetting);

		// ����Ani
		Utility_SaveAni(obj);

		this->UpdateInfoByChildType(ChildWnd_ModelInfo);
	}
}

void RightWindow::OnMenuItemSkinRename(wxCommandEvent &WXUNUSED(event))
{
	ModelObj *obj = gMainFrame->GetCurrentModel();
	if (obj == NULL)
		return;

	wxTreeItemId curSel = mMexConfigTree->GetSelection();
	wxString settingName = mMexConfigTree->GetItemText(curSel);
	if (settingName == wxT("Default"))
		return;

	wxTextEntryDialog dlg(this, wxT("������Skin����"), wxT("������"), settingName);
	if (dlg.ShowModal() == wxID_OK)
	{
		MexCfgAvatarSetting *setting = obj->model->GetMexCfg()->m_AvatarSettings.FindByName(settingName.mb_str());
		setting->m_spName.SetString(dlg.GetValue().mb_str());

		// ����Ani
		Utility_SaveAni(obj);

		// ����TreeItemText
		mMexConfigTree->SetItemText(curSel, dlg.GetValue());
	}
}

void RightWindow::OnMenuItemDelSkin(wxCommandEvent &WXUNUSED(event))
{
	ModelObj *obj = gMainFrame->GetCurrentModel();
	if (obj == NULL)
		return;

	if (wxMessageBox(wxT("���������, �Ƿ�ȷ��ɾ��?"), wxT("ɾ����ʾ"), wxOK | wxCANCEL | wxCENTER) == wxOK)
	{
		wxTreeItemId curSel = mMexConfigTree->GetSelection();
		wxString settingName = mMexConfigTree->GetItemText(curSel);
		if (settingName == wxT("Default"))
			return;

		for (AvatarSettingsIter iter = obj->model->GetMexCfg()->m_AvatarSettings.m_vectorSetting.begin();
			iter != obj->model->GetMexCfg()->m_AvatarSettings.m_vectorSetting.end(); ++iter)
		{
			if (stricmp((*iter)->m_spName.GetString(), settingName.mb_str()) == 0)
			{
				obj->model->GetMexCfg()->m_AvatarSettings.m_vectorSetting.erase(iter);
				break;
			}
		}

		// ����Ani
		Utility_SaveAni(obj);

		// ɾ��TreeItem
		mMexConfigTree->Delete(curSel);
	}
}

void RightWindow::OnSize(wxSizeEvent &event)
{
	wxSize wndSize = event.GetSize();
	{
		mModelInfoPG->SetPosition(wxPoint(0, 0));
		mModelInfoPG->SetSize(wndSize.GetWidth(), wndSize.GetHeight() - RIGHT_WND_MEXCONFIG_TREE_HEIGHT);
		mModelInfoPG->Refresh();

		mMexConfigTree->SetPosition(wxPoint(0, wndSize.GetHeight() - RIGHT_WND_MEXCONFIG_TREE_HEIGHT));
		mMexConfigTree->SetSize(wndSize.GetWidth(), wndSize.GetHeight() - RIGHT_WND_MEXCONFIG_TREE_HEIGHT);
	}
	{
		mAnimationWnd->SetPosition(wxPoint(0, 0));
		mAnimationWnd->SetSize(wndSize);
		mAnimationWnd->Refresh();
	}

	{
		mParticleEmitterChoiceLabel->SetPosition(wxPoint(20, 10));
		mParticleEmitterChoice->SetPosition(wxPoint(88, 5));
		mParticleEmitterChoice->SetSize(128, 22);
		mPartEmitterExportBtn->SetPosition(wxPoint(228, 5));
		mPartEmitterExportBtn->SetSize(42, 22);

		mPartEmitterEditPG->SetPosition(wxPoint(0, 32));
		mPartEmitterEditPG->SetSize(wndSize.GetWidth(), wndSize.GetHeight() - 32);
		mPartEmitterEditPG->Refresh();
	}

	{
		mAvatarWnd->SetPosition(wxPoint(0, 0));
		mAvatarWnd->SetSize(wndSize);
		mAvatarWnd->Refresh();
	}

	{
		m_ModeConfigWnd->SetPosition(wxPoint(0, 0));
		m_ModeConfigWnd->SetSize(wndSize);
		m_ModeConfigWnd->Refresh();
	}

	ShowChildByType(mCurChildType);
}