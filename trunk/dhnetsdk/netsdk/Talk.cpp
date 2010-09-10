
#include "Talk.h"
#include "RenderManager.h"
#include "VideoRender.h"
#include "DevConfig.h"

#ifdef WIN32

#include "Alaw_encoder.c"
#include "./depend/hisamr.h"

/*	$FXN :	CTalk()
==	======================================================================
==	$DSC :	���캯���������ж����һЩ��Ա���������˳�ʼ��
==	$ARG :	
==		 :	
==	$RET :	
==	$MOD :	2006-12-20		yehao(10857)		Create the Function
==	======================================================================
*/
CTalk::CTalk(CManager *pManager)
	: m_pManager(pManager)
{
//	InitializeCriticalSection(&m_cs);

	m_ARStartSuc = FALSE;

	m_iEncodeFlag = 0;
	m_render = NULL;
	
	m_hisEncodeHandle = 0;
	m_hisDecodeHandle = 0;
}

/*	$FXN :	~CTalk()
==	======================================================================
==	$DSC :	����������һЩ�ƺ���
==	$ARG :	
==		 :	
==	$RET :	
==	$MOD :	2006-12-20		yehao(10857)		Create the Function
==	======================================================================
*/
CTalk::~CTalk()
{
//	DeleteCriticalSection(&m_cs);
}

/*	$FXN :	Init()
==	======================================================================
==	$DSC :	ģ�鹤��ǰ�ĳ�ʼ������,��ʼ���Ĺ������ܻ�ʧ��,����Ҫ�ӹ��캯���з������
==	$ARG :	
==		 :	
==	$RET :	0��ʾ�ɹ�,����ʧ��
==	$MOD :	2006-12-20		yehao(10857)		Create the Function
==	======================================================================
*/
int CTalk::Init()
{
	{
		list<LPTALKHANDLEINFO>::iterator it = m_talkhandlelist.begin();
		for (; it != m_talkhandlelist.end(); it++)
		{
			if (*it)
			{
				if ((*it)->pTalkChannel)
				{
					(*it)->pTalkChannel->close((*it)->pTalkChannel);
				}
				delete (*it);
			}
		}
		m_talkhandlelist.clear();
	}
	
	{
		list<LPTALKBROADCASTINFO>::iterator it = m_broadcastlist.begin();
		for (; it != m_broadcastlist.end(); it++)
		{
			if (*it)
			{
				if ((*it)->pTalkChannel)
				{
					(*it)->pTalkChannel->close((*it)->pTalkChannel);
				}
				delete (*it);
			}
		}
		m_broadcastlist.clear();
	}
	
	
	//Begin: Modify by li_deming(11517) 2008-1-14	
	/*
	memset((void *)&m_AudioFormat, 0, sizeof(AUDIOFORMAT));
	m_AudioFormat.dwFrameLen = 1024*2;
		m_AudioFormat.nAudioBitrate = 64;
		m_AudioFormat.nAudioLayer = 5;
		m_AudioFormat.wChannels = 1;
		m_AudioFormat.dwSamplesPerSec = 8000;
		m_AudioFormat.wBitsPerSample = 8;*/
	m_FrameLength=2048;//1024*2
	//End:li_deming(11517)
	m_ARStartSuc = FALSE;

	m_dwAudioEncodeType = INTERNEL_ENCODE_TYPE_8K8BPCM;
	
	m_render = m_pManager->GetRenderManager().GetRender((HWND)0xFFFFFFFF);
	if (0 == (int)m_render || -1 == (int)m_render)
	{
		m_render = NULL;
	}

	if (0 == m_hisEncodeHandle) 
	{
		if (HI_SUCCESS != AMR_Encode_Init(&m_hisEncodeHandle, 0)) 
		{
			m_iEncodeFlag = 0;
			m_hisEncodeHandle = 0;
			m_pManager->SetLastError(NET_ILLEGAL_PARAM);
			return NET_ILLEGAL_PARAM;
		}
	}
/*
	��ʵ��render_open֮ǰһ��Ҫ����render_init���Ѿ���render��Ŀ�����Լ����AUDIO_RENDER_INDEXΪ�Խ�ģ������
	if (render_open(AUDIO_RENDER_INDEX, 0, 0, 0, NULL, 0, ByDDOffscreen, 0) == 0)
	{
		m_irenderindex = AUDIO_RENDER_INDEX;
	}
*/
	m_iEncodeFlag = 0;

	return 0;
}

/*	$FXN :	UnInit()
==	======================================================================
==	$DSC :	ģ�鹦�ܲ���ʹ��ʱ�ͷ���Դ.
==	$ARG :	
==		 :	
==	$RET :	0��ʾ�ɹ�,����ʧ��
==	$MOD :	2006-12-20		yehao(10857)		Create the Function
==	======================================================================
*/
int CTalk::UnInit()
{
//	EnterCriticalSection(&m_cs);
	m_cs.Lock();
	{
		list<LPTALKHANDLEINFO>::iterator it = m_talkhandlelist.begin();
		for (; it != m_talkhandlelist.end(); it++)
		{
			if (*it)
			{
				if ((*it)->pTalkChannel)
				{
					(*it)->pTalkChannel->close((*it)->pTalkChannel);
				}
				delete (*it);
			}
		}
		m_talkhandlelist.clear();
	}
	
	{
		list<LPTALKBROADCASTINFO>::iterator it = m_broadcastlist.begin();
		for (; it != m_broadcastlist.end(); it++)
		{
			if (*it)
			{
				if ((*it)->pTalkChannel)
				{
					(*it)->pTalkChannel->close((*it)->pTalkChannel);
				}
				delete (*it);
			}
		}
		m_broadcastlist.clear();
	}
	
//	LeaveCriticalSection(&m_cs);
	m_cs.UnLock();
		
	//Begin: Delete by li_deming(11517) 2008-1-14
	/*
	if (m_RecordHandle != NULL)
		{
			CloseAudioRecordEx(m_RecordHandle);
			m_RecordHandle = 0;
		}*/
	//End:li_deming(11517)
	
	if (TRUE == m_ARStartSuc)
	{		
		//Begin: Modify by li_deming(11517) 2008-1-14
		//UnInitAudioRecordEx();
		m_render->CloseAudioRecord();
		//End:li_deming(11517)
		m_ARStartSuc = FALSE;
	}

	if (m_render != NULL)
	{
		m_pManager->GetRenderManager().ReleaseRender(m_render);
		m_render = NULL;
	}

	if (m_hisEncodeHandle != 0) 
	{
		AMR_Encode_Exit(&m_hisEncodeHandle);
	}
/*
	if (AUDIO_RENDER_INDEX == m_irenderindex)
	{
		render_close(m_irenderindex);
		m_irenderindex = INVALID_RENDER_INDEX;
	}
*/
	
	return 0;
}

