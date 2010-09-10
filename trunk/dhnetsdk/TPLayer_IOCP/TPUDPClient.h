/*
* Copyright (c) 2008, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�TPUDPClient.h
* ժ����Ҫ��UDP�ͻ��˹�����
*
*
* ȡ���汾��0.1
* ԭ���ߡ���Peng Dongfeng
* ������ڣ�2008��8��6��
* �޶���¼������
*/
//////////////////////////////////////////////////////////////////////

#ifndef _TPUDPClient_H_
#define _TPUDPClient_H_

#include "ITPObject.h"


class TPUDPClient : public ITPObject, protected IOCPListener
{
public:
    TPUDPClient(ITPListener *callback, int engineId = 0);
    virtual ~TPUDPClient();


public:	/* �ӿ� */
    virtual int Close(void);

    virtual int Connect(const char* szIp, int nPort);

	virtual int Connect(const char* szLocalIp, int nLocalPort, const char* szRemoteIp, int nRemotePort);

    virtual int Send(int id, IBufferRef pSendBuf);


public:	/* �ڲ���ɶ˿ڻص� */
	virtual int onIOData(int nEngineId, int nConnId, unsigned char* data, int nLen, BOOL bPostSuccess);

	virtual int onIODealData(int nEngineId, int nConnId, unsigned char* buffer, int nLen);

	virtual int onIODisconnect(int nEngineId, int nConnId);

	virtual int onIOSendDataAck(int nEngineId, int nConnId, int nId, BOOL bPostSuccess);


protected:
	int		CreateClientEnvironment();
	int		ClearClientEnvironment();


protected:
	CPerIoData		*m_pPerIoRecv;		// Receive PerIoData
	CPerHandleData	*m_pPerHandleData;	// Socket PerHandle

	BOOL			m_bIsPostSend;		// �Ƿ����Ͷ�ݷ���
	Queue_List		m_lstSendQueue;
	CReadWriteMutex	m_csSendQueue;

	DWORD			m_dwLastDealTime;
	BOOL			m_bLastStatus;
	BOOL			m_bIsDealData;
	CReadWriteMutex m_csDealData;
};

#endif // _TPUDPClient_H_
