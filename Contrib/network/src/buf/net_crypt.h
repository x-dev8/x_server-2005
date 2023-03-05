#ifndef _H_NET_CRYPT_FUNCTION_DEF_H_
#define _H_NET_CRYPT_FUNCTION_DEF_H_

#ifdef __cplusplus
extern "C"{
#endif

// 如果要使用一次一密码乱本就定义这个宏
//#define  OneTimePad

typedef void (*dofunc_f) (void *logicdata, char *buf, int len);

void default_encrypt_func (void *logicdata, char *buf, int len);//加密

void default_decrypt_func (void *logicdata, char *buf, int len);//解密


void OneTimePad_Encrypt_Func(void *logicdata, char *buf, int len);

void OneTimePad_Decrypt_Func(void *logicdata, char *buf, int len);

#ifdef __cplusplus
}
#endif
#endif

