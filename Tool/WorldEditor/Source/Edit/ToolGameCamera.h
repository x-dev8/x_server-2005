/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	ToolGameCamera.h
* Create: 	10/13/06
* Desc:		
* Author:	Yuan ding
*
* Modify:
* Modify by:
*******************************************************************************/

#ifndef __TOOL_GAME_CAMERA_H__
#define __TOOL_GAME_CAMERA_H__

#include "BaseTool.h"
////////////////////////////////////////////////////////////////////////////////
class CToolGameCamera	: public CBaseTool
{
public:
    friend class GameCamera;
					CToolGameCamera();
	virtual			~CToolGameCamera();
				
	virtual ToolID	GetToolId()	{ return TOOL_GAMECAMERA; };

	virtual bool	Create( CToolManager* toolMgr );

	virtual	void	SetActive( bool isActive = true );

	virtual void	Render();

	virtual bool	OnLMouseDown( UINT nFlags, CPoint point );
	virtual bool	OnLMouseUp( UINT nFlags, CPoint point );
	virtual bool	OnLMouseDblClk( UINT nFlags, CPoint point );
	virtual bool	OnRMouseDown( UINT nFlags, CPoint point );
	virtual bool	OnRMouseUp( UINT nFlags, CPoint point );
	virtual bool	OnMouseMove( UINT nFlags, CPoint point );
	virtual bool	OnMouseWheel( UINT nFlags, short zDelta, CPoint point);
	virtual bool	OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags );
	virtual bool	OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags );

    void            AttachModel();
    void            DetalModel();
    bool            LoadMode();

	void            InitModelAndCamera();

    void            SetCameraPos(Vector &pos);    //������ת�Ƕ�
    void            SetViewPoint(Vector &point);  //���ù۲��
 
    bool			CameraAdjust( CPoint point, UINT nFlags );
protected:			
	bool			m_bInit;
	flt32			m_position[3];
public:
    struct Player 
    {
         TObjectEditInfo     m_Hero;       //��������ģ��
         Vector          m_position;   // ���ǵ�λ��
         flt32           m_Scale;      //���ǵ�ģ������
         flt32           m_Rot;        //��Z�����ת�Ƕ�
         Player()
         {
             m_position = Vector(0.0f,0.0f,0.0f);
             m_Scale = 1.0f;
             m_Rot   = /*18*/0.0f;
         }

         void  SetPosition(Vector &Pos)
         {
             m_position = Pos;
             m_Hero.model->SetPosition(Pos);
         }
         Vector& GetPosition(){return m_position;}

         void SetScale(flt32 fScale)
         {
             m_Scale = fScale;
             m_Hero.model->SetScale(fScale * GetMe3dConfig()->m_fMdlSpaceScale);
         }
         flt32 GetScale(){return m_Scale;}


         bool LoadModel(const char* pszFilePath)
         {
             assert(pszFilePath != NULL);
             return m_Hero.LoadFromFile(pszFilePath);
         }

         void SetDir(flt32 fDir)
         {
             m_Rot /*+*/= fDir;
             if(m_Hero.model != NULL)
             {
                m_Hero.model->SetRotationZ(m_Rot/*(float)((m_Rot + 180.0f) * PI)/(float)(180)*/);
             }
         }

         flt32 GetDir(flt32 fDir){return m_Rot;}

         bool IsNeedLoadModel(){return (m_Hero.model == NULL);}
    };
protected:
        Player          m_Player; 

        enum eum_Action
        {
            eum_Idle,  //Idle״̬
            eum_Walk   //��·״̬
        };
public:
       void SetAction(eum_Action eumValue);   //����Action
       void ChangeAction();                   //�ı䶯��״̬
private:
        struct AnimControl
        {
           eum_Action  m_eumState;         //��Ҫ�ı�Ķ���״̬
           std::string  m_CurrAction;      //��ǰ���ŵĶ���״̬

           AnimControl()
           {
               m_eumState = eum_Idle;
               m_CurrAction = "Idle";
           }
        };

        AnimControl m_animAction;      //Action������

public:
	void SetOffsetCamera(int iOffset)
	{
		m_iOffsetCamera=iOffset;
	}
private:
	int					m_iOffsetCamera;    // ��������˵�ƫ��ֵ, �ܹ��ֿ��� //&& add by pyj
};




#endif //__TOOL_GAME_CAMERA_H__