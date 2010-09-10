/*
**  ************************************************************************
**                                    DHPlay  ͨ�ò���SDK
**
**         (c) Copyright 1992-2004, ZheJiang Dahua Technology Stock Co.Ltd.
**                            All Rights Reserved
**
**	File  Name	: display.cpp
**	Description	: ����sdk��ʾ���Ƴ���
**	Modification	: 2005/11/28		chenmy		Create the file
**  ************************************************************************
*/
#include "StdAfx.h"
#include "display.h"
#include "stdio.h"
#include "playmanage.h"

typedef void (__stdcall *pDrawCBFunc)(int index, HDC hDc);


/*	$Function		:	CDisplay
==  ===============================================================
==	Description		:	���캯��
==	Argument		:	���������
							nPort �˿ں�
==				:			hWnd ���ھ��
== 	Return		:	
==	Modification	:	2005/11/28		chenmy   Create
==  ===============================================================
*/
CDisplay::CDisplay(int nPort)
{
	m_nIndex = nPort;   //�˿ں�
	m_DisType = ByDDOffscreen ;
	m_colorkey = 0 ;
	m_nWidth = 352 ;         //ÿ֡ͼƬ�Ŀ��
	m_nHeight = 288 ;        //ÿ֡ͼƬ�ĸ߶�
	m_CurFrameNum = -1 ;         //��ǰ��ʾ�������
	m_PlayedFrames = 0 ;       //��������
	m_nDisplayType = DISPLAY_NORMAL;
	m_decType = DEC_COMPLEX;	
	m_nCoefficient = 0 ;
	m_volume       = m_renderManager.getvolume();//0x7fff7fff ;
	m_nRotateType = 0;

	for (int i = 0; i < MULTI_DISPLAY_RECT_NUM; i++)
	{
		m_MultiDisInfo[i].bEnable = FALSE;
		m_MultiDisInfo[i].nRegionNum = -1;
		memset(&(m_MultiDisInfo[i].pSrcRect),0,sizeof(RECT));
	}

	memset(&m_mainRect, 0, sizeof(RECT));

	m_IfRenderOpen = false ;
	m_i = 0 ;
	m_pQuarterBuf = NULL;

	m_hWnd = NULL;
}

/*	$Function		:	~CDisplay
==  ===============================================================
==	Description		:	��������
==	Argument		:				
==				:			
== 	Return		:	
==	Modification	:	2005/11/28		chenmy   Create
==  ===============================================================
*/
CDisplay::~CDisplay()
{
	if (m_pQuarterBuf)
	{
		delete m_pQuarterBuf;
		m_pQuarterBuf = NULL;
	}
}

/*	$Function		:	Init
==  ===============================================================
==	Description		:	��ʼ������
==	Argument		:							
==				:			
== 	Return		:	
==	Modification	:	2005/11/28		chenmy   Create
==  ===============================================================
*/

//draw_callback draw_cb ;
void __stdcall draw_cb(int index, HDC hDc)
{
	if (g_cDHPlayManage.pCallback[index]&&g_cDHPlayManage.pCallback[index]->GetCBStatus(CBT_DrawCBFun))
		g_cDHPlayManage.pCallback[index]->ProcessDraw(hDc) ;
}

void __stdcall drawEx_cb(int index, HDC hDc)
{
	int port = index / FUNC_MAX_PORT;
	int reginNum = index % FUNC_MAX_PORT;
	
	if (g_cDHPlayManage.pCallback[port]&&g_cDHPlayManage.pCallback[port]->GetCBStatus(CBT_DrawCBFunEx))
		g_cDHPlayManage.pCallback[port]->ProcessDrawEx(reginNum, hDc) ;
}

BOOL CDisplay::OpenSound()
{
	int iRet = 0 ;	
   	iRet = m_renderManager.openSound(1, 8000, 8) ;
	//SetVolume(m_volume&0xffff) ;
	return (iRet == 0) ? TRUE : FALSE ; 
}

BOOL CDisplay::CloseSound()
{
// 	m_renderManager.closeSound() ;
	return TRUE  ; 
}

