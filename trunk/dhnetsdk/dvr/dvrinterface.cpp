
#include "dvrinterface.h"
#include "dvrdevice/dvrdevice.h"
#include "dvrdevice/dvrchannel.h"


/* �汾��Ϣ */
char* interface_version(afk_device_s *device)
{
    CDvrDevice *pDvrDevice = (CDvrDevice*)device;
    return pDvrDevice->device_version();
}

/* ��������Ϣ */							
char* interface_manufactory(afk_device_s *device)
{
    CDvrDevice *pDvrDevice = (CDvrDevice*)device;
    return pDvrDevice->device_manufactory();
}

/* ��Ʒ��Ϣ */
char* interface_product(afk_device_s *device)
{
    CDvrDevice *pDvrDevice = (CDvrDevice*)device;
    return pDvrDevice->device_product();
}

/* IP��ַ */
char* interface_ip(afk_device_s *device)
{
    CDvrDevice *pDvrDevice = (CDvrDevice*)device;
    return pDvrDevice->GetIp();
}

/* �˿� */
int interface_port(afk_device_s *device)
{
    CDvrDevice *pDvrDevice = (CDvrDevice*)device;
    return pDvrDevice->GetPort();
}

/* ���� */
int interface_type(afk_device_s *device)
{
    CDvrDevice *pDvrDevice = (CDvrDevice*)device;
    return pDvrDevice->GetType();
}

/* ͨ������ */
int interface_channelcount(afk_device_s *device)
{
    CDvrDevice *pDvrDevice = (CDvrDevice*)device;
    return pDvrDevice->GetVideoChannelCount();
}

/* ����������� */                        
int interface_alarminputcount(afk_device_s *device)
{
    CDvrDevice *pDvrDevice = (CDvrDevice*)device;
    return pDvrDevice->GetAlarminputCount();
}

/* ����������� */                     
int interface_alarmoutputcount(afk_device_s *device)
{
    CDvrDevice *pDvrDevice = (CDvrDevice*)device;
    return pDvrDevice->GetAlarmoutputCount();
}

/* �ر��豸 */
int interface_close(afk_device_s *device)
{
	int nRet = -1;
    CDvrDevice *pDvrDevice = (CDvrDevice*)device;
	if (pDvrDevice)
	{
		nRet = pDvrDevice->device_close();
	}

    return nRet;
}

/* �õ�ͨ�� */
void* interface_get_channel(afk_device_s *device, int type, unsigned int parm)
{
    CDvrDevice *pDvrDevice = (CDvrDevice*)device;
    return (afk_channel_s*)pDvrDevice->device_get_channel(type, parm);
}         

/* ��ͨ�� */
void* interface_open_channel(afk_device_s *device, int type, void *parm)
{
    CDvrDevice *pDvrDevice = (CDvrDevice*)device;
    return pDvrDevice->device_open_channel(type, parm);
}

/* �Ƿ�ͨ���� */
BOOL interface_channel_is_opened(afk_device_s *device, int type, void *parm)
{
    CDvrDevice *pDvrDevice = (CDvrDevice*)device;
    return pDvrDevice->device_channel_is_opened(type, parm);
}
	
/* ��ȡ��Ϣ */
int interface_get_info(afk_device_s *device, int type, void *parm)
{
    CDvrDevice *pDvrDevice = (CDvrDevice*)device;
    return pDvrDevice->device_get_info(type, parm);
}

/* ������Ϣ */
int interface_set_info(afk_device_s *device, int type, void *parm)
{
    CDvrDevice *pDvrDevice = (CDvrDevice*)device;
    return pDvrDevice->device_set_info(type, parm);
}

/* �豸��Դ�������� */
int interface_dev_addref(afk_device_s *device)
{
	CDvrDevice *pDvrDevice = (CDvrDevice *)device;
	return pDvrDevice->device_AddRef();
}

int interface_dev_decref(afk_device_s *device)
{
	CDvrDevice *pDvrDevice = (CDvrDevice *)device;
	return pDvrDevice->device_DecRef();
}

/* �õ��豸 */
void* interface_get_device(afk_channel_s *channel)
{
    CDvrChannel *pDvrChannel = (CDvrChannel*)channel;
    return (afk_device_s*)pDvrChannel->channel_getdevice();
}

/* �ر�ͨ�� */
BOOL interface_close_ch(afk_channel_s *channel)
{
	BOOL ret = FALSE;
    CDvrChannel *pDvrChannel = (CDvrChannel*)channel;
	if (pDvrChannel)
	{
		ret = pDvrChannel->channel_close();
		if (!ret)
		{
			//...this can not happen for now
		}
		pDvrChannel->channel_decRef();
	}

	return ret;
}

/* ��ͣͨ�� */
BOOL interface_pause_ch(afk_channel_s *channel, BOOL pause)
{
    CDvrChannel *pDvrChannel = (CDvrChannel*)channel;
    return pDvrChannel->channel_pause(pause);
}

/* ��ȡ��Ϣ */
int interface_get_info_ch(afk_channel_s *channel, int type, void *parm)
{
    CDvrChannel *pDvrChannel = (CDvrChannel*)channel;
    return pDvrChannel->channel_get_info(type, parm);
}

/* ������Ϣ */
int interface_set_info_ch(afk_channel_s *channel, int type, void *parm)
{
    CDvrChannel *pDvrChannel = (CDvrChannel*)channel;
    return pDvrChannel->channel_set_info(type, parm);
}

