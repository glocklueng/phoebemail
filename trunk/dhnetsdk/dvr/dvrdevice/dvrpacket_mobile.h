///////////////////////////////////////////////////////////////////////////////////////////
// �ļ���: dvrpacket_mobile.h
// ������: jinyx
// ����ʱ��: 2007-4-2
// ��������: mobile dvr��packet
///////////////////////////////////////////////////////////////////////////////////////////

#ifndef DVRPACKETMOBILE_H
#define DVRPACKETMOBILE_H

class CDvrDevice;

//ץͼ
bool sendSnap_mobile(CDvrDevice* device, void* snapParam, unsigned char type);

//gps����
bool sendGpsAlarm_mobile(CDvrDevice* device, void* gpsParam);

#endif

