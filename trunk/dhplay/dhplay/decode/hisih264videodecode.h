#ifndef HISIH264VIDEODECODE_H
#define HISIH264VIDEODECODE_H

#include "interface.h"
#include "../depend/DllDeinterlace.h"
#include "../depend/hi_config.h"
#include "../depend/hi_h264api.h"

#define FILED_WIDTH    720   //��ͼ���
#define FIELD_HEIGHT   240   //��ͼ���

typedef HI_HDL (/*_stdcall*/* HI264_DecCreate)( H264_DEC_ATTR_S *pDecAttr );

typedef void (/*_stdcall*/* HI264_DecDestroy)( HI_HDL hDec );

typedef HI_S32 (/*_stdcall*/* HI264_DecFrame)(
    HI_HDL  hDec,
    HI_U8*  pStream,
    HI_U32  iStreamLen,
    HI_U64  ullPTS,
    H264_DEC_FRAME_S *pDecFrame,
    HI_U32  uFlags );

typedef HI_S32 (*HI264_DecAU)(
	HI_HDL hDec,
	HI_U8 *pStream,
	HI_U32 iStreamLen,
	HI_U64 ullPTS,
	H264_DEC_FRAME_S *pDecFrame,
	HI_U32 uFlags );

class HisiH264VideoDecoder:public IDecode
{
public:
    HisiH264VideoDecoder();
    ~HisiH264VideoDecoder();
    
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

private:
	void *m_decHandle;	
	void *m_hDeinterlace;
	H264_DEC_ATTR_S		m_attr;
	int m_width;
	int m_height;
	DEINTERLACE_FRAME_S m_struDstFrame;                     //Deinterlace�����YUV420���
    DEINTERLACE_PARA_S  m_struPara;                         //��ʼ��Deinterlace�������
	
	static HI264_DecCreate m_Fun_HIDecCreate;
    static HI264_DecDestroy m_Fun_HIDecDestroy;
	static HI264_DecAU m_Fun_HIDecAU;
};

#endif /* HISIH264VIDEODECODE_H */