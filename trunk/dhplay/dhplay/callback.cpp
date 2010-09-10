/*
**  ************************************************************************
**                                     DHPlay  ͨ�ò���SDK
**         (c) Copyright 1992-2004, ZheJiang Dahua Technology Stock Co.Ltd.
**                            All Rights Reserved
**
**	File  Name	: callback.cpp
**	Description	: ����sdk�ص����Ƴ���
**	Modification	: 2005/01/10		chenmy		Create the file
**  ************************************************************************
*/
#include "StdAfx.h"
#include "callback.h"
#include "playmanage.h"

/*	$Function		:	CCallback
==  ===============================================================
==	Description		:	���캯��
==	Argument		:	���������
							nPort �˿ں�
==				:	
== 	Return		:	
==	Modification	:	2005/01/10		chenmy   Create
==  ===============================================================
*/
CCallback::CCallback(LONG nPort)
{
	m_nIndex = nPort;               //��������	

	for(int i = 0; i < CBT_TOTAL; i++)
	{
		m_cbState[i] = false;           
	}

	m_cbStreamState = TRUE ;
	
	//��ʼ�����ص�����ָ��Ϊ��ָ�� 
	cb_Dec         = NULL ;                  
	temp_Dec       = NULL ;

	cb_Display     = NULL ;
	temp_Display   = NULL ;	

	cb_Draw        = NULL ;
	temp_Draw      = NULL ;

	cb_Audio       = NULL ;
	temp_Audio     = NULL ;

	cb_Verify      = NULL ;
	temp_Verify    = NULL ;

	cb_EncChange   = NULL ;
	temp_Verify    = NULL ;

	cb_FileRef     = NULL ;
	temp_FileRef   = NULL ;

	cb_Sourcebuf   = NULL ;
	temp_SourceBuf = NULL ;

	cb_DrawEx      = NULL ;
	temp_DrawEx    = NULL ;
	
	cb_VisibleDec = NULL;
	temp_VisibleDec = NULL;

	cb_demux = NULL;
	temp_demux = NULL;
}

/*	$Function		:	~CCallback
==  ===============================================================
==	Description		:	��������
==	Argument		:	
==				:	
== 	Return		:	
==	Modification	:	2005/01/10		chenmy   Create
==  ===============================================================
*/
CCallback::~CCallback()
{

}


/*	$Function		:	GetCBStatus
==  ===============================================================
==	Description		:	��ȡ�ص�״̬���������ĳ�ص������Ƿ�������Ч 1��Ч��0 ��Ч
==	Argument		:	���������
							nStatus �ص���������
==				:	
== 	Return		:	
==	Modification	:	2005/01/10		chenmy   Create
==  ===============================================================
*/
BOOL CCallback::GetCBStatus(CALLBACK_TYPE nStatus)
{
	if (nStatus >= CBT_TOTAL)
	{
		return FALSE ;
	}
	return m_cbState[nStatus]  ;
}

/*	$Function		:	SetDecCallBack
==  ===============================================================
==	Description		:	����ص����ƺ���������/ȡ������ص�
==	Argument		:	���������
							pcbDec ����ص�����ָ��
==				:	
== 	Return		:	
==	Modification	:	2005/01/10		chenmy   Create
==  ===============================================================
*/
BOOL CCallback::SetDecCallBack(Callback_Dec pcbDec,BOOL IfSet)
{
	//������ָ��ָ���ɲ��������ݽ����ĺ�����
	m_cbState[CBT_DecCBFun] = IfSet ;
	mParam_decCB.nUser = 0;
	temp_Dec = pcbDec ;
	
	if (temp_Dec == NULL)
		m_cbState[CBT_DecCBFun] = false;

	return TRUE;	
}

