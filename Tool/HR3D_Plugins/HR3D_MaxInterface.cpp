//----------------------------------------------------------------------------//
// MaxInterface.cpp                                                           //
// Copyright (C) 2001, 2002 Bruno 'Beosil' Heidelberger                       //
//----------------------------------------------------------------------------//
// This program is free software; you can redistribute it and/or modify it    //
// under the terms of the GNU General Public License as published by the Free //
// Software Foundation; either version 2 of the License, or (at your option)  //
// any later version.                                                         //
//----------------------------------------------------------------------------//

//----------------------------------------------------------------------------//
// Includes                                                                   //
//----------------------------------------------------------------------------//
//#include "hr3d_include.h"
#include "hr3d_plugins.h"
#include "hr3d_MaxInterface.h"

#include "d3dx9math.h"
#include "defines.h"

//----------------------------------------------------------------------------//
// Constructors                                                               //
//----------------------------------------------------------------------------//

HR3D_MaxInterface::HR3D_MaxInterface()
{
	m_pExpInterface = 0;
	m_pInterface = 0;
}

//----------------------------------------------------------------------------//
// Destructor                                                                 //
//----------------------------------------------------------------------------//

HR3D_MaxInterface::~HR3D_MaxInterface()
{
}

//----------------------------------------------------------------------------//
// Create a max interface instance                                            //
//----------------------------------------------------------------------------//

bool HR3D_MaxInterface::Create(ExpInterface *pExpInterface, Interface *pInterface)
{
	m_pExpInterface = pExpInterface;
	m_pInterface = pInterface;

	return true;
}

//----------------------------------------------------------------------------//
// Get the current frame of the animation                                     //
//----------------------------------------------------------------------------//

int HR3D_MaxInterface::GetCurrentFrame()
{
	return m_pInterface->GetTime() / GetTicksPerFrame();
}

//----------------------------------------------------------------------------//
// Get the current time in seconds of the animation                           //
//----------------------------------------------------------------------------//

float HR3D_MaxInterface::GetCurrentTime()
{
	return TicksToSec(m_pInterface->GetTime());
}

//----------------------------------------------------------------------------//
// Get the end frame of the animation                                         //
//----------------------------------------------------------------------------//

int HR3D_MaxInterface::GetEndFrame()
{
	return m_pInterface->GetAnimRange().End() / GetTicksPerFrame();
}

//----------------------------------------------------------------------------//
// Get the frames per second (Fps) of the animation                           //
//----------------------------------------------------------------------------//

int HR3D_MaxInterface::GetFps()
{
	return GetFrameRate();
}


int HR3D_MaxInterface::GetStartTick()
{
	return m_pInterface->GetAnimRange().Start();
}
int HR3D_MaxInterface::GetEndTick()
{
	return m_pInterface->GetAnimRange().End();
}
int HR3D_MaxInterface::GetFrameCount()
{
	return (GetEndTick()-GetStartTick())/GetFps() + 1;
}
int HR3D_MaxInterface::GetTickPerFrame()
{
	return GetTicksPerFrame();
}
//----------------------------------------------------------------------------//
// Get the transformation matrix of a given max node                          //
//----------------------------------------------------------------------------//

Matrix3 HR3D_MaxInterface::GetNodeTM(INode *pNode, float time)
{
	// initialize matrix with the identity
	Matrix3 tm;
	tm.IdentityMatrix();

	// only do this for valid nodes
	if(pNode != 0)
	{
		// get the node transformation
		tm = pNode->GetNodeTM(SecToTicks(time));

		// make the transformation uniform
		tm.NoScale();
	}

	return tm;
}

//----------------------------------------------------------------------------//
// Get the number of selected nodes in the scene                              //
//----------------------------------------------------------------------------//

int HR3D_MaxInterface::GetSelectedNodeCount()
{
	// get the number of selected nodes
	int nodeCount;
	nodeCount = m_pInterface->GetSelNodeCount();

	// if nothing is selected, there is always the scene root node
	if(nodeCount == 0) return 1;

	return nodeCount;
}


//----------------------------------------------------------------------------//
// Get the start frame of the animation                                       //
//----------------------------------------------------------------------------//

int HR3D_MaxInterface::GetStartFrame()
{
	return m_pInterface->GetAnimRange().Start() / GetTicksPerFrame();
}



//----------------------------------------------------------------------------//
// Check if the given node is a bone                                          //
//----------------------------------------------------------------------------//

bool HR3D_MaxInterface::IsBone(INode *pNode)
{

	// check for root node
	if(pNode->IsRootNode()) return false;

	// check for bone node
	ObjectState os;
	os = pNode->EvalWorldState(0);
	if(os.obj->ClassID() == Class_ID(BONE_CLASS_ID, 0)) return true;

#if MAX_RELEASE >= 4000
	if(os.obj->ClassID() == BONE_OBJ_CLASSID) return true;
#endif

	if(os.obj->ClassID() == Class_ID(DUMMY_CLASS_ID, 0)) return false;

	// check for biped node
	Control *pControl;
	pControl = pNode->GetTMController();
	if((pControl->ClassID() == BIPSLAVE_CONTROL_CLASS_ID) || (pControl->ClassID() == BIPBODY_CONTROL_CLASS_ID)) return true;

	return false;
}

//----------------------------------------------------------------------------//
// Check if the given node is a dummy                                         //
//----------------------------------------------------------------------------//

bool HR3D_MaxInterface::IsDummy(INode *pNode)
{
	// check for invalid nodes
	if(pNode == 0) return false;
	// check for root node
	if(pNode->IsRootNode()) return false;

	// check for dummy node
	ObjectState os;
	os = pNode->EvalWorldState(0);
	if(os.obj->ClassID() == Class_ID(DUMMY_CLASS_ID, 0)) return true;

	return false;
}

//----------------------------------------------------------------------------//
// Check if the given node is a mesh                                          //
//----------------------------------------------------------------------------//
bool HR3D_MaxInterface::IsLightObject( INode* pNode )
{
	// check for root node
	if( !pNode ) return false;
	if(pNode->IsRootNode()) return false;

	// check for mesh node
	ObjectState os;
	os = pNode->EvalWorldState(0);
	if( os.obj->SuperClassID() == LIGHT_CLASS_ID &&
		os.obj->ClassID () == Class_ID ( OMNI_LIGHT_CLASS_ID, 0 ) ) 
		return true;
	return false;
}
bool HR3D_MaxInterface::IsMesh(INode *pNode)
{
	// check for root node
	if( !pNode ) 
		return false;
	if( pNode->IsRootNode() ) 
		return false;

	// check for mesh node
	ObjectState os;
	os = pNode->EvalWorldState(0);
	if(os.obj->SuperClassID() == GEOMOBJECT_CLASS_ID) 
		return true;

	return false;
}

