
/*
* Copyright (c) 2008, ���ݰ�г������޹�˾
* All rights reserved.
*
* �ļ����ƣ�AX_RW_Thread_Mutex.cpp
* �ļ���ʶ��
* ժ����Ҫ��AX��д�߳��� .cpp�ļ�������win32&linux
*

* ��ǰ�汾��1.0
* ԭ���ߡ����ּ���
* ������ڣ�2008��5��20��
* �޶���¼������
*/

#include <AX_RW_Thread_Mutex.h>

//#include "AX_RW_Thread_Mutex.inl"


AX_RW_Thread_Mutex::AX_RW_Thread_Mutex (const char *name,	void *arg)
:
AX_RW_Mutex (AX_USYNC_THREAD, name, arg)
{
	// ACE_TRACE ("ACE_RW_Thread_Mutex::ACE_RW_Thread_Mutex");
}

