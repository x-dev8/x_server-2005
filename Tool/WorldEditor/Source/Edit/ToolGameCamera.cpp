/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	ToolGameCamera.cpp
* Create: 	10/13/06
* Desc:		
* Author:	Yuan Ding
*
* Modify:
* Modify by:
*******************************************************************************/

#include "stdafx.h"
#include "ToolGameCamera.h"
#include "EditRender/GameCamera.h"
#include "Ndl/NdlHelper.h"
#include "swLuaScript.h"

////////////////////////////////////////////////////////////////////////////////
#define STEP  0.5
#define IDLE   "Idle"
#define RUN    "run"
////////////////////////////////////////////////////////////////////////////////
CToolGameCamera::CToolGameCamera()
:
m_bInit(false),
m_iOffsetCamera(30)
{
	memset( m_position, 0, 3*sizeof(flt32) );
}

CToolGameCamera::~CToolGameCamera()
{

}

bool CToolGameCamera::OnLMouseDown( UINT nFlags, CPoint point )
{
	m_isLDrag = true;
	m_oldPos = point; 
	return true;
}

bool CToolGameCamera::OnLMouseUp( UINT nFlags, CPoint point )
{
	m_isLDrag = false;

	return true;
}

bool CToolGameCamera::OnLMouseDblClk( UINT nFlags, CPoint point )
{
	return true;
}

bool CToolGameCamera::OnRMouseDown( UINT nFlags, CPoint point )
{
	m_isRDrag = true;
	m_oldPos = point; 
	
	return true;
}

bool CToolGameCamera::OnRMouseUp( UINT nFlags, CPoint point )
{
	m_isRDrag = false;
	return true;
}

bool CToolGameCamera::OnMouseMove( UINT nFlags, CPoint point )
{
	Vector2 viewSize;
	CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetViewSize( viewSize.x, viewSize.y );
	if( viewSize.x < 1 || viewSize.y < 1 )
		return false;

    SwCamera* pCamera = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetActiveCamera();
	CPoint delta = point - m_oldPos;
    //跟随相机变换
	if( m_isRDrag )
    {
        D3DXVECTOR3 lookAt;
        CameraAdjust(point,nFlags);  //调整相机的方向
        Vector rot = pCamera->GetRot();
        //m_Player.SetDir(-rot.z);    //&& 调整摄象机时不再调整人的方向
	}
    else if(m_isLDrag)
    {
        //只是改变视角
        CameraAdjust(point,nFlags);
    }

    pCamera->Update(0.0f,0.0f);

	return true;
}

bool CToolGameCamera::CameraAdjust( CPoint point, UINT nFlags )
{
    CPoint delta		= point - m_oldPos;
    Vector2 viewSize;
    CWorldEditView* view = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
    view->GetViewSize( viewSize.x, viewSize.y );
    SwCamera* camera	= view->GetActiveCamera();
    if( viewSize.x < 1 || viewSize.y < 1 )
        return false;

    Vector deltaRot;	
    //deltaRot.x	= delta.y / viewSize.y * PI;    //&& 调节的是上下
	deltaRot.x  = 0.0f;
    deltaRot.y  = 0.f;
    deltaRot.z	= delta.x / viewSize.x * PI;	//&& 调节的是左右
	
    deltaRot += camera->GetRot();
    camera->SetRot( deltaRot );
    m_oldPos = point;
    return true;
}

