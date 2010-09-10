#ifndef DH_DSS_COMPONENT_AX_API_AX_STR_H_INCLUDED
#define DH_DSS_COMPONENT_AX_API_AX_STR_H_INCLUDED

#include "platform.h"

namespace AX_OS
{


	typedef int (*Fun_snprintf)(char *buffer,size_t count,const char *format ,... );
	extern Fun_snprintf snprintf;
	
	typedef int (*Fun_stricmp)(const char* str1, const char* str2);
	extern Fun_stricmp stricmp;
	
	//dest:Ŀ��buffer,���Ŀ��bufferû��'\0'�������������һ���ַ�Ϊ'\0',����0
	//src:
	//srcBufLen:Ŀ��buffer���ܳ���,copy����Ŀ���ᳬ�����srcBufLen-1
	//ִ����ɺ������copy����ô��Destһ��������0����
	//���صĽ���Ǵ�src copy��dest�е��ַ���Ŀ
	size_t strncat(char* dest, const char* src, const size_t srcBufLen);

	//��ȫ���ַ���copy����
	//���ݴ����siz��С����src copy���siz-1���ַ���dst,����copy��ɵ��ַ��������'\0'
	//���ڴ����dst=NULL����src=NULL�����˼��
	//����ֵsizΪdst��buffer�Ĵ�С
	//���ؽ����ʵ��copy��dst�е��ַ�����Ŀ��������'\0'�ַ�
	size_t strncpy(char* dst, const char* src, size_t siz);

	//��ȫ���ַ���copy����
	//dst,Ŀ��buffer
	//dstBufLen,Ŀ��buffer�ռ��С,�ú������д��dstBufLen-1���ַ���������д���ַ��������'\0'�ַ�
	//src,Դbuffer
	//Ҫcopy���ַ�����,��dstBufLen-1�ռ����������£����copy���ַ���ĿΪsrcCopyCount,�����ں������'\0'�ַ�
	size_t strncpy(char* dst, size_t dstBufLen, const char* src, size_t srcCopyCount);

}

#endif//DH_DSS_COMPONENT_AX_API_AX_STR_H_INCLUDED