/*	$FXN :	StartTalk(LONG lLoginID, pfAudioDataCallBack pfcb, DWORD dwUser)
==	======================================================================
==	$DSC :	�������豸�ĶԽ���ʵ���˺��豸֮�佨���Խ�ͨ��
==	$ARG :	(in)lLoginID�����豸�ľ����(in)pfcbͨ�������豸�����ݺ�¼������(�����¼���Ļ�)�ص����û���
==		 :	(in)dwUser���û��Զ�����Ϣ
==	$RET :	-1 or 0��ʾʧ�ܣ����򷵻�һ��ע��ľ����ͨ�������������TalkSendData��StopTalk
==	$MOD :	2006-12-20		yehao(10857)		Create the Function
==	======================================================================
*/
LONG CTalk::StartTalk(LONG lLoginID, pfAudioDataCallBack pfcb, DWORD dwUser)
{
	afk_device_s *device = (afk_device_s *)lLoginID;

	int nTalkMode = 0;
	BOOL bServerMode = FALSE;
	AUDIO_ATTR_T stTalkEncodeType = {0};

	device->get_info(device, dit_talk_use_mode, &nTalkMode);
	bServerMode = nTalkMode==1? TRUE:FALSE;

	device->get_info(device, dit_talk_encode_type, &stTalkEncodeType);

	m_dwAudioEncodeType = INTERNEL_ENCODE_TYPE_8K8BPCM;
	m_FrameLength=1024;
	m_dwSampleRate = 8000;
	m_nAudioBit = 8;
	
	if (stTalkEncodeType.iAudioType == 0xFFFF)	// Ϊ�˼����ԣ�Ĭ�Ϸ�ʽ��ΪPCM
	{
		stTalkEncodeType.iAudioType = 0;
		int	bufLen = sizeof(DIALOG_CAPS)+16*sizeof(AUDIO_ATTR_T);
		char* capBuf = new char[bufLen];
		if (NULL == capBuf)
		{
			return NET_SYSTEM_ERROR;
		}
		
		int retlen = 0;
		int iRet = m_pManager->GetDevConfig().QuerySystemInfo(lLoginID, SYSTEM_INFO_TALK_ATTR, capBuf, bufLen, &retlen, QUERY_WAIT);
		if (iRet >= 0 && retlen >= sizeof(DIALOG_CAPS) && ((retlen-sizeof(DIALOG_CAPS))%sizeof(AUDIO_ATTR_T))==0) 
		{
			DIALOG_CAPS* pDialogCap = (DIALOG_CAPS*)capBuf;
			if (0 == pDialogCap->iAudioTypeNum)
			{
				delete[] capBuf;
				return NET_UNSUPPORTED;
			}
			AUDIO_ATTR_T* pAAT = NULL;
			for (int i = 0; i < pDialogCap->iAudioTypeNum; i++)
			{
				pAAT = (AUDIO_ATTR_T*)(capBuf+sizeof(DIALOG_CAPS)+i*sizeof(AUDIO_ATTR_T));
				
				if(1==pAAT->iAudioType && m_dwAudioEncodeType<INTERNEL_ENCODE_TYPE_8K16BNEWPCM)
				{
					//�豸֧�ִ�ͷ��Ϣ��PCM 8K 16 Bit
					m_dwAudioEncodeType = INTERNEL_ENCODE_TYPE_8K16BNEWPCM;
					m_FrameLength=1024;
					m_dwSampleRate = pAAT->dwSampleRate;
					m_nAudioBit = pAAT->iAudioBit;
				}
			}
		}
		
		if (capBuf != NULL)
		{
			delete[] capBuf;
			capBuf = NULL;
		}
	}
	else if (stTalkEncodeType.iAudioType == 0)
	{
		m_dwAudioEncodeType = INTERNEL_ENCODE_TYPE_8K8BPCM;
		m_FrameLength=1024;
		m_dwSampleRate = stTalkEncodeType.dwSampleRate;
		m_nAudioBit = stTalkEncodeType.iAudioBit;
	}
	else if (stTalkEncodeType.iAudioType == 1)
	{
		m_dwAudioEncodeType = INTERNEL_ENCODE_TYPE_8K16BNEWPCM;
		m_FrameLength=1024;
		m_dwSampleRate = stTalkEncodeType.dwSampleRate;
		m_nAudioBit = stTalkEncodeType.iAudioBit;
	}
	else if (stTalkEncodeType.iAudioType == 2)
	{
		m_dwAudioEncodeType = INTERNEL_ENCODE_TYPE_G711A8K16B;
		m_FrameLength=1280;
		m_dwSampleRate = stTalkEncodeType.dwSampleRate;
		m_nAudioBit = stTalkEncodeType.iAudioBit;
	}
	else if (stTalkEncodeType.iAudioType == 3)
	{
		m_dwAudioEncodeType = INTERNEL_ENCODE_TYPE_AMR8K16B;
		m_FrameLength=320;
		m_dwSampleRate = stTalkEncodeType.dwSampleRate;
		m_nAudioBit = stTalkEncodeType.iAudioBit;
	}
	else if (stTalkEncodeType.iAudioType == 4)
	{
		m_dwAudioEncodeType = INTERNEL_ENCODE_TYPE_G711U8K16B;
		m_FrameLength=320;
		m_dwSampleRate = stTalkEncodeType.dwSampleRate;
		m_nAudioBit = stTalkEncodeType.iAudioBit;
	}
	else if (stTalkEncodeType.iAudioType == 5)
	{
		m_dwAudioEncodeType = INTERNEL_ENCODE_TYPE_G7268K16B;
		m_FrameLength=320;
		m_dwSampleRate = stTalkEncodeType.dwSampleRate;
		m_nAudioBit = stTalkEncodeType.iAudioBit;
	}


	if (NULL == m_render) 
	{
		return NET_NO_TALK_CHANNEL;
	}

	if (!bServerMode)
	{
		if (m_render->StartDec(FALSE, 
			(INTERNEL_ENCODE_TYPE_8K16BNEWPCM==m_dwAudioEncodeType || INTERNEL_ENCODE_TYPE_G711A8K16B==m_dwAudioEncodeType || INTERNEL_ENCODE_TYPE_AMR8K16B==m_dwAudioEncodeType || INTERNEL_ENCODE_TYPE_G711U8K16B==m_dwAudioEncodeType || INTERNEL_ENCODE_TYPE_G7268K16B==m_dwAudioEncodeType) ? 2 : 1) < 0)
		{
			return NET_RENDER_SOUND_ON_ERROR;
		}
	}
	
	m_cs.Lock();

	LONG lRet = 0;
	list<LPTALKHANDLEINFO>::iterator it = m_talkhandlelist.begin();
	for (;it != m_talkhandlelist.end(); it++)
	{
		if ((*it)->lDevHandle == lLoginID)
		{
			m_cs.UnLock();
			return 0;
		}
	}

	afk_talk_channel_param_s talkchannelpar;
	LPTALKHANDLEINFO pstTalkInfo = NULL;
	pstTalkInfo = new TALKHANDLEINFO;
	if (NULL == pstTalkInfo)
	{
		lRet = NET_SYSTEM_ERROR;
		goto FAILED;
	}
	memset((void *)pstTalkInfo, 0, sizeof(TALKHANDLEINFO));
	memset((void *)&talkchannelpar, 0, sizeof(afk_channel_param_s));
	talkchannelpar.base.udata = (void *)pstTalkInfo;
	talkchannelpar.base.func = CTalk::TalkFunc;
	talkchannelpar.no = pstTalkInfo->iChannelId;
	talkchannelpar.nEncodeType = stTalkEncodeType.iAudioType==0?1:stTalkEncodeType.iAudioType;
	talkchannelpar.nAudioBit = stTalkEncodeType.iAudioBit;
	talkchannelpar.dwSampleRate = stTalkEncodeType.dwSampleRate;
	
	pstTalkInfo->pTalkChannel = (afk_channel_s *)device->open_channel(device, AFK_CHANNEL_TYPE_TALK, &talkchannelpar);
	if (NULL == pstTalkInfo->pTalkChannel)
	{
		lRet = NET_OPEN_CHANNEL_ERROR;
		goto FAILED;
	}
	pstTalkInfo->lDevHandle = lLoginID;
	pstTalkInfo->pfcb = pfcb;
	pstTalkInfo->dwUser = dwUser;
	m_talkhandlelist.push_back(pstTalkInfo);
	lRet = (LONG)pstTalkInfo;
	
	goto END;

FAILED:
	if (pstTalkInfo != NULL)
	{
		if (pstTalkInfo->pTalkChannel)
		{
			pstTalkInfo->pTalkChannel->close(pstTalkInfo->pTalkChannel);
		}
		delete pstTalkInfo;
	}

	if (!bServerMode)
	{
		if (m_render != NULL)
		{
			m_render->CloseAudio();
			m_render->StopDec();
		}
	}

END:
	m_cs.UnLock();
	return lRet;
}

/*	$FXN :	SetVolume(LONG lTalkHandle, WORD wVolume)
==	======================================================================
==	$DSC :	���������Խ��������������lTalkHandle��ͨ�������StartTalk�����ġ�
==	$ARG :	(in)lTalkHandle��Ȩ��ƾ֤���������StartTalk�ķ���ֵ��
==		 :	(in)wVolume��Ҫ���õ�����ֵ����Χ: 0 -- 0xFFFF, 0 ������С;
==	$RET :	�ɹ�����TRUE�����򷵻�FALSE
==	$MOD :	2006-12-20		yehao(10857)		Create the Function
==	======================================================================
*/
BOOL CTalk::SetVolume(LONG lTalkHandle, WORD wVolume)
{
//	EnterCriticalSection(&m_cs);
	m_cs.Lock();

	BOOL bRet = FALSE;
	list<LPTALKHANDLEINFO>::iterator it = m_talkhandlelist.begin();
	for (; it != m_talkhandlelist.end(); it++)
	{
		if (lTalkHandle == (LONG)(*it))
		{
			break;
		}
	}
	if (it == m_talkhandlelist.end())
	{
		m_pManager->SetLastError(NET_INVALID_HANDLE);
		bRet = FALSE;
		goto END;
	}
	
	if (NULL == m_render) 
	{
		m_pManager->SetLastError(NET_NO_TALK_CHANNEL);
		bRet = FALSE;
		goto END;
	}

	bRet = m_render->SetAudioVolume(wVolume);
	if (!bRet)
	{
		m_pManager->SetLastError(NET_RENDER_SET_VOLUME_ERROR);
		goto END;
	}
	/*
	if (m_irenderindex != AUDIO_RENDER_INDEX)
	{
		m_pManager->SetLastError(NET_SYSTEM_ERROR);
		bRet = FALSE;
		goto END;
	}
	*/
	/*
	DWORD dwVol;
	dwVol = ((0xFFFF*wVolume)/100 << 16 | (0xFFFF*wVolume)/100);
    if (render_set_volume(m_irenderindex, dwVol) >= 0)
	{
		bRet = TRUE;
		goto END;
	}
	*/
	//m_pManager->SetLastError(NET_ERROR);

END:
//	LeaveCriticalSection(&m_cs);
	m_cs.UnLock();
	return bRet;
}

