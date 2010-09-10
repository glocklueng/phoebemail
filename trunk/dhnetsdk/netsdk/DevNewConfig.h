/*
* Copyright (c) 2009, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �����ƣ���������
* ժ��Ҫ�������ù���ģ��(JsonЭ���ʽ)
*
*/
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DEVNEWCONFIG_H__02ACB021_5772_48ED_B4A2_3358EAE097C4__INCLUDED_)
#define AFX_DEVNEWCONFIG_H__02ACB021_5772_48ED_B4A2_3358EAE097C4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "netsdk.h"

class CManager;

class CDevNewConfig  
{
public:
	CDevNewConfig(CManager *pManager);
	virtual ~CDevNewConfig();
	
public:
	/* ��ʼ�� */
	int					Init(void);

	/* ���� */
	int					Uninit(void);

	/* �ر�һ���豸������ͨ�� */
	int					CloseChannelOfDevice(afk_device_s* device);

	/* ͬ��������Ϣ */
	int					SysConfigInfo(LONG lLoginID, int nType, void* pCondition, char *pOutBuffer, int maxlen, int *pRetlen, int *error, int *restart, int waittime=1000);


	/* �µĻ�ȡ�豸���ã��ַ���Э�飩*/
	int					GetDevConfig(LONG lLoginID, char* szCommand, int nChannelID, char* szOutBuffer, DWORD dwOutBufferSize, int *error, int waittime/*=500*/);
	
	/* �µ������豸���ã��ַ���Э�飩*/
	int					SetDevConfig(LONG lLoginID, char* szCommand, int nChannelID, char* szInBuffer, DWORD dwInBufferSize, int *error, int *restart, int waittime/*=500*/); 

private:
	CManager*			m_pManager;
};

#endif // !defined(AFX_DEVNEWCONFIG_H__02ACB021_5772_48ED_B4A2_3358EAE097C4__INCLUDED_)
