
#ifndef _AutoBuffer_H_
#define _AutoBuffer_H_

#include "Referable.h"

using namespace SPTools;

class CAutoBuffer : public IReferable
{
	friend class IReferable;
public:
	virtual ~CAutoBuffer(void);

	//�����Ի�����aBufferΪ���ݵ���ά�����棬isbackup��ʾ�ڲ��Ƿ���һ��
	//������ֹ������븴�ƣ����ȫ�������ɲ�����,���ӹ��ⲿ�����������ƺ��ٹ����ⲿ������
	static CAutoBuffer * CreateBuffer( int nSize, char * aBuffer = NULL, bool isbackup = false );
	static CAutoBuffer * CreateBuffer( int nSize, const char * aBuffer );

	char * GetBuf();
	unsigned int BufferSize();

private:
	CAutoBuffer(void);
	BOOL SetBuf( int nSize, char * aBuffer = NULL );
	BOOL CopyBuf( int nSize, const char * aBuffer );

	char * m_buff;
	unsigned int m_datalen;
};

typedef CReferableObj<CAutoBuffer> IBufferRef;

#endif // _AutoBuffer_H_

