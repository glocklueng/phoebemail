/*
* Copyright (c) 2009, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �����ƣ�Զ�̻ط���
* ժ��Ҫ��Զ�̻طŹ���ģ�顣
*
*/
//////////////////////////////////////////////////////////////////////////

#ifndef _SEARCHRECORDANDPLAYBACK_H_
#define _SEARCHRECORDANDPLAYBACK_H_

#include "StdAfx.h"
#include "netsdk.h"

class CManager;
class CVideoRender;
class CNetPlayBack;

#define INVALID_OFFSET_TIME -1
#define INVAlID_OFFSET_BYTE	-1

#define MAX_RECORD_NUM 16 //ÿ�β�ѯ¼�󷵻ص����¼������ 

/* ����¼���ļ����û���Ϣ */
typedef struct
{
	afk_device_s*		device;
	list<NET_RECORDFILE_INFO*> lstrf;	/* ¼���ļ���Ϣ�б� */
} st_SearchRecord_Info;

/* ����ط���Ϣ�ṹ */
typedef struct
{
	afk_channel_s*		channel;			// ͨ��������
	int					channelid;			// ͼ��ͨ����
	int					nPlayBackType;		// 0�����ļ��طţ�1����ʱ��ط�
	CVideoRender*		Render;				// ���롢���Ŷ���
	CNetPlayBack*		PlayBack;			// �طŻ������
	unsigned int		nFrameRate;			// �ط�֡��
	BOOL				bAudioPlay;			// �Ƿ񲥷���Ƶ
	BOOL				bDownLoadEnd;		// ��־�Ƿ������ؽ���
	NET_TIME			timeStart;			// �û��ط�¼��(���ļ���ʱ��)�Ŀ�ʼʱ��
	NET_TIME			timeEnd;			// ͬ�ϣ�����ʱ��
	unsigned int		nTotalSize;			// ¼���ܴ�С
	unsigned int		nReceiveSize;		// �ѽ��յ�¼�����ݳ���
	unsigned int		nPlayBackSize;		// �Ѳ��Ŵ�С
	unsigned int		nOffsetSize;		// ¼��λ���ƫ��λ��
	
	fDownLoadPosCallBack pNetPlayBackPosCallBack;// �طŽ��Ȼص�����ָ��
	DWORD				dwPosUser;			// ���Ȼص����û�����
	fDataCallBack		fNetDataCallBack;	// �ط����ݻص�����ָ��
	DWORD				dwDataUser;			// ���ݻص����û�����
	NET_RECORDFILE_INFO* pFileInfo;			// ���ļ��ط�ʱ����ļ���Ϣ
	NET_RECORDFILE_INFO* prf;				// ��ʱ��ط�ʱ����ļ���Ϣ�б�
	int					nrflen;				// ��ʱ��ط�ʱ���ļ���Ϣ�б�ĳ���
	int					ncurrf;				// ��ʱ��ط�ʱ����ǰ���ڻطŵ��ļ��±�
	DWORD				dwTotalTime;		// ��ʱ��ط�ʱ����ʱ������
	
	OS_THREAD			hThread;			// �ط��߳�
	OS_EVENT			hPBExit;			// ֪ͨ�����ط��̵߳��¼����
	DWORD				dwThreadID;			// �ط��̵߳��߳�ID
	int					nConnectID;
} st_NetPlayBack_Info;

/* ¼��������Ϣ�ṹ */
typedef struct
{
	afk_channel_s*		channel;			// ͨ��������
	int					channelid;			// ���ص�ͼ��ͨ����
	FILE*				file;				// �����ļ�
	int					fileflushflag;		// �ļ�����ˢ�±�־
	unsigned int		nTotalSize;			// ���ص������ܳ���
	unsigned int		nDownLoadSize;		// �����ص����ݳ���
	NET_TIME			timeStart;			// ���ؿ�ʼʱ��
	NET_TIME			timeEnd;			// ���ؽ���ʱ��
	fDownLoadPosCallBack pDownLoadPosCallBack;			// ���ļ�����ʱ�����ؽ��Ȼص�����ָ��
	fTimeDownLoadPosCallBack pTimeDownLoadPosCallBack;	// ��ʱ������ʱ�����ؽ��Ȼص�����ָ��
	DWORD				userdata;			// �ص����û�����
	NET_RECORDFILE_INFO* prf;				// ��ʱ��ط�ʱ������ļ���Ϣ���б�
	int					nrflen;				// ͬ�ϣ��б���
	int					ncurrf;				// ͬ�ϣ���ǰ�������ص��ļ��±�
	int					nConnectID;
} st_DownLoad_Info;

//////////////////////////////////////////////////////////////////////////


