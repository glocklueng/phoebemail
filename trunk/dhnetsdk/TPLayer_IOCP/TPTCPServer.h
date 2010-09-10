/*
* Copyright (c) 2008, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�TPTCPServer.h
* ժ����Ҫ��TCP������������
*
*
* ȡ���汾��0.1
* ԭ���ߡ���Peng Dongfeng
* ������ڣ�2008��6��16��
* �޶���¼������
*/
//////////////////////////////////////////////////////////////////////

#ifndef TPTCPSERVER
#define TPTCPSERVER

#include "ITPObject.h"


class TPTCPServer : public ITPObject, protected IOCPListener
{
public:
    TPTCPServer(ITPListener* tcpserverapp, int engineId = 0);
    virtual ~TPTCPServer();


public: /* �ӿ� */
    virtual int CloseClient(int connId);

    virtual int Close();
    
	virtual int Listen(const char* szIp, int nPort);
    
    virtual int Send(int connId, int id, IBufferRef pSendBuf);

    virtual int Heartbeat();


public:	//�ڲ�����
	virtual int onIOData(int nEngineId, int nConnId, unsigned char* data, int nLen, BOOL bPostSuccess);

	virtual int onIODealData(int nEngineId, int nConnId, unsigned char* buffer, int nLen);

	virtual int onIODisconnect(int nEngineId, int nConnId);

	virtual int onIOSendDataAck(int nEngineId, int nConnId, int nId, BOOL bPostSuccess);

	virtual	int	ListenSocket();

	//	�麯����������дAccept����ʽ
	virtual int	DealNewSocket(SOCKET newsock, int nConnId, char* szIp, int nPort);

	
protected:
	int		CreateClientEnvironment(CConnClientData *pClientConn);
	int		ClearClientEnvironment(CConnClientData *pClientConn);


protected:
	HANDLE			m_hListenThread;
	HANDLE			m_hListenExitEvent;

	CONN_MAP		m_lstConnClients;
	CReadWriteMutex	m_csClientsMap;
};

#endif
