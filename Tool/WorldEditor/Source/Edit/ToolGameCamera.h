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

    void            SetCameraPos(Vector &pos);    //设置旋转角度
    void            SetViewPoint(Vector &point);  //设置观察点
 
    bool			CameraAdjust( CPoint point, UINT nFlags );
protected:			
	bool			m_bInit;
	flt32			m_position[3];
public:
    struct Player 
    {
         TObjectEditInfo     m_Hero;       //用于主角模型
         Vector          m_position;   // 主角的位置
         flt32           m_Scale;      //主角的模型缩放
         flt32           m_Rot;        //绕Z轴的旋转角度
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
            eum_Idle,  //Idle状态
            eum_Walk   //走路状态
        };
public:
       void SetAction(eum_Action eumValue);   //设置Action
       void ChangeAction();                   //改变动画状态
private:
        struct AnimControl
        {
           eum_Action  m_eumState;         //需要改变的动画状态
           std::string  m_CurrAction;      //当前播放的动画状态

           AnimControl()
           {
               m_eumState = eum_Idle;
               m_CurrAction = "Idle";
           }
        };

        AnimControl m_animAction;      //Action控制器

public:
	void SetOffsetCamera(int iOffset)
	{
		m_iOffsetCamera=iOffset;
	}
private:
	int					m_iOffsetCamera;    // 摄象机与人的偏移值, 受滚轮控制 //&& add by pyj
};




#endif //__TOOL_GAME_CAMERA_H__