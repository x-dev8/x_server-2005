inline bool MexAnimCtrl::IntersectQuick(MexAnimCtrl* pAnimCtrl, D3DXVECTOR3 *pvRay,D3DXVECTOR3 *pvDir)
{
	// added, jiayi, [2009.4.20]
	//pAnimCtrl->UpdateBillboardBBox();

	if( !pAnimCtrl->GetWorldBBox()->Intersect( 
		*(Vector*)pvRay,
		*(Vector*)pvDir ) )
		return false;

	if( !pAnimCtrl->IntersectRayQuick( (Vector*)pvRay,(Vector*)pvDir ) ) 
		return false;	
	return true;

}
inline void MexAnimCtrl::SetTransform( float* pMatrix )
{
	memcpy( &m_matTransform, pMatrix, sizeof( float )*16 );
}