/*	$Function		:	SetDecCallBackEx
==  ===============================================================
==	Description		:	����ص���չ���ƺ���������/ȡ������ص�
==	Argument		:	���������
							pcbDec ����ص�����ָ��
==				:			nUser  �û�����
== 	Return		:	
==	Modification	:	2009/02/16		wanglanjun   Create
==  ===============================================================
*/
BOOL CCallback::SetDecCallBackEx(Callback_Dec pcbDec,long nUser,BOOL IfSet)
{
	//������ָ��ָ���ɲ��������ݽ����ĺ�����
	m_cbState[CBT_DecCBFun] = IfSet ;
	mParam_decCB.nUser = nUser;
	temp_Dec = pcbDec ;
	
	if (temp_Dec == NULL)
		m_cbState[CBT_DecCBFun] = false;

	return TRUE;	
}

/*	$Function		:	SetVisibleDecCallBack
==  ===============================================================
==	Description		:	����ص�ͬʱ��ʾ��Ƶ������/ȡ������ص�
==	Argument		:	���������
							pcbDec ����ص�����ָ��
==				:			nUser  �û�����
== 	Return		:	
==	Modification	:
==  ===============================================================
*/
BOOL CCallback::SetVisibleDecCallBack(Callback_Dec pcbDec,long nUser,BOOL IfSet)
{
	//������ָ��ָ���ɲ��������ݽ����ĺ�����
	m_cbState[CBT_VisibleDec] = IfSet ;
	mParam_decCB.nUser = nUser;
	temp_VisibleDec = pcbDec ;
	
	if (temp_VisibleDec == NULL)
		m_cbState[CBT_VisibleDec] = false;

	return TRUE;	
}

/*	$Function		:	ProcessDec
==  ===============================================================
==	Description		:	����ص��������������ص�
==	Argument		:	
==				:	
== 	Return		:	
==	Modification	:	2005/01/10		chenmy   Create
==  ===============================================================
*/
BOOL CCallback::ProcessDec(DEC_TYPE type,BYTE* pBuf,int nSize,int width,int height)
{	
	FRAME_INFO nFrameInfo ;
	
	if (type == DEC_VIDEO) 
	{
		//������ֵ
		nFrameInfo.nWidth = width; //�������λ���ء��������Ƶ������Ϊ0�� 
		nFrameInfo.nHeight = height; //����ߡ��������Ƶ������Ϊ0�� 
		nFrameInfo.nStamp = g_cDHPlayManage.pDHPlay[m_nIndex]->GetPlayedTimeEX(); //ʱ����Ϣ����λ���롣 
		nFrameInfo.nType = T_YV12; //�������ͣ�T_AUDIO16��T_RGB32�� T_YV12������궨��˵���� 
		nFrameInfo.nFrameRate = g_cDHPlayManage.pDHPlay[m_nIndex]->GetFrameRate();//����ʱ������ͼ��֡�ʡ�
	}
	
	if (type == DEC_AUDIO)
	{
		nFrameInfo.nWidth = nFrameInfo.nHeight = 0 ;
		nFrameInfo.nStamp = g_cDHPlayManage.pDHPlay[m_nIndex]->GetPlayedTimeEX(); //ʱ����Ϣ����λ���롣

		if (width == 8)
		{
			nFrameInfo.nType = T_AUDIO8; //�������ͣ�T_AUDIO16��T_RGB32�� T_YV12������궨��˵���� 
		}
		else if (width == 16)
		{
			nFrameInfo.nType = T_AUDIO16;
		}

		nFrameInfo.nFrameRate = height;		
	}

	cb_Dec = temp_Dec;
	//���ý���ص�����
	if (cb_Dec == NULL)
	{
		return FALSE ;
	}
	
	cb_Dec(m_nIndex,(char*)pBuf,nSize,&nFrameInfo, mParam_decCB.nUser/*g_cDHPlayManage.pDHPlay[m_nIndex]->GetPlayedFrames()*/, NULL);

	return TRUE;

}

