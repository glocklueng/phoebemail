
/*
* Copyright (c) 2008, ���ݰ�г������޹�˾
* All rights reserved.
*
* �ļ����ƣ�AX_RW_Thread_Mutex.h
* �ļ���ʶ��
* ժ����Ҫ��AX��д�߳��� .h�ļ�������win32&linux
*

* ��ǰ�汾��1.0
* ԭ���ߡ����ּ���
* ������ڣ�2008��5��20��
* �޶���¼������
*/

#ifndef AX_RW_THREAD_MUTEX_INCLUDE
#define AX_RW_THREAD_MUTEX_INCLUDE

#include "AX_RW_Mutex.h"

class AX_RW_Thread_Mutex : public AX_RW_Mutex
{
	AX_RW_Thread_Mutex (const char *name = 0,	void *arg = 0);

	/// Default dtor.
	~AX_RW_Thread_Mutex (void);
};
#include "AX_RW_Thread_Mutex.inl"

#endif

