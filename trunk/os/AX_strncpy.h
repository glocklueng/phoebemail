#ifndef DSS_AX_STRNCPY_H_INCLUDED
#define DSS_AX_STRNCPY_H_INCLUDED

#include "platform.h"
#include <string.h>

namespace AX_OS
{
	//��ȫ���ַ���copy����
	//���ݴ����siz��С����src copy���siz-1���ַ���dst,����copy��ɵ��ַ��������'\0'
	//���ڴ����dst=NULL����src=NULL�����˼��
	//����ֵsizΪdst��buffer�Ĵ�С
	//���ؽ����ʵ��copy��dst�е��ַ�����Ŀ��������'\0'�ַ�
	size_t strncpy(char* dst, const char* src, size_t siz);
}

#endif//