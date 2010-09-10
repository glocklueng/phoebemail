/*
* Copyright (c) 2009, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �����ƣ�TCP�ͻ�����
* ժ��Ҫ��TCP��ʽ���䡣
*
*/
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_TCPSOCKET_H__8E1B116D_3800_4C99_A666_8413ABE8E9F7__INCLUDED_)
#define AFX_TCPSOCKET_H__8E1B116D_3800_4C99_A666_8413ABE8E9F7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifdef WIN32
#pragma comment( lib, "Ws2_32.lib")
#ifdef NETSDK_VERSION_SSL
#pragma comment( lib, "libeay32.lib")
#pragma comment( lib, "ssleay32.lib")
#endif
#endif

#if (defined(WIN32) && !(defined(NETSDK_VERSION_SSL)))
#include "../../TPLayer_IOCP/TPTCPClient.h"
#include "../../TPLayer_IOCP/TPTCPServer.h"
#else
#include "../../TPLayer_Select/TPTCPClient.h"
#include "../../TPLayer_Select/TPTCPServer.h"
using namespace NET_TOOL;
#endif

#ifndef HEADER_SIZE
#define HEADER_SIZE  32
#endif


//	���߻ص�����
typedef int (__stdcall *OnDisConnectFunc)(void *userdata);

//	���������ӻص�����
typedef int	(__stdcall *OnReConnectFunc)(void *userdata);

//	��ָ����Ϣ�ص�������
typedef int (__stdcall *OnNormalPacketFunc)(unsigned char *pbuf, int nlen, void *userdata);

//	���ջص�����(��������ͳ��)
typedef int (__stdcall *OnRecPacketFunc)(unsigned char *pbuf, int nlen, void *userdata);

//	�����ص�����
typedef void (__stdcall *OnListenSockFunc)(void* caller, char *ip, int port, int type, void *value, void *userdata);


//////////////////////////////////////////////////////////////////////////

class CTcpSocket : virtual public TPTCPServer, virtual public TPTCPClient, public ITPListener
{
public:
	CTcpSocket();
	virtual ~CTcpSocket();
	int		CreateRecvBuf(unsigned int nRecvSize); // �������ջ���

	
public:
	static int InitNetwork();
	static int ClearNetwork();


public:	// client
    void	SetCallBack(OnDisConnectFunc cbDisConnect, OnReConnectFunc cbReconnect, OnNormalPacketFunc cbNormalPacket, OnRecPacketFunc cbReceivePacket, void* userdata);

	void	SetKeepLife(unsigned char *szLifePacket, int nBufLen, unsigned int nKeepLifeTime=10);

	int		ConnectHost(const char *szIp, int nPort, int nTimeOut = 1500);

	void	Disconnect();

	int		WriteData(char *pBuf, int nLen);

	int		Heartbeat();


public:	// server
	int		StartListen(const char *szIp, int nPort, OnListenSockFunc cbListenSock, void *userdata);
	
	int		StopListen();

	virtual int	DealNewSocket(SOCKET newsock, int connId, char* ip, int port);

	int		SetSocket(SOCKET newsock, int connId, const char* ip, int port, OnListenSockFunc cbListen, void* listenuserdata, void* pListenSocket);

	int		ResponseReg(bool bAccept);

	
public:	// event
	virtual int onData(int nEngineId, int nConnId, unsigned char* data, int nLen);

	virtual int	onDealData(int nEngineId, int nConnId, unsigned char* buffer, int nLen);

	virtual int onSendDataAck(int nEngineId, int nConnId, int nId);

	virtual int onConnect(int nEngineId, int nConnId, char* szIp, int nPort);

	virtual int onClose(int nEngineId, int nConnId);

	virtual int onDisconnect(int nEngineId, int nConnId);

	virtual int onReconnect(int nEngineId, int nConnId);


public:

	int		SetIsReConn(int nEnable);

	int		SetIsDetectDisconn(int nEnable);

	int		GetIsOnline();

	void	DealSpecialPacket(unsigned char *pbuf, int nlen);

	int		CloseSubConn();	// �ر�������

	int		ConnectSubConn(); // ����������

#ifdef NETSDK_VERSION_SSL
	int		SetSSL(int nEnable);
#endif


private:
	int		GetData(unsigned char* buf, int len);

#ifdef NETSDK_VERSION_BOGUSSSL
	int		DealSSL();
#endif


public:
	OS_EVENT			m_hRecEvent;		// ͬ���������ݵ��¼�
	unsigned char		m_registerAck[64];
	int					m_nRegisterLen;
		
#ifdef NETSDK_VERSION_BOGUSSSL
	OS_EVENT			m_hSpecialEvent;
	int					m_nSSL;	
#endif


private:
	OnDisConnectFunc	m_pDisConnect;
    OnReConnectFunc		m_pReconnect;
    OnNormalPacketFunc	m_pNormalPacket;
	OnRecPacketFunc		m_pRecvPakcet;
    void*				m_pUserData;

	OnListenSockFunc	m_pListenSockFunc;
	void*				m_pListenUserData;
	void*				m_pListenSocket;

	// ���׻������
    unsigned int		m_nWritePos;
    unsigned int		m_nReadPos;
	unsigned char		*m_pPacketBuf;
	unsigned int		m_nBufSize;
	CReadWriteMutex		m_csBuffer;
	CReadWriteMutex		m_csOutCallBack;
};

#endif // !defined(AFX_TCPSOCKET_H__8E1B116D_3800_4C99_A666_8413ABE8E9F7__INCLUDED_)
