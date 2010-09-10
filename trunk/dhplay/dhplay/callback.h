/********************************************************************
	created:	2006/01/10
	created:	10:1:2006   9:15
	filename: 	callback.h
	file base:	callback
	file ext:	h
	author:		chenmy	
	purpose:	
*********************************************************************/
#ifndef CALLBACK_H
#define CALLBACK_H

#ifdef DHVECPLAY
	#include "dhvecplay.h"
#else
	#include "dhplay.h"
#endif

#include "display.h"

//ע��Ļص�����
typedef enum
{
	CBT_DecCBFun = 0,              //������ʾ�ص�
	CBT_DisplayCBFun ,             //��ʾץͼ�ص�
	CBT_DrawCBFun ,                //ע�ửͼ��ص�
	CBT_FILEREF,                   //�����ļ������ɹ�����ص�
	CBT_FILEREFEX,
	CBT_SourceBuf ,                //����Դ����С�ڷ�ֵ�ص�
	CBT_AudioCBFun ,               //��Ƶ�ص�
	CBT_VerifyCBFun,               //ˮӡ��֤�ص�
	CBT_EncChangeCBFun,            //�����ʽ�ı�ص�
	CBT_FileEnd,                        //�ļ����Ž����ص�
	CBT_DemuxCBFun,
	CBT_DrawCBFunEx,
	CBT_VisibleDec,
	CBT_TOTAL ,
}CALLBACK_TYPE;

//����ص��Ĳ����ص�����,added by wlj 2009.1.19
typedef struct 
{
	long nUser ;
}PARAM_DEC;

typedef void (__stdcall *Callback_Dec)(long nPort,char * pBuf,long nSize,
        FRAME_INFO * pFrameInfo, long nReserved1,long nReserved2) ; //��ȡ�������ݣ����û����д���

typedef struct 
{
	long nUser ;
}PARAM_VISIBLEDEC;

//��Ƶ�ص��Ĳ����ͻص�����
typedef struct 
{
	long nUser ;
}PARAM_DISPLAY;
typedef void (__stdcall *Callback_Display)(long nPort,char * pBuf,long nSize,
		long nWidth,long nHeight,long nStamp,long nType,long nReserved);//ץͼ�ص�����

//GDI�ص��Ĳ����ͻص�����
typedef struct 
{
	LONG nUser;
}PARAM_DRAW;
typedef void (__stdcall *Callback_Draw)(long nPort,HDC hDc,LONG nUser);

//������GDI�ص��Ĳ����ͻص�����
typedef struct 
{
	LONG nUser;
}PARAM_DRAWEX;
typedef void (__stdcall *Callback_DrawEx)(long nPort,long nReginNum, HDC hDc,LONG nUser);



typedef struct 
{
	LONG nUser ;
}PARAM_FILEREF;
typedef void (__stdcall *Callback_FileRef)(DWORD nPort,DWORD nUser) ;

typedef void (__stdcall *Callback_FileRefEx)(DWORD nPort, BOOL bIndexCreated, DWORD nUser) ;

//����ԴС�ڷ�ֵ�ص��Ĳ����ͻص�����
typedef struct 
{
	DWORD nThreShold;
	LONG nUser;
}PARAM_SOURCEBUF;
typedef void (__stdcall *Callback_SourceBuf)(long nPort,DWORD nBufSize,DWORD dwUser,void*pResvered);


//��Ƶ�ص��Ĳ����ͻص�����
typedef struct 
{
	long nUser ;
}PARAM_AUDIO;
typedef void (__stdcall * Callback_Audio)(long nPort, char * pAudioBuf,
								 long nSize, long nStamp, long nType, long nUser);

//����ı�ʱ�ص������ͻص�����
typedef struct {
	long nUser;
}PARAM_ENCCHANGE;
typedef void (__stdcall *Callback_EncChange)(long nPort,long nUser);  //����ı�ʱ�ص�����

//ˮӡ��֤�ص������ͻص�����
typedef struct {
	DWORD nBeginTime;
	DWORD nEndTime;
	FRAME_POS nFilePos;
	DWORD bIsVideo;
	long nUser;
}PARAM_VERIFY;
typedef void (__stdcall *Callback_Verify)(long nPort, FRAME_POS * pFilePos, DWORD bIsVideo, DWORD nUser); 

typedef struct 
{
	LONG nUser ;
}PARAM_FILEEND;
typedef void (__stdcall *Callback_FileEnd)(DWORD nPort,DWORD nUser) ;

typedef struct 
{
	LONG nUser ;
}PARAM_DEMUX;
//���ݻص��Ļص�����
typedef void (__stdcall *Callback_Demux)(long nPort,char * pBuf,long nSize,
        void * pParam, long nReserved,long nUser) ; //��ȡ�������ݣ����û����д���

//�û��ص���Ϣ���������ص���������Ҫ���ݲ���
class CCallback
{
	LONG m_nIndex;						//�������������Ŷ˿ںţ�
	BOOL m_cbState[CBT_TOTAL];          //��ǰ���ֻص�������״̬
	BOOL m_cbStreamState;	//����ʽ�£��ص�������Ϊ0�����Դ������ʣ������С�ڵ��ڷ�ֵʱ�ص�

	PARAM_DEC mParam_decCB;  //added by wlj 2009.01.19
	Callback_Dec cb_Dec;                  //����ָ��
	Callback_Dec temp_Dec ;

	PARAM_VISIBLEDEC mParam_visibleDecCB; 
	Callback_Dec cb_VisibleDec; 
	Callback_Dec temp_VisibleDec;

	PARAM_DISPLAY mParam_display;
	Callback_Display cb_Display;
	Callback_Display temp_Display ;

	PARAM_DRAW mParam_draw;
//	Callback_Draw cb_Draw;

	PARAM_FILEREF mParam_fileref ;
	Callback_FileRef cb_FileRef ;
	Callback_FileRef temp_FileRef ;

	Callback_FileRefEx cb_FileRefEx;
	Callback_FileRefEx temp_FileRefEx;
	
	PARAM_SOURCEBUF mParam_sourcebuf;
	Callback_SourceBuf cb_Sourcebuf;
	Callback_SourceBuf temp_SourceBuf ;

	PARAM_AUDIO mParam_audio;
	Callback_Audio cb_Audio;
	Callback_Audio temp_Audio ;

	PARAM_VERIFY mParam_verify;
	Callback_Verify cb_Verify;
	Callback_Verify temp_Verify ;

	PARAM_ENCCHANGE mParam_encchange;        
	Callback_EncChange cb_EncChange;
	Callback_EncChange temp_EncChange ;

	PARAM_FILEEND  mParam_fileend;    
	Callback_FileEnd    cb_FileEnd ;
	Callback_FileEnd    temp_FileEnd ;

	PARAM_DEMUX  mParam_demux;
	Callback_Demux    cb_demux;
	Callback_Demux    temp_demux;
public:

	CCallback(LONG nPort);
	~CCallback();
	Callback_Draw cb_Draw;
	Callback_Draw temp_Draw ;

	PARAM_DRAWEX mParam_drawEx;
	Callback_DrawEx cb_DrawEx;
	Callback_DrawEx temp_DrawEx ;

		//���ûص�
	BOOL SetDecCallBack(Callback_Dec pcbDec,BOOL IfSet = TRUE);
	BOOL SetDecCallBackEx(Callback_Dec pcbDec,long nUser,BOOL IfSet = TRUE);
	BOOL SetDisplayCallBack(Callback_Display pcbDisplay, long nUser);
	BOOL SetDrawCallback(Callback_Draw pcbDraw, long nUser);
	BOOL SetDrawExCallback(Callback_DrawEx pcbDrawEx, long nReginNum, long nUser);
	BOOL SetSourceBufCallBack(Callback_SourceBuf pcbSourceBuf, DWORD nThreShold, long dwUser, void *pReserved);
	BOOL ResetSourceBufFlag();
	BOOL SetAudioCallBack(Callback_Audio pcbAudio, long nUser);
	BOOL SetVerifyCallBack(Callback_Verify pcbfunVerify, DWORD nBeginTime, DWORD nEndTime, long nUser);
	BOOL SetEncChangeCallBack(Callback_EncChange pcbEncChange, long nUser);
	BOOL SetFileRefCallBack(Callback_FileRef pcbFileRef,DWORD nUser) ;
	BOOL SetFileEndCallBack(Callback_FileEnd pcbFileEnd, DWORD nUser) ;
	BOOL SetDemuxCallBack(Callback_Demux pcbDemux, long nUser) ;
	BOOL SetVisibleDecCallBack(Callback_Dec pcbDec,long nUser,BOOL IfSet = TRUE);
	BOOL SetFileRefCallBackEx(Callback_FileRefEx pcbFileRef, DWORD nUser);
public:
		//���ݲ������ûص�����
	BOOL ProcessDec(DEC_TYPE type,BYTE* pBuf,int nSize,int width,int height); // 1��Ƶ 2 ��Ƶ
	BOOL ProcessVisibleDec(DEC_TYPE type,BYTE* pBuf,int nSize,int width,int height);
	BOOL ProcessDisplay(BYTE* pBuf,int width,int height);	
	BOOL ProcessAudio(BYTE * pAudioBuf, long nSize, long nStamp, long nType);
	BOOL ProcessDemux(char * pBuf,long nSize, void* pParam);
	BOOL ProcessSourceBuf();
	BOOL ProcessVerify();
	BOOL ProcessEncChange();
	BOOL ProcessDraw(HDC hDC) ;
	BOOL ProcessDrawEx(long nReginNum, HDC hDC) ;
	BOOL ProcessFileRef() ;
	BOOL ProcessFileRefEx(BOOL bIndexCreated) ;
	BOOL ProcessFileEnd() ;

public:
	BOOL GetCBStatus(CALLBACK_TYPE nStatus);        //��ȡĳ���ͻص���״̬
	
};

#endif
