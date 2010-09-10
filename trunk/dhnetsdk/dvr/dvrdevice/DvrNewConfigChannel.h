// DvrNewConfigChannel.h: interface for the CDvrNewConfigChannel class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DVRNEWCONFIGCHANNEL_H__B24695CE_864D_4C8C_B417_B54D0AD5A75C__INCLUDED_)
#define AFX_DVRNEWCONFIGCHANNEL_H__B24695CE_864D_4C8C_B417_B54D0AD5A75C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "dvrchannel.h"
class CDvrDevice;

class CDvrNewConfigChannel : public CDvrChannel  
{
public:
	CDvrNewConfigChannel(CDvrDevice *pDvrDevice, int nMainCommand, void *pParam);
	virtual ~CDvrNewConfigChannel();

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
	int				GetPacketSequence() { return m_newconfigParam.nSequence; }

private:
	afk_newconfig_channel_param m_newconfigParam;
};

#endif // !defined(AFX_DVRNEWCONFIGCHANNEL_H__B24695CE_864D_4C8C_B417_B54D0AD5A75C__INCLUDED_)
