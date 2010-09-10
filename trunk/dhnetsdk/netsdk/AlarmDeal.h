/*
* Copyright (c) 2009, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �����ƣ�����������
* ժ��Ҫ������������ģ�顣
*
*/
//////////////////////////////////////////////////////////////////////////

#ifndef _ALARMDEAL_H_
#define _ALARMDEAL_H_

class CManager;

class CAlarmDeal  
{
public:

	/* ������Ϣ�ṹ */
	typedef struct
	{
		afk_channel_s  *channel;
	} st_Alarm_Info;


	class SearchAIbydevice;
	friend class SearchAIbydevice;

public:
	CAlarmDeal(CManager *pManager);
	virtual ~CAlarmDeal();

public:
	
	/* ��ʼ�� */
	int							Init(void);

	/* ���� */
	int							Uninit(void);

	/* ��ʼ֡�� */
	int							StartListen(LONG lLoginID);
	int							StartListenEx(LONG lLoginID);

	/* ֹͣ֡�� */
	int							StopListen(LONG lLoginID);

public:

	static	int	__stdcall		DeviceStateFunc(
									afk_handle_t object,	/* �����ṩ�� */
									unsigned char *data,	/* ������ */
									unsigned int datalen,	/* ���ݳ��� */
									void *param,			/* �ص����� */
									void *userdata);
private:

	list<st_Alarm_Info*>		m_lstAlarm;
	DEVMutex						m_csAlarm;

private:
	CManager*		m_pManager;

};

class CAlarmDeal::SearchAIbydevice
{
	LONG m_ldevice;
public:
	SearchAIbydevice(LONG ldevice):m_ldevice(ldevice){}

	bool operator()(st_Alarm_Info*& ai)
	{
		return m_ldevice == (LONG)(ai?ai->channel->get_device(ai->channel):0);
	}
};


#endif // _ALARMDEAL_H_

