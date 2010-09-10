 //DISPLAY_H

/********************************************************************
	created:	2005/11/28
	created:	28:11:2005   17:00
	filename: 	display.h
	file base:	display
	file ext:	h
	author:		
	
	purpose:	
*********************************************************************/
//���ڷ���طŵĴ�������һ����������˫���崦����ʾ���ݣ������ͬ��������������ʾ�ĵȴ���
//���⻺���ȡ��̬���䷽ʽ����ֹͬһӦ�ó����·�ط�������������ͨ������Դ�˷� 205-12-23
//�����лط���ʾ��صĴ����Ƶ������д��� 2006-1-25 chenmy
#ifndef DISPLAY_H
#define DISPLAY_H
#include <vector>
#include "render/manager.h"

#define  MULTI_DISPLAY_RECT_NUM 16

//��������
typedef enum
{
	DEC_NO = 0 ,
	DEC_VIDEO ,
	DEC_AUDIO ,
	DEC_COMPLEX,
}DEC_TYPE ;

//��������ʾ�����Ϣ
typedef struct _MULTI_DIS_INFO
{
	int nRegionNum ;
	RECT pSrcRect ;
	BOOL bEnable ;
 	DhRenderManager nVideoRender  ;
}MULTI_DIS_INFO ;

class CDisplay
{	
	MULTI_DIS_INFO m_MultiDisInfo[MULTI_DISPLAY_RECT_NUM];
	unsigned char* m_pQuarterBuf;
	DWORD m_volume ;
	int  m_nIndex;    //�˿ں�
	HWND m_hWnd;
	int  m_nWidth;      //ÿ֡ͼƬ�Ŀ��
	int  m_nHeight;     //ÿ֡ͼƬ�ĸ߶�
	int  m_CurFrameNum ;          //��ǰ��ʾ����������
	int  m_PlayedFrames ;         //��������
	DWORD m_DisType ;
	DWORD m_colorkey ;
	DEC_TYPE m_decType ;
	int   m_nDisplayType ;//��ʾ���ͣ������ֱ������ķ�֮һ�ֱ���,20060818 zgf
	long  m_nCoefficient ;//���ε�������
	int m_i ;
	bool m_IfRenderOpen ;
	DhRenderManager m_renderManager ;
	RECT m_mainRect;
	int  m_nRotateType;

	void (__stdcall *m_DDRAWCB)(int index, HDC hDc);
//��Ҫ��Ա������
public:
	
	CDisplay(int nPort = 0);
	~CDisplay();
	
	int   Init(HWND mWnd);         //��ʼ������      
	int   Close();         //�رջط���ʾ     
	int   ResetVideoDisplay(void);
	int   ReciveYUV(int index, unsigned char *py, unsigned char *pu, unsigned char *pv,
            int width, int height,int AddFrameNum);  //������Ƶ����
	int   RecivePCM(int index, unsigned char *pcm, int len,int bitsPerSample,int samplesPerSecond); //������Ƶ����
	int   Show();      //�ٴ���ʾ����
	int   ShowRegion(int RegionNum, unsigned char* pBuf) ;
	int   GetPicWidth()  ;//���ͼƬ���
	int   GetPicHeight() ;//���ͼƬ�߶�
	void  SetWidthHeight(int width,int height);
		
	int   GetCurFrameNum();                  //��õ�ǰ��ʾ����������
	int   GetPlayedFrames() ;                //��ò�������
	void  SetCurFrameNum(int FrameNum) ;    //���õ�ǰ��ʾ����������

	BOOL  SetOverlayMode(BOOL boverlay,DWORD nColorKey) ;//�����Ƿ���overlay��ʽ���ż��ؼ�ɫ
	DWORD GetColorKey() ;                 //�õ��ؼ�ɫ
	DWORD GetOverlayMode() ;              //�����Ƿ���overlay��ʽ����
	BOOL  MulitiDisplay(int nRegionNum,HWND hDestWnd,RECT* pSrcRect,BOOL bEnable) ;//��������ʾ

	BOOL  SetDecCBType(DWORD dectype) ;//���ý���ص�����
	int   GetDecType();
	//////////////////////////////////////////add by zgf 2006_0819
	BOOL  SetDisplayType(int displaytype) ; //�����������ֱ��ʻ����ķ�֮һ�ֱ���
	int   GetDisplayType() ;
	void  ToQuarter(BYTE* py,BYTE* pu,BYTE* pv,int width,int height) ;//��ͼ������ת���ķ�֮һ��С
	BOOL  AdjustWaveAudio(BYTE* pcm, unsigned int datalen, int bitsPerSample,long nCoefficient) ;//��������
	BOOL  SetCoefficient(int nCoefficient) ;
    WORD  GetVolume() ;
	BOOL  SetVolume(WORD volume) ;
	BOOL  OpenSound() ;
	BOOL  CloseSound() ;
	BOOL  SetRotateAngle(int rotateType); 
	BOOL  VerticalSyncEnable(BOOL bEnable);
};

#endif 
