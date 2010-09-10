/*
* Copyright (c) 2009, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �����ƣ��໭��Ԥ�����ܽ�����
* ժ��Ҫ���໭��Ԥ���������ݽ�����
*
*/
//////////////////////////////////////////////////////////////////////////

#ifndef _DVRPREVIEWCHANNEL_H_
#define _DVRPREVIEWCHANNEL_H_

#include "dvrchannel.h"
class CDvrDevice;


class CDvrPreviewChannel : public CDvrChannel
{
public:
	CDvrPreviewChannel(CDvrDevice *pDvrDevice, int nMainCommand, void *pParam);
	virtual ~CDvrPreviewChannel();

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
    void			GetPreviewType(int *type1, int *type2);
	unsigned int	GetChannelConnectID() { return m_preview_channel_parm.conn.nConnectID; }


private:
	afk_preview_channel_param_s m_preview_channel_parm;
	void*			m_pSubSocket;
    BOOL			m_bWorking;
};


#endif // _DVRPREVIEWCHANNEL_H_


