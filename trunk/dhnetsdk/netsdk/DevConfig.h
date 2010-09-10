/*
* Copyright (c) 2009, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �����ƣ�������
* ժ��Ҫ�����ù���ģ�顣
*
*/
//////////////////////////////////////////////////////////////////////////

#ifndef _DEVCONFIG_H_
#define _DEVCONFIG_H_

#include "netsdk.h"
#include "assistant.h"

#define MAX_COMM_PROTO_NUM	32
#define CONFIG_ALARM_NUM	16
#define CONFIG_DETECT_NUM	16
#define CONFIG_RECORD_NUM	16
#define CONFIG_CAPTURE_NUM	16
#define CONFIG_PTZ_NUM		16
#define SETUP_SLEEP			0
#define QUERY_WAIT			500
#define CONFIG_ALARM_NUM_EX	32
#define CONFIG_CAPTURE_NUM_EX	32

#include "../dvr/dvrdevice/dvr2cfg.h"

#define Min(a,b) ((a)<(b)?(a):(b))
#define BITRHT(x,y) ((x)>>(y))

typedef struct
{
    fLogDataCallBack cbLogData;
    DWORD dwUser;
}QueryLogInfo; 

class CManager;


class CDevConfig  
{
public:
	CDevConfig(CManager *pManager);
	virtual ~CDevConfig();

public:
	
	/* ��ʼ�� */
	int		Init(void);

	/* ���� */
	int		Uninit(void);

	int		CloseChannelOfDevice(afk_device_s* device);


	/* ��ȡ�豸������Ϣ���ϵģ� */
	int		QueryConfig(LONG lLoginID, int nConfigType, int nParam,
                                   char *pConfigbuf, int maxlen, int *nConfigbuflen, 
								   int waittime);

	/* �����豸������Ϣ���ϵģ� */
	int		SetupConfig(LONG lLoginID, int nConfigType, int nParam, 
                                   char *pConfigbuf, int nConfigbuflen, int waittime);

	/* ��ȡͨ������ */
	int		QueryChannelName(LONG lLoginID, 
                                        char *pChannelName, int maxlen, int *nChannelCount, int waittime);

	/* �ص���ʽ��ѯ��־ */
	int		QueryLogCallback(LONG lLoginID, fLogDataCallBack cbLogData, DWORD dwUser);

	/* ͬ����ʽ��ѯ��־ */
	int		QueryLog(LONG lLoginID, char *pLogBuffer, int maxlen, int *nLogBufferlen, void* reserved, int waittime, int type = 0);
	
	/* ��ѯ¼�����״̬ */
	int		QueryRecordState(LONG lLoginID, char *pRSBuffer, int maxlen, 
                                        int *nRSBufferlen, int waittime);
	/* ����¼�����״̬ */
	int		SetupRecordState(LONG lLoginID, char *pRSBuffer, int nRSBufferlen);
	
	/* ��ѯ�豸ʱ�� */
	int		QueryDeviceTime(LONG lLoginID, LPNET_TIME pDeviceTime, int waittime);

	/* �����豸ʱ�� */
	int		SetupDeviceTime(LONG lLoginID, LPNET_TIME pDeviceTime);

	/* ��ѯ����Э���б����� */
	int		QueryComProtocol(LONG lLoginID, int nProtocolType, char *pProtocolBuffer, 
                               int maxlen, int *nProtocollen, int waittime,DWORD dwProtocolIndex =0);

	/* ��ѯ�豸��ϵͳ��Ϣ */
	int		QuerySystemInfo(LONG lLoginID, int nSystemType, 
                              char *pSysInfoBuffer, int maxlen, int *nSysInfolen, int waittime);

	/* ��ѯ�豸�û���Ϣ */
	int		QueryUserInfo(LONG lLoginID, USER_MANAGE_INFO *info, int waittime);
	int		QueryUserInfoEx(LONG lLoginID, USER_MANAGE_INFO_EX *info, int waittime);
	/* ��������ӡ��޸ġ�ɾ�����豸�û���Ϣ */
	int		OperateUserInfo(LONG lLoginID, int nOperateType, void *opParam, void *subParam, int waittime);
	int		OperateUserInfoEx(LONG lLoginID, int nOperateType, void *opParam, void *subParam, int waittime);
	/* ��ѯIO�˿ڣ��������롢����ȣ�ʹ��״̬ */
	int		QueryIOControlState(LONG lLoginID, IO_CTRL_TYPE emType, 
                                  void *pState, int maxlen, int *nIOCount, int waittime);

