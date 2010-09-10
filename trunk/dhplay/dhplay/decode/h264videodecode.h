#ifndef H264VIDEODECODE_H
#define H264VIDEODECODE_H

#include <windows.h>
#include "interface.h"

extern "C" {
void h264_decode_init_all();

void * h264_decode_init();

// flag = 0 ��H264 ,flag = 1 ADI H264
int h264_decode_frame(void *handle,
		unsigned char *frame, int len, 
		unsigned char *out,
		int *width, int *height, 
		int *qp,int level);
	
int h264_decode_end(void *handle);
}

typedef void (/*_stdcall*/* H264_Init_All)();
typedef void* (/*_stdcall*/* H264_Init)();
typedef int (/*_stdcall*/* H264_Decode_OneFrame)(void *handle,
		unsigned char *frame, int len, 
		unsigned char *out,
		int *width, int *height, 
		int *qp,int level);

typedef int (/*_stdcall*/* H264_End)(void *handle);

class H264VideoDecoder:public IDecode
{
public:
    H264VideoDecoder();
    ~H264VideoDecoder();
    
	/************************************************************************/
	/* ��Ƶ����ӿ�(��ʼ������������ã�ͼ���С�����ı䣬���룬etc			*/
	/************************************************************************/
    int init();		// ��ʼ��
    int clean();	// ���
	int reset();	// ����
    int resize(int w, int h); // �ı�ͼ���С�����Բ���
    int decode(unsigned char *src_buf,unsigned int buflen,unsigned char* dest_buf, int param1, int param2); // ����	
	
	int getWidth(){return m_width;}
	int getHeight(){return m_height;}

	DWORD m_threadId;

private:
	void *m_decHandle;	
	int m_qp;
	int m_width;
	int m_height;
	unsigned char* m_preBuffer;

public:
	static H264_Init_All m_Fun_h264_init_all;
	static H264_Init m_Fun_h264_int;
	static H264_Decode_OneFrame m_Fun_h264_decode_oneFrame;
	static H264_End m_Fun_h264_end;

};

#endif /* H264VIDEODECODE_H */