BOOL HR3D_MaxInterface::IsRenderable( INode* node )
{
	Object *obj = node->EvalWorldState ( 0 ).obj;	
	return obj->IsRenderable();
}

//----------------------------------------------------------------------------//
// Progress callback function                                                 //
//----------------------------------------------------------------------------//

DWORD WINAPI HR3D_MaxInterface::ProgressFunction(LPVOID arg)
{
	return 0;
}

//----------------------------------------------------------------------------//
// Set the progress information to a given text and percentage                //
//----------------------------------------------------------------------------//

void HR3D_MaxInterface::SetProgressInfo(int percentage)
{
	m_pInterface->ProgressUpdate(percentage);
}

//----------------------------------------------------------------------------//
// Start the progress information process                                     //
//----------------------------------------------------------------------------//

void HR3D_MaxInterface::StartProgressInfo(const std::string& strText)
{
	m_pInterface->ProgressStart(const_cast<char *>(strText.c_str()), true, ProgressFunction, 0);
}

//----------------------------------------------------------------------------//
// Stop the progress information process                                      //
//----------------------------------------------------------------------------//

void HR3D_MaxInterface::StopProgressInfo()
{
	m_pInterface->ProgressEnd();
}

//----------------------------------------------------------------------------//
INode* HR3D_MaxInterface::GetRootNode()
{
	return m_pInterface->GetRootNode();
}

Mesh* HR3D_MaxInterface::GetMesh( INode* pNode )
{
	if( !IsMesh( pNode ) )
		return NULL;
	// get the current time
	TimeValue time = 0;
	//time = m_pInterface->GetTime();

	//Object* obj = MaxNode->EvalWorldState( curTime ).obj;
	//TriObject* triObj = (TriObject*)obj->ConvertToType( curTime, triObjectClassID );
	//Mesh& mesh = triObj->GetMesh();

	// get max mesh instance
	ObjectState os;
	os = pNode->EvalWorldState(time);

	//NullView maxNullView;
	//BOOL b = false;
	//Mesh* pMesh = ((TriObject *)os.obj)->GetRenderMesh(time, pNode, maxNullView, b );
	Object* obj = os.obj;
	if( !os.obj )
	{
		assert( false );
		return NULL;
	}
	TriObject* triObj = (TriObject *)obj->ConvertToType( time, triObjectClassID );
	if( !triObj )
	{
		assert( false );
		return NULL;
	}
	//Mesh* pMesh = &((TriObject *)os.obj)->GetMesh();
	Mesh* pMesh = &triObj->GetMesh();

	return pMesh;
}
Modifier* HR3D_MaxInterface::FindModifier(INode *pINode, Class_ID id)
{
	// get the object reference of the node
	Object *pObject;
	pObject = pINode->GetObjectRef();
	if(pObject == 0) return 0;

	// loop through all derived objects
	while(pObject->SuperClassID() == GEN_DERIVOB_CLASS_ID)
	{
		IDerivedObject *pDerivedObject;
		pDerivedObject = static_cast<IDerivedObject *>(pObject);

		// loop through all modifiers
		int stackId;
		for(stackId = 0; stackId < pDerivedObject->NumModifiers(); stackId++)
		{
			// get the modifier
			Modifier *pModifier;
			pModifier = pDerivedObject->GetModifier(stackId);

			// check if we found the physique modifier
			if(pModifier->ClassID() == id) return pModifier;
		}

		// continue with next derived object
		pObject = pDerivedObject->GetObjRef();
	}

	return 0;

}

Modifier* HR3D_MaxInterface::FindPhysiqueModifier(INode *pINode)
{
	// get the object reference of the node
	Object *pObject;
	pObject = pINode->GetObjectRef();
	if(pObject == 0) return 0;

	// loop through all derived objects
	while(pObject->SuperClassID() == GEN_DERIVOB_CLASS_ID)
	{
		IDerivedObject *pDerivedObject;
		pDerivedObject = static_cast<IDerivedObject *>(pObject);

		// loop through all modifiers
		int stackId;
		for(stackId = 0; stackId < pDerivedObject->NumModifiers(); stackId++)
		{
			// get the modifier
			Modifier *pModifier;
			pModifier = pDerivedObject->GetModifier(stackId);

			// check if we found the physique modifier
			if(pModifier->ClassID() == Class_ID(PHYSIQUE_CLASS_ID_A, PHYSIQUE_CLASS_ID_B)) return pModifier;
		}

		// continue with next derived object
		pObject = pDerivedObject->GetObjRef();
	}
	return 0;
}

Modifier* HR3D_MaxInterface::FindVertexModifier(INode *pINode)
{
	// get the object reference of the node
	Object *pObject;
	pObject = pINode->GetObjectRef();
	if(pObject == 0) return 0;

	// loop through all derived objects
	while(pObject->SuperClassID() == GEN_DERIVOB_CLASS_ID)
	{
		IDerivedObject *pDerivedObject;
		pDerivedObject = static_cast<IDerivedObject *>(pObject);

		// loop through all modifiers
		int stackId;
		for(stackId = 0; stackId < pDerivedObject->NumModifiers(); stackId++)
		{
			// get the modifier
			Modifier *pModifier;
			pModifier = pDerivedObject->GetModifier(stackId);

			// check if we found the physique modifier
			if(pModifier->ClassID() == PAINTLAYERMOD_CLASS_ID) return pModifier;
		}

		// continue with next derived object
		pObject = pDerivedObject->GetObjRef();
	}

	return 0;
}

