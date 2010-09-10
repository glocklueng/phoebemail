/*
* Copyright (c) 2009, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �����ƣ�ʵʱ������
* ժ��Ҫ��ʵʱ���ӹ���ģ�顣
*
*/
//////////////////////////////////////////////////////////////////////////

#ifndef _REALPLAY_H_
#define _REALPLAY_H_

#include "StdAfx.h"
#include "netsdk.h"
#include "Timer.h"

class CManager;
class CVideoRender;


/* ʵʱԤ����Ϣ�ṹ */
typedef struct
{
	afk_channel_s		*channel;
	int					channelid;
	CVideoRender		*Render;
	FILE				*file;
	int					fileflushflag;
	fRealDataCallBack	pRealDataCallBack;
	fRealDataCallBackEx	pRealDataCallBackEx;
	DWORD				dwDataTypeFlag;
	DWORD				userdata;
	BOOL				bAudioPlay;
	int					nConnectID;
} st_Monitor_Info;


/* ��̨������Ϣ�ṹ */
typedef struct
{
	afk_device_s		*device;
	afk_control_channel_param_s controlparam;
} st_PtzControl_Info;


class CRealPlay  
{
public:
	CRealPlay(CManager *pManager);
	virtual ~CRealPlay();

public:
	
	/* ��ʼ�� */
	int							Init(void);

	/* ���� */
	int							Uninit(void);

	/* �ر�һ���豸����ͨ�� */
	int							CloseChannelOfDevice(afk_device_s* device);

	/* ��ʼʵʱ���� */
	LONG						StartRealPlay(LONG lLoginID, int nChannelID, HWND hWnd, UINT subType = 0);

	/* ֹͣʵʱ���� */
	int							StopRealPlay(LONG lRealHandle);

	/* ����ͼ�󲥷ŵ������� */
	int							AdjustFluency(LONG lRealHandle, int nLevel);

	/* ��ʼ�໭��Ԥ�� */
	LONG						StartMultiPlay(LONG lLoginID, int nChannelID, HWND hWnd, UINT subType = RType_Multiplay);

	/* ֹͣ�໭��Ԥ�� */
	int							StopMultiPlay(LONG lMultiPlay);

	/* ���ý����ͼ�� */
	int							SetDecoderVideoEffect(LONG lRealHandle, unsigned char brightness, unsigned char contrast, unsigned char hue, unsigned char saturation);

	/* ��ȡ�����ͼ�� */
	int							GetDecoderVideoEffect(LONG lRealHandle, unsigned char *brightness, unsigned char *contrast, unsigned char *hue, unsigned char *saturation);

	/* �򿪽�������� */
	int							Decoder_OpenSound(LONG lRealHandle);

	/* �رս�������� */
	int							Decoder_CloseSound();

	/* �������� */
	int							SetVolume(LONG lRealPlay, int nVolume);

	/* ��ʼ����ʵʱ�������� */
	int							StartSaveRealData(LONG lRealPlay, const char *pchFileName);

	/* ֹͣ����ʵʱ�������� */
	int							StopSaveRealData(LONG lRealPlay);

	/* ���ñ���ʵʱ�������ݵĻص����� */
	int							SetRealDataCallBack(LONG lRealPlay, fRealDataCallBack cbRealData, DWORD dwUser);

	/* ���ñ���ʵʱ�������ݵĻص�����-��չ*/
	int							SetRealDataCallBackEx(LONG lRealPlay, fRealDataCallBackEx cbRealData, DWORD dwUser, DWORD dwFlag);
	
	/* ��������� */
	int							CapturePicture(LONG lRealPlay, const char *pchPicFileName);

	/* ��ʼ��̨���ƴ����� */
	int							StartPTZControlCommand(afk_device_s *device, afk_control_channel_param_s controlparam, BOOL bOnce, BOOL bInTimer);	

	/* ֹͣ��̨���ƴ����� */
	int							StopPTZControlCommand(afk_device_s *device, int nChannelID);

	/* ��ͨ��̨���� */
	int							PTZControl(LONG lLoginID, int nChannelID, DWORD dwPTZCommand, DWORD dwStep, BOOL dwStop);

	/* ������̨���� */
	int							YWPTZControl(LONG lLoginID, int nChannelID, DWORD dwPTZCommand, unsigned char param1, unsigned char param2, unsigned char param3, BOOL dwStop);
	
	/*������̨������չ*/
	int							YWPTZControlEx(LONG lLoginID, int nChannelID, DWORD dwPTZCommand, LONG lParam1, LONG lParam2, LONG lParam3, BOOL dwStop);
	
	/* ��ȡ����ͳ�� */
	LONG						GetStatiscFlux(LONG lLoginID, LONG lPlayHandle);

	/* ��ȡ֡�� */
	int							GetFrameRealPlay(LONG lPlayHandle, int *fileframerate, int *playframerate);


public:
	class SearchMIbyHandle;
	friend class SearchMIbyHandle;

	class SearchPIbyDevice;
	friend class SearchPIbyDevice;


public:
	static void	__stdcall		ptzcontrol_proc(LPVOID lpPara);

	void						Process_ptzcontrol_proc();


private:
	/* ����ر�ʵʱԤ��ͼ�� */
	int							ProcessStopRealPlay(st_Monitor_Info& moninfo);


private:
	CManager*					m_pManager;

	std::list<st_Monitor_Info*>	m_lstMonitors;	/* ������Ϣ�б� */
	DEVMutex						m_csMonitors;
	
	std::list<st_PtzControl_Info*> m_lstPTZ;	/* ��̨������Ϣ�б� */
	DEVMutex						m_csPTZ;

	CTimer					m_timer;		/* ��̨��ʱ�� */
	BOOL						m_bIsOpen;		/* ��ʱ���Ƿ��� */
};


class CRealPlay::SearchMIbyHandle
{
	LONG m_lHandle;
public:
	SearchMIbyHandle(LONG lHandle):m_lHandle(lHandle){}

	bool operator()(st_Monitor_Info*& mi)
	{
		return m_lHandle == (LONG)(mi?mi->channel:0);
	}
};

class CRealPlay::SearchPIbyDevice
{
	LONG m_lDevice;
	int  m_nChannelId;
public:
	SearchPIbyDevice(LONG lDevice,int nChannelId):m_lDevice(lDevice),m_nChannelId(nChannelId){}

	bool operator()(st_PtzControl_Info*& pi)
	{
		return (m_lDevice == (LONG)(pi?pi->device:0)) && (m_nChannelId == pi->controlparam.no);
	}
};


#endif // _REALPLAY_H_