BOOL CCallback::ProcessVisibleDec(DEC_TYPE type,BYTE* pBuf,int nSize,int width,int height)
{	
	FRAME_INFO nFrameInfo;
	
	if (type == DEC_VIDEO) 
	{
		//������ֵ
		nFrameInfo.nWidth = width; //�������λ���ء��������Ƶ������Ϊ0�� 
		nFrameInfo.nHeight = height; //����ߡ��������Ƶ������Ϊ0�� 
		nFrameInfo.nStamp = g_cDHPlayManage.pDHPlay[m_nIndex]->GetPlayedTimeEX(); //ʱ����Ϣ����λ���롣 
		nFrameInfo.nType = T_YV12; //�������ͣ�T_AUDIO16��T_RGB32�� T_YV12������궨��˵���� 
		nFrameInfo.nFrameRate = g_cDHPlayManage.pDHPlay[m_nIndex]->GetFrameRate();//����ʱ������ͼ��֡�ʡ�
	}
	
	if (type == DEC_AUDIO)
	{
		nFrameInfo.nWidth = nFrameInfo.nHeight = 0 ;
		nFrameInfo.nStamp = g_cDHPlayManage.pDHPlay[m_nIndex]->GetPlayedTimeEX(); //ʱ����Ϣ����λ���롣
		
		if (width == 8)
		{
			nFrameInfo.nType = T_AUDIO8; //�������ͣ�T_AUDIO16��T_RGB32�� T_YV12������궨��˵���� 
		}
		else if (width == 16)
		{
			nFrameInfo.nType = T_AUDIO16;
		}
		
		nFrameInfo.nFrameRate = height;		
	}
	
	cb_VisibleDec = temp_VisibleDec;
	//���ý���ص�����
	if (cb_VisibleDec == NULL)
	{
		return FALSE ;
	}
	
	cb_VisibleDec(m_nIndex,(char*)pBuf,nSize,&nFrameInfo, mParam_decCB.nUser/*g_cDHPlayManage.pDHPlay[m_nIndex]->GetPlayedFrames()*/, NULL);
	
	return TRUE;
}

/*	$Function		:	SetDisplayCallBack
==  ===============================================================
==	Description		:	ץͼ�ص����ƺ���������ץͼ�ص�
==	Argument		:	���������
							pcbDisplay ץͼ�ص�����ָ��
==				:	
== 	Return		:	
==	Modification	:	2005/01/10		chenmy   Create
==  ===============================================================
*/
BOOL CCallback::SetDisplayCallBack(Callback_Display pcbDisplay, long nUser)
{
	//������ָ��ָ���ɲ��������ݽ����ĺ�����
	temp_Display = pcbDisplay;
	mParam_display.nUser = nUser;

	if (temp_Display != NULL) 
	{
		m_cbState[CBT_DisplayCBFun] = true;
	}
	else 
	{
		m_cbState[CBT_DisplayCBFun] = false;
	}
	
	return TRUE;
}

/*	$Function		:	ProcessDisplay
==  ===============================================================
==	Description		:	ץͼ�ص�����������ץͼ�ص�
==	Argument		:	
==				:	
== 	Return		:	
==	Modification	:	2005/01/10		chenmy   Create
==  ===============================================================
*/
BOOL CCallback::ProcessDisplay(BYTE* pBuf,int width,int height)
{
	//������ֵ
	cb_Display = temp_Display ;

	if (cb_Display == NULL)
	{
		return FALSE ;
	}
	//����ץͼ�ص�����
	cb_Display(m_nIndex,(char*)pBuf,width*height*3/2,width,height,
		g_cDHPlayManage.pDHPlay[m_nIndex]->GetPlayedTimeEX(),T_YV12,mParam_display.nUser) ;

	return TRUE;
}
/*	$Function		:	SetDrawCallback
==  ===============================================================
==	Description		:	���û�ͼ��ص�
==	Argument		:	
==				:	
== 	Return		:	
==	Modification	:	2005/01/10		chenmy   Create
==  ===============================================================
*/
BOOL CCallback::SetDrawCallback(Callback_Draw pcbDraw, long nUser)
{
	mParam_draw.nUser = nUser;
	temp_Draw = pcbDraw;

	if (temp_Draw != NULL)
	{
		m_cbState[CBT_DrawCBFun] = true;
	}
	else 
	{
		m_cbState[CBT_DrawCBFun] = false;
	}
	
	return TRUE;
}
BOOL CCallback::ProcessDraw(HDC hDC)
{
	cb_Draw = temp_Draw ;

	if (cb_Draw == NULL)
	{
		return FALSE ;
	}
	
	cb_Draw(m_nIndex,hDC,mParam_draw.nUser) ;
	
	return TRUE ;
}

