
#ifndef _AFKPLUGIN_H_
#define _AFKPLUGIN_H_

#include "afkinc.h"


/**************************************************************************** 
 * ������Ͷ���
 * SDK���ò�����, �ܶ�ʵ�־����ڲ�������
 ****************************************************************************/
#define AFK_PLUGIN_DEVICEPROBE		1		/* �豸̽���� */
#define AFK_PLUGIN_STREAM_PARSER	2		/* �������� */
#define AFK_PLUGIN_VIDEO_DECODER	4		/* ��Ƶ���� */
#define AFK_PLUGIN_AUDIO_DECODER	5		/* ��Ƶ���� */

/****************************************************************************
 * �ýṹʵ����plugin�ṩ.
 * type == AFK_PLUGIN_DEVICEPROBE: init()��������afk_device_prob_t*
 ****************************************************************************/
typedef struct afk_plugin_info_s afk_plugin_info_t;

struct afk_plugin_info_s{
	unsigned short	type;						/* ������� */
	unsigned short	API;						/* ֧�ֵĺ��İ汾 */
	int				priority;					/* ���ȼ� */
	char			*id;						/* ID */
	unsigned long	version;					/* �Զ����ӵ�Plugin�汾�� */
	void			*special_info;				/* plugin �Զ������� */
	void			*(*init)(void *);			/* ��ʼ������ */
};

typedef struct afk_device_prob_s afk_device_prob_t;

/****************************************************************************
 * �豸̽�������
 * ����������ӳɹ�,����Ϊһ��afk_device_s���͵ı���
 ****************************************************************************/
typedef void (__stdcall *fDisconnectCallBack)(void *device, void *channel, int nOnline, char *szIp, int nPort, int nInterfaceType, void *userdata);
typedef void (__stdcall *fDeviceEventCallBack)(void *device, int nEventType, void *pEventInfo, void *userdata);

typedef void (__stdcall *fListenCallback)(void* pServerHandle, char *szClientIp, int nClientPort, int nCommand, void *pParam, void *userdata);
typedef int  (__stdcall *fEventCallBack)(LONG lHandle, int connId, char *szIp, WORD wPort, LONG lCommand, void *pParam, DWORD dwParamLen, DWORD dwUserData);


struct afk_device_prob_s
{
	void* (*try_connect)(const char *szIp, int nPort, const char *szUser, const char *szPassword, int nSpecCap, void* pCapParam, 
						fDisconnectCallBack cbDisconnect, fDeviceEventCallBack cbDevEvent, void *userdata, 
						int *pErrorCode, int nTimeout, int nTryTime, BOOL bIsReConn, int nConnHostTime, int nSubConnSpaceTime, int nConnBufLen);

	void* (*start_listen)(char *szIp, int nPort, fListenCallback cbListen, void *userdata, int nConnBufLen);
	BOOL  (*stop_listen)(void *pListenHandle);
	BOOL  (*close_client)(void *pClientHandle);
	BOOL  (*response_reg)(void *pClientHandle, BOOL bAccept);

	BOOL  (*net_startup)(void);
	BOOL  (*net_cleanup)(void);

	LONG  (*start_alarm_server)(char *szIp, int nPort, fEventCallBack RecAlarmCallBack, unsigned long user_data);
	BOOL  (*stop_alarm_server)(LONG lHandler);
	int   (*server_heart_beat)(LONG lHandler);

	LONG  (*start_search_device)(afk_callback cbReceived, void *userdata);
	int   (*stop_search_device)(LONG lHandle);

	LONG  (*new_tcp_socket)(char *szIp, int nPort, int nWaitTime);
	int   (*delete_tcp_socket)(LONG lHandle);
	int   (*write_data)(LONG lHandle, char *pBuf, int nBufLen);
};

#endif // _AFKPLUGIN_H_

