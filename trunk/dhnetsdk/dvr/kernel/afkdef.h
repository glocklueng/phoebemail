
#ifndef _AFKDEF_H_
#define _AFKDEF_H_

#include "../StdAfx.h"


/************************************************************************
 ** �豸��ӿڶ���
 ***********************************************************************/
struct afk_device_s
{
	virtual	~afk_device_s(){}
	char*	(*version)(afk_device_s *device);							// �汾��Ϣ
	char*	(*manufactory)(afk_device_s *device);						// ��������Ϣ
	char*	(*product)(afk_device_s *device);							// ��Ʒ��Ϣ
	char*	(*device_ip)(afk_device_s *device);							// ip��ַ
    int		(*device_port)(afk_device_s *device);						// �˿�
    int		(*device_type)(afk_device_s *device);						// ����
    int		(*close)(afk_device_s *device);								// �ر��豸
    int		(*channelcount)(afk_device_s *device);						// ͨ������
    int		(*alarminputcount)(afk_device_s *device);					// �����������
    int		(*alarmoutputcount)(afk_device_s *device);					// �����������

    void*	(*get_channel)(afk_device_s *device, int type, unsigned int parm);	// �õ�ͨ��
	void*	(*open_channel)(afk_device_s *device, int type, void *parm);		// ��ͨ��
	BOOL	(*channel_is_opened)(afk_device_s *device, int type, void *parm);	// �Ƿ�ͨ���Ѵ�

	int		(*get_info)(afk_device_s *device, int type, void *parm);	// ��ȡ��Ϣ
	int		(*set_info)(afk_device_s *device, int type, void *parm);	// ������Ϣ

	int		(*dev_addref)(afk_device_s *device);
	int		(*dev_decref)(afk_device_s *device);
};


/************************************************************************
 ** ����ͨ����ӿڶ���
 ***********************************************************************/
struct afk_channel_s
{
	virtual	~afk_channel_s(){}
    void*	(*get_device)(afk_channel_s *channel);						// �õ��豸
	BOOL	(*close)(afk_channel_s *channel);							// �ر�ͨ��
    BOOL	(*pause)(afk_channel_s *channel, BOOL pause);				// ��ͣͨ��
	int		(*get_info)(afk_channel_s *channel, int type, void *parm);	// ��ȡ��Ϣ
	int		(*set_info)(afk_channel_s *channel, int type, void *parm);	// ������Ϣ
};


#endif // _AFKDEF_H_

