/*
* Copyright (c) 2009, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �����ƣ����ù��ܽ�����
* ժ��Ҫ�����ù������ݽ�����
*
*/
//////////////////////////////////////////////////////////////////////////

#ifndef _DVRCONFIGCHANNEL_H_
#define _DVRCONFIGCHANNEL_H_

#include "dvrchannel.h"
class CDvrDevice;


class CDvrConfigChannel : public CDvrChannel
{
public:
	CDvrConfigChannel(CDvrDevice *pDvrDevice, int nMainCommand, void *pParam);
	virtual ~CDvrConfigChannel();
	
public:
	/* �ر�ͨ�� */
    virtual BOOL	channel_close();

    /* ��ͣͨ�� */
    virtual BOOL	channel_pause(BOOL pause);

    /* ��ȡ��Ϣ */
    virtual int		channel_get_info(int type, void *parm);

    /* ������Ϣ */
    virtual int		channel_set_info(int type, void *parm);

	/* �������� */
	virtual int		OnRespond(unsigned char *pBuf, int nLen);


public:
    unsigned int	GetConfigType() { return m_config_channel_parm.type; }


private:
    afk_config_channel_param_s m_config_channel_parm;
};


#endif // _DVRCONFIGCHANNEL_H_