int CDisplay::Init(HWND mWnd)
{
	m_DDRAWCB = NULL;
	if (g_cDHPlayManage.pCallback[m_nIndex]&&
		g_cDHPlayManage.pCallback[m_nIndex]->GetCBStatus(CBT_DrawCBFun))
	{
		m_DDRAWCB = draw_cb;
	}

	if (g_cDHPlayManage.pCallback[m_nIndex]&&
		g_cDHPlayManage.pCallback[m_nIndex]->GetCBStatus(CBT_DrawCBFunEx))
	{
		m_DDRAWCB = drawEx_cb;
	}
	
	if (ByGDI == m_DisType)
	{
		m_DisType = ByDDOffscreen;
	}

	if (m_renderManager.openVideo(m_nIndex, mWnd, 352, 288,m_DDRAWCB,(VideoRenderMethod)m_DisType,m_colorkey) != 0)    //�򿪻طŴ���
	{
		//����ø���ʾģʽ�򿪲���,��ô��offscreen ����ʾһ��
		m_DisType = ByDDOffscreen;	
		if (m_renderManager.openVideo(m_nIndex, mWnd, 352, 288,m_DDRAWCB,(VideoRenderMethod)m_DisType,m_colorkey) != 0)
		{						
			//�����offscreen����ʾ����,��ôֻ����GDI��ʾ
 			m_DisType = ByGDI;	
			if(m_renderManager.openVideo(m_nIndex, mWnd, 352, 288,m_DDRAWCB,(VideoRenderMethod)m_DisType,m_colorkey) != 0)
			{
				//������ǲ���,��ô����ʧ��
				return 9; //DH_PLAY_CREATE_DDRAW_ERROR
			}
			else;
		}
		else;
	}
	
	m_IfRenderOpen = true ;

	m_hWnd = mWnd;

	return 0 ;
}

int CDisplay::ResetVideoDisplay(void)
{
	int ret = m_renderManager.ResetVideoRender(m_nIndex, m_hWnd, m_nWidth, m_nHeight, m_DDRAWCB,
		(VideoRenderMethod)m_DisType,m_colorkey);

	return ret;
}
/*	$Function		:	SetJumpNum
==  ===============================================================
==	Description		:	�رջط���ʾ�������Źر�ʱҲӦ�ùر���ʾ�������´�render_open�����
==	Argument		:							
==				:				
== 	Return		:	
==	Modification	:	2006/01/26		chenmy   Create
==  ===============================================================
*/
int CDisplay::Close() 
{
	m_renderManager.close() ;

	m_IfRenderOpen = false ;
	m_CurFrameNum = -1 ;         //��ǰ��ʾ�������
	m_PlayedFrames = 0 ;       //��������
	
	for (int i = 0 ;i < MULTI_DISPLAY_RECT_NUM ; i++)
	{
		if (m_MultiDisInfo[i].nRegionNum >= 0)
		{
			m_MultiDisInfo[i].nVideoRender.close() ;
		}
	}

	return 0;
}