	/* ����IO�˿ڣ��������롢����ȣ�ʹ��״̬ */
	int		IOControl(LONG lLoginID, IO_CTRL_TYPE emType, void *pState, int maxlen, int waittime = 1000);

	/* ��ȡ�豸�Ĺ���״̬ */
	int		GetDEVWorkState(LONG lLoginID, LPNET_DEV_WORKSTATE lpWorkState, int waittime);

	/* �µĻ�ȡ�豸ϵͳ�������� */
	int		GetDevConfig(LONG lLoginID, DWORD dwCommand,LONG lChannel, LPVOID lpOutBuffer,DWORD dwOutBufferSize,LPDWORD lpBytesReturned,int waittime);
	/*  �������Ӻ��� */
	int		GetDevConfig_DevCfg(LONG lLoginID, DEV_SYSTEM_ATTR_CFG &stSAC, int waittime);
	int		GetDevConfig_NetCfg(LONG lLoginID, DEVICE_NET_CFG &stNC, int waittime);
	int		GetDevConfig_ChnCfg(LONG lLoginID, DEV_CHANNEL_CFG &stCHC, LONG lChannel, int waittime);
	int		GetDevConfig_AllChnCfg(const LONG lLoginID, DEV_CHANNEL_CFG *pstCHC, LONG lChnNum, int waittime);
	int		GetDevConfig_RecCfg(LONG lLoginID, DEV_RECORD_CFG &stREC, LONG lChannel, int waittime);
	int		GetDevConfig_RecCfgNew(LONG lLoginID, DEV_RECORD_CFG &stREC, LONG lChannel, int waittime);
	int		GetDevConfig_AllRecCfg(LONG lLoginID, DEV_RECORD_CFG *pstREC, LONG lChnNum, int waittime);
	int		GetDevConfig_AllRecCfgNew(LONG lLoginID, DEV_RECORD_CFG *pstREC, LONG lChnNum, int waittime);
	int		GetDevConfig_ComCfg(LONG lLoginID, DEV_COMM_CFG &stCMC, int waittime);
	int		GetDevConfig_PtzCfg(LONG lLoginID, PTZ_OPT_ATTR *stuPtzAttr,DWORD dwProtocolIndex,int waittime);
	int		GetDevConfig_AlmCfg(LONG lLoginID, DEV_ALARM_SCHEDULE &stAS, int waittime);
	int		GetDevConfig_Devtime(LONG lLoginID, NET_TIME &stNT, int waittime);
	int		GetDevConfig_PreviewCfg(LONG lLoginID, DEV_PREVIEW_CFG &stPVC, int waittime);
	int		GetDevConfig_AutoMtCfg(LONG lLoginID, DEV_AUTOMT_CFG &stAMT, int waittime);
	int		GetDevConfig_VdMtrxCfg(LONG lLoginID, DEV_VIDEO_MATRIX_CFG *pstMatrix, int waittime);
	int		GetDevConfig_MultiDdnsCfg(LONG lLoginID, DEV_MULTI_DDNS_CFG &stMD, int waittime);
	int		GetDevConfig_SnapCfg(LONG lLoginID, DEVICE_SNAP_CFG *pstSC, LONG lChnNum, int waittime);
	int		GetDevConfig_UrlCfg(LONG lLoginID, DEVWEB_URL_CFG &stUC, int waittime);
	int		GetDevConfig_FtpCfg(LONG lLoginID, DEVICE_FTP_PROTO_CFG &stFC, int waittime);
	int		GetDevConfig_InterVedioCfg(LONG lLoginID, char* pCfg, int cfgLen, LONG lPlatform, int waittime);
	int		GetDevConfig_AllChnCoverCfg(const LONG lLoginID, DEV_VIDEOCOVER_CFG *lpChnCoverCfg, LONG lChnNum, int waittime);
	int		GetDevConfig_ChnCoverCfg(LONG lLoginID, DEV_VIDEOCOVER_CFG &ChnCoverCfg, LONG lChannel, int waittime);
	int		GetDevConfig_TransStrategyCfg(LONG lLoginID, DEV_TRANSFER_STRATEGY_CFG &stTSC, int waittime);
	int		GetDevConfig_DownloadStrategyCfg(LONG lLoginID, DEV_DOWNLOAD_STRATEGY_CFG &stDSC, int waittime);
	int		GetDevConfig_AllWaterMakeCfg(LONG lLoginID, DEVICE_WATERMAKE_CFG *pstCHC, LONG lChnNum, int waittime);
	int		GetDevConfig_WaterMakeCfg(LONG lLoginID, DEVICE_WATERMAKE_CFG *pstCHC, LONG lChannel, int waittime);
	int		GetDevConfig_EthernetCfg(LONG lLoginID, CONFIG_ETHERNET *pEthernetInfo, int &nEthernetNum, int waittime);
	int		GetDevConfig_WLANCfg(LONG lLoginID, DEV_WLAN_INFO &stuWlanInfo, int waittime);
	int		GetDevConfig_WLANDevCfg(LONG lLoginID, DEV_WLAN_DEVICE_LIST *pWlanLst, int waittime);
	int		GetDevConfig_AutoRegisterCfg(LONG lLoginID, DEV_REGISTER_SERVER *pRegisterSev, int waittime);
	int		GetDevConfig_AllChnCmrCfg(LONG lLoginID, DEVICE_CAMERA_CFG *pstCHC, LONG lChnNum, int waittime);
	int		GetDevConfig_ChnCmrCfg(LONG lLoginID, DEVICE_CAMERA_CFG &stCHC, LONG lChannel, int waittime);
	int		GetDevConfig_InfraredCfg(LONG lLoginID, INFRARED_CFG* pInfraredAlarm, int waittime);
	int		GetDevConfig_SnifferCfg(LONG lLoginID, DEVICE_SNIFFER_CFG *pstSniffer, int waittime);
	int		GetDevConfig_MailCfg(LONG lLoginID, DEVICE_MAIL_CFG *pstMail, int waittime);
	int		GetDevConfig_EtherDHCPCfg(LONG lLoginID, CONFIG_ETHERNET *pEthernetInfo, int waittime);
	int		GetDevConfig_DNSCfg(LONG lLoginID, DEVICE_DNS_CFG *pstDNS, int waittime);
	int		GetDevConfig_NTPCfg(LONG lLoginID, DEVICE_NTP_CFG *pstNTP, int waittime);
	int		GetDevConfig_AudioDetectCfg(LONG lLoginID, AUDIO_DETECT_CFG* pAudioDetectAlarm, int waittime);
	int		GetDevConfig_StorageStateCfg(LONG lLoginID, STORAGE_STATION_CFG &stuStorageCHA, LONG lChannel, int waittime);
	int		GetDevConfig_AllStorageStateCfg(LONG lLoginID, STORAGE_STATION_CFG *pstStorageCHC, LONG lChnNum, int waittime);
	int		GetDevConfig_DSTCfg(LONG lLoginID, DEVICE_DST_CFG *pstDSTInfo, int waittime);
	int		GetDevConfig_AlarmCenterCfg(LONG lLoginID, ALARMCENTER_UP_CFG *pAlarmCenterCfg, int waittime);
	int		GetDevConfig_VideoOSDCfg(LONG lLoginID, DVR_VIDEO_OSD_CFG &pstVideoOSD, LONG lChannel, int waittime);
	int     GetDevConfig_AllVideoOSDCfg(LONG lLoginID, DVR_VIDEO_OSD_CFG *pstVideoOSD, LONG lChnNum, int waittime);
	int     GetDevConfig_GPRSCDMACfg(LONG lLoginID, DEVICE_CDMAGPRS_CFG* pstGPRSCDMAInfo, int waittime);

