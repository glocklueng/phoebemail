
/*
* Copyright (c) 2008, ���ݰ�г������޹�˾
* All rights reserved.
*
* �ļ����ƣ�AX_Thread_Mutex.h
* �ļ���ʶ��
* ժ����Ҫ��AX�̻߳����� .h�ļ�
*

* ��ǰ�汾��1.0
* ԭ���ߡ����ּ���
* ������ڣ�2008��5��20��
* �޶���¼������
*/

#ifndef AX_THREAD_MUTEX_INCLUDE
#define AX_THREAD_MUTEX_INCLUDE

#include "AX_OS.h"

class AX_Thread_Mutex
{
public:
	/// Initialize the mutex.
	AX_Thread_Mutex ();

	/// Implicitly destroy the mutex.
	~AX_Thread_Mutex (void);

	/// Explicitly destroy the mutex.
	int remove (void);

	int acquire (void);

	int acquire (timeval &tv);

	int acquire (timeval *tv);

	int tryacquire (void);

	int release (void);

	int acquire_read (void);
	int acquire_write (void);
	int tryacquire_read (void);
	int tryacquire_write (void);

//protected:
	AX_Mutex_t lock_;
	int removed_;

private:
	// Prevent assignment and initialization.
	void operator= (const AX_Thread_Mutex &);
	AX_Thread_Mutex (const AX_Thread_Mutex &);

};

#include "AX_Thread_Mutex.inl"

#endif