/*	$FXN :	SendData2Dev(LONG lchannel, char *pSendBuf, DWORD dwBufSize)
==	======================================================================
==	$DSC :	��pSendBuf,ͨ��lchannel���͸��豸��������������Ϊ�˾ֲ����ܵ�ģ�黯��
==	$ARG :	(in)lchannel�������Խ���ͨ�������(in)pSendBuf��Ҫ���͵����ݵ�ַ��(in)dwBufSize��Ҫ���͵����ݳ���
==		 :	
==	$RET :	�ɹ����ط��͵����ݳ��ȣ�ʧ�ܷ���-1 or 0
==	$MOD :	2006-12-20		yehao(10857)		Create the Function
==	======================================================================
*/
LONG CTalk::SendData2Dev(afk_channel_s *pChannel, char *pSendBuf, DWORD dwBufSize)
{
	LONG lRet = 0;
	if (NULL == pChannel || NULL == pSendBuf || 0 == dwBufSize)
	{
		m_pManager->SetLastError(NET_ILLEGAL_PARAM);
		return -1;
	}
	struct afk_talk_info_s tempst;
	tempst.data = pSendBuf;
	tempst.datalen = dwBufSize;
	if (1 == pChannel->set_info(pChannel, 0, &tempst))
	{
		lRet = dwBufSize;
	}

	return lRet;
}

/*	$FXN :	TalkSendData(LONG lTalkHandle, char *pSendBuf, DWORD dwBufSize)
==	======================================================================
==	$DSC :	�����û�������Ҫ�������ݵ��豸��
==	$ARG :	(in)lTalkHandle������ע��������Խ��ľ����(in)pSendBuf��Ҫ���͵����ݵ�ַ��(in)dwBufSize��Ҫ���͵����ݳ���
==		 :	
==	$RET :	�ɹ����ط��͵����ݳ��ȣ�ʧ�ܷ���-1 or 0
==	$MOD :	2006-12-20		yehao(10857)		Create the Function
==	======================================================================
*/
LONG CTalk::TalkSendData(LONG lTalkHandle, char *pSendBuf, DWORD dwBufSize)
{
	m_cs.Lock();

	LONG lRet = 0;
	list<LPTALKHANDLEINFO>::iterator it = m_talkhandlelist.begin();
	for (; it != m_talkhandlelist.end(); it++)
	{
		if ((LONG)(*it) == lTalkHandle)
		{
			break;
		}
	}
	if (it == m_talkhandlelist.end() || NULL == (*it))
	{
		m_pManager->SetLastError(NET_INVALID_HANDLE);
		lRet = -1;
		goto END;
	}
	lRet = SendData2Dev((*it)->pTalkChannel, pSendBuf, dwBufSize);

END:
	m_cs.UnLock();
	
	return lRet;
}

/*	$FXN :	RecordStart()
==	======================================================================
==	$DSC :	��������¼������
==	$ARG :	
==		 :	
==	$RET :	�ɹ�����TRUE,ʧ�ܷ���FALSE
==	$MOD :	2006-12-20		yehao(10857)		Create the Function
==	======================================================================
*/
BOOL CTalk::RecordStart()
{
//	EnterCriticalSection(&m_cs);
	m_cs.Lock();
	//Begin: Modify by li_deming(11517) 2008-1-14
	
	/*
	if (FALSE == m_ARStartSuc) 
		{
			if (InitAudioRecordEx(m_AudioFormat) == 1)
			{
				m_ARStartSuc = TRUE;
			}
		}
	
		BOOL bRet = FALSE;
		if (FALSE == m_ARStartSuc)
		{
			m_pManager->SetLastError(NET_TALK_INIT_ERROR);
			bRet = FALSE;
			goto END;
		}
		if (NULL == m_RecordHandle)
		{
			m_RecordHandle = OpenAudioRecordEx(CTalk::RecordFunc, (int)this);
			if (m_RecordHandle != NULL)
			{
				bRet = TRUE;
				goto END;
			}
		}
		else
		{
			bRet = TRUE;
			goto END;
		}
		
		m_pManager->SetLastError(NET_ERROR);*/
	
	BOOL bRet = FALSE;
	m_ARStartSuc=FALSE;
	bRet=m_render->OpenAudioRecord(CTalk::RecordFunc,m_nAudioBit,m_dwSampleRate,m_FrameLength,0,(long)this);	
	if(TRUE==bRet)
	{
		m_ARStartSuc=TRUE;
		goto END;
	}	
	m_pManager->SetLastError(NET_ERROR);
	//End:li_deming(11517)	
END:

//	LeaveCriticalSection(&m_cs);
	m_cs.UnLock();
	return bRet;
}

/*	$FXN :	RecordStop()
==	======================================================================
==	$DSC :	ֹͣ����¼������
==	$ARG :	
==		 :	
==	$RET :	�ɹ�����TRUE,ʧ�ܷ���FALSE
==	$MOD :	2006-12-20		yehao(10857)		Create the Function
==	======================================================================
*/
BOOL CTalk::RecordStop()
{
//	EnterCriticalSection(&m_cs);
	m_cs.Lock();

	BOOL bRet = FALSE;
	//Begin: Modify by li_deming(11517) 2008-1-14
	/*	
		if (FALSE == m_ARStartSuc)
		{
			m_pManager->SetLastError(NET_TALK_INIT_ERROR);
			bRet = FALSE;
			goto END;
		}
		if (NULL == m_RecordHandle)
		{
			m_pManager->SetLastError(NET_ERROR);
			bRet = FALSE;
		}
		else
		{
			if (CloseAudioRecordEx(m_RecordHandle) != 1)
			{
				m_pManager->SetLastError(NET_ERROR);
				bRet = FALSE;
				goto END;
			}
			m_RecordHandle = NULL;
			bRet = TRUE;
		}
		
	END:
		if (TRUE == m_ARStartSuc)
		{
			UnInitAudioRecordEx();
			m_ARStartSuc = FALSE;
		}*/
	
	//End:li_deming(11517)	
//	LeaveCriticalSection(&m_cs);
	if(TRUE==m_ARStartSuc)
	{
		bRet=m_render->CloseAudioRecord();
	}
	m_cs.UnLock();
	return bRet;
}

/*	$FXN :	AudioDec(char *pAudioDataBuf, DWORD dwBufSize)
==	======================================================================
==	$DSC :	ʵ����Ƶ���ݽ���
==	$ARG :	(in)pAudioDataBuf��Ҫ�������Ƶ���ݣ�(in)dwBufSize����Ƶ���ݵĳ���
==		 :	
==	$RET :	
==	$MOD :	2006-12-20		yehao(10857)		Create the Function
==	======================================================================
*/
void CTalk::AudioDec(char *pAudioDataBuf, DWORD dwBufSize)
{
	if (NULL == m_render)
	{
		return;
	}

	/*
	static FILE* f = NULL;
	if (f == NULL)
	{
		f = fopen("e:\\savetalk.dav", "wb");
		if (f == NULL)
		{
			DWORD dw = GetLastError();
			OutputDebugString("damen!\n");
		}
	}
	if (f != NULL)
	{
		fwrite(pAudioDataBuf, 1, dwBufSize, f);
	}
*/
	if (INTERNEL_ENCODE_TYPE_8K8BPCM == m_dwAudioEncodeType)
	{
		for (int i = 0; i < dwBufSize; i++)
		{
			pAudioDataBuf[i] += 128;
		}
	}
/*
	//test
	static FILE* f = NULL;
	if (f == NULL)
	{
		f = fopen("e:\\savetalk.pcm", "wb");
		if (f == NULL)
		{
			DWORD dw = GetLastError();
			OutputDebugString("damen!\n");
		}
	}
	if (f != NULL)
	{
		fwrite(pAudioDataBuf, 1, dwBufSize, f);
	}
*/

	m_render->Play((BYTE*)pAudioDataBuf, dwBufSize);
	/*
	if (AUDIO_RENDER_INDEX == m_irenderindex)
	{
		render_audio(m_irenderindex, (unsigned char *)pAudioDataBuf, dwBufSize, 8, 8000);
	}
	*/
}

