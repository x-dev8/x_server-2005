
-- 设置装备特效
function setEquipEffect()
	local playerAnimParam = Equip.getCurrentEquipParam();
	local playerAnim = Equip.getCurrentEquipPlayerAnim();
	
	local equip = playerAnimParam:getCurrentEquip();
	
	if equip.item.equipdata.nIntensifyTime == 0 then
		playerAnim:setEquipEffect( playerAnimParam.nPart, "DATA\\TEXTURES\\Effect\\cp_lava1.tga" );
	end
end