BOOL CCallback::SetDrawExCallback(Callback_DrawEx pcbDrawEx, long nReginNum, long nUser)
{
	if (nReginNum > MAX_DISPLAY_WND || nReginNum < 0)
	{
		return FALSE;
	}
	
	mParam_drawEx.nUser = nUser;
	temp_DrawEx = pcbDrawEx;
	
	if (temp_DrawEx != NULL)
	{
		m_cbState[CBT_DrawCBFunEx] = true;
	}
	else 
	{
		m_cbState[CBT_DrawCBFunEx] = false;
	}
	
	return TRUE;
}

BOOL CCallback::ProcessDrawEx(long nReginNum, HDC hDC)
{
	cb_DrawEx = temp_DrawEx ;
	
	if (cb_DrawEx == NULL)
	{
		return FALSE ;
	}
	
	cb_DrawEx(m_nIndex,nReginNum, hDC,mParam_drawEx.nUser) ;
	
	return TRUE ;
}

BOOL CCallback::SetFileRefCallBack(Callback_FileRef pcbFileRef, DWORD nUser)
{
	mParam_fileref.nUser = nUser ;
	temp_FileRef = pcbFileRef ;

	if (temp_FileRef != NULL)
	{
		m_cbState[CBT_FILEREF] = true;
	}
	else
	{
		m_cbState[CBT_FILEREF] = false;
	}
	
	return TRUE;
}
BOOL CCallback::ProcessFileRef()
{
	cb_FileRef = temp_FileRef ;

	if (cb_FileRef == NULL)
	{
		return FALSE ;
	}

	cb_FileRef(m_nIndex, mParam_fileref.nUser) ;

	return TRUE ;
}

BOOL CCallback::SetFileRefCallBackEx(Callback_FileRefEx pcbFileRefEx, DWORD nUser)
{
	mParam_fileref.nUser = nUser ;
	temp_FileRefEx = pcbFileRefEx ;
	
	if (temp_FileRefEx != NULL)
	{
		m_cbState[CBT_FILEREFEX] = true;
	}
	else
	{
		m_cbState[CBT_FILEREFEX] = false;
	}
	
	return TRUE;
}

BOOL CCallback::ProcessFileRefEx(BOOL bIndexCreated)
{
	cb_FileRefEx = temp_FileRefEx ;
	
	if (cb_FileRefEx == NULL)
	{
		return FALSE ;
	}
	
	cb_FileRefEx(m_nIndex, bIndexCreated, mParam_fileref.nUser) ;
	
	return TRUE ;
}
/*	$Function		:	SetSourceBufCallBack
==  ===============================================================
==	Description		:	��������ԴС�ڷ�ֵ�ص����˻ص��ڻص��߳��м�⣬һ����⵽����ִ�У���־��λ��Ч����Ҫ�û���λ��־
==	Argument		:	
==				:	
== 	Return		:	
==	Modification	:	2005/01/17		chenmy   Create
==  ===============================================================
*/
BOOL CCallback::SetSourceBufCallBack(Callback_SourceBuf pcbSourceBuf, DWORD nThreShold, long dwUser, void *pReserved)
{
	mParam_sourcebuf.nThreShold = nThreShold;
	mParam_sourcebuf.nUser = dwUser;
	
	temp_SourceBuf = pcbSourceBuf;

	if (temp_SourceBuf != NULL)
	{
		m_cbState[CBT_SourceBuf] = true;
	}
	else 
	{
		m_cbState[CBT_SourceBuf] = false;
	}
	
	return TRUE;
}