/*	$FXN :	StopTalk(LONG lTalkHandle)
==	======================================================================
==	$DSC :	ֹͣ���豸֮��ĶԽ�����
==	$ARG :	(in)lTalkHandle�������Խ�ʱ�õ��ĶԽ����
==		 :	
==	$RET :	�ɹ�����TRUE�����򷵻�FALSE
==	$MOD :	2006-12-20		yehao(10857)		Create the Function
==	======================================================================
*/
BOOL CTalk::StopTalk(LONG lTalkHandle)
{
	m_cs.Lock();
	
	BOOL bRet = TRUE;
	list<LPTALKHANDLEINFO>::iterator it = m_talkhandlelist.begin();
	for (; it != m_talkhandlelist.end(); it++)
	{
		if ((LONG)(*it) == lTalkHandle)
		{
			break;
		}
	}
	if (it == m_talkhandlelist.end())
	{
		bRet = FALSE;
		m_pManager->SetLastError(NET_ERROR);
		goto END;
	}
	if (*it)
	{
		if ((*it)->pTalkChannel)
		{
			(*it)->pTalkChannel->close((*it)->pTalkChannel);
		}
		delete (*it);
	}
	m_talkhandlelist.erase(it);

	if (m_render != NULL)
	{
		if (m_render->StopDec() < 0)
		{
#ifdef DEBUG
			OutputDebugString("stop dec while stop talk failed!\n");
#endif
		}

		if (!m_render->CloseAudio())
		{
#ifdef DEBUG
			OutputDebugString("stop dec while stop talk failed!\n");
#endif
		}
	}
	
END:
	m_cs.UnLock();
	return bRet;
}

/*	$FXN :	AddDev(LONG lLoginID)
==	======================================================================
==	$DSC :	���豸���ӵ��㲥�飬�ڱ��زɼ��������ݣ�ģ����Զ��ط��͸��㲥���е��豸
==	$ARG :	(in)lLoginID���豸�ľ��
==		 :	
==	$RET :	�ɹ�����TRUE�����򷵻�FALSE
==	$MOD :	2006-12-20		yehao(10857)		Create the Function
==	======================================================================
*/
BOOL CTalk::BroadcastAddDev(LONG lLoginID)
{
	if (m_pManager->IsDeviceValid((afk_device_s *)lLoginID) < 0)
    {
		m_pManager->SetLastError(NET_INVALID_HANDLE);
        return FALSE;
    }
	
//	EnterCriticalSection(&m_cs);
	m_cs.Lock();

	list<LPTALKBROADCASTINFO>::iterator it = m_broadcastlist.begin();
	for (; it != m_broadcastlist.end(); it++)
	{
		if ((*it)->lDevHandle == lLoginID)
		{
//			LeaveCriticalSection(&m_cs);
			m_cs.UnLock();
			m_pManager->SetLastError(NET_ERROR);
			return FALSE;
		}
	}

	BOOL bRet = FALSE;
	afk_device_s *device = (afk_device_s *)lLoginID;
	afk_talk_channel_param_s talkchannelpar;
	LPTALKBROADCASTINFO ptmpinfo = NULL;
	ptmpinfo = new TALKBROADCASTINFO;
	if (NULL == ptmpinfo)
	{
		m_pManager->SetLastError(NET_SYSTEM_ERROR);
		goto FAILED;
	}
	memset((void *)ptmpinfo, 0, sizeof(TALKBROADCASTINFO));
	memset((void *)&talkchannelpar, 0, sizeof(afk_talk_channel_param_s));
	talkchannelpar.base.udata = (void *)ptmpinfo;
	talkchannelpar.base.func = NULL;
	talkchannelpar.no = ptmpinfo->iChannelId;
	ptmpinfo->pTalkChannel = (afk_channel_s *)device->open_channel(device, AFK_CHANNEL_TYPE_TALK, &talkchannelpar);
	if (NULL == ptmpinfo->pTalkChannel)
	{
		m_pManager->SetLastError(NET_OPEN_CHANNEL_ERROR);
		goto FAILED;
	}
	ptmpinfo->lDevHandle = lLoginID;
	m_broadcastlist.push_back(ptmpinfo);
	bRet = TRUE;
	goto END;

FAILED:
	bRet = FALSE;
	if (ptmpinfo != NULL)
	{
		if (ptmpinfo->pTalkChannel)
		{
			ptmpinfo->pTalkChannel->close(ptmpinfo->pTalkChannel);
		}
		delete ptmpinfo;
	}
END:
//	LeaveCriticalSection(&m_cs);
	m_cs.UnLock();
	return bRet;
}

/*	$FXN :	DelDev(LONG lLoginID)
==	======================================================================
==	$DSC :	��AddDev(LONG lLoginID)����ԵĹ���
==	$ARG :	(in)lLoginID���豸�ľ��
==		 :	
==	$RET :	�ɹ�����TRUE�����򷵻�FALSE
==	$MOD :	2006-12-20		yehao(10857)		Create the Function
==	======================================================================
*/
BOOL CTalk::BroadcastDelDev(LONG lLoginID)
{
//	EnterCriticalSection(&m_cs);
	m_cs.Lock();
	
	BOOL bRet = FALSE;
	list<LPTALKBROADCASTINFO>::iterator it = m_broadcastlist.begin();
	for (; it != m_broadcastlist.end(); it++)
	{
		if ((*it) && (*it)->lDevHandle == lLoginID)
		{
			if ((*it)->pTalkChannel)
			{
				(*it)->pTalkChannel->close((*it)->pTalkChannel);
			}
			delete (*it);
			m_broadcastlist.erase(it);
			break;
		}
	}
	if (m_broadcastlist.end() == it)
	{
		m_pManager->SetLastError(NET_ERROR);
		bRet = FALSE;
	}
//	LeaveCriticalSection(&m_cs);
	m_cs.UnLock();
	return bRet;
}

/*	$FXN :	InitAudioEncode(AUDIO_FORMAT aft)
==	======================================================================
==	$DSC :	��Ƶ�����ʼ��(��׼��ʽ->���ܸ�ʽ)
==	$ARG :	[in]aft����ʾ����Ҫ�����ԭʼ���ݵ���Ƶ��ʽ��
==		 :	
==	$RET :	�ɹ�����0,ʧ�ܷ��ش�����
==	$MOD :	2007-03-20		yehao(10857)		Create the Function
==	======================================================================
*/
int CTalk::InitAudioEncode(AUDIO_FORMAT aft)
{
	if (aft.byFormatTag != 0 || aft.nChannels != 1 || aft.wBitsPerSample != 16 || aft.nSamplesPerSec != 8000)
	{
		m_iEncodeFlag = 0;
		m_pManager->SetLastError(NET_ILLEGAL_PARAM);
		return NET_ILLEGAL_PARAM;
	}

	m_iEncodeFlag = 1;
	return 0;
}

/*	$FXN :	AudioEncode(LONG lHandle, BYTE *lpInBuf, DWORD *lpInLen, BYTE *lpOutBuf, DWORD *lpOutLen)
==	======================================================================
==	$DSC :	������Ƶ���ݱ���
==	$ARG :	[in]lHandle�������Խ��ľ����//Ŀǰû����
==     	 :	[in]lpInBuf��Ҫ���б����Դ���ݣ�
==     	 :	[in,out]lpInBuf������ʱ�������lpInBuf�����ݳ��ȣ����÷���ʱ�ǳɹ���������ݳ��ȣ�
==     	 :	[out]lpOutBuf�������洢��������Ƶ���ݣ�
==     	 :	[in,out]lpOutLen������ʱ����lpOutBuf����󳤶ȣ������Ƶ���峤�Ȳ����ʧ��ʱlpOutLen��ʾҪ������ݳ��ȣ��ɹ�����ʱ��ʾlpOutBuf��Ч���ݳ��ȣ�
==		 :	
==	$RET :	�ɹ�����0,ʧ�ܷ��ش�����
==	$MOD :	2006-12-20		yehao(10857)		Create the Function
==	======================================================================
*/
int	CTalk::AudioEncode(LONG lHandle, BYTE *lpInBuf, DWORD *lpInLen, BYTE *lpOutBuf, DWORD *lpOutLen)
{
	if (0 == m_iEncodeFlag)
	{
		m_pManager->SetLastError(NET_AUDIOENCODE_NOTINIT);
		return NET_AUDIOENCODE_NOTINIT;
	}
	if (NULL == lpInBuf || NULL == lpInLen || NULL == lpOutBuf || NULL == lpOutLen || 0 == *lpInLen)
	{
		m_pManager->SetLastError(NET_ILLEGAL_PARAM);
		return NET_ILLEGAL_PARAM;
	}
	if (*lpInLen >= MAX_ENCODE_LEN*2)
	{
		*lpInLen = MAX_ENCODE_LEN*2;
		m_pManager->SetLastError(NET_DATA_TOOLONGH);
		return NET_DATA_TOOLONGH;
	}
	if (*lpOutLen < (*lpInLen/2 + 8))
	{
		*lpOutLen = *lpInLen/2 + 8;
		m_pManager->SetLastError(NET_INSUFFICIENT_BUFFER);
		return NET_INSUFFICIENT_BUFFER;
	}
	
	int iRet = 0;
	int iCount = 0;
	int iDataLen = (*lpInLen>>1);
	unsigned short *p16 = (unsigned short *)lpInBuf;
	lpOutBuf[iCount++] = 0x00;
	lpOutBuf[iCount++] = 0x00;
	lpOutBuf[iCount++] = 0x01;
	lpOutBuf[iCount++] = 0xf0;
	lpOutBuf[iCount++] = 0x07;
	lpOutBuf[iCount++] = 0x02;
	*(unsigned short *)(lpOutBuf+iCount) = (unsigned short)iDataLen;
	iCount += 2;
	for (int i = 0; i < iDataLen; i++)
	{
		lpOutBuf[iCount++] = BYTE(*p16>>8);
		p16++;
	}
	*lpOutLen = iCount;	
	*lpInLen = 0;
	
	return iRet;
}

