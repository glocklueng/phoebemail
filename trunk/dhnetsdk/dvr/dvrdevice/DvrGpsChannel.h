/*
* Copyright (c) 2009, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �����ƣ�GPS���ܽ�����
* ժ��Ҫ��GPS�������ݽ�����
*
*/
//////////////////////////////////////////////////////////////////////////

#ifndef _DVRGPSCHANNEL_H_
#define _DVRGPSCHANNEL_H_

#include "dvrchannel.h"
class CDvrDevice;


class CDvrGpsChannel : public CDvrChannel
{
public:
	CDvrGpsChannel(CDvrDevice *pDvrDevice, int nMainCommand, void *pParam);
	virtual ~CDvrGpsChannel();
	
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
    afk_gps_channel_param_s m_gps_channel_parm;
};

#endif // _DVRGPSCHANNEL_H_

