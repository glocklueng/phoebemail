/*
* Copyright (c) 2009, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �����ƣ�������������
* ժ��Ҫ������������ģ�顣
*
*/
//////////////////////////////////////////////////////////////////////////

#if !defined(AFX_DECODERDEVICE_H__BC11FEE5_2969_4260_97B8_6E884CD697AF__INCLUDED_)
#define AFX_DECODERDEVICE_H__BC11FEE5_2969_4260_97B8_6E884CD697AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "netsdk.h"

class CManager;


class CDecoderDevice  
{
public:
	CDecoderDevice(CManager *pManager);
	virtual ~CDecoderDevice();

public:
	/* ��ʼ�� */
	int							Init(void);

	/* ���� */
	int							Uninit(void);

	/* �ر�һ���豸������ͨ�� */
	int							CloseChannelOfDevice(afk_device_s* device);

	/* ͬ����ѯ��Ϣ */
	int							SysQueryInfo(LONG lLoginID, int nType, void* pCondition, char *pOutBuffer, int maxlen, int *pRetlen, int waittime=1000);


	/* ͬ��������Ϣ */
	int							SysSetupInfo(LONG lLoginID, int nType, void* pCondition, int waittime);
	
	/* ��ѯ�����������Ϣ */
	int							QueryDecoderInfo(LONG lLoginID, LPDEV_DECODER_INFO lpDecInfo, int waittime);

	/* ��ѯ������TV��Ϣ */
	int							QueryDecoderTVInfo(LONG lLoginID, int nMonitorID, LPDEV_DECODER_TV lpMonitorInfo, int waittime);

	/* ��ѯ����������ͨ����Ϣ */
	int							QueryDecEncoderInfo(LONG lLoginID, int nEncoderID, LPDEV_ENCODER_INFO lpEncoderInfo, int waittime);

	/* ���ý�����TV���ʹ��*/
	int							SetDecoderTVEnable(LONG lLoginID, BYTE *pDecTVOutEnable, int nBufLen, int waittime);

	/* �����첽�ص����� */
	int							SetOperateCallBack(LONG lLoginID, fMessDataCallBack cbMessData, DWORD dwUser);

	/* ���ƽ�����TV����ָ� */
	LONG						CtrlDecTVScreen(LONG lLoginID, int nMonitorID, BOOL bEnable, int nSplitType, BYTE *pEncoderChannel, int nBufLen, void* userdata);

	/* ������TV�����л� */
	LONG						SwitchDecTVEncoder(LONG lLoginID, int nEncoderID, LPDEV_ENCODER_INFO lpEncoderInfo, void* userdata);

	/* ���ӻ������ */          
	int							AddTourCombin(LONG lLoginID, int nMonitorID, int nSplitType, BYTE *pEncoderChannnel, int nBufLen, int waittime);
	
	/* ɾ��������� */          
	int							DelTourCombin(LONG lLoginID, int nMonitorID, int nCombinID, int waittime);

	/* �޸Ļ������ */
	int							SetTourCombin(LONG lLoginID, int nMonitorID, int nCombinID, int nSplitType, BYTE *pEncoderChannel, int nBufLen, int waittime);

	/* ��ѯ������� */          
	int							QueryTourCombin(LONG lLoginID, int nMonitorID, int nCombinID, LPDEC_COMBIN_INFO lpDecCombinInfo, int waittime);

	/* ���ý�������Ѳ */
	int							SetDecoderTour(LONG lLoginID, int nMonitorID, LPDEC_TOUR_COMBIN lpDecTourInfo, int waittime);
	
	/* ��ѯ��������Ѳ״̬ */   
	int							QueryDecoderTour(LONG lLoginID, int nMonitorID, LPDEC_TOUR_COMBIN lpDecTourInfo, int waittime);

	/* ������TV����ط� */
	LONG						DecTVPlayback(LONG lLoginID, int nEncoderID, DEC_PLAYBACK_MODE emPlaybackMode, LPVOID lpInBuffer, DWORD dwInBufferSize, void* userdata);

	/* ǰ���豸���ļ���ʽ�ط� */
	LONG						PlayBackByDevByFile(LONG lLoginID, int nEncoderID, LPDEC_PLAYBACK_FILE_PARAM lpPlaybackParam, void* userdata);

	/* ǰ���豸��ʱ�䷽ʽ�ط� */
	LONG						PlayBackByDevByTime(LONG lLoginID, int nEncoderID, LPDEC_PLAYBACK_TIME_PARAM lpPlaybackParam, void* userdata);

	/* ���ûطŽ��Ȼص����� */
	int							SetDecPlaybackPos(LONG lLoginID, fDecPlayBackPosCallBack cbPlaybackPos, DWORD dwUser);

	/* �طſ��� */
	int							CtrlDecPlayback(LONG lLoginID, int nEncoderID, DEC_CTRL_PLAYBACK_TYPE emCtrlType, int nValue, int waittime);

	/* ��ѯ����ͨ������*/
	int							QuerChannelFlux(LONG lLoginID, int nEncoderID, DEV_DECCHANNEL_STATE* lpChannelState, int waittime);

	/* ��Ѳ����*/
	int							CtrlDecTour(LONG lLoginID, int nMonitorID, DEC_CTRL_TOUR_TYPE emCtrlParm, int waittime);

private:
	CManager*		m_pManager;
};


#endif // !defined(AFX_DECODERDEVICE_H__BC11FEE5_2969_4260_97B8_6E884CD697AF__INCLUDED_)


