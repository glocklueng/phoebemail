/*
* Copyright (c) 2009, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �����ƣ�͸�����ڹ��ܽ�����
* ժ��Ҫ��͸�����ڹ������ݽ�����
*
*/
//////////////////////////////////////////////////////////////////////////

#ifndef _DVRTRANSCHANNEL_H_
#define _DVRTRANSCHANNEL_H_

#include "dvrchannel.h"
class CDvrDevice;


class CDvrTransChannel : public CDvrChannel
{
public:
	CDvrTransChannel(CDvrDevice *pDvrDevice, int nMainCommand, void *pParam);
	virtual ~CDvrTransChannel();
	
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
    int				GetChannelIndex() { return (int)m_trans_channel_parm.trans_device_type; }


private:
    afk_trans_channel_param_s m_trans_channel_parm;
};


#endif // _DVRTRANSCHANNEL_H_

