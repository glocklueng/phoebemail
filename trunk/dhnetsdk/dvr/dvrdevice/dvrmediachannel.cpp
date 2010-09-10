
#include "dvrmediachannel.h"
#include "dvrdevice.h"
#include "../def.h"
#include "dvrpacket_dvr2.h"


CDvrMediaChannel::CDvrMediaChannel(CDvrDevice *pDvrDevice, int nMainCommand, void *pParam)
	: CDvrChannel(pDvrDevice, nMainCommand)
{
    m_media_channel_parm = *(afk_media_channel_param_s*)pParam;
	m_nChannelType = m_media_channel_parm.conn.nInterfaceType;
	m_pSubSocket = NULL;
    m_bWorking = FALSE;
}

CDvrMediaChannel::~CDvrMediaChannel()
{
	
}

/*
 * ժҪ����������
 */
int CDvrMediaChannel::OnRespond(unsigned char *pBuf, int nLen)
{
	int nRet = -1;

	CReadWriteMutexLock lock(m_csDataCallBack);
    if (m_media_channel_parm.base.func != NULL)
    {
		nRet = m_media_channel_parm.base.func(this, pBuf + HEADER_SIZE, nLen - HEADER_SIZE, 0, m_media_channel_parm.base.udata);
    }
	lock.Unlock();

	CDvrChannel::OnRespond(pBuf, nLen);

	return nRet;
}

/*
 * ժҪ���ر�ͨ��
 */
BOOL CDvrMediaChannel::channel_close()
{
	// Ŀ��ֹͣ�ص�����ֹ����ɾ���˻ص�����쳣
	CReadWriteMutexLock lock(m_csDataCallBack);
	m_media_channel_parm.base.func = NULL;
	lock.Unlock();

	// �����Ƶ�����ˣ���Ҫ�ر���Ƶ
	if (m_bWorking)
    {
        if (!sendMonitor_dvr2(m_pDvrDevice, m_media_channel_parm.no, m_media_channel_parm.subtype, false, m_media_channel_parm.conn.nConnType, m_media_channel_parm.conn.nConnectID, m_media_channel_parm.conn.szLocalIp, m_media_channel_parm.conn.nLocalPort))
        {
#ifdef _DEBUG
			// OutputDebugString("Error:���͹ر�ʵʱԤ���������-->CDvrMediaChannel_dvr2::channel_close()\n");
#endif
        }
        m_bWorking = false;
    }
    
	m_pDvrDevice->device_remove_channel(this);
	
	if (m_pSubSocket != NULL)
	{
		m_pDvrDevice->DestroySubConn(m_media_channel_parm.conn.nConnType, m_pSubSocket, m_media_channel_parm.conn.nConnectID);
		m_pSubSocket = NULL;
	}

	return TRUE;
}

BOOL CDvrMediaChannel::channel_pause(BOOL pause)
{
    return FALSE;
}

int CDvrMediaChannel::channel_get_info(int type, void *parm)
{
	return 0;
}

int CDvrMediaChannel::channel_set_info(int type, void *parm)
{
	return 0;
}

/*
 * ժҪ����ͨ��
 */
int CDvrMediaChannel::channel_open()
{
	int nProtocalVer = 0;
	m_pDvrDevice->device_get_info(dit_protocol_version, &nProtocalVer);
	
	// �Ƚ���������
	if (nProtocalVer >= 6 || m_media_channel_parm.conn.nConnType != channel_connect_tcp)
	{
		m_media_channel_parm.conn.userdata = this;
		m_pSubSocket = m_pDvrDevice->CreateSubConn(&m_media_channel_parm.conn);
		if (m_pSubSocket == NULL)
		{
			return -1;
		}
	}

	// Ȼ��������Ƶ
	if (!sendMonitor_dvr2(m_pDvrDevice, m_media_channel_parm.no, m_media_channel_parm.subtype, true, m_media_channel_parm.conn.nConnType, m_media_channel_parm.conn.nConnectID, m_media_channel_parm.conn.szLocalIp, m_media_channel_parm.conn.nLocalPort))
	{
		if (m_pSubSocket != NULL)
		{
			m_pDvrDevice->DestroySubConn(m_media_channel_parm.conn.nConnType, m_pSubSocket, m_media_channel_parm.conn.nConnectID);
			m_pSubSocket = NULL;
		}
		return -1;
	}

	m_bWorking = TRUE;
	return 0;
}


