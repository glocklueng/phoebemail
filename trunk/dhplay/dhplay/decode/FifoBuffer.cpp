// FifoBuffer.cpp: implementation of the CFifoBuffer class.
//
//////////////////////////////////////////////////////////////////////
#include "fifobuffer.h"
//#define AUDIOBUFLEN 16*1024

FifoBuffer::FifoBuffer()
{
	m_mempool = 0;
	m_inited = false;	// δ��ʼ��
	m_ifLock = true ;
	m_count = 0;
	m_chunksize = 0;
	// ���ڿ�������
	m_freeQueueFirst	= 0; // ͷ
	m_freeQueueLast		= 0; // β
	m_freeCount			= 0; // ����
	// ������������
	m_outQueueFirst		= 0; // ͷ
	m_outQueueLast	  	= 0; // β
	m_outCount			= 0; // ����

	m_dataFrame.context = 0;

	InitializeCriticalSection(&m_DataAccessLock) ;
}

FifoBuffer::~FifoBuffer()
{
	clear() ;
	DeleteCriticalSection(&m_DataAccessLock) ;
}

int FifoBuffer::resize(int chunksize)
{
	int count = m_count;
	clear();
	return init(count, chunksize);
}

/*!
 * ���û�����
 * 1. ������ݿ�����Ϳ��п�����
 * 2. ������֯���п�����
 */
int FifoBuffer::reset()
{
	EnterCriticalSection(&m_DataAccessLock) ;

	cleanFreeList();
	cleanDataList();		
	bool bRet = createFreeList();
	if (!bRet) 
	{
		LeaveCriticalSection(&m_DataAccessLock);
		return 6; //DH_PLAY_ALLOC_MEMORY_ERROR
	}

	m_dataFrame.context = 0;
	LeaveCriticalSection(&m_DataAccessLock) ;
		
    return 0;
}

/*!
 * ��ʼ��FIFO������
 * 1. ��黺�����Ƿ��ʼ����,���û�г�ʼ���������
 * 2. ������, �����������ȷ����ʾ����
 * 3. ����������б�
 * 4. �����������������ڰ������еķ���
 * 5. ���ó�ʼ���ɹ���־
 */
int FifoBuffer::init(int count,int chunksize)
{
	// ���ڿ�������
	m_freeQueueFirst	= 0; // ͷ
	m_freeQueueLast		= 0; // β
	m_freeCount			= 0; // ����
	// ������������
	m_outQueueFirst		= 0; // ͷ
	m_outQueueLast	  	= 0; // β
	m_outCount			= 0; // ����
	
	m_dataFrame.context = 0;

	m_count = count ;
	m_chunksize = chunksize;
	m_mempool = (unsigned char*)malloc(m_chunksize*m_count);
	if (m_mempool == 0)
	{
		return 6; //DH_PLAY_ALLOC_MEMORY_ERROR
	}

	memset(m_mempool, 0, m_chunksize*m_count);

	bool bRet = createFreeList();
	if (!bRet) return 6; //DH_PLAY_ALLOC_MEMORY_ERROR

	m_inited = true;

 	m_dataFrame.context = 0;
	m_bReadNull = false;

	return 0;
}

/*!
 * ���������
 * 1. ������ݿ�����Ϳ��п�����
 * 2. �������������
 * 3. ��λ��ʼ���ɹ���־
 */
int FifoBuffer::clear()
{
	if (!m_inited) 
	{
		return 0;
	}

	EnterCriticalSection(&m_DataAccessLock) ;
	cleanDataList();
	cleanFreeList();	
	free(m_mempool);
	m_mempool = NULL;
	m_outCount = m_freeCount = 0 ;
	m_inited = false;
	LeaveCriticalSection(&m_DataAccessLock) ;
	return 0;
}

int FifoBuffer::chunkCount()
{
    return m_outCount;
}

void FifoBuffer::setlock(bool iflock)
{
	m_ifLock = iflock ;
}

bool FifoBuffer::getlock()
{
	return m_ifLock;
}

BYTE* FifoBuffer::GetNextWritePos()
{
	DhAVFrame *item = m_freeQueueLast;

	if(m_freeCount <= 1)
	{	
		return NULL;
	}

	return item->context;
}

