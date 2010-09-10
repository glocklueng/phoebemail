#ifndef DDOVERLAYRENDER_H
#define DDOVERLAYRENDER_H

#include "manager.h"
#include "videorender.h"
#include "colorspace.h"

#include <windows.h>
#include <ddraw.h>
#include <stdio.h>

class DDOverlayRender : public VideoRender
{
public:
	// ���캯��
    DDOverlayRender(DWORD color);

	// ��������
	virtual ~DDOverlayRender();

	// �ӿں���
	virtual int init(int index, HWND hWnd, int width, int height, draw_callback cb);
	
    virtual int render(unsigned char *py, unsigned char *pu, unsigned char *pv, 
		int width, int height,RECT*rc);

	virtual void resize();

	virtual int clean();

	virtual void VerticalSyncEnable(BOOL bEnable) {};

private:
	// ��ʼ��DirectDraw
    int initDirectDraw();

	// ������ͼ����
    HRESULT createDrawSurface();

	// �ڲ�����
    HRESULT destroyDDObjects();

	// ����Ƿ�֧��Overlay
    BOOL hasOverLaySupport();

	// ����Ƿ�֧��FourCC (���ַ�����)
    BOOL hasFourCCSupport(LPDIRECTDRAWSURFACE7 lpdds);
    
	// ��ɫ��������
    DWORD colorMatch(IDirectDrawSurface7 * pdds, COLORREF rgb);
    DWORD convertGDIColor(COLORREF dwGDIColor);
	
	void adjustRect(RECT &rcSrc, RECT &rcDest);
	void GetRenderRect(HWND hWnd, RECT &rcRect);
private:
	// �����Ĳ���
	int	m_index;

	DWORD	m_colorKey;

	// ���ھ��
    HWND	m_hWnd;
	
	int	m_width;	// Ҫ�����Ļ�ͼ����Ŀ��
	int	m_height;	// Ҫ�����Ļ�ͼ����ĸ߶�
	
	draw_callback m_callback;

private: // DirectDraw ���
    LPDIRECTDRAW7        m_pDD;						// DirectDraw����
    LPDIRECTDRAWSURFACE7 m_pDDSPrimary;				// ������
    LPDIRECTDRAWSURFACE7 m_pDDSVideoSurface;		// ��ͼ����
    LPDIRECTDRAWSURFACE7 m_pDDSVideoSurfaceBack;	// ��̨��ͼ����

	// Overlay��ʽ��Ҫʹ�õĲ���
    DDOVERLAYFX m_OverlayFX;
    DWORD m_dwOverlayFlags;
	DDBLTFX	m_ddbltfx;
 
	// ��ͼ������Ϣ
    DDCAPS  m_ddCaps;
    
	// Overlay֧�ֱ�ʶ
    BOOL m_hasOverlaySupport;

	// FourCC֧�ֱ�ʶ
    BOOL m_hasFourCCSupport;

	color_convert_func m_colorConvert;

	//Ŀ�ı������������ϵ�λ��
	RECT m_destRect;
	RECT rcSrc;

	//��Ļ��͸�
	int	m_screenWidth;
	int	m_screenHeight;

	//�Ƿ�֧��Overlay
	bool m_updataOverlay;

	int m_MonitorBeginPosX;
	int m_MonitorBeginPosY;
};

#endif /* DDOVERLAYRENDER_H */
