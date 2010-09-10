/*
* Copyright (c) 2009, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �����ƣ��û������ܽ�����
* ժ��Ҫ���û����������ݽ�����
*
*/
//////////////////////////////////////////////////////////////////////////

#ifndef _DVRUSERCHANNEL_H_
#define _DVRUSERCHANNEL_H_

#include "dvrchannel.h"
class CDvrDevice;


class CDvrUserChannel : public CDvrChannel
{
public:
	CDvrUserChannel(CDvrDevice *pDvrDevice, int nMainCommand, void *pParam);
	virtual ~CDvrUserChannel();

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
    unsigned int	GetUserType() { return m_user_channel_parm.type; }


private:
    afk_user_channel_param_s m_user_channel_parm;
};


#endif // _DVRUSERCHANNEL_H_