class CSearchRecordAndPlayBack  
{
public:
	CSearchRecordAndPlayBack(CManager *pManager);
	virtual ~CSearchRecordAndPlayBack();

public:
	/* ��ʼ�� */
	int							Init(void);

	/* ���� */
	int							Uninit(void);

	/* ��ѯĳ��ʱ�����Ƿ���¼�� */
	BOOL						QueryRecordTime(LONG lLoginID, int nChannelId, int nRecordFileType, LPNET_TIME tmStart, 
												LPNET_TIME tmEnd, char* pchCardid, BOOL *bResult, int waittime=1000);

	/* �ϵ�¼���ѯ�ӿ� */
	BOOL						QueryRecordFile(LONG lLoginID, int nChannelId, int nRecordFileType, LPNET_TIME time_start,
												LPNET_TIME time_end, char* cardid, LPNET_RECORDFILE_INFO fileinfo, int maxlen,
												int *filecount, int waittime, BOOL bTime);


	BOOL						QueryFurthestRecordTime(LONG lLoginID, int nRecordFileType, char *pchCardid, NET_FURTHEST_RECORD_TIME* pFurthrestTime, int nWaitTime);

	/* ��ʼ����¼���ļ� */
	LONG						FindFile(LONG lLoginID, int nChannelId, int nRecordFileType, char* cardid, 
												LPNET_TIME time_start,LPNET_TIME time_end, BOOL bTime,int waittime);

	/* �����ļ���Ϣ */
	int							FindNextFile(LONG lFindHandle, LPNET_RECORDFILE_INFO lpFindData);

	/* �رղ��Ҿ�� */
	int							FindClose(LONG lFindHandle);

	/* ����ط� */
	LONG						PlayBackByRecordFile(LONG lLoginID, LPNET_RECORDFILE_INFO lpRecordFile, 
													HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, DWORD dwUserData);

	/* ��չ�����������ݻص� */
	LONG						PlayBackByRecordFileEx(LONG lLoginID, LPNET_RECORDFILE_INFO lpRecordFile, 
													HWND hWnd, fDownLoadPosCallBack cbDownLoadPos, DWORD dwPosData, 
													fDataCallBack fDownLoadDataCallBack, DWORD dwDataUser);
	
	/* ��ͣ�ط� */
	int							PausePlayBack(LONG lPlayHandle, BOOL bPause);

	/* ��λ¼��ط� */
	int							SeekPlayBack(LONG lPlayHandle, unsigned int offsettime, unsigned int offsetbyte);

	/* ֹͣ¼��ط� */
	int							StopPlayBack(LONG lPlayHandle);

	/* �����ط� */
	int							StepPlayBack(LONG lPlayHandle, BOOL bStop);

	/* ��� */
	int							FastPlayBack(LONG lPlayHandle);

	/* ���� */
	int							SlowPlayBack(LONG lPlayHandle);
	
	/* �ָ����������ٶ� */
	int							NormalPlayBack(LONG lPlayHandle);

	/* ����֡�� */
	int							SetFramePlayBack(LONG lPlayHandle, int framerate);

	/* ��ȡ֡�� */
	int							GetFramePlayBack(LONG lPlayHandle, int *fileframerate, int *playframerate);

	/* ��ȡOSDʱ�� */
	int							GetPlayBackOsdTime(LONG lPlayHandle, LPNET_TIME lpOsdTime, LPNET_TIME lpStartTime, LPNET_TIME lpEndTime);

	/* ��ʼ����¼�� */
	LONG						DownloadByRecordFile(LONG lLoginID,LPNET_RECORDFILE_INFO lpRecordFile, char *sSavedFileName, 
													fDownLoadPosCallBack cbDownLoadPos, DWORD dwUserData);

	/* ֹͣ����¼�� */
	int							StopDownload(LONG lFileHandle);

	/* ��ȡ¼�����ؽ��� */
	int							GetDownloadPos(LONG lFileHandle, int *nTotalSize, int *nDownLoadSize);

	/* ���ý����ͼ�� */
	int							SetDecoderVideoEffect(LONG lPlayHandle, unsigned char brightness, unsigned char contrast, 
														unsigned char hue, unsigned char saturation);

	/* ��ȡ�����ͼ�� */
	int							GetDecoderVideoEffect(LONG lPlayHandle, unsigned char *brightness, unsigned char *contrast, 
														unsigned char *hue, unsigned char *saturation);

	/* �򿪽�������� */
	int							Decoder_OpenSound(LONG lPlayHandle);

	/* �رս�������� */
	int							Decoder_CloseSound();

	/* �������� */
	int							SetVolume(LONG lPlayHandle, int nVolume);

	/* ��������� */
	int							CapturePicture(LONG lPlayHandle, const char *pchPicFileName);

