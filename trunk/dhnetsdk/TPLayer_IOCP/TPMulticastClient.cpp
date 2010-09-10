// TPMulticastClient.cpp: implementation of the TPMulticastClient class.
//
//////////////////////////////////////////////////////////////////////

#include "TPMulticastClient.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

TPMulticastClient::TPMulticastClient(ITPListener *callback, int engineId) : TPUDPClient(callback, engineId)
{
	m_sockMultipoint = INVALID_SOCKET;
}

TPMulticastClient::~TPMulticastClient()
{

}

int TPMulticastClient::Connect(const char* szIp, int nPort)
{
	if (szIp == NULL)
    {
        m_remoteIp = INADDR_ANY;
    }
    else
    {
        m_remoteIp = inet_addr(szIp);
    }

    m_remotePort = htons(nPort);

	//	Winsock1.1
// 	//	��create
// 	int nRet = Create(opMode_udp);
// 	if (nRet < 0)
// 	{
// 		return -1;
// 	}
// 
// 
// 	//	����ಥ��
// 	struct ip_mreq	mcast;
// 	int optval = 8;
// 
// 	mcast.imr_multiaddr.s_addr = m_remoteIp;	//	���IP�ಥ��ַ
// 	mcast.imr_interface.s_addr = m_localIp;		//	�ӿڵı���IP��ַ
// 
// 	nRet = setsockopt(m_socket, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char*)&mcast, sizeof(struct ip_mreq));
// 	if (nRet == SOCKET_ERROR)
// 	{
// 		goto e_clean;
// 	}
// 
// 	nRet = setsockopt(m_socket, IPPROTO_IP, IP_MULTICAST_TTL, (char*)&optval, sizeof(int));
// 	if (nRet == SOCKET_ERROR)
// 	{
// 		goto e_clean;
// 	}
// 
// 	optval = 0;
// 	nRet = setsockopt(m_socket, IPPROTO_IP, IP_MULTICAST_LOOP, (char*)&optval, sizeof(optval));
// 	if (nRet == SOCKET_ERROR)
// 	{
// 		goto e_clean;
// 	}

	//	Winsock2.0
	//	��create
	m_socket = WSASocket(AF_INET, SOCK_DGRAM, 0, NULL, 0,
		WSA_FLAG_MULTIPOINT_C_LEAF | WSA_FLAG_MULTIPOINT_D_LEAF | WSA_FLAG_OVERLAPPED);
	if (m_socket == INVALID_SOCKET)
	{
		return -1;
	}

	//	���׽��ֵ�ַ�Ͷ˿�
	if (m_localIp != INADDR_ANY && m_localPort != 0)
	{
		struct sockaddr_in local_addr;
		memset(&local_addr, 0, sizeof(struct sockaddr_in));
		local_addr.sin_family = AF_INET;
		local_addr.sin_port = m_localPort;
		local_addr.sin_addr.s_addr = m_localIp;

		if (INVALID_SOCKET == bind(m_socket, (struct sockaddr *)&local_addr, sizeof(struct sockaddr)))
		{
			closesocket(m_socket);
			m_socket = INVALID_SOCKET;
			return -1;
		}
	}
	else
	{
		//	�����Ϊ�鲥�˿ں�
		char szLocalIp[32] = {0};
		int ret = GetLocalIP(szLocalIp);
		if (ret < 0)
		{
			closesocket(m_socket);
			m_socket = INVALID_SOCKET;
			return -1;
		}
		m_localIp = inet_addr(szLocalIp);

		struct sockaddr_in local_addr;
		memset(&local_addr, 0, sizeof(struct sockaddr_in));
		local_addr.sin_family = AF_INET;
		local_addr.sin_port = m_remotePort;
		local_addr.sin_addr.s_addr = m_localIp;

		if (INVALID_SOCKET == bind(m_socket, (struct sockaddr *)&local_addr, sizeof(struct sockaddr)))
		{
			closesocket(m_socket);
			m_socket = INVALID_SOCKET;
			return -1;
		}
	}

	//	��Ϊ������ģʽ
	unsigned long flags = 1;
	int nRet = ioctlsocket(m_socket, FIONBIO, &flags);
	if (nRet != 0)
	{
		closesocket(m_socket);
		m_socket = INVALID_SOCKET;
		return -1;
	}

	if(m_recvBuffSize > 0)
		setsockopt(m_socket, SOL_SOCKET, SO_RCVBUF, (char*)&m_recvBuffSize, sizeof(int));
	if(m_sendBuffSize > 0)
		setsockopt(m_socket, SOL_SOCKET, SO_SNDBUF, (char*)&m_sendBuffSize, sizeof(int));

	//	����ಥ��
	struct sockaddr_in	remote_addr;
	memset(&remote_addr, 0, sizeof(struct sockaddr_in));
	remote_addr.sin_family = AF_INET;
	remote_addr.sin_port = m_remotePort;
	remote_addr.sin_addr.s_addr = m_remoteIp;
	
	m_sockMultipoint = WSAJoinLeaf(m_socket, (SOCKADDR*)&remote_addr, sizeof(struct sockaddr_in), NULL, NULL, NULL, NULL, JL_BOTH);
	if (m_sockMultipoint == INVALID_SOCKET)
	{
		closesocket(m_socket);
		m_socket = INVALID_SOCKET;
		return -1;
	}
	
	//	�ٴ����ͻ��˻���
	nRet = CreateClientEnvironment();
	if (nRet < 0)
	{
		goto e_clean;
	}

	//	Ȼ��socket��ӵ���ɶ˿���
	nRet = AddSocketToIOCP(m_socket, m_pPerHandleData);
	if (nRet >= 0)
	{
		m_pPerHandleData->AddRef();
		m_pPerIoRecv->AddRef();
		nRet = PostRecvToIOCP(m_socket, m_pPerIoRecv);
		if (nRet < 0)
		{
			m_pPerIoRecv->DecRef();
			m_pPerHandleData->DecRef();

			ClearClientEnvironment();
			goto e_clean;
		}
	}
	else
	{
		ClearClientEnvironment();
		goto e_clean;
	}

    return 1;

e_clean:
	DelSocketFromIOCP(m_socket, m_pPerHandleData);
	m_socket = INVALID_SOCKET;
	return -1;
}

