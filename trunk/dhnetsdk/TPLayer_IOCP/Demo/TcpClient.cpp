// TcpClient.cpp: implementation of the CTcpClient class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TCPClient.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTcpClient::CTcpClient() : TPTCPClient(this)
{

}

CTcpClient::~CTcpClient()
{

}

int CTcpClient::onConnect(int engineId, int connId, const char* ip, int port)
{
	return 0;
}

int CTcpClient::onClose(int engineId, int connId)
{
	return 0;
}

/*
 *	ժҪ���������ݻص�
 */
int CTcpClient::onData(int engineId, int connId, const char* data, int len)
{
	return 0;
}

/*
 *	ժҪ������������ɻص����ӷ��Ͷ�����ȡ���ݼ�������
 */
int CTcpClient::onSendDataAck(int engineId, int connId, int id)
{
	return 0;
}

/*
 *	ժҪ�����ͻ����òŻص������߻ص����ڲ�������������Ӧ�ò�����Ƿ�close
 */
int CTcpClient::onDisconnect(int engineId, int connId)
{
	return 0;
}

/*
 *	ժҪ�����ͻ����òŻص������ߺ������ɹ��ص����ָ����е�ҵ��(����)
 */
int CTcpClient::onReconnect(int engineId, int connId)
{
	return 0;
}
