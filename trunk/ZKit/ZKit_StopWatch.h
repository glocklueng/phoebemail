#ifndef _ZKit_StopWatch_h_
#define _ZKit_StopWatch_h_

#include "ZKit_Config.h"

BEGIN_ZKIT

//�����, �����ж��Ƿ�ʱ, �Լ�����ʱ����. by qguo.
class StopWatch
{
public:
	StopWatch(clock_t timeout = 5 * CLOCKS_PER_SEC) : m_start(clock()), m_stop(clock()), m_running(false), m_timeout(timeout)
	{

	}

	//������ʱ
	void Start()
	{
		m_running = true;
		m_start = clock();
	}

	//ֹͣ��ʱ
	void Stop()
	{
		m_running = false;
		m_stop = clock();
	}

	//���ó�ʱʱ��
	void SetTimeout(clock_t timeout)
	{
		m_timeout = timeout;
	}

	//�Ƿ�������
	bool IsRunning() const
	{
		return m_running;
	}

	//��ʼ��ֹ֮ͣ���ʱ����
	clock_t TimeSpan()
	{
		return m_stop - m_start;
	}

	//�ӿ�ʼ�����ڹ�ȥ�˶೤ʱ��
	clock_t Elapse() const 
	{
		return clock() - m_start;
	}

	//�ж��Ƿ��ѵ���ʱʱ��
	bool IsTimeout() const
	{
		return Elapse() > m_timeout;
	}

private:
	clock_t m_start;
	clock_t m_stop;
	clock_t m_timeout;
	bool    m_running;
};

#define ENABLE_TIME_COST_PRINT 1

class AutoClock
{
public:
	AutoClock(const char* job = "job") : m_start(clock()), m_stopped(false)
	{
		strncpy(m_job, job, 64);
	}

	~AutoClock()
	{
		Stop();
	}

	void Start()
	{
		m_stopped = false;
		m_start = clock();
	}

	void Stop()
	{
#ifdef ENABLE_TIME_COST_PRINT
		if (!m_stopped)
		{
			clock_t stop = clock();
			printf("\n%s costs %d ticks!", m_job, stop - m_start);
			m_stopped = true;
		}
#endif
	}

private:
	clock_t m_start;
	char m_job[64];
	bool m_stopped;
};

END_ZKIT
#endif // _ZKit_StopWatch_h_