	int     GetDevConfig_PosCfg( LONG lLoginID , DEVICE_POS_INFO* pPosCfg , int waittime ) ;
	int     SetDevConfig_PosCfg( LONG lLoginID , DEVICE_POS_INFO* pPosCfg , int waittime ) ;


	/* �µ������豸ϵͳ�������� */
	int		SetDevConfig(LONG lLoginID, DWORD dwCommand,LONG lChannel, LPVOID lpInBuffer,DWORD dwInBufferSize,int waittime);
	/*  �������Ӻ��� */
	int		SetDevConfig_DevCfg(LONG lLoginID, DEV_SYSTEM_ATTR_CFG  *pstSAC, int waittime);
	int		SetDevConfig_NetCfg(LONG lLoginID, DEVICE_NET_CFG *pstNC, int waittime);
	int		SetDevConfig_ChnCfg(LONG lLoginID, DEV_CHANNEL_CFG *pstCHC, LONG lChannel, int waittime);
	int		SetDevConfig_AllChnCfg(LONG lLoginID, DEV_CHANNEL_CFG *pstCHC, LONG lChnNum, int waittime);
	int		SetDevConfig_RecCfg(LONG lLoginID, DEV_RECORD_CFG *pstREC, LONG lChannel, int waittime);
	int		SetDevConfig_RecCfgNew(LONG lLoginID, DEV_RECORD_CFG *stREC, LONG lChannel, int waittime);
	int		SetDevConfig_AllRecCfg(LONG lLoginID, DEV_RECORD_CFG *pstREC, int waittime);
	int		SetDevConfig_ComCfg(LONG lLoginID, DEV_COMM_CFG *pstCMC, int waittime);
	int		SetDevConfig_AlmCfg(LONG lLoginID, DEV_ALARM_SCHEDULE *pstAS, int waittime);
	int		SetDevConfig_Devtime(LONG lLoginID, NET_TIME *pstNT, int waittime);
	int		SetDevConfig_PreviewCfg(LONG lLoginID, DEV_PREVIEW_CFG *pstPVC, int waittime);
	int		SetDevConfig_AutoMtCfg(LONG lLoginID, DEV_AUTOMT_CFG *pstAMT, int waittime);
	int		SetDevConfig_VdMtrxCfg(LONG lLoginID, DEV_VIDEO_MATRIX_CFG *pstVM, int waittime);
	int		SetDevConfig_MultiDdnsCfg(LONG lLoginID, DEV_MULTI_DDNS_CFG *pstMD, int waittime);
	int		SetDevConfig_SnapCfg(LONG lLoginID, DEVICE_SNAP_CFG *pstSC, LONG lChnNum, int waittime);
	int		SetDevConfig_UrlCfg(LONG lLoginID, DEVWEB_URL_CFG *pstUC, int waittime);
	int		SetDevConfig_FtpCfg(LONG lLoginID, DEVICE_FTP_PROTO_CFG *pstFC, int waittime);
	int		SetDevConfig_InterVedioCfg(LONG lLoginID, char* pCfg, int cfgLen, LONG lPlatform, int waittime);
	int		SetDevConfig_ChnCoverCfg(LONG lLoginID, DEV_VIDEOCOVER_CFG *pChnCoverCfg, LONG lChannel, int waittime);
	int		SetDevConfig_TransStrategyCfg(LONG lLoginID, DEV_TRANSFER_STRATEGY_CFG *pTransStrategyCfg, int waittime);
	int		SetDevConfig_DownloadStrategyCfg(LONG lLoginID, DEV_DOWNLOAD_STRATEGY_CFG *pDownloadStrategyCfg, int waittime);
	int		SetDevConfig_AllWaterMakeCfg(LONG lLoginID, DEVICE_WATERMAKE_CFG *pstCHC, LONG lChnNum, int waittime);
	int		SetDevConfig_WaterMakeCfg(LONG lLoginID, DEVICE_WATERMAKE_CFG *pstCHC, LONG lChannel, int waittime);
	int		SetDevConfig_EthernetCfg(LONG lLoginID, CONFIG_ETHERNET *pEthernetInfo, int nEthernetNum, int waittime);
	int		SetDevConfig_WLANCfg(LONG lLoginID, DEV_WLAN_INFO *pWlanInfo, int waittime);
	int		SetDevConfig_WLANDevCfg(LONG lLoginID, DEV_WLAN_DEVICE *pWlanDevInfo, int waittime);
	int		SetDevConfig_AutoRegisterCfg(LONG lLoginID, DEV_REGISTER_SERVER *pRegiSevInfo, int waittime);
	int		SetDevConfig_ChnCmrCfg(LONG lLoginID, DEVICE_CAMERA_CFG *pstCHC, LONG lChannel, int waittime);
	int		SetDevConfig_InfraredCfg(LONG lLoginID, INFRARED_CFG *pInfrared, int waittime);
	int		SetDevConfig_SnifferCfg(LONG lLoginID, DEVICE_SNIFFER_CFG *pstSniffer, int waittime);
	int		SetDevConfig_EtherDHCPCfg(LONG lLoginID, CONFIG_ETHERNET *pEthernetInfo, int nEthernetNum, int waittime);
	int		SetDevConfig_DNSCfg(LONG lLoginID, DEVICE_DNS_CFG *pstDNS, int waittime);
	int		SetDevConfig_NTPCfg(LONG lLoginID, DEVICE_NTP_CFG *pstNTP, int waittime);
	int		SetDevConfig_AudioDetectCfg(LONG lLoginID, AUDIO_DETECT_CFG* pAudioDetectAlarm, int waittime);
	int		SetDevConfig_StorageStateCfg(LONG lLoginID, STORAGE_STATION_CFG *pstStorageCHC, LONG lChannel, int waittime);
	int		SetDevConfig_DSTCfg(LONG lLoginID, DEVICE_DST_CFG *pstDSTInfo, int waittime);
	int		SetDevConfig_AlarmCenterCfg(LONG lLoginID, ALARMCENTER_UP_CFG *pAlarmCenterCfg, int waittime);
	int		SetDevConfig_VideoOSDCfg(LONG lLoginID, DVR_VIDEO_OSD_CFG *pstVideoOSD, LONG lChannel, int waittime); 
    int     SetDevConfig_GPRSCDMACfg(LONG lLoginID, DEVICE_CDMAGPRS_CFG* pstGPRSCDMAInfo, int waittime);

