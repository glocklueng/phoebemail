
/*
* Copyright (c) 2008, ���ݰ�г������޹�˾
* All rights reserved.
*
* �ļ����ƣ�AX_RW_Mutex.cpp
* �ļ���ʶ��
* ժ����Ҫ��AX��д�� .cpp�ļ�������win32&linux
*

* ��ǰ�汾��1.0
* ԭ���ߡ����ּ���
* ������ڣ�2008��5��15��
* �޶���¼������
*/

#include <AX_RW_Mutex.h>

//#include "AX_RW_Mutex.inl"


AX_RW_Mutex::AX_RW_Mutex(int type, const char *name, void *arg)
 :
process_lock_ (0),
removed_ (0)
{
	if (AX_OS::rwlock_init (&this->lock_, type, name, arg) != 0)
		//error
		//noop
		return ;
}

AX_RW_Mutex::~AX_RW_Mutex(void)
{
	this->remove();
}