	/* ��ȡ����ͳ�� */
	LONG						GetStatiscFlux(LONG lLoginID,LONG lPlayHandle);

	/* �ر�һ���豸����ͨ�� */
	int							CloseChannelOfDevice(afk_device_s* device);

	/* ��ʱ��ط� */
	LONG						PlayBackByTime(LONG lLoginID, int nChannelID, LPNET_TIME lpStartTime, LPNET_TIME lpStopTIme, 
												fDownLoadPosCallBack cbDownLoadPos, DWORD dwPosUser, HWND hWnd);

	/* ��ʱ��ط���չ�����������ݻص� */
	LONG						PlayBackByTimeEx(LONG lLoginID, int nChannelID, LPNET_TIME lpStartTime, LPNET_TIME lpStopTIme, 
												fDownLoadPosCallBack cbDownLoadPos, DWORD dwPosUser, HWND hWnd, 
												fDataCallBack fDownLoadDataCallBack, DWORD dwDataUser);
	/* ��ʱ������ */
	LONG						DownloadByTime(LONG lLoginID, int nChannelId, int nRecordFileType, LPNET_TIME tmStart, LPNET_TIME tmEnd, char *sSavedFileName, fTimeDownLoadPosCallBack cbTimeDownLoadPos, DWORD dwUserData);


public:
	class SearchNPIbyChannel;
	friend class SearchNPIbyChannel;

	class SearchDLIbyChannel;
	friend class SearchDLIbyChannel;


public:
	
	static	int	__stdcall		QueryRecordFileInfoFunc(
												afk_handle_t object,	/* �����ṩ�� */
												unsigned char *data,	/* ������ */
												unsigned int datalen,	/* ���ݳ��� */
												void *param,			/* �ص����� */
												void *udata);

	static	int	__stdcall		NetPlayBackCallBackFunc(
												afk_handle_t object,	/* �����ṩ�� */
												unsigned char *data,	/* ������ */
												unsigned int datalen,	/* ���ݳ��� */
												void *param,			/* �ص����� */
												void *udata);
			

private:
	
	/* �ͷ�¼���ļ��ľ���б� */
	void						ReleaseAllSearchRecordInfo(void);
	/* �ͷŵ�����¼���ļ���� */
	void						ReleaseRecordFileInfo(st_SearchRecord_Info& sr);
	/* ִ�йرջطŲ��� */
	int							Process_stopplayback(st_NetPlayBack_Info& npi);
	/* ���ݻطž����ȡ�ط���Ϣ */
	st_NetPlayBack_Info*		GetNetPlayBackInfo(LONG lPlayHandle);
	/* �������ؾ����ȡ������Ϣ */
	st_DownLoad_Info*			GetDownLoadInfo(LONG lFileHandle);
	/* ִ�в�ѯ¼���ļ� */
	int							Process_QueryRecordfile(afk_device_s* device,
												int nChannelId, 
												int nRecordFileType, 
												LPNET_TIME time_start,
												LPNET_TIME time_end,
												char* cardid, 
												int waittime,
												BOOL bTime,
												list<NET_RECORDFILE_INFO*>& lstRecordFile);

	/* ��¼���ѯ���������ж� */
	BOOL						SearchRecordProtocol(LONG lLoginID);

private:

	list<st_SearchRecord_Info*> m_lstSRI;	/* ����¼���ļ��ľ���б��������µĲ�ѯ¼��ӿ� */
	DEVMutex						m_csSRI;	/* ������¼���ļ�������б� */
	list<st_NetPlayBack_Info*>	m_lstNPI;	/* ����ط���Ϣ�б� */
	DEVMutex						m_csNPI;	/* ������ط���Ϣ�б� */
	list<st_DownLoad_Info*>		m_lstDLI;	/* ¼��������Ϣ�б� */
	DEVMutex						m_csDLI;	/* ��¼��������Ϣ�б� */

private:
	CManager*		m_pManager;
};


class CSearchRecordAndPlayBack::SearchNPIbyChannel
{
	LONG m_lChannel;
public:
	SearchNPIbyChannel(LONG lChannel):m_lChannel(lChannel){}
	
	bool operator()(st_NetPlayBack_Info*& pi)
	{
		return m_lChannel == (LONG)(pi?pi->channel:0);
	}
};

class CSearchRecordAndPlayBack::SearchDLIbyChannel
{
	LONG m_lChannel;
public:
	SearchDLIbyChannel(LONG lChannel):m_lChannel(lChannel){}

	bool operator()(st_DownLoad_Info*& di)
	{
		return m_lChannel == (LONG)(di?di->channel:0);
	}
};


#endif // _SEARCHRECORDANDPLAYBACK_H_