	//�������µı�������Э��(��Ӧdvr�汾LB2.42�����Ժ�)
	//linjianyan 2007-7-17
	int		GetDevConfig_AlmCfgNew(LONG lLoginID, DEV_ALARM_SCHEDULE &stAs, int waittime);

	void	GetAlmActionMsk(CONFIG_TYPES almType, DWORD *dwMsk);
	void	GetAlmActionFlag(EVENT_HANDLER hEvent, DWORD *dwFlag);
	int		GetDevConfig_AlmCfgLocalAlarm(LONG lLoginID, ALARM_IN_CFG *pAlmCfg, int waittime);
	int		GetDevConfig_AlmCfgNetAlarm(LONG lLoginID, ALARM_IN_CFG *pAlmCfg, int waittime);
	int		GetDevConfig_AlmCfgMotion(LONG lLoginID, MOTION_DETECT_CFG *pMtnCfg, int waittime);
	int		GetDevConfig_AlmCfgLoss(LONG lLoginID, VIDEO_LOST_ALARM_CFG *pLosCfg, int waittime);
	int		GetDevConfig_AlmCfgBlind(LONG lLoginID, BLIND_ALARM_CFG *pBldCfg, int waittime);
	int		GetDevConfig_AlmCfgDisk(LONG lLoginID, DISK_ALARM_CFG *pDiskAlmCfg, int waittime);
	int		GetDevConfig_AlmCfgNetBroken(LONG lLoginID, NETBROKEN_ALARM_CFG *pNetBrkCfg, int waittime);
	