/*	$FXN :	ReleaseAudioEncode(LONG lHandle)
==	======================================================================
==	$DSC :	��Ƶ��������˳�
==	$ARG :	
==		 :	
==	$RET :	�ɹ�����0,ʧ�ܷ��ط���Ĵ�����
==	$MOD :	2007-03-20		yehao(10857)		Create the Function
==	======================================================================
*/
int CTalk::ReleaseAudioEncode()
{
//	EnterCriticalSection(&m_cs);
	m_cs.Lock();
	m_iEncodeFlag = 0;
//	LeaveCriticalSection(&m_cs);
	m_cs.UnLock();
	return 0;
}

/*	$FXN :	InitAudioDecode(AUDIO_FORMAT aft)
==	======================================================================
==	$DSC :	��Ƶ����ĳ�ʼ��(���ܸ�ʽ->��׼��ʽ)
==	$ARG :	[in]aft��Ҫת����Ŀ����Ƶ��ʽ��
==		 :	
==	$RET :	�ɹ�������Ч���,ʧ�ܷ�����Ч���
==	$MOD :	2007-03-20		yehao(10857)		Create the Function
==	======================================================================
*/
LONG CTalk::InitAudioDecode(AUDIO_FORMAT aft)
{
	LONG lRet = (LONG)INVALID_HANDLE_VALUE;

	return lRet;
}

/*	$FXN :	AudioDecode(LONG lHandle, BYTE *lpInBuf, DWORD *lpInLen, BYTE *lpOutBuf, DWORD *lpOutLen)
==	======================================================================
==	$DSC :	�������ݽ���
==	$ARG :	[in]lHandle����ֵ��������ĳ�ʼ���ķ���ֵ��
==     	 :	[in]lpInBuf��Ҫ������ԭ��Ƶ���ݣ�
==		 :	[in,out]lpInLen������ʱ��ʾlpInBuf�ĳ��ȣ�����ʱ��ֵ��û����ɽ�������ݳ��ȣ�
==		 :	[in]lpOutBuf��������Ž�������Ƶ���ݣ�
==		 :	[in,out]lpOutLen������ʱ��ʾlpOutBuf�Ļ�����󳤶ȣ������Ƶ���峤�Ȳ����ʧ��ʱlpOutLen��ʾҪ������ݳ��ȣ��ɹ�����ʱ��ʾlpOutBuf��Ч���ݳ��ȣ�
==		 :	
==	$RET :	�ɹ�����0,ʧ�ܷ��ط���Ĵ�����
==	$MOD :	2007-03-20		yehao(10857)		Create the Function
==	======================================================================
*/
int CTalk::AudioDecode(LONG lHandle, BYTE *lpInBuf, DWORD *lpInLen, BYTE *lpOutBuf, DWORD *lpOutLen)
{
	int iRet = 0;

	return iRet;
}

/*	$FXN :	ReleaseAudioDecode(LONG lHandle)
==	======================================================================
==	$DSC :	��ɽ��룬�˳�
==	$ARG :	[in]lHandle������ĳ�ʼ���ӿڵķ���ֵ��
==		 :	
==	$RET :	�ɹ�����0,ʧ�ܷ��ط���Ĵ�����
==	$MOD :	2007-03-20		yehao(10857)		Create the Function
==	======================================================================
*/
int CTalk::ReleaseAudioDecode(LONG lHandle)
{
	int iRet = 0;

	return iRet;
}

/*	$FXN :	CloseChannelOfDevice(afk_device_s * pdev)
==	======================================================================
==	$DSC :	�رպ�pdev�豸��ص�����ͨ��
==	$ARG :	[in]pdev,�������豸
==		 :	
==	$RET :	�ɹ�����0,ʧ�ܷ��ط���Ĵ�����
==	$MOD :	2006-12-20		yehao(10857)		Create the Function
==	======================================================================
*/
int CTalk::CloseChannelOfDevice(afk_device_s * pdev)
{
//	EnterCriticalSection(&m_cs);
	m_cs.Lock();
	
	int iRet = 0;
	{
		list<LPTALKHANDLEINFO>::iterator it = m_talkhandlelist.begin();
		for (; it != m_talkhandlelist.end(); it++)
		{
			if ((*it)->lDevHandle == LONG(pdev))
			{
				if ((*it)->pTalkChannel != NULL)
				{
					(*it)->pTalkChannel->close((*it)->pTalkChannel);
				}
				delete (*it);
				m_talkhandlelist.erase(it);
				break;
			}
		}
	}
	{
		list<LPTALKBROADCASTINFO>::iterator it = m_broadcastlist.begin();
		for (; it != m_broadcastlist.end(); it++)
		{
			if ((*it)->lDevHandle == LONG(pdev))
			{
				if ((*it)->pTalkChannel != NULL)
				{
					(*it)->pTalkChannel->close((*it)->pTalkChannel);
				}
				delete (*it);
				m_broadcastlist.erase(it);
				break;
			}
		}
	}

//	LeaveCriticalSection(&m_cs);
	m_cs.UnLock();
	return iRet;
}

/*	$FXN :	TalkFunc(...)
==	======================================================================
==	$DSC :	�򿪺��豸�ĶԽ�ͨ��ʱע��Ļص�����
==	$ARG :	
==		 :	
==	$RET :	
==	$MOD :	2006-12-20		yehao(10857)		Create the Function
==	======================================================================
*/
int WINAPI CTalk::TalkFunc(
						   afk_handle_t object,  
						   unsigned char *data, 
						   unsigned int datalen,  
						   void *param,  
						   void *udata)
{
	LPTALKHANDLEINFO pTalkHandle = (LPTALKHANDLEINFO)udata;
	if (pTalkHandle == NULL || 0 == datalen)
	{
		return -1;
	}

	if (pTalkHandle->pfcb)
	{
		pTalkHandle->pfcb((LONG)pTalkHandle, (char *)data, datalen, 1, pTalkHandle->dwUser);
	}
	
	return 0;
}