bool HR3D_MaxInterface::IsBipedBone( INode* pNode )
{
	// check for invalid nodes
	if(pNode == 0) return false;

	// check for root node
	if(pNode->IsRootNode()) return false;

	// check for bone node
	ObjectState os;
	os = pNode->EvalWorldState(0);
	if(os.obj->ClassID() == Class_ID(DUMMY_CLASS_ID, 0)) return false;

	// check for biped node
	Control *pControl;
	pControl = pNode->GetTMController();
	if((pControl->ClassID() == BIPSLAVE_CONTROL_CLASS_ID) || (pControl->ClassID() == BIPBODY_CONTROL_CLASS_ID)) return true;

	return false;

}
bool HR3D_MaxInterface::IsTarget( INode* pNode )
{
	return pNode->IsTarget();
}
bool HR3D_MaxInterface::IsSelected( INode* pNode )
{
	return pNode->Selected();
}

Matrix3 HR3D_MaxInterface::GetRelativeTransform( INode* src, INode* dst )
{
	Matrix3 matSrc = src->GetObjectTM(SecToTicks(GetCurrentTime()));
	Matrix3 matDst = dst->GetObjectTM(SecToTicks(GetCurrentTime()));

	matSrc.NoScale();
	matDst.NoScale();
	Matrix3 mat = matSrc*Inverse( matDst );
	return mat;

}

// realrender added 2002.11.18 for select node
INode* HR3D_MaxInterface::GetSelectedNode()
{
	if( m_pInterface->GetSelNodeCount() <= 0 )
		return 0;
	return m_pInterface->GetSelNode(0);
}

// realrender added 2002.11.18 for select node
INode* HR3D_MaxInterface::GetSelectedNode( int nNodeId )
{
	if( nNodeId < 0 || nNodeId >= m_pInterface->GetSelNodeCount() )
		return 0;
	return m_pInterface->GetSelNode(nNodeId);
}

void HR3D_MaxInterface::GetTranslationAndRotation(INode *pNode, INode *pParentNode, float time, HR3D_Vector& translation, HR3D_Quaternion& rotation)
{
	// check for invalid nodes
	if(pNode == 0) return;

	// calculate the relative transformation
	Matrix3 tm;
	tm = GetNodeTM(pNode, time) * Inverse(GetNodeTM(pParentNode, time));

	// calculate the translation component
	Point3 p;
	p = tm.GetTrans();

	translation.x = p[0];
	translation.y = p[1];
	translation.z = p[2];

	// calculate the rotation component
	Quat q(tm);

	rotation.x = q[0];
	rotation.y = q[1];
	rotation.z = q[2];
	rotation.w = q[3];

}

void HR3D_MaxInterface::GetTranslationAndRotationBoneSpace(INode *pNode, float time, HR3D_Vector& translation, HR3D_Quaternion& rotation )
{
	// check for invalid nodes
	if(pNode == 0) return;

	// calculate the relative transformation
	Matrix3 tm;
	tm = Inverse(GetNodeTM(pNode, time));
	//tm = GetNodeTM(pNode, time);

	// calculate the translation component
	Point3 p;
	p = tm.GetTrans();

	translation.x = p[0];
	translation.y = p[1];
	translation.z = p[2];

	// calculate the rotation component
	Quat q(tm);

	rotation.x = q[0];
	rotation.y = q[1];
	rotation.z = q[2];
	rotation.w = q[3];
}

char* HR3D_MaxInterface::GetMapname( StdMat* pStdMtl )
{
	if( pStdMtl == 0 )
		return 0;
	Texmap *pTexMap = pStdMtl->GetSubTexmap(ID_DI);
	if( pTexMap == 0 )
		return 0;
	if( pTexMap->ClassID() != Class_ID( BMTEX_CLASS_ID,0 ) )
		return 0;
	BitmapTex *pBitmapTex = (BitmapTex*)pTexMap;
	return pBitmapTex->GetMapName();

}

Point3 HR3D_MaxInterface::GetVertexNormal( Mesh* pMesh, int faceId, int vertexId )
{
	RVertex *pRVertex;
	pRVertex = pMesh->getRVertPtr(vertexId);


	// get the face
	Face *pFace;
	pFace = &pMesh->faces[faceId];

	// get the smoothing group of the face
	DWORD smGroup;
	smGroup = pFace->smGroup;

	// get the number of normals
	int normalCount;
	normalCount = pRVertex->rFlags & NORCT_MASK;

	// check if the normal is specified ...
	if(pRVertex->rFlags & SPECIFIED_NORMAL)
	{
		return pRVertex->rn.getNormal();
	}
	// ... otherwise, check for a smoothing group
	else if((normalCount > 0) && (smGroup != 0))
	{
		// If there is only one vertex is found in the rn member.
		if(normalCount == 1)
		{
			return pRVertex->rn.getNormal();
		}
		else
		{
			int normalId;
			Point3 n(0,0,0);
			for(normalId = 0; normalId < normalCount; normalId++)
			{
				if(pRVertex->ern[normalId].getSmGroup() & smGroup)
				{
					//return pRVertex->ern[normalId].getNormal();
					n = n+pRVertex->ern[normalId].getNormal();
				}
			}
			n = n.Normalize();
			return n;
		}
	}

	// if all fails, return the face normal
	return pMesh->getFaceNormal(faceId);

}

