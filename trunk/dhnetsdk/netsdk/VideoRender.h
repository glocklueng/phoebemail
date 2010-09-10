#ifndef _VIDEORENDER_H
#define _VIDEORENDER_H

#include "StdAfx.h"
#include "RealPlay.h"

#ifdef WIN32	//Ŀǰ����ֻ֧��windows����ϵͳ
#include "./depend/playsdk.h"
#include "./depend/playdef.h"
#endif 
/*
class CVideoRender
{
public:
	CVideoRender(long hWnd);
	virtual ~CVideoRender();
protected:
	//���ھ��
    long  m_hWnd;

	//��־�Ƿ����ڲ���
    bool  m_bPlay;

	//֡��
    int   m_nframerate;

	//��־�Ƿ����ڵ�֡����
    bool  m_bStep;

	//��־�Ƿ�����ͣ
    bool  m_bPause;

	//ͼ����ɫ����
    unsigned char m_brightness;
    unsigned char m_contrast;
    unsigned char m_hue;
    unsigned char m_saturation;

	//֡ʱ����Ϣ
    unsigned int  m_year;
    unsigned int  m_month;
    unsigned int  m_day;
    unsigned int  m_hour;
    unsigned int  m_minute;
    unsigned int  m_second;

public:
	//������ʾ�ص�����ָ��
    void  *m_pDrawFunc;
    void  *m_userdata1;
    void  *m_userdata2;
    void  *m_userdata3;

    st_Monitor_Info *m_monitor;

public:
	//����m_monitor
	CRITICAL_SECTION m_csMT;

	//����drawCallback
	CRITICAL_SECTION m_csDC;

	//��־�Ƿ������Ƶ
	bool  m_bAudioPlay;
private:
	//�����־λ��0��MAX_RENDER_COUNT
    int   m_nScreenID;

	//����������
    void *m_h264Decoder;
public:
	//��ȡ/ռ�ݿ��н����־λ��0��MAX_RENDER_COUNT
    static int GetFreeScreenID();
    static void SetScreenFlag(int index, char bFlag);

	//����OSDʱ�䣬�����ڲ���
    void  SetOSDTime(unsigned long year, unsigned long month, unsigned long day,
        unsigned long hour, unsigned long minute, unsigned long second);

	//��ȡOSDʱ�䣬�ӿں���
    void  GetOSDTime(unsigned long *year, unsigned long *month, unsigned long *day,
        unsigned long *hour, unsigned long *minute, unsigned long *second);

	//���û�����ʾ�ص�����
    void  SetDrawCallBack(void *pDrawCBFunc, void *userdata1, void *userdata2, void *userdata3);

	//��ʼ/�������ţ������ڲ�����
    bool  StartPlay(int type, bool framectrl);
    bool  EndPlay();
	
	//����ý������
    bool  Play(unsigned char *pBuf, int nLen);
	//��ս��뻺��
    int  Reset();
	//�жϽ��뻺���Ƿ�Ϊ��
    bool  IsEmpty();

	//��ʼ/�������룬����ӿں������Ƕ�StartPlay/EndPlay�ķ�װ
	int  StartDec(BOOL framectrl);
	int  StopDec();

	//����render��Դ�ٴα�����ʱ��ˢ��һЩ��Ա����
	int  ChangeHwnd(HWND hwnd);

	//��ȡ֡��
    int   GetFrameRate() { return m_nframerate; }
	//���ſ���
    bool  SetFrameRate(int framerate);
    bool  Slow();
    bool  Fast();
    bool  Pause(bool bPause);
    bool  Step(bool bStop);
	//ץͼ
    bool  SnapPicture(const char *pchFileName);

	//��Ƶ����
    bool  OpenAudio();
    bool  CloseAudio();
    bool  PlayAudio(unsigned char *pBuf, int nLen);
    bool  IsAudio() { return m_bAudioPlay; }
    bool  SetAudioVolume(int nVolume);

	//ͼ����ɫ����
    bool  AdjustColor(unsigned char brightness, unsigned char contrast, 
        unsigned char hue, unsigned char saturation);
    void  GetColorParam(unsigned char *brightness, unsigned char *contrast, 
        unsigned char *hue, unsigned char *saturation);

	void SetMonitorInfo(st_Monitor_Info* pMI);

	int  CaptureToFile(char* inbuf, int buflen, const char *filename, void *parm);
};
*/

