#ifndef __GROUPPLAYER_INC__
#define __GROUPPLAYER_INC__

#include "AX_Mutex.h"
#include "MY_IAddRefAble.h"
#include <vector>
using namespace std;

class CNBPlayer;
class CGroupPlayer : public MY_IAddRefAble
{
public:
	CGroupPlayer(int nGroupId);
	virtual ~CGroupPlayer(void);

	friend class CGroupManage;

//�ӿ�
public:
	void	PausePlay(bool bPause);
	void	SetRateScale(double fRateScale);

	int		GetGroupId();

//��������
protected:
	int		AddPlayer(CNBPlayer* pPlayer);
	int		DelPlayer(CNBPlayer* pPlayer);

//�ص�
public:
	void	OnTime(int nTimerId);

//����
protected:
	AX_Mutex	m_mtxData;

	struct PlayerInfo
	{
		CNBPlayer*	pPlayer;

		int			nSetDelay;				//���һ��ͬ����Delay��ֵ
		uint32		nLastSynchTime;			//���һ�η���ͬ����Ϣ��ʱ��
		uint32		nLastSynchNextFramePaintTime;
		bool		bSynchLimit;

		uint64		nNextFrameTime;			//��ʱ������һ֡����Ƶʱ��
		uint32		nNextPaintTime;			//��ʱ������һ֡�Ļ���ʱ��(����ʱ�����)
	};
	vector<PlayerInfo> m_vecPlayer;
	uint32		m_nLastOnTimeTime;			//���һ��ONTIME��ʱ��
	uint64		m_nLastOnTimeVideoTime;		//

	int			m_nGroupId;
	int			m_nWatchTimerId;
	bool		m_bPausePlay;
	double		m_fRateScale;
protected:
	void		InitPlayerInfoData(PlayerInfo* pInfo);
};

#endif //__GROUPPLAYER_INC__