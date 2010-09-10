/*
* Copyright (c) 2009, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �����ƣ�����ͳһ��
* ժ��Ҫ������ͳ�ơ�
*
*/
//////////////////////////////////////////////////////////////////////////

#ifndef _DVRSTATISCCHANNEL_H_
#define _DVRSTATISCCHANNEL_H_

#include "dvrchannel.h"
class CDvrDevice;


class CDvrStatiscChannel : public CDvrChannel
{
public:
	CDvrStatiscChannel(CDvrDevice *pDvrDevice, int nMainCommand, void *pParam);
	virtual ~CDvrStatiscChannel();
	
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
};


#endif // _DVRSTATISCCHANNEL_H_