int TPMulticastClient::Connect(const char* szLocalIp, int nLocalPort, const char* szRemoteIp, int nRemotePort)
{
	m_localIp = inet_addr(szLocalIp);
    m_localPort = htons(nLocalPort);

	return Connect(szRemoteIp, nRemotePort);
}

int TPMulticastClient::Close()
{
	ClearClientEnvironment();

// 	//	�뿪�ಥ��
// 	struct ip_mreq	mcast;
// 	mcast.imr_multiaddr.s_addr = m_remoteIp;	//	���IP�ಥ��ַ
// 	mcast.imr_interface.s_addr = m_localIp;		//	�ӿڵı���IP��ַ
// 
// 	setsockopt(m_socket, IPPROTO_IP, IP_DROP_MEMBERSHIP, (char*)&mcast, sizeof(struct ip_mreq));

	if (m_socket != INVALID_SOCKET)
	{
		DelSocketFromIOCP(m_socket, m_pPerHandleData);
		m_socket = INVALID_SOCKET;
	}

	if (m_sockMultipoint != INVALID_SOCKET)
	{
		closesocket(m_sockMultipoint);
		m_sockMultipoint = INVALID_SOCKET;
	}

	CReadWriteMutexLock lock(m_csSendQueue);
	while (!m_lstSendQueue.empty())
	{
		DataRow *conn = m_lstSendQueue.front();
		if (conn != NULL)
		{
			delete conn;
		}
		m_lstSendQueue.pop();
	}
	lock.Unlock();

	return 1;
}