bool FifoBuffer::write(DhAVFrame* vframe) 
{
	if (m_chunksize > AUDIOBUFLEN)
	{
		if (m_outCount>= m_count * 2 / 3)
		{
			Sleep(45) ;
		}	
	
		while (m_freeCount <= 1 )
		{
			if (m_ifLock == FALSE)
			{
				return false ;
			}
			
			Sleep(45) ;
		}
	}
	
	EnterCriticalSection(&m_DataAccessLock);

	DhAVFrame * item = getFreeNode() ;
	if (item == NULL)
	{
		LeaveCriticalSection(&m_DataAccessLock) ;
		return false ;
	}
	item->width		= vframe->width ;
	item->height	= vframe->height ;
	item->size		= vframe->size;
	item->frameLen	= vframe->frameLen;
	item->frameType	= vframe->frameType;
	item->ivsobjnum	= vframe->ivsobjnum;

	item->tIvsPrePos.lInfoSize = 0;

	if ((vframe->tIvsPrePos.lInfoSize > 0)
		&& (vframe->tIvsPrePos.pIVSPreposInfo != NULL))
	{
		SAFE_DELETEBUFF(item->tIvsPrePos.pIVSPreposInfo);
		item->tIvsPrePos.pIVSPreposInfo = new BYTE[vframe->tIvsPrePos.lInfoSize];
		if (item->tIvsPrePos.pIVSPreposInfo != NULL)
		{
			memcpy(item->tIvsPrePos.pIVSPreposInfo, 
				vframe->tIvsPrePos.pIVSPreposInfo, vframe->tIvsPrePos.lInfoSize);
			item->tIvsPrePos.lInfoSize = vframe->tIvsPrePos.lInfoSize;
		}
		else
		{
			item->tIvsPrePos.lInfoSize = 0;
		}		
	}

	if (item->ivsobjnum > 0)
	{
		memcpy(item->ivsObjList, vframe->ivsObjList, sizeof(DH_IVS_OBJ)*vframe->ivsobjnum);
	}

	if (m_chunksize > AUDIOBUFLEN)
	{
		item->context = vframe->context;
	}
	else
	{
		memcpy(item->context, vframe->context,item->size) ;
	}

	appendToDataList(item) ;

	LeaveCriticalSection(&m_DataAccessLock) ;

	return true ;
}

bool FifoBuffer::read(DhAVFrame* vframe)
{
	EnterCriticalSection(&m_DataAccessLock) ;

	DhAVFrame* item = getDataNode() ;
	if (item == NULL)
	{
		m_bReadNull = true;
		LeaveCriticalSection(&m_DataAccessLock) ;
		return false ;
	}
	m_bReadNull = false;
	vframe->width	= item->width ;
	vframe->height	= item->height ;
	vframe->size	= item->size;
// 	vframe->context = item->context;

	vframe->frameLen  = item->frameLen;
	vframe->frameType = item->frameType; 
	vframe->ivsobjnum = item->ivsobjnum;

	vframe->tIvsPrePos.lInfoSize = 0;

	if ((item->tIvsPrePos.lInfoSize > 0)
		&& (item->tIvsPrePos.pIVSPreposInfo != NULL))
	{
		SAFE_DELETEBUFF(vframe->tIvsPrePos.pIVSPreposInfo);
		vframe->tIvsPrePos.pIVSPreposInfo = new BYTE[item->tIvsPrePos.lInfoSize];
		if (vframe->tIvsPrePos.pIVSPreposInfo != NULL)
		{
			memcpy(vframe->tIvsPrePos.pIVSPreposInfo, 
			item->tIvsPrePos.pIVSPreposInfo, item->tIvsPrePos.lInfoSize);
			vframe->tIvsPrePos.lInfoSize = item->tIvsPrePos.lInfoSize;
		}
		else
		{
			vframe->tIvsPrePos.lInfoSize = 0;
		}		
	}

	if (item->ivsobjnum > 0)
	{
		memcpy(vframe->ivsObjList, item->ivsObjList, sizeof(DH_IVS_OBJ)*vframe->ivsobjnum);
	}

	if (m_chunksize > AUDIOBUFLEN)
	{
		vframe->context = item->context;
		m_dataFrame.context = item->context;
	}
	else
	{
		memcpy(vframe->context, item->context, vframe->size);
	}

	appendToFreeList(item) ;
	
	LeaveCriticalSection(&m_DataAccessLock);

	return true ;
}

BYTE  *FifoBuffer::GetLastFrame()
{
	return m_dataFrame.context ;
}

