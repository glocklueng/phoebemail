/*
* Copyright (c) 2009, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �����ƣ��豸��
* ժ��Ҫ��SDK��DVR֮����ö�����Э�飬ÿ�ν������á�����Ӧ�𡱵ķ�ʽ����˿��԰�
*         ÿ���������̿��ɳ���ͨ������������ڳ���ͨ���д��䣬���ٸ��������໥������
*
*/
//////////////////////////////////////////////////////////////////////////

#ifndef _DVRDEVICE_H_
#define _DVRDEVICE_H_

#include "../StdAfx.h"
#include "dvrchannel.h"

class CTcpSocket;
class CUdpSocket;
class CMulticastSocket;


class CDvrDevice : public afk_device_s
{
public:
	CDvrDevice(afk_dvrdevice_info stuDeviceInfo, CTcpSocket *pTcpSocket,
				const char *szIp, int nPort, const char *szUser, const char *szPassword, 
				fDisconnectCallBack cbDisconnect, fDeviceEventCallBack cbDevEvent, void *userdata);
	virtual ~CDvrDevice();

public:
    /* �汾��Ϣ */
    virtual char*	device_version();

    /* ��������Ϣ */
    virtual char*	device_manufactory();

    /* ��Ʒ��Ϣ */
    virtual char*	device_product();

    /* �ر��豸 */
    virtual int		device_close();
	
    /* ��ͨ�� */
    virtual void*	device_open_channel(int type, void *parm);

    /* ͨ���Ƿ�� */
    virtual BOOL	device_channel_is_opened(int type, void *parm);

	/* �õ�ͨ�� */
	CDvrChannel*	device_get_channel(int type, unsigned int param, unsigned int subparam = 0);

	/* �ر�ͨ�� */
	void			device_remove_channel(CDvrChannel *pDvrChannel);
	
    /* ��ȡ��Ϣ */
    virtual int		device_get_info(int type, void *parm);

    /* ������Ϣ */
    virtual int		device_set_info(int type, void *parm);


public:
	/* ����ͳ�� */
    void			startstatisc();
    void			statiscing(unsigned int nLen);
    unsigned int	statisc();

	/* ��̬�����ӺͶ������� */
	void*			CreateSubConn(afk_connect_param_t *pConnParam);
	void			DestroySubConn(int type, void *pSubSocket, int nConnectID);
	void			CleanDisConn();
	void			ExecuteAllTask();	// ������������ɹ����һЩ����

	
public:
	int				device_AddRef();
	int				device_DecRef();

	
public:
    char*			GetIp() { return m_szIp; }
    int				GetPort() { return m_nPort; }
    int				GetType() { return m_Deviceinfo.type; }
    char*			GetUser() { return m_szUser; }
    char*			GetPassword() { return m_szPassword; }
    CTcpSocket*		GetTcpSocket() { return m_pTcpSocket; } 
    int				GetVideoChannelCount() { return m_Deviceinfo.channelcount; }
    int				GetAlarminputCount() { return m_Deviceinfo.alarminputcount; }
    int				GetAlarmoutputCount() { return m_Deviceinfo.alarmoutputcount; }
    afk_dvrdevice_info GetDvrInfo() { return m_Deviceinfo; }
	void			SetDeviceInfo(int type, DWORD dwParm);
	fDisconnectCallBack		GetDisconnectFunc() { return m_pfDisConnect; }
	fDeviceEventCallBack	GetDevEventFunc() { return m_pfDevEvent; }
    void*			GetDisconnectUserdata() { return m_userdata; }


protected:
	/***************************�����б�**************************/
	// ������
	CTcpSocket*					m_pTcpSocket;

	// ������
	std::map<unsigned int, CTcpSocket*>	m_lstSubTcpSockets;
	std::map<unsigned int, CUdpSocket*>	m_lstSubUdpSockets;
	std::map<unsigned int, CMulticastSocket*> m_lstMulticastSockets;
	CReadWriteMutex				m_csSubTcp;

	// ɾ�������б��õ����߳�ɾ�����ӣ���ֹ�û��ڻص���ɾ�������������
	std::queue<CTcpSocket*>		m_lstDisTcpSockets;
	std::queue<CUdpSocket*>		m_lstDisUdpSockets;
	std::queue<CMulticastSocket*> m_lsDistMultiSockets;
	CReadWriteMutex				m_csDisTcp;

    /**************************��ͨ���б�*************************/
    // ��Ƶͨ���б�
	std::map<unsigned int, CDvrChannel*> m_media_channel_list;
	CReadWriteMutex				m_csmedia;

	// Ԥ��ͨ���б�(Ψһ)
	std::map<unsigned int, CDvrChannel*> m_preview_channel_list;
	CReadWriteMutex				m_cspreview;

	// ����ͨ���б�
	std::map<unsigned int, CDvrChannel*> m_download_channel_list;
	CReadWriteMutex				m_csdownload;
	
    // ͸��ͨ���б�(����������232��485)
	std::vector<CDvrChannel*>	m_trans_channel_list;
	CReadWriteMutex				m_cstrans;

    // ��ѯͨ���б�
	std::list<CDvrChannel*>		m_search_channel_list;
	CReadWriteMutex				m_cssearch;

    // ����ͨ���б�
	std::list<CDvrChannel*>		m_config_channel_list;
	CReadWriteMutex				m_csconfig;