/*	$FXN :	RecordFunc(LPBYTE pDataBuffer, DWORD DataLength, int user)
==	======================================================================
==	$DSC :	ע��¼����ʱ��ע��ص������������г��˰���Ƶ���ݻص����Խ��û��⣬�����͸��㲥���е��豸��
==	$ARG :	(in)pDataBuffer��¼����Ƶ���ݣ�(in)����Ƶ���ݳ���,(in)ע��¼����ʱ���û��Զ�����Ϣ
==		 :	
==	$RET :	
==	$MOD :	2006-12-20		yehao(10857)		Create the Function
==	======================================================================
*/
//Begin: Modify by li_deming(11517) 2008-1-14
//void WINAPI CTalk::RecordFunc(LPBYTE pDataBuffer, DWORD DataLength, int user)
void WINAPI CTalk::RecordFunc(LPBYTE pDataBuffer, DWORD DataLength, long user)
//End:li_deming(11517)
{

/*
	//test
	static FILE* ff = NULL;
	int jjj = 0;
	if (ff == NULL)
	{
		ff = fopen("e:\\savetalk1.pcm", "wb");
		if (ff == NULL)
		{
			DWORD dw = GetLastError();
			OutputDebugString("damen!\n");
		}
	}
	
	if (ff != NULL)
	{
		fwrite(pDataBuffer, 1, DataLength, ff);
	}
	
*/	
	if (NULL == pDataBuffer || 0 == DataLength)
	{
		return;
	}
	CTalk *ptalk = (CTalk *)user;
	if (NULL == ptalk)
	{
		return;
	}

	char* pCbData = NULL;
	pCbData = new char[DataLength+100]; //���˵�������ԭ�������ݻ������ҡ���
	if (NULL == pCbData) 
	{
		return;
	}
	int  iCbLen = 0;
	
	if ((ptalk->GetAudioEncodeType() == INTERNEL_ENCODE_TYPE_8K8BPCM) || (ptalk->GetAudioEncodeType() == INTERNEL_ENCODE_TYPE_8K16BNEWPCM)) 
	{
		if (ptalk->GetAudioEncodeBit() == 8)
		{
			for( int j = 0 ; j < DataLength; j++)
			{
				*(pDataBuffer + j) += 128;
			}
		}

		pCbData[0]=0x00;
		pCbData[1]=0x00;
		pCbData[2]=0x01;
		pCbData[3]=0xF0;
		
		pCbData[4]= 8 == ptalk->GetAudioEncodeBit() ? 0x07:0x0C;	//pcm8:0x07; pcm16:0x0C
		pCbData[5]=0x02;//8k
		*(DWORD*)(pCbData+6)=DataLength;
		memcpy(pCbData+8, pDataBuffer, DataLength);
		
		iCbLen = 8+DataLength;
		/*
		//��16bitת��8bit
		iCbLen = DataLength+8;

		DWORD dwRecordDataSize = DataLength;
		unsigned short *p16 = (unsigned short *)pDataBuffer;
		BYTE *pu8 = (BYTE *)pDataBuffer;
		int i = 0;

		dwRecordDataSize = DataLength>>1;
		
		while(dwRecordDataSize>0)
		{
			pCbData[i++]=0x00;
			pCbData[i++]=0x00;
			pCbData[i++]=0x01;
			pCbData[i++]=0xF0;
			
			pCbData[i++]=0x07;//pcm8
			pCbData[i++]=0x02;//8k
			
			if(dwRecordDataSize>=1024)
			{
				pCbData[i++]=0x00;
				pCbData[i++]=0x04;
				
				for(int j=0;j<1024;j++)
				{
					pCbData[i++]=BYTE(*p16>>8);
					p16++;
				}
				dwRecordDataSize-=1024;
			}
			else
			{
				pCbData[i++]=BYTE(dwRecordDataSize&0xff);
				pCbData[i++]=BYTE(dwRecordDataSize>>8);
				for(int j=0;j<(int)dwRecordDataSize;j++)
				{		
					pCbData[i++]=BYTE(*p16>>8);
					p16++;
				}
				dwRecordDataSize=0;
			}
			iCbLen = i;
		}
		*/
	}
	else if (ptalk->GetAudioEncodeType() == INTERNEL_ENCODE_TYPE_G711A8K16B)
	{		
		if (g711a_Encode((char*)pDataBuffer, pCbData+8, DataLength, &iCbLen) != 1)
		{
			delete pCbData;
			return;
		}
		
		//����������ʽ֡ͷ
		pCbData[0]=0x00;
		pCbData[1]=0x00;
		pCbData[2]=0x01;
		pCbData[3]=0xF0;

		pCbData[4]=0x0E; //G711A
		pCbData[5]=0x02;
		pCbData[6]=BYTE(iCbLen&0xff);
		pCbData[7]=BYTE(iCbLen>>8);
		
		iCbLen += 8;
	
	}
	else if (ptalk->GetAudioEncodeType() == INTERNEL_ENCODE_TYPE_AMR8K16B)
	{
		//AMR encode
		iCbLen = AMR_Encode_Frame(ptalk->GetHisEncodeHandle(),(HI_S16*)pDataBuffer,
			(HI_U8*)(pCbData+8),MR102,MIME);
		if (iCbLen <= 0)
		{
			delete pCbData;
			return;
		}
		
		pCbData[0]=0x00;
		pCbData[1]=0x00;
		pCbData[2]=0x01;
		pCbData[3]=0xF0;
		
		pCbData[4]=0x14; //AMR
		pCbData[5]=0x02;
		pCbData[6]=BYTE(iCbLen&0xff);
		pCbData[7]=BYTE(iCbLen>>8);

		iCbLen += 8;
	}
	else if (ptalk->GetAudioEncodeType() == INTERNEL_ENCODE_TYPE_G711U8K16B)
	{
		if (g711u_Encode((char*)pDataBuffer, pCbData+8, DataLength, &iCbLen) != 1)
		{
			delete pCbData;
			return;
		}

		//����������ʽ֡ͷ
		pCbData[0]=0x00;
		pCbData[1]=0x00;
		pCbData[2]=0x01;
		pCbData[3]=0xF0;

		pCbData[4]=0x0A; //G711u
		pCbData[5]=0x02;
		pCbData[6]=BYTE(iCbLen&0xff);
		pCbData[7]=BYTE(iCbLen>>8);
		
		iCbLen += 8;
	}
	else
	{
		return;
	}
/*
		//test
	
		static FILE* ff2 = NULL;
		if (ff2 == NULL)
		{
		ff2 = fopen("e:\\savetalk-enc.pcm", "wb");
		if (ff2 == NULL)
		{
		DWORD dw = GetLastError();
		OutputDebugString("damen!\n");
		}
		}
		
		if (ff2 != NULL)
		{
		 fwrite(pCbData, 1, iCbLen, ff2);
		}
	
*/
	
//	EnterCriticalSection(&ptalk->m_cs);
	ptalk->m_cs.Lock();

	{
		list<LPTALKHANDLEINFO>::iterator it = ptalk->m_talkhandlelist.begin();
		for (; it != ptalk->m_talkhandlelist.end(); it++)
		{
			if (*it && (*it)->pfcb)
			{
				(*it)->pfcb(LONG(*it), pCbData, iCbLen, 0, (*it)->dwUser);
				//(*it)->pfcb(LONG(*it), newdata, DataLength+8, 0, (*it)->dwUser);
			}
		}
	}
	
	{
		list<LPTALKBROADCASTINFO>::iterator it = ptalk->m_broadcastlist.begin();
		for (; it != ptalk->m_broadcastlist.end(); it++)
		{
			if ((*it) && (*it)->pTalkChannel)
			{
				ptalk->SendData2Dev(((*it)->pTalkChannel), pCbData, iCbLen);
			}
		}
	}
//	LeaveCriticalSection(&ptalk->m_cs);
	ptalk->m_cs.UnLock();

	delete[] pCbData;
}
#else	//linux

CTalk::CTalk(CManager &man):m_man(man)
{
	m_ARStartSuc = FALSE;
	
	m_iEncodeFlag = 0;
	m_render = NULL;
	
	m_hisEncodeHandle = 0;
	m_hisDecodeHandle = 0;
}
CTalk::~CTalk()
{
}
int CTalk::Init()
{
	{
		list<LPTALKHANDLEINFO>::iterator it = m_talkhandlelist.begin();
		for (; it != m_talkhandlelist.end(); it++)
		{
			if (*it)
			{
				if ((*it)->pTalkChannel)
				{
					(*it)->pTalkChannel->close((*it)->pTalkChannel);
				}
				delete (*it);
			}
		}
		m_talkhandlelist.clear();
	}
	
	{
		list<LPTALKBROADCASTINFO>::iterator it = m_broadcastlist.begin();
		for (; it != m_broadcastlist.end(); it++)
		{
			if (*it)
			{
				if ((*it)->pTalkChannel)
				{
					(*it)->pTalkChannel->close((*it)->pTalkChannel);
				}
				delete (*it);
			}
		}
		m_broadcastlist.clear();
	}
	
	m_ARStartSuc = FALSE;
	m_dwAudioEncodeType = INTERNEL_ENCODE_TYPE_8K8BPCM;
	m_render = m_pManager->GetRenderManager().GetRender((HWND)0xFFFFFFFF);
	if (0 == (int)m_render || -1 == (int)m_render)
	{
		m_render = NULL;
	}
	m_iEncodeFlag = 0;

	return 0;
}

