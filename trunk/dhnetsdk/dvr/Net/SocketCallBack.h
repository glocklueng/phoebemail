/*
* Copyright (c) 2009, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �����ƣ�TCP���մ�����
* ժ��Ҫ����TCP�����н������ְ�����������Ӧ�Ĺ���ģ�鴦��
*         ������ݣ������������Ͱ���š�
*
*/
//////////////////////////////////////////////////////////////////////////

#ifndef _SOCKETCALLBACK_H_
#define _SOCKETCALLBACK_H_


// �����ӽ������ݴ���
int __stdcall OnOtherPacket(unsigned char *pBuf, int nLen, void *userdata);

// ��������������ͳ��
int __stdcall OnReceivePacket(unsigned char *pBuf, int nLen, void *userdata);

// �����Ӷ���
int __stdcall OnDisconnect(void *userdata);

// �����Ӷ��߻ָ�
int	__stdcall OnReConnect(void *userdata);

// �����ӽ������ݴ���
int __stdcall OnSubOtherPacket(unsigned char *pBuf, int nLen, void *userdata);

// ��������������ͳ��
int __stdcall OnSubReceivePacket(unsigned char *pBuf, int nLen, void *userdata);

// �����Ӷ���
int __stdcall OnSubDisconnect(void *userdata);

// �����Ӷ��߻ָ�
int	__stdcall OnSubReConnect(void *userdata);


#endif // _SOCKETCALLBACK_H_




