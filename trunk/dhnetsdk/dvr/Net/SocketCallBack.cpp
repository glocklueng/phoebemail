
#include "../def.h"
#include "../dvrdevice/dvrdevice.h"
#include "../dvrdevice/dvrchannel.h"
#include "../ParseString.h"
#include "SocketCallBack.h"


/*
 * ժҪ�������ӽ������ݴ���
 */
int __stdcall OnOtherPacket(unsigned char *pBuf, int nLen, void *userdata)
{
    if (nLen < HEADER_SIZE)
    {
        return -1;	// ������
    }

    CDvrDevice *device = (CDvrDevice*)userdata;
    CDvrChannel *pDvrChannel = NULL;

	try
	{
	if (NULL == device)
	{
		return -1;  // ϵͳ����
	}

    /************************************************************************/

    // ʵʱ���Ӱ�
    if (0xBC == (unsigned char)*pBuf)
    {
        int channel = (unsigned char)*(pBuf + 8);

		// Ԥ��ͨ���� = �ܵ�ͨ����
        if (channel == device->GetVideoChannelCount())
        {
            pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_PREVIEW, channel);
        }
		else if (10 == pBuf[24]) // ץͼ
		{
			pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_CAPTURE, channel);
		}
        else
        {
            pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_MEDIA, channel);
        }

        if (pDvrChannel)
        {
            pDvrChannel->OnRespond((unsigned char*)pBuf, nLen);
        }
    }

    // ���ذ�
    else if (0xBB == (unsigned char)*pBuf)
    {
        int channel = (unsigned char)*(pBuf + 8);
        pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_DOWNLOAD, AFK_CHANNEL_DOWNLOAD_RECORD, channel-1);
        if (pDvrChannel)
        {
            pDvrChannel->OnRespond((unsigned char*)pBuf, nLen);
			
            // ��������
            if (*(unsigned int*)(pBuf + 15) == 0x12 ||
                *(unsigned int*)(pBuf + 4) == 0x00)
            {
                pDvrChannel->OnRespond(0, -1);
            }
        }
    }

	// ���������ļ�
	else if (0xF3 == (unsigned char)*pBuf && (0x02 == (unsigned char)*(pBuf + 8) || 0xFF == (unsigned char)*(pBuf + 8)))
	{
		pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_DOWNLOAD, AFK_CHANNEL_DOWNLOAD_CONFIGFILE, 16);

		if (pDvrChannel)
		{
			pDvrChannel->OnRespond((unsigned char*)pBuf, nLen);
		}
	}

    // ����״̬�� and record state
    else if (0xB1 == (unsigned char)*pBuf)
    {
        if (nLen == HEADER_SIZE)
        {
			//if querying
			if (pBuf[8] != 0x0A && pBuf[8] != 0x00)//0x0aΪ��ѯ��Ƶ����״̬,0x00Ϊ�������ѯ����
			{
				pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, AFK_CHENNEL_SEARCH_DEVSTATE);
				if (pDvrChannel)
				{
					pDvrChannel->OnRespond((unsigned char*)pBuf, nLen);
					pDvrChannel->channel_decRef();
				}
			}
			pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, AFK_CHENNEL_SEARCH_DEVSTATE,0x10);
			if (pDvrChannel)
			{
				pDvrChannel->OnRespond((unsigned char*)pBuf, nLen);
				pDvrChannel->channel_decRef();
			}
			pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, AFK_CHENNEL_SEARCH_DEVSTATE,0x12);
			if (pDvrChannel)
			{
				pDvrChannel->OnRespond((unsigned char*)pBuf, nLen);
				pDvrChannel->channel_decRef();
			}

			//alarm packet
			pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_ALARM, 0);
			if (pDvrChannel)
			{
				pDvrChannel->OnRespond((unsigned char*)pBuf, nLen);
			}
        }
		else if ((nLen > HEADER_SIZE + 10) &&
			((pBuf[13] == 0xbf) || (pBuf[13] == 0x7f))) // СƱ��Ϣ����СƱ������
		{
			pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_ALARM, 0);
			if (pDvrChannel)
			{
				pDvrChannel->OnRespond((unsigned char*)pBuf, nLen);
			}
		}
		else if (0x04 == pBuf[8])
		{
			//burning progress
			pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, AFK_CHENNEL_SEARCH_DEVSTATE);
			if (pDvrChannel)
			{
				pDvrChannel->OnRespond((unsigned char*)pBuf, nLen);
			}
		}
		else if (0x06 == pBuf[8]) 
		{
			//shelter alarm
 			pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_ALARM, 0);
            if (pDvrChannel)
            {
                pDvrChannel->OnRespond((unsigned char*)pBuf, nLen);
            }	
		}
		else if (0x03 == pBuf[8] || 0x08 == pBuf[8] || 0x09 == pBuf[8])
		{
			//alarm packet-disk full, disk error
 			pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_ALARM, 0);
            if (pDvrChannel)
            {
                pDvrChannel->OnRespond((unsigned char*)pBuf, nLen);
            }	
		}
        else if (0x01 == pBuf[8])
        {
            pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, AFK_CHANNEL_SEARCH_RECORDSTATE);
            if (pDvrChannel)
            {
                pDvrChannel->OnRespond((unsigned char*)pBuf, nLen);
            }
        }
		else if (0x0b == pBuf[8])
		{
			pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, AFK_CHENNEL_SEARCH_DEVSTATE);
			if (pDvrChannel)
			{
				pDvrChannel->OnRespond((unsigned char *)pBuf, nLen);
			}
		}
		else if (0x0c == pBuf[8])
		{
			pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, AFK_CHENNEL_SEARCH_DEVSTATE);
			if (pDvrChannel)
			{
				pDvrChannel->OnRespond((unsigned char *)pBuf, nLen);
			}
		}
		else if (0x0d == pBuf[8])//���������ź�ǿ��
		{
			pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, AFK_CHENNEL_SEARCH_DEVSTATE);
			if (pDvrChannel)
			{
				pDvrChannel->OnRespond((unsigned char *)pBuf, nLen);
			}
		}
		else
		{
#ifdef _DEBUG
			OutputDebugString(" UnKnown subCmd in Cmd 0xb1 \n");		
#endif
		}
    }
	else if (0x69 == pBuf[0] && nLen > HEADER_SIZE) //==HEADER_SIZE�Ƕ��ķ��ذ�����������
	{
		//gps������Ϣ
		if(pBuf[8] == 2 &&  (*(unsigned char *)(pBuf+12)) == 155)
		{
			pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_GPS,0);
			if(pDvrChannel)
			{
				pDvrChannel->OnRespond((unsigned char *)pBuf,nLen);
				pDvrChannel->channel_decRef();
			}
		}
		//if querying
		pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, AFK_CHENNEL_SEARCH_DEVSTATE,0x11);
		if (pDvrChannel)
		{
			pDvrChannel->OnRespond((unsigned char*)pBuf, nLen);
			pDvrChannel->channel_decRef();
		}
		//alarm packet
		pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_ALARM, 0);
		if (pDvrChannel)
		{
			pDvrChannel->OnRespond((unsigned char*)pBuf, nLen);
		}
	}
	else if(0x69 == pBuf[0])// && 0xa1 == pBuf[12] && nLen == HEADER_SIZE)
	{
		//alarm packet
		if(0xa1 == (unsigned char)pBuf[12] && 0x01 == (unsigned char)pBuf[8])// && nLen == HEADER_SIZE)
		{
			pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_ALARM, 0);
			if (pDvrChannel)
			{
				pDvrChannel->OnRespond((unsigned char*)pBuf, nLen);
			}
		}
	}
	
    // ¼���ļ�,�����ļ�,�����ļ�
    else if (0xB6 == (unsigned char)*pBuf || 0xB7 == (unsigned char)*pBuf 
        || 0xE5 == (unsigned char)*pBuf)
    {
        //0Ϊ��ѯ����
        pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, AFK_CHANNEL_SEARCH_RECORD);
        if (pDvrChannel)
        {
            pDvrChannel->OnRespond((unsigned char*)pBuf , nLen);
        }
    }

    // ��־��Ϣ
    else if (0xB2 == (unsigned char)*pBuf)
    {
        //1Ϊ��ѯ����
        pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, AFK_CHANNEL_SEARCH_LOG, pBuf[16]);
        if (pDvrChannel)
        {
            pDvrChannel->OnRespond((unsigned char*)pBuf , nLen);
        }
    }

    // ͨ������
    else if (0xB8 == (unsigned char)*pBuf)
    {
        //2Ϊ��ѯ����
        pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, AFK_CHANNEL_SEARCH_CHANNELNAME);
		//ͨ��0xA8��ѯ
        if (pDvrChannel)
        {
            pDvrChannel->OnRespond((unsigned char*)pBuf , nLen);
			pDvrChannel->channel_decRef();
        }
		
        pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, AFK_CHANNEL_SEARCH_CONFIG, CONFIG_TYPE_TITLE);
        if (pDvrChannel)
        {
            pDvrChannel->OnRespond((unsigned char*)pBuf , nLen);
        }
    }

    // ͸������
    else if (0x20 == (unsigned char)*pBuf)
    {
        int trans_device_type = (unsigned char)*(pBuf + 8);
		int nCmdType = (unsigned char)*(pBuf + 9);
		if(nCmdType != 5)
		{
			pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_TRANS, trans_device_type);

			if (pDvrChannel)
			{
				pDvrChannel->OnRespond((unsigned char*)pBuf, nLen);
			}
		}
		else 
		{
			pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, AFK_CHANNEL_SEARCH_TRANSCOM, trans_device_type);
			if (pDvrChannel)
			{
				pDvrChannel->OnRespond((unsigned char*)pBuf , nLen);
			}
		}
    }

    // �����Խ�
    else if (0xC0 == (unsigned char)*pBuf)
    {
//      unsigned char respond = (unsigned char)*(pBuf + 8);
        pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_TALK, 0);
        if (pDvrChannel)
        {
			//delete by zhaojs 10-28 �ᵼ�´���
            //pDvrChannel->OnRespond((unsigned char*)respond, 0);
            /*//���նԽ�
            if (respond == 1)
            {       
                pDvrChannel->OnRespond((unsigned char*)respond, 0);
            }
            //�ܾ��Խ�(2)
            else
            {
                pDvrChannel->OnRespond((unsigned char*)respond, 0);
            }*/
        }
    }

    // �����Խ�����
    else if (0x1D == (unsigned char)*pBuf)
    {
        //int id = pBuf[12];
        pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_TALK, 0);
        if (pDvrChannel)
        {
            pDvrChannel->OnRespond((unsigned char*)pBuf, nLen);
        }
    }

    // �������ò�ѯ������
    else if (0xE3 == (unsigned char)*pBuf)
    {
        if ((unsigned char)*(pBuf + 8) == 0x00)
        {
            pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, AFK_CHANNEL_SEARCH_ALARMCTRL_IN);
        }
        else if ((unsigned char)*(pBuf + 8) == 0x01)
        {
            pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, AFK_CHANNEL_SEARCH_ALARMCTRL_OUT);
        }
        else if ((unsigned char)*(pBuf + 8) == 0x02)
        {
			//�ݲ�����
            //pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, 0);
        }
        else if ((unsigned char)*(pBuf + 8) == 0x03)
        {
			//��������
            //pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_CONTROL, 0);
        }
		else if((unsigned char)*(pBuf + 8) == 0x05)
		{
			pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, AFK_CHANNEL_SEARCH_ALARMTRRIGER_MODE);
		}
		
        if (pDvrChannel)
        {
            pDvrChannel->OnRespond((unsigned char*)pBuf, nLen);
        }
    }

    // �豸ʱ��
    else if (0x24 == (unsigned char)*pBuf)
    {
		unsigned char subcmd = pBuf[8];
        pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, AFK_CHANNEL_SEARCH_DEVTIME);
        if (pDvrChannel && (0 == subcmd))
        {
            pDvrChannel->OnRespond((unsigned char*)pBuf , nLen);
        }
    }

	// ǿ��I֡
	else if (0x80 == (unsigned char)*pBuf)
	{
		pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_CONFIG, 19);
		if (pDvrChannel)
		{
			pDvrChannel->OnRespond((unsigned char*)pBuf, nLen);
		}
	}

	// ������������
	else if (0x81 == (unsigned char)*pBuf)
	{
		pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_CONFIG, 20);
		if (pDvrChannel)
		{
			pDvrChannel->OnRespond((unsigned char*)pBuf, nLen);
		}
	}

    // ����Э���������Э��
    else if (0xE4 == (unsigned char)*pBuf)
    {
        int protocoltype = *(unsigned char*)(pBuf + 8);
        if (protocoltype == 0)
        {
            pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, AFK_CHANNEL_SEARCH_COMMPROTOCOL);
        }
        else if (protocoltype == 1)
        {
            pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, AFK_CHANNEL_SEARCH_DCDPROTOCOL);
        }
        else if(protocoltype == 2)
		{
			pDvrChannel =device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH,AFK_CHANNEL_SEARCH_PTZ);
		}
        if (pDvrChannel)
        {
            pDvrChannel->OnRespond((unsigned char*)pBuf , nLen);
        }
    }

    // ϵͳ��Ϣ
    else if (0xB4 == (unsigned char)*pBuf)
    {
		int systemtype = *(unsigned char*)(pBuf + 8);

		pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, AFK_CHANNEL_SEARCH_SYSTEM_INFO, systemtype);
		/*
        if (systemtype >= 0 && systemtype <= 6)
        {
            pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, 24 + systemtype);
        }
		else if (7 == systemtype)
		{
			pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, 33);
		}
		else if (11 == systemtype)
		{
			pDvrChannel = device->GetChannel(AFK_CHANNEL_TYPE_SEARCH, 43);
		}
       */

        if (pDvrChannel)
        {
            pDvrChannel->OnRespond((unsigned char*)pBuf , nLen);
        }
    }

    // ���÷���
    else if (0xB3 == (unsigned char)*pBuf && 0xF7 != (unsigned char)*(pBuf+16))
    {
        int configtype = *(unsigned char*)(pBuf + 16);

		pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, AFK_CHANNEL_SEARCH_CONFIG, configtype);

	//	if (200 == configtype)
	//	{
	//		pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, 32);
	//	}
	//	else if (23 == configtype) //��Ƶ��������
	//	{
	//		pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, 36);
	//	}
	//	else if (126 == configtype)
	//	{
	//		pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, 40);
	//	}
	//	else if (127 == configtype)
	//	{
	//		pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, 35);
	//	}
	//	else if (128 == configtype)
	//	{
	//		pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, 38);
	//	}
	//	else if (129 == configtype)
	//	{
	//		pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, 39);
	//	}
	//	else if (123 == configtype)
	//	{
	//		pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, CONFIG_TYPE_RECORD_NEW);
	//	}
	//	else 
		if (124 == configtype)
		{
			if (pDvrChannel != NULL)
			{
				pDvrChannel->channel_decRef();
			}
			pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, AFK_CHANNEL_SEARCH_CONFIG, pBuf[24]+CONFIG_TYPE_ALARM_BEGIN);
		}
		else if (125 == configtype)
		{
			if (pDvrChannel != NULL)
			{
				pDvrChannel->channel_decRef();
			}
			pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, AFK_CHANNEL_SEARCH_CONFIG, CONFIG_TYPE_TIMESHEET);
		}
	//	else if (17 == configtype)
	//	{
	//		pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, 41);
	//	}
	//	else if (18 == configtype)
	//	{
	//		pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, 42);
	//	}
	//	else
	//	{
	//		pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, 5 + configtype);
	//	}

        if (pDvrChannel)
        {
            pDvrChannel->OnRespond((unsigned char*)pBuf , nLen);
        }
    }

    // �û���������
    else if (0xB5 == (unsigned char)*pBuf)
    {
        int useroperatetype = *(unsigned char*)(pBuf + 8);	
		if (11 == useroperatetype)
		{
			//��ѯ�����û�״̬
			pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, AFK_CHENNEL_SEARCH_DEVSTATE);
		}
		else
		{
			pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_USER, useroperatetype);
		}
        
        if (pDvrChannel)
        {
            pDvrChannel->OnRespond((unsigned char*)pBuf , nLen);
        }
    }

	// ��ѯ�豸����״̬ & DDNS��ѯIP����
	else if (0x82 == (unsigned char)*pBuf)
	{
		//DDNS��ѯIP����
		if (device->GetType() == PRODUCT_DVR_DDNS && pBuf[8] == 50)
		{
			pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, AFK_CHANNEL_SEARCH_DDNSIP_BYNAME);
			if (pDvrChannel)
			{
				pDvrChannel->OnRespond((unsigned char*)pBuf, nLen);
			}
		}
		//��ѯ�豸����״̬
		else
		{
			pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, AFK_CHENNEL_SEARCH_DEVWORKSTATE);
			if (pDvrChannel)
			{
				pDvrChannel->OnRespond((unsigned char*)pBuf, nLen);
			}
		}
	}

	// �豸���ƣ�������رգ����� Added by Linjy-2006-11-1
	// Ӳ�̿��Ʒ��� Linjy-2006-12-18
	else if (0x60 == (unsigned char)*pBuf)
	{
		pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_CONTROL, 0);
		if (pDvrChannel)
		{
			pDvrChannel->OnRespond((unsigned char*)pBuf, nLen);
		}
	} 

	// �豸�������� Added by Linjy-2006-11-8
	else if (0XBA == (unsigned char)*pBuf)
	{
		pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_UPGRADE, AFK_CHANNEL_UPLOAD_UPGRADE);
		if (pDvrChannel)
		{
			pDvrChannel->OnRespond((unsigned char*)pBuf, nLen);
		}
	}

	// ���������ļ�
	else if (0xF3 == (unsigned char)*pBuf && 0x03 == (unsigned char)*(pBuf + 8))
	{
		pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_UPGRADE, AFK_CHANNEL_UPLOAD_CONFIGFILE);
		if (pDvrChannel)
		{
			pDvrChannel->OnRespond((unsigned char*)pBuf, nLen);
		}
	}

	// ��ȡͨ�������ʽ�ͷֱ��ʵ����뷵�� Added by Linjy-2006-11-7
	else if (0x83 == (unsigned char)*pBuf)
	{
		pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_SEARCH, AFK_CHANNEL_SEARCH_CONFIG, CONFIG_TYPE_DSP_MASK);
		if (pDvrChannel)
		{
			pDvrChannel->OnRespond((unsigned char*)pBuf, nLen);
		}
	}

	else if (0xC1 == (unsigned char)*pBuf && 0xF7 != (unsigned char)*(pBuf+16)) 
	{
		// ���ACK��Ϣ����Ҫ�豸����������һ���¼�������
		if (0x01 == (unsigned char)*(pBuf+9))
		{
			fDeviceEventCallBack cbDevEvent = device->GetDevEventFunc();
			void* userdata = device->GetDisconnectUserdata();
			
			if (cbDevEvent != NULL)
			{
				cbDevEvent((afk_device_s*)device, EVENT_CONFIG_REBOOT, NULL, userdata);
			}
		}
		
		if((BYTE)*(pBuf+16) == 242)//�豸���÷����ı�
		{
			fDeviceEventCallBack cbDevEvent = device->GetDevEventFunc();
			void* userdata = device->GetDisconnectUserdata();

			if (cbDevEvent != NULL)
			{
				cbDevEvent((afk_device_s*)device, EVENT_CONFIG_CHANGE, NULL, userdata);
			}
		}
		else
		{
			// �ص����÷�����
			CONFIG_ACK_INFO stuAckInfo = {0};
			stuAckInfo.type = *(pBuf+16);		// �޸Ĳ������
			stuAckInfo.nResultCode = *(pBuf+8);	// ������
			stuAckInfo.bReboot = *(pBuf+9);		// ������־

			fDeviceEventCallBack cbDevEvent = device->GetDevEventFunc();
			void* userdata = device->GetDisconnectUserdata();
			
			if (cbDevEvent != NULL)
			{
				cbDevEvent((afk_device_s*)device, EVENT_CONFIG_ACK, &stuAckInfo, userdata);
			}
		}

		pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_CONFIG, 0);
		if (pDvrChannel)
		{
			pDvrChannel->OnRespond((unsigned char*)pBuf, nLen);
		}
	}

	// ���ACK��Ϣ�����豸����������Խ�������һ���¼�������
	else if (0x1E == (unsigned char)*pBuf)
	{
		//�����Խ� 2��ʼ 3����
		fDeviceEventCallBack cbDevEvent = device->GetDevEventFunc();
		void* userdata = device->GetDisconnectUserdata();
		
		if (cbDevEvent != NULL)
		{
			if (2 == (unsigned char)*(pBuf+8))
			{
				cbDevEvent((afk_device_s*)device, EVENT_TALK_START, NULL, userdata);
			}
			else if (3 == (unsigned char)*(pBuf+8))
			{
				cbDevEvent((afk_device_s*)device, EVENT_TALK_STOP, NULL, userdata);
			}
		}
	}

	else if (0x1A == (unsigned char)*pBuf || 0x1B == (unsigned char)*pBuf)
	{
		pDvrChannel = device->device_get_channel(AFK_CHANNEL_TYPE_CONTROL, 0);
		if (pDvrChannel)
		{
			pDvrChannel->OnRespond((unsigned char*)pBuf, nLen);
		}
	}

	else if (0xf1 == (unsigned char)*pBuf)
	{
		//������ע�᷵�ء��ݲ�����
	}

	// �ַ���Э��
	else if ((0xC1 == (unsigned char)*pBuf || 0xB3 == (unsigned char)*pBuf) && 0xF7 == (unsigned char)*(pBuf+16) && nLen > HEADER_SIZE)
	{
		int nRequestType = 0;
		int nPacketSequence = 0;

		pBuf[nLen-1] = '\0';
		pBuf[nLen-2] = '\0';

		char szValue[64] = {0};
		char *p = GetProtocolValue((char*)(pBuf+HEADER_SIZE), "ProtocolType:", "\r\n", szValue, 64);
		if (p)
		{
			if (_stricmp(szValue, "CfgTVCombin") == 0 && 0xC1 == (unsigned char)*pBuf)
			{
				nRequestType = AFK_REQUEST_DECODER_CTRLTV;
			}
			else if (_stricmp(szValue, "CfgDigitalChn") == 0 && 0xC1 == (unsigned char)*pBuf)
			{
				nRequestType = AFK_REQUEST_DECODER_SWITCH;
			}
			else if (_stricmp(szValue, "CfgTVCombin") == 0 && 0xB3 == (unsigned char)*pBuf)
			{
				nRequestType = AFK_REQUEST_DEC_QUERY_TV;
			}
			else if (_stricmp(szValue, "CfgDigitalChn") == 0 && 0xB3 == (unsigned char)*pBuf)
			{
				nRequestType = AFK_REQUEST_DEC_QUERY_CHANNEL;
			}
		}

		p = GetProtocolValue((char*)(pBuf+HEADER_SIZE), "PacketSequence:", "\r\n", szValue, 64);
		if (p)
		{
			nPacketSequence = atoi(szValue);
		}
	
		pDvrChannel = device->device_get_channel(AFX_CHANNEL_TYPE_REQUEST, nRequestType, nPacketSequence);
		if (pDvrChannel)
		{
			pDvrChannel->channel_set_info(channel_protocoltype, &nRequestType);
			pDvrChannel->channel_set_info(channel_packetsequence, &nPacketSequence);
			pDvrChannel->OnRespond((unsigned char*)pBuf, nLen);
		}
	}
	else if (0xF4 == (unsigned char)*pBuf)
	{
		int nRequestType = 0;
		int nPacketSequence = 0;

		pBuf[nLen-1] = '\0';
		pBuf[nLen-2] = '\0';

		char szValue[64] = {0};
		char *p = GetProtocolValue((char*)(pBuf+HEADER_SIZE), "ParameterName:", "\r\n", szValue, 64);
		if (p)
		{
			char szMethod[64] = {0};
			p = GetProtocolValue((char*)(pBuf+HEADER_SIZE), "Method:", "\r\n", szMethod, 64);
			if (p)
			{
				if (_stricmp(szValue, "Dahua.Device.VideoOut.TV.CfgTv") == 0)
				{
					if (_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_DEC_QUERY_SYS;
					}
				}
				else if (_stricmp(szValue, "Dahua.Device.Decode.Cfg") == 0)
				{
					if (_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_DEC_QUERY_CHNNUM;
					}
				}
				else if (_stricmp(szValue, "Dahua.Device.VideoOut.TV.MultiCombin") == 0)
				{
					if (_stricmp(szMethod, "AddObjectResponse") == 0)
					{
						nRequestType = AFK_REQUEST_DEC_ADD_COMBIN;
					}
					else if (_stricmp(szMethod, "DeleteObjectResponse") == 0)
					{
						nRequestType = AFK_REQUEST_DEC_DEL_COMBIN;
					}
					else if (_stricmp(szMethod, "SetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_DEC_SET_COMBIN;
					}
					else if (_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_DEC_QUERY_COMBIN;
					}
				}
				else if (_stricmp(szValue, "Dahua.Device.VideoOut.TV.Scout.CfgScout") == 0)
				{
					if (_stricmp(szMethod, "SetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_DEC_SET_TOUR;
					}
					else if (_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_DEC_QUERY_TOUR;
					}
				}
				else if (_stricmp(szValue, "Dahua.Device.VideoOut.TV.CfgTv") == 0)
				{
					if (_stricmp(szMethod, "SetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_DEC_SET_TV_ENABLE;
					}
				}
				else if (_stricmp(szValue, "Dahua.Device.Decode.ControlPlayback.Start") == 0)
				{
					if (_stricmp(szMethod, "SetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_DEC_PLAYBACKBYDEC;
					}
				}
				else if (_stricmp(szValue, "Dahua.Device.Decode.ControlPlayback.Progress") == 0)
				{
					if (_stricmp(szMethod, "Inform") == 0)
					{
						NVD_PLAYBACK_EVENT stuAckInfo = {0};

						p = GetProtocolValue((char*)(pBuf+HEADER_SIZE), "DisChn:", "\r\n", szValue, 64);
						if (p)
						{
							stuAckInfo.nEncoderNum = atoi(szValue);
						}
						
						p = GetProtocolValue((char*)(pBuf+HEADER_SIZE), "RecTotalLength:", "\r\n", szValue, 64);
						if (p)
						{
							stuAckInfo.nTotalSize = atoi(szValue);
						}
							
						p = GetProtocolValue((char*)(pBuf+HEADER_SIZE), "CurrentLength:", "\r\n", szValue, 64);
						if (p)
						{
							stuAckInfo.nCurSize = atoi(szValue);
						}

						fDeviceEventCallBack cbDevEvent = device->GetDevEventFunc();
						void* userdata = device->GetDisconnectUserdata();
						if (cbDevEvent != NULL)
						{
							cbDevEvent((afk_device_s*)device, EVENT_NVD_PLAYBACK, &stuAckInfo, userdata);
						}
					}
				}
				else if (_stricmp(szValue, "Dahua.Device.Decode.ControlPlayback.Resume") == 0)
				{
					if (_stricmp(szMethod, "SetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_DEC_CTRLPLAYBACK;
					}
				}
				else if (_stricmp(szValue, "Dahua.Device.Decode.ControlPlayback.Pause") == 0)
				{
					if (_stricmp(szMethod, "SetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_DEC_CTRLPLAYBACK;
					}
				}
				else if (_stricmp(szValue, "Dahua.Device.Decode.ControlPlayback.Stop") == 0)
				{
					if (_stricmp(szMethod, "SetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_DEC_CTRLPLAYBACK;
					}
				}
				else if (_stricmp(szValue, "Dahua.Device.Network.IPFilter") == 0) //ip����
				{
					if (_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_GET_IPFILTER;
					}
					else if (_stricmp(szMethod, "SetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_SET_IPFILTER;
					}
					else if (_stricmp(szMethod, "AddObjectResponse") == 0)
					{
						nRequestType = AFK_REQUEST_ADD_IPFILTER;
					}
					else if (_stricmp(szMethod, "DeleteObjectResponse") == 0)
					{
						nRequestType = AFK_REQUEST_DEL_IPFILTER;
					}
				}
				else if (_stricmp(szValue, "Dahua.Device.Audio.Talkback.Cfg") == 0)//������������
				{
					if (_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_GET_AMRENCODE_CFG;
					}
					else if (_stricmp(szMethod, "SetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_SET_AMRENCODE_CFG;
					}
				}
				else if (_stricmp(szValue, "Dahua.Device.Record.General.RecordLen") == 0)//¼�񳤶�����
				{
					if (_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_GET_RECORDLEN_CFG;
					}
					else if (_stricmp(szMethod, "SetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_SET_RECORDLEN_CFG;
					}
				}
				else if (_stricmp(szValue, "Dahua.Device.VideoOut.General") == 0)//��Ƶ��ʽ
				{
					if (_stricmp(szMethod, "GetParameterNamesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_GET_VIDEOFORMAT_INFO;
					}
					else if (_stricmp(szMethod, "SetParameterNamesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_SET_VIDEOOUT;
					}
				}
				else if (_stricmp(szValue, "Dahua.Device.Network.Mobile.EventMessageSending.Cfg") == 0)//MMS����
				{
					if (_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_GET_MMS_INFO;
					}
					else if (_stricmp(szMethod, "SetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_SET_MMS_INFO;
					}
				}
				else if (_stricmp(szValue, "Dahua.Device.Network.Mobile.SMSActivation.Cfg") == 0)//SMSACTIVATION����
				{
					if (_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_GET_SMSACTIVE_INFO;
					}
					else if (_stricmp(szMethod, "SetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_SET_SMSACTIVE_INFO;
					}
				}
				else if (_stricmp(szValue, "Dahua.Device.Network.Mobile.DialInActivation.Cfg") == 0)//DIALINACTIVATION����
				{
					if (_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_GET_DIALIN_INFO;
					}
					else if (_stricmp(szMethod, "SetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_SET_DIALIN_INFO;
					}
				}
				else if (_stricmp(szValue, "Dahua.Device.Record.Backup.Extra") == 0)//˾����¼
				{
					if( _stricmp(szMethod, "SetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_SET_BURNFILE_TRANS;
					}
					else if( _stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_GET_BURNFILE_TRANS;
					}
				}
				else if(_stricmp(szValue, "Dahua.Device.Network.ControlConnection.Passive") == 0)
				{
					if( _stricmp(szMethod, "AddObjectResponse") == 0)
					{
						nRequestType = AFK_REQUEST_CONNECT;
					}
					else if( _stricmp(szMethod, "DeleteObjectResponse") == 0)
					{
						nRequestType = AFK_REQUEST_DISCONNECT;
					}
				}
				else if(_stricmp(szValue, "Dahua.Device.Network.ControlConnection.Port") == 0)
				{
					if( _stricmp(szMethod, "AddObjectResponse") == 0)
					{
						nRequestType = AFK_REQUEST_AUTOREGISTER_CONNECT;
					}
					else if( _stricmp(szMethod, "DeleteObjectResponse") == 0)
					{
						nRequestType = AFK_REQUEST_AUTOREGISTER_DISCONNECT;
					}
					else if ( _stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_AUTOREGISTER_GETSERVER;
					}
				}
				else if (_stricmp(szValue, "Dahua.Device.Network.CtrolRegister.Choose") == 0)//����ע��
				{
					if (_stricmp(szMethod, "SetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_AUTOREGISTER_REGSERVER;
					}
					if (_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_AUTOREGISTER_GETCONID;
					}
				}
				else if(_stricmp(szValue, "Dahua.Device.Record.Backup.Extra.Option") == 0)
				{
					if(_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_GET_BURN_ATTACH;
					}
					else if(_stricmp(szMethod, "SetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_SET_BURN_ATTACH;
					}
				}
				else if(_stricmp(szValue, "Dahua.Device.Network.Sniffer.Cfg.Group") == 0)
				{
					if(_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_GET_SNIFFER;
					}
					else if(_stricmp(szMethod, "SetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_SET_SNIFFER;
					}
				}
				else if(_stricmp(szValue, "Dahua.Device.Network.Sniffer.Cfg.Group.Frame") == 0)
				{
					if(_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_GET_SNIFFER;
					}
					else if(_stricmp(szMethod, "SetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_SET_SNIFFER;
					}
				}
				else if(_stricmp(szValue, "Dahua.Device.Network.Sniffer.Cfg.Group.Frame.Content") == 0)
				{
					if(_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_GET_SNIFFER;
					}
					else if(_stricmp(szMethod, "SetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_SET_SNIFFER;
					}
				}
				else if(_stricmp(szValue, "Dahua.Device.NetWork.DownloadBitrate.Cfg") == 0)
				{
					if(_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_GET_DOWNLOAD_RATE;
					}
					else if(_stricmp(szMethod, "SetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_SET_DOWNLOAD_RATE;
					}
				}
				else if (_stricmp(szValue, "Dahua.Device.Decode.ChannelState") == 0)//����ͨ����״̬��Ϣ
				{
					if(_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_DEC_CHANNEL_STATE;
					}
				}
				else if(_stricmp(szValue, "Dahua.Device.Oem.JunYi.Intelligent.General") == 0)
				{
					if(_stricmp(szMethod, "GetParameterNamesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_GET_POINT_CFG;
					}
					else if(_stricmp(szMethod, "SetParameterNamesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_SET_POINT_CFG;
					}
				}
				else if(_stricmp(szValue, "Dahua.Device.Oem.WeiKeMu.Video.OSD") == 0)
				{
					if(_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_GET_OSDENABLE_CFG;
					}
					else if(_stricmp(szMethod, "SetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_SET_OSDENABLE_CFG;
					}
				}
				else if(_stricmp(szValue, "Dahua.Device.VideoOut.TV.Cfg.Adjust") == 0)
				{
					if(_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_GET_TVADJUST_CFG;
					}
					else if(_stricmp(szMethod, "SetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_SET_TVADJUST_CFG;
					}
				}
				else if(_stricmp(szValue, "Dahua.Device.Record.General") == 0)
				{
					if(_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_FUNCTION_MASK;
					}
				}
				else if(_stricmp(szValue, "Dahua.Device.OnVehicle.General") == 0)
				{
					if(_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{	
						nRequestType = AFK_REQUEST_GET_VEHICLE_CFG;
					}
					else if(_stricmp(szMethod, "SetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_SET_VEHICLE_CFG;
					}
				}
				else if(_stricmp(szValue, "Dahua.Device.ATM.Overlap.General") == 0)
				{
					if(_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_GET_ATM_OVERLAY_ABILITY;
					}
				}
				else if(_stricmp(szValue, "Dahua.Device.ATM.Overlap.Config") == 0)
				{
					if(_stricmp(szMethod, "SetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_SET_ATM_OVERLAY_CFG;
					}
					else if(_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_GET_ATM_OVERLAY_CFG;
					}
				}
				else if(_stricmp(szValue, "Dahua.Device.Record.Backup.General") == 0)
				{
					if(_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{	
						nRequestType = AFK_REQUEST_QUERY_BACKUP_DEV;
					}
				}
				else if(_stricmp(szValue, "Dahua.Device.Record.Backup.Device") == 0)
				{
					if(_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{	
						nRequestType = AFK_REQUEST_QUERY_BACKUP_DEV_INFO;
					}
				}
				else if(_stricmp(szValue, "Dahua.Device.Record.Backup.Control.Start") == 0)
				{
					if(_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{	
						nRequestType = AFK_REQUEST_BACKUP_START;
					}
				}
				else if(_stricmp(szValue, "Dahua.Device.Record.Backup.Control.Stop") == 0)
				{
					if(_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{	
						nRequestType = AFK_REQUEST_BACKUP_STOP;
					}
				}
				else if(_stricmp(szValue, "Dahua.Device.Record.Backup.Control.Progress") == 0)
				{
					if(_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{	
						nRequestType = AFK_REQUEST_BACKUP_FEEDBACK;
					}
				}
				else if(_stricmp(szValue, "Dahua.Device.ATM.General") == 0)
				{
					if(_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{	
						nRequestType = AFK_REQUEST_ATM_TRADE_TYPE;
					}
				}
				else if(_stricmp(szValue, "Dahua.Device.Decode.TourCfg") == 0)
				{
					if(_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_GET_DECODER_TOUR_CFG;
					}
					else if(_stricmp(szMethod, "SetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_SET_DECODER_TOUR_CFG;
					}
				}
				else if (_stricmp(szValue, "Dahua.Device.Decode.Control") == 0)
				{
					if (_stricmp(szMethod, "SetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_DEC_CONTROL;		
					}
				}
				else if(_stricmp(szValue, "Dahua.Device.StreamMedia.Info") == 0)
				{
					if(_stricmp(szMethod, "GetParameterNamesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_GET_SIP_ABILITY;
					}
				}
				else if(_stricmp(szValue, "Dahua.Device.StreamMedia.SIP.Cfg") == 0)
				{
					if(_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_GET_SIP_CFG;
					}
					else if(_stricmp(szMethod, "SetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_SET_SIP_CFG;
					}
				}
				else if(_stricmp(szValue, "Dahua.Device.StreamMedia.SIP.State") == 0)
				{
					if(_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_GET_SIP_STATE;
					}
				} //jfchen 
				else if ( _stricmp( szValue , "ZenoIntel.Device.OnPos.Pos.Cfg" ) == 0 )
				{
					if(_stricmp(szMethod, "GetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_GET_POS_CFG;
					}
					else if(_stricmp(szMethod, "SetParameterValuesResponse") == 0)
					{
						nRequestType = AFK_REQUEST_SET_POS_CFG;
					}
				}
			}
		}

		p = GetProtocolValue((char*)(pBuf+HEADER_SIZE), "TransactionID:", "\r\n", szValue, 64);
		if (p)
		{
			nPacketSequence = atoi(szValue);
		}
	
		pDvrChannel = device->device_get_channel(AFX_CHANNEL_TYPE_REQUEST, nRequestType, nPacketSequence);
		if (pDvrChannel)
		{
			pDvrChannel->channel_set_info(channel_protocoltype, &nRequestType);
			pDvrChannel->channel_set_info(channel_packetsequence, &nPacketSequence);
			pDvrChannel->OnRespond((unsigned char*)pBuf, nLen);
		}
	}
	else if (0xf5 == (unsigned char)*pBuf)
	{
		int nPacketSequence = 0;
		nPacketSequence = *(int*)(pBuf+8);
		pDvrChannel = device->device_get_channel(AFX_CHANNEL_TYPE_NEWCONFIG, 0, nPacketSequence);
		if (pDvrChannel)
		{
			pDvrChannel->OnRespond((unsigned char*)pBuf, nLen);
		}
	}
	else
	{
#ifdef _DEBUG
	//	printf("Error:������:(%x )û�ж���-->OnOtherPacket\n",pBuf[0]);
#endif
	}
	
	}
    catch (...)
    {
#ifdef _DEBUG
		OutputDebugString("Error:������������쳣-->OnOtherPacket\n");
#endif
	return -1;
	}
	
	if (pDvrChannel)
	{
		pDvrChannel->channel_decRef();
	}

	return 1;
}


/*
 * ժҪ����������������ͳ��
 */
int __stdcall OnReceivePacket(unsigned char *pBuf, int nLen, void *userdata)
{
    CDvrDevice *pDvrDevice = (CDvrDevice*)userdata;
	if (pDvrDevice == NULL) 
	{
		return -1; 
	}

    pDvrDevice->statiscing(nLen);

	return 1;
}


/*
 * ժҪ�������Ӷ���
 */
int __stdcall OnDisconnect(void *userdata)
{
    CDvrDevice *pDvrDevice = (CDvrDevice*)userdata;
	if (pDvrDevice != NULL) 
	{
		int nIsHaveTask = 0;
		pDvrDevice->set_info(pDvrDevice, dit_device_task, &nIsHaveTask);

		fDisconnectCallBack pfDisconnectFunc = pDvrDevice->GetDisconnectFunc();
		void* userdata = pDvrDevice->GetDisconnectUserdata();
		if (pfDisconnectFunc != NULL)
		{
			pfDisconnectFunc((afk_device_s*)pDvrDevice, NULL, FALSE, pDvrDevice->GetIp(), pDvrDevice->GetPort(), 0, userdata);
		}
	}
	
	return 1;
}


/*
 * ժҪ�������Ӷ��߻ָ�
 */
int	__stdcall OnReConnect(void *userdata)
{
	CDvrDevice *pDvrDevice = (CDvrDevice*)userdata;
	if (pDvrDevice != NULL) 
	{
		int nIsHaveTask = 1;
		pDvrDevice->set_info(pDvrDevice, dit_device_task, &nIsHaveTask);
	}

	return 1;
}


/*
 * ժҪ�������ӽ������ݴ���
 */
int __stdcall OnSubOtherPacket(unsigned char *pBuf, int nLen, void *userdata)
{
	CDvrChannel *pDvrChannel = (CDvrChannel*)userdata;
	if (nLen < HEADER_SIZE || pDvrChannel == NULL)
    {
        return -1;
    }

    if (0xB1 != (unsigned char)*pBuf)
    {
		pDvrChannel->OnRespond((unsigned char*)pBuf, nLen);

		if (0xBB == (unsigned char)*pBuf)
		{
			// ��������
            if (*(unsigned int*)(pBuf + 15) == 0x12 ||
                *(unsigned int*)(pBuf + 4) == 0x00)
            {
#ifdef _DEBUG
				OutputDebugString("DVR: DOWNLOAD END!\n");
#endif
                pDvrChannel->OnRespond(0, -1);
            }
		}
    }

	return 1;
}


/*
 * ժҪ����������������ͳ��
 */
int __stdcall OnSubReceivePacket(unsigned char *pBuf, int nLen, void *userdata)
{
	CDvrChannel *pDvrChannel = (CDvrChannel*)userdata;
	if (nLen < HEADER_SIZE || pDvrChannel == NULL)
    {
        return -1;
    }

	CDvrDevice *pDvrDevice = pDvrChannel->channel_getdevice();
	if (pDvrDevice == NULL) 
	{
		return -1; 
	}

    pDvrDevice->statiscing(nLen);

	return 1;
}


/*
 * ժҪ�������Ӷ���
 */
int __stdcall OnSubDisconnect(void *userdata)
{
	CDvrChannel *pDvrChannel = (CDvrChannel*)userdata;
	if (pDvrChannel == NULL)
    {
        return -1;
    }

	CDvrDevice *pDvrDevice = pDvrChannel->channel_getdevice();
	if (pDvrDevice == NULL) 
	{
		return -1; 
	}

	if (pDvrDevice != NULL) 
	{
		int nIsHaveTask = 0;
		pDvrDevice->set_info(pDvrDevice, dit_device_task, &nIsHaveTask);

		fDisconnectCallBack pfDisconnectFunc = pDvrDevice->GetDisconnectFunc();
		void* userdata = pDvrDevice->GetDisconnectUserdata();
		if (pfDisconnectFunc != NULL)
		{
			pfDisconnectFunc((afk_device_s*)pDvrDevice, pDvrChannel, FALSE, pDvrDevice->GetIp(), pDvrDevice->GetPort(), pDvrChannel->GetChannelType(), userdata);
		}
	}
	
	return 1;
}


/*
 * ժҪ�������Ӷ��߻ָ�
 */
int	__stdcall OnSubReConnect(void *userdata)
{
// 	CDvrChannel *pDvrChannel = (CDvrChannel*)userdata;
// 	if (pDvrChannel == NULL)
//     {
//         return -1;
//     }
// 
// 	CDvrDevice *pDvrDevice = pDvrChannel->channel_getdevice();
// 	if (pDvrDevice == NULL) 
// 	{
// 		return -1; 
// 	}
// 	
// 	if (pDvrDevice != NULL) 
// 	{
// 		int nIsHaveTask = 1;
// 		pDvrDevice->set_info(pDvrDevice, dit_device_task, &nIsHaveTask);
// 	}

	return 1;
}






























