#include "net_crypt.h"

/* default encrypt/decrypt function key. */
static const char chKey = 0x66;

void default_encrypt_func (void *logicdata, char *buf, int len)//加密
{
	int i;
	if (len <= 0)
		return;
	for (i = 0; i < len; ++i)
	{
		buf[i] ^= chKey;
	}
}

void default_decrypt_func (void *logicdata, char *buf, int len)//解密
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
	译码与解码--“一次一密码乱本(one-time pad)”的变体
	“一次一密码乱本(one-time pad)”原为高度机密，但是因为此处密钥不是真随机密钥所以机密度
	不高。此处密钥根据几个初始字符、明文以及生成的秘文字符共同组合形成。因为密钥选取方式的变化
	一个密钥字符的改变一般将引起多个密文字符的改变。

	明文与密文字符的取值范围都是' '至'~'暨0x20至0xfe。明文与秘文存储容量保持一致。

	整个字符串采用“一次一密码乱本(one-time pad)”的变体法加密存储。运算速度非常快。
*/
#define NUM_FIX_HEAD_CHARA		13	// 值 N
#define NUM_FIX_CIPHER_CHARA	128	// 值 KeyLen
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
	// 1、取包头的前N个字节计算出一个值M 对这前N个字节采用普通加密
	if ( len <= NUM_FIX_HEAD_CHARA )
		return;

	for (i = 0; i < NUM_FIX_HEAD_CHARA; ++i) 
	{
		nValueM += (buf[i]*buf[i]);
		buf[i] ^= cHeadCipher[i];
	}
	// 2、得到keys的index  对后面的字节进行加密
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
	// 1、先对包头的前N个字节解密  取包头的前N个字节计算出一个值M
 	if ( len <= NUM_FIX_HEAD_CHARA )
 		return;

 	for (i = 0; i < NUM_FIX_HEAD_CHARA; ++i) 
 	{
 		buf[i] ^= cHeadCipher[i];
 		nValueM += (buf[i]*buf[i]);
 	}
 	// 2、得到keys的index  对后面的字节进行解密
 	nKeyindex = nValueM % NUM_FIX_CIPHER_CHARA;
 	for (i = NUM_FIX_HEAD_CHARA; i < len; ++i,++nKeyindex) 
 	{
 		if ( nKeyindex >= NUM_FIX_CIPHER_CHARA ) nKeyindex = 0;
 		buf[i] ^= cCipher[nKeyindex];
 	}
}


