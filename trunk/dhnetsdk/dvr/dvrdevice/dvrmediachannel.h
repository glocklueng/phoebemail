/*
* Copyright (c) 2009, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �����ƣ�ʵʱ���ӽ�����
* ժ��Ҫ��ʵʱ���ӹ������ݽ�����
*
*/
//////////////////////////////////////////////////////////////////////////

#ifndef _DVRMEDIACHANNEL_H_
#define _DVRMEDIACHANNEL_H_

#include "dvrchannel.h"
class CDvrDevice;


class CDvrMediaChannel : public CDvrChannel
{
public:
	CDvrMediaChannel(CDvrDevice *pDvrDevice, int nMainCommand, void *pParam);
	virtual ~CDvrMediaChannel();

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

	/* ��ͨ�� */
	int				channel_open();


public:
    int				GetChannelIndex() { return m_media_channel_parm.no; }
	int				GetChannelSubtype() { return m_media_channel_parm.subtype; }
	unsigned int	GetChannelConnectID() { return m_media_channel_parm.conn.nConnectID; }
	int				GetConnectType() { return m_media_channel_parm.conn.nConnType; }
	char*			GetConnLocolIp() { return m_media_channel_parm.conn.szLocalIp; }
	int				GetConnLocolPort() { return m_media_channel_parm.conn.nLocalPort; }
	

private:
	afk_media_channel_param_s  m_media_channel_parm;
	void*			m_pSubSocket;
    BOOL            m_bWorking;
};


#endif // _DVRMEDIACHANNEL_H_

