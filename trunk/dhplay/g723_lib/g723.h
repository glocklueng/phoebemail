#ifndef _G723_H_
#define _G723_H_

typedef enum 
{
	G723_63, 
	G723_53
} eG723Mode;


int g723enc_init(void** handle,eG723Mode mode);	//�����ʼ�� 
int g723dec_init(void** handle);	//�����ʼ��
int g723enc_mode(void* handle, eG723Mode mode);	//���ñ���ģʽ
int g723enc(void* handle, short* sample, char* bits, int src_len, int* out_len);	//����
int g723dec(void* handle, char* bits,  short* out, int bits_len, int* out_len);		//����
int g723enc_close(void** handle);	//�رձ���
int g723dec_close(void** handle);	//�رս���

#endif

