
--[[
	�ж��Ƿ���������ա�
	
	@param currYear, currMonth, currDay �����ǰʱ�䡣
	@param charYear, charMonth, charDay ���ʱ�䡣
]]--
function isBirthday( currYear, currMonth, currDay, charYear, charMonth, charDay )
	return currYear - charYear >= 1 &&
		currMonth == charMonth &&
		currDay ==  charDay;

end