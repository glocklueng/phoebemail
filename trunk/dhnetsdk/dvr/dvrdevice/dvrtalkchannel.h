/*
* Copyright (c) 2009, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �����ƣ������Խ����ܽ�����
* ժ��Ҫ�������Խ��������ݽ�����
*
*/
//////////////////////////////////////////////////////////////////////////

#ifndef _DVRTALKCHANNEL_H_
#define _DVRTALKCHANNEL_H_

#include "dvrchannel.h"
class CDvrDevice;


class CDvrTalkChannel : public CDvrChannel
{
public:
	CDvrTalkChannel(CDvrDevice *pDvrDevice, int nMainCommand, void *pParam);
	virtual ~CDvrTalkChannel();
	
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
    afk_talk_channel_param_s m_talk_channel_parm;
    BOOL            m_bWorking;
};


#endif // _DVRTALKCHANNEL_H_