// bool CToolGameCamera::OnMouseWheel( UINT nFlags, short zDelta, CPoint point)
// {
// 	Vector2 viewSize;
// 	CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetViewSize( viewSize.x, viewSize.y );
// 	if( viewSize.x < 1 || viewSize.y < 1 )
// 		return false;
// 
// 	Vector deltaPos;
// 	deltaPos.x	= ( zDelta / 64.0f ) * WORLD_SCALE;
// 	deltaPos.y  = 0.0f;
// 	deltaPos.z	= 0.0f;
// 
// 	if( 0 != (nFlags&MK_CONTROL) ) {
// 		deltaPos = deltaPos * CAMERA_HUGE_STEP;
// 	}
// 	
// 	CWorldEditView* pView = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
// 	GameCamera* camera =  dynamic_cast< GameCamera*>(pView->GetActiveCamera());
// 	camera->OnMouseScroll(deltaPos.x);
// 	camera->Update( 0.0f, 0.0f );
// 	
// 	return true;
// }
const float fAngle45=float(45.0f * PI)/float(180.0f);
const float fAngle90=float(90.0f * PI)/float(180.0f);
const float fAngle180=float(180.0f * PI)/float(180.0f);
bool CToolGameCamera::OnKeyDown( UINT nChar, UINT nRepCnt, UINT nFlags )
{
	if (nChar != VK_UP && 'W' != nChar
		&& nChar != VK_DOWN && 'S' != nChar
		&& nChar != VK_LEFT && 'A' != nChar
		&& nChar != VK_RIGHT && 'D' != nChar)
	{
		return false;
	}

    m_animAction.m_eumState = eum_Walk;

	CWorldEditView* pView = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
	GameCamera* camera =  dynamic_cast< GameCamera*>(pView->GetActiveCamera());
// 	Vector cameraSpherical = camera->GetSphericalPos();
// 	float	rfz = -cameraSpherical.y + 0.5 * PI;
// 	NiMatrix3 matRot;
// 	Vector offset(0.f,0.f,0.f);
// 	offset.y = -0.5f;
// 	if( nChar == VK_UP || 'W' == nChar  ) {
// 	}
// 	if( nChar == VK_DOWN || 'S' == nChar  ) {
// 		rfz -= PI ;
// 	}
// 	if( nChar == VK_LEFT || 'A' == nChar  ) {
// 		rfz -= PI * 0.5;
// 	}
// 	if( nChar == VK_RIGHT || 'D' == nChar  ) {
// 		rfz += PI * 0.5;
// 	}
// 	if( rfz > PI )
// 		rfz -= 2*PI;
// 	if( rfz < -PI )
// 		rfz += 2* PI;
// 	Trace("rotate z: %f\n", rfz);
// 	matRot.FromEulerAnglesXYZ(0.f,0.f,rfz);

    Vector		pos			= m_Player.GetPosition();
	//flt32		fCharDir	= m_Player.GetDir(0);
    D3DXVECTOR3 dxDir		= camera->GetDir();
    Vector		rot			= camera->GetRot();                  //摄象机的旋转向量，z表示绕z轴的旋转角度 pi/180
    bool		bMove		= false;
	flt32		fCharDir    = 0.0f;


	D3DXMATRIX    pRotMat;				//用来旋转摄象机的方向
	D3DXVECTOR3   vCameraDir=dxDir;     //摄象机旋转后的方向
    switch(nChar)
    {
    case 'W':
		fCharDir = rot.z+fAngle180;
        vCameraDir *= 0.5f;
        bMove = true;
        break;
    case 'S':
		fCharDir = rot.z;
        vCameraDir *= -0.5f;
		bMove = true;
        break;
    case 'A':
//         rot.z -= 0.03f;
//         camera->SetRot(rot);
		fCharDir = rot.z+fAngle90;
		D3DXMatrixRotationZ(&pRotMat,fAngle90);
		D3DXVec3TransformCoord( &vCameraDir, &dxDir, &pRotMat );
		vCameraDir *= 0.5f;
		bMove = true;
        break;
    case 'D':
//         rot.z += 0.03f;
//         camera->SetRot(rot);
		fCharDir = rot.z-fAngle90;
		D3DXMatrixRotationZ(&pRotMat,-fAngle90);
		D3DXVec3TransformCoord( &vCameraDir, &dxDir, &pRotMat );
		vCameraDir *= 0.5f;
		bMove = true;
        break;
    }

    if(!bMove)
        return true;
   
    pos.x += vCameraDir.x;
    pos.y += vCameraDir.y;

    BOOL bInFloor = false;
    flt32 fHeight = SwGlobal::GetWorldPicker()->GetZByXY(10000.0,pos.x,pos.y,NULL,&bInFloor);
    pos.z = fHeight;

    m_Player.SetPosition(pos);              //设置位置
    //SetCameraPos(pos);                      //设置相机位置
    SetViewPoint(m_Player.GetPosition());   //设置观察点

    //m_Player.SetDir(fCharDir);
	m_Player.m_Hero.model->SetRotationZ(-fCharDir);
    
	return true;
}