/*	$Function		:	ReciveYUV
==  ===============================================================
==	Description		:	��Ƶ���ݴ��������������ص����õ�����Ƶ����
==	Argument		:	���������						
==				:			index ͨ����
==              :           py    ����ص����õ���YUV���ݵ�Y��������ָ��
==              :           pu                             U��������ָ��
==              :           pv                             V��������ָ��
==              :           width �ɸý���ص�������������ͼ��Ŀ��
==              :           height                        ͼ��ĸ߶�	
== 	Return		:	
==	Modification	:	2005/11/28		chenmy   Create
==  ===============================================================
*/
int CDisplay::ReciveYUV(int index, unsigned char *py, unsigned char *pu, unsigned char *pv,
        int width, int height,int AddFrameNum)  //������Ƶ����
{
	if (m_nIndex != index)
	{
		return 1;
	}

	if (py == NULL)
	{
		m_CurFrameNum += AddFrameNum ;
		return 0 ;
	}

	int ret = 0;
	
	m_CurFrameNum += AddFrameNum ;
	m_PlayedFrames++ ;

	if (g_cDHPlayManage.pCallback[index] && g_cDHPlayManage.pCallback[index]->GetCBStatus(CBT_DisplayCBFun))   //�Ƿ�ץͼ�ص�
	{
		g_cDHPlayManage.pCallback[index]->ProcessDisplay(py,m_nWidth,m_nHeight);//��ץͼ�ص�������״̬��Ϊ"PROCESS",���û��ص��߳̽�����ִ�иûص�����
	}
	
	if (g_cDHPlayManage.pCallback[index] && g_cDHPlayManage.pCallback[index]->GetCBStatus(CBT_DecCBFun)
		&& (m_decType == DEC_VIDEO || m_decType == DEC_COMPLEX) )   //�Ƿ������ʾ�ص�
	{
		g_cDHPlayManage.pCallback[index]->ProcessDec(DEC_VIDEO,py,m_nWidth*m_nHeight*3/2,m_nWidth,m_nHeight);
		return 0 ;
	}
	else
	{
		if (m_IfRenderOpen == false)
		{
			return 1;
		}

		for (int i = 0 ; i < MULTI_DISPLAY_RECT_NUM ; i++)
		{
			if (m_MultiDisInfo[i].bEnable)
			{
				ShowRegion(m_MultiDisInfo[i].nRegionNum, py);
			}
 		}

		if (m_nDisplayType == DISPLAY_QUARTER)
		{
			if (m_pQuarterBuf == NULL)
			{
				m_pQuarterBuf = new unsigned char[m_nWidth*m_nHeight*3/2];
			}

			memcpy(m_pQuarterBuf, py, m_nWidth*m_nHeight*3/2);
			BYTE *mYp,*mUp, *mVp;
			mYp = m_pQuarterBuf;
			mUp = m_pQuarterBuf + m_nWidth*m_nHeight;
			mVp = m_pQuarterBuf + m_nWidth*m_nHeight*5/4;
		 	ToQuarter(mYp,mUp,mVp,width,height);

			ret = m_renderManager.renderVideo(mYp, mUp, mVp, m_nWidth/2, m_nHeight/2 ,m_nRotateType) ;//��ʾһ��ͼ��
		}
		else
		{
			int rate = g_cDHPlayManage.pDHPlay[index]->GetFrameRate();
			if (rate > 25)
			{
				if (m_i % (rate/25) == 0)
				{
					if (m_mainRect.right == 0 || m_mainRect.bottom == 0)
					{
						ret = m_renderManager.renderVideo(py, pu, pv, m_nWidth, m_nHeight, m_nRotateType) ;//��ʾһ��ͼ��
					}
					else
					{
						ret = m_renderManager.renderVideo(py, pu, pv, m_nWidth, m_nHeight, m_nRotateType ,&m_mainRect) ;//��ʾһ��ͼ��
					}					
				}			

				m_i++ ;

				if (m_i > 10000)
				{
					m_i = 0 ;//��ֹI����
				}
			}
			else
			{
				if (m_mainRect.right == 0 || m_mainRect.bottom == 0)
				{
					ret = m_renderManager.renderVideo(py, pu, pv, m_nWidth, m_nHeight , m_nRotateType) ;//��ʾһ��ͼ��
				}
				else
				{
					ret = m_renderManager.renderVideo(py, pu, pv, m_nWidth, m_nHeight, m_nRotateType , &m_mainRect) ;//��ʾһ��ͼ��
				}
			}
		}
	}

	return ret;
}

/*	$Function		:	RecivePCM
==  ===============================================================
==	Description		:	��Ƶ���ݴ��������������ص��õ�����Ƶ����
==	Argument		:	���������						
==				:			index ͨ����
==              :           pcm   ��Ƶ����
==              :           len   ��Ƶ���ݳ���	
== 	Return		:	
==	Modification	:	2005/11/28		chenmy   Create
==  ===============================================================
*/
int CDisplay::RecivePCM(int index, unsigned char *pcm, int len,int bitsPerSample,int samplesPerSecond)
{	
	if (m_nIndex != index)
	{
		return 1;
	}

	if (g_cDHPlayManage.pCallback[index] && g_cDHPlayManage.pCallback[index]->GetCBStatus(CBT_AudioCBFun))   //�Ƿ���Ƶ�ص�
	{
		g_cDHPlayManage.pCallback[index]->ProcessAudio(pcm ,len ,(bitsPerSample == 8)?T_AUDIO8:T_AUDIO16 , bitsPerSample);//����Ƶ�ص�������״̬��Ϊ"PROCESS",���û��ص��߳̽�����ִ�иûص�����
	}
	
	if (g_cDHPlayManage.pCallback[index] && g_cDHPlayManage.pCallback[index]->GetCBStatus(CBT_DecCBFun)
		&& (m_decType == DEC_AUDIO || m_decType == DEC_COMPLEX))   //�Ƿ���Ƶ�ص�
	{
		g_cDHPlayManage.pCallback[index]->ProcessDec(DEC_AUDIO,pcm,len,bitsPerSample,samplesPerSecond);//����Ƶ�ص�������״̬��Ϊ"PROCESS",���û��ص��߳̽�����ִ�иûص�����
	}
	else
	{
		if (m_nCoefficient != 0)
		{
			AdjustWaveAudio(pcm,len,bitsPerSample,m_nCoefficient) ;
		}

	 	int ret = m_renderManager.renderAudio(pcm, len,bitsPerSample,samplesPerSecond);   //������Ƶ	
		if (ret < 0)
		{
			Sleep(100) ;
			m_renderManager.renderAudio(pcm, len,bitsPerSample,samplesPerSecond);  
		}
	}
	
	return 0;
}

