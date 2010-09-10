/*
* Copyright (c) 2009, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �����ƣ���Э�齻����
* ժ��Ҫ���ʺϼӰ���ŵ��ַ���Э�飬ÿ�������������ð���ű�ʶ�����������ֹ��ܡ�
*
*/
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_REQUESTCHANNEL_H__0053C362_A0DF_42F5_9EFB_AB1D4D2AA702__INCLUDED_)
#define AFX_REQUESTCHANNEL_H__0053C362_A0DF_42F5_9EFB_AB1D4D2AA702__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dvrchannel.h"
class CDvrDevice;


class CRequestChannel : public CDvrChannel
{
public:
	CRequestChannel(CDvrDevice *pDvrDevice, int nMainCommand, void *pParam);
	virtual ~CRequestChannel();

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
	int				GetRequestType() { return m_requestParam.nType; }
	int				GetPacketSequence() { return m_requestParam.nSequence; }

private:
	afk_request_channel_param m_requestParam;
	int				m_nProtocolType;
	int				m_nPacketSequence;
	DWORD			m_dwCreateTime;	// �첽δ�յ�Ӧ�����ɾ��
};


#endif // !defined(AFX_REQUESTCHANNEL_H__0053C362_A0DF_42F5_9EFB_AB1D4D2AA702__INCLUDED_)


