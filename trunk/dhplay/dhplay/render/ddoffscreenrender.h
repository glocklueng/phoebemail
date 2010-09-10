#ifndef DDRENDER_H
#define DDRENDER_H

#include "manager.h"
#include "videorender.h"
#include "colorspace.h"

#include <windows.h>
#include <ddraw.h>
#include <stdio.h>

// #define USE_OSD_SURFACE
#define LPMYDIRECTDRAWSURFACE	LPDIRECTDRAWSURFACE7

class DDOffscreenRender : public VideoRender
{
public:
	// ���캯��
	DDOffscreenRender();
	// ��������
	virtual ~DDOffscreenRender();
	// �ӿں���
	virtual int init(int index, HWND hWnd, int width, int height, 
		draw_callback cb);	

	virtual int render(unsigned char *py, unsigned char *pu, unsigned char *pv, 
		int width, int height,RECT*rc);	

	virtual void resize();

	virtual int clean();

	virtual void VerticalSyncEnable(BOOL bEnable) {m_bVerticalSyncEnable = bEnable;};

private:
	// ��ʼ��DirectDraw
	int initDirectDraw();

	// ������ͼ����
	HRESULT createDrawSurface();

	// �ڲ�����
	HRESULT destroyDDObjects();

	// ����Ƿ�֧��FourCC (���ַ�����)
	BOOL hasFourCCSupport(LPDIRECTDRAWSURFACE7 lpdds);

	void adjustRect(RECT &rcSrc, RECT &rcDest);

	void GetRenderRect(HWND hWnd, RECT &rcRect);

private:
	// �����Ĳ���
	int	m_index;
	int	m_width;	// Ҫ�����Ļ�ͼ����Ŀ��
	int	m_height;	// Ҫ�����Ļ�ͼ����ĸ߶�
	// ���ھ��
	HWND	m_hWnd;
	draw_callback m_callback;

	BOOL m_bVerticalSyncEnable;
	CritSec m_csRgbSurfaceCritsec;//��RGBҳ��Ҫ���б���

private: // DirectDraw ���
	// DirectDraw����
	LPDIRECTDRAW7        m_pDD;						// DirectDraw����
	LPDIRECTDRAWSURFACE7 m_pDDSPrimary;				// ������
	LPDIRECTDRAWSURFACE7 m_pDDSVideoSurface;		// ��ͼ����

	LPMYDIRECTDRAWSURFACE m_pDDRGBSurface;           //����OSD����

	// ��ͼ������Ϣ
	DDCAPS  m_ddCaps;

	// FourCC֧�ֱ�ʶ
	BOOL m_hasFourCCSupport;

	color_convert_func m_colorConvert;

	RECT m_destRect;
	//��Ļ��͸�
	int	m_screenWidth;
	int	m_screenHeight;

	int m_MonitorBeginPosX;
	int m_MonitorBeginPosY;

private:
	bool GetMonitorBeginPos(int* width, int*height);
};

#endif /* DDRENDER_H */
