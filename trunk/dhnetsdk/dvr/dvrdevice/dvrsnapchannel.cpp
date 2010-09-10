
#include "../StdAfx.h"
#include "dvrsnapchannel.h"
#include "dvrdevice.h"
#include "../def.h"
#include <stdio.h>
#include "memory.h"


CDvrSnapChannel::CDvrSnapChannel(CDvrDevice *pDvrDevice, int nMainCommand, void *pParam)
	: CDvrChannel(pDvrDevice, nMainCommand)
{
    m_snap_channel_parm = *(afk_snap_channel_param_s*)pParam;
    m_bWorking = TRUE;
	m_Pos = 0;
}

CDvrSnapChannel::~CDvrSnapChannel()
{
    
}

/*
 * ժҪ����������
 */
int CDvrSnapChannel::OnRespond(unsigned char *pBuf, int nLen)
{
	int nRet = -1;

    if (m_snap_channel_parm.base.func != NULL)
    {
		UINT EncodeType = 0;
		LONG CmdSerial = 0;
        LONG bodylen = 0;

		EncodeType = *(pBuf + 28); // ��������
		CmdSerial  = *(pBuf + 25); // ������ˮ��
        bodylen = nLen - HEADER_SIZE;

        nRet = m_snap_channel_parm.base.func(this, pBuf + HEADER_SIZE, bodylen, 0, m_snap_channel_parm.base.udata);

		/* ͼƬ�Ƿ�����������ص�����;���򻺴����ݴ� */
		if (nLen == HEADER_SIZE)
		{
			if (m_Pos > 0 && m_snap_channel_parm.snapcallback != NULL)
			{
				m_snap_channel_parm.snapcallback(m_snap_channel_parm.dwLoginID, m_SnapPicBytes, m_Pos,
					EncodeType, CmdSerial, m_snap_channel_parm.dwuser);
			}
			
			m_Pos = 0;
		}
		else
		{
			if (MAX_SNAPBUFFER_LEN > (m_Pos + bodylen)) // �жϻ����Ƿ��㹻����
			{
               memcpy(m_SnapPicBytes + m_Pos, pBuf + HEADER_SIZE, bodylen);
               m_Pos += bodylen;
			}
		}
    }

	CDvrChannel::OnRespond(pBuf, nLen);

	return nRet;
}

/*
 * ժҪ���ر�ͨ��
 */
BOOL CDvrSnapChannel::channel_close()
{
    m_pDvrDevice->device_remove_channel(this);

	return TRUE;
}

BOOL CDvrSnapChannel::channel_pause(BOOL pause)
{
    return FALSE;
}

int CDvrSnapChannel::channel_get_info(int type, void *parm)
{
    return 0;
}

int CDvrSnapChannel::channel_set_info(int type, void *parm)
{
    return 0;
}



