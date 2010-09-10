
/*
* Copyright (c) 2008, ���ݰ�г������޹�˾
* All rights reserved.
*
* �ļ����ƣ�AX_Thread.cpp
* �ļ���ʶ��
* ժ����Ҫ��AX�߳��� .cpp�ļ�
*

* ��ǰ�汾��1.0
* ԭ���ߡ����ּ���
* ������ڣ�2008��5��19��
* �޶���¼������
*/

#include <AX_Thread.h>

//#include "AX_Mutex.inl"

size_t
AX_Thread::spawn_n (size_t n,
					AX_THR_FUNC func,
					void *arg,
					long flags,
					long priority,
					void *stack[],
					size_t stack_size[])
{
	AX_thread_t t_id;
	size_t i;

	for (i = 0; i < n; i++)
		// Bail out if error occurs.
		if (AX_OS::thr_create (func,
			arg,
			flags,
			&t_id,
			0,
			priority,
			stack == 0 ? 0 : stack[i],
			stack_size == 0 ? 0 : stack_size[i]) != 0)
			break;

	return i;
}

size_t
AX_Thread::spawn_n (AX_thread_t thread_ids[],
					size_t n,
					AX_THR_FUNC func,
					void *arg,
					long flags,
					long priority,
					void *stack[],
					size_t stack_size[],
					AX_hthread_t thread_handles[])
{
	size_t i;

	for (i = 0; i < n; i++)
	{
		AX_thread_t t_id;
		AX_hthread_t t_handle;

		int result =
			AX_OS::thr_create (func,
			arg,
			flags,
			&t_id,
			&t_handle,
			priority,
			stack == 0 ? 0 : stack[i],
			stack_size == 0 ? 0 : stack_size[i]);

		if (result == 0)
		{
			if (thread_ids != 0)
				thread_ids[i] = t_id;
			if (thread_handles != 0)
			{
				thread_handles[i] = t_handle;
			}
		}
		else
			// Bail out if error occurs.
			break;
	}

	return i;
}
