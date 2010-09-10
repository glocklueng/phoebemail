/*
* Copyright (c) 2008, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�TPMulticastClient.h
* ժ����Ҫ���ಥ�ͻ��˹�����
*
*
* ȡ���汾��0.1
* ԭ���ߡ���Peng Dongfeng
* ������ڣ�2008��8��6��
* �޶���¼������
*/
//////////////////////////////////////////////////////////////////////

#ifndef _TPMulticastClient_H_
#define _TPMulticastClient_H_

#include "TPUDPClient.h"


class TPMulticastClient : public TPUDPClient
{
public:
    TPMulticastClient(ITPListener *callback, int engineId = 0);
    virtual ~TPMulticastClient();


public:	/* �ӿ� */
	virtual int Close(void);

	virtual int Connect(const char* szIp, int nPort);

	virtual int Connect(const char* szLocalIp, int nLocalPort, const char* szRemoteIp, int nRemotePort);


private:
	SOCKET	m_sockMultipoint;
};

#endif // _TPMulticastClient_H_
