#ifndef _LUMA_STRETCH_H_
#define _LUMA_STRETCH_H_

#ifdef __cplusplus
extern "C" {
#endif

/********************************************************************
	function name:	LumaStretch
    purpose:		����ͼ���ͨ͸��
    input param:	unsigned char* pSrc:ԴYUVͼ���ַ					
					unsigned char* pDst��Ŀ��YUVͼ���ַ,���pDstΪNULL��������ֱ��д��pSrc��					
					int nWidth��ͼ���
					int nHeight��ͼ���
    output param:	NULL
    return:			-1��failed	0:success
    created:		13:3:2008   16:05
	author:			winton	
	
*********************************************************************/
int LumaStretch(unsigned char* pSrc,unsigned char* pDst,int nWidth,int nHeight);

#ifdef __cplusplus
}
#endif
#endif