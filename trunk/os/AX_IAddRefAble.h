/*
* Copyright (c) 2008, ���ݰ�г������޹�˾
* All rights reserved.
*
* �ļ����ƣ�AX_IAddRefAble.h
* �ļ���ʶ��
* ժҪ������ָ�룬�����ڶ��߳�ָ�밲ȫ���ݡ�
*
* ��ʷ��������2006��7��26�գ�������(li_mingjiang@dahuatech.com)
*		����2008��5��21�գ��ּ���(linjy@anxiesoft.cn)
*		��д��2008��6��11�գ��ּ���(linjy@anxiesoft.cn)
*
*/
//////////////////////////////////////////////////////////////////////

#if !defined AX_IADDREFABLD_INCLUDE
#define AX_IADDREFABLD_INCLUDE

#include "AX_Mutex.h"

class AX_IAddRefAble
{
public:
	AX_IAddRefAble();
	virtual ~AX_IAddRefAble();

	virtual int addRef(void);
	virtual int release(void);

protected:
	int	_ref;
	AX_Mutex _mutex;
};

/* linux�µ�atomic_tϵ�к����ƺ����ܱ�֤�߳�ͬ��������ʵ��
#if defined(WIN32)
	#include "winsock2i.h"
#else
	#include <pthread.h> 

	#ifdef LINUX
		#include "AX_Atomic.h"
	#else
		#include <asm/asm-armnommu/atomic.h>
	#endif
#endif

class AX_IAddRefAble
{
public:
	AX_IAddRefAble();
	virtual ~AX_IAddRefAble();

	virtual int addRef(void);
	virtual int release(void);

protected:

#ifdef WIN32
	long _ref;
#else
	atomic_t _ref;
#endif
};
*/

#include "AX_IAddRefAble.inl"

#endif // !defined AX_IADDREFABLD_INCLUDE
