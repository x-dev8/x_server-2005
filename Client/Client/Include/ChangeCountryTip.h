#pragma once

class CChangeCountryTips
{
public:
	//enum ECountryTip
	//{
	//	ECountry_No,
	//	ECountry_Shu,
	//	ECountry_Wei,
	//	ECountry_Wu,
	//};
	struct TipsInfo 
	{
		RECT rtImgSrc;
		short shWidth;
		short shHeight;
		short shMinWidth;
		short shMinHeight;
		short shFrameNum;
		short shEndFlashFrame;
		short shRenderType;
		short shOffsetX;
		short shOffsetY;
		bool bSpeed;
		std::string strSound;
	};
	struct RenderTips
	{
		TipsInfo info;
		short shWidth;
		short shHeight;
		short shMinWidth;
		short shMinHeight;
		short shCurrFrame;
		unsigned int nStartTime;
		unsigned int nAlphaColor;
		bool bFlash;
		int nFlashNum;
		DWORD dwLastFrmTime;
	};
	CChangeCountryTips();
	~CChangeCountryTips();
	static CChangeCountryTips& Instance()
	{
		static CChangeCountryTips s;
		return s;
	}
	void InitTips();
	void RegisterTipsTexture();
	void UnRegisterTipsTexture();
	void AddTips(short shTipsNum);
	void Render();

private:
	short m_shTipsTexture;
	std::map<short, TipsInfo> m_mapTipsInfo;
	std::vector<RenderTips> m_vRenderTips;
	short m_shCurrTips;
	short m_shCurrRenderStep;
	UINT  m_srcWidth;
	UINT  m_srcHeight;
	bool m_bStopRender;
};

#define theCountryTipInstance	CChangeCountryTips::Instance()