/*
* Copyright (c) 2010, ������ŵ�Ӿ��Ƽ����޹�˾
* All rights reserved.
*
* �ļ����ƣ�AudioThread.h
* �ļ���ʶ��
* ժ����Ҫ����Ƶ�����߳�
*

* ��ǰ�汾��1.0
* ԭ���ߡ�����һ��
* ������ڣ�2010��5��18��
* �޶���¼������
*/
#ifndef ZENO_AUDIO_THREAD_H
#define ZENO_AUDIO_THREAD_H

#include "ThreadBase.h"
#include "Singleton.h"
#include "pcmrender.h"
#include "AX_Mutex.h"
#include <list>

#define AUDIO_BUF_LEN 16*1024
typedef struct Zeno_Audio_Frame 
{
	char data[AUDIO_BUF_LEN];
	int  len;
	int  samplesPerSecond;
	int	 bitsPerSample;
}Zeno_Audio_Frame_t;

typedef std::list<Zeno_Audio_Frame_t*> AudioFrameList;

class CAudioThread : public ThreadBase
{
public:
	CAudioThread(void);
	virtual ~CAudioThread(void);

	int openSound(int id);
	int closeSound(void);
	int inputData(int id, char* buf, int len, int samplesPerSecond, int bitsPerSample);
	int getVolume();
	void setVolume(int nVol);
	int getId();
	void clearBuf();

protected:
	virtual int run(void);

	int renderAudio(Zeno_Audio_Frame_t* frame);
	void clearFrames(void);

private:
	CAudioRender*	m_render;		//��Ƶ����
	int				m_id;			//��ǰ���ŵ�ID
	AudioFrameList	m_activeFrames; //�ȴ����ŵ�֡
	AudioFrameList  m_framePool;	//���ݳ�
	AX_Mutex		m_mutex;
};

typedef Singleton<CAudioThread> CAudioThreadSingleton;

#endif
