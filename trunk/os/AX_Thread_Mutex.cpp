
/*
* Copyright (c) 2008, ���ݰ�г������޹�˾
* All rights reserved.
*
* �ļ����ƣ�AX_Thread_Mutex.cpp
* �ļ���ʶ��
* ժ����Ҫ��AX�̻߳����� .cpp�ļ�
*

* ��ǰ�汾��1.0
* ԭ���ߡ����ּ���
* ������ڣ�2008��5��20��
* �޶���¼������
*/

#include <AX_Thread_Mutex.h>

//#include "AX_Thread_Mutex.inl"


AX_Thread_Mutex::AX_Thread_Mutex()
 :
removed_ (0)
{
	int result = AX_OS::thread_mutex_init(&this->lock_, 0);
	//printf("after AX_Thread_Mutex::AX_Thread_Mutex result:%d\n",result);
}

AX_Thread_Mutex::~AX_Thread_Mutex(void)
{
	this->remove();
}

