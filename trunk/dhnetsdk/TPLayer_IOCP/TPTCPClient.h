/*
* Copyright (c) 2008, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�TPTCPClient.h
* ժ����Ҫ��TCP�ͻ��˹�����
*
*
* ȡ���汾��0.1
* ԭ���ߡ���Peng Dongfeng
* ������ڣ�2008��6��16��
* �޶���¼������
*/
//////////////////////////////////////////////////////////////////////

#ifndef _TPTCPClient_H_
#define _TPTCPClient_H_

#include "ITPObject.h"


class TPTCPClient : public ITPObject, protected IOCPListener
{
public:
    TPTCPClient(ITPListener *tcpclientapp, int engineId = 0);
    virtual ~TPTCPClient();


public:	/* �ӿ� */
    virtual int Close(void);

    virtual int Connect(const char* szIp, int nPort, int nTimeOut=1500);

	virtual int Connect(const char* szLocalIp, int nLocalPort, const char* szRemoteIp, int nRemotePort);

    virtual int Send(int id, IBufferRef pSendBuf);

	//	������������Ϣ
	virtual int	SetKeepLifePacket(unsigned char *pLifePacketBuf, int nBufLen, unsigned int nKeepLifeTime);

	//	�����������������ߣ���������
    virtual int Heartbeat(void);


public:	/* �ڲ���ɶ˿ڻص� */

	virtual int onIOData(int nEngineId, int nConnId, unsigned char* data, int nLen, BOOL bPostSuccess);

	virtual int onIODealData(int nEngineId, int nConnId, unsigned char* buffer, int nLen);

	virtual int onIODisconnect(int nEngineId, int nConnId);

	virtual int onIOSendDataAck(int nEngineId, int nConnId, int nId, BOOL bPostSuccess);


protected:
	int		CreateClientEnvironment();
	int		ClearClientEnvironment();
	int		closeInside();
	int		IsConnected();


protected:
	CPerIoData		*m_pPerIoRecv;		// Receive PerIoData
	CPerHandleData	*m_pPerHandleData;	// Socket PerHandle

	BOOL			m_bIsPostSend;		// �Ƿ����Ͷ�ݷ���
	Queue_List		m_lstSendQueue;
	CReadWriteMutex	m_csSendQueue;
	
	int				m_nLifePacketLen;
	IBufferRef		m_lifePacketBuf;						// ����������
	unsigned int	m_nKeepLifeTime;						// �������
	unsigned long	m_dwLastReceiveTime;					// ���һ�ν�������ʱ��
	unsigned long	m_dwLastHeartBeatTime;					// ���һ�η���������ʱ��

	BOOL			m_bCreateEnable;
	unsigned long	m_dwLastConTime;	// ���һ��connectʱ��
	BOOL			m_bOnline;			// �Ƿ�����
	CReadWriteMutex	m_csOnline;

	DWORD			m_dwLastDealTime;
	BOOL			m_bLastStatus;
	int				m_nDealData;
	CReadWriteMutex m_csDealData;
};

#endif // _TPTCPClient_H_
