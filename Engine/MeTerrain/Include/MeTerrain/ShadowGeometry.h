/*******************************************************************************
* Copyright ShenWang 2008 - All Rights Reserved
* 
* File: 	ShadowGeometry.h
* Create: 	12/11/2008
* Desc:		渲染阴影
* Author:	Qiu Li
*
* Modify:
* Modify by:
*******************************************************************************/
#ifndef SHADOWGEOMETRY_H
#define SHADOWGEOMETRY_H

NiSmartPointer(NiCamera);
NiSmartPointer(NiPropertyState);
NiSmartPointer(NiRenderTargetGroup);
NiSmartPointer(NiTexture);

#define BLUR_KERNEL_SIZE 9

class ShadowGeometry : public NiMemObject
{
public:
    // The shadow will be rendered from the caster geometry each frame.
    // The detail value is the log2 of the size of the shadow texture.
    // The max triangle count is the max number of shadow recipient (ground)
    // triangles that can receive the shadow at once.  Set too small, this
    // could result in objects in the area of the shadow not being shadowed
    // correctly.
    static ShadowGeometry* Create(unsigned int uiDetail = 6, 
        unsigned int uiMaxTriangleCount = 0);

    ~ShadowGeometry();
    
    // Render the shadow texture
    void Click(float fTime, NiCamera* pkSceneCamera, bool bRealShadow = false,
        bool bVisible = true, bool bUpdateImage = true);

    void AddCaster(NiAVObject* pkCaster, NiCamera* camera);		// 这个相机用于获取模型的LOD数据，所以只要高度够远，具体位置没要求
	void RemoveCaster(NiAVObject* pkCaster);
	void RemoveAllCasters();
	void AddFakeCaster(NiMesh* pkFakeCaster);					// 添加假阴影

    void AddGroundSceneGraph(NiAVObject* pkGround);
	void ClearGroundScene() {m_spGroundList.clear();};
    NiMesh* GetShadowGeometry() const;
    void ForceRender(); // necessary if alt-tab detected
	bool NeedRender();
	void SetLightDir(const NiPoint3& kLightDir);
	void RestoreLightDir();
	NiMesh* GetFakeShadowModel() {return m_spFakeCaster;};

protected:
    ShadowGeometry(unsigned int uiMaxTriangleCount);

    void UpdateShadowCamera(float fTime);
    void UpdateShadowGeometry();
    void UpdateShadowGeometryBound();
    void TraverseGroundGeometry(NiAVObject* pkObject);
    void AddToShadowGeometry(NiMesh* pkMesh);
    void AddShadowTriangle(NiPoint3 akV[3]);
    void RecursiveStoreCasterObjects(NiAVObject* pkObject, NiCamera* camera=NULL, bool bAdd = true);	// bAdd为false则移除
    bool GenerateCameraRay(unsigned int uiIndex, NiPoint3& kPt, 
        NiPoint3& kDir);
    void CullTriAgainstCameraFrustum(NiPoint3& kV0, NiPoint3& kV1, NiPoint3& kV2);
    // Initial max triangle and vertex counts allowed when generating the
    // set of geometry subtended by the shadow (i.e. shadow "recipient"
    // geometry).  This method is independent of "caster" geometry count, as
    // the system renders the shadow to a texture (or uses a loaded texture)
    enum { TRIANGLE_COUNT = 200, VERTEX_COUNT = 600 };

    // Leaf geometry objects in the shadow caster scene.  If the shadow is
    // dynamically rendered, we will render these as a flat list (a batch
    // rendering).  They are found by traversing the m_spCaster for leaf 
    // geometry
    NiTObjectSet<NiAVObjectPtr> m_kCastingObjects;

    // The tree containing all objects that will cast a shadow upon the scene
    // Used only in the case that the shadow is dynamically rendered per frame
    NiAVObjectPtr m_spCaster;

	// 假阴影，用椭圆形面片
	NiMeshPtr m_spFakeCaster;

    // A very distant camera, designed to represent an infinite light source
    NiCameraPtr m_spCamera;

    // The shadow texture which will be rendered each frame to represent the
    // shadow geometry as seen from the casting light's POV
    NiTexturePtr m_spTexture;

    // The render target used by the system to render the shadow geometry
    NiRenderTargetGroupPtr m_spRenderTargetGroup;

    // Root of the scene upon which shadow will be cast (the "recipient")
	std::vector<NiAVObjectPtr> m_spGroundList;

    // Current recipient geometry, created from triangles in the m_spGround
    // scene that intersect the cast shadow volume.  This is a dynamic object
    // and will be refilled each frame
    NiMeshPtr m_spShadowGeometry;

    // Streams on the mesh
    NiDataStream* m_pkPositionStream;
    NiDataStream* m_pkTexCoordStream;
    NiDataStream* m_pkIndexStream;

    // A property state that causes the shadow caster to be rendered as dark
    // gray into the white background of the shadow image.  Used when drawing
    // the shadow caster geometry into the shadow texture.
    NiPropertyStatePtr m_spPropertyState;
	NiPropertyStatePtr m_spFakePropertyState;

    NiPoint3 m_kLightDir;
    NiPoint3 m_kCenterP;			// 阴影中心点
	float	 m_fRadius;				// 阴影半径
    float m_fOOWidth;

    // Limits on the amount of ground (recipient) geometry that can be added
    // to m_spShadowGeometry, to avoid overflowing (or having to resize) the
    // geometry arrays
    unsigned int m_uiMaxTriangleCount;
    unsigned int m_uiMaxVertexCount;

    // Disables fast culling of the shadow casters w.r.t. the shadow camera
    // Useful to ensure that the texture is rendered the first time around
    // or when the application loses focus (via Alt-Tab)
    bool m_bForceRender;

    NiMeshCullingProcess m_kCuller;
    NiFrustumPlanes m_kFrPlanes;
    NiVisibleArray m_kVisible;

	NiPick*				m_pkPick;

	bool				m_bRealShadow;

	float				fAddTriangleTime;
	float				fAddGeometryTime;
	int					nShadowTriCount;

	float				fFakeCasterRotateZ;
};

//----------------------------------------------------------------------------
inline NiMesh* ShadowGeometry::GetShadowGeometry() const
{ 
	return m_spShadowGeometry; 
}
//----------------------------------------------------------------------------
inline void ShadowGeometry::ForceRender()
{
	m_bForceRender = true;
}
//----------------------------------------------------------------------------
inline void ShadowGeometry::RemoveAllCasters()
{
	m_spCaster = NULL;
	m_kCastingObjects.RemoveAll();
}
//----------------------------------------------------------------------------
inline void ShadowGeometry::RestoreLightDir()
{
	m_kLightDir = NiPoint3(0.66f, -0.1f, -0.9f);
	m_kLightDir.Unitize();
}
//----------------------------------------------------------------------------

#endif // SHADOWGEOMETRY_H