/*	$Function		:	Show
==  ===============================================================
==	Description		:	ͼƬ��ʾ��������ʾ����һ��ͼƬ
==	Argument		:						
==              :           
== 	Return		:	
==	Modification	:	2005/11/28		chenmy   Create
==  ===============================================================
*/
int CDisplay::Show()    
{
	BYTE *mYp,*mUp, *mVp;
	
	if(g_cDHPlayManage.pCallback[m_nIndex] && g_cDHPlayManage.pCallback[m_nIndex]->GetCBStatus(CBT_DecCBFun)
		&& (m_decType == DEC_VIDEO || m_decType == DEC_COMPLEX) )   //�Ƿ������ʾ�ص�
	{
		return 1 ;
	}

	if (!m_nWidth || !m_nHeight || m_IfRenderOpen == false)
	{
		return 1;
	}

	unsigned char* pDataBuf =  g_cDHPlayManage.pDHPlay[m_nIndex]->GetLastFrame();

	if (m_nDisplayType == DISPLAY_QUARTER)		
	{
		if (m_pQuarterBuf == NULL)
		{
			m_pQuarterBuf = new unsigned char[m_nWidth*m_nHeight*3/2];
		}

		mYp = m_pQuarterBuf;
		mUp = m_pQuarterBuf + m_nWidth * m_nHeight;
		mVp = m_pQuarterBuf + m_nWidth * m_nHeight * 5 / 4;

		ToQuarter(mYp,mUp, mVp,m_nWidth,m_nHeight) ;
		__try
		{
			m_renderManager.renderVideo(mYp, mUp, mVp, m_nWidth/2, m_nHeight/2 , m_nRotateType) ;//��ʾһ��ͼ��
		}
		__except(0,1)
		{
			int wlj = 0;
		}

	}
	else
	{
		mYp = pDataBuf;
		mUp = pDataBuf + m_nWidth * m_nHeight;
		mVp = pDataBuf + m_nWidth * m_nHeight * 5 / 4;
		__try
		{
			m_renderManager.renderVideo(mYp, mUp, mVp, m_nWidth, m_nHeight , m_nRotateType);//��ʾ���µ�һ������
		}
		__except(0,1)
		{
			int wlj = 0;
		}
	}

	return 0;
}

/*	$Function		:	ShowRegion
==  ===============================================================
==	Description		:	ͼƬ��ʾ��������ʾ����һ��ͼƬ
==	Argument		:	���������						
==				:		   nRegionNum   �����					
==              :           
== 	Return		:	
==	Modification	:	2006/4/28		zhougf   Create
==  ===============================================================
*/
int CDisplay::ShowRegion(int nRegionNum, unsigned char* pBuf)
{
	if (nRegionNum < 0 || nRegionNum >= MULTI_DISPLAY_RECT_NUM)
	{
		return 1 ;
	}

	__try
	{
		if (m_MultiDisInfo[nRegionNum].pSrcRect.left  == 0 &&
			m_MultiDisInfo[nRegionNum].pSrcRect.right == 0 &&
			m_MultiDisInfo[nRegionNum].pSrcRect.top   == 0 &&
			m_MultiDisInfo[nRegionNum].pSrcRect.bottom== 0 )
		{
			m_MultiDisInfo[nRegionNum].nVideoRender.renderVideo(pBuf, pBuf+m_nWidth*m_nHeight, 
				pBuf+m_nWidth*m_nHeight*5/4, m_nWidth, m_nHeight, m_nRotateType) ;
		}
		else
		{
			m_MultiDisInfo[nRegionNum].nVideoRender.renderVideo(pBuf, pBuf+m_nWidth*m_nHeight, 
				pBuf+m_nWidth*m_nHeight*5/4, m_nWidth, m_nHeight, m_nRotateType,
				&(m_MultiDisInfo[nRegionNum].pSrcRect)) ;
		}
// 		m_MultiDisInfo[nRegionNum].nVideoRender.renderVideo(pBuf, pBuf+m_nWidth*m_nHeight, 
// 			pBuf+m_nWidth*m_nHeight*5/4, m_nWidth, m_nHeight, m_nRotateType ,
// 			&(m_MultiDisInfo[nRegionNum].pSrcRect)) ;
	}
	__except(0,1)
	{
		int wlj = 0;
	}

	return 0 ;
}

