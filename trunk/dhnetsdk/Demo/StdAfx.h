// stdafx.h : include file for standard system include files,
//  or project specific include files that are used frequently, but
//      are changed infrequently
//

#if !defined(_STDAFX_H_)
#define _STDAFX_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define VC_EXTRALEAN		// Exclude rarely-used stuff from Windows headers

#include <afxwin.h>         // MFC core and standard components
#include <afxext.h>         // MFC extensions
#include <afxdisp.h>        // MFC Automation classes
#include <afxdtctl.h>		// MFC support for Internet Explorer 4 Common Controls
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>			// MFC support for Windows Common Controls
#endif // _AFX_NO_AFXCMN_SUPPORT

//#define LANG_ENG
#define LANG_ENG

#ifdef LANG_ENG
#include "messagetext_eng.h"
#else
//#include "messagetext.h"
#endif
#include "Depend/netsdk.h"

//#define STREAMPARSER

#include "DevMgr.h"

typedef struct _In_DeviceInfo
{
    long                lDeviceID;   	//�豸��ID
    char                cDeviceName[32]; //�豸����
    unsigned long       unTypeIndex;      //�豸����
    unsigned long       unNetType;       //����ģʽ,0����ͷģʽ��1�Ǵ���ͷģʽ
    unsigned long       unVideoCodeType; //��Ƶ�����ʽ:8ΪMPEG4,9ΪH264
    unsigned long       unChannelNum;   //��ǰ�豸ͨ����
    unsigned long       unAlarmInNum;   //��ǰ�豸��������ͨ����
    unsigned long       unAlarmOutNum;  //��ǰ�豸�������ͨ����
}In_DeviceInfo;

#define CONFIG_WAITTIME	500


//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(_STDAFX_H_)
