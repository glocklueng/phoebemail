/*
* Copyright (c) 2009, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �����ƣ�����ӿ�ʵ����
* ժ��Ҫ��ʵ�ֽӿڡ�
*
*/
//////////////////////////////////////////////////////////////////////////

#ifndef _DVRINTERFACE_H_
#define _DVRINTERFACE_H_

#include "StdAfx.h"

/*****************************�豸�ӿ�*******************************/
/* �汾��Ϣ */
char*	interface_version(afk_device_s *devive);

/* ��������Ϣ */							
char*	interface_manufactory(afk_device_s *devive);

/* ��Ʒ��Ϣ */
char*	interface_product(afk_device_s *devive);

/* IP��ַ */
char*	interface_ip(afk_device_s *devive);

/* �˿� */
int		interface_port(afk_device_s *devive);

/* ���� */
int		interface_type(afk_device_s *devive);

/* ͨ������ */
int		interface_channelcount(afk_device_s *devive);

/* ����������� */                        
int		interface_alarminputcount(afk_device_s *devive);

/* ����������� */                     
int		interface_alarmoutputcount(afk_device_s *devive);

/* �ر��豸 */
int		interface_close(afk_device_s *devive);

/* �õ�ͨ�� */
void*	interface_get_channel(afk_device_s *devive, int type, unsigned int parm);
					
/* ��ͨ�� */
void*	interface_open_channel(afk_device_s *devive, int type, void *parm);

/* �Ƿ�ͨ���� */
BOOL	interface_channel_is_opened(afk_device_s *devive, int type, void *parm);

/* ��ȡ��Ϣ */
int		interface_get_info(afk_device_s *devive, int type, void *parm);

/* ������Ϣ */
int		interface_set_info(afk_device_s *devive, int type, void *parm);

/* �豸��Դ�������� */
int		interface_dev_addref(afk_device_s *devive);
int		interface_dev_decref(afk_device_s *devive);


/*****************************ͨ���ӿ�*******************************/
/* �õ��豸 */
void*	interface_get_device(afk_channel_s *channel);

/* �ر�ͨ�� */
BOOL	interface_close_ch(afk_channel_s *channel);

/* ��ͣͨ�� */
BOOL	interface_pause_ch(afk_channel_s *channel, BOOL pause);
						
/* ��ȡ��Ϣ */
int		interface_get_info_ch(afk_channel_s *channel, int type, void *parm);

/* ������Ϣ */
int		interface_set_info_ch(afk_channel_s *channel, int type, void *parm);


/*****************************��������*******************************/
#ifdef NETSDK_VERSION_SSL
template <class T> T* device_create_connect(afk_connect_param_t* pConnParam, BOOL bSSL=FALSE) 
#else
template <class T> T* device_create_connect(afk_connect_param_t* pConnParam) 
#endif
{
	T* pSubSocket = new T();
	if (NULL == pSubSocket)
	{
		return NULL;
	}
	
	if (pSubSocket->CreateRecvBuf(pConnParam->nConnBufSize) < 0)
	{
		delete pSubSocket;
		return NULL;
	}

#ifdef NETSDK_VERSION_SSL
	// SSL
	if (bSSL)
	{
		pSubSocket->SetSSL(1);
	}
#endif
	
	BOOL bIsConnect = FALSE;
	int nTryTime = pConnParam->nTryTime;
	while (nTryTime > 0)
	{
		if (pSubSocket->ConnectHost(pConnParam->szSevIp, pConnParam->nSevPort, pConnParam->nConnTime) >= 0)
		{
			bIsConnect = TRUE;
			break;
		}
		
		nTryTime--;
	}
	
	if (!bIsConnect)
	{
		delete pSubSocket;
		return NULL;
	}
	
	return pSubSocket;
}

		
#endif // _DVRINTERFACE_H_