BOOL CDisplay::SetRotateAngle(int rotateType)
{
	m_nRotateType = rotateType;
	return TRUE;
}

/*	$Function		:	GetPicHeight
==  ===============================================================
==	Description		:	���ͼƬ���Ժ������õ�ͼƬ�߶�
==	Argument		:						
==              :           
== 	Return		:	
==	Modification	:	2005/11/28		chenmy   Create
==  ===============================================================
*/
int CDisplay::GetPicHeight() 
{
	return m_nHeight ;
}


/*	$Function		:	GetPicWidth
==  ===============================================================
==	Description		:	���ͼƬ���Ժ������õ�ͼƬ���
==	Argument		:						
==              :           
== 	Return		:	
==	Modification	:	2005/11/28		chenmy   Create
==  ===============================================================
*/
int CDisplay::GetPicWidth()
{
	return m_nWidth ;
}

/*	$Function		:	GetCurFrameNum
==  ===============================================================
==	Description		:	�õ���ǰ��ʾ����������
==	Argument		:	
== 	Return		:	
==	Modification	:	2005/11/28		chenmy   Create
==  ===============================================================
*/
int CDisplay::GetCurFrameNum()
{
	return (m_CurFrameNum < 0)? 0 : m_CurFrameNum;
}

/*	$Function		:	GetPlayedFrames
==  ===============================================================
==	Description		:	��ò�������
==	Argument		:	
== 	Return		:	
==	Modification	:	2005/11/28		chenmy   Create
==  ===============================================================
*/
int CDisplay::GetPlayedFrames()
{
	return m_PlayedFrames ;
}

/*	$Function		:	SetCurFrameNum
==  ===============================================================
==	Description		:	���µ�ǰ��ʾ����������
==	Argument		:	���������
							FrameNum ����� 			
== 	Return		:	
==	Modification	:	2005/11/28		chenmy   Create
==  ===============================================================
*/
void CDisplay::SetCurFrameNum(int FrameNum)
{
	if (FrameNum < 0 || FrameNum >= g_cDHPlayManage.pDHFile[m_nIndex]->GetTotalFrames())
	{
		return ;
	}
	m_CurFrameNum = FrameNum ;
}


/*	$Function		:	SetOverlayMode
==  ===============================================================
==	Description		:	�����Ƿ���overlay��ʾ�������ùؼ�ɫ
==	Argument		:	���������						
==				:			boverlay   �Ƿ���overlay��ʾ
==              :           nColorKey  �ؼ�ɫ	
== 	Return		:	
==	Modification	:	2006/4/28		zhougf   Create
==  ===============================================================
*/
BOOL CDisplay::SetOverlayMode(BOOL boverlay, DWORD nColorKey)
{
    if (boverlay)
	{
		m_DisType = 1 ;
		m_colorkey = nColorKey ;
	}
	else
	{
		m_DisType = 0 ;
	}

	return true ;
}
/*	$Function		:	GetOverlayMode
==  ===============================================================
==	Description		:	���overlayģʽ
==	Argument		:		
== 	Return		:	
==	Modification	:	2006/4/28		zhougf   Create
==  ===============================================================
*/
DWORD CDisplay::GetOverlayMode()
{
	return (m_DisType == ByDDOverlay)? 1 : 0;
}
/*	$Function		:	GetColorKey
==  ===============================================================
==	Description		:	�õ��ؼ�ɫ
==	Argument		:		
== 	Return		:	
==	Modification	:	2006/4/28		zhougf   Create
==  ===============================================================
*/
DWORD CDisplay::GetColorKey()
{
	return m_colorkey ;
}

