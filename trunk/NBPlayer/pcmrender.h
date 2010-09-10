#ifndef PCMRENDER_H
#define PCMRENDER_H

#include <windows.h>
#include <mmsystem.h>
#include <mmreg.h>
#include <msacm.h>

#define PCM_BUF_COUNT	4
#define BUFFER_SIZE		32768

class CAudioRender
{
public:
	virtual int init(int channels, int samplePerSec, int bitPerSample, HWND hWnd)=0;
	virtual int clean() = 0;
	// д����
	virtual int write(unsigned char *pcm, int len) = 0;
	// �������߳���صķ���
	virtual void terminating() = 0; // ��ֹ����
	virtual int getVolume() = 0;
	virtual void setVolume(int nVol) = 0;
	virtual ~CAudioRender(){} ;
	
	int m_bitsPerSample ;
	int m_samplesPerSecond ;
};

class CPcmRender : public CAudioRender
{
	struct PcmBuffer {
		PcmBuffer() {
			hWaveOut = NULL;
			memset(&header, 0, sizeof(header));
			header.dwFlags |= WHDR_DONE;
		}
		
		DWORD Prepare(HWAVEOUT hOut, unsigned int count)
		{
			Release();
			
			memset(&header, 0, sizeof(header));
			
			header.lpData = data;
			header.dwBufferLength = count;
			header.dwUser = (DWORD)this;

			hWaveOut = hOut;

			return waveOutPrepareHeader(hWaveOut, &header, sizeof(header));
		}

		DWORD Release()
		{
			DWORD err = MMSYSERR_NOERROR;
			if (hWaveOut!=NULL) {
				err = waveOutUnprepareHeader(hWaveOut, &header, sizeof(header));
				if (err== WAVERR_STILLPLAYING) {
					return err;
				}

				hWaveOut = NULL;
			}

			header.dwFlags |= WHDR_DONE;
			
			return err;
		}

		char data[BUFFER_SIZE];
		WAVEHDR header;
		HWAVEOUT hWaveOut;

	};
public:
	CPcmRender();
	~CPcmRender();

	// �����ֱ�Ϊͨ������������
	virtual int init(int channels, int samplePerSec, int bitPerSample, HWND hWnd);
	virtual int clean();

	// д����
	virtual int write(unsigned char *pcm, int len);
	virtual int getVolume();
	virtual void setVolume(int nVol);

	// �������߳���صķ���
	virtual void terminating(); // ��ֹ����
	void loop(); // ��ʼ����ѭ������һ�������̣߳�
	
private:
	// �ڲ�����
	void initParam(); // ��ʼ������
	void setFormat(int channels, int samplePerSec, int bitPerSample);
	
	void reset(); // ���û����״̬
	int start(); // ����
	
	int Abort();
private:
	// ������Ϣ
	int m_nVolumn;

	WAVEFORMATEX m_waveFormat;

    HWAVEOUT m_hWaveOut; // WAVEOUT���

	HANDLE m_hEventDone;

	int m_bufferIndex;

	HANDLE m_mutex;
	
	// ���Ż����� 
	PcmBuffer m_buffer[PCM_BUF_COUNT];
};

#endif /* PCMRENDER_H */