#define RENDER_BUFFER_LEN (1024*900)

class CVideoRender
{
public:
	CVideoRender(HWND hWnd);
	virtual ~CVideoRender();
	
public:
	//��ʼ/ֹͣ����
	int  StartDec(BOOL framectrl, DWORD dwTalkType = 0/*�Ƿ����������Խ����Խ���Ƶ����������Ϣ*/);
	int  StopDec();

	//��Ƶ����
    BOOL  OpenAudio();
    BOOL  CloseAudio();
//    BOOL  PlayAudio(unsigned char *pBuf, int nLen);
    BOOL  IsAudio();
    BOOL  SetAudioVolume(int nVolume);

	//��ȡ֡��
    int   GetFrameRate();
	//���ſ���
    BOOL  SetFrameRate(int framerate);
    BOOL  Slow();
    BOOL  Fast();
    BOOL  Pause(BOOL bPause);
    BOOL  Step(BOOL bStop);
	BOOL  PlayNormal();

	//ץͼ
    BOOL  SnapPicture(const char *pchFileName);

	
	//����render��Դ�ٴα�����ʱ��ˢ��һЩ��Ա����
	int  ChangeHwnd(HWND hWnd);

	
	//����ý������
    BOOL  Play(unsigned char *pBuf, int nLen);
	//��ս��뻺��
    int  Reset();
	//�жϽ��뻺���Ƿ�Ϊ��
    BOOL  IsEmpty();
	
	//��ȡOSDʱ�䣬�ӿں���
    BOOL  GetOSDTime(unsigned long *year, unsigned long *month, unsigned long *day,
        unsigned long *hour, unsigned long *minute, unsigned long *second);
	
	//���û�����ʾ�ص�����
    BOOL  SetDrawCallBack(void* pDrawCBFunc, void* ud1, void* ud2, void* ud3);
	
	
	//ͼ����ɫ����
    BOOL  AdjustColor(unsigned char brightness, unsigned char contrast, 
        unsigned char hue, unsigned char saturation);
    BOOL  GetColorParam(unsigned char *brightness, unsigned char *contrast, 
        unsigned char *hue, unsigned char *saturation);
	

	BOOL SetMonitorInfo(st_Monitor_Info* pMI);

	//����ͼ�󲥷ŵ�������
	BOOL  AdjustFluency(int nLevel);

	//��ȡ���뻺����δ��������ݴ�С
	DWORD GetSourceBufferRemain();

	
#ifdef WIN32	//Ŀǰ����ֻ֧��windows����ϵͳ
	BOOL CloseAudioRecord();
	BOOL OpenAudioRecord(pCallFunction pProc,long nBitsPerSample,long nSamplesPerSec,long nLength,long nReserved,long nUser);
#endif

	//�ڲ��ӿ�
public:
	void MyDrawFunc_Imp(long nPort,HDC hDc);
	void MyDisplayFunc_Imp(long nPort, char* pBuf, long nSize, long nWidth, long nHeight, long nStamp, long nType);
	void MyDemuxFunc_Imp(long nPort, char* pBuf, long nSize, void* pParam, long nReserved);
	void MyAudioFunc_Imp(long nPort, char * pAudioBuf, long nSize, long nStamp, long nType);

protected:
private:
	HWND m_hWnd;
	int m_iPlayPort;

	BOOL m_bPlaying;
	BOOL m_bStep;
	BOOL m_bAudio;

	int m_tmpbpsam; //��ʱ��Ų������
	int m_tmpsamps; //��ʱ��Ų�����

	void*	m_pfDrawFunc;
	void*	m_drawUd1;
	void*	m_drawUd2;
	void*	m_drawUd3;

	st_Monitor_Info *m_monitor;
	//����m_monitor
	DEVMutex m_csMT;
	
	//test file
//	FILE* m_file;
};

#endif

