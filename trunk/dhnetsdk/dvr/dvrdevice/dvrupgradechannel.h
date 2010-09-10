/*
* Copyright (c) 2009, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �����ƣ��������ܽ�����
* ժ��Ҫ�������������ݽ�����
*
*/
//////////////////////////////////////////////////////////////////////////

#ifndef _DVRUPGRADECHANNEL_H_
#define _DVRUPGRADECHANNEL_H_

#include "dvrchannel.h"
class CDvrDevice;


class CDvrUpgradeChannel : public CDvrChannel
{
public:
	CDvrUpgradeChannel(CDvrDevice *pDvrDevice, int nMainCommand, void *pParam);
	virtual ~CDvrUpgradeChannel();

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
    afk_upgrade_channel_param_s	GetUpgradeChannelParam() { return m_upgrade_channel_param; }
	BOOL			GetUpgradeState() { return m_bSendDone; }
	void			SetUpgradeState(BOOL bSendDone) { m_bSendDone = bSendDone; }
	unsigned int	GetMainType() { return m_upgrade_channel_param.type; }


public:
    unsigned int	m_packetindex;
	OS_THREAD		m_hThread;
	OS_EVENT		m_hExitThread;
	DWORD			m_dwThreadID;

protected:
    afk_upgrade_channel_param_s  m_upgrade_channel_param;
    BOOL			m_bSendDone;
};


#endif // _DVRUPGRADECHANNEL_H_


