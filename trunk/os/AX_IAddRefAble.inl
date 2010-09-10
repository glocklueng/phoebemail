/*
* Copyright (c) 2008, ���ݰ�г������޹�˾
* All rights reserved.
*
* �ļ����ƣ�AX_IAddRefAble.inl
* �ļ���ʶ��
* ժҪ������ָ�룬�����ڶ��߳�ָ�밲ȫ���ݡ�
*
* ��ʷ��������2006��7��26�գ�������(li_mingjiang@dahuatech.com)
*		����2008��5��21�գ��ּ���(linjy@anxiesoft.cn)
*		��д��2008��6��11�գ��ּ���(linjy@anxiesoft.cn)
*
*/

inline AX_IAddRefAble::AX_IAddRefAble()
{
	_ref = 0;
}

inline AX_IAddRefAble::~AX_IAddRefAble()
{
}

inline int
AX_IAddRefAble::addRef(void)
{
	_mutex.acquire();
	int ret = (++_ref);
	_mutex.release();

	return ret;
}

inline int
AX_IAddRefAble::release(void)
{
	_mutex.acquire();
	int ret = (--_ref);
	_mutex.release();

	//if ret < 0, the user program must check why. and prevent it.
	if (ret <= 0)
	{
		delete this;
		return 0;
	}

	return ret;
}

/* linux�µ�atomic_tϵ�к����ƺ����ܱ�֤�߳�ͬ��������ʵ��
inline AX_IAddRefAble::AX_IAddRefAble()
{
#ifdef WIN32
	_ref = 0;
#else
	_ref.counter = 0;
#endif
}

inline AX_IAddRefAble::~AX_IAddRefAble()
{

}

inline int
AX_IAddRefAble::addRef(void)
{
#ifdef WIN32
	return InterlockedIncrement(&_ref);
#else
	return atomic_inc_return(&_ref);
#endif
}

inline int
AX_IAddRefAble::release(void)
{
#ifdef WIN32
	if (InterlockedDecrement(&_ref) <= 0)
	{
		delete this;
		return 0;
	}

	return _ref;
#else
	if(atomic_dec_return(&_ref) <= 0)
	{
		delete this;
		return 0;
	}

	return _ref.counter;
#endif
}
*/