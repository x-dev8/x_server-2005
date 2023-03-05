#pragma once

#include "Avatar.h"
#include "RenderHelper.h"

/*
 * ��ģ���ļ��ķ�װ��
 */
class ModelObj : public TObjectInfo
{
public:
	ModelObj(RenderHelper *rh, bool isAvatar = true);
	virtual ~ModelObj();

public:
	/*
	 * ģ���ļ���
	 */
	const wxString & GetFileName() const { return mFileName; }

	/*
	 * ģ���ļ�Ŀ¼
	 */
	const wxString & GetFileFolder() const { return mFileFolder; }

	/*
	 * ģ���ļ�ȫ·��
	 */
	const std::string & GetFilePath() const { return mFilePath; }

	/*
	 * ��ȡģ��ID
	 */
	int GetModelID() { return model->GetModelID(); }

	/*
	 * ��ȡAvatar
	 */
	Avatar * GetAvatar() { return mAvatar; }

	/*
	 * �Ƿ���ͣ����
	 */
	void SetPause(bool pause, int frameID);

	// ��ȡRenderer
	IRenderer * GetRenderer() { return mRH->mRenderer; }

	/*
	 * ģ����֡��
	 */
	int GetFrameCount();

	/*
	 * �з�������ӷ�����
	 */
	bool HasParticleEmitters();

	/*
	 * ��ȡ����
	 */
	float GetScale();

	/*
	 * ��������
	 */
	void SetScale(float s = 0.0f);

	/*
	 * ��ȡ֡��Χ
	 */
	void GetFrameRange(int *start, int *end) { *start = mFrameRange[0]; *end = mFrameRange[1]; }

	/*
	 * �Բ�����ʽ����ģʽ����ģ��
	 */
	void ToLargerOrSmaller(bool larger);

	/*
	 * Ӧ�ñ任
	 */
	void ApplyTransform();

	/*
	 * ����ģ���ļ�
	 */
	BOOL SaveToFile();

	/*
	 * ��Ⱦ
	 */
	void Render() { model->Render(1.0); }

	/*
	 * ��ȾAvatar
	 */
	void RenderAvatar();

	/*
	 * ��ȾSkeleton
	 */
	void RenderSkeleton();

public:
	/*
	 * ���ļ��м���ģ��
	 */
	virtual bool LoadFromFile(const char *lpszFile);

protected:
	RenderHelper *mRH;

	bool mIsAvatar;
	Avatar *mAvatar;

	wxString mFileName;
	wxString mFileFolder;
	std::string mFilePath;

	// ����֡�ķ�Χ
	int mFrameRange[2];
};