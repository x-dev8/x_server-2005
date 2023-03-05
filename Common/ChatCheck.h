/*
**		�����ַ�
*/
#pragma once

#include<vector>

#define WARN_STRING			"���ķ������в������ۣ�"
#define MARK_CHAR_STAR		'*'
#define MARK_CHAR_X			'X'

#define theChatCheck CChatCheck::getInstance()
class CChatCheck
{
public:
	static CChatCheck* getInstance()
	{
		static CChatCheck instance;
		return &instance;
	}
public:
	bool			LoadUndueString(const char* slkname);
	bool			LoadSpecialCharFilterString(const char* filename);				//�����ַ�����
	bool			CheckStringInLow(const char* szStr);										//�������벻�Ϸ�
	std::string		CheckStringInLowMark(char* szStr,char cMark);					//�����Ϸ����ַ�ת��ΪMARK_CHAR�������

    bool            CheckStringInForbit(const char* pszStr);    //��ֹ�Ƿ��ַ�
	//static ��Ϊ����ͨ���� �����ַ������ λ��ǰ�Ƿ�ضϺ�����....
    static bool		CheckPosationInLow(const std::string& str, int nOff );		//������滻��λ���Ƿ��������ж�
    static bool		CheckPosationInLow(const std::wstring& str, int nOff );		//������滻��λ���Ƿ��������ж�
    
private:
	int lowbyte;
	std::vector<std::wstring> vecUndueStringList;
    std::vector<std::wstring> vecForbitStringList;
};
