#ifndef _INTERFACE_H
#define _INTERFACE_H

struct IDecode//����ӿ�
{
	virtual  int decode(unsigned char *src_buf,unsigned int buflen,unsigned char* dest_buf, int param1, int param2)=0; // ����	
	virtual  int reset() = 0 ;
	virtual int resize(int w, int h) = 0; 
};

#endif