DhAVFrame *FifoBuffer::getFreeNode()
{
	DhAVFrame *item = m_freeQueueLast;

	if (m_freeCount == 0)
	{
		return NULL ;
	}

	if (m_freeCount == 1)
	{
		m_freeQueueFirst = 0;
		m_freeQueueLast = 0;
	}
	else
	{
		m_freeQueueLast = item->prev;
		m_freeQueueLast->next = 0;
		item->next = 0;
		item->prev = 0;
	}
	
	m_freeCount--;

	return item;
}

/*!
 * �õ�һ����Ч���ݿ�	
 */
DhAVFrame *FifoBuffer::getDataNode()
{
	if (m_outCount == 0)
	{
		return NULL ;
	}

	DhAVFrame *item = m_outQueueLast;

	if (m_outCount == 1)
	{
		m_outQueueFirst = 0;
		m_outQueueLast = 0;
	}
	else
	{
		m_outQueueLast = item->prev;
		m_outQueueLast->next = 0;
		item->prev = 0;
		item->next = 0;
	}

	m_outCount--;
	
	return item;	
}

/*!
 * �����ݿ����ӵ����ж���β��	
 */
void FifoBuffer::appendToFreeList(DhAVFrame *item)
{
	if (m_freeCount > 0) 
	{
		item->next = m_freeQueueFirst;
		m_freeQueueFirst->prev = item;
		m_freeQueueFirst = item;
	} 
	else 
	{
		m_freeQueueFirst = item;
		m_freeQueueLast = item;
	}
	
	m_freeCount++;
}

/*!
 * �����ݿ����ӵ����ݶ���β��
 */
void FifoBuffer::appendToDataList(DhAVFrame *item)
{
	if (m_outCount > 0) 
	{
		item->next = m_outQueueFirst;
		m_outQueueFirst->prev = item;
		m_outQueueFirst = item;
	} 
	else 
	{      
		m_outQueueFirst = item;
		m_outQueueLast = item;
	}
    
	m_outCount++;	
}

void FifoBuffer::cleanDataList()
{
	DhAVFrame *item = 0;
	DhAVFrame *temp = 0;

	item = m_outQueueFirst;

	while (0 != item ) 
	{
		temp = item->next;
		item->context = 0;
		item->prev = 0;
		item->next = 0;

		SAFE_DELETEBUFF(item->ivsObjList);
		SAFE_DELETEBUFF(item->tIvsPrePos.pIVSPreposInfo);
		item->tIvsPrePos.lInfoSize = 0;

		delete item;
		item = temp;
	}
	
	m_outQueueFirst = 0;
	m_outQueueLast = 0;
	m_outCount = 0;	
}

void FifoBuffer::cleanFreeList()
{
	DhAVFrame *item = 0;
	DhAVFrame *temp = 0;

	item = m_freeQueueFirst;

	while (0 != item) 
	{
		temp = item->next;
		item->context = 0;
		item->prev = 0;
		item->next = 0;

		SAFE_DELETEBUFF(item->ivsObjList);
		SAFE_DELETEBUFF(item->tIvsPrePos.pIVSPreposInfo);
		item->tIvsPrePos.lInfoSize = 0;

		delete item;
		item = temp;
	}

	m_freeQueueFirst = 0;
	m_freeQueueLast = 0;
	m_freeCount = 0;
}

bool FifoBuffer::createFreeList()
{
	DhAVFrame *item = 0;

	EnterCriticalSection(&m_DataAccessLock);
	for (int i = 0; i < m_count; ++i) 
	{
		// ����һ��Item, �嵽˫�����β��
		item = new DhAVFrame;
		if (item == NULL)
		{
			LeaveCriticalSection(&m_DataAccessLock);
			return false;
		}

		memset(item, 0, sizeof(DhAVFrame));
		item->context = m_mempool+m_chunksize*i;//(unsigned char *)malloc(m_blockSize);
		item->prev = 0;
		item->next = 0;

		item->ivsobjnum  = 0;
		item->ivsObjList = new DH_IVS_OBJ[MAX_IVSOBJ_NUM];
		if (item->ivsObjList == NULL)
		{
			LeaveCriticalSection(&m_DataAccessLock);
			return false;
		}
		
		appendToFreeList(item);
	}
	LeaveCriticalSection(&m_DataAccessLock);

	return true;
}

