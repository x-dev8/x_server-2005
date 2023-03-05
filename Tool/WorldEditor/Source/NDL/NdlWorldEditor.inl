inline bool CNdlWorldEditor::IsPointInTriangle(D3DXVECTOR2 &va, D3DXVECTOR2 &vb, D3DXVECTOR2 &vc, D3DXVECTOR2 &vp, float& u, float& v)
{
	// Compute vectors        
	D3DXVECTOR2 v0 = vc - va;
	D3DXVECTOR2 v1 = vb - va;
	D3DXVECTOR2 v2 = vp - va;	

	// Compute dot products
	float dot00 = D3DXVec2Dot(&v0, &v0);
	float dot01 = D3DXVec2Dot(&v0, &v1);
	float dot02 = D3DXVec2Dot(&v0, &v2);
	float dot11 = D3DXVec2Dot(&v1, &v1);
	float dot12 = D3DXVec2Dot(&v1, &v2);

	// Compute barycentric coordinates
	float invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
	u = (dot11 * dot02 - dot01 * dot12) * invDenom;
	v = (dot00 * dot12 - dot01 * dot02) * invDenom;

	// Check if point is in triangle
	return (u >= 0) && (v >= 0) && (u + v <= 1);
}

