inline bool CNdlWorldPickerBase::IsShadow(float nTileX, float nTileY , CWorldTile* tile /* = 0 */)
{

	if( !tile )
		tile = m_worldBuffer->GetActiveTile();
	if( !tile )
		return false;

	CWorldChunk* worldChunk =  tile->GetChunkFromPos(nTileX,nTileY);
	if( NULL == worldChunk )
		return false;	

	// jiayi, [2009.4.13]
	//下面的16和4两个数值是为了速度考虑，直接写出
	sInt32 nXinChunk = ((int)nTileX) % 16;
	sInt32 nYinChunk = ((int)nTileY) % 16;

	sInt32 nXinShadow = nXinChunk << 2;
	sInt32 nYinShadow = nYinChunk << 2;

	return worldChunk->IsInShadow( nXinShadow, nYinShadow );	

}