// TcpSocket.cpp: implementation of the CTcpSocket class.
//
//////////////////////////////////////////////////////////////////////

#include "StdAfx.h"
#include "TcpSocket.h"
#include "DataCenter.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
#pragma   warning(disable:4355)
CTcpSocket::CTcpSocket() : TPTCPServer(this), TPTCPClient(this)
{
	m_pDataCenter = NULL;
	m_nSessionId = 0;
	m_bConnType = TRUE;

	m_nWritePos = 0;
	m_nReadPos = 0;
}

CTcpSocket::~CTcpSocket()
{
	
}

int CTcpSocket::InitNetwork()
{
	return TPTCPClient::Startup();
}

int CTcpSocket::ClearNetwork()
{
	return TPTCPClient::Cleanup();
}

/*
 *	ժҪ���������ݻص�
 */
int CTcpSocket::onData(int engineId, int connId, const char* data, int len)
{
	CReadWriteMutexLock lock(m_csBuffer);

    if (len > 0)
    {
        /***********************��������***********************/
        //	���ڵ��������ڴ洢�ռ�ʱ��ȡ������ԭ��
        //	��������У������ж�̫�ú��յ��������ݰ�

        int nEndPos = len + m_nWritePos;
        
		//	����������㹻��������
        if (nEndPos <= MAX_BUF_SIZE)
        {
            memcpy(m_packetBuf + m_nWritePos, data, len);
            m_nWritePos = m_nWritePos + len;
        }
		//	��������������Ի�������,��ͷ����
        else
        {   
			//	���������������������ɸ����ݣ�һ������Ϊ�����ж�̫�û�������ݰ�
            if (len + (m_nWritePos-m_nReadPos) >= MAX_BUF_SIZE)
            {
				len = 0;
            }
			else
            {
				memmove(m_packetBuf, m_packetBuf + m_nReadPos, m_nWritePos - m_nReadPos);
        
				m_nWritePos = m_nWritePos - m_nReadPos;
				m_nReadPos = 0;				

				if (len > 0)
				{
					memcpy(m_packetBuf + m_nWritePos, data, len);
					m_nWritePos = m_nWritePos + len;
				}
			}
		}
    }

	return 1;
}

/*
 *	ժҪ����������
 *	����ֵ��0��æ��1������
 */
int	CTcpSocket::onDealData(int engineId, int connId)
{
	int nRet = 1;

	int len = GetData();
	if (len > 0)
	{
		if (0xA0 == m_dealBuf[0])
		{
			//	�����
			if (m_nSessionId == 0)
			{
				m_nSessionId = TPTCPClient::m_socket;
				m_bConnType = TRUE;

				//	����Ȩ�������б�ת���û������б���
				m_pDataCenter->AddUserConn(m_nSessionId, this);
			}
			
			BYTE *pCommand = new BYTE[32];
			memset(pCommand, 0, 32);
			pCommand[0] = 0xB0;
			pCommand[3] = 0x50;
			pCommand[10] = m_pDataCenter->m_nDevChannel;
			pCommand[11] = 0x09;
			pCommand[12] = 0x02;
			*(DWORD*)(pCommand+16) = m_nSessionId;
			
			IBufferRef pCommandData = CAutoBuffer::CreateBuffer(32, (char*)pCommand, false);
			WriteData(pCommandData);
		}
		else if (0x11 == m_dealBuf[0])
		{
			//	���Ӱ�
			if (m_nSessionId != 0)
			{
				m_pDataCenter->UserConnPlay(m_nSessionId, m_dealBuf, len);
			}
		}
		else if (0xF1 == m_dealBuf[0])
		{
			//	������
			m_nSessionId = *(DWORD*)(m_dealBuf+8);
			m_bConnType = FALSE;
			int nChannel = m_dealBuf[13] - 1;
			
			m_pDataCenter->UserConnSubConn(m_nSessionId, this, TPTCPClient::m_socket, nChannel);
		}
		else if (0xA1 == m_dealBuf[0])
		{
			//	������
			BYTE *pCommand = new BYTE[32];
			memset(pCommand, 0, 32);
			pCommand[0] = 0xB1;
			
			IBufferRef pCommandData = CAutoBuffer::CreateBuffer(32, (char*)pCommand, false);
			WriteData(pCommandData);
		}
		
		nRet = 0;
	}

	return nRet;
}

/*
 *	ժҪ������������ɻص����ӷ��Ͷ�����ȡ���ݼ�������
 */
int CTcpSocket::onSendDataAck(int engineId, int connId, int id)
{
	return 1;
}

/*
 *	ժҪ�����������òŻص������µ�client���ӣ�����ֵΪ0��ʾ���ܴ����ӣ�����ֵΪ1��ʾ�ܾ�����
 */
int CTcpSocket::onConnect(int engineId, int connId, const char* ip, int port)
{
	return 1;
}