	// ץͼͨ���б�
	std::vector<CDvrChannel*>	m_snap_channel_list;
	CReadWriteMutex				m_cssnap;

	// ����ͨ���б�
	std::list<CDvrChannel*>		m_request_channel_list;
	CReadWriteMutex				m_csRequest;

	// ������ͨ���б�
	std::list<CDvrChannel*>		m_newconfig_channel_list;
	CReadWriteMutex				m_csnewconfig;

    /**************************��ͨ���б�*************************/
	// ����ͨ���б�(Ψһ)
	CDvrChannel*				m_alarm_channel;
	CReadWriteMutex				m_csalarm;

	// ����ͨ���б�(Ψһ)
	CDvrChannel*				m_control_channel;
	CReadWriteMutex				m_cscontrol;

    // ����ͨ���б�(Ψһ)
	CDvrChannel*				m_upgrade_channel;
	CReadWriteMutex				m_csupgrade;

	// �ϴ������ļ�
	CDvrChannel*				m_importcfg_channel;
	CReadWriteMutex				m_csimportcfg;

    // ͳ��ͨ���б�(Ψһ)
	CDvrChannel*				m_statisc_channel;
	CReadWriteMutex				m_csstatisc;

    // �����Խ�ͨ���б�(Ψһ)
	CDvrChannel*				m_audio_channel;
	CReadWriteMutex				m_csaudio;

    // �û�����ͨ���б�(Ψһ)
	CDvrChannel*				m_user_channel;
	CReadWriteMutex				m_csuser;

	// GPSͨ���б�(Ψһ)
    CDvrChannel*				m_gps_channel;
	CReadWriteMutex				m_csgps;


private:
	afk_dvrdevice_info			m_Deviceinfo;
    fDisconnectCallBack			m_pfDisConnect;
	fDeviceEventCallBack		m_pfDevEvent;
    void*						m_userdata;
    unsigned int				m_statisc;
    BOOL						m_enablestatisc;
    char						m_szIp[120];
    int							m_nPort;
    char						m_szUser[20];
    char						m_szPassword[20];
	LN_LIFECOUNT				m_lLifeCount;


private:
	DWORD			m_dwSpecial;		// �����豸��һЩʵʱ������Ϣ
	CReadWriteMutex m_csSpecial;
	int				m_nRecordProto;		// ¼���ѯ������Ϣ
	int				m_nLogProto;		// ��־��ѯ������Ϣ
	int				m_nProtocolVer;		// Э��汾��
	int				m_nIsMutiEther;		// ����֧�������0�������� 1��������(��������֮ǰ�ɵ�Э�飬�������µ��ַ���Э��)
	unsigned int	m_nSessionId;
	int				m_nTalkMode;		// 0���ͻ��˷�ʽ��1����������ʽ
	int				m_nCardQuery;		// 0:��֧�ֿ��Ų�ѯ��1��֧�ֿ��Ų�ѯ
	int             m_nQuickConfig;     // 0:��֧�ֿ��ٶ�ȡ���ã� 1��֧�ֿ��ٶ�ȡ����
	int				m_nAlarmInCaps;		// ��������ӿ���
	DWORD			m_dwTalkFormat;		// �豸֧�ֵ������Խ���ʽ����λ��ʾ��0����ͷPCM��1����DHͷPCM��2��G711a��3��AMR��4��G711u��5��G726
	AUDIO_ATTR_T	m_stCurTalkFmt;		// ��ǰ���õ������Խ���ʽ��-1��Ĭ��������ȼ���0����ͷPCM��1��PCM��2��G711a��3��AMR��4��G711u��5��G726
	int				m_nAudioAlarmInCaps;// ��Ƶ�����������
	DWORD			m_dwAlarmListenMode[32];// �������ķ�ʽ,��λ��ʾ��0��ȫ��ͨ�����ģ�1��1024������ͨ���Ķ���
	DWORD			m_dwCurMotionAlarm[32];	// ��ǰ��̬��ⱨ��״̬
	DWORD			m_dwCurVideoLost[32];	// ��ǰ��Ƶ��ʧ����״̬
	DWORD			m_dwCurShelter[32];		// ��ǰ��Ƶ�ڵ�����״̬
	DWORD			m_dwCurInputAlarm[32];	// ��ǰ�ⲿ���뱨��״̬
	int				m_nMultiPlayFlag;	// �໭��Ԥ����־
	int				m_nIsHaveTask;		// ��ʾ�Ƿ�������
	DWORD			m_dwLastLoginPacket;
	DWORD			m_dwLastSubKeep;
	AUTO_CONN_STATUS m_emTaskStatus;
	std::map<unsigned int, CTcpSocket*>::iterator m_pCurSubTcpSocket;
	int				m_nImportantRecord; // (0����ͨ¼�������Ҫ¼��ĵ�һ�β�ѯ��1����Ҫ¼��ķǵ�һ�β�ѯ)
	CONFIG_ETHERNET m_stEthernet[5];    // ������Ϣ
	
	// �豸��������
	DVR_AUTHORITY_INFO m_nAuthorityInfo;// �豸Ȩ����Ϣ
	DEVICE_MESS_CALLBACK m_messCallFunc;// �첽�ص�����
	DEVICE_MESS_CALLBACK m_nvdPlaybackCall;// �첽�ص�����
	afk_login_device_type m_loginType;
};


#endif	// _DVRDEVICE_H_


