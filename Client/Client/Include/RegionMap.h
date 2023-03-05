#ifndef REGION_MAP_INC

#define REGION_MAP_INC


#include "MiniMap.h"

class CRegionMap : public CAdvancedMiniMap
{

public:
	struct RegionMapImage 
	{
		RegionMapImage()
		{
			nImageType = -1;
			nPlayerId = -1;
			pInfo = NULL;
		}
		float GetX();
		float GetY();
		const char* GetName();
        int GetLevel();
        bool IsMonster();
		int nImageType;
		NpcCoordInfo* pInfo;
		GameObjectId nPlayerId;
	};
	void						SetUpdateStableImage(bool val) { m_bUpdateStableImage = val; }
	void						AddRegionMapImage(int nImage,NpcCoordInfo* pInfo,GameObjectId nPlayerId = -1);
	// ��ͼ���
	enum
	{
		eMarkType_None,				// ����
		eMarkType_TellNpcPos,		// ��ʾnpc��λ��
		eMarkType_Helper,
	};
	struct Mark
	{
		int		nType;				// ����
		DWORD	dwBornTime;			// ����ʱ�䣬��λ����
		DWORD	dwLife;				// ��������λ����
		BOOL	bFlicker;			// �Ƿ���˸
		int		x, y;				// �ڵ�ͼ�ϵ�λ�ã���λ���񣬲�������
		char	szText[eMaxMarkText];
		Mark()
		{
			nType = eMarkType_None;
			dwBornTime = 0;
			dwLife = 0;
			bFlicker = FALSE;
			x = 0;
			y = 0;
		}
	};
private:
public:
	CRegionMap();
	~CRegionMap();


	BOOL		AddMark( Mark* pMark );

	BOOL		MarkNpcPosByID( int nNpcID );
	void		RenderRegionMap( RECT rcWindow,RECT rcSrc, int nMapId, float nRoleX, float nRoleY,float fPixelPerRealDis,int xPixelOffset,int yPixelOffset);
	void		DrawImageOnRegionMap(RECT rcWindow,RECT rcSrc,int nMapId, float nRoleX, float nRoleY ,float fPixelPerRealDis,int xPixelOffset,int yPixelOffset);


	bool		IsMatchShowOption(int nImageType);
	RegionMapImage* GetNpcCursorOn() const { return m_pNpcCursorOn; }
	bool		IsOutSide(RECT& rcWindow,RECT& rcDes);

protected:
	Mark		m_marks[eMaxMark];

	int nTargetFrameIndex;
	std::list<RegionMapImage>			m_currRegionMapImageList;
	int								m_RegionStableImageIndex;
	bool								m_bUpdateStableImage;
	int								m_nRegionMapId;


	RegionMapImage* m_pNpcCursorOn;
	std::string m_strTargetNpc;
	bool m_ShowTeamTip;

	HDC m_hMonsterDC;//�������������ͼ������
	int m_nMonsterFont;//
};


extern CRegionMap* GetRegionMap();
#endif