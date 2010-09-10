///////////////////////////////////////////////////////////////////////////////////////////
// �ļ���: dvrpacket_mobile.cpp
// ������: jinyx
// ����ʱ��: 2007-4-2
//           2007-4-11 ����GPS��������
// ��������: mobile dvr��packet
///////////////////////////////////////////////////////////////////////////////////////////
#include "../Net/TcpSocket.h"
#include "dvrpacket_mobile.h"
#include "dvrdevice.h"
#include "../def.h"
#include "../kernel/afkinc.h"

/****************************************************************************/

/*****************ץͼ�ṹ��******************/
//	����DVRץͼ�ṹ��
typedef struct _snap_param
{
   int Channel;        //ץͼ��ͨ��
   int Quality;       //����1~6
   int ImageSize;     //�����С 0:QCIF,1:CIF,2:D1
   int mode;       //ץͼģʽ 0����ʾ����һ֡,1����ʾ��ʱ��������,2����ʾ��������
   int InterSnap;     //ʱ�䵥λ�� ��mode=1��ʾ��ʱ��������ʱ����Ϊ�����豸����ʱ����Ч��
   int CmdSerial;    //�������к�
   int Reserved[4];
}SNAP_PARAMS_IN,*LPSNAP_PARAMS_IN;

//	��ͨDVRץͼ�ṹ��
typedef struct _snap_param_new
{
   int Channel;        //ץͼ��ͨ��
   int res[2];       
   int mode;       //ץͼģʽ 0����ʾ����һ֡,1����ʾ��ʱ��������
   int res1;     
   int CmdSerial;    //�������к�
   BYTE  Opr;// 0: stop 1:start
   BYTE  Res[3];
   int Reserved[3];
}SNAP_PARAMS_NEW,*LPSNAP_PARAMS_NEW;


/****************************************************************************/

//ץͼ
bool sendSnap_mobile(CDvrDevice* device, void* snapParam, unsigned char type)
{
	bool bRet = false;

	if (0 == type)		//���ص�
	{
		LPSNAP_PARAMS_IN par = (LPSNAP_PARAMS_IN)snapParam;
		int len = sizeof(*par);
		char *pbuf = new char[HEADER_SIZE + len];
		memset(pbuf, 0, HEADER_SIZE + len);
		
		*pbuf = 0x11;                          //ץͼ������
		
		if(par->mode!=-1)
		{
			*(pbuf+8+par->Channel) = 1;            //��Ӧͨ����1
		}
		else
		{
			*(pbuf+8+par->Channel) = 0;           //mode = -1 ��ʾֹͣ��Ӧͨ���ļ��ӷ���
		}
		
		*(pbuf + 28) = 10;                     //ץͼʶ��
		
		*(unsigned int*)(pbuf + 4) = len;      //��չ���ݰ�����
		
		memcpy(pbuf + HEADER_SIZE,par,len);    //��չ��дץͼ����
		
		CTcpSocket *tcp = device->GetTcpSocket();
		if (tcp)
		{
			if (tcp->WriteData(pbuf, HEADER_SIZE + len) >= 0)
			{
				bRet = true;
			}
		}

		delete[] pbuf;
	}
	else		//��ͨDVR
	{
		LPSNAP_PARAMS_IN lpSnapParam = (LPSNAP_PARAMS_IN)snapParam;
		SNAP_PARAMS_NEW NewSnapParam = {0};

		int nLen = sizeof(SNAP_PARAMS_NEW);
		char *pBuf = new char[HEADER_SIZE + nLen];
		memset(pBuf, 0, HEADER_SIZE + nLen);

		NewSnapParam.Channel = lpSnapParam->Channel;
		NewSnapParam.CmdSerial = lpSnapParam->CmdSerial;
		NewSnapParam.mode = lpSnapParam->mode;

		if (lpSnapParam->mode == -1)
		{
			NewSnapParam.Opr = 0;
		}
		else
		{
			NewSnapParam.Opr = 1;
		}

		pBuf[0] = 0x11;
		pBuf[28] = 10;
		*(unsigned int*)(pBuf + 4) = nLen;
		memcpy(pBuf + HEADER_SIZE, &NewSnapParam, nLen);

		CTcpSocket *tcp = device->GetTcpSocket();
		if (tcp)
		{
			if (tcp->WriteData(pBuf, HEADER_SIZE + nLen) >= 0)
			{
				bRet = true;
			}
		}

		delete[] pBuf;
	}
  
    return bRet;	
}

//GPS����
bool sendGpsAlarm_mobile(CDvrDevice* device,void* gpsParam)
{
    afk_gps_channel_param_s* parm = (afk_gps_channel_param_s*) gpsParam;

    unsigned char data[HEADER_SIZE];
	memset(data, 0, HEADER_SIZE);

	data[0] = 0x68;
    data[8] = parm->active==0 ? 3 : 2;
	data[12] = 155;
	*(unsigned long *)(data+24) = parm->InterlTime;
	*(unsigned long *)(data+28) = parm->keeptime;

    CTcpSocket *tcp = device->GetTcpSocket();
    if (tcp)
    {
        if (tcp->WriteData((char*)data, HEADER_SIZE) >= 0)
        {
            return true;
        }
    }
    return false;
}


