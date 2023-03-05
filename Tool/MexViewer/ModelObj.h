#pragma once

#include "Avatar.h"
#include "RenderHelper.h"

/*
 * 对模型文件的封装类
 */
class ModelObj : public TObjectInfo
{
public:
	ModelObj(RenderHelper *rh, bool isAvatar = true);
	virtual ~ModelObj();

public:
	/*
	 * 模型文件名
	 */
	const wxString & GetFileName() const { return mFileName; }

	/*
	 * 模型文件目录
	 */
	const wxString & GetFileFolder() const { return mFileFolder; }

	/*
	 * 模型文件全路径
	 */
	const std::string & GetFilePath() const { return mFilePath; }

	/*
	 * 获取模型ID
	 */
	int GetModelID() { return model->GetModelID(); }

	/*
	 * 获取Avatar
	 */
	Avatar * GetAvatar() { return mAvatar; }

	/*
	 * 是否暂停播放
	 */
	void SetPause(bool pause, int frameID);

	// 获取Renderer
	IRenderer * GetRenderer() { return mRH->mRenderer; }

	/*
	 * 模型总帧数
	 */
	int GetFrameCount();

	/*
	 * 有否存在粒子发射器
	 */
	bool HasParticleEmitters();

	/*
	 * 获取缩放
	 */
	float GetScale();

	/*
	 * 设置缩放
	 */
	void SetScale(float s = 0.0f);

	/*
	 * 获取帧范围
	 */
	void GetFrameRange(int *start, int *end) { *start = mFrameRange[0]; *end = mFrameRange[1]; }

	/*
	 * 以步进方式缩放模式缩放模型
	 */
	void ToLargerOrSmaller(bool larger);

	/*
	 * 应用变换
	 */
	void ApplyTransform();

	/*
	 * 保存模型文件
	 */
	BOOL SaveToFile();

	/*
	 * 渲染
	 */
	void Render() { model->Render(1.0); }

	/*
	 * 渲染Avatar
	 */
	void RenderAvatar();

	/*
	 * 渲染Skeleton
	 */
	void RenderSkeleton();

public:
	/*
	 * 从文件中加载模型
	 */
	virtual bool LoadFromFile(const char *lpszFile);

protected:
	RenderHelper *mRH;

	bool mIsAvatar;
	Avatar *mAvatar;

	wxString mFileName;
	wxString mFileFolder;
	std::string mFilePath;

	// 保存帧的范围
	int mFrameRange[2];
};