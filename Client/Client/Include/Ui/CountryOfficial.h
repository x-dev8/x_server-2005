/********************************************************************
	Created by UIEditor.exe
	FileName: D:\3Guo_Client_02.05\Data\Ui\CountryOfficial.h
*********************************************************************/
#pragma once
#include "MeUi/MeUi.h"
#include "UiBase.h"
#include "CountryBaseInfo.h"
#include "Player.h"
#ifndef ID_FRAME_Official
#define ID_FRAME_Official		"ID_FRAME_Official"
#endif  ID_FRAME_Official
#ifndef ID_TEXT_CouncilorLeft
#define ID_TEXT_CouncilorLeft		"ID_TEXT_CouncilorLeft"
#endif  ID_TEXT_CouncilorLeft
#ifndef ID_TEXT_CaptorRight
#define ID_TEXT_CaptorRight		"ID_TEXT_CaptorRight"
#endif  ID_TEXT_CaptorRight
#ifndef ID_TEXT_CaptorLeft
#define ID_TEXT_CaptorLeft		"ID_TEXT_CaptorLeft"
#endif  ID_TEXT_CaptorLeft
#ifndef ID_TEXT_General
#define ID_TEXT_General		"ID_TEXT_General"
#endif  ID_TEXT_General
#ifndef ID_TEXT_Queen
#define ID_TEXT_Queen		"ID_TEXT_Queen"
#endif  ID_TEXT_Queen
#ifndef ID_TEXT_King
#define ID_TEXT_King		"ID_TEXT_King"
#endif  ID_TEXT_King
#ifndef ID_TEXT_CouncilorRight
#define ID_TEXT_CouncilorRight		"ID_TEXT_CouncilorRight"
#endif  ID_TEXT_CouncilorRight
#ifndef ID_BUTTON_CouncilorRight
#define ID_BUTTON_CouncilorRight		"ID_BUTTON_CouncilorRight"
#endif  ID_BUTTON_CouncilorRight
#ifndef ID_BUTTON_CaptorRight
#define ID_BUTTON_CaptorRight		"ID_BUTTON_CaptorRight"
#endif  ID_BUTTON_CaptorRight
#ifndef ID_BUTTON_CaptorLeft
#define ID_BUTTON_CaptorLeft		"ID_BUTTON_CaptorLeft"
#endif  ID_BUTTON_CaptorLeft
#ifndef ID_BUTTON_General
#define ID_BUTTON_General		"ID_BUTTON_General"
#endif  ID_BUTTON_General
#ifndef ID_BUTTON_Queen
#define ID_BUTTON_Queen		"ID_BUTTON_Queen"
#endif  ID_BUTTON_Queen
#ifndef ID_BUTTON_King
#define ID_BUTTON_King		"ID_BUTTON_King"
#endif  ID_BUTTON_King
#ifndef ID_BUTTON_CouncilorLeft
#define ID_BUTTON_CouncilorLeft		"ID_BUTTON_CouncilorLeft"
#endif  ID_BUTTON_CouncilorLeft

#ifndef ID_PICTURE_CouncilorLeft
#define ID_PICTURE_CouncilorLeft		"ID_PICTURE_CouncilorLeft"
#endif  ID_PICTURE_CouncilorLeft
#ifndef ID_PICTURE_CouncilorRight
#define ID_PICTURE_CouncilorRight		"ID_PICTURE_CouncilorRight"
#endif  ID_PICTURE_CouncilorRight
#ifndef ID_PICTURE_King
#define ID_PICTURE_King		"ID_PICTURE_King"
#endif  ID_PICTURE_King
#ifndef ID_PICTURE_Queen
#define ID_PICTURE_Queen		"ID_PICTURE_Queen"
#endif  ID_PICTURE_Queen
#ifndef ID_PICTURE_General
#define ID_PICTURE_General		"ID_PICTURE_General"
#endif  ID_PICTURE_General
#ifndef ID_PICTURE_CaptorLeft
#define ID_PICTURE_CaptorLeft		"ID_PICTURE_CaptorLeft"
#endif  ID_PICTURE_CaptorLeft
#ifndef ID_PICTURE_CaptorRight
#define ID_PICTURE_CaptorRight		"ID_PICTURE_CaptorRight"
#endif  ID_PICTURE_CaptorRight

