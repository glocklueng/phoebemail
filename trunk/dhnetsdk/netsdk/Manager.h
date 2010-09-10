/*
* Copyright (c) 2009, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �����ƣ�������
* ժ��Ҫ��SDK��DVR���ܶ��⿪�ŵĴ��ڣ�DVRӵ�кܶ๦�ܣ���ȡ������ģʽ�ǽϺõ�ѡ��
*         ��DVR���ܽ��й��࣬��Ҫ�����У�ʵʱ���ӡ�Զ�̻طš������������Խ�����ѯ�����ơ����õȡ�
*
*/
//////////////////////////////////////////////////////////////////////////

#ifndef _MANAGER_H_
#define _MANAGER_H_

#include "netsdk.h"
#include "netsdktypes.h"

#ifdef WIN32
#include <Mmsystem.h>
#pragma comment( lib, "Winmm.lib")
#endif

struct afk_device_prob_s;
class CRealPlay;
class CSearchRecordAndPlayBack;
class CAlarmDeal;
class CTalk; 
class CDevConfig;
class CDevConfigEx;
class CDevControl;
class CRenderManager;
class CServerSet;
class CSnapPicture;
class CGPSSubcrible;
class CDecoderDevice;
class CAutoRegister;
class CDynamicThread;
class CDevNewConfig;


class CManager  
{
public:
	CManager();
	virtual ~CManager();

public:
	/* ��ʼ������ */
	int							Init(fDisConnect cbDisConnect, DWORD dwUser);

	/* ������ */
	int							Uninit();

	/* �����豸 */
	LONG						Login_Dev(char *szDevIp, int nPort, char *szUser, char *szPassword, LPNET_DEVICEINFO lpDeviceInfo, int *pErrorCode);
	
	/* ��¼�豸����չ�ӿ� */
	LONG						Login_DevEx(char *szDevIp, int nPort, char *szUser, char *szPassword, int nSpecCap, void* pCapParam, LPNET_DEVICEINFO lpDeviceInfo, int *pErrorCode = 0);
	
	/* �ǳ��豸 */
	int							Logout_Dev(LONG lLoginID);

	/* ��ȡ�豸����ͳ�ƣ�lPlayHandleΪ0ʱĿ��Ϊ�����豸 */
	LONG						GetStatiscFlux(LONG lLoginID, LONG lPlayHandle);

	/* ͨ���豸���ֻ����к���DDNS��������ѯIP */
	BOOL						GetDVRIPByResolveSvr(char *szDevIp, int nPort, unsigned char *szDVRName, int nDVRNameLen, unsigned char *szDVRSerialNumber, int nDVRSerialLen, char *szGetIp);

	/* ��ʼ�����豸 */
	LONG						ListenServer(char *szIp, int nPort, fServiceCallBack cbListen, DWORD dwUserData);

	/* ֹͣ�����豸 */
	BOOL						StopListenServer(LONG lServerHandle);
	
	/* ��Ӧ�豸��ע������ */
	BOOL						ResponseDevReg(char *szDevSerial, char *szIp, int nPort, BOOL bAccept);

	/* ���ò��� */
	BOOL						SetDeviceMode(LONG lLoginID, EM_USEDEV_MODE emType, void* pValue);


public:
	/* ����豸�Ƿ���Ч */	
	int							IsDeviceValid(afk_device_s* device, int specFlag = 0);

	/* device��Դ����������1 */
	void						EndDeviceUse(afk_device_s* device);

	/* ɾ���豸 */
	int							DeleteDevice(afk_device_s* device);

	/* �����������Ͷ��߼�� */
	void						AllSendHeartBeat();

	/* ִ�ж����������� */
	void						AllDevExecuteTask();

	/* �첽�ӿڳ�ʱ��� */
	void						AllAsynTimeoutDetect();
	
	/* ɾ���������� */
	void						DelAlarmData(AFK_ALARM_DATA *pstAlarmData);

	/* ���������Ϣ�ص� */
	void						DealDisconnCallback();

	/* ���������ݻص� */
	void						DealAlarmDataCallback();

	/* ��������ע�����ӻص� */
	void						DealAutoRegiCallback();

	/* ��������ע����߻ص� */
	void						DealAutoRegiDisCallback();

	/* �����첽��Ϣ�ص� */
	void						DealResponseDataCallback();

	/* ����NVD���Ȼص� */
	void						DealNVDPosCallback();

	/* �������������Դ */
	void						DealCleanResource();

