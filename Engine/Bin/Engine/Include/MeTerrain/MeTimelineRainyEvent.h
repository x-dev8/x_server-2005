#pragma once
#include <MeFoundation/MeTimelineShadeEvent.h>

class CHeightMapData;

/**
* @brief ��������Ч��
*/
class MEFOUNDATION_ENTRY MeTimelineRainyEvent : public MeTimelineShadeEvent
{
// Defines.
protected:
	/// Rain's Vertex Definition.
	struct MeRainVertex
	{
		enum { RainVertexFVF = D3DFVF_XYZ | D3DFVF_TEX1 };
		Vector m_kPosition;		// λ��
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

	/// ���޵��еĸ��¡�
	virtual void UpdateBeginToFull( const MeTimeValue& kTime );

	/// ��ȫ�仯ʱ�ĸ��¡�
	virtual void UpdateInFull( const MeTimeValue& kTime );

	/// ���е��޵ĸ��¡�
	virtual void UpdateFullToEnd( const MeTimeValue& kTime );

// Methods.
public:
	/// �����ļ�����
	static void SetRainTextureFilename( const std::string& strFilename ){ ms_strRainTextureFilename = strFilename; }

	/// ������㷶Χ��
	static void SetRainyRange( int nRange ){ ms_nRainyRange = nRange; }

	/// ������������ٶȡ�
	static void SetRainySpeed( float fSpeed ){ ms_fRainSpeed = fSpeed; }

	/// ������㳤�ȡ�
	static void SetRaindropHeight( float fHeight ){ ms_fRaindropHeight = fHeight; }

	/// ���õ�ǰԭ��λ�á�
	static void SetCurrentPosition( const Vector& rkPos ){ ms_kPosition = rkPos; }

// Methods.
protected:
	/// ������ˮ���㡣
	void GenerateRainVertex( int nStartPosition, float fRadius );

	/// �������z����Ϣ��
	void UpdateRainVertexZ( unsigned int uiCount, const MeTimeValue& kTimeValue );

	/// ����ˮ��UV����ɫ��Ϣ��
	void UpdateRainSprayUVnColor( unsigned int uiCount, const MeTimeValue& kTimeValue );

	/// ����ˮ��λ����Ϣ��
	void UpdateRainSprayPosition( int nVertexIndex, int nSprayIndex, const MeTimeValue& kTimeValue, CHeightMapData* pHeightData );

	/// ��Ⱦˮ�Ρ�
	void RenderRainSpray();

	/// ��Ⱦ��ˮ��
	void RenderRain();

	/// ���һ�������z����ƫ�ơ�
	float GetRandomZOffsetValue();

// Static Members.
public:
	/// �������
	static const int ms_ncRainDropCount = 2000;

	/// ��㶥������
	static const int ms_ncRainVecticesCount = ms_ncRainDropCount * 3;

	/// ˮ����������
	static const int ms_ncRainSprayVecticesCount = ms_ncRainDropCount * 3;

// Members.
protected:
	/// ˮ�ζ��㡣
	static MeRainVertex ms_kRainVertices[ms_ncRainVecticesCount];

	/// ˮ������ƫ�ơ�
	static Vector ms_kRainSprayVerticesOffset[ms_ncRainSprayVecticesCount];

	/// ˮ�����㡣
	static MeRainSprayVertex ms_kRainSprayVertices[ms_ncRainSprayVecticesCount];

	/// ˮ�������Ƿ�������ʾ��־λ��
	static RainSprayVisible ms_bRainSprayVisible[ms_ncRainDropCount];

	/// ��ǰ��Ⱦ��������
	static int ms_nRenderCount;

	/// �����ͼid��
	static int ms_nRainTextureId;

	/// ˮ����ͼid��
	static int ms_nRainSprayTextureId;

	/// ��ǰԭ��λ�á�
	static Vector ms_kPosition;

	/* �����ò����� */ 

	/// �����ͼ��
	static std::string ms_strRainTextureFilename;

	/// ����ˮ����ͼ��
	static std::string ms_strRainSprayTextureFilename;

	/// ��㷶Χ��
	static int ms_nRainyRange;

	/// ��������ٶȡ�
	static float ms_fRainSpeed;

	/// һ�����ĸ߶ȡ�
	static float ms_fRaindropHeight;
};