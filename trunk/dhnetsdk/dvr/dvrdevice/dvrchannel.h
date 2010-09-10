/*
* Copyright (c) 2009, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �����ƣ�����ͨ������
* ժ��Ҫ��ÿ��Э�齻�����̿��Կ���һ������ͨ����
*         ���ó��󹤳������ģʽ��Ϊnetsdk���ṩ��ͳһ�Ľӿڣ����������ܲ�ͬЭ�鲻ͬ��ɲ����ԡ�
*
*/
//////////////////////////////////////////////////////////////////////////

#ifndef _DVRCHANNEL_H_
#define _DVRCHANNEL_H_

#include "../osIndependent.h"
#include "../kernel/afkdef.h"
#include "../kernel/afkinc.h"

#include "../ReadWriteMutex.h"
using namespace SPTools;

class CDvrDevice;


class CDvrChannel : public afk_channel_s
{
public:
	CDvrChannel(CDvrDevice *pDvrDevice, int nMainCommand);
	virtual ~CDvrChannel();

public:
    /* �ر�ͨ�� */
    virtual BOOL	channel_close() = 0;

    /* ��ͣͨ�� */
    virtual BOOL	channel_pause(BOOL pause) = 0;

    /* ��ȡ��Ϣ */
    virtual int		channel_get_info(int type, void *parm) = 0;

    /* ������Ϣ */
    virtual int		channel_set_info(int type, void *parm) = 0;

	/* �������� */
	virtual int		OnRespond(unsigned char *pBuf, int nLen);


public:
    int				GetMainCommand() { return m_nMainCommand; }
	int				GetChannelType() { return m_nChannelType; }
    CDvrDevice*		channel_getdevice() { return m_pDvrDevice; }


public:
	int				channel_addRef();
	int				channel_decRef();

	void			startstatisc();
    void			statiscing(unsigned int nLen);
    unsigned int	statisc();


protected:
    CDvrDevice*		m_pDvrDevice;
    int             m_nMainCommand;
	int				m_nChannelType;

    unsigned int    m_nStatistic;
    BOOL            m_bStatiscEn;

	CReadWriteMutex	m_csDataCallBack;	// �������ڸ�ֹͣ�ص�ͬ��
	LN_LIFECOUNT	m_llifecount;
};

#endif // _DVRCHANNEL_H_