	/* ����ע���������� */
	void						DealListenServer(void* pServerHandle, char *szClientIp, int nClientPort, int nCommand, void *pParam);
	
	/* ��ձ������� */
	int							ClearAlarm(afk_device_s* device);

	/* ����Ψһ������ */
	DWORD						GetPacketSequence(void);

	/* �豸�����Ͽ��ڲ��ص����� */
	void						DeviceDisConnect(afk_device_s* device, afk_channel_s* channel, int nOnline, char *szIp, int nPort, int nInterfaceType);

	/* �豸�¼��ڲ��ص����� */
	void						DeviceEvent(afk_device_s* device, int nEventType, void *param);

	/* �û�Ȩ�� */
	int							AnalyzeAuthorityInfo(afk_device_s* device);


public:
	class SearchLEbyThreadID;
	friend class SearchLEbyThreadID;

	class SearchLSIbyHandle;
	friend class SearchLSIbyHandle;

	class SearchLCIbyIpPort;
	friend class SearchLCIbyIpPort;
	

public:
	/* ��ȡ����ִ��ʧ�ܵ�ԭ�� */
	DWORD						GetLastError(void);
	int							SetLastError(DWORD dwError);

	/* ��ȡʵʱ����ģ����� */
	CRealPlay&					GetRealPlay(void) { return *m_pRealPlayMdl; }					

	/* ��ȡԶ�̻ط�ģ����� */
	CSearchRecordAndPlayBack&	GetPlayBack(void) { return *m_pPlayBackMdl; }

	/* ��ȡrender���������� */
	CRenderManager&				GetRenderManager(void) { return *m_pRenderManager; }

	/* ��ȡ�豸����ģ����� */
	CDevConfig&					GetDevConfig(void) { return *m_pConfigMdl; }

	/* ��ȡ�豸����ģ��ģ�� */
	CDevConfigEx&				GetDevConfigEx(void) { return *m_pConfigExMdl; }

	/* ��ȡ�豸�ַ�������ģ����� */
	CDevNewConfig&				GetNewDevConfig(void) { return *m_pNewConfigMdl; }

	/* ��ȡ�豸����ģ����� */
	CDevControl&				GetDevControl(void) { return *m_pControlMdl; }

	/* ��ȡ��������ģ����� */
	CAlarmDeal&					GetAlarmDeal(void) { return *m_pAlarmMdl; }

	/* ��ȡ�����Խ�ģ����� */
	CTalk&						GetTalk(void) { return *m_pTalkMdl; }

	/* ��ȡ����������ģ����� */
	CServerSet&					GetAlarmServer(void) { return *m_pAlarmServerMdl; }

	/* ��ȡץͼ����ģ����� */
    CSnapPicture&               GetSnapPicture(void) { return *m_pSnapPicMdl; }

	/* ��ȡGPS����ģ����� */
	CGPSSubcrible&              GetGPSSubcrible(void) { return *m_pGPSMdl; }

	/* ��ȡ������ģ����� */
	CDecoderDevice&				GetDecoderDevice(void) { return *m_pNVDMdle; }

	/* ��ȡ����ע��ģ����� */
	CAutoRegister&				GetAutoRegister(void) { return *m_pAutoRegiMdl; }

	CDynamicThread&				GetDynamicThread(void) { return *m_pDynamicThread; }

	/* ��ȡSDK�ӿڻ��������� */
	DEVMutex&					GetCS(void)	{ return m_csDevices; }

	/* �������Ӵ��� */
	void						SetConnectTryNum(const int& ConnectTryNum) 
	{ 
		if(ConnectTryNum > 0)
		{
			m_nConnTryNum = ConnectTryNum; 
		}
	}

	/* �������ӳ�ʱ */
	void						SetConnectTime(const int& ConnectTime) 
	{
		if(m_nLoginTimeout > 0)
		{
			m_nLoginTimeout = ConnectTime; 
		}
	}

	/* ����������� */
	void						SetNetParameter(NET_PARAM *pNetParam);

	/* ��ȡ������� */
	void						GetNetParameter(NET_PARAM *pNetParam);

	/* ���ö��������ɹ��ص����� */
	void						SetAutoReconnCallBack(fHaveReConnect cbHaveReconn, DWORD dwUser)
	{
		m_pfReConnect = cbHaveReconn;
		m_dwHaveReconnUser = dwUser;
	}

	/* ���������Ӷ��߻ص����� */
	void						SetSubDisconnCallBack(fSubDisConnect cbSubDisconn, DWORD dwUser)
	{
		m_pfSubDisConnect = cbSubDisconn;
		m_dwSubDisconnUser = dwUser;
	}

