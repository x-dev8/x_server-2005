#pragma once
#include <MeFoundation/MeTimelineShadeEvent.h>

class CHeightMapData;

/**
* @brief 下雨类特效。
*/
class MEFOUNDATION_ENTRY MeTimelineRainyEvent : public MeTimelineShadeEvent
{
// Defines.
protected:
	/// Rain's Vertex Definition.
	struct MeRainVertex
	{
		enum { RainVertexFVF = D3DFVF_XYZ | D3DFVF_TEX1 };
		Vector m_kPosition;		// 位置
		Vector2 m_kUV;			// UV
	};

	/// RainSpray's Vertex Definition.
	struct MeRainSprayVertex
	{
		enum{ RainSprayVertexFVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1 };
		Vector m_kPosition;		
		DWORD m_kColor;
		Vector2 m_kUV;
	};

	/// RainSpray's visible structure.
	struct RainSprayVisible
	{
		bool m_bVisible;
		MeTimeValue m_kStartTime;
	};

// Construction.
public:	
	/// Constructor.
	MeTimelineRainyEvent(){}

	/// Copy constructor.
	MeTimelineRainyEvent( const MeTimelineRainyEvent& kClass ){}

// Overload operator.
public:
	/// Assignment operator.
	const MeTimelineRainyEvent& operator=( const MeTimelineRainyEvent& kClass ){ return *this; }

// Override.
public:
	/// Destructor.
	virtual ~MeTimelineRainyEvent(){}

	/// Initialize.
	virtual void InitializeEvent();

	/// Destroy.
	virtual void DestroyEvent();

	/// Reset.
	virtual void ResetEvent();

	/// Render.
	virtual void RenderEvent(const Vector &playerPos);

	/// 从无到有的更新。
	virtual void UpdateBeginToFull( const MeTimeValue& kTime );

	/// 完全变化时的更新。
	virtual void UpdateInFull( const MeTimeValue& kTime );

	/// 从有到无的更新。
	virtual void UpdateFullToEnd( const MeTimeValue& kTime );

// Methods.
public:
	/// 设置文件名。
	static void SetRainTextureFilename( const std::string& strFilename ){ ms_strRainTextureFilename = strFilename; }

	/// 设置雨点范围。
	static void SetRainyRange( int nRange ){ ms_nRainyRange = nRange; }

	/// 设置雨点下落速度。
	static void SetRainySpeed( float fSpeed ){ ms_fRainSpeed = fSpeed; }

	/// 设置雨点长度。
	static void SetRaindropHeight( float fHeight ){ ms_fRaindropHeight = fHeight; }

	/// 设置当前原点位置。
	static void SetCurrentPosition( const Vector& rkPos ){ ms_kPosition = rkPos; }

// Methods.
protected:
	/// 生成雨水顶点。
	void GenerateRainVertex( int nStartPosition, float fRadius );

	/// 更新雨滴z轴信息。
	void UpdateRainVertexZ( unsigned int uiCount, const MeTimeValue& kTimeValue );

	/// 更新水花UV和颜色信息。
	void UpdateRainSprayUVnColor( unsigned int uiCount, const MeTimeValue& kTimeValue );

	/// 更新水花位置信息。
	void UpdateRainSprayPosition( int nVertexIndex, int nSprayIndex, const MeTimeValue& kTimeValue, CHeightMapData* pHeightData );

	/// 渲染水滴。
	void RenderRainSpray();

	/// 渲染雨水。
	void RenderRain();

	/// 获得一个随机的z方向偏移。
	float GetRandomZOffsetValue();

// Static Members.
public:
	/// 雨点数。
	static const int ms_ncRainDropCount = 2000;

	/// 雨点顶点数。
	static const int ms_ncRainVecticesCount = ms_ncRainDropCount * 3;

	/// 水花顶点数。
	static const int ms_ncRainSprayVecticesCount = ms_ncRainDropCount * 3;

// Members.
protected:
	/// 水滴顶点。
	static MeRainVertex ms_kRainVertices[ms_ncRainVecticesCount];

	/// 水花顶点偏移。
	static Vector ms_kRainSprayVerticesOffset[ms_ncRainSprayVecticesCount];

	/// 水花顶点。
	static MeRainSprayVertex ms_kRainSprayVertices[ms_ncRainSprayVecticesCount];

	/// 水花顶点是否正在显示标志位。
	static RainSprayVisible ms_bRainSprayVisible[ms_ncRainDropCount];

	/// 当前渲染顶点数。
	static int ms_nRenderCount;

	/// 雨点贴图id。
	static int ms_nRainTextureId;

	/// 水花贴图id。
	static int ms_nRainSprayTextureId;

	/// 当前原点位置。
	static Vector ms_kPosition;

	/* 可配置参数。 */ 

	/// 雨点贴图。
	static std::string ms_strRainTextureFilename;

	/// 地面水花贴图。
	static std::string ms_strRainSprayTextureFilename;

	/// 雨点范围。
	static int ms_nRainyRange;

	/// 雨点下落速度。
	static float ms_fRainSpeed;

	/// 一个雨点的高度。
	static float ms_fRaindropHeight;
};