#include "net_crypt.h"

/* default encrypt/decrypt function key. */
static const char chKey = 0x66;

void default_encrypt_func (void *logicdata, char *buf, int len)//����
{
	int i;
	if (len <= 0)
		return;
	for (i = 0; i < len; ++i)
	{
		buf[i] ^= chKey;
	}
}

void default_decrypt_func (void *logicdata, char *buf, int len)//����
{
	int i;
	if (len <= 0)
		return;
	for (i = 0; i < len; ++i) 
	{
		buf[i] ^= chKey;
	}
}


/* 
	���������--��һ��һ�����ұ�(one-time pad)���ı���
	��һ��һ�����ұ�(one-time pad)��ԭΪ�߶Ȼ��ܣ�������Ϊ�˴���Կ�����������Կ���Ի��ܶ�
	���ߡ��˴���Կ���ݼ�����ʼ�ַ��������Լ����ɵ������ַ���ͬ����γɡ���Ϊ��Կѡȡ��ʽ�ı仯
	һ����Կ�ַ��ĸı�һ�㽫�����������ַ��ĸı䡣

	�����������ַ���ȡֵ��Χ����' '��'~'��0x20��0xfe�����������Ĵ洢��������һ�¡�

	�����ַ������á�һ��һ�����ұ�(one-time pad)���ı��巨���ܴ洢�������ٶȷǳ��졣
*/
#define NUM_FIX_HEAD_CHARA		13	// ֵ N
#define NUM_FIX_CIPHER_CHARA	128	// ֵ KeyLen
static char cHeadCipher[NUM_FIX_HEAD_CHARA+1] =  "gcloudfg12321";
static char cCipher[NUM_FIX_CIPHER_CHARA+1]   =  "abcdefghij123456" 
												 "bcdefghijk234567"
												 "cdefghijkl345678"
												 "defghijklm456789"
												 "efghijklmn012345"
												 "fghijklmno567890"
												 "ghijklmnop567891"
												 "momomomomn678901";

void OneTimePad_Encrypt_Func(void *logicdata, char *buf, int len)
{
	int nValueM = 0 ,i = 0 ,nKeyindex = 0;
	// 1��ȡ��ͷ��ǰN���ֽڼ����һ��ֵM ����ǰN���ֽڲ�����ͨ����
	if ( len <= NUM_FIX_HEAD_CHARA )
		return;

	for (i = 0; i < NUM_FIX_HEAD_CHARA; ++i) 
	{
		nValueM += (buf[i]*buf[i]);
		buf[i] ^= cHeadCipher[i];
	}
	// 2���õ�keys��index  �Ժ�����ֽڽ��м���
	nKeyindex = nValueM % NUM_FIX_CIPHER_CHARA;
	for (i = NUM_FIX_HEAD_CHARA; i < len; ++i,++nKeyindex) 
	{
		if ( nKeyindex >= NUM_FIX_CIPHER_CHARA ) nKeyindex = 0;
		buf[i] ^= cCipher[nKeyindex];
	}
}

void OneTimePad_Decrypt_Func(void *logicdata, char *buf, int len)
{
	int nValueM = 0 ,i = 0 ,nKeyindex = 0;
	// 1���ȶ԰�ͷ��ǰN���ֽڽ���  ȡ��ͷ��ǰN���ֽڼ����һ��ֵM
 	if ( len <= NUM_FIX_HEAD_CHARA )
 		return;

 	for (i = 0; i < NUM_FIX_HEAD_CHARA; ++i) 
 	{
 		buf[i] ^= cHeadCipher[i];
 		nValueM += (buf[i]*buf[i]);
 	}
 	// 2���õ�keys��index  �Ժ�����ֽڽ��н���
 	nKeyindex = nValueM % NUM_FIX_CIPHER_CHARA;
 	for (i = NUM_FIX_HEAD_CHARA; i < len; ++i,++nKeyindex) 
 	{
 		if ( nKeyindex >= NUM_FIX_CIPHER_CHARA ) nKeyindex = 0;
 		buf[i] ^= cCipher[nKeyindex];
 	}
}


