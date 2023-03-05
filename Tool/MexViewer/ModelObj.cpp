#include "StdAfx.h"
#include "ModelObj.h"

ModelObj::ModelObj(RenderHelper *rh, bool isAvatar)
{
	mRH = rh;
	mAvatar = NULL;
	mIsAvatar = isAvatar;
}

ModelObj::~ModelObj()
{
	SAFE_DELETE(mAvatar);
}

void ModelObj::SetPause(bool pause, int frameID)
{
	MexAnimCtrl::SPlayTask *task = model->GetPlayTask(0);
	if (task == NULL)
		return;

	model->SetUpperBodyFactor((float)(frameID - model->GetStartFrameID()) / (model->GetEndFrameId()-model->GetStartFrameID()+1) );
	if (pause)
	{
		model->SetFrameID(frameID);
		task->dwPlayMode = MexAnimCtrl::eSingleFrame;
		task->nSingleFrameID = frameID;
	}
	else
	{
		task->dwPlayMode = MexAnimCtrl::eNormalPlay;
	}
}

int ModelObj::GetFrameCount()
{
	return model->GetFrameCount();
}

bool ModelObj::HasParticleEmitters()
{
	IMex *mex = model->GetMex();
	if (mex == NULL || mex->GetParticleEmitters() == NULL)
		return false;

	return mex->GetParticleEmitters()->GetEmitterCount() > 0;
}

float ModelObj::GetScale()
{
	float scale = 0.0;
	this->model->GetScaleXYZ(scale, scale, scale);
	return scale;
}

void ModelObj::SetScale(float s)
{
	if (s == 0.0f)
		model->SetScaleXYZ(1, 1, 1);
	else
		model->SetScaleXYZ(s, s, s);
}

void ModelObj::ToLargerOrSmaller(bool larger)
{
	D3DXVECTOR3 scale;
	model->GetScaleXYZ(scale.x, scale.y, scale.z);
	if (larger)
		scale.x += 0.5f;
	else
		scale.x -= 0.5f;
	
	SetScale(scale.x);
}

bool ModelObj::LoadFromFile(const char *lpszFile)
{
	mFilePath = lpszFile;
	if (!TObjectInfo::LoadFromFile(lpszFile))
		return false;

	SetScale();
	ApplyTransform();

	if (mIsAvatar)
		mAvatar = new Avatar(this);

	wxFileName fn(lpszFile);
	mFileName = fn.GetName() + wxT("." ) + fn.GetExt();
	mFileFolder = fn.GetPath();

	mFrameRange[0] = 0;
	mFrameRange[1] = model->GetFrameCount();
	return true;
}

void ModelObj::ApplyTransform()
{
	model->UseTexture();
	model->UpdateTransform();

	this->CreateFloorAndCollision();
}

BOOL ModelObj::SaveToFile()
{
	IMex *mex = model->GetMex();
	return mex->SaveToFile(mFilePath.c_str(), 0);
}

void ModelObj::RenderAvatar()
{
	if (mIsAvatar)
		mAvatar->Render(this->model);
}

void ModelObj::RenderSkeleton()
{
	static Vector pos[10240];

	IRenderer *r = mRH->mRenderer;
	if (r == NULL)
		return;

	IMex *mex = model->GetMex();
	if (mex == NULL)
		return;

	IMexSkeleton *skeleton = mex->GetSkeleton();
	if (skeleton == NULL)
		return;

	for (int i = 0; i < skeleton->GetBoneCount(); ++i)
	{
		IMexBone *bone = skeleton->GetBone(i);
		int curFrame = model->GetFrameId() % model->GetFrameCount();

		MeMatrix *mat = (MeMatrix *) bone->GetMatricesFromKeyTime(curFrame * ONEFRAMEINTERVAL, FRAMEPERSEC);

		pos[i] = Vector(mat->m[3][0], mat->m[3][1], mat->m[3][2]);
	}

	r->SetTexture(0, NULL);
	r->SetFVF(D3DFVF_XYZ);
	r->SetRenderState(D3DRS_ZENABLE, FALSE);
	r->Commit();

	for (int i = 0; i < skeleton->GetBoneCount(); ++i)
	{		
		Vector line[2];
		line[0] = pos[i];
		IMexBone* pBone = skeleton->GetBone(i);
		for (int j = 0; j < pBone->GetChildCount(); ++j)
		{
			// 画出骨骼之间的连线
			line[1] = pos[pBone->GetChildId(j)];
			r->DrawPrimitiveUP(D3DPT_LINELIST, 1, line, sizeof(Vector));
		}
	}
}