#ifndef __RESMANAGE_INC__
#define __RESMANAGE_INC__

#include <map>
#include <list>
#include "AX_Mutex.h"
#include "videorender.h"
#include "INBPlayer.h"
using namespace std;

class CResManage
{
public:
	CResManage(void);
	~CResManage(void);

protected:
	static CResManage m_staticThis;
public:
	static CResManage* Instance();

//��ʼ��
protected:
	bool m_bManageInit;
public:
	bool InitManage();
	void UnInitManage();

//��ͼ��Դ�ı���
protected:
	AX_Mutex		m_mtxRander;
	map<HWND, list<VideoRender*> >	m_mapRander;
public:
	void			SaveRander(HWND hWnd, VideoRender* pRander);
	VideoRender*	LoadRander(HWND hWnd);

//�˿���Դ����
protected:
	AX_Mutex		m_mtxPort;
	list<int>		m_listPort[StreamSourceType_Num];
	list<uint32>	m_listPortBufSize[StreamSourceType_Num];
public:
	void			SavePort(int nDevType, int nPort, uint32 nBufSize);		//nDevTypeС��2
	int				LoadPort(int nDevType, uint32 nBufSize);				//��1Ϊʧ��

//����������
protected:
	AX_Mutex		m_mtxFrameBuffer;
	list<char*>		m_listFrameBuffer;
public:
	void			SaveFrameBuffer(char* pBuf);
	char*			LoadFrameBuffer();

//��������
public:
	void ClearAllResource();
};

#endif //__RESMANAGE_INC__