/*
* Copyright (c) 2009, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �����ƣ����ƹ��ܽ�����
* ժ��Ҫ�����ƹ������ݽ�����
*
*/
//////////////////////////////////////////////////////////////////////////

#ifndef _DVRCONTROLCHANNEL_H_
#define _DVRCONTROLCHANNEL_H_

#include "dvrchannel.h"
class CDvrDevice;


class CDvrControlChannel : public CDvrChannel
{
public:
	CDvrControlChannel(CDvrDevice *pDvrDevice, int nMainCommand, void *pParam);
	virtual ~CDvrControlChannel();
	
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
    unsigned int	GetControlType1() { return m_control_channel_parm.type1; }


private:
    afk_control_channel_param_s m_control_channel_parm;
};


#endif // _DVRCONTROLCHANNEL_H_

