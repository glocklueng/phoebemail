// TcpServer.cpp: implementation of the CTcpServer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TcpServer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTcpServer::CTcpServer() : TPTCPServer(this)
{

}

CTcpServer::~CTcpServer()
{

}

int CTcpServer::onDisconnect(int engineId, int connId)
{
	return 0;
}

int CTcpServer::onReconnect(int engineId, int connId)
{
	return 0;
}

/*
 *	ժҪ���������ݻص�
 */
int CTcpServer::onData(int engineId, int connId, const char* data, int len)
{
	return 0;
}

/*
 *	ժҪ������������ɻص����ӷ��Ͷ�����ȡ���ݼ�������
 */
int CTcpServer::onSendDataAck(int engineId, int connId, int id)
{
	return 0;
}

/*
 *	ժҪ�����������òŻص������µ�client���ӣ�����ֵΪ0��ʾ���ܴ����ӣ�����ֵΪ1��ʾ�ܾ�����
 */
int CTcpServer::onConnect(int engineId, int connId, const char* ip, int port)
{
	return 0;
}

/*
 *	ժҪ�����������òŻص���client�˳��ص���ɾ���ͻ��������б�
 */
int CTcpServer::onClose(int engineId, int connId)
{
	return 0;
}