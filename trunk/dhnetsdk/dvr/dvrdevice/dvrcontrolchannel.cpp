
#include "dvrcontrolchannel.h"
#include "dvrdevice.h"


CDvrControlChannel::CDvrControlChannel(CDvrDevice *pDvrDevice, int nMainCommand, void *pParam)
	: CDvrChannel(pDvrDevice, nMainCommand)
{
    m_control_channel_parm = *(afk_control_channel_param_s*)pParam;
}

CDvrControlChannel::~CDvrControlChannel()
{
    
}

/*
 * ժҪ����������
 */
int CDvrControlChannel::OnRespond(unsigned char *pBuf, int nLen)
{ 
	int nRet = -1;

	if (m_control_channel_parm.base.func != NULL)
	{
		if (0x60 == (unsigned char)*pBuf)
		{
			// ����Ӳ�̷��� or ���ƾ��� or ����SD��
			if (1 == pBuf[8] || 2 == pBuf[8] || 3 == pBuf[8] || 6 == pBuf[8] || 7 == pBuf[8] || 8 == pBuf[8] || 10 == pBuf[8]) 
			{
				DWORD controlret = pBuf[12];
				nRet = m_control_channel_parm.base.func(this, 0, 0, (void *)controlret, m_control_channel_parm.base.udata);
			}
		}
		else if (0xE3 == (unsigned char)*pBuf)
		{
			// ���ñ������롢����ķ���
			int result = pBuf[9];
			nRet = m_control_channel_parm.base.func(this, 0, 0, (void *)result, m_control_channel_parm.base.udata);
		}
		else if (0x1A == (unsigned char)*pBuf || 0x1B == (unsigned char)*pBuf) 
		{
			// ���ñ������롢����ķ���
			int result = pBuf[8];
			nRet = m_control_channel_parm.base.func(this, 0, 0, (void *)result, m_control_channel_parm.base.udata);
		}
	}

	CDvrChannel::OnRespond(pBuf, nLen);

	return nRet;
}

/*
 * ժҪ���ر�ͨ��
 */
BOOL CDvrControlChannel::channel_close()
{
    m_pDvrDevice->device_remove_channel(this);

    return TRUE;
}

BOOL CDvrControlChannel::channel_pause(BOOL pause)
{
    return FALSE;
}

int CDvrControlChannel::channel_get_info(int type, void *parm)
{
    return 0;
}

int CDvrControlChannel::channel_set_info(int type, void *parm)
{
    return 0;
}

