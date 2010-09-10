#ifndef VIDEORENDER_H
#define VIDEORENDER_H

#include "manager.h"

struct VideoRender
{
	/*!
	 * hWnd: �����Ĵ��ھ��
	 * width, height: һ��Ϊ��Ƶͼ��Ŀ����
	 * cb: ��ͼ�ص�, ��Ҫ��ͳһ�������.
	 */
	virtual int init(int index, HWND hWnd, int width, int height, draw_callback cb) = 0;
	virtual int clean() = 0;
   	virtual int render(unsigned char *py, unsigned char *pu, unsigned char *pv, int width, int height,RECT*rc) = 0;
	virtual void resize() = 0;
	virtual void VerticalSyncEnable(BOOL bEnable) = 0;
	virtual ~VideoRender(){} ;
};

#include <stdio.h>
#include <stdarg.h>
#include <windows.h>

inline void dbg_print(const char *msg, ...)
{
#ifdef _DEBUG
	char buf[256];
	
	va_list ap;
	va_start(ap, msg); // use variable arg list
	vsprintf(buf, msg, ap);
	va_end( ap );
	
	OutputDebugString(buf);
#endif
}

#endif // VIDEORENDER_H
