/*
* Copyright (c) 2009, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �����ƣ�Э��ջ
* ժ��Ҫ������������Э�����
*         ��ͬ�豸�����ϲ�һ���������豸�������֡�
*
*/
//////////////////////////////////////////////////////////////////////////

#ifndef _DVRPACKET_COMM_H_
#define _DVRPACKET_COMM_H_

#include "../kernel/afkinc.h"

class CDvrDevice;
class CDvrSearchChannel;

/**********************************
Ŀǰ��Ҫ����Ȩ�Ĺ���:
�Խ�
�ش���¼
Уʱ
����ϵͳ����
�ط�
************************************/

//ʵ�Ӽ���
bool sendMonitor_comm(CDvrDevice* device, int channel, int subtype, bool bstart, 
					  int nConnType, int nConnectID, char* szLocalIp, int nLocalPort);

//��ѯ¼��
bool sendQueryRecord_comm(CDvrDevice* device, 
                      afk_query_record_s queryrecord, int nParam);

//��ѯ��־
bool sendQueryLog_comm(CDvrDevice* device, int logtype, int nParam, char* szPacket = NULL, int nPacketLen = 0);

//����
bool sendDownload_comm(CDvrDevice* device, 
                  afk_record_file_info_s recordinfo, bool bstart, int nByTime, int nConnectID, DWORD dwParm = 0);

//���������ļ�
bool sendExportCfgFile_comm(CDvrDevice* device, bool bStart, int nParam = 0);

//���������ļ�
bool sendImportCfgFile_comm(CDvrDevice* device, afk_upgrade_channel_param_s *ucparam);

int sendImportCfgData_comm(CDvrDevice* device, int packetId, char *buf, int len, afk_upgrade_channel_param_s *ucparam);


//���ؿ���
bool sendDownload_control_comm(CDvrDevice* device, int channel,
                               int offset_time, int offset_data, int nConnectID);

//��������׼��
//Edited by Linjy-2006-11-2
bool sendUpgradeControl_comm(CDvrDevice* device, afk_upgrade_channel_param_s *ucparam/*, bool bstart*/);

//����������Ϣ
int sendUpgradeData_comm(CDvrDevice* device, int packetId, char *buf, int len, afk_upgrade_channel_param_s *ucparam);

//����Ԥ����Ϣ
bool sendPreview_comm(CDvrDevice* device, 
                 int type1, int type2, bool bstart);

//���󱨾���Ϣ
bool sendAlarmQuery_comm(CDvrDevice* device, bool bRecordState/*�ò���û�ã�*/, int proType = 0);

//���Ϳ�����Ϣ
bool sendControl_comm(CDvrDevice* device, 
                      int ch, int type1, int type2, int parm1, int parm2, int parm3, char *pParam4 = NULL);

//��ѯͨ����
bool sendQueryChannelName_comm(CDvrDevice* device);

//��ѯ��������������
bool sendQueryAlarmInput_comm(CDvrDevice* device);

//��ѯ�������������
bool sendQueryAlarmOutput_comm(CDvrDevice* device);

//��ѯ���߱������
bool sendQueryWirelessAlarmOutput_comm(CDvrDevice* device);

//��ѯ����������ʽ
bool sendQueryAlarmTrrigerMode_comm(CDvrDevice* device);

//���ñ���������ʽ
bool sendSettingAlarmTrrigerMode_comm(CDvrDevice* device, afk_alarm_trriger_mode_s dainfo);

//���ñ���������
bool sendSettingAlarm_comm(CDvrDevice* device, afk_alarm_control_info_s alarminfo);

//���ñ������������
bool sendSetingDecoderAlarm_comm(CDvrDevice* device, afk_decoder_alarm_info_s dainfo);

//����͸������
bool sendSettingSerial_comm(CDvrDevice* device, afk_trans_channel_param_s transinfo);

//����͸��������Ϣ
bool sendTransSerialData_comm(CDvrDevice* device, int transtype, char *buffer, int buflen);

//���ͶԽ�Ҫ��
bool sendTalkRequest_comm(CDvrDevice* device, int channel, bool bstart, int encodetype=0);

//���ͶԽ���Ϣ
bool sendTalkData_comm(CDvrDevice* device, int channel, char *buffer, int buflen, int encodetype=0);

//ת��֡��
int  getframerate_comm(CDvrDevice* device, unsigned char chframerate);

//��ѯ����
bool sendQueryConfig_comm(CDvrDevice* device, unsigned short configtype, int param);

//��������
bool sendSetupConfig_comm(CDvrDevice* device, unsigned short configtype, int param, unsigned char *buffer, int buflen);

//����¼��״̬
bool sendSetupRecordState_comm(CDvrDevice* device, unsigned char *buffer, int buflen);

//��ѯ�豸ʱ��
bool sendQueryDeviceTime_comm(CDvrDevice* device);

//�����豸ʱ��
bool sendSetupDeviceTime_comm(CDvrDevice* device, int year, int month, int day,
                              int hour, int minute, int second);

//��ѯЭ��(����Э���������Э��)
bool sendQueryProtocol_comm(CDvrDevice* device, int protocoltype,DWORD dwProtocolIndex=0);

//��ѯϵͳ��Ϣ
bool sendQuerySystemInfo_comm(CDvrDevice* device, int type, int param);

//�����û�����
bool sendUserOperate_comm(CDvrDevice* device, int type, char *buffer, int bufferlen);

//ǿ��I��
bool sendForceIframe_comm(CDvrDevice* device,  unsigned char mainchn, unsigned char subchn);

//������������
bool sendLimitFlux_comm(CDvrDevice* device, unsigned short limitflux);

//��ѯ�豸����״̬
bool sendQuerydevstate_comm(CDvrDevice* device, unsigned char chn, unsigned char type);

//ͨ��������DDNS��ѯIP
bool sendQueryIPByName_comm(CDvrDevice* device, char *name, int namelen);

//��ѯ�豸������״̬
bool sendQueryAlarmState_comm(CDvrDevice* device, int statetype,int deviceid = 0);

//Զ��ץͼ
bool sendCapture_comm(CDvrDevice* device, int channel, int pipeno, bool bstart);

//���û���OSD����
bool sendSetupChannelOsdString_comm(CDvrDevice* device, int channelno, int enable, int* position, unsigned char *buf, int buflen);

//ץͼ����
bool sendSnap_comm(CDvrDevice* device, void* snapParam, unsigned char type);

//Gps�������÷���
bool sendGpsAlarm_comm(CDvrDevice* device,void* gpsParam);

//����������
bool sendHeartBeat_comm(CDvrDevice* device);

//���������
bool sendRequestPacket_comm(CDvrDevice* device, int type, int nSequence, int subtype, void *pCondition);

//��ѯ����״̬
bool sendQueryTransCom_comm(CDvrDevice* device, int nTransComType);

//�����÷���
bool sendNewConfigPacket_comm(CDvrDevice* device,int nSequence, void *pCondition);


#endif // _DVRPACKET_COMM_H_