/*	$Function		:	ResetSourceBufFlag
==  ===============================================================
==	Description		:	��λ�ص���־
==	Argument		:	
==				:	
== 	Return		:	
==	Modification	:	2005/01/17		chenmy   Create
==  ===============================================================
*/
BOOL CCallback::ResetSourceBufFlag()
{
	if (cb_Sourcebuf == NULL)
	{
		return FALSE;
	}

	m_cbStreamState = TRUE ;
	
	return TRUE;
}
/*	$Function		:	ProcessSourceBuf
==  ===============================================================
==	Description		:	����ԴС�ڷ�ֵ�ص�����
==	Argument		:	
==				:	
== 	Return		:	
==	Modification	:	2005/01/17		chenmy   Create
==  ===============================================================
*/
BOOL CCallback::ProcessSourceBuf()
{
	DWORD nRemain;
	
	if (g_cDHPlayManage.pDHPlay[m_nIndex]==NULL)
	{
		return FALSE;
	}

	//ȡ�õ�ǰ����Դ��ʣ�����ݴ�С
	nRemain = g_cDHPlayManage.pDHPlay[m_nIndex]->GetSourceBufferRemain();

	if (nRemain <= mParam_sourcebuf.nThreShold && m_cbStreamState) 
	{
		cb_Sourcebuf = temp_SourceBuf ;
		
		if (cb_Sourcebuf == NULL)
		{
			return FALSE ;
		}
		else
		{
			m_cbStreamState = FALSE ;
			cb_Sourcebuf(m_nIndex,nRemain,mParam_sourcebuf.nUser,0);			
		}
				
	}
	
	return TRUE;
}
/*	$Function		:	SetAudioCallBack
==  ===============================================================
==	Description		:	��Ƶ�ص����ƺ�����������Ƶ�ص�
==	Argument		:	���������
							pcbAudio ��Ƶ�ص�����ָ��
							nUser �û�
==				:	
== 	Return		:	
==	Modification	:	2005/01/10		chenmy   Create
==  ===============================================================
*/
BOOL CCallback::SetAudioCallBack(Callback_Audio pcbAudio, long nUser)
{
	temp_Audio = pcbAudio ;
	mParam_audio.nUser = nUser;

	if (temp_Audio != NULL)
	{
		m_cbState[CBT_AudioCBFun] = true;
	}
	else
	{
		m_cbState[CBT_AudioCBFun] = false ;
	}
	
	return TRUE;
}

/*	$Function		:	ProcessAudio
==  ===============================================================
==	Description		:	��Ƶ�ص�������������Ƶ�ص�
==	Argument		:	
==				:	
== 	Return		:	
==	Modification	:	2005/01/10		chenmy   Create
==  ===============================================================
*/
BOOL CCallback::ProcessAudio(BYTE * pAudioBuf, long nSize, long nStamp, long nType)
{
	cb_Audio = temp_Audio;
	
	if (cb_Audio == NULL)
	{
		return FALSE ;
	}

	//������Ƶ�ص�����
	cb_Audio(m_nIndex, (char*)pAudioBuf, nSize, 
		g_cDHPlayManage.pDHPlay[m_nIndex]->GetPlayedTimeEX(),nType,mParam_audio.nUser);

	return TRUE;
}


/*	$Function		:	SetVerifyCallBack
==  ===============================================================
==	Description		:	ˮӡ���ƺ���������ˮӡ�ص�
==	Argument		:	���������
							pcbfunVerify ˮӡ�ص�����ָ��
==				:			nBeginTime ��ʼʱ��
							nUser �û�
== 	Return		:	
==	Modification	:	2005/01/10		chenmy   Create
==  ===============================================================
*/
BOOL CCallback::SetVerifyCallBack(Callback_Verify pcbfunVerify, DWORD nBeginTime, DWORD nEndTime, long nUser)
{
	//������ָ��ָ���ɲ������ݽ����ĺ�����
	temp_Verify = pcbfunVerify;
	//��������
	mParam_verify.nBeginTime = nBeginTime;
	mParam_verify.nEndTime = nEndTime;
	mParam_verify.nUser = nUser;

	if (temp_Verify != NULL)
	{
		m_cbState[CBT_VerifyCBFun] = true;
	}
	else
	{
		m_cbState[CBT_VerifyCBFun] = false;
	}

	return TRUE;
}

