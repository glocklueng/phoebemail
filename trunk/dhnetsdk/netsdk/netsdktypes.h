/*
* Copyright (c) 2009, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* ժ��Ҫ�����ڲ�ʹ�õĽṹ����
*
*/
//////////////////////////////////////////////////////////////////////

#ifndef _NETSDKTYPES_H_
#define _NETSDKTYPES_H_


// ��������Ϣ
typedef struct __AFK_LAST_ERROR
{
#ifdef WIN32
	DWORD			dwThreadID;
#else	//linux
	pthread_t		dwThreadID;
#endif
	DWORD			dwError;
} AFK_LAST_ERROR;

// ���Ӷ�����Ϣ
typedef struct __AFK_DISCONN_INFO 
{
	char			szIp[32];
	int				nPort;
	afk_device_s*	device;
	afk_channel_s*	channel;
	BOOL			bOnline;
	EM_INTERFACE_TYPE emInterfaceType;
} AFK_DISCONN_INFO;

// ������Ϣ
typedef struct __AFK_ALARM_DATA
{
	char			szIp[32];
	int				nPort;
	afk_device_s*	device;
	DWORD			dwAlarmType;
	void*			data;
	int				datalen;
} AFK_ALARM_DATA;

// DDNS�����ṹ
typedef struct  __AFK_DDNS_DOMAIN
{
	char			dvr_webname[64];
	char			dvr_MacAddr[64];
	char			dvr_Ip[32];
	unsigned short	dvr_Port;
	char			reserved[2];
} AFK_DDNS_DOMAIN;

// �������ͻ�����Ϣ
typedef struct __AFK_CLIENT_NODE
{
	char			serial[DEV_SERIAL_NUM_LEN];
	char			ip[MAX_IP_ADDRESS_LEN];
	void*			clnHandle;
	int				status; //0-δ�ϴ����кţ�1�����ϴ����к�
	WORD			port;
} AFK_CLIENT_NODE;

// ����-��������Ϣ
typedef struct __AFK_LISTER_DATA
{
	void*			lsnHandle;
	fServiceCallBack pCb;
	DWORD			lsnUser;
	list<AFK_CLIENT_NODE*> lstClients;
} AFK_LISTER_DATA;

// �豸����ע����Ϣ
typedef struct __AFK_CLIENT_REGISTER_INFO
{
	char			serial[DEV_SERIAL_NUM_LEN];
	char			ip[MAX_IP_ADDRESS_LEN];
	void*			caller;
	WORD			port;
} AFK_CLIENT_REGISTER_INFO;

// �ͻ������Ӷ�����Ϣ
typedef struct __AFK_CLIENT_DISCONN_INFO
{
	char			ip[MAX_IP_ADDRESS_LEN];
	void*			caller;
	void*			clnHandle;
	WORD			port;
} AFK_CLIENT_DISCONN_INFO;

// �첽�ص���Ϣ
typedef struct __AFK_RESPONSE_DATA
{
	LONG			lCommand;
	LPNET_CALLBACK_DATA lpCallBackData;
	fMessDataCallBack cbMessFunc;
	DWORD			dwUserdata;
} AFK_RESPONSE_DATA;

// �������طŽ�����Ϣ
typedef struct __AFK_NVD_PLAYBACK 
{
	afk_device_s*	device;
	int				nEncoderNum;
	DWORD			dwTotalSize;
	DWORD			dwCurSize;
	fDecPlayBackPosCallBack cbPlayBackPos;
	DWORD			dwUser;
} AFK_NVD_PLAYBACK;



// Ŀǰ��receivedata_s�����Ծ�̬��ʽʹ�ã�������������
class receivedata_s
{
public:
	receivedata_s() 
	{
		CreateEventEx(hRecEvt, TRUE, FALSE);
		data = NULL;
		maxlen = 0;
		datalen = NULL;
		result = 0;
//		llifecount = 1;
		memset(reserved, 0, sizeof(long)*4);
	}
	~receivedata_s() 
	{
		CloseEventEx(hRecEvt);
//		InterlockedDecrement(&llifecount);
	}
	bool addRef()
	{
		bool bRet = true;
//		InterlockedIncrement(&llifecount);
//		
//		if (llifecount <= 1 || llifecount > 111)
//		{
//			InterlockedDecrement(&llifecount);
//			bRet = false;
//			goto END;
//		}
//END:
		return bRet;
	}
	bool decRef()
	{
		bool bRet = true;
//		if (llifecount <= 0 || llifecount > 10)
//		{
//			bRet = false;
//			goto END;
//		}
//		
//		if (InterlockedDecrement(&llifecount) <= 0)
//		{
//			//OutputDebugString("Deleting receive data myself\n");
//		}
//END:
		return bRet;
	}
    char   *data;
    int    maxlen;
    int    *datalen;
	OS_EVENT hRecEvt;
    int    result;
	long   reserved[4];
//	LONG   llifecount;
};


#endif // _NETSDKTYPES_H_


