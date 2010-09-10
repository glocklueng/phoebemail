#include "pcmrender.h"

#include <process.h> 
#include <string.h>
#include <stdio.h>

//#define DUMP_PCM

#ifdef DUMP_PCM
FILE *pcmdata = 0;
#endif

/***********************************************************************
 *  ���캯��
************************************************************************/
CPcmRender::CPcmRender()
{
	initParam();
#ifdef DUMP_PCM
	pcmdata = fopen("audio_r.pcm", "w+b");
#endif
}

/************************************************************************
 * ��������
************************************************************************/
CPcmRender::~CPcmRender()
{
	clean();
	CloseHandle(m_hEventDone);
	CloseHandle(m_mutex);
#ifdef DUMP_PCM
	fclose(pcmdata);
#endif
}

/**********************************************************************
 * �ڲ�ʹ�ã���ʼ������                                                                     
***********************************************************************/
void CPcmRender::initParam()
{
	m_hWaveOut = NULL;
	m_hEventDone = CreateEvent(NULL, FALSE, FALSE, NULL);
	m_mutex = CreateMutex(NULL,FALSE,NULL);

	m_bufferIndex = 0;
	m_samplesPerSecond = 0;
	m_bitsPerSample = 0;
	m_nVolumn = -1;
}

void CPcmRender::setFormat(int channels, int samplePerSec, int bitsPerSample)
{
	// ��һ��: ��ȡwaveformat��Ϣ
	m_waveFormat.wFormatTag = WAVE_FORMAT_PCM;
	m_waveFormat.nChannels = channels;
	m_waveFormat.wBitsPerSample = bitsPerSample;
	m_waveFormat.nSamplesPerSec = samplePerSec;
	m_waveFormat.nBlockAlign = 
		m_waveFormat.nChannels * m_waveFormat.wBitsPerSample / 8;
	m_waveFormat.nAvgBytesPerSec = 
		m_waveFormat.nSamplesPerSec * m_waveFormat.nBlockAlign;
	m_waveFormat.cbSize = sizeof(m_waveFormat);
}

/***********************************************************************
 * ��ʼ��CPcmRender����
 *
************************************************************************/
int CPcmRender::init(int channels, int samplePerSec, int bitsPerSample, HWND hWnd)
{
	if (m_hWaveOut != NULL) {
		return 0;// �Ѿ������˳�ʼ��
	}

	setFormat(channels,samplePerSec,bitsPerSample);
	
	MMRESULT ret = waveOutOpen(NULL, WAVE_MAPPER, &m_waveFormat, 
		NULL, NULL, WAVE_FORMAT_QUERY);

	if (MMSYSERR_NOERROR != ret) {
		return -1;
	}
    
	// �ڶ���: ��ȡWAVEOUT���
	ret = waveOutOpen(&m_hWaveOut, WAVE_MAPPER, &m_waveFormat, 
		(DWORD)m_hEventDone,0,CALLBACK_EVENT);
	
	if (MMSYSERR_NOERROR != ret) {
		return -1;
	}

	m_bitsPerSample = bitsPerSample ;
	m_samplesPerSecond = samplePerSec ;
	
	reset();
	start();
    
    return 0;
}

/************************************************************************
 * ���û����������ԣ����������������ա�ָʾ�Լ���д��
************************************************************************/
void CPcmRender::reset()
{
	m_bufferIndex = 0;
}

/***********************************************************************
 *  ����CPcmRender����	
 *
 *  1. ���ȴ����߳��������												
 *  2. �ٴ���WaveOut��ض���
 *                                                                   
 ************************************************************************/
int CPcmRender::clean()
{
	if (m_hWaveOut==NULL) {
		return -2;
	}
	
	Abort();
	
	if (m_hWaveOut != NULL) {
		while (waveOutClose(m_hWaveOut)==WAVERR_STILLPLAYING) {
			waveOutReset(m_hWaveOut);
		}
		m_hWaveOut = NULL;
	}
	
	Abort();
	
	
	
	return 0;
}

BOOL CPcmRender::Abort()
{
	DWORD osError = MMSYSERR_NOERROR;
	
	if (m_hWaveOut != NULL) {
		osError = waveOutReset(m_hWaveOut);
	}
	
	{
	WaitForSingleObject(m_mutex,INFINITE);
	
	if (m_hWaveOut!=NULL) {
		for (unsigned i = 0; i<PCM_BUF_COUNT; i++) {
			while (m_buffer[i].Release()==WAVERR_STILLPLAYING) {
				if (m_hWaveOut!=NULL) {
					waveOutReset(m_hWaveOut);
				}	
			}
		}
	}

	ReleaseMutex(m_mutex);

	m_bufferIndex = 0;
	
	// Signal any threads waiting on this event, they should then check
	// the bufferByteOffset variable for an abort.
	SetEvent(m_hEventDone);
	}
	
	if (osError != MMSYSERR_NOERROR)
		return FALSE;
	
	return TRUE;
}

