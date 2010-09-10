#ifndef __GROUPMANAGE_INC__
#define __GROUPMANAGE_INC__

#include "AX_Mutex.h"
#include "TimerManage.h"
#include "AX_IAddRefAble.h"
#include <map>
using namespace std;

class CNBPlayer;
class CGroupPlayer;
class CGroupManage
{
public:
	CGroupManage(void);
	~CGroupManage(void);

//ȫ��
protected:
	static CGroupManage m_staticThis;
public:
	static CGroupManage* Instance();

//��ʼ��
protected:
	bool m_bManageInit;
public:
	bool InitManage();
	void UnInitManage();

//
public:
	bool AddPlayerToGroup(CNBPlayer* pPlayer, int nGroupId);			//nGroupId������0
	void DelPlayerFromGroup(CNBPlayer* pPlayer, int nGroupId);
	CGroupPlayer* GetGroupPlayer(int nGroupId);

//����
protected:
	AX_Mutex m_mtxData;
	map<int, CGroupPlayer*> m_mapGroup;

//��ʱ��
protected:
	static void StaticOnTimerFunc(int nTimerId, int nContext);
	void OnTimerFunc(int nTimerId, int nContext);
public:
	OnTimerFuncType		GetOnTimerCB();
};

#endif //__GROUPMANAGE_INC__