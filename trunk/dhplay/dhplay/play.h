 
/********************************************************************
	created:	2005/11/28
	created:	28:11:2005   17:03
	filename: 	play.h
	file base:	play
	file ext:	h
	author:		
	
	purpose:	
*********************************************************************/
#ifndef PLAY_H
#define PLAY_H

#include "data.h"
#include "display.h"

#include "decode\graphfactory.h"
//����״̬
typedef enum
{
	PS_INVALID = -1,    //��Ч
	PS_STOP = 0,        //ֹͣ
	PS_PLAY,            //��������
	PS_BACK,            //����ط�
	PS_ONEFRAME,
	PS_TOTAL,
}PLAY_STATUS;

//����طŵ���״̬
typedef enum 
{
	BF_START = 0,   //����طſ�ʼ���ƶ��ļ�ָ�뵽I��ͷ
	BF_DECODE,      //���룬ȡ��Ƶ�����ͽ���
	BF_DISPLAY,     //��ʾ���ȴ���ʾ
}BACK_FLAG;

//������־
typedef enum{
	SF_STOP = 0,
	SF_PLAY,
	SF_SHAREPLAY,
	SF_SHARESTOP,
}SOUND_FLAG;

//��Ƶ������Ϣ
typedef struct _COLOR{
	int nBrightness ;
	int nContrast ;
	int nSaturation ;
	int nHue ;
}COLOR_INFO ;

//�ٶ�ֵ
//const int SPEED[9] = {1,3,6,12,25,40,60,80,100} ;
const int SPEED[10] = {1,3,6,12,25,50,100,150,200,400} ;

//������
typedef enum
{
	STREAM_VIDEO = 1,
	STREAM_AUDIO,
	STREAM_COMPLEX
}STREAM_TYPE ;


//�ٶ�״̬
typedef enum _SPEED
{
	PS_SLOW4=0,
	PS_SLOW3,
	PS_SLOW2,
	PS_SLOW1,
	PS_NORMAL,
	PS_FAST1,
	PS_FAST2,
	PS_FAST3,
	PS_FAST4,
}PS_SPEED;

class CDHPlay
{		
	PLAY_STATUS		m_nStatus;     //����״̬��-1 ��Ч ��0 ֹͣ�� 1 ��ͣ ��2�������š� 3 ��1 ��4 ��2�� ����������	
	int				m_ImgBufCount ;          //��������С��ͼƬ����	
	DecodeOption m_sDecSet;    //��ǰ�������ã���������� 
	int m_bFlag ;              //����������Ч�ԣ�ȡ���ļ����ݺ��ó�ȡ�����ݳ��ȣ��ͽ���ɹ�����0
	BYTE *m_mBuffer;    //�ͽ������ݻ���
	CDHAVData* m_pDHFile ;	//���ݶ���ָ��	
	DhPlayGraph* m_PlayGragh ;
	COLOR_INFO m_ColorInfo ;   //��Ƶ����		
	//�û���λ����
	long m_FrameNumSeted ;     //�û����õ�֡��
	long m_tepFrameSeted ;
	float m_fRelativePos ;     //�û����õĲ���λ��
	__int64 m_userfilepos ;
	HANDLE	m_hThread ;   //�������߳�
	
	BOOL m_IsSoundPlay ;//�Ƿ񲥷�����
	BOOL m_IsPause ;           //�Ƿ���ͣ
	BOOL m_IsOneFrame ;     //�Ƿ�֡����
	BOOL m_IsFileEnd ;
	int m_ResetStreamFlag ;//��ģʽ����
//	HANDLE m_RecordFile ;//¼���ļ� test
	DWORD m_CurPlayedTime;
public:	
	HANDLE m_RecordFile ;//¼���ļ�
	char   m_cDiskNum[4]; //¼���ļ������̷�
	BOOL   m_ifRecord;//test
	BOOL   m_bPosAdjust4Index;
	
	//��Щ��������Ҫ�ڽ���ص�����dec_cb����ã���������Ϊpublic���ͣ��Է������
	PS_SPEED m_nSpeed ;        //�ٶ�״̬�������ĵ�����
	int    m_iDesiredRate;
	CDisplay *m_pDisplay ;      //��ʾ����ָ��
	DWORD m_nTimerType;
	STREAM_TYPE m_StreamType ; //�����뷽ʽ	

	LONG m_nIndex;             //�������������Ŷ˿ںţ�
	CRITICAL_SECTION  m_PlayCritSec ;//����ͬ���������̺߳�ֹͣ����

	CRITICAL_SECTION  m_SpeedCritSec;