// realrender added 2003.05.26
void HR3D_MaxInterface::GetNodeTree( INode* pNode )
{
	if( pNode == NULL )
	{
		//return;
		pNode = GetRootNode();
	}
	if( !pNode )
		return;
	if( pNode != GetRootNode() )
		m_vectorNode.push_back( pNode );

	for (int i = 0; i < pNode->NumberOfChildren(); i++) 
	{
		GetNodeTree( pNode->GetChildNode( i ) );
	}

}
extern Interface* g_ip;
void SampleController(INode *n, Control *c) ;
void PluginOutput( const char *string, ... )
{
	if( !string )
		return;
	va_list	va;
	static char data[1024];
	va_start( va, string );
	wvsprintf( (char*)data, string, va );
	va_end( va );

	OutputDebugString( data );
}
void KeyTest( INode* pNode )
{
	//Interface* ip = g_ip;

	int i, numKeys;

	INode *n = pNode;

	Control *c;

	Quat newQuat, prevQuat;
	IKeyControl		*ikeys;
	ITCBPoint3Key	tcbPosKey;
	ITCBRotKey		tcbRotKey;
	ITCBScaleKey	tcbScaleKey;
	IBezPoint3Key	bezPosKey;
	IBezQuatKey		bezRotKey;
	IBezScaleKey	bezScaleKey;
	ILinPoint3Key	linPosKey;
	ILinRotKey		linRotKey;
	ILinScaleKey	linScaleKey;
	// --- Process the position keys ---

	c = n->GetTMController()->GetPositionController();
	if( c )
	{		

		ikeys = GetKeyControlInterface(c);

		if (!ikeys)
		{
			SampleController(n, c);
			return; 
		}
		numKeys = ikeys->GetNumKeys();

		PluginOutput(_T("\nThere are %d position key(s)"), numKeys);

		if (c->ClassID() == Class_ID(TCBINTERP_POSITION_CLASS_ID, 0)) 
		{
			for (i = 0; i < numKeys; i++) 
			{
				ikeys->GetKey(i, &tcbPosKey);

				PluginOutput(_T("\nTCB Position Key: %d=(%.1f, %.1f, %.1f)"), 
					i, tcbPosKey.val.x, tcbPosKey.val.y, tcbPosKey.val.z);
			}

		}
		else if (c->ClassID() == Class_ID(HYBRIDINTERP_POSITION_CLASS_ID, 0)) 
		{
			for (i = 0; i < numKeys; i++) 
			{
				ikeys->GetKey(i, &bezPosKey);
				PluginOutput(_T("\nBezier Position Key: %d=(%.1f, %.1f, %.1f)"), 
					i, bezPosKey.val.x, bezPosKey.val.y, bezPosKey.val.z);
			}
		}
		else if (c->ClassID() == Class_ID(LININTERP_POSITION_CLASS_ID, 0)) 
		{
			for (i = 0; i < numKeys; i++) 
			{
				ikeys->GetKey(i, &linPosKey);
				PluginOutput(_T("\nLinear Position Key: %d=(%.1f, %.1f, %.1f)"), 
					i, linPosKey.val.x, linPosKey.val.y, linPosKey.val.z);
			}
		}
	}

	// --- Process the rotation keys ---

	c = n->GetTMController()->GetRotationController();

	if( c )
	{
		ikeys = GetKeyControlInterface(c);

		if (!ikeys) return;

		numKeys = ikeys->GetNumKeys();

		PluginOutput(_T("\nThere are %d rotation key(s)"), numKeys);

		if (c->ClassID() == Class_ID(TCBINTERP_ROTATION_CLASS_ID, 0)) 
		{
			for (i = 0; i < numKeys; i++) 
			{
				ikeys->GetKey(i, &tcbRotKey);

				newQuat = QFromAngAxis(tcbRotKey.val.angle, tcbRotKey.val.axis);
				if (i) newQuat = prevQuat * newQuat;
				prevQuat = newQuat;
				PluginOutput(_T("\nTCB Rotation Key: %d=(%.1f, %.1f, %.1f, %.1f)"), 
					i, newQuat.x, newQuat.y, newQuat.z, newQuat.w);
			}
		}
		else if (c->ClassID() == Class_ID(HYBRIDINTERP_ROTATION_CLASS_ID, 0))
		{
			for (i = 0; i < numKeys; i++)
			{
				ikeys->GetKey(i, &bezRotKey);

				newQuat = bezRotKey.val;

				if (i) newQuat = prevQuat * newQuat;

				prevQuat = newQuat;
				PluginOutput(_T("\nBezier Rotation Key: %d=(%.1f, %.1f, %.1f, %.1f)"), 
					i, newQuat.x, newQuat.y, newQuat.z, newQuat.w);
			}
		}
		else if (c->ClassID() == Class_ID(LININTERP_ROTATION_CLASS_ID, 0))
		{
			for (i = 0; i < numKeys; i++) 
			{
				ikeys->GetKey(i, &linRotKey);

				newQuat = linRotKey.val;

				if (i) newQuat = prevQuat * newQuat;
				prevQuat = newQuat;
				PluginOutput(_T("\nLinear Rotation Key: %d=(%.1f, %.1f, %.1f, %.1f)"), 
					i, newQuat.x, newQuat.y, newQuat.z, newQuat.w);
			}
		}
	}

	// --- Process the scale keys ---

	c = n->GetTMController()->GetScaleController();

	if( c )
	{
		ikeys = GetKeyControlInterface(c);

		if (!ikeys) return;

		numKeys = ikeys->GetNumKeys();
		PluginOutput(_T("\nThere are %d scale key(s)"), numKeys);

		if (c->ClassID() == Class_ID(TCBINTERP_SCALE_CLASS_ID, 0)) 
		{
			for (i = 0; i < numKeys; i++)
			{
				ikeys->GetKey(i, &tcbScaleKey);
				PluginOutput(_T("\nTCB Scale Key: %2d=(%.1f, %.1f, %.1f)"), 
					i, tcbScaleKey.val.s.x, tcbScaleKey.val.s.y, 
					tcbScaleKey.val.s.z);
			}
		}
		else if (c->ClassID() == Class_ID(HYBRIDINTERP_SCALE_CLASS_ID, 0)) 
		{
			for (i = 0; i < numKeys; i++) 
			{
				ikeys->GetKey(i, &bezScaleKey);
				PluginOutput(_T("\nBezier Scale Key: %2d=(%.1f, %.1f, %.1f)"), 
					i, bezScaleKey.val.s.x, bezScaleKey.val.s.y, 
					bezScaleKey.val.s.z);
			}
		}
		else if (c->ClassID() == Class_ID(LININTERP_SCALE_CLASS_ID, 0)) 
		{
			for (i = 0; i < numKeys; i++)
			{
				ikeys->GetKey(i, &linScaleKey);

				PluginOutput(_T("\nLinear Scale Key: %2d=(%.1f, %.1f, %.1f)"), 
					i, linScaleKey.val.s.x, linScaleKey.val.s.y, 
					linScaleKey.val.s.z);
			}

		}
	}

}



// Display the position data of controller in world coordinates for each

// frame in the animation range

void SampleController(INode *n, Control *c) 
{

	Interface* ip = g_ip;
	TimeValue t;

	Point3 trans;

	Matrix3 pmat;

	Interval ivalid;

	int tpf = GetTicksPerFrame();

	int s = ip->GetAnimRange().Start()/tpf, 

		e = ip->GetAnimRange().End()/tpf;



	// Sample the controller at every frame in the anim range

	for (int f = s; f <= e; f++)
	{

		t = f*tpf;

		ivalid = FOREVER;

		pmat = n->GetParentTM(t);

		c->GetValue(t, &pmat, ivalid, CTRL_RELATIVE);

		trans = pmat.GetTrans();

		PluginOutput(_T("\nPosition at frame: %d of %d=(%.1f, %.1f, %.1f)"), 

			f, e, trans.x, trans.y, trans.z);

	}

}

