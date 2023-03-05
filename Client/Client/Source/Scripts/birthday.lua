
--[[
	判断是否是玩家生日。
	
	@param currYear, currMonth, currDay 天机当前时间。
	@param charYear, charMonth, charDay 玩家时间。
]]--
function isBirthday( currYear, currMonth, currDay, charYear, charMonth, charDay )
	return currYear - charYear >= 1 &&
		currMonth == charMonth &&
		currDay ==  charDay;

end