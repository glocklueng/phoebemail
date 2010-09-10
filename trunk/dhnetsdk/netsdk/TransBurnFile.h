// Tread.h: interface for the CTread class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TREAD_H__948D05D2_192C_407A_BBDD_E0BB0886FCD4__INCLUDED_)
#define AFX_TREAD_H__948D05D2_192C_407A_BBDD_E0BB0886FCD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdafx.h"
#include <map>

class CRef
{
public:
	CRef():m_lLifeCount(1)
	{
	}
	virtual ~CRef()
	{
	}
	int AddRef()
	{
		if (InterlockedIncrement(&m_lLifeCount) <= 1)
		{
			InterlockedDecrement(&m_lLifeCount);
			return 0;
		}
		return m_lLifeCount;
	}

	int DecRef()
	{
		if (m_lLifeCount <= 0)
		{
			return 0;
		}
		if (InterlockedDecrement(&m_lLifeCount) <= 0)
		{
			delete this;
			return 0;
		}
		return m_lLifeCount;
	}
private:
	LONG			m_lLifeCount;
};

class CTask : public CRef
{
public:
	CTask(){}
	virtual ~CTask(){}
	
public:
	//����
	virtual int	Task() = 0;
	//�����Ƿ�׼����
	virtual int Prepare() = 0;
	virtual int IsPrepared() = 0;
	//�����Ƿ����
	virtual int Done() = 0;
	virtual int IsDone() = 0;

};

/*
 * ��������.	
 */
class CTaskCenter
{
public:
	// ˳����ʽӿ�
	CTask*	GetFirstTask(void** pvPairData = NULL);
	CTask*	GetNextTask(void** pvPairData = NULL, CTask* pTask = NULL);//��ȡ����ʹ��Ȩ
	BOOL	BackTask(CTask* pTask);			 //��������ʹ�ú���Ҫ��������ʹ��Ȩ
	BOOL	IsEnd(void);

	// �������ɾ���ӿ�
	void*	GetPairData(CTask* pTask);
	BOOL	AddTask(CTask *pTask, void* pvPairData = NULL);
	BOOL	DecTask(CTask *pTask);
	DWORD	TaskNum(void);//������Ŀ
	
private:
	SPTools::CReadWriteMutex	m_csListTask;
	std::map<CTask *, void*>	m_mapTask;
	//û�ж�����iterator,����Ϊû�ж���̹߳�������.
	std::map<CTask *, void*>::iterator m_itTask;
};

class CDynamicThread //: public IThread
{
public:
	CDynamicThread();
	virtual ~CDynamicThread();
	friend void WINAPI WorkThread(void* pvData);
public:
	int Run();
	int Stop();
public:
	//��̬��������������������������Ҫ�ܵ����ƣ���Ȼ�����ڴ����͡�
	enum eLifeCountMode{eFromTaskPrepared, eFromTaskDone};
	enum eTaskType{eBurnFileTrans};
	CTask*	CreateTask(eTaskType eType, eLifeCountMode eMode, DWORD m_dwLife, DWORD dwUserData);
	int		DeleteTask(CTask* pTask);
	int		GetUserData(CTask* pTask, DWORD& dwUserData);

private:
	int	ExitThread(void);
	int WorkFunc(DWORD dwTimePass);
	struct TaskLifecycle
	{
		eLifeCountMode	m_eMode;
		DWORD			m_dwLife;
		DWORD			m_dwUserData;
	};	
private:
	//���ϣ�����ݹ����ɷ������ⶨ��.
	CTaskCenter	m_cTaskCenter;

	OS_THREAD	m_osThread;
	OS_EVENT	m_osEvent;

	BOOL		m_bRun;						//�Ƿ��ڹ���.
};

/************************************************************************/
/* ��¼�ļ��ϴ�                                                         */
/************************************************************************/
typedef void (CALLBACK *fTransFileCallBack)(LONG lHandle, int nTransType, int nState, int nSendSize, int nTotalSize, DWORD dwUser);
class CManager;
struct afk_device_prob_s;

class CTaskBurnFileTrans : public CTask
{
public:
	CTaskBurnFileTrans();
	virtual ~CTaskBurnFileTrans();
	int	Task();
	int Prepare();
	int IsPrepared();
	int Done();
	int IsDone();
public:
	int SetParam(CManager *mgr, char *szFileName, int nFileSize, char* szIP, int nPort, fTransFileCallBack cbCallBack, DWORD dwUser, int nWaittime = 500);
private:
	//�����ļ�
	FILE*				m_pFileSend;

	char				m_szIP[48];
	int					m_nPort;
	int					m_nWaittime;

	fTransFileCallBack	m_cbCallBack;
	DWORD				m_dwUser;
	int					m_nSendSize;//�ѷ��͵Ĵ�С
	int					m_nFileSize;

	CManager*			m_mgr;
	afk_device_prob_s*	m_prob;
	LONG				m_lTcpHandle;

	BOOL				m_bPrepared;
	BOOL				m_bDone;
};


#endif // !defined(AFX_TREAD_H__948D05D2_192C_407A_BBDD_E0BB0886FCD4__INCLUDED_)