/*	$Function		:	ProcessVerify
==  ===============================================================
==	Description		:	ˮӡ�ص�����������ˮӡ�ص�
==	Argument		:	
==				:	
== 	Return		:	
==	Modification	:	2005/01/10		chenmy   Create
==  ===============================================================
*/
BOOL CCallback::ProcessVerify()
{
	cb_Verify = temp_Verify ;

	if (cb_Verify == NULL)
	{
		return FALSE ;
	}
	//����ˮӡ�ص�����
	cb_Verify(m_nIndex, &mParam_verify.nFilePos, mParam_verify.bIsVideo, 
		mParam_verify.nUser);
	
	return TRUE;
}


/*	$Function		:	SetEncChangeCallBack
==  ===============================================================
==	Description		:	�����ʽ���ƺ������ı�����ʽ�ص�
==	Argument		:	���������
							pcbEncChange �ı�����ʽ�Ļص�����ָ��
==				:			nUser �û�
== 	Return		:	
==	Modification	:	2005/01/10		chenmy   Create
==  ===============================================================
*/
BOOL CCallback::SetEncChangeCallBack(Callback_EncChange pcbEncChange, long nUser)
{
	//����ָ��ָ���ɲ������ݹ����ĺ�����
	temp_EncChange = pcbEncChange;

	if (temp_EncChange != NULL)
	{
		m_cbState[CBT_EncChangeCBFun] = TRUE;
	}
	else
	{
		m_cbState[CBT_EncChangeCBFun] = FALSE;
	}
	
	mParam_encchange.nUser = nUser;
	
	return TRUE;
}

/*	$Function		:	ProcessEncChange
==  ===============================================================
==	Description		:	�����ʽ�ı�ص���������������ʽ�ı�ص�
==	Argument		:	
==				:	
== 	Return		:	
==	Modification	:	2005/01/10		chenmy   Create
==  ===============================================================
*/
BOOL CCallback::ProcessEncChange()
{
	cb_EncChange = temp_EncChange ;
	
	if (cb_EncChange == NULL)
	{
		return FALSE ;
	}

	cb_EncChange(m_nIndex, mParam_encchange.nUser);
	
	return TRUE;
}

BOOL CCallback::SetFileEndCallBack(Callback_FileEnd pcbFileEnd, DWORD nUser) 
{
	mParam_fileend.nUser = nUser ;
	temp_FileEnd = pcbFileEnd ;

	if (temp_FileEnd != NULL)
	{
		m_cbState[CBT_FileEnd] = TRUE;
	}
	else
	{
		m_cbState[CBT_FileEnd] = FALSE;
	}
	
	return TRUE;
}

BOOL CCallback::ProcessFileEnd()
{
	cb_FileEnd = temp_FileEnd ;

	if (cb_FileEnd == NULL)
	{
		return FALSE ;
	}

	cb_FileEnd(m_nIndex, mParam_fileend.nUser) ;

	return TRUE ;
}

BOOL CCallback::SetDemuxCallBack(Callback_Demux pcbDemux, long nUser)
{
	temp_demux = pcbDemux;
	mParam_demux.nUser = nUser;

	if (temp_demux != NULL) 
	{
		m_cbState[CBT_DemuxCBFun] = true;
	}
	else 
	{
		m_cbState[CBT_DemuxCBFun] = false;
	}
	
	return TRUE;
}

BOOL CCallback::ProcessDemux(char * pBuf,long nSize, void* pParam)
{
	cb_demux = temp_demux;

	if (cb_demux == NULL)
	{
		return FALSE;
	}

	cb_demux(m_nIndex, pBuf, nSize, pParam, 0, mParam_demux.nUser);

	return TRUE;
}