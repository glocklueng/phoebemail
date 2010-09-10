/*
* Copyright (c) 2009, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �����ƣ��������ܽ�����
* ժ��Ҫ�������������ݽ�����
*
*/
//////////////////////////////////////////////////////////////////////////

#ifndef _DVRALARMCHANNEL_H_
#define _DVRALARMCHANNEL_H_

#include "dvrchannel.h"
class CDvrDevice;


class CDvrAlarmChannel : public CDvrChannel
{
public:
	CDvrAlarmChannel(CDvrDevice *pDvrDevice, int nMainCommand, void *pParam);
	virtual ~CDvrAlarmChannel();

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


private:
	afk_alarm_channel_param_s  m_alarm_channel_parm;
	afk_state_info_s* m_pstateinfo;
};


#endif // _DVRALARMCHANNEL_H_