void HR3D_MaxInterface::GetAnim( INode* pNode, Anim* pAnim )
{
	if( !pNode )
		return;
	//KeyTest( pNode );
	//return;
	Interface* ip = m_pInterface;
	Control *c = pNode->GetTMController();

	Control* pPositionController = NULL;
	Control* pRotationController = NULL;
	Control* pScaleController = NULL;

	if ((c->ClassID() == BIPSLAVE_CONTROL_CLASS_ID) ||
		(c->ClassID() == BIPBODY_CONTROL_CLASS_ID) ||
		(c->ClassID() == FOOTPRINT_CLASS_ID))
	{
		IBipedExport *BipIface = (IBipedExport *) c->GetInterface(I_BIPINTERFACE);

		BipIface->RemoveNonUniformScale(1);

		pPositionController = c->GetPositionController();


		c->ReleaseInterface(I_BIPINTERFACE, BipIface);
	}
	if( pPositionController )
	{
		IKeyControl *pKeyControl = GetKeyControlInterface(pPositionController);
		int nNumKey = pKeyControl->GetNumKeys();
		if (pPositionController->ClassID() == Class_ID(TCBINTERP_POSITION_CLASS_ID, 0))
		{
			ITCBPoint3Key tcbPosKey;
			for( int nKey = 0; nKey < nNumKey; nKey++) 
			{
				pKeyControl->GetKey(nKey, &tcbPosKey);

				PluginOutput(_T("\nPosition Key: %d=(%.1f, %.1f, %.1f)"), nKey, tcbPosKey.val.x, tcbPosKey.val.y, tcbPosKey.val.z);

			}

		}
	}

}
void HR3D_MaxInterface::GetTracks( int nNodeCount, INode** nodes, Track** tracks, BOOL bOnlyFirstFrame )
{
	StartProgressInfo("Get node track...");
	TimeValue nStartTick = GetStartTick();
	TimeValue nEndTick = GetEndTick();
	int nTickPerFrame = GetTickPerFrame();
	int nFrameCount = 0;
	if( bOnlyFirstFrame )
		nFrameCount = 1;
	else
	{
		for( TimeValue t = nStartTick; t <= nEndTick; t += nTickPerFrame )
			nFrameCount++;
	}
	for( int i = 0; i < nNodeCount; i++ )
	{
		tracks[i]->vectorMatrix.resize( nFrameCount );
		tracks[i]->vectorVisibleFloat.resize( nFrameCount );
		tracks[i]->vectorVisibleBool.resize( nFrameCount );
		tracks[i]->vectorTrans.resize( nFrameCount );		
		tracks[i]->vectorRot.resize( nFrameCount );

		Matrix3 matrix = nodes[i]->GetObjTMAfterWSM ( 0 );
		BOOL bMirror = DotProd ( CrossProd ( matrix.GetRow ( 0 ), matrix.GetRow ( 1 ) ), matrix.GetRow ( 2 ) ) < 0.0 ? TRUE : FALSE;
		//int k = 0;
		tracks[i]->bMirror = bMirror;
	}
	TimeValue t = nStartTick;
	for( int nFrameId = 0; nFrameId < nFrameCount; nFrameId++, t += nTickPerFrame )
	{
		SetProgressInfo( 100.0f*nFrameId/nFrameCount );

		for( int nNodeId = 0; nNodeId < nNodeCount; nNodeId++ )
		{
			//SetProgressInfo( 100.0f*nNodeId/nNodeCount );
			INode* pNode = nodes[nNodeId];
			Track* pTrack = tracks[nNodeId];

			Matrix3 tm = pNode->GetNodeTM(t);

			//求出相对矩阵
			/*INode* parent=pNode->GetParentNode();
			if(parent)
			{
				Matrix3 ptm=pNode->GetParentTM(t);
				Matrix3 iptm=Inverse(ptm);
				tm=tm*iptm;
			}*/

			HR3D_Vector trans;
			HR3D_Quaternion quat;

			Point3 p;
			p = tm.GetTrans();

			trans.x = p[0];
			trans.y = p[1];
			trans.z = p[2];

			// calculate the rotation component
			Quat q(tm);
			if( tracks[nNodeId]->bMirror )
			{
				float m[4][3];
				memcpy( m, &tm, sizeof(float)*4*3 );
				//Matrix3 m = tm;
				m[0][0] *= -1;
				m[1][0] *= -1;
				m[2][0] *= -1;
				//m[3][0] *= -1;
				Matrix3 mm(m);
				//mm.SetRow( 0, Point3(m[0]) );
				Quat q0(mm);
				q = q0;
			}


			quat.x = q[0];
			quat.y = q[1];
			quat.z = q[2];
			quat.w = q[3];

			pTrack->vectorTrans[nFrameId] = trans;
			pTrack->vectorRot[nFrameId] = quat;

			/*
			* 2012.6.7 废弃了VisibleBool(vis2), 直接使用VisibleFloat(visf)
			*/
			float fv = pNode->GetVisibility( t );
			pTrack->vectorVisibleFloat[nFrameId] = fv;
			if ( fv != 1)
				pTrack->vectorVisibleBool[nFrameId] = FALSE;
			else
				pTrack->vectorVisibleBool[nFrameId] = TRUE;

			HR3D_Matrix* matrix = &pTrack->vectorMatrix[nFrameId];
			for (int i =0; i < 4; i++ )
			{
				Point3 row = tm.GetRow(i);
				matrix->m[i][0] = row.x;
				matrix->m[i][1] = row.y;
				matrix->m[i][2] = row.z;

			}

			matrix->m[0][3] = 0;
			matrix->m[1][3] = 0;
			matrix->m[2][3] = 0;
			matrix->m[3][3] = 1;

		}

	}
}