	CDHPlay(LONG nPort);
	~CDHPlay();

//��Ҫ��Ա�����У�
	int PlayProc();             //�����̵߳��ô�����	
	//���ⲿ����
	BOOL Start(HWND hWnd);          //��ʼ����
	BOOL Stop();                    //ֹͣ����
	BOOL Pause(DWORD nPause);       //��ͣ/�ָ�
	BOOL PlayFast();                //���
	BOOL PlaySlow();                //����
	BOOL PlayBack();                //����,��ʱû��ʵ��
	BOOL PlayBackOne();             //������
	BOOL PlayOnebyone();            //��֡����
	BOOL SetPlayPos(float fRelativePos);  //���ò���λ��
	float GetPlayPos();                   //��õ�ǰ����λ��
	BOOL InputData(PBYTE pBuf,DWORD nSize);  //���ӿ���������
	DWORD GetFileTime();                     //�õ��ļ���ʱ�䳤��
	DWORD GetPlayedTime();                   //�õ��Ѿ����ŵ�ʱ��
	DWORD GetPlayedTimeEX();
	DWORD GetPlayedFrames();                 //�õ��Ѿ����ŵ�����
	BOOL SetImgBufCount(int Num) ;           //���û�������С��ͼƬ����
	BOOL GetImgBufCount() ;                  //�õ���������С

	BOOL SetDecCBType(DWORD dectype) ;         //���ý���ص�����
	BOOL SetDecAudio(BOOL IfDecAudio) ;//�����Ƿ������Ƶ
	BOOL ReFreshEx(int nRegionNum) ;         //ˢ�¶�������ʾ�е�ĳ������
	//��չ���ӿڣ���ʱ�����һ��
	BOOL InputVideoData(PBYTE pBuf,DWORD nSize);
	BOOL InputAudioData(PBYTE pBuf,DWORD nSize);
	DWORD GetSourceBufferRemain();    //��ȡ��ģʽ��ʣ�໺���С
	BOOL  ResetBufferRemain();        //��λ��ģʽʣ������
	BOOL RefreshPlay() ;            //ˢ����ʾ
	DWORD GetFileTotalFrames() ;    //�õ��ļ�������
	DWORD GetCurFrameNum();         //�õ���ǰ���������
	DWORD GetFrameRate();           //�õ���ǰ��������
	BOOL  GetPictureSize(LONG* pWidth, LONG* pHeight);

	BOOL SetCurrentFrameNum(DWORD nFrameNum);   //����������ò���λ��
	BOOL SetPlayTime(DWORD nTime);              //��ʱ�����ò���λ��
	
	BOOL GetRefValue(BYTE *pBuffer, DWORD *pSize);         //��ȡ������Ϣ
	BOOL SetRefValue(BYTE *pBuffer, DWORD nSize);          //����������Ϣ

	BOOL ResetBuffer(DWORD nBufType);                 //��λ����
	DWORD GetBufferValue(DWORD nBufType);             //��ȡ����Ĵ�С
	BOOL SetColor(DWORD nRegionNum, int nBrightness, int nContrast, int nSaturation, int nHue);      //������Ƶ����
	BOOL GetColor(DWORD nRegionNum, int *pBrightness, int *pContrast, int *pSaturation, int *pHue);  //��ȡ��Ƶ����

	////////////////////////////////////////////
	BOOL  SetDisplayType(int displaytype) ;
	int   GetDisplayType() ;
	BOOL  AdjustWaveAudio(BYTE* pcm, unsigned int datalen, int bitsPerSample,long nCoefficient) ;//��������
	BOOL  SetCoefficient(int nCoefficient) ;	
	BOOL  precess(unsigned char *yuv, int width, int height) ;
	BOOL  StartDataRecord(char *sFileName, int idataType) ;
	BOOL  StartAVIResizeConvert(char *sFileName, long lDesWidth, long lDesHeight);
	BOOL StopDataRecord() ;

	BOOL AdjustFluency(int bufnum, int adjustrange);
	BYTE* GetLastFrame();
	BOOL FixRate(int rate);
	void GetTimeStr(char* pBuf,int len);

	BOOL GetMediaInfo(char* pBuf, int len);

	int GetFileRate();
	BOOL  SetWaterMarkCallbackFunc(void *pvFunc, long useData);
	BOOL  SetWaterPandoraMarkCallbackFunc(void *pvFunc, long nUser);
	BOOL  SetRotateAngle(int rotateType);

	BOOL SetIVSCallbackFunc(void *pIVSFunc, long nUser);
	BOOL GetRealFrameBitRate(double *pBitRate);
protected:
private:
	BOOL Write();       //�����ݽ���,ͨ������ص��������ͳ�����ʾ
	int GetAVData();   //��ȡ��Ƶ����
	static DWORD  __stdcall ChangeSpeedProc(LPVOID pParam);
};

#endif