	/* ������Ϣ�ص����� */
	void						SetMessCallBack(fMessCallBack cbMessage,DWORD dwUser)
	{
		m_pfMessCallBack = cbMessage;
		m_dwMessUser = dwUser;
	}

	/* ���û�����ӻص����� */
	void						SetDrawCallBack(fDrawCallBack cbDraw,const DWORD& dwUser)
	{
		m_pfDrawCallBack = cbDraw;
		m_dwDrawUser	 = dwUser;	
	}

	/* ��ȡ�����ص����� */
	fHaveReConnect&				GetHaveReconnFunc(void) { return m_pfReConnect; }

	/* ��ȡͼ����ӻص����� */
	fDrawCallBack&				GetDrawFunc(void) {	return m_pfDrawCallBack; }

	/* ��ȡ������ӻص��Զ������ */
	DWORD						GetDrawCallBackUserData(void) { return m_dwDrawUser; }

	/* ��ȡ�������� */
	std::list<AFK_ALARM_DATA*>&	GetAlarmDataList(void) { return	m_lstAlarmData; }

	/* ��ȡ�첽���ݻص����� */
	std::list<AFK_RESPONSE_DATA*>& GetResponseDataList(void) { return m_lstResponseData; }

	/* ��ȡ������������ */
	DEVMutex&					GetAlarmDataCS(void) { return m_csAlarmData; }

	DEVMutex&					GetASCS(void) { return m_csAlarmServer; }

	/* ��ȡ�첽���ݻص����� */
	DEVMutex&					GetResponseDataCS(void) { return m_csResponse; }


private:
	/* ��ѯ�豸������Ϣ */
	int							GetDeviceInfo(afk_device_s* device, NET_DEVICEINFO *pstDevInfo, int nWaitTime);

	/* ת��������� �ڲ� --> �ⲿ */
	int							GetLoginError(int nErrorCode);


public:
	afk_device_prob_s*			m_pDeviceProb;		/* �豸ģ��װ���� */
	
	OS_EVENT					m_hDisEvent;
	OS_EVENT					m_hExitThread;
	OS_EVENT					m_hAlarmDataEvent;
	OS_EVENT					m_hCleanResEvent;
	OS_EVENT					m_hAutoRegiEvent;
	OS_EVENT					m_hAutoRegiDisEvent;
	OS_EVENT					m_hResponseEvent;
	OS_EVENT					m_hNVDPlaybackEvent;
	OS_THREAD					m_hThread;
	OS_THREAD					m_hHeatBeatThread;
	OS_THREAD					m_hCleanResThread;


private:	/* һ�������˽�б��� */
	LN_LIFECOUNT				m_nLifeCount;		/*�������ڼ�������*/

	fMessCallBack				m_pfMessCallBack;	/* SDK�û���Ϣ�ص�����ָ�� */

	fDrawCallBack				m_pfDrawCallBack;	/* ͼ����ӻص�����ָ�� */

	fDisConnect					m_pfDisConnect;		/* �豸���߻ص�����ָ�� */

	fHaveReConnect				m_pfReConnect;		/* �豸���������ɹ��ص�����ָ�� */

	fSubDisConnect				m_pfSubDisConnect;	/* ��̬�����Ӷ��߻ص�����ָ�� */

	CRealPlay*					m_pRealPlayMdl;		/* ʵʱ���ӹ���ģ�� */
	CSearchRecordAndPlayBack*	m_pPlayBackMdl;		/* Զ�̻طŹ���ģ�� */
	CRenderManager*				m_pRenderManager;	/* Render��Դ������ */
	CAlarmDeal*					m_pAlarmMdl;		/* ��������ģ�� */
	CTalk*						m_pTalkMdl;			/* �����Խ�����ģ�� */
	CDevConfig*					m_pConfigMdl;		/* ���ù���ģ�� */
	CDevConfigEx*				m_pConfigExMdl;		/* ��չ���ù���ģ�� */
	CDevControl*				m_pControlMdl;		/* ���ƹ���ģ�� */
	CServerSet*					m_pAlarmServerMdl;	/* ��������������ģ�� */
	CSnapPicture*               m_pSnapPicMdl;		/* ץͼ����ģ�� */ 
	CGPSSubcrible*              m_pGPSMdl;			/* GPS����ģ�� */
	CDecoderDevice*				m_pNVDMdle;			/* NVD����ģ�� */
	CAutoRegister*				m_pAutoRegiMdl;		/* ����ע�Ṧ��ģ�� */
	CDynamicThread*				m_pDynamicThread;
	CDevNewConfig*				m_pNewConfigMdl;	/* �ַ������ù���ģ�� */

