/*********************************************************
                      DllDeinterlace.h
*********************************************************/
#ifndef _DLLDEINTERLACE_H_
#define _DLLDEINTERLACE_H_

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */
    
#if defined(WIN32)
#if !defined(USELIB)
#define HI_API __declspec( dllexport ) 
#define HI_APICALL __stdcall
#else
#define HI_API
#define HI_APICALL
#endif
#elif defined(LINUX)
#define HI_API
#define HI_APICALL
#else
#error "Please specify a design-in platform!"
#endif


//������
#define HI_SUCCESS_DEINTERLACE  0   //�ɹ�
#define HI_ERR_MALLOC           -1  //mallocʱʧ��
#define HI_ERR_PITCH            -2  //���롢���ͼ��Ŀ�����ò���
#define HI_ERR_POINT_NULL       -3  //����ָ��Ϊ��
#define HI_ERR_FIELD_FLAG       -4  //����Ĳ��ǳ���־

typedef enum hiPIC_TYPE_E
{
    PIC_PROGRESSIVE = 0,    // ֡
    PIC_INTERLACED_ODD,     // �泡
    PIC_INTERLACED_EVEN     // ż��
} PIC_TYPE_E;

typedef struct hiDEINTERLACE_PARA_S
{
    int iFieldWidth;    //����
    int iFieldHeight;   //����
    int iSrcYPitch;     //���볡ͼ��Y�����Ŀ��
    int iSrcUVPitch;    //���볡ͼ��UV�����Ŀ��
    int iDstYPitch;     //���֡ͼ��Y�����Ŀ��
    int iDstUVPitch;    //���֡ͼ��UV�����Ŀ��
}DEINTERLACE_PARA_S;

typedef struct hiDEINTERLACE_FRAME_S
{
    unsigned char *pszY;  //YUV420ͼ��Y����
    unsigned char *pszU;  //YUV420ͼ��U����
    unsigned char *pszV;  //YUV420ͼ��V����
}DEINTERLACE_FRAME_S;

/***************************************************************************
           ��ʼ��deinterlace����
  ���ܣ�����HI_Deinterlace����ǰ����ô˺���
        �����deinterlace�ĳ�ʼ������
  ������
      **pHandle    : ���������Deinterlace���,����Ҫ���κβ���,ֻ��
                               �������������������.
      struPara     : �����������������YUV420��ͼ��߿��Ȳ�����
                               �������YUV420֡ͼ��Ŀ�Ȳ���.
  ����ֵ:
      HI_SUCCESS_DEINTERLACE:  �ɹ�
      HI_ERR_MALLOC         :  ���ٿռ�ʧ��
      HI_ERR_PITCH          :  ���������ͼ�������ò��ԣ������ȱȿ�Ȼ�С
/***************************************************************************/
HI_API int HI_InitDeinterlace(void **pHandle, DEINTERLACE_PARA_S struPara);

/***************************************************************************
         �ͷ�deinterlace����
  ���ܣ��ͷ�Deinterlace��Դ
  ������
      *pHandle    : ���������Deinterlace���,����Ҫ���κβ���,ֻ��
                    ����ʵ�������������.
  ����ֵ:
         HI_SUCCESS_DEINTERLACE:  �ɹ�
         HI_ERR_POINT_NULL     �� ����pHandleָ��Ϊ��
***************************************************************************/
HI_API int HI_ReleaseDeinterlace(void *pHandle);

/**************************************************************************
             deinterlace���ýӿ�
 ���ܣ� �˺������ÿ�������һ֡ͼ��Ĺ���
 ������
     *pHandle    : ���������deinterlace���
     struDstFrame��������������֡YUV420ͼ��
     *pszSrcY    ��������������볡YUV420ͼ��Y����
     *pszSrcU    ��������������볡YUV420ͼ��U����
     *pszSrcV    ��������������볡YUV420ͼ��V����
     tFieldFlag  ��������������붥�׳���־ֵ
 ����ֵ��
     HI_SUCCESS_DEINTERLACE�� �ɹ�
     HI_ERR_POINT_NULL     �� ����pszDstFrame��pszSrcYָ��Ϊ��
     HI_ERR_FIELD_FLAG     �� �����tFieldFlag���Ƕ��׳���־ֵ
**************************************************************************/
HI_API int HI_Deinterlace(void *pHandle,
                          DEINTERLACE_FRAME_S struDstFrame,
                          unsigned char *pszSrcY,
                          unsigned char *pszSrcU,
                          unsigned char *pszSrcV,
                          PIC_TYPE_E tFieldFlag);

/***************************************************************************
         ��ȡdeinterlace�汾�ź���
  ���ܣ���ȡdeinterlace�汾��
  ������
         *pszVersion : �������������汾���ַ���.
  ����ֵ:
         HI_SUCCESS_DEINTERLACE:  �ɹ�
         HI_ERR_POINT_NULL     �� ����pszVersionָ��Ϊ��
***************************************************************************/
HI_API int HI_GetVersion(char **pszVersion);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif   //_DLLDEINTERLACE_H_
