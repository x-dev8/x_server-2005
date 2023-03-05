#ifndef _H_NET_CRYPT_FUNCTION_DEF_H_
#define _H_NET_CRYPT_FUNCTION_DEF_H_

#ifdef __cplusplus
extern "C"{
#endif

// ���Ҫʹ��һ��һ�����ұ��Ͷ��������
//#define  OneTimePad

typedef void (*dofunc_f) (void *logicdata, char *buf, int len);

void default_encrypt_func (void *logicdata, char *buf, int len);//����

void default_decrypt_func (void *logicdata, char *buf, int len);//����


void OneTimePad_Encrypt_Func(void *logicdata, char *buf, int len);

void OneTimePad_Decrypt_Func(void *logicdata, char *buf, int len);

#ifdef __cplusplus
}
#endif
#endif