/*
 *	ժҪ�����������òŻص���client�˳��ص���ɾ���ͻ��������б�
 */
int CTcpSocket::onClose(int engineId, int connId)
{
	return 1;
}

/*
 *	ժҪ�����ͻ����òŻص������߻ص����ڲ�������������Ӧ�ò�����Ƿ�close
 */
int CTcpSocket::onDisconnect(int engineId, int connId)
{
	if (m_nSessionId != 0 && m_bConnType)
	{
		m_pDataCenter->DelUserConn(m_nSessionId, this);
	}
	else
	{
		m_pDataCenter->DelConn(TPTCPClient::m_socket, this);
	}
	
	return 1;
}

/*
 *	ժҪ�����ͻ����òŻص������ߺ������ɹ��ص����ָ����е�ҵ��(����)
 */
int CTcpSocket::onReconnect(int engineId, int connId)
{
	return 1;
}

//////////////////////////////////////////////////////////////////////////

int	CTcpSocket::WriteData(IBufferRef pSendBuf)
{
	return TPTCPClient::Send(0, pSendBuf);
}

void CTcpSocket::Disconnect()
{
	TPTCPClient::Close();
}

int	CTcpSocket::Heartbeat()
{
	return TPTCPClient::Heartbeat();
}

int	CTcpSocket::GetData()
{
	int nDataLen = 0;

	CReadWriteMutexLock lock(m_csBuffer);

	if ((int)(m_nWritePos - m_nReadPos) >= HEADER_SIZE)
	{
		unsigned int extlen = *(unsigned int*)(m_packetBuf + m_nReadPos + 4);

		if (extlen >= MAX_PACKET_SIZE)
		{
			//	ָʾ����չ����̫��������������ջ���
			m_nWritePos = m_nReadPos = 0;

			return 0;
		}

		if (m_nWritePos - m_nReadPos >= extlen + HEADER_SIZE)
        {
			nDataLen = extlen + HEADER_SIZE;
			memcpy(m_dealBuf, m_packetBuf + m_nReadPos, nDataLen);

			m_nReadPos += nDataLen;
        }
	}

	return nDataLen;
}

//////////////////////////////////////////////////////////////////////////

int	CTcpSocket::StartServer(const char *szIp, int nPort, CDataCenter *pDataCenter)
{
	m_pDataCenter = pDataCenter;
	return TPTCPServer::Listen((char*)szIp, nPort);
}

int	CTcpSocket::StopServer()
{
	return TPTCPServer::Close();
}

int	CTcpSocket::DealNewSocket(SOCKET newsock, int connId, const char* ip, int port)
{
	CTcpSocket *pNewSocket = new CTcpSocket();
	if (pNewSocket == NULL || m_pDataCenter == NULL)
	{
		closesocket(newsock);
		return -1;
	}

	//	��ɿͻ��˵�������
	int ret = pNewSocket->SetSocket(newsock, connId, ip, port, m_pDataCenter);
	if (ret >= 0)
	{
		CReadWriteMutexLock lock(m_pDataCenter->m_csConn);
		m_pDataCenter->m_lstConns[newsock] = pNewSocket;
	}

	return 1;
}

int	CTcpSocket::SetSocket(SOCKET newsock, int connId, const char* ip, int port, CDataCenter *pDataCenter)
{
	int nRet = -1;
	CPerHandleData *pPerHandleData = NULL;

	TPTCPClient::m_bReconnEn = FALSE;
	TPTCPClient::m_socket = newsock;
	TPTCPClient::m_remoteIp = inet_addr(ip);
	TPTCPClient::m_remotePort = htons(port);
	TPTCPClient::m_bOnline = TRUE;
	m_pDataCenter = pDataCenter;

	int ret = TPTCPClient::CreateClientEnvironment();
	if (ret >= 0)
	{
		//	��socket��ӵ���ɶ˿���
		ret = TPTCPClient::AddSocketToIOCP(TPTCPClient::m_socket, TPTCPClient::m_pPerHandleData);
		if (ret >= 0)
		{
			pPerHandleData = TPTCPClient::m_pPerHandleData;

			TPTCPClient::m_pPerHandleData->AddRef();
			TPTCPClient::m_pPerIoRecv->AddRef();
			ret = TPTCPClient::PostRecvToIOCP(TPTCPClient::m_socket, TPTCPClient::m_pPerIoRecv);
			if (ret < 0)
			{
				TPTCPClient::m_pPerIoRecv->DecRef();
				TPTCPClient::m_pPerHandleData->DecRef();
				TPTCPClient::ClearClientEnvironment();
			}
			else
			{
				nRet = 1;
			}
		}
		else
		{
			TPTCPClient::ClearClientEnvironment();
		}
	}
	
	if (nRet < 0)
	{
		TPTCPClient::DelSocketFromIOCP(newsock, pPerHandleData);
	}

	return nRet;
}