/*	$Function		:	MulitiDisplay
==  ===============================================================
==	Description		:	���ö�������ʾ
==	Argument		:	�������
						  nRegionNum   �����
						  hDestWnd     ���
						  pSrcRect     ��ָ��������С
						  bEnable      �Ƿ���ʾ
== 	Return		:	
==	Modification	:	2006/4/28		zhougf   Create
==  ===============================================================
*/
BOOL CDisplay::MulitiDisplay(int nRegionNum,HWND hDestWnd,RECT* pSrcRect,BOOL bEnable)
{	
	if (nRegionNum < 0 || nRegionNum >= MULTI_DISPLAY_RECT_NUM)
	{
		return FALSE ;
	}

	if (nRegionNum == 0)
	{
		if (pSrcRect == NULL || bEnable == FALSE)
		{
			m_mainRect.bottom = m_mainRect.right = m_mainRect.left = m_mainRect.top = 0;
		}
		else
		{
			m_mainRect.left = pSrcRect->left;
			m_mainRect.right = pSrcRect->right;
			m_mainRect.top = pSrcRect->top;
			m_mainRect.bottom = pSrcRect->bottom;
		}

		return TRUE;
	}

	if (bEnable == TRUE)
	{
// 		if (pSrcRect == NULL)
// 		{
// 			return FALSE ;
// 		}

		if (pSrcRect != NULL)
		{
			if (pSrcRect->right <= pSrcRect->left || pSrcRect->bottom <= pSrcRect->top 
				|| pSrcRect->bottom > m_nHeight 
				|| pSrcRect->right  > m_nWidth 
				|| pSrcRect->left   < 0
				|| pSrcRect->top    < 0)
			{
				return FALSE ;
			}
		}


		//����������Ѿ����ڣ���ֻ�ı���ָ��������С��λ�ã�pSrcRect��
		if (m_MultiDisInfo[nRegionNum].nRegionNum >= 0)//
		{
			m_MultiDisInfo[nRegionNum].pSrcRect.left   = (pSrcRect == NULL)?0:pSrcRect->left ;
			m_MultiDisInfo[nRegionNum].pSrcRect.right  = (pSrcRect == NULL)?m_nWidth:pSrcRect->right ;
			m_MultiDisInfo[nRegionNum].pSrcRect.bottom = (pSrcRect == NULL)?m_nHeight:pSrcRect->bottom ;
			m_MultiDisInfo[nRegionNum].pSrcRect.top    = (pSrcRect == NULL)?0:pSrcRect->top ;
			m_MultiDisInfo[nRegionNum].bEnable  = TRUE ;
			return TRUE ;
		}
		else//Ϊ�������һ·�ط�
		{	
			void (__stdcall *DDRAWCB)(int index, HDC hDc) = NULL;
			if ((g_cDHPlayManage.pCallback[m_nIndex]&&
				g_cDHPlayManage.pCallback[m_nIndex]->GetCBStatus(CBT_DrawCBFunEx)))
			{
				DDRAWCB = drawEx_cb;
			}

			int iRet = m_MultiDisInfo[nRegionNum].nVideoRender.openVideo(m_nIndex*FUNC_MAX_PORT+nRegionNum, hDestWnd, 
				352, 288, DDRAWCB, ByDDOffscreen, 0);
			if (iRet != 0)
			{
				int iRet = m_MultiDisInfo[nRegionNum].nVideoRender.openVideo(m_nIndex*FUNC_MAX_PORT+nRegionNum, hDestWnd, 
				352, 288, DDRAWCB, ByGDI, 0);

				if (iRet != 0) return FALSE;
			}
			
// 			m_MultiDisInfo[nRegionNum].nVideoRender.openVideo(m_nIndex*FUNC_MAX_PORT+nRegionNum, hDestWnd,352,288,
// 				drawEx_cb,ByDDOffscreen,0) ;

// 			m_MultiDisInfo[nRegionNum].nVideoRender.openVideo(-1, hDestWnd,352,288,
// 				NULL,ByDDOffscreen,0) ;
		
			m_MultiDisInfo[nRegionNum].pSrcRect.left   = (pSrcRect == NULL)?0:pSrcRect->left ;
			m_MultiDisInfo[nRegionNum].pSrcRect.right  =  (pSrcRect == NULL)?0:pSrcRect->right ;
			m_MultiDisInfo[nRegionNum].pSrcRect.bottom =  (pSrcRect == NULL)?0:pSrcRect->bottom ;
			m_MultiDisInfo[nRegionNum].pSrcRect.top    =  (pSrcRect == NULL)?0:pSrcRect->top ;
			m_MultiDisInfo[nRegionNum].bEnable         = TRUE ;
			m_MultiDisInfo[nRegionNum].nRegionNum      = nRegionNum ;

		}//end of else

	}//end of if (bEnable == TRUE)
	
	else
	{	
		m_MultiDisInfo[nRegionNum].nVideoRender.close() ;
		m_MultiDisInfo[nRegionNum].bEnable = FALSE;
		m_MultiDisInfo[nRegionNum].nRegionNum = -1;
		memset(&(m_MultiDisInfo[nRegionNum].pSrcRect),0,sizeof(RECT));
	}

	return TRUE ;
}

