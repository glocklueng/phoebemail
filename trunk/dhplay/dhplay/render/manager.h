#ifndef DHRENDERMANAGER_H
#define DHRENDERMANAGER_H

#include <windows.h>
#include <multimon.h>
#include "../utils.h"

enum VideoRenderMethod
{
	ByDDOffscreen = 0,	// Ĭ��, DirectDraw Offscreen��ʽ,֧��OSD
	ByDDOverlay = 1,	// Overlay��ʽ,��֧��OSD
	ByGDI = 2			// ���Ǳ�ѡ,֧��OSD
};

typedef struct _HWND_MONITOR 
{
	GUID guid;
	HMONITOR hMonitor;
}HWNDHMONITOR;

enum AudioRenderMethod
{
	DIRECTSOUND_WITH_LOOPBUFFER = 0,
	PCM_OUT = 1
};

typedef void (__stdcall *draw_callback)(int index, HDC hDc);

class CAudioRender;
struct VideoRender;
struct AudioRender;

class DhRenderManager
{
public:
	DhRenderManager();
	virtual ~DhRenderManager();

	VideoRenderMethod m_eVideoRenderMode;

	BOOL VideoVerticalSyncEnable(BOOL bEnable);

//	int open(int index, HWND hWnd, int width, int height, draw_callback cb, VideoRenderMethod vrm, DWORD ck,bool IfSoundOpen = true);
	int openVideo(int index, HWND hWnd, int width, int height, draw_callback cb, VideoRenderMethod vrm, DWORD ck);

	int openSound(int channels, int samplePerSec, int bitsPerSample) ;
	
	int closeSound() ;

	int close();

	// ����ӿ�
	int renderVideo(
		unsigned char *py, 
		unsigned char *pu, 
		unsigned char *pv, 
		int width, int height, int rotateType = 0 , RECT* rect = NULL );
	
	static bool setvolume(DWORD lVolume);

	void setaudiorenderstyle( int style);
	
	int renderAudio(unsigned char *pcm, int len, 
		int bitsPerSample, int samplesPerSecond);
	
	static DWORD getvolume();

	int ResetVideoRender(int index, HWND hWnd, int width, int height, draw_callback cb, VideoRenderMethod vrm, DWORD ck);

private:
	HWND m_hWnd; // ���ھ��
	VideoRender	*m_videoRender;
	CAudioRender *m_audioRender;

	CritSec m_renderCritsec;
};

#endif /* DHRENDERMANAGER_H */