int CTalk::UnInit()
{
//	EnterCriticalSection(&m_cs);
	m_cs.Lock();
	{
		list<LPTALKHANDLEINFO>::iterator it = m_talkhandlelist.begin();
		for (; it != m_talkhandlelist.end(); it++)
		{
			if (*it)
			{
				if ((*it)->pTalkChannel)
				{
					(*it)->pTalkChannel->close((*it)->pTalkChannel);
				}
				delete (*it);
			}
		}
		m_talkhandlelist.clear();
	}
	
	{
		list<LPTALKBROADCASTINFO>::iterator it = m_broadcastlist.begin();
		for (; it != m_broadcastlist.end(); it++)
		{
			if (*it)
			{
				if ((*it)->pTalkChannel)
				{
					(*it)->pTalkChannel->close((*it)->pTalkChannel);
				}
				delete (*it);
			}
		}
		m_broadcastlist.clear();
	}
	
//	LeaveCriticalSection(&m_cs);
	m_cs.UnLock();
	
	
	if (m_render != NULL)
	{
		m_pManager->GetRenderManager().ReleaseRender(m_render);
		m_render = NULL;
	}
	
	return 0;
}

LONG CTalk::StartTalk(LONG lLoginID, pfAudioDataCallBack pfcb, DWORD dwUser)
{	
	if (m_pManager->IsDeviceValid((afk_device_s *)lLoginID) < 0)
    {
		m_pManager->SetLastError(NET_INVALID_HANDLE);
        return 0;
    }
	
	afk_device_s *device = (afk_device_s *)lLoginID;

	int nTalkMode = 0;
	BOOL bServerMode = FALSE;

	device->get_info(device, dit_talk_use_mode, &nTalkMode);
	bServerMode = nTalkMode==1? TRUE:FALSE;

	//�Ȳ�ѯ�豸֧�ֵ���Ƶ�����ʽ
	int	bufLen = sizeof(DIALOG_CAPS)+16*sizeof(AUDIO_ATTR_T);
	char* capBuf = new char[bufLen];
	if (NULL == capBuf)
	{
		m_pManager->SetLastError(NET_SYSTEM_ERROR);
		return FALSE;
	}
	
	int retlen = 0;
	int iRet = m_pManager->GetDevConfig().QuerySystemInfo(lLoginID, SYSTEM_INFO_TALK_ATTR, capBuf, bufLen, &retlen, QUERY_WAIT);
	if (iRet >= 0 && retlen >= sizeof(DIALOG_CAPS) && ((retlen-sizeof(DIALOG_CAPS))%sizeof(AUDIO_ATTR_T))==0) 
	{
		DIALOG_CAPS* pDialogCap = (DIALOG_CAPS*)capBuf;
		if (0 == pDialogCap->iAudioTypeNum)
		{
			int tecType = 0;
			device->set_info(device, dit_talk_encode_type, &tecType);
			
			delete capBuf;
			m_pManager->SetLastError(NET_UNSUPPORTED);
			return FALSE;
		}
		AUDIO_ATTR_T* pAAT = NULL;
		for (int i = 0; i < pDialogCap->iAudioTypeNum; i++)
		{
			pAAT = (AUDIO_ATTR_T*)(capBuf+sizeof(DIALOG_CAPS)+i*sizeof(AUDIO_ATTR_T));
			if (2 == pAAT->iAudioType && 16 == pAAT->iAudioBit && 8000 == pAAT->dwSampleRate
				&& m_dwAudioEncodeType < INTERNEL_ENCODE_TYPE_G711A8K16B) 
			{
				//�豸֧��G711 8K 16 Bit
				m_dwAudioEncodeType = INTERNEL_ENCODE_TYPE_G711A8K16B;
			//	m_AudioFormat.dwFrameLen = 320;
				int tecType = 2;
				device->set_info(device, dit_talk_encode_type, &tecType);
			}

			if (3 == pAAT->iAudioType && 16 == pAAT->iAudioBit && 8000 == pAAT->dwSampleRate
				&& m_dwAudioEncodeType < INTERNEL_ENCODE_TYPE_AMR8K16B)
			{
				//�豸֧��AMR 8K 16 Bit
				m_dwAudioEncodeType = INTERNEL_ENCODE_TYPE_AMR8K16B;		
		//		m_AudioFormat.dwFrameLen = 320;		
				int tecType = 3;
				device->set_info(device, dit_talk_encode_type, &tecType);
			}
		}
	}

	delete capBuf;

	if (NULL == m_render) 
	{
		m_pManager->SetLastError(NET_NO_TALK_CHANNEL);
		return 0;
	}

	if (!bServerMode)
	{
		if (m_render->StartDec(FALSE, 
			(INTERNEL_ENCODE_TYPE_G711A8K16B==m_dwAudioEncodeType || INTERNEL_ENCODE_TYPE_AMR8K16B==m_dwAudioEncodeType) ? 2 : 1) < 0)
		{
			m_pManager->SetLastError(NET_RENDER_SOUND_ON_ERROR);
			return 0;
		}
	}
	
	
//	EnterCriticalSection(&m_cs);
	m_cs.Lock();

	LONG lRet = 0;
	list<LPTALKHANDLEINFO>::iterator it = m_talkhandlelist.begin();
	for (;it != m_talkhandlelist.end(); it++)
	{
		if ((*it)->lDevHandle == lLoginID)
		{
//			LeaveCriticalSection(&m_cs);
			m_cs.UnLock();
			return 0;
		}
	}

	afk_talk_channel_param_s talkchannelpar;
	LPTALKHANDLEINFO ptmpinfo = NULL;
	ptmpinfo = new TALKHANDLEINFO;
	if (NULL == ptmpinfo)
	{
		m_pManager->SetLastError(NET_SYSTEM_ERROR);
		lRet = 0;
		goto FAILED;
	}
	memset((void *)ptmpinfo, 0, sizeof(TALKHANDLEINFO));
	memset((void *)&talkchannelpar, 0, sizeof(afk_channel_param_s));
	talkchannelpar.base.udata = (void *)ptmpinfo;
	talkchannelpar.base.func = CTalk::TalkFunc;
	talkchannelpar.no = ptmpinfo->iChannelId;
	
	ptmpinfo->pTalkChannel = (afk_channel_s *)device->open_channel(device, AFK_CHANNEL_TYPE_TALK, &talkchannelpar);
	if (NULL == ptmpinfo->pTalkChannel)
	{
		m_pManager->SetLastError(NET_OPEN_CHANNEL_ERROR);
		lRet = 0;
		goto FAILED;
	}
	ptmpinfo->lDevHandle = lLoginID;
	ptmpinfo->pfcb = pfcb;
	ptmpinfo->dwUser = dwUser;
	m_talkhandlelist.push_back(ptmpinfo);
	lRet = (LONG)ptmpinfo;
	
	goto END;

FAILED:
	if (ptmpinfo != NULL)
	{
		if (ptmpinfo->pTalkChannel)
		{
			ptmpinfo->pTalkChannel->close(ptmpinfo->pTalkChannel);
		}
		delete ptmpinfo;
	}

	if (!bServerMode)
	{
		if (m_render != NULL)
		{
			m_render->CloseAudio();
			m_render->StopDec();
		}
	}
	

END:
//	LeaveCriticalSection(&m_cs);
	m_cs.UnLock();
	return lRet;
}

BOOL CTalk::SetVolume(LONG lTalkHandle, WORD wVolume)
{
	return FALSE;
}

LONG CTalk::SendData2Dev(afk_channel_s *pChannel, char *pSendBuf, DWORD dwBufSize)
{	
	LONG lRet = 0;
	if (NULL == pChannel || NULL == pSendBuf || 0 == dwBufSize)
	{
		m_pManager->SetLastError(NET_ILLEGAL_PARAM);
		return -1;
	}
	struct afk_talk_info_s tempst;
	tempst.data = pSendBuf;
	tempst.datalen = dwBufSize;
	if (1 == pChannel->set_info(pChannel, 0, &tempst))
	{
		lRet = dwBufSize;
	}
	
	return lRet;
}

LONG CTalk::TalkSendData(LONG lTalkHandle, char *pSendBuf, DWORD dwBufSize)
{
	//	EnterCriticalSection(&m_cs);
	m_cs.Lock();
	
	LONG lRet = 0;
	list<LPTALKHANDLEINFO>::iterator it = m_talkhandlelist.begin();
	for (; it != m_talkhandlelist.end(); it++)
	{
		if ((LONG)(*it) == lTalkHandle)
		{
			break;
		}
	}
	if (it == m_talkhandlelist.end() || NULL == (*it))
	{
		m_pManager->SetLastError(NET_INVALID_HANDLE);
		lRet = -1;
		goto END;
	}
	lRet = SendData2Dev((*it)->pTalkChannel, pSendBuf, dwBufSize);
	
END:
	//	LeaveCriticalSection(&m_cs);
	m_cs.UnLock();
	
	return lRet;
}
BOOL CTalk::RecordStart()
{
	return FALSE;
}
BOOL CTalk::RecordStop()
{
	return FALSE;
}
void CTalk::AudioDec(char *pAudioDataBuf, DWORD dwBufSize)
{
}
BOOL CTalk::StopTalk(LONG lTalkHandle)
{
	return FALSE;
}

