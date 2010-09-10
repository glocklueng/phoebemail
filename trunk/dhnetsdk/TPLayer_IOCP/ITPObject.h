/*
* Copyright (c) 2008, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�ITPObject.h
* ժ����Ҫ�������ӿڳ����࣬����ɶ˿�ģ����ʵ�֣�ֻ����Windowsϵͳ��
*
*
* ȡ���汾��0.1
* ԭ���ߡ���Peng Dongfeng
* ������ڣ�2008��6��16��
* �޶���¼������
*/
//////////////////////////////////////////////////////////////////////

#ifndef _ITPOBJECT_H_
#define _ITPOBJECT_H_

#include "TPTypedef.h"
#include "ITPListener.h"


#define RECEIVE_BUFFER_SIZE	(64*1024)
#define MAX_PACKET_SIZE		(50*1024)
#define MAX_DEAL_SPANTIME	(10)	//ms

class ITPObject  
{
public:
	ITPObject();
	virtual ~ITPObject();


public:
	//	������ʼ���������������
	static int Startup(void);
	static int Cleanup(void);
	
	static long GetNewClientId();
	static long GetNewPort();

	//	����socket����ɶ˿�
	int	AddSocketToIOCP(SOCKET socket, CPerHandleData *pPerHandleData);

	//	����ɶ˿����Ƴ�socket
	int	DelSocketFromIOCP(SOCKET socket, CPerHandleData *pPerHandleData);

	//	Ͷ��һ������
	int	PostRecvToIOCP(SOCKET socket, CPerIoData *pPerIoRecv);

	//	Ͷ��һ������
	int	PostSendToIOCP(SOCKET socket, CPerIoData *pPerIoSend);


public:	/* �����෽�� */

	//	���õײ��׽��ֻ�������С��type��ʾ�Ƿ��ͻ��������ǽ��ջ�����
	int SetSocketBufferSize(TP_DATA_TYPE type, int size);

	//	��ȡ�ײ��׽��ֻ�������С��type��ʾ�Ƿ��ͻ��������ǽ��ջ�����
	int GetSocketBufferSize(TP_DATA_TYPE type);

	//	���ô�������selectʱ�ĳ�ʱֵ���������ֵ��Ĭ����sec=0;usec=10;
	//...�������Ϊ0���ʾΪ��ѭ״̬
	int SetSelectTimeout(long sec, long usec);

	//	�����Ƿ��������
	int	SetIsReconnect(int nEnable);

	//	�����Ƿ���߼��
	int	SetIsDetectDisconn(int nEnable);

	//	���÷����ж���󳤶ȣ��������˳��Ȼᷢ��ʧ��
	int	SetMaxSendQueue(int size);

	//	��ȡ�ײ��׽��ְ󶨵ĵ�ַ�Ͷ˿ں�
	int	GetSocketBindInfo(char *szIp, int &nPort);


protected:
	int	Create(opMode type);

	int	GetLocalIP(char *szIp);

protected:
	unsigned long	m_remoteIp;			// IP,PORT ���������ֽ���
	unsigned short	m_remotePort;
	unsigned long	m_localIp;
	unsigned short	m_localPort;
	SOCKET			m_socket;

	int				m_engineId;
	ITPListener		*m_listener;

	int				m_recvBuffSize;
	int				m_sendBuffSize;

	BOOL			m_bDisCallBack;	// �Ƿ���Զ��߻ص�
	BOOL			m_bReconnEn;	// �Ƿ��������
	BOOL			m_bDetectDisconn; // �Ƿ���߼��

	long			m_timeout_sec;
	long			m_timeout_usec;

	int				m_nSendQueueSize;
	unsigned int	m_nDetectDisconnTime;	//���߼��ʱ��
};

#endif // _ITPOBJECT_H_