bool CToolGameCamera::OnMouseWheel( UINT nFlags, short zDelta, CPoint point)
{
// 	CWorldEditView* pView	=	CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
// 	GameCamera*		camera	=	dynamic_cast< GameCamera*>(pView->GetActiveCamera());
// 	D3DXVECTOR3		vCameraDir	=	camera->GetDir();
// 	Vector	        vCameraPos  =   camera->GetPos();
// 	D3DXVECTOR3 temp = vCameraDir*( zDelta );
// 	vCameraPos.x += temp.x;
// 	vCameraPos.y += temp.y;
// 	vCameraPos.z += temp.z;
// 	camera->SetPos( vCameraPos );

// 	SwCamera* pCamera =  CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetActiveCamera();
// 	if(pCamera)
// 	{
// 		D3DXVECTOR3 dir = pCamera->GetDir();
// 		Vector		pos = pCamera->GetPos();
// 
// 		Vector  kDir;
// 		kDir.x = dir.x;
// 		kDir.y = dir.y;
// 		kDir.z = dir.z;
// 
// 		pos -= kDir * zDelta/20; 
// 
// 		pCamera->SetPos(pos);
// 	}

	/* 使用时打开下面这段注释就行.
 	CWorldEditView* pView	=	CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
 	GameCamera*		pCamera	=	dynamic_cast< GameCamera*>(pView->GetActiveCamera());
	if(pCamera)
	{
		m_iOffsetCamera += zDelta/20;
		pCamera->SetOffsetCamera(m_iOffsetCamera);
	}
	*/
	return true;
}

bool CToolGameCamera::OnKeyUp( UINT nChar, UINT nRepCnt, UINT nFlags )
{
    m_animAction.m_eumState = eum_Idle;
	return true;
}

bool CToolGameCamera::Create( CToolManager* toolMgr )
{
	CBaseTool::Create(toolMgr);
	return true;
}

void CToolGameCamera::Render()
{
    if(m_Player.m_Hero.model != NULL)
    {
        ChangeAction();  //改变Action

        m_Player.m_Hero.Update(HQ_TimeGetTime());
        m_Player.m_Hero.Render(1.0f);
    }
}

void CToolGameCamera::SetActive( bool isActive /*= true */ )
{
	CBaseTool::SetActive(isActive);
	if (isActive)
	{
        //激活1号相机
        if(CWorldEditDoc::GetActiveMapDoc())
        {
            CWorldEditView* pView = CWorldEditDoc::GetActiveMapDoc()->GetWorldView();
            pView->SetActiveCameraID(1);


            CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile();
            if(pTile != NULL)
            {
                //初始化相机位置
                flt32 *origin;
                BOOL bInFloor = false;
                flt32 fHeight = 0.0f;

                origin = pTile->GetOrigin();
                fHeight = SwGlobal::GetWorldPicker()->GetZByXY(10000.0,origin[0],origin[1],NULL,&bInFloor);

                 Vector pos;
                 pos.x = origin[0];
                 pos.y = origin[1];
                 pos.z = fHeight;

                 //SetCameraPos(pos);
                 SetViewPoint(pos);

            }

            AttachModel(); //连接模型
        }
	}
    else
    {
        //如果设置的不激活
        //DetalModel(); //释放模型
    }
}

void   CToolGameCamera::AttachModel()
{
    if(m_Player.IsNeedLoadModel())
    { 
        if(!LoadMode())
            return;
    }
	else
	{
		InitModelAndCamera();
	}

    CNdlHelper *helper = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetHelper();
    assert(helper != NULL);
    if(helper)
    {
        //helper->AttachHelper(&m_Player.m_Hero);
    }
}

void CToolGameCamera::DetalModel()
{
    SAFE_DELETE(m_Player.m_Hero.model);
}

