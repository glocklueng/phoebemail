/*
* Copyright (c) 2009, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �����ƣ�ץͼ���ܽ�����
* ժ��Ҫ��ץͼ�������ݽ�����
*
*/
//////////////////////////////////////////////////////////////////////////

#ifndef _DVRSNAPCHANNEL_H_
#define _DVRSNAPCHANNEL_H_

#include "dvrchannel.h"
class CDvrDevice;

#define MAX_SNAPBUFFER_LEN  1048576 //1M bytes


class CDvrSnapChannel : public CDvrChannel
{
public:
	CDvrSnapChannel(CDvrDevice *pDvrDevice, int nMainCommand, void *pParam);
	virtual ~CDvrSnapChannel();
	
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
    int				GetChannelIndex() { return m_snap_channel_parm.no; }
	int				GetChannelSubtype() { return m_snap_channel_parm.subtype; }


protected:
	unsigned char	m_SnapPicBytes[MAX_SNAPBUFFER_LEN]; // ץͼ�������ݻ���
    afk_snap_channel_param_s m_snap_channel_parm;
    BOOL            m_bWorking;
	LONG			m_Pos;			// ͼƬ�ݴ滺��λ��
};


#endif // _DVRSNAPCHANNEL_H_