	int		SetDevConfig_AlmCfgNew(LONG lLoginID, DEV_ALARM_SCHEDULE &stAs, int waittime);
	
	void	SetAlmActionFlag(EVENT_HANDLER *pEvent, DWORD dwFlag);
	int		SetDevConfig_AlmCfgLocalAlarm(LONG lLoginID, ALARM_IN_CFG *pAlmCfg, int waittime);
	int		SetDevConfig_AlmCfgNetAlarm(LONG lLoginID, ALARM_IN_CFG *pAlmCfg, int waittime);
	int		SetDevConfig_AlmCfgMotion(LONG lLoginID, MOTION_DETECT_CFG *pMtnCfg, int waittime);
	int		SetDevConfig_AlmCfgLoss(LONG lLoginID, VIDEO_LOST_ALARM_CFG *pLosCfg, int waittime);
	int		SetDevConfig_AlmCfgBlind(LONG lLoginID, BLIND_ALARM_CFG *pBldCfg, int waittime);
	int		SetDevConfig_AlmCfgDisk(LONG lLoginID, DISK_ALARM_CFG *pDiskAlmCfg, int waittime);
	int		SetDevConfig_AlmCfgNetBroken(LONG lLoginID, NETBROKEN_ALARM_CFG *pNetBrkCfg, int waittime);
	
