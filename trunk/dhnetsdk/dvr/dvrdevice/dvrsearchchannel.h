/*
* Copyright (c) 2009, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �����ƣ���ѯ���ܽ�����
* ժ��Ҫ����ѯ�������ݽ�����
*
*/
//////////////////////////////////////////////////////////////////////////

#ifndef _DVRSEARCHCHANNEL_H_
#define _DVRSEARCHCHANNEL_H_

#include "dvrchannel.h"
class CDvrDevice;


class CDvrSearchChannel : public CDvrChannel
{
public:
	CDvrSearchChannel(CDvrDevice *pDvrDevice, int nMainCommand, void *pParam);
	virtual ~CDvrSearchChannel();
	
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
    unsigned int	GetSearchType() { return m_search_channel_parm.type; }
	unsigned int	GetSearchSubtype() { return m_search_channel_parm.subtype; }
    int				GetChannelIndex() { return m_search_channel_parm.no; }


protected:
    afk_search_channel_param_s m_search_channel_parm;
    unsigned int	m_nLogSize;
    unsigned int	m_nLogRecSize;
};


#endif // _DVRSEARCHCHANNEL_H_

