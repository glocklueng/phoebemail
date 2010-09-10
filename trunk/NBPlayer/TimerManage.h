
/*
�������̸߳�����CPU����
��������CPU�ļ�ʱ����
��ʱ������Ϊ����
*/

#ifndef __TIMERMANAGE_INC__
#define __TIMERMANAGE_INC__

#include "AX_Mutex.h"
#include "AX_OS.h"
#include "AX_IAddRefAble.h"
#include <vector>
#include <list>
#include <map>
using namespace std;

#define DELAY_PAUSE_TIMER			0x80000000

typedef void (*OnTimerFuncType)(int nTimerId, int nContext);

class CTimerManage
{
public:
	CTimerManage(void);
	~CTimerManage(void);

protected:
	static CTimerManage m_staticThis;
public:
	static CTimerManage* Instance();

//��ʼ��
protected:
	bool m_bManageInit;
public:
	bool InitManage();
	void UnInitManage();

//��ʱ������
protected:
	struct TimerInfo
	{
		int		nTimerId;
		int		nContext;
		uint32	nPeriod;
		OnTimerFuncType funcCB;

		uint32	tLastActiveTime;
		uint32	nNextPeriod;
	};
	AX_Mutex	m_mtxTimer;
	vector<TimerInfo> m_vecTimer;
	int			m_nPreciseTimerCount;
	int			m_nTimerIdSeek;
public:
	int		SetTimer(uint32 nPeriod, int nContext, OnTimerFuncType funcCB);		//����ֵ������0
	void	DelayTimer(int nTimerId, int nDelay);								//0x80000000Ϊ��ʱ����ͣ
	void	ModifyTimerPeriod(int nTimerId, uint32 nPeriod);					//��ʱ����0
	void	KillTimer(int nTimerId);

//�߳�����
protected:
	vector<int> m_vecTimerId;
	vector<AX_hthread_t> m_vecThread;
	vector<HANDLE> m_vecSysTimer;
	bool	m_bCloseThread;

protected:
	static void CALLBACK StaticThreadProcTimer(UINT wTimerID, UINT msg, DWORD dwUser, DWORD dw1, DWORD dw2);
	static void* StaticThreadProcMy(void* pParam);
	void ThreadProcTimer(int nTimerIndex);
	void ThreadProcMy(int nTimerIndex);
};

#endif //__TIMERMANAGE_INC__