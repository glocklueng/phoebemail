// AutoRegister.h: interface for the CAutoRegister class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_AUTOREGISTER_H__55EF1893_48EB_442C_A58F_7F4BCCAD48D6__INCLUDED_)
#define AFX_AUTOREGISTER_H__55EF1893_48EB_442C_A58F_7F4BCCAD48D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "netsdk.h"

class CManager;


class CAutoRegister  
{
public:
	CAutoRegister(CManager *pManager);
	virtual ~CAutoRegister();
	
public:
	/* ��ʼ�� */
	int							Init(void);

	/* ���� */
	int							Uninit(void);

	/* �ر�һ���豸������ͨ�� */
	int							CloseChannelOfDevice(afk_device_s* device);

	/* ����ע���ض�����*/
	// ʹ�豸�����������ӷ�����
	LONG ConnectRegServer(LONG lLoginID, char* RegServerIP, WORD RegServerPort, int TimeOut);
	// ʹ�豸����ע��ӷ�����
	int ControlRegister(LONG lLoginID, LONG ConnectionID, int waittime);
	// ʹ�豸�Ͽ�����ע��������
	int DisConnectRegServer(LONG lLoginID, LONG ConnectionID);
	// ��ѯ�豸����ע�����������Ϣ
	int QueryRegServerInfo(LONG lLoginID, LPDEV_SERVER_AUTOREGISTER lpRegServerInfo, int waittime);

private:
	CManager*		m_pManager;

};


#endif // !defined(AFX_AUTOREGISTER_H__55EF1893_48EB_442C_A58F_7F4BCCAD48D6__INCLUDED_)