void CToolGameCamera::InitModelAndCamera()
{
	Vector vecPos;

	flt32 *origin;
	BOOL bInFloor = false;
	flt32 fHeight = 0.0f;

	CWorldTile* pTile = SwGlobal::GetWorld()->GetWorldBuffer()->GetActiveTile();
	if(pTile)
	{
		origin = pTile->GetOrigin();
		fHeight = SwGlobal::GetWorldPicker()->GetZByXY(10000.0,origin[0],origin[1],NULL,&bInFloor);

		vecPos.x = origin[0];
		vecPos.y = origin[1];
		vecPos.z = fHeight + 0.2;

		m_Player.SetPosition(vecPos);
		//m_Player.SetScale(1.5f);  //1.5f //&&
		m_Player.m_Hero.model->SetScale(1.0f);
		SwCamera *pCamera = CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetActiveCamera();
		Vector vecRot = pCamera->GetRot();
		vecRot.x = float(45.0f * PI)/float(180.0f);
		pCamera->SetRot(vecRot);
		GameCamera * pGameCamera = dynamic_cast<GameCamera*>(pCamera);
		if (NULL!=pGameCamera)
		{
			pGameCamera->SetLookAt(vecPos);
		}
		//m_Player.SetDir(-vecRot.z);
		m_Player.m_Hero.model->SetRotationZ(vecRot.z);
	}
}

bool CToolGameCamera::LoadMode()
{
    //载入模型  //&&
	//F:\\work_hero\\Hero\\Program\\trunk\\Bin\\Client\\WorldEditor\\Required\\Model\\renwu.mex
	char cszWorkingDir[MAX_PATH] = {0};
	_getcwd( cszWorkingDir, MAX_PATH );
	char gameDataDir[MAX_PATH] = {0};	
	sprintf(gameDataDir, "%s\\Required\\Model\\renwu.mex", cszWorkingDir);
// 	char szModuleName[MAX_PATH] = {0};
// 	GetModuleFileName(NULL, szModuleName, MAX_PATH);
// 	int nLength = strlen(szModuleName);
// 	for (int i=nLength-1; i>0; i--)
// 	{
// 		if (szModuleName[i] == '\\')
// 		{
// 			szModuleName[i] = '\0';
// 			break;  
// 		}  
// 	}
// 	char gameDataDir[MAX_PATH] = {0};	
// 	sprintf(gameDataDir, "%s\\Required\\Model\\renwu.mex", szModuleName);

    if(!m_Player.LoadModel(gameDataDir))  //..\\Data\\Character\\Monster\\Animal\\gou\\gou.mex
        return false;

    InitModelAndCamera();

    return true;
}

void CToolGameCamera::SetAction(eum_Action eumValue)
{
    m_animAction.m_eumState = eumValue;
}

void CToolGameCamera::ChangeAction()
{
    switch(m_animAction.m_eumState)
    {
    case eum_Idle:
        {
            if(m_animAction.m_CurrAction.compare(IDLE) == 0)
                return;
            else
            {
                m_Player.m_Hero.model->PlayAnimByName(IDLE,0);
                m_animAction.m_CurrAction.clear();
                m_animAction.m_CurrAction = IDLE;
            }
        }
        break;
    case eum_Walk:
        {

            if(m_animAction.m_CurrAction.compare(RUN) == 0)
                return;
            else
            {
                m_Player.m_Hero.model->PlayAnimByName(RUN,0);
                m_animAction.m_CurrAction.clear();
                m_animAction.m_CurrAction = RUN;
            }
        }
        break;
    }
}

void  CToolGameCamera::SetCameraPos(Vector &pos)
{
    SwCamera* pCamera =  CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetActiveCamera();
    if(pCamera)
    {
        D3DXVECTOR3 dir = pCamera->GetDir();
   
        Vector  kDir;
        kDir.x = dir.x;
        kDir.y = dir.y;
        kDir.z = dir.z;

//      pos -= kDir * 30.0f; m_iOffsetCamera
//      pos.z += 10.0f;   //&&
		pos -= kDir * m_iOffsetCamera; 

        pCamera->SetPos(pos);
    }
}

void CToolGameCamera::SetViewPoint(Vector &point)
{
   GameCamera *pCamera = static_cast<GameCamera*>(CWorldEditDoc::GetActiveMapDoc()->GetWorldView()->GetActiveCamera());
   if(pCamera != NULL)
   {
       pCamera->SetLookAt(point);
   }
}
