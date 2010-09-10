
#include "dvrupgradechannel.h"
#include "dvrdevice.h"
#include "dvrpacket_comm.h"


CDvrUpgradeChannel::CDvrUpgradeChannel(CDvrDevice *pDvrDevice, int nMainCommand, void *pParam)
	: CDvrChannel(pDvrDevice, nMainCommand)
{
    m_upgrade_channel_param = *(afk_upgrade_channel_param_s*)pParam;
    m_bSendDone = FALSE;
    m_packetindex = 0;
	m_dwThreadID = 0;
    CreateEventEx(m_hExitThread, TRUE, FALSE);
}

CDvrUpgradeChannel::~CDvrUpgradeChannel()
{
	CloseEventEx(m_hExitThread);
	CloseThreadEx(m_hThread);

    m_upgrade_channel_param.base.func = 0;
}

/*
 * ժҪ����������
 */
int CDvrUpgradeChannel::OnRespond(unsigned char *pBuf, int nLen)
{
	int nRet = -1;

	CReadWriteMutexLock lock(m_csDataCallBack);
	
    if (m_upgrade_channel_param.base.func != NULL)
    {
		int nMainType = GetMainType();
		
		switch(nMainType)
		{
		case AFK_CHANNEL_UPLOAD_UPGRADE:
			{
				if (pBuf[9] == 's' && pBuf[10] == 't' && pBuf[11] == 'a' && pBuf[12] == 'r' && pBuf[13] == 't') // ��ʼ����Ӧ��
				{
					nRet = m_upgrade_channel_param.base.func(this, 0, 0, (void *)1, m_upgrade_channel_param.base.udata);
				}
				else if (pBuf[9] == 'r' && pBuf[10] == 'i' && pBuf[11] == 'g' && pBuf[12] == 'h' && pBuf[13] == 't') // �������Ӧ��
				{
					nRet = m_upgrade_channel_param.base.func(this, 0, 0, (void *)2, m_upgrade_channel_param.base.udata);
				}
				else if (pBuf[9] == 'e' && pBuf[10] == 'r' && pBuf[11] == 'r' && pBuf[12] == 'o' && pBuf[13] == 'r') // ��������Ӧ��
				{
					nRet = m_upgrade_channel_param.base.func(this, 0, 0, (void *)3, m_upgrade_channel_param.base.udata);
				}
				else if (2 == pBuf[24]) // ��������֪ͨ
				{
					nRet = m_upgrade_channel_param.base.func(this, pBuf+26, 1, (void *)4, m_upgrade_channel_param.base.udata); // 4��ʾ��������֪ͨ
				}
				/*
				switch(pBuf[24])
				{
				case 1: // ���Դ�����������
					{
						nRet = m_upgrade_channel_param.base.func(this, 0, 0, (void *)1, m_upgrade_channel_param.base.udata);
					}
					break;
				case 2: // ��������
					{
						nRet = m_upgrade_channel_param.base.func(this, (unsigned char *)m_upgrade_channel_param.size, 
									m_upgrade_channel_param.size*pbuf[26]/100, (void *)2, m_upgrade_channel_param.base.udata);
						SetEvent(m_hACK);
					}
					break;
				case 10: // ���ݴ���
					{
						nRet = m_upgrade_channel_param.base.func(this, 0, 0, (void *)10, m_upgrade_channel_param.base.udata);
					}
					break;
				case 11: // ϵͳæ����ʱ�޷�����
					{
						nRet = m_upgrade_channel_param.base.func(this, 0, 0, (void *)11, m_upgrade_channel_param.base.udata);
					}
					break;
				case 12: // ������У��ʧ��
					{
						nRet = m_upgrade_channel_param.base.func(this, 0, 0, (void *)12, m_upgrade_channel_param.base.udata);
					}
					break;
				case 13:  // �������Ƿ�(��ͬ������)
					{
						nRet = m_upgrade_channel_param.base.func(this, 0, 0, (void *)13, m_upgrade_channel_param.base.udata);
					}
					break;
				case 14: // ����ʧ��
					{
						nRet = m_upgrade_channel_param.base.func(this, 0, 0, (void *)14, m_upgrade_channel_param.base.udata);
					}
					break;
				case 15: // �ò���Ա��Ȩ�����豸
					{
						nRet = m_upgrade_channel_param.base.func(this, 0, 0, (void *)15, m_upgrade_channel_param.base.udata);
					}
					break;
				default:
					break;
				}
				*/
			}
			break;
		case AFK_CHANNEL_UPLOAD_CONFIGFILE:
			{
				if (0x04 == (unsigned char)*(pBuf + 10))		// ���Կ�ʼ���������ļ�
				{
					nRet = m_upgrade_channel_param.base.func(this, 0, 0, (void *)1, m_upgrade_channel_param.base.udata);
				}
				else if (0x05 == (unsigned char)*(pBuf + 10))	// �������������ļ�
				{
					nRet = m_upgrade_channel_param.base.func(this, 0, 0, (void *)2, m_upgrade_channel_param.base.udata);
				}
				else if (0x06 == (unsigned char)*(pBuf + 10))	// ���������ļ��ɹ�
				{
					nRet = m_upgrade_channel_param.base.func(this, 0, 0, (void *)3, m_upgrade_channel_param.base.udata);
				}
				else if (0x07 == (unsigned char)*(pBuf + 10))	// ���������ļ�ʧ��
				{
					nRet = m_upgrade_channel_param.base.func(this, 0, 0, (void *)4, m_upgrade_channel_param.base.udata);
				}
				else if (0x08 == (unsigned char)*(pBuf + 10))	// ���������ļ�����
				{
					nRet = m_upgrade_channel_param.base.func(this, 0, 0, (void *)5, m_upgrade_channel_param.base.udata);
				}
			}
			break;
		default:
			break;
		}
	}

	lock.Unlock();

	CDvrChannel::OnRespond(pBuf, nLen);

	return nRet;
}

