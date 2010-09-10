/*
* Copyright (c) 2009, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �����ƣ����ع��ܽ�����
* ժ��Ҫ�����ع������ݽ�����
*
*/
//////////////////////////////////////////////////////////////////////////

#ifndef _DVRDOWNLOADCHANNEL_H_
#define _DVRDOWNLOADCHANNEL_H_

#include "dvrchannel.h"
class CDvrDevice;


class CDvrDownLoadChannel : public CDvrChannel
{
public:
	CDvrDownLoadChannel(CDvrDevice *pDvrDevice, int nMainCommand, void *pParam);
	virtual ~CDvrDownLoadChannel();

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
    int				GetChannelIndex() { return m_download_channel_parm.info.ch; }
	unsigned int	GetMainType() { return m_download_channel_parm.type; }
	unsigned int	GetSubType() { return m_download_channel_parm.subtype; }
	unsigned int	GetChannelConnectID() { return m_download_channel_parm.conn.nConnectID; }


private:
	afk_download_channel_param_s m_download_channel_parm;
	BOOL			m_bDownloading;
    unsigned char	m_nFrameRate;
	void*			m_pSubSocket;
};


#endif // _DVRDOWNLOADCHANNEL_H_

