#ifndef FIFOBUFFER_H
#define FIFOBUFFER_H
#include <windows.h>
#include "decode.h"
// ֻҪ�����ڲ���¼������Ϣ
struct DhAVFrame 
{
	DhAVFrame *prev;
	DhAVFrame *next;	
	unsigned char *context;	// ����ָ��
	int width ;
	int height ;
	int size;
	//Frame bit rate
	int frameLen;
	int frameType;
	//IVS
	int ivsobjnum;
	DH_IVS_OBJ* ivsObjList;
	DH_IVS_PREPOS tIvsPrePos;
};

class FifoBuffer 
{
public:
	FifoBuffer();
	~FifoBuffer();

	int init(int count,int chunksize);
	int reset();
	int resize(int chunksize);
	int clear();
	bool write(DhAVFrame* vframe) ;
	bool read(DhAVFrame* vframe) ;
	int chunkCount();//��Ч���� ����
	void setlock(bool iflock) ;
	bool getlock();
	BYTE* GetLastFrame();
	BYTE* GetNextWritePos();

	void SetbReadNull(bool ifReadNull){m_bReadNull = ifReadNull;}
	bool GetIfReadNull(){return m_bReadNull;}

	void GetLastFrameBuf(unsigned char* pBuf){m_dataFrame.context = pBuf;}

private:		
	bool createFreeList();	
	void cleanFreeList();
	void cleanDataList();
	
	DhAVFrame *getFreeNode();
	DhAVFrame *getDataNode();
	
	void appendToFreeList(DhAVFrame *item);
	void appendToDataList(DhAVFrame *item);

private:

	unsigned char *m_mempool;//�ڴ��

	bool m_ifLock ;//�����������write������һֱ�ȴ��пյĻ���飬�ڶ�λ����ʱ��������ΪFalse,��ʹwrite�������췵��
	bool m_inited; // ��ʼ���ɹ���־
	int m_count; // �ڵ�����
	int m_chunksize;
	DhAVFrame *m_freeQueueFirst;
	DhAVFrame *m_freeQueueLast;
	int m_freeCount;//�յĿ����

	DhAVFrame *m_outQueueFirst;
	DhAVFrame *m_outQueueLast;
	int m_outCount;//��Ч���ݿ���

	DhAVFrame m_dataFrame;
	CRITICAL_SECTION m_DataAccessLock ;

	bool m_bReadNull;
};

#endif 




















