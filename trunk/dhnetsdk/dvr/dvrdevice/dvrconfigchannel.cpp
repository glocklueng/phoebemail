
#include "dvrconfigchannel.h"
#include "dvrdevice.h"


CDvrConfigChannel::CDvrConfigChannel(CDvrDevice *pDvrDevice, int nMainCommand, void *pParam)
	: CDvrChannel(pDvrDevice, nMainCommand)
{
    m_config_channel_parm = *(afk_config_channel_param_s*)pParam;
}

CDvrConfigChannel::~CDvrConfigChannel()
{
}

/*
 * ժҪ����������
 */
int CDvrConfigChannel::OnRespond(unsigned char *pBuf, int nLen)
{
	int nRet = -1;
    int nConfigType = GetConfigType();
    int nConfigResult = 0;
	
	switch(nConfigType)
	{
	case 0:
	case 1: // ���ñ������롢���
		nConfigResult = (*(pBuf + 9) == 0);
		break;
	case 2: // ��������
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
	case 16:
	case 32: // ��������������
		nConfigResult = pBuf[8];
		break;
	case 17: // ����¼��״̬        
	case 18: // �����豸ʱ��
		break;
	case 19: // ǿ��I��
	case 20: // ������������
		nConfigResult = (*(pBuf + 8) == 0);
		break;
	default:
		return -1;
		break;
	}

	if (m_config_channel_parm.base.func != NULL)
	{
		nRet = m_config_channel_parm.base.func(this, 0, nConfigResult, 0, m_config_channel_parm.base.udata);
	}

	CDvrChannel::OnRespond(pBuf, nLen);

	return nRet;
}

/*
 * ժҪ���ر�ͨ��
 */
BOOL CDvrConfigChannel::channel_close()
{
    m_pDvrDevice->device_remove_channel(this);

    return TRUE;
}

BOOL CDvrConfigChannel::channel_pause(BOOL pause)
{
    return FALSE;
}

int CDvrConfigChannel::channel_get_info(int type, void *parm)
{
    return 0;
}

int CDvrConfigChannel::channel_set_info(int type, void *parm)
{
    return 0;
}


