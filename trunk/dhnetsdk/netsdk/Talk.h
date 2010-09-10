/*
* Copyright (c) 2009, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �����ƣ������Խ���
* ժ��Ҫ�������Խ�����ģ�顣
*
*/
//////////////////////////////////////////////////////////////////////////

#ifndef _TALK_H_
#define	_TALK_H_

#include "StdAfx.h"
#include "Manager.h"


#define MAX_ENCODE_LEN	65527

//��Ƶ�������ͣ�����豸ͬʱ֧�ֶ��֣�������Խ�����ȼ�Խ�ߡ�
#define INTERNEL_ENCODE_TYPE_8K8BPCM		0	//PCM��û��ͷ��Ϣ
#define INTERNEL_ENCODE_TYPE_8K16BNEWPCM	1	//��ͷ��Ϣ��PCM
#define INTERNEL_ENCODE_TYPE_G711A8K16B		2	//G711a
#define INTERNEL_ENCODE_TYPE_G711U8K16B		3	//G711u
#define INTERNEL_ENCODE_TYPE_AMR8K16B		4	//AMR
#define INTERNEL_ENCODE_TYPE_G7268K16B		5	//G726



#define FRAME_LEN_8K8BPCM	(1024*2)
#define FRAME_LEN_G711A8K16B	2560

typedef void (__stdcall *pfAudioDataCallBack)(LONG lTalkHandle, char *pDataBuf, DWORD dwBufSize, BYTE byAudioFlag, DWORD dwUser);

typedef struct _talk_handle_info
{
	LONG				lDevHandle;
	afk_channel_s		*pTalkChannel;
	int					iChannelId;
	pfAudioDataCallBack	pfcb;
	DWORD				dwUser;
} TALKHANDLEINFO, *LPTALKHANDLEINFO;

typedef struct _talk_mr_handle_info
{
	TALKHANDLEINFO		hTalkHandle;
	LONG				lTalkMRList;
} TALKMRHANDLEINFO, *LPTALKMRHANDLEINFO;

typedef struct _talk_broadcast_info
{
	LONG				lDevHandle;
	afk_channel_s		*pTalkChannel;
	int					iChannelId;
} TALKBROADCASTINFO, *LPTALKBROADCASTINFO;

typedef struct _encode_audio_format
{
	BYTE	wFormatTag;				//�������ͣ���0-PCM
	WORD	nChannels;				//������
	WORD	wBitsPerSample;			//�������			
	DWORD	nSamplesPerSec;			//������
} ENCODEAUDIOFORMAT, *LPENCODEAUDIOFORMAT;

class CVideoRender;
class CManager;


class CTalk
{
public:
	CTalk(CManager *pManager);
	virtual ~CTalk();

	int Init();
	int UnInit();

	DWORD GetAudioEncodeType() {return m_dwAudioEncodeType;}

	int	GetAudioEncodeBit() { return m_nAudioBit; }

	LONG StartTalk(LONG lLoginID, pfAudioDataCallBack pfcb, DWORD dwUser);
	BOOL SetVolume(LONG lTalkHandle, WORD wVolume);
	LONG TalkSendData(LONG lTalkHandle, char *pSendBuf, DWORD dwBufSize);
	BOOL RecordStart();
	BOOL RecordStop();
	void AudioDec(char *pAudioDataBuf, DWORD dwBufSize);
	BOOL StopTalk(LONG lTalkHandle);
	BOOL BroadcastAddDev(LONG lLoginID);
	BOOL BroadcastDelDev(LONG lLoginID);

	int InitAudioEncode(AUDIO_FORMAT aft);
	int	 AudioEncode(LONG lHandle, BYTE *lpInBuf, DWORD *lpInLen, BYTE *lpOutBuf, DWORD *lpOutLen);
	int	 ReleaseAudioEncode();

	LONG InitAudioDecode(AUDIO_FORMAT aft);
	int	 AudioDecode(LONG lHandle, BYTE *lpInBuf, DWORD *lpInLen, BYTE *lpOutBuf, DWORD *lpOutLen);
	int	 ReleaseAudioDecode(LONG lHandle);

	int  CloseChannelOfDevice(afk_device_s * pdev);
	void* GetHisEncodeHandle(){return m_hisEncodeHandle;}

	static int WINAPI TalkFunc(
								afk_handle_t object,	/* �����ṩ�� */
								unsigned char *data,	/* ������ */
								unsigned int datalen,	/* ���ݳ��� */
								void *param,			/* �ص����� */
								void *udata);
	static int WINAPI TalkFunc_MR(
									afk_handle_t object,
									unsigned char *data,
									unsigned int datalen,
									void *param,
									void *udata);

	static void WINAPI RecordFunc(LPBYTE pDataBuffer, DWORD DataLength, long user);

protected:
	LONG SendData2Dev(afk_channel_s *pChannel, char *pSendBuf, DWORD dwBufSize);

private:

	long						m_FrameLength;
	unsigned long				m_dwSampleRate;
	int							m_nAudioBit;
	
	DWORD						m_dwAudioEncodeType;
	DEVMutex						m_cs;
	BOOL						m_ARStartSuc;
	list<LPTALKHANDLEINFO>		m_talkhandlelist;
	list<LPTALKMRHANDLEINFO>	m_dispatchlist;
	list<LPTALKBROADCASTINFO>	m_broadcastlist;
	int							m_iEncodeFlag;
	CVideoRender*				m_render;
	
	void*						m_hisEncodeHandle;
	void*						m_hisDecodeHandle;
private:
	CManager*		m_pManager;
};


#endif // _TALK_H_