void HR3D_MaxInterface::GetTrack( INode* pNode, Track& track, BOOL bOnlyFirstFrame )
{
	if( pNode == NULL )
		return;
	StartProgressInfo("Get node track...");
	TimeValue nStartTick = GetStartTick();
	TimeValue nEndTick = GetEndTick();
	int nTickPerFrame = GetTickPerFrame();


	int nFrameCount = 0;
	TimeValue t;
	if( !bOnlyFirstFrame )
	{
		// 计算帧数
		for( t = nStartTick; t <= nEndTick; t += nTickPerFrame )
			nFrameCount++;
	}
	else
		nFrameCount = 1;

	track.vectorMatrix.reserve( nFrameCount );
	track.vectorMatrix.resize( nFrameCount );
	track.vectorVisibleBool.reserve( nFrameCount );
	track.vectorVisibleBool.resize( nFrameCount );

	t = nStartTick;
	for( int i = 0; i < nFrameCount; i++, t += nTickPerFrame )
	{
		SetProgressInfo( 100.0f*i/nFrameCount );

		Matrix3 tm = pNode->GetNodeTM(t);

		/*
		* 2012.6.7 废弃了VisibleBool(vis2), 直接使用VisibleFloat(visf)
		*/
		float fv = pNode->GetVisibility( t );
		track.vectorVisibleFloat[i] = fv;
		if ( fv != 1 )
			track.vectorVisibleBool[i] = FALSE;
		else
			track.vectorVisibleBool[i] = TRUE;
		//Matrix3 tm = pNode->GetObjectTM(t);
		//pNode->GetObjectTMBeforeWSM();
		//tm.NoScale();

		//HR3D_Matrix* matrix = &track.pMatrices[i];
		HR3D_Matrix* matrix = &track.vectorMatrix[i];
		for (int i =0; i <4; i++ )
		{
			Point3 row = tm.GetRow(i);
			matrix->m[i][0] = row.x;
			matrix->m[i][1] = row.y;
			matrix->m[i][2] = row.z;

		}

		matrix->m[0][3] = 0;
		matrix->m[1][3] = 0;
		matrix->m[2][3] = 0;
		matrix->m[3][3] = 1;
	}

}

// realrender added 2003.05.31
bool HR3D_MaxInterface::GetSubtexmap( INode* node, DWORD dwChannel, char szMapname[], TexInfo* pTexInfo )
{
	if( !node )return 0;
	if( !IsMesh( node ) )return 0;
	if( !IsRenderable( node ) )return 0;
	if( IsBone( node ) )return 0;
	if( IsTarget( node ) )return 0;

	Mesh* mesh = GetMesh( node );

	if( !mesh->tvFace )
	{
		MessageBox(NULL, "网格体没有贴图，请指定贴图！！", "", MB_OK );
		return 0;
	}


	//static char szMapname[256] = "\0";
	Mtl* mtl = node->GetMtl();
	if( !mtl )
	{
		MessageBox(NULL, "您选择的刚体没有材质，请指定材质！！", "", MB_OK );
		return 0;
	}
	if( mtl->IsMultiMtl() )
	{
		MessageBox(NULL, "刚体文件不支持多重材质，请指定单一材质！！", "", MB_OK );
		return 0;
	}

	StdMat* stdmtl = (StdMat*)mtl;
	if( stdmtl )
	{
		Texmap *tx = stdmtl->GetSubTexmap(dwChannel);
		if( !tx )
		{
			//MessageBox(NULL, "通道没有指定贴图！！", "", MB_OK );
			return 0;
		}
		if( tx->ClassID() != Class_ID( BMTEX_CLASS_ID, 0 ) )
		{
			MessageBox(NULL, "您应该使用位图当作贴图！！", "", MB_OK );
			return 0;
		}
		BitmapTex *bmt = (BitmapTex*)tx;
		if( szMapname )
			strcpy( szMapname, bmt->GetMapName() );



		if( pTexInfo )
		{
			StdUVGen *uv = bmt->GetUVGen();
			pTexInfo->fUTile = uv->GetUScl(0);
			pTexInfo->fVTile = uv->GetVScl(0);
		}

	}
	return 1;

}
HR3D_Matrix HR3D_MaxInterface::ConverteMatrix3( Matrix3& tm )
{
	// 写入初始化矩阵
	D3DXMATRIX matrix; 
	Point3 point[4];

	// 得到运动矩阵

	point[0] = tm.GetRow ( 0 );
	point[1] = tm.GetRow ( 1 );
	point[2] = tm.GetRow ( 2 );
	point[3] = tm.GetRow ( 3 );

	// 坐标系转换
	point[0].z = -point[0].z;
	point[1].z = -point[1].z;
	point[2].x = -point[2].x;
	point[2].y = -point[2].y;
	point[3].z = -point[3].z;

	D3DXMatrixIdentity ( &matrix );
	matrix._11 = point[0].x;
	matrix._12 = point[0].y;
	matrix._13 = point[0].z;
	matrix._21 = point[1].x;
	matrix._22 = point[1].y;
	matrix._23 = point[1].z;
	matrix._31 = point[2].x;
	matrix._32 = point[2].y;
	matrix._33 = point[2].z;
	matrix._41 = point[3].x;
	matrix._42 = point[3].y;
	matrix._43 = point[3].z;

	return *(HR3D_Matrix*)&matrix;

}
// realrender added 2003.08.24

