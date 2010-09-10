#ifndef _ZKit_Mutex_h_
#define _ZKit_Mutex_h_

#include "ZKit_IMutex.h"
#include "AX_OS.h"
#include "AX_Mutex.h"

BEGIN_ZKIT

//���Ѿ���AX_Mutex�������, ��Ȼ��д�����, ��Ϊ���ֲ�AX_Mutex��һ��ȱ��:
//AX_Mutex�Ľӿڶ��Ƿ�const����, ��������һ�����const��Ա������ʹ��AX_Mutex���޷�ͨ������
//����������ܳ���, ����Getter����ͨ����const��
//���������Ҳ�ṩ�򻯵Ľӿ�, ����󲿷�����
//by qguo. 2010.04.29
class Mutex : public IMutex
{
public:
	Mutex();
	~Mutex();

	virtual void Lock() const;
	virtual void Unlock() const;
private:
	mutable AX_Mutex m_mutex;
};

END_ZKIT

#endif // _ZKit_Mutex_h_
