#ifndef _particleemittersetting_h
#define _particleemittersetting_h

#include <windows.h>
#include <vector>
#include <max.h>

#include "defines.h"
#include "UIComponents.h"

class HR3D_Mdx2Candidate;
class ParticleEmitter;
class ParticleEmitterSettingDlg : public UIComponents
{
public:
	enum Field
	{
		eCount, eSpeed, eVaration, eConeAngle, eLife, eParts, eSquirt, eWidth, eHeight, eLineEmitter,eBlendMode,
		eTextureName, eTextureNameButton, eRow, eCol, eUnshaded, eSortZ, eUnfogged, eParticlePart, eTailLength,
		eStart, eMiddle, eEnd, eColorStart, eColorMiddle, eColorEnd, eAlphaStart, eAlphaMiddle, eAlphaEnd, eScaleStart,
		eScaleMiddle, eScaleEnd, eUVAnimFps, eLifeSpanHeadUVAnimStart, eLifeSpanHeadUVAnimEnd, eLifeSpanHeadUVAnimRepeat,
		eDecayHeadUVAnimStart, eDecayHeadUVAnimEnd, eDecayHeadUVAnimRepeat, eLifeSpanTailUVAnimStart, eLifeSpanTailUVAnimEnd,
		eLifeSpanTailUVAnimRepeat, eDecayTailUVAnimStart, eDecayTailUVAnimEnd, eDecayTailUVAnimRepeat, eParticlesInModelSpace,
		eGravity, eBindPartName, eLockEmitter, eUseTimeBasedCell, eSeqLoopTimes, eXYQuad,

		// 新增15个参数
		eRotate, eRotateCost, eRandomDir, eFollowEmitter, eVertexColorInv, eRotateFollowDir,
		eTailChange, eTailChangeStart, eTailChangeMiddle, eTailChangeEnd, eLaydownInWorld, eRandomFirstCell,
		eLifeMax, eScaleMin, eScaleMax,

		eFieldMax
	};
public:
	ParticleEmitterSettingDlg();
	void DefaultSetting();

	BOOL SaveToFile(const char* pszFilename);
	void SaveToNode(INode* pNode);
	void LoadFromNode(INode* pNode);

	void RefreshAllComponentUI();
	void RefreshComponentUI( Component* c );
	BOOL Convert( const char* s, DWORD* value );

	void GetSetting( Mex2ParticleEmitterSetting4* pSetting, void *particleEmitter);

	LRESULT	MsgProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
public:

	HWND m_hWnd;
};

extern ParticleEmitterSettingDlg g_emitterSetting;
#endif