void HR3D_MaxInterface::GetBoneGroup( Modifier *pModifier,
									 int nModifierType, 
									 INode* pNode, 
									 Mesh* pMesh,
									 int nVertexId,
									 HR3D_MaxInterface::BoneGroup& boneGroup )
{
	if( !pMesh )
	{
		assert( false );
		return;
	}

	if( nVertexId >= pMesh->numVerts )
	{
		assert( false );
		return;
	}

	// 刚体
	if( nModifierType == MODIFIER_NONE )
	{
		INode* pParent = pNode->GetParentNode();
		if( pParent && ( IsBone( pParent ) || IsBipedBone( pParent ) ) )
		{
			Influence infl;
			infl.fWeight = 1.0f;
			strcpy( infl.szBoneName, pParent->GetName() );
			//boneGroup.vectorInfl.push_back( infl );
			boneGroup.AddInfluence( infl );
		}
	}
	// check for physique modifier
	else if( nModifierType == MODIFIER_PHYSIQUE )
	{
		assert( pModifier && "get bone group error, modifier is null" );
		// create a physique export interface
		IPhysiqueExport *pPhysiqueExport;
		pPhysiqueExport = (IPhysiqueExport *)pModifier->GetInterface(I_PHYINTERFACE);
		if(pPhysiqueExport == 0)
		{
			return;
		}

		// create a context export interface
		IPhyContextExport *pContextExport;
		pContextExport = (IPhyContextExport *)pPhysiqueExport->GetContextInterface(pNode);
		if(pContextExport == 0)
		{
			pModifier->ReleaseInterface(I_PHYINTERFACE, pPhysiqueExport);
			return;
		}

		// set the flags in the context export interface
		pContextExport->ConvertToRigid(TRUE);
		pContextExport->AllowBlending(TRUE);

		// get the vertex export interface
		IPhyVertexExport *pVertexExport;
		pVertexExport = (IPhyVertexExport *)pContextExport->GetVertexInterface(nVertexId);
		if(pVertexExport == 0)
		{
			pPhysiqueExport->ReleaseContextInterface(pContextExport);
			pModifier->ReleaseInterface(I_PHYINTERFACE, pPhysiqueExport);
			return;
		}

		// get the vertex type
		int vertexType;
		vertexType = pVertexExport->GetVertexType();
		//BoneGroup* infls = new BoneGroup;
		// handle the specific vertex type
		if(vertexType == RIGID_TYPE)
		{
			// typecast to rigid vertex
			IPhyRigidVertex *pTypeVertex;
			pTypeVertex = (IPhyRigidVertex *)pVertexExport;


			Influence infl;
			//assert( pTypeVertex->GetNode() );
			if( pTypeVertex->GetNode() )
			{
				strcpy( infl.szBoneName, pTypeVertex->GetNode()->GetName() );
				infl.fWeight = 1.0f;
				boneGroup.AddInfluence( infl );
			}
			else 
				return;

		}
		else if(vertexType == RIGID_BLENDED_TYPE)
		{
			// typecast to blended vertex
			IPhyBlendedRigidVertex *pTypeVertex;
			pTypeVertex = (IPhyBlendedRigidVertex *)pVertexExport;

			// loop through all influencing bones
			Influence infl;

			int nodeId;
			for(nodeId = 0; nodeId < pTypeVertex->GetNumberNodes(); nodeId++)
			{
				INode* pNode = pTypeVertex->GetNode( nodeId );
				if( pNode == NULL ) continue;
				strcpy( infl.szBoneName, pTypeVertex->GetNode( nodeId )->GetName() );
				infl.fWeight = pTypeVertex->GetWeight( nodeId );

				boneGroup.AddInfluence( infl );
			}
		}

		// release all interfaces
		pPhysiqueExport->ReleaseContextInterface(pContextExport);
		pModifier->ReleaseInterface(I_PHYINTERFACE, pPhysiqueExport);

		//return infls;

	}
	else if( nModifierType == MODIFIER_SKIN)
	{
		assert( pModifier && "get bone group error, modifier is null" );
		// create a skin interface
		ISkin *pSkin;
		pSkin = (ISkin*)pModifier->GetInterface(I_SKIN);
		if(pSkin == 0)
		{
			return;
		}

		// create a skin context data interface
		ISkinContextData *pSkinContextData;
		pSkinContextData = (ISkinContextData *)pSkin->GetContextInterface(pNode);
		if(pSkinContextData == 0)
		{
			pModifier->ReleaseInterface(I_SKIN, pSkin);
			//theExporter.SetLastError("Skin context data interface not found.", __FILE__, __LINE__);
			return;
		}

		// loop through all influencing bones
		//BoneGroup* infls = new BoneGroup;
		//这个顶点受那些骨骼影响
		for( int nodeId = 0; nodeId < pSkinContextData->GetNumAssignedBones(nVertexId); nodeId++)
		{
			// get the bone id
			int boneId;
			boneId = pSkinContextData->GetAssignedBone(nVertexId, nodeId);
			if(boneId < 0) continue;

			INode* pBone = pSkin->GetBone( boneId );
			Influence infl;
			strcpy( infl.szBoneName, pBone->GetName() );
			infl.fWeight = pSkinContextData->GetBoneWeight(nVertexId, nodeId);
			//boneGroup.vectorInfl.push_back( infl );
			boneGroup.AddInfluence( infl );
		}

		// release all interfaces
		pModifier->ReleaseInterface(I_SKIN, pSkin);
		//return infls;
	}
	//return NULL;	
}
// realrender added 2004.08.06
bool HR3D_MaxInterface::GetLightColorTrack( INode* pNode, ColorTrack& track )
{
	int nFrameCount = 0;
	TimeValue nStartTick = GetStartTick();
	TimeValue nEndTick = GetEndTick();
	int nTickPerFrame = GetTickPerFrame();
	TimeValue t;
	for( t = nStartTick; t <= nEndTick; t += nTickPerFrame )
		nFrameCount++;
	track.vectorColorKey.reserve( nFrameCount );
	track.vectorColorKey.resize( nFrameCount );

	Object *obj = pNode->EvalWorldState ( 0 ).obj;
	LightObject *pLight = ( LightObject* )obj;

	for( int i = 0; i < nFrameCount; i++, t += nTickPerFrame )
	{
		HR3D_Mdx2ColorKey key;
		memset( &key, 0x00, sizeof( key ) );
		Point3 color = pLight->GetRGBColor( t );
		key.dr = color[0];
		key.dg = color[1];
		key.db = color[2];
		track.vectorColorKey[i] = key;
	}

	return true;
}