/*	$Function		:	SetDecCBType
==  ===============================================================
==	Description		:	���ý���ص�����
==	Argument		:	�������
						  dectype  ����ص�����
== 	Return		:	
==	Modification	:	2006/4/28		zhougf   Create
==  ===============================================================
*/
BOOL CDisplay::SetDecCBType(DWORD dectype)
{
	m_decType = (DEC_TYPE)dectype ;
	return TRUE ;
}

int CDisplay::GetDecType()
{
	return (int)m_decType;
}

void CDisplay::SetWidthHeight(int width, int height)
{
	m_nWidth = width;
	m_nHeight = height;
}

BOOL CDisplay::SetDisplayType(int displaytype)
{
	if (displaytype != DISPLAY_NORMAL && displaytype != DISPLAY_QUARTER)
	{
		return FALSE;
	}
	else
	{
		m_nDisplayType = displaytype ;
	}
	
	return TRUE ;
}

int CDisplay::GetDisplayType()
{
	return m_nDisplayType ;
}

void CDisplay::ToQuarter(BYTE* py,BYTE* pu,BYTE* pv, int width,int height) 
{
	int i, j, m, n ;
	
	m = n = 0 ;
	
	for (i = 0 ; i < (height>>1) ; ++i)
	{
		for (j = 0 ; j < (width>>1) ; ++j)
		{
			*(py + m) = *(py + m + n) ;
			++m ;
			++n ;
		}
		n += width ;
	}

	m = n = 0;
	
	for (i = 0 ; i < (height>>2) ; ++i) 
	{
		for (j = 0; j < (width>>2) ; ++j) 
		{
			*(pu + m) = *(pu + m + n) ;
			++m ;
			++n ;
		}
						
    	n += (width>>1);
	}

	m = n = 0;
	
	for (i = 0 ; i < (height>>2) ; ++i) 
	{
		for (j = 0; j < (width>>2) ; ++j) 
		{
			*(pv + m) = *(pv + m + n) ;
			++m ;
			++n ;
		}
						
    	n += (width>>1);
	}

}

BOOL CDisplay::AdjustWaveAudio(BYTE* pcm, unsigned int datalen, int bitsPerSample,long nCoefficient)
{
	if (bitsPerSample == 8)		//λ��8
	{				
		for(int i = 0 ; i < datalen; i++)
		{
			int x = (BYTE)pcm[i];	
			int y = (int)((float)x*(nCoefficient+100)/100+0.5);
													
			if (y > 255)
			{
				y = 255;
			}
			else;
			pcm[i] = y;
					
		} 	
	}

	else if (bitsPerSample == 16)	//λ��16
	{
		for (int i = 0; i < datalen/2; i++)
		{
			unsigned short *x = (unsigned short*)(pcm+2*i);
			unsigned long y = (unsigned long)((float)*x *(nCoefficient+100)/100+0.5);
			if (y >= (1<<16))
			{
				y = 65535;
			}
			else;

			pcm[2*i] = y%256;
			pcm[2*i+1] = y/256;							
		}				
	}

	else
	{
		return FALSE ;
	}

	return TRUE ;
}

BOOL CDisplay::SetCoefficient(int nCoefficient)
{
	m_nCoefficient = nCoefficient ;
	return TRUE ;
}

BOOL CDisplay::SetVolume(WORD volume)
{
	if (m_IfRenderOpen == false)
	{
		return FALSE ;
	}

	m_volume = (volume << 16) | volume;

	m_renderManager.setvolume(volume) ;
	
	return TRUE ;
}

WORD  CDisplay::GetVolume() 
{
	return m_volume & 0xffff ;
}

BOOL CDisplay::VerticalSyncEnable(BOOL bEnable)
{
	return m_renderManager.VideoVerticalSyncEnable(bEnable);
}