#ifndef ID_PICTURE_28124
#define ID_PICTURE_28124		"ID_PICTURE_28124" //亲王
#endif  ID_PICTURE_28124
#ifndef ID_PICTURE_21540
#define ID_PICTURE_21540		"ID_PICTURE_21540" //王后
#endif  ID_PICTURE_21540

#ifndef ID_BUTTON_DelOff
#define ID_BUTTON_DelOff		"ID_BUTTON_DelOff"
#endif  ID_BUTTON_DelOff

class CUI_ID_FRAME_Official : public CUIBase
{
	// Member
public:	
	 CUI_ID_FRAME_Official();
	 ControlFrame*	m_pID_FRAME_Official;
	 ControlText*	m_pID_TEXT_CouncilorLeft;
	 ControlText*	m_pID_TEXT_CaptorRight;
	 ControlText*	m_pID_TEXT_CaptorLeft;
	 ControlText*	m_pID_TEXT_General;
	 ControlText*	m_pID_TEXT_Queen;
	 ControlText*	m_pID_TEXT_King;
	 ControlText*	m_pID_TEXT_CouncilorRight;
	 ControlButton*	m_pID_BUTTON_CouncilorRight;
	 ControlButton*	m_pID_BUTTON_CaptorRight;
	 ControlButton*	m_pID_BUTTON_CaptorLeft;
	 ControlButton*	m_pID_BUTTON_General;
	 ControlButton*	m_pID_BUTTON_Queen;
	 ControlButton*	m_pID_BUTTON_King;
	 ControlButton*	m_pID_BUTTON_CouncilorLeft;
	 ControlButton*	m_pID_BUTTON_DelOff;

	 
	 ControlPicture*	m_pID_PICTURE_CouncilorLeft;
	 ControlPicture*	m_pID_PICTURE_CouncilorRight;
	 ControlPicture*	m_pID_PICTURE_King;
	 ControlPicture*	m_pID_PICTURE_Queen;
	 ControlPicture*	m_pID_PICTURE_General;
	 ControlPicture*	m_pID_PICTURE_CaptorLeft;
	 ControlPicture*	m_pID_PICTURE_CaptorRight;

	 ControlPicture*	m_pID_PICTURE_28124;
	 ControlPicture*	m_pID_PICTURE_21540;


	// Frame
	bool OnFrameRun();
	bool OnFrameRender();
	bool ID_BUTTON_CouncilorRightOnButtonClick( ControlObject* pSender );

	bool ID_BUTTON_CaptorRightOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CaptorLeftOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_GeneralOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_QueenOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_KingOnButtonClick( ControlObject* pSender );
	bool ID_BUTTON_CouncilorLeftOnButtonClick( ControlObject* pSender );

	bool ID_BUTTON_DelOffOnButtonClick( ControlObject* pSender );

	virtual bool _LoadUI();				// 载入UI
	bool DoControlConnect();	// 关连控件
	virtual bool _UnLoadUI();			// 卸载UI
	virtual bool _IsVisable();			// 是否可见
	virtual void _SetVisable( const bool bVisable );			// 设置是否可视
	virtual void InitializeAtEnterWorld();
	void DestroyAnimCtrl();
	void Reset();

	BOOL InitCamera();

	void OnInitUIInfo();
private:
	void UpdateCountryOfficialDisPlayer();
	void RanderPlayerMode(int idx,ESexType sex,uint16 faceID,uint16 headerID,uint32 equipID,uint16 professionID,ControlObject* pSender);
	void ResetProperties();
	void RenderPlayers( ControlPicture* checkBox, const int idx );
private:
	//国家官员渲染状态
	CountryPlayerDisPlayer	m_CountryOfficialDisPlayer[CountryDefine::Position_Max];


	CPlayerAnim*			m_PlayerAnims[CountryDefine::Position_Max];
	CPlayer*				m_pPlayers[CountryDefine::Position_Max];


	MeCamera			m_Camera;
	D3DVIEWPORT9		m_ViewPort;
	float m_fRotateZ;
	bool m_bRotate;
	float m_fLightTry1;
	float m_fLightTry2;
	float m_fLightTry3;
};
extern CUI_ID_FRAME_Official s_CUI_ID_FRAME_Official;
