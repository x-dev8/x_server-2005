#pragma once

class CDuelTips 
{
public:
    enum
    {
        RENDER_WILK,
        RENDER_SPLIT
    };
	enum
	{
		Image_START_FIGHT = 0,
		Image_NUMBER_1,
		Image_NUMBER_2,
		Image_NUMBER_3,
		Image_FIGHT_WIN,
		Image_FIGHT_LOSE,
	};
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
    };
public:
    CDuelTips(void);
    ~CDuelTips(void);

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