	int		GetDevConfig_WorkSheet(LONG lLoginID, CONFIG_WSHEET_TYPE sheetType, CONFIG_WORKSHEET *pWSheetCfg, int waittime, int nSheetNum=16, int nChannel = 0);
	int		SetDevConfig_WorkSheet(LONG lLoginID, CONFIG_WSHEET_TYPE sheetType, CONFIG_WORKSHEET *pWSheetCfg, int waittime, int nSheetNum=16, int nChannel = 0);
	//new  set mail cfg func
	int		SetDevConfig_MailCfg(LONG lLoginID, DEVICE_MAIL_CFG *pstMail ,int waittime);
	/* �����豸ͼ��ͨ�����ƣ�MB��ʽ���� */
	int		SetupChannelName(LONG lLoginID,char *pbuf, int nbuflen);

	/* ������ѯ�豸״̬������������Ӳ�̡�¼��״̬�ȡ� */
	int		QueryDevState(LONG lLoginID, int nType, char *pBuf, int nBufLen, int *pRetLen, int waittime=1000);

	/* ����ͨ���ַ����� */
	int		SetupChannelOsdString(LONG lLoginID, int nChannelNo, CHANNEL_OSDSTRING* struOsdString, int nbuflen);

	/* ��ȡ������ƽ̨��Ϣ */
	int		GetPlatFormInfo(LONG lLoginID, DWORD dwCommand, int nSubCommand, int nParam, LPVOID lpOutBuffer, DWORD dwOutBufferSize, LPDWORD lpBytesReturned,int waittime);

	/* ���ø�����ƽ̨��Ϣ */
	int		SetPlatFormInfo(LONG lLoginID, DWORD dwCommand, int nSubCommand, int nParam, LPVOID lpInBuffer, DWORD dwInBufferSize, int waittime);

	/*  ��ѯ�豸������ */
	int		GetDevFunctionInfo(LONG lLoginID, int nType, char *pBuf, int nBufLen, int *pRetLen, int waittime=1000);

	/* ��ȡ�豸֧�ֵ������Խ���ʽ�б� */
	int		GetDevTalkFormatList(LONG lLoginID, DEV_TALK_FORMAT_LIST *pstTalkFormat, int waittime=1000);

	int		QueryNetUserState(LONG lLoginID, DEV_TOTAL_NET_STATE *pstNetUserState, int waittime=1000);

	//�����豸�������������ӹ�����
	void	GetFunctionMsk(int EnableType, const char *strSource ,DWORD *dwMsk, LONG lLogin, int waittime);
	

	/* ��ѯ���ڲ��� */
	int		QueryTransComParams(LONG lLoginID, int TransComType, COMM_STATE* pCommState, int nWaitTime);

private:

	/* ��־��ѯ�������ж� */
	BOOL	SearchLogProtocol(LONG lLoginID, int waittime);

#ifdef WIN32
	/* ������־XML���� */
	int		ParseLogXML(char *pXMLFile, char *pOutLogBuffer, int nMaxLen, int *nResultlen);

#endif
private:
	CManager*		m_pManager;
	//Begin: Add by li_deming(11517) 2008-2-20
//	DWORD	  m_dwSign;	//��������һЩ������Ϣ��
						//0x0:��ʼֵ(��Чֵ)
						//0x1:û�б���ʱ��Ķ�DDNS������Ϣ
						//0x2:�б���ʱ��Ķ�DDNS������Ϣ
						//0x3:
	//End:li_deming(11517)
	OS_EVENT					m_hRecEvent;	/* ��������ͬ���¼� */
};

/* �����豸Э����������Ϣ��PPPOE��DDNS�� */
int DecodeHostString(int iHostType, void *vHostStru, char *szSubParam, char *szOutBuf, int iMaxOutBufLen, LONG lLoginID);

/* �����豸Э�����ʼ����� */
int DecodeMailCfg(void *lpMailCfg, char *pOutBuf, int iMaxOutBufLen);

/* ��ֵת�� ������ <----> �±� */
DWORD ChangeBaudRate(DWORD dwBaud);

/* �����������ڴ���Э�顢���롢�û��ӿڽṹ��ת�� */
void GetMaskedFuncName(char *buf, int buflen, DWORD dwMask, char *namelist, int maxnum, DWORD *getnum);
void GetMaskedFuncIndex(BYTE *des, BYTE src, DWORD dwMask);
void GetMaskedFuncIndex2Dev(BYTE *des, BYTE src, DWORD dwMask);



#endif // _DEVCONFIG_H_