BOOL CDvrUpgradeChannel::channel_close()
{
	CReadWriteMutexLock lock(m_csDataCallBack);
	m_upgrade_channel_param.base.func = NULL;
	lock.Unlock();

	SetEventEx(m_hExitThread);

#ifdef WIN32
	DWORD hdl = GetCurrentThreadId();
	if (hdl == m_dwThreadID)
	{
		//��ǰ�߳�
	}
#else	//linux
	pthread_t self = pthread_self();
	if (self == m_hThread.m_hThread)
	{
		//��ǰ�߳�
	}
#endif
	else
	{
		DWORD dw = WaitForSingleObjectEx(m_hThread, 1000*10);
		if (WAIT_OBJECT_0 != dw)
		{
			TerminateThreadEx(m_hThread, 0);	
		}
	}

	CloseThreadEx(m_hThread);
	CloseEventEx(m_hExitThread);

	if (m_bSendDone)
	{
		int nMainType = GetMainType();

		// ���ͽ�����־
		switch(nMainType)
		{
		case AFK_CHANNEL_UPLOAD_UPGRADE:
			{
				if (sendUpgradeData_comm(m_pDvrDevice, m_upgrade_channel_param.filetype, 0, -1, &m_upgrade_channel_param))
				{
					m_bSendDone = FALSE;
				}
			}
			break;
		case AFK_CHANNEL_UPLOAD_CONFIGFILE:
			{
				if (sendImportCfgData_comm(m_pDvrDevice, m_upgrade_channel_param.filetype, 0, -1, &m_upgrade_channel_param))
				{
					m_bSendDone = FALSE;
				}
			}
		    break;
		default:
		    break;
		}
	}

    m_pDvrDevice->device_remove_channel(this);

    return TRUE;
}

BOOL CDvrUpgradeChannel::channel_pause(BOOL pause)
{
    return FALSE;
}

int CDvrUpgradeChannel::channel_get_info(int type, void *parm)
{
	return 0;
}