	std::list<AFK_LAST_ERROR *>	m_lstLastError;		/* Last Error �б� */
	DEVMutex						m_csError;

	std::list<afk_device_s*>	m_lstDevices;		/* ��ǰ���ߵ��豸�б� */
	DEVMutex						m_csDevices;

	std::list<AFK_DISCONN_INFO*> m_lstDisconnDev;	/* �Ͽ����ӵ��豸�б� */
	DEVMutex						m_csDisconn;

	std::list<AFK_ALARM_DATA*>	m_lstAlarmData;		/* ������Ϣ���� */
	DEVMutex						m_csAlarmData;

	std::list<afk_device_s*>	m_lstCleanRes;		/* �������ӵ��豸�б� */
	DEVMutex						m_csCleanRes;

	std::list<AFK_LISTER_DATA*>	m_lstListenHandle;	/* ��������б� */
	DEVMutex						m_csListen;

	std::list<AFK_CLIENT_REGISTER_INFO*> m_lstCltRegInfo;/* �ͻ���ע����Ϣ���� */
	DEVMutex						m_csCltRegInfo;
	
	std::list<AFK_CLIENT_DISCONN_INFO*>	m_lstCltDisconn;/* �ͻ��˶��������б� */
	DEVMutex						m_csCltDisconn;

	std::list<AFK_RESPONSE_DATA*> m_lstResponseData;/* �첽���ݻص��б� */
	DEVMutex						m_csResponse;

	std::list<AFK_NVD_PLAYBACK*> m_lstNVDPlayback;	/* NVD�طŽ��Ȼص��б� */
	DEVMutex						m_csNVDPlayback;

	DEVMutex						m_csAlarmServer;

	DWORD						m_dwErrorCode;		/* ����ʱ������� */

	DWORD						m_dwDrawUser;		/* ͼ����ӻص��û����� */
	
	DWORD						m_dwDisConnectUser;	/* �豸���߻ص��û����� */

	DWORD						m_dwHaveReconnUser;	/* ���������ɹ��ص��û����� */

	DWORD						m_dwSubDisconnUser;	/* ��̬�����Ӷ��߻ص��û����� */

	DWORD						m_dwMessUser;		/* �û���Ϣ�ص��Զ������� */

	int							m_nLoginTimeout;	/* �ȴ����뷵�ذ���ʱʱ�� */

	int							m_nConnTryNum;		/* ���ӳ��Դ��� */

	int							m_nSubConnSpaceTime;/*������֮��ĵȴ�ʱ��*/

	int							m_nConnHostTime;	/* ��������ʱ�� */

	int							m_nConnBufLen;		/* ÿ�����ӽ��ջ����С */

	int							m_nGetDevInfoTime;	/* ��ȡ�豸��Ϣ�ĳ�ʱʱ��*/

	int							m_nGetSubConnTime;	/* ��ȡ��������Ϣ�ĳ�ʱʱ�� */
	
	LONG						m_dwPacketSequence;	/* Ψһ������ˮ�� */
};

class CManager::SearchLEbyThreadID
{
#ifdef WIN32

	DWORD m_dwID;
public:
	SearchLEbyThreadID(DWORD dwThreadID):m_dwID(dwThreadID){}

#else	//linux

	pthread_t m_dwID;
public:
	SearchLEbyThreadID(pthread_t dwThreadID):m_dwID(dwThreadID){}

#endif
	bool operator()(AFK_LAST_ERROR*& le)
	{
		return (m_dwID == (le?le->dwThreadID:0));
	}
};

class CManager::SearchLSIbyHandle
{
	LONG m_lHandle;
public:
	SearchLSIbyHandle(LONG lHandle):m_lHandle(lHandle){}
	
	bool operator()(AFK_LISTER_DATA*& ld)
	{
		return (m_lHandle == (LONG)(ld?ld->lsnHandle:0));
	}
};

class CManager::SearchLCIbyIpPort
{
	char *m_ip;
	WORD m_port;
public:
	SearchLCIbyIpPort(char *ip, WORD port):m_ip(ip), m_port(port){}
	
	bool operator()(AFK_CLIENT_NODE*& cn)
	{
		if (NULL == m_ip || NULL == cn->ip)
		{
			return false;
		}
		return (_stricmp(m_ip, cn->ip)==0)&&(m_port==cn->port);
	}
};


#endif // _MANAGER_H_

