#ifndef VIDEORENDER_H
#define VIDEORENDER_H

#include "decode.h"
#include <windows.h>
#include "FifoBuffer.h"

#define _TIMER_1 1 //Only 16 timers for every process.Default TIMER;
#define _TIMER_2 2

class DhVideoRender
{
public:
    DhVideoRender();
    virtual ~DhVideoRender();

	DhAVFrame* m_item ;
	FifoBuffer m_YuvDataList;	//�ѽ������ݶ���
	FifoBuffer m_PcmDataList;
	int m_ifPause ;//�û���������ͣ
	CRITICAL_SECTION  m_CritSec ;//����ͬ����ʱ���ص�����ջ������
	CRITICAL_SECTION  m_ResetTimerCritSec;
	BOOL m_bTimerDisable; //��ʱ����������

	dec_callback m_callback ;//�ص�ָ�룬�ص���Ƶ����

    int init(int port, int imgcount, int chunksize,dec_callback cb);//��ʼ��

    int clear();//����

	int call_render() ;//��ʱ����Ϣ������

    int render();//��Ƶ�ص�

    int changeRate(int rate);//�ı�֡��
	
	int changeInterval(int interval);

	int getRate();//�õ�֡��
    
    int startTimer();//�𶯶�ʱ��

    void stopTimer();//ֹͣ��ʱ��

	void StopTimerSafely(void);//��ȫ�عرն�ʱ��

	void SetPause(int value) ;//������ͣ

	int   GetPause() ;

	int  StopSoundThread();
	int  StartSoundThread();

	void SetACTimerObj(CAccurateTimer *pACTimer) { m_pACTimer = pACTimer; }
	int  GetTimerType(){return m_timertype;}

	double GetRealFrameBitRate(void) { return m_dRealBitRate; } //Kbps

	void SetIVSCallback(void *pIVSCallback, long userData){
		m_IVSCallback = (IVS_callback)pIVSCallback;
		m_IVS_user = userData;
	}

public:
	int		m_interval;		// ��ʱ�����	
	int     m_port ;  //ͨ����
	int     m_timerId ; // ��ʱ����
	int     m_rate; //��ǰ֡��
	int		m_timertype;
	HANDLE	m_hTimerThread;
	DWORD	m_preFrameTime;
	HANDLE	m_hMMTimerEvent;
	int		m_iMMTimerSigRef;

	CAccurateTimer *m_pACTimer;
#ifdef THREAD_RENDER
	HANDLE m_hVideoRender;
#endif //THREAD_RENDER

	int		m_iIntervalSum;
	int		m_iFrameLenSum;
	double	m_dRealBitRate;

public:
	int		m_tmpinterval ;
	bool	m_time2_state;
	int		m_flagvalue;
	int		m_flagnum;
	bool    m_audio_state;
	HANDLE  m_audioThread;
	int m_flagcount;
	
	IVS_callback m_IVSCallback; //����IVS�ص�
	long m_IVS_user;

private:
	static DWORD  __stdcall timer(LPVOID pParam);
	static DWORD  __stdcall audiothread(LPVOID pParam);
};

#endif /* VIDEORENDER_H */