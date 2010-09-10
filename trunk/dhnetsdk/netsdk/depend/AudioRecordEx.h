#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#if !defined(__AUDIORECORDEX_H__)
#define __AUDIORECORDEX_H__

#ifdef AUDIORECORDEX_EXPORTS
#define AUDIORECORDEX_API __declspec(dllexport)
#else
#define AUDIORECORDEX_API __declspec(dllimport)
#endif

//¼����̬��_�ص�����(Mpeg���ݻ�����,���ݳ���)
typedef void (WINAPI *pCallFunction)(LPBYTE pDataBuffer, DWORD DataLength, int user);

typedef struct AUDIOFORMAT
{    
	DWORD		dwFrameLen;			//ÿ֡����
    WORD        wChannels;          // ������  --2
    DWORD       dwSamplesPerSec;     // ������ --44100
    WORD        wBitsPerSample;     // ÿ���������� --16
	UINT		nAudioBitrate;		//	���� --vcd:224K
	UINT		nAudioLayer;			//	��1:1, ��2:2
} AUDIOFORMAT;

/*
AudioBitrate:
          {0,32,64,96,128,160,192,224,256,288,320,352,384,416,448} //��1
          {0,32,48,56,64,80,96,112,128,160,192,224,256,320,384}    //��2
*/
//¼����̬��_��ʼ��
AUDIORECORDEX_API int WINAPI InitAudioRecordEx(AUDIOFORMAT tempFormat);

//¼����̬��_ע��ʹ��
/*
 *	����ķ���ֵ��һ�������������ֻ��Ϊ�˳�ʹ��ʱ����CloseAudioRecordEx(HANDLE huser)�ṩ�����ġ�
 */
AUDIORECORDEX_API HANDLE WINAPI OpenAudioRecordEx(pCallFunction pProc, int user);
//¼����̬��_�˳�ʹ��
/*
 *	�������huser��ֵҪ����ע��������huser�Ƿ�NULL�ľͰ�huserָ����ע����Ϣ�������������NULL����������ǰע�����Ϣȫ
 *	������
 */
AUDIORECORDEX_API int WINAPI CloseAudioRecordEx(HANDLE huser);

//������̬��_�ر�
AUDIORECORDEX_API int WINAPI UnInitAudioRecordEx();

#endif //__AUDIORECORDEX_H__