bool HR3D_MaxInterface::GetMtlAnim( StdMat* pStdMtl, ColorTrack& track )
{
	if( pStdMtl == NULL )
	{
		assert( false && "std mtl is NULL" );
		return false;
	}

	int nFrameCount = 0;
	TimeValue nStartTick = GetStartTick();
	TimeValue nEndTick = GetEndTick();
	int nTickPerFrame = GetTickPerFrame();

	track.bTiling = FALSE;

	StdUVGen *uv = NULL;
	Texmap *tx = pStdMtl->GetSubTexmap(ID_OP);;
	if( tx )
	{
		if( tx->ClassID() == Class_ID( BMTEX_CLASS_ID, 0 ) )
		{
			BitmapTex *bmt = (BitmapTex*)tx;
			uv = bmt->GetUVGen();
			if( uv )
			{
				track.nUTile = (int)uv->GetUScl(0);
				track.nVTile = (int)uv->GetVScl(0);
				if( track.nUTile == 1 && track.nVTile == 1 )
					track.bTiling = FALSE;
				else
					track.bTiling = TRUE;
				track.nStartFrame = bmt->GetStartTime();
				track.fPlaybackRate = bmt->GetPlaybackRate();
			}
		}
	}
	//uv->GetUScl(0);
	//uv->GetVScl(0);
	// 计算帧数
	TimeValue t;
	for( t = nStartTick; t <= nEndTick; t += nTickPerFrame )
		nFrameCount++;
	//track.pMatrices = new HR3D_Matrix[track.nFrameCount];
	track.vectorColorKey.reserve( nFrameCount );
	track.vectorColorKey.resize( nFrameCount );

	t = nStartTick;
	for( int i = 0; i < nFrameCount; i++, t += nTickPerFrame )
	{
		HR3D_Mdx2ColorKey key;
		memset( &key, 0x00, sizeof( key ) );
		Color diffuse	= pStdMtl->GetDiffuse( t );
		Color ambient	= pStdMtl->GetAmbient( t );
		Color specular	= pStdMtl->GetSpecular( t );
		//Color specular( 1.0f, 1.0f, 1.0f );
		Color filter	= pStdMtl->GetFilter( t );
		float alpha		= pStdMtl->GetOpacity( t );
		float shinstr	= pStdMtl->GetShinStr(t);//pStdMtl->GetShininess( t );
		//float shinstr = 0.2;
		float selfillum = pStdMtl->GetSelfIllum( t );

		float uoffset	= 0;
		float voffset	= 0;
		if( uv )
		{
			uoffset	= uv->GetUOffs( t );
			voffset	= uv->GetVOffs( t );
		}

		int	nTransparencyType = pStdMtl->GetTransparencyType();

		key.dwBlendMode = 0;
		switch( nTransparencyType )
		{
		case TRANSP_SUBTRACTIVE:
			key.dwBlendMode |= HR3D_MDX2_MODULATE;
			break;
		case TRANSP_ADDITIVE:
			key.dwBlendMode |= HR3D_MDX2_ADD;
			break;
		case TRANSP_FILTER:
			key.dwBlendMode |= HR3D_MDX2_MODULATE2X;
			break;
		default:
			break;
		};

		key.dr = diffuse.r;
		key.dg = diffuse.g;
		key.db = diffuse.b;

		key.ar = ambient.r;
		key.ag = ambient.g;
		key.ab = ambient.b;

		key.sr = specular.r;
		key.sg = specular.g;
		key.sb = specular.b;

		key.alpha = alpha;
		key.shinstr = shinstr;
		key.selfillum = selfillum;


		if( uv )
		{
			key.uoffset = uv->GetUOffs( t );
			key.voffset = uv->GetVOffs( t );
		}
		else
		{
			key.uoffset = 0;
			key.voffset = 0;
		}

		track.vectorColorKey[i] = key;

		// 打印材质动画每一帧的材质Alpha值
		static char temp[32] = {0};
		sprintf_s(temp, 32, "alpha: %f, %d\n", alpha, (int) alpha * 255);
		OutputDebugString(temp);
	}
	return true;
}

BOOL HR3D_MaxInterface::ConvertBoneName()
{
	ClearNodeTree();
	GetNodeTree( NULL );
	char* table[][2] = 
	{
		"Bip01 Head",			"Head",
		"Bip01 L Calf",			"L_Calf",
		"Bip01 L Clavicle",		"L_Clavicle",
		"Bip01 L Foot",			"L_Foot",
		"Bip01 L ForeArm",		"L_ForeArm",
		"Bip01 L Hand",			"L_Hand",
		"Bip01 L Thigh",		"L_Thigh",
		"Bip01 L Toe0",			"L_Toe0",
		"Bip01 L UpperArm",		"L_UpperArm",
		"Bip01 Neck",			"Neck",
		"Bip01 Pelvis",			"Pelvis",
		"Bip01 Ponytail1",		"Ponytail1",
		"Bip01 Ponytail2",		"Ponytail2",
		"Bip01 Ponytail11",		"Ponytail11",
		"Bip01 Ponytail21",		"Ponytail21",
		"Bip01 R Calf",			"R_Calf",
		"Bip01 R Clavicle",		"R_Clavicle",
		"Bip01 R Foot",			"R_Foot",
		"Bip01 R ForeArm",		"R_ForeArm",
		"Bip01 R Hand",			"R_Hand",
		"Bip01 R Thigh",		"R_Thigh",
		"Bip01 R Toe0",			"R_Toe0",
		"Bip01 R UpperArm",		"R_UpperArm",
		"Bip01 Spine",			"Spine",
		"Bip01 Tail",			"Tail",
		"Bip01 Tail1",			"Tail1",
		NULL,
	};
	for( int i = 0; i < GetNodeCount(); i++ )
	{
		INode* pNode = GetNode( i );
		char szName[256];
		strcpy( szName, pNode->GetName() );
		int nLength = strlen( szName );

		// 忽略所有的nub名字结尾的node
		if( nLength > 3 &&
			strnicmp( &szName[nLength-3], "nub", 3 ) == 0 )
			continue;

		// 如果是骨骼
		if( !IsBone( pNode ) )
			continue;
		if( !IsBipedBone( pNode ) )
			continue;
		for( int j = 0; ; j++ )
		{
			if( table[j][0] == NULL )
				break;
			if( stricmp( szName, table[j][0] ) == 0 )
			{
				pNode->SetName( table[j][1] );
			}
		}
	}

	return TRUE;
}
BOOL HR3D_MaxInterface::GetStdMtlChannelBitmapFileName( StdMat* pStdMat, int nChannel, char szFileName[] )
{
	if( !pStdMat )
	{
		assert( false );
		return FALSE;
	}
	Texmap *tx = pStdMat->GetSubTexmap(nChannel);
	if( !tx  )
		return FALSE;
	if(tx->ClassID() != Class_ID(BMTEX_CLASS_ID,0))
		return FALSE;
	BitmapTex *bmt = (BitmapTex*)tx;
	strcpy( szFileName, bmt->GetMapName() );
	return TRUE;
}