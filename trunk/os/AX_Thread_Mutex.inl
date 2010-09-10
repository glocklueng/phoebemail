
/*
* Copyright (c) 2008, ���ݰ�г������޹�˾
* All rights reserved.
*
* �ļ����ƣ�AX_Thread_Mutex.inl
* �ļ���ʶ��
* ժ����Ҫ��AX�̻߳����� .inl�ļ�
*

* ��ǰ�汾��1.0
* ԭ���ߡ����ּ���
* ������ڣ�2008��5��20��
* �޶���¼������
*/

inline int 
AX_Thread_Mutex::remove (void)
{
	int result = 0;

	if (this->removed_ == 0)
	{
		this->removed_ = 1;
		result = AX_OS::thread_mutex_destroy (&this->lock_);
	}

	return result;
}

inline int 
AX_Thread_Mutex::acquire (void)
{
	return AX_OS::thread_mutex_lock (&this->lock_);
}

inline int 
AX_Thread_Mutex::acquire (timeval &tv)
{
	return AX_OS::thread_mutex_lock (&this->lock_, tv);
}

inline int 
AX_Thread_Mutex::acquire (timeval *tv)
{
	return AX_OS::thread_mutex_lock (&this->lock_, tv);
}

inline int 
AX_Thread_Mutex::tryacquire (void)
{
	return AX_OS::thread_mutex_trylock (&this->lock_);
}

inline int 
AX_Thread_Mutex::release (void)
{
	return AX_OS::thread_mutex_unlock (&this->lock_);
}

inline int 
AX_Thread_Mutex::acquire_read (void)
{
	return AX_OS::thread_mutex_lock (&this->lock_);
}

inline int 
AX_Thread_Mutex::acquire_write (void)
{
	return AX_OS::thread_mutex_lock (&this->lock_);
}

inline int 
AX_Thread_Mutex::tryacquire_read (void)
{
	return AX_OS::thread_mutex_trylock (&this->lock_);
}

inline int 
AX_Thread_Mutex::tryacquire_write (void)
{
	return AX_OS::thread_mutex_trylock (&this->lock_);
}


