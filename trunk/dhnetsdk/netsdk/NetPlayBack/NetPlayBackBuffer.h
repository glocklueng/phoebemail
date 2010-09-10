
#if !defined NETPLAYBACKBUFFER_H_
#define NETPLAYBACKBUFFER_H_

#include "../StdAfx.h"

typedef bool (__stdcall *NetPlayBackBufferPause)
        (bool bPause, void *userdata);

/*�������ö���������ǲ�ͬ��ԭ������ͣ��־����ռ��λ*/
enum PauseResumeID
{
	BUFFER_SHORT = 0,	//��Ϊ��������������ͣ
	BUFFER_RESET,		//��Ϊ������Ҫ��ն���ͣ
	BUFFER_OTHER,		//����
};

class CNetPlayBackBuffer
{
public:
    CNetPlayBackBuffer();
    ~CNetPlayBackBuffer();
public:
    bool  init(int nTotalSize, int nMaxWriteSize, int nMinWriteSize,
        NetPlayBackBufferPause pPauseFunc, void *userdata);
	bool  IsInited();

    bool  AddData(unsigned char *data, int datalen);
    int   GetData(unsigned char *data, int datalen);
    void  DecDataLength(int datalen);
    void  Reset();
	void  IsRePause();

	void  Pause(enum PauseResumeID id);
	void  Resume(enum PauseResumeID id);

    int   GetSize() { return m_nWritePos - m_nReadPos;}

protected:
    DEVMutex			 m_csBuf;

    int             m_nTotalSize;
    int             m_nMaxWriteSize;
    int             m_nMinWriteSize;

    unsigned char  *m_pData;
    int             m_nReadPos;
    int             m_nWritePos;

    int             m_bWriteFlag;
	int				m_iPauseFlag;

    NetPlayBackBufferPause m_pPauseFunc;
    void           *m_userdata;

protected:
    int             OutputState();

private:
	BOOL			IsPaused(enum PauseResumeID id);
};

#endif