/***********************************************************************
 * ��ֹ�����̣߳�
 * ���ȷ����źţ����߳��Լ���ֹ��
************************************************************************/
void CPcmRender::terminating()
{
}

/************************************************************************
 * д����
************************************************************************/
int CPcmRender::write(unsigned char *pcm, int len)
{
	if (m_hWaveOut==NULL) {
		return -1;
	}

	unsigned char * ptr = pcm;

	WaitForSingleObject(m_mutex,INFINITE);

	DWORD osError = MMSYSERR_NOERROR;

	while (len>0) {
		DWORD flags = m_buffer[m_bufferIndex].header.dwFlags;

		while ((flags&WHDR_DONE)==0) {
			ReleaseMutex(m_mutex);

			if (WaitForSingleObject(m_hEventDone, INFINITE) != WAIT_OBJECT_0) {
				return -1;
			}

			WaitForSingleObject(m_mutex,INFINITE);

			flags = m_buffer[m_bufferIndex].header.dwFlags;
		}
		
		osError = m_buffer[m_bufferIndex].Prepare(m_hWaveOut, len);
		if (osError!=MMSYSERR_NOERROR) {
			break;
		}
		
		memcpy(m_buffer[m_bufferIndex].data, ptr, len);
		
		osError = waveOutWrite(m_hWaveOut, &m_buffer[m_bufferIndex].header, sizeof(WAVEHDR));
		if (osError!= MMSYSERR_NOERROR) {
			break;
		}
		
		m_bufferIndex = (m_bufferIndex+1)%PCM_BUF_COUNT;

		break;
	}

	ReleaseMutex(m_mutex);

	return 0;
}

int CPcmRender::getVolume()
{
	//�����������
	/*if (m_hWaveOut)
	{
		DWORD dwVol = 0;
		waveOutGetVolume(m_hWaveOut, &dwVol);
		dwVol &= 0xFFFF;
		return dwVol;
	}*/

	if (m_nVolumn != -1)
	{
		return m_nVolumn;
	}

	DWORD dwVolumeRet = 0;
	WAVEFORMATEX waveFormat;
	HWAVEOUT hWaveOut;

	waveFormat.wFormatTag = WAVE_FORMAT_PCM;		// init
	waveFormat.nChannels = 1;
	waveFormat.wBitsPerSample = 8;
	waveFormat.nSamplesPerSec = 8000;
	waveFormat.nBlockAlign = waveFormat.nChannels * waveFormat.wBitsPerSample / 8;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = sizeof(waveFormat);

	if (MMSYSERR_NOERROR != waveOutOpen(NULL, WAVE_MAPPER, &waveFormat, NULL, NULL, WAVE_FORMAT_QUERY))
	{
		return 0;
	}
	if (MMSYSERR_NOERROR != waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormat, (DWORD)0,0,CALLBACK_NULL))
	{
		return 0;
	}

	DWORD dwVol = 0;
	waveOutGetVolume(hWaveOut, &dwVol);
	int nRet = dwVol & 0xFFFF;

	return nRet;
}

void CPcmRender::setVolume(int nVol)
{
	nVol = max(0, min(nVol, 0xFFFF));

	DWORD dwVol = nVol << 16;
	dwVol += nVol;

	/*if (m_hWaveOut)
	{
		waveOutSetVolume(m_hWaveOut, dwVol);
	}*/

	WAVEFORMATEX waveFormat;
	HWAVEOUT hWaveOut;

	waveFormat.wFormatTag = WAVE_FORMAT_PCM;		// init
	waveFormat.nChannels = 1;
	waveFormat.wBitsPerSample = 8;
	waveFormat.nSamplesPerSec = 8000;
	waveFormat.nBlockAlign = waveFormat.nChannels * waveFormat.wBitsPerSample / 8;
	waveFormat.nAvgBytesPerSec = waveFormat.nSamplesPerSec * waveFormat.nBlockAlign;
	waveFormat.cbSize = sizeof(waveFormat);

	if (MMSYSERR_NOERROR != waveOutOpen(NULL, WAVE_MAPPER, &waveFormat, NULL, NULL, WAVE_FORMAT_QUERY))
	{
		return;
	}
	if (MMSYSERR_NOERROR != waveOutOpen(&hWaveOut, WAVE_MAPPER, &waveFormat, (DWORD)0,0,CALLBACK_NULL))
	{
		return;
	}
	waveOutSetVolume(hWaveOut, dwVol);

	waveOutReset(hWaveOut);
	waveOutClose(hWaveOut);

	m_nVolumn = nVol;
}

void CPcmRender::loop()
{
}

/************************************************************************
 * �����߳�
************************************************************************/
int CPcmRender::start()
{
	return 0;
}