BOOL CTalk::BroadcastAddDev(LONG lLoginID)
{
	if (m_pManager->IsDeviceValid((afk_device_s *)lLoginID) < 0)
    {
		m_pManager->SetLastError(NET_INVALID_HANDLE);
        return FALSE;
    }
	
	//	EnterCriticalSection(&m_cs);
	m_cs.Lock();
	
	list<LPTALKBROADCASTINFO>::iterator it = m_broadcastlist.begin();
	for (; it != m_broadcastlist.end(); it++)
	{
		if ((*it)->lDevHandle == lLoginID)
		{
			//			LeaveCriticalSection(&m_cs);
			m_cs.UnLock();
			m_pManager->SetLastError(NET_ERROR);
			return FALSE;
		}
	}
	
	BOOL bRet = FALSE;
	afk_device_s *device = (afk_device_s *)lLoginID;
	afk_talk_channel_param_s talkchannelpar;
	LPTALKBROADCASTINFO ptmpinfo = NULL;
	ptmpinfo = new TALKBROADCASTINFO;
	if (NULL == ptmpinfo)
	{
		m_pManager->SetLastError(NET_SYSTEM_ERROR);
		goto FAILED;
	}
	memset((void *)ptmpinfo, 0, sizeof(TALKBROADCASTINFO));
	memset((void *)&talkchannelpar, 0, sizeof(afk_talk_channel_param_s));
	talkchannelpar.base.udata = (void *)ptmpinfo;
	talkchannelpar.base.func = NULL;
	talkchannelpar.no = ptmpinfo->iChannelId;
	ptmpinfo->pTalkChannel = (afk_channel_s *)device->open_channel(device, AFK_CHANNEL_TYPE_TALK, &talkchannelpar);
	if (NULL == ptmpinfo->pTalkChannel)
	{
		m_pManager->SetLastError(NET_OPEN_CHANNEL_ERROR);
		goto FAILED;
	}
	ptmpinfo->lDevHandle = lLoginID;
	m_broadcastlist.push_back(ptmpinfo);
	bRet = TRUE;
	goto END;
	
FAILED:
	bRet = FALSE;
	if (ptmpinfo != NULL)
	{
		if (ptmpinfo->pTalkChannel)
		{
			ptmpinfo->pTalkChannel->close(ptmpinfo->pTalkChannel);
		}
		delete ptmpinfo;
	}
END:
	//	LeaveCriticalSection(&m_cs);
	m_cs.UnLock();
	return bRet;
}

BOOL CTalk::BroadcastDelDev(LONG lLoginID)
{
	//	EnterCriticalSection(&m_cs);
	m_cs.Lock();
	
	BOOL bRet = FALSE;
	list<LPTALKBROADCASTINFO>::iterator it = m_broadcastlist.begin();
	for (; it != m_broadcastlist.end(); it++)
	{
		if ((*it) && (*it)->lDevHandle == lLoginID)
		{
			if ((*it)->pTalkChannel)
			{
				(*it)->pTalkChannel->close((*it)->pTalkChannel);
			}
			delete (*it);
			m_broadcastlist.erase(it);
			break;
		}
	}
	if (m_broadcastlist.end() == it)
	{
		m_pManager->SetLastError(NET_ERROR);
		bRet = FALSE;
	}
	//	LeaveCriticalSection(&m_cs);
	m_cs.UnLock();
	return bRet;
}

int CTalk::InitAudioEncode(AUDIO_FORMAT aft)
{
	if (aft.byFormatTag != 0 || aft.nChannels != 1 || aft.wBitsPerSample != 16 || aft.nSamplesPerSec != 8000)
	{
		m_iEncodeFlag = 0;
		m_pManager->SetLastError(NET_ILLEGAL_PARAM);
		return NET_ILLEGAL_PARAM;
	}
	
	m_iEncodeFlag = 1;
	return 0;
}

int	CTalk::AudioEncode(LONG lHandle, BYTE *lpInBuf, DWORD *lpInLen, BYTE *lpOutBuf, DWORD *lpOutLen)
{
	if (0 == m_iEncodeFlag)
	{
		m_pManager->SetLastError(NET_AUDIOENCODE_NOTINIT);
		return NET_AUDIOENCODE_NOTINIT;
	}
	if (NULL == lpInBuf || NULL == lpInLen || NULL == lpOutBuf || NULL == lpOutLen || 0 == *lpInLen)
	{
		m_pManager->SetLastError(NET_ILLEGAL_PARAM);
		return NET_ILLEGAL_PARAM;
	}
	if (*lpInLen >= MAX_ENCODE_LEN*2)
	{
		*lpInLen = MAX_ENCODE_LEN*2;
		m_pManager->SetLastError(NET_DATA_TOOLONGH);
		return NET_DATA_TOOLONGH;
	}
	if (*lpOutLen < (*lpInLen/2 + 8))
	{
		*lpOutLen = *lpInLen/2 + 8;
		m_pManager->SetLastError(NET_INSUFFICIENT_BUFFER);
		return NET_INSUFFICIENT_BUFFER;
	}
	
	int iRet = 0;
	int iCount = 0;
	int iDataLen = (*lpInLen>>1);
	unsigned short *p16 = (unsigned short *)lpInBuf;
	lpOutBuf[iCount++] = 0x00;
	lpOutBuf[iCount++] = 0x00;
	lpOutBuf[iCount++] = 0x01;
	lpOutBuf[iCount++] = 0xf0;
	lpOutBuf[iCount++] = 0x07;
	lpOutBuf[iCount++] = 0x02;
	*(unsigned short *)(lpOutBuf+iCount) = (unsigned short)iDataLen;
	iCount += 2;
	for (int i = 0; i < iDataLen; i++)
	{
		lpOutBuf[iCount++] = (BYTE)(*p16>>8);
		p16++;
	}
	*lpOutLen = iCount;	
	*lpInLen = 0;
	
	return iRet;
}
int CTalk::ReleaseAudioEncode()
{
	//	EnterCriticalSection(&m_cs);
	m_cs.Lock();
	m_iEncodeFlag = 0;
	//	LeaveCriticalSection(&m_cs);
	m_cs.UnLock();
	return 0;
}
LONG CTalk::InitAudioDecode(AUDIO_FORMAT aft)
{
	return 0;
}
int CTalk::AudioDecode(LONG lHandle, BYTE *lpInBuf, DWORD *lpInLen, BYTE *lpOutBuf, DWORD *lpOutLen)
{
	return 0;
}
int CTalk::ReleaseAudioDecode(LONG lHandle)
{
	return 0;
}
int CTalk::CloseChannelOfDevice(afk_device_s * pdev)
{
	//	EnterCriticalSection(&m_cs);
	m_cs.Lock();
	
	int iRet = 0;
	{
		list<LPTALKHANDLEINFO>::iterator it = m_talkhandlelist.begin();
		for (; it != m_talkhandlelist.end(); it++)
		{
			if ((*it)->lDevHandle == LONG(pdev))
			{
				if ((*it)->pTalkChannel != NULL)
				{
					(*it)->pTalkChannel->close((*it)->pTalkChannel);
				}
				delete (*it);
				m_talkhandlelist.erase(it);
				break;
			}
		}
	}
	{
		list<LPTALKBROADCASTINFO>::iterator it = m_broadcastlist.begin();
		for (; it != m_broadcastlist.end(); it++)
		{
			if ((*it)->lDevHandle == LONG(pdev))
			{
				if ((*it)->pTalkChannel != NULL)
				{
					(*it)->pTalkChannel->close((*it)->pTalkChannel);
				}
				delete (*it);
				m_broadcastlist.erase(it);
				break;
			}
		}
	}
	
	//	LeaveCriticalSection(&m_cs);
	m_cs.UnLock();
	return iRet;
}

int CTalk::WINAPI TalkFunc(afk_handle_t object,  
				   unsigned char *data, 
				   unsigned int datalen,  
				   void *param,  
				   void *udata)
{
	if (NULL == data || 0 == datalen)
	{
		return -1;
	}
	
	int iRet = 0;
	LPTALKHANDLEINFO pTalkHandle = (LPTALKHANDLEINFO)udata;
	if (pTalkHandle && pTalkHandle->pfcb)
	{
		pTalkHandle->pfcb((LONG)pTalkHandle, (char *)data, datalen, 1, pTalkHandle->dwUser);
	}
	
	return iRet;
}

void CTalk::WINAPI RecordFunc(LPBYTE pDataBuffer, DWORD DataLength, /*int*/long user)
{
}

#endif