DWORD __stdcall  UpgradeThreadProc(LPVOID *pPara)
{
    CDvrUpgradeChannel *pUpgradeChannel = (CDvrUpgradeChannel*)pPara;
	if (pUpgradeChannel == NULL)
	{
		return 0;
	}

    afk_upgrade_channel_param_s param = pUpgradeChannel->GetUpgradeChannelParam();
	CDvrDevice *pDvrDevice = pUpgradeChannel->channel_getdevice();

    unsigned char buffer[1024];
    FILE *file = fopen(param.filename, "rb");
    if (file)
    {
        int readlen = 0;
        int packetId = 0;
		int sendlen = 0;
		
        while (WaitForSingleObjectEx(pUpgradeChannel->m_hExitThread,0) != WAIT_OBJECT_0)
        {
			int nMainType = pUpgradeChannel->GetMainType();
			
			if (AFK_CHANNEL_UPLOAD_UPGRADE == nMainType)
			{
				if ((readlen = fread(buffer, 1, 1024, file)) > 0)
				{
					int ret = sendUpgradeData_comm(pDvrDevice, packetId++, (char*)buffer, readlen, &param);
					if (ret == -3)	// ���ͻ�����������sleep�ٷ�
					{
						fseek(file, -readlen, SEEK_CUR);
						Sleep(1);
						continue;
					}
					else if (ret < 0)
					{
						fclose(file);
						if (param.base.func)
						{
							param.base.func(pUpgradeChannel, 0, 0, (void *)3, param.base.udata);
						}
						break;
					}
					
					sendlen += readlen;
					if (sendlen >= param.size)
					{
						pUpgradeChannel->SetUpgradeState(true);
					}
					
					if (param.base.func)
					{
						param.base.func(pUpgradeChannel, (unsigned char*)param.size, sendlen, 0, param.base.udata);
					}
				}
				else
				{
					// ���ݷ��꣬���ͽ�����־��
					int ret = sendUpgradeData_comm(pDvrDevice, param.filetype, 0, -1, &param);
					while (ret == -3 && WaitForSingleObjectEx(pUpgradeChannel->m_hExitThread,0) != WAIT_OBJECT_0)	//	���ͻ�����������sleep�ٷ�
					{
						Sleep(1);
						ret = sendUpgradeData_comm(pDvrDevice, param.filetype, 0, -1, &param);
					}

					pUpgradeChannel->SetUpgradeState(FALSE);
					fclose(file);
					file = 0;
					break;
				}
			}
			else if (AFK_CHANNEL_UPLOAD_CONFIGFILE == nMainType)
			{
				if ((readlen = fread(buffer, 1, 1024, file)) > 0)
				{
					int ret = sendImportCfgData_comm(pDvrDevice, packetId++, (char*)buffer, readlen, &param);
					if (ret == -3)	// ���ͻ�����������sleep�ٷ�
					{
						fseek(file, -readlen, SEEK_CUR);
						Sleep(1);
						continue;
					}
					else if (ret < 0)
					{
						fclose(file);
						if (param.base.func)
						{
							param.base.func(pUpgradeChannel, 0, 0, (void *)3, param.base.udata);
						}
						break;
					}
					
					sendlen += readlen;
					if (sendlen >= param.size)
					{
						pUpgradeChannel->SetUpgradeState(TRUE);
					}
					
					if (param.base.func)
					{
						param.base.func(pUpgradeChannel, (unsigned char*)param.size, sendlen, 0, param.base.udata);
					}
				}
				else
				{
					// ���ݷ��꣬���ͽ�����־��
					int ret = sendImportCfgData_comm(pDvrDevice, param.filetype, 0, -1, &param);
					while (ret == -3 && WaitForSingleObjectEx(pUpgradeChannel->m_hExitThread,0) != WAIT_OBJECT_0)	//	���ͻ�����������sleep�ٷ�
					{
						Sleep(1);
						ret = sendImportCfgData_comm(pDvrDevice, param.filetype, 0, -1, &param);
					}
					
					pUpgradeChannel->SetUpgradeState(FALSE);
					fclose(file);
					file = 0;

					if (param.base.func)
					{
						param.base.func(pUpgradeChannel, (unsigned char*)param.size, -1, 0, param.base.udata);
					}
					break;
				}
			}
			else
			{
				break;
			}
        }

		if (file)
		{
			fclose(file);
		}
    }

    return 0;
}

int CDvrUpgradeChannel::channel_set_info(int type, void *parm)
{
    int ret = CreateThreadEx(m_hThread, 0, (LPTHREAD_START_ROUTINE)UpgradeThreadProc, (void*)this, /*CREATE_SUSPENDED*/0, &m_dwThreadID);
	if (ret >= 0)
	{
// 		m_hACK = CreateEvent(0, FALSE, FALSE, 0);
// 		if (m_hACK)
// 		{
// 			ResumeThread(m_hThread);
// 			return 1;
// 		}
// 		else
// 		{
// 			TerminateThread(m_hThread, 0);
// 			CloseHandle(m_hThread);
// 		}
	}

    return 1;
}




