/*
* Copyright (c) 2009, �㽭���ܼ����ɷ����޹�˾
* All rights reserved.
*
* �����ƣ�Э��ջ
* ժ��Ҫ������������Э�����
*
*/
//////////////////////////////////////////////////////////////////////////

#ifndef _DVRPACKET_DVR_H_
#define _DVRPACKET_DVR_H_

#include "../kernel/afkinc.h"

class CDvrDevice;
class CDvrSearchChannel;


//ʵ�Ӽ���
bool sendMonitor_dvr2(CDvrDevice* device, int channel, int subtype, bool bstart, 
					  int nConnType, int nConnectID, char* szLocalIp, int nLocalPort);

//��ѯ¼��
bool sendQueryRecord_dvr2(CDvrDevice* device, 
                      afk_query_record_s queryrecord, int nParam);

//��ѯ��־
bool sendQueryLog_dvr2(CDvrDevice* device, int logtype, int nParam, char* szPacket = NULL, int nPacketLen = 0);

//����¼�񷵻�
void parseSearchRecordResult_dvr2(CDvrSearchChannel *ch,  
                             unsigned char *recordresult, unsigned int len, 
                             afk_record_file_info_s **p, int &filecount, bool bQueryEndTime, int nParam);

//����
bool sendDownload_dvr2(CDvrDevice* device, 
                  afk_record_file_info_s recordinfo, bool bstart, int nByTime, int nConnectID, DWORD dwParm = 0);

//���������ļ�
bool sendExportCfgFile_dvr2(CDvrDevice* device, bool bStart, int nParam = 0);

//���������ļ�
bool sendImportCfgFile_dvr2(CDvrDevice* device, afk_upgrade_channel_param_s *ucparam);

int sendImportCfgData_dvr2(CDvrDevice* device, int packetId, char *buf, int len, afk_upgrade_channel_param_s *ucparam);


//���ؿ���
bool sendDownload_control_dvr2(CDvrDevice* device, int channel,
                               int offset_time, int offset_data, int nConnectID);

//���ؼ�������ͣ
bool sendDownLoad_pause_dvr2(CDvrDevice* device, unsigned int ch, bool pause, int nConnectID);

//����������ʼ����
//upgraeflag  1:bois  2:web  3:boot
//Edited by Linjy-2006-11-2
bool sendUpgradeControl_dvr2(CDvrDevice* device, afk_upgrade_channel_param_s *ucparam/*, bool bstart*/);

//����������Ϣ
int sendUpgradeData_dvr2(CDvrDevice* device, int packetId, char *buf, int len, afk_upgrade_channel_param_s *ucparam);

//����Ԥ����Ϣ
bool sendPreview_dvr2(CDvrDevice* device, int type1, int type2, bool bstart, 
					  int nConnType, int nConnectID, char* szLocalIp, int nLocalPort);

//���󱨾���Ϣ
bool sendAlarmQuery_dvr2(CDvrDevice* device, bool bRecordState, int proType);

//���Ϳ�����Ϣ
bool sendControl_dvr2(CDvrDevice* device, 
                     int ch, int type1, int type2, int parm1, int parm2, int parm3, char *pParam4 = NULL);

//���Ϳ��ƿ�¼��Ϣ
bool SendControlForBurning(CDvrDevice *pDevice, int nParam1, char *pParam2);

//���ݼ���
void Encrypt(void *pdata, int len);

//��ѯͨ����
bool sendQueryChannelName_dvr2(CDvrDevice* device);

//��ѯ��������������
bool sendQueryAlarmInput_dvr2(CDvrDevice* device);

//��ѯ�������������
bool sendQueryAlarmOutput_dvr2(CDvrDevice* device);

//��ѯ���߱������
bool sendQueryWirelessAlarmOutput_dvr2(CDvrDevice* device);

//��ѯ����������ʽ
bool sendQueryAlarmTrrigerMode_dvr2(CDvrDevice* device);

//���ñ���������ʽ
bool sendSetingAlarmTrrigerMode_dvr2(CDvrDevice* device, afk_alarm_trriger_mode_s trrigerinfo);

//��������������
void parseSearchAlarmResult_dvr2(CDvrDevice* device, 
                          unsigned char *alarmresult, unsigned int len,
                          afk_alarm_info_s **p);

//���ñ���������
bool sendSettingAlarm_dvr2(CDvrDevice* device, afk_alarm_control_info_s alarminfo);

//���ñ������������
bool sendSetingDecoderAlarm_dvr2(CDvrDevice* device, afk_decoder_alarm_info_s dainfo);

//����͸������
bool sendSettingSerial_dvr2(CDvrDevice* device, afk_trans_channel_param_s transinfo, bool bstart=true);

//����͸��������Ϣ
bool sendTransSerialData_dvr2(CDvrDevice* device, int transtype, char *buffer, int buflen);

//���ͶԽ�Ҫ��
bool sendTalkRequest_dvr2(CDvrDevice* device, int channel, bool bstart, int encodetype);

//���ͶԽ���Ϣ
bool sendTalkData_dvr2(CDvrDevice* device, int channel, char *buffer, int buflen, int encodetype);

//��ѯ����
bool sendQueryConfig_dvr2(CDvrDevice* device, unsigned short configtype, int param);

//��������
bool sendSetupConfig_dvr2(CDvrDevice* device, unsigned short configtype, int param,
                         unsigned char *buffer, int buflen);

//����¼��״̬
bool sendSetupRecordState_dvr2(CDvrDevice* device, unsigned char *buffer, int buflen);

//��ѯ�豸ʱ��
bool sendQueryDeviceTime_dvr2(CDvrDevice* device);

//�����豸ʱ��
bool sendSetupDeviceTime_dvr2(CDvrDevice* device, int year, int month, int day,
                              int hour, int minute, int second);

//��ѯЭ��(����Э���������Э��)
bool sendQueryProtocol_dvr2(CDvrDevice* device, int protocoltype,DWORD dwProtocolIndex =0);

//��ѯϵͳ��Ϣ
bool sendQuerySystemInfo_dvr2(CDvrDevice* device, int type, int param);

//�����û�����
bool sendUserOperate_dvr2(CDvrDevice* device, int type, char *buffer, int bufferlen);

//ǿ��I��
bool sendForceIframe_dvr2(CDvrDevice* device,  unsigned char mainchn, unsigned char subchn);

//������������
bool sendLimitFlux_dvr2(CDvrDevice* device, unsigned short limitflux);

//��ѯ�豸����״̬
bool sendQuerydevstate_dvr2( CDvrDevice* device, unsigned char chn, unsigned char type);

//��ѯ�豸������״̬
bool sendQueryAlarmState_dvr2(CDvrDevice* device, int statetype,int deviceid = 0);

//�����緢������
int sendcammand_dvr2(CDvrDevice* device, void *data, int datalen);

//Զ��ץͼ
bool sendCapture_dvr2(CDvrDevice* device, int channel, int pipeno, bool bstart);

//���û���OSD����
bool sendSetupChannelOsdString_dvr2(CDvrDevice* device, int channelno, int enable, int* position, unsigned char *buf, int buflen);

//����������
bool sendHeartBeat_dvr2(CDvrDevice* device);

//���������
bool sendRequestPacket_dvr2(CDvrDevice* device, int type, int nSequence, int subtype, void *pCondition);

//���Ͳ�ѯ���ڲ�����
bool sendQueryTransCom_dvr2(CDvrDevice* device, int nTransComType);

//�����÷���
int sendNewConfigPacket_dvr2(CDvrDevice* device,int nSequence, void *pCondition);


#endif // _DVRPACKET_DVR_H_

