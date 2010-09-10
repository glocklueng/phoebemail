
/*
* Copyright (c) 2008, ���ݰ�г������޹�˾
* All rights reserved.
*
* �ļ����ƣ�AX_Mutex.cpp
* �ļ���ʶ��
* ժ����Ҫ��AX������ .cpp�ļ�
*

* ��ǰ�汾��1.0
* ԭ���ߡ����ּ���
* ������ڣ�2008��5��15��
* �޶���¼������
*/

//#include "../inlcude/AX_Mutex.h"
#include <AX_Mutex.h>

//#include "AX_Mutex.inl"


AX_Mutex::AX_Mutex(int type)
 :
process_lock_ (0),
removed_ (0)
{
	// ACE_TRACE ("ACE_Mutex::ACE_Mutex");
#ifdef AX_HAS_PROCESS_MUTEX
	if (type == USYNC_PROCESS)
	{
		//process mutex, to be implemented
	}
	else
	{
#endif
		if (AX_OS::thread_mutex_init(&this->lock_, type) != 0)
		{
			//error
			//TRACE ..
		}
#ifdef AX_HAS_PROCESS_MUTEX
	}
#endif
}

AX_Mutex::~AX_Mutex(void)
{
	this->remove();
}

