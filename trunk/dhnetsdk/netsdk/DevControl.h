/*
* Copyright (c) 2009, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �����ƣ�������
* ժ��Ҫ�����ƹ���ģ�顣
*
*/
//////////////////////////////////////////////////////////////////////////

#ifndef _DEVCONTROL_H_
#define _DEVCONTROL_H_

#include "StdAfx.h"
#include "netsdk.h"
class CManager;

#define WAIT_TIME 200


class CDevControl  
{
public:

	/* ͸��������Ϣ�ṹ */
	typedef struct
	{
		afk_device_s*		device;
		afk_channel_s*		channel;
		unsigned int		transComtype;
		fTransComCallBack	cbFunc;
		DWORD				dwUser;

		//���ڻص���رղ�����ͬ��
		DEVMutex*			pcsLock;			

		LN_LIFECOUNT		life;
	} st_TransCom_Info;

	/* Զ��������Ϣ�ṹ */
	typedef struct
	{
		afk_device_s*		device;
		afk_channel_s*		channel;
		fUpgradeCallBack	cbUpgrade;
		DWORD				dwUser;
		OS_EVENT			hRecEvent;

		//���ڻص���رղ�����ͬ��
		DEVMutex*			pcsLock;			

		LN_LIFECOUNT		life;
	} st_Upgrade_Info;

public:
	class SearchTCI;
	friend class SearchTCI;

	class SearchUI;
	friend class SearchUI;

public:
	CDevControl(CManager *pManager);
	virtual ~CDevControl();

public:
	
	/* ��ʼ�� */
	int							Init(void);

	/* ���� */
	int							Uninit(void);

	/* �ر��豸����ͨ�� */
	int							CloseChannelOfDevice(afk_device_s* device);

	/* ��һ��͸������ */
	LONG						CreateTransComChannel(LONG lLoginID, int TransComType, 
                                      unsigned int baudrate, unsigned int databits,
                                      unsigned int stopbits, unsigned int parity,
                                      fTransComCallBack cbTransCom, DWORD dwUser);

	/* ����͸���������� */
	int							SendTransComData(LONG lTransComChannel, char *pBuffer, DWORD dwBufSize);

	/* �ر�һ��͸������ */
	int							DestroyTransComChannel(LONG lTransComChannel);

	/* ��ʼ�����豸 */
	LONG						StartUpgrade(LONG lLoginID, char *pchFileName, fUpgradeCallBack cbUpgrade, DWORD dwUser);

	LONG						StartUpgradeEx(LONG lLoginID, EM_UPGRADE_TYPE emType, char *pchFileName, fUpgradeCallBack cbUpgrade, DWORD dwUser);

	/* ������������ */
	int							SendUpgrade(LONG lUpgradeID);

	/* ���������豸 */
	int							StopUpgrade(LONG lUpgradeID);

	/*�����Ѿ��ϵ���Reset�ӿ�*/
	int							Reset(LONG lLoginID, BOOL bReset);

	/* ǿ��I֡ */
	int							MakeKeyFrame(LONG lLoginID, int nChannelID, int nSubChannel);

	/* ����������� */
	int							SetMaxFlux(LONG lLoginID, WORD wFlux);

	/*�����豸*/
	int							RebootDev(LONG lLoginID);
	
	/*�ر��豸�����ض�����֧��*/
	int							ShutDownDev(LONG lLoginID);

	/* �����豸�������������رա�Ӳ�̿��Ƶȹ��� */
	int ControlDevice(LONG lLoginID, CtrlType type, void *param, int waittime);


private:
	/* ����Ӳ�̱�ʶ */
	int							QueryDiskIndex(LONG lLoginID, int nIndex);
	/*���ڲ���Ӳ���Ƿ�߱�����������*/
	int							QueryPartitionAbility(LONG lLoginID);


private:

	/* ͸�������б� */
	list<st_TransCom_Info*>		m_lstTCI;
	DEVMutex						m_csTCI;	/* ��͸�������б� */
		
	/* �����б� */
	list<st_Upgrade_Info*>		m_lstUI;
	DEVMutex						m_csUI;		/* �������б� */


private:
	CManager*		m_pManager;
};


class CDevControl::SearchTCI
{
	LONG m_lchn;
public:
	SearchTCI(LONG lchn):m_lchn(lchn){}

	bool operator()(st_TransCom_Info*& tci)
	{
		return m_lchn == (LONG)(tci?tci->channel:0);
	}
};

class CDevControl::SearchUI
{
	LONG m_lchn;
public:
	SearchUI(LONG lchn):m_lchn(lchn){}

	bool operator()(st_Upgrade_Info*& ui)
	{
		return m_lchn == (LONG)(ui?ui->channel:0);
	}
};


#endif // _DEVCONTROL_H_


