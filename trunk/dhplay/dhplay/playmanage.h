   /********************************************************************
	created:	2006/01/10
	created:	10:1:2006   8:51
	filename: 	playmanage.h
	file base:	playmanage
	file ext:	h
	author:		chenmy
	
	purpose:	
*********************************************************************/
#ifndef PLAYMANAGE_H
#define PLAYMANAGE_H

#include "stdafx.h"
#include "play.h"
#include "callback.h"
#include "HI_PLAY_AudioIN.h"
#ifdef DHVECPLAY
	#include "dhvecplay.h"
#else
	#include "dhplay.h"
#endif

/*#include "Multimon.H"*/
#include <vector>

#include "AccurateTimer.h"

#define MAX_CHUNKSIZE 65536

//sdk�İ汾����
#ifdef DHVECPLAY
//��16λ��ʾ��ǰ��build�š�9~16λ��ʾ���汾�ţ�1~8λ��ʾ�ΰ汾�š�
#define  VERSION  0x1207  //��ʾxx.yy
#define  BUILD_VER 0x0200  //����汾

#else
#define VERSION 28
#define BUILD_VER 3
#define MEND_VER 3

#endif

//�˿�״̬
typedef enum _PORT_STATE
{
	PORT_STATE_FREE,
	PORT_STATE_BUSY
}PORT_STATE;

//ϵͳ��Ϣ(��Ҫ�ṩ���û���ϵͳ��Ϣ)
typedef struct _SYS_INFO 
{
	int nstatus;     //ϵͳ֧��״̬(��λ��ʾ)
	DWORD dwVersion;  //SDK�汾��
	//��������         //����ϵͳ��Ϣ
}SYS_INFO;

//��Ϣ�����Ϣ
typedef struct _MSG_INFO {
	BOOL nMsgFlag;    //1������Ч
	HWND hWnd;        //��Ϣ���ھ��
	UINT nMsg;        //��Ϣ
	_MSG_INFO(){
		nMsgFlag = FALSE ;
		hWnd = NULL ;
	}
}MSG_INFO;

struct DeviceInfo
{
	LPSTR lpDeviceDescription ;
	LPSTR lpDeviceName ;
// 	HMONITOR* hMonitor ;
}  ;
//���Ź����ඨ��

class CDHPLAY_MANAGE
{
public:
	int m_nSoundPort;                    //��ǰ��Ƶ�˿�,��ռ��ʽ
	std::vector<int> m_nShareSoundPortList ;//�����������Ŷ˿��б�
// 	int m_volume;
	int m_nFluency[FUNC_MAX_PORT];
	int m_nQuality[FUNC_MAX_PORT];      //����
	int m_nStreamMode[FUNC_MAX_PORT];
	int m_nTimer1Cnt;
	SYS_INFO m_pSysInfo;                //ϵͳ��Ϣ�������Կ���������һЩϵͳ��Ϣ
	char m_DLLPath[256+1024];//playsdk.dll���ڵ�·��
	std::vector<DeviceInfo*>DeviceInfoList ;
	int m_supportmultidevice;
	int m_error[FUNC_MAX_PORT] ;    //��������
	CRITICAL_SECTION m_interfaceCritSec[FUNC_MAX_PORT] ;   
	CDHPlay   *pDHPlay[FUNC_MAX_PORT];    //���Ŷ���ָ���
	CDHAVData *pDHFile[FUNC_MAX_PORT] ; //�����ļ�ָ���
	CDisplay  *pDisplay[FUNC_MAX_PORT] ;//��ʾ��ָ���
	CCallback *pCallback[FUNC_MAX_PORT];  //�ص�ָ���
	MSG_INFO  *pMsgFileEnd[FUNC_MAX_PORT];//�ļ����Ž�����Ϣ
	MSG_INFO  *pMsgEncChang[FUNC_MAX_PORT];    //�����ʽ�ı���Ϣ
	PORT_STATE m_ePortState[FUNC_MAX_PORT];
	DWORD      m_dwTimerType[FUNC_MAX_PORT]; //�˿ڶ�Ӧ�Ķ�ʱ������

	CACTimerManager  m_ACTimerManager;
	CRITICAL_SECTION m_PortStateCrit;

	CHI_PLAY_AudioIn* pAudioRecored;
	DhRenderManager m_YUVRenderMng;
//��Ҫ�������У�
	CDHPLAY_MANAGE();
	~CDHPLAY_MANAGE();

	int  GetCaps();           //��ȡ��ǰϵͳ��Ϣ����λȡ��
	int  CheckPort(LONG nPort);   //���˿��Ƿ������ɿ�
	DWORD GetError(LONG nPort);    //��ȡ������
	DWORD GetSdkVersion();    //��ȡ�汾��
	DWORD GetFileHeadLenth();    //��ȡ�ļ�ͷ�ĳ���
	BOOL  SetPortState(LONG lPort, PORT_STATE eState); //���ö˿�״̬
	BOOL GetPortState(LONG lPort, PORT_STATE *peState); //��ȡ�˿�״̬
	int  OpenYuvRender(int port, HWND hwnd, void (CALLBACK* DrawFun)(int nPort,HDC hDc));
	int  RenderYuv(int port, unsigned char* py, unsigned char* pu, unsigned char* pv, int width, int height);
	int  CloseYuvRender(int port);

protected:
private:
	
	void init_sysinfo();
};

extern CDHPLAY_MANAGE g_cDHPlayManage;

#endif
