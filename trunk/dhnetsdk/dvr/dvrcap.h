///////////////////////////////////////////////////////////////////////////////////////////
// �ļ���: dvrcap.h
// ������: ����
// ����ʱ��: 
// ��������: dvr����
///////////////////////////////////////////////////////////////////////////////////////////
#ifndef DVRCAP_H
#define DVRCAP_H

//�õ���������˿ڸ���
int alarminputCount(int type, unsigned char *buf);

//�õ���������˿ڸ���
int alarmoutputCount(int type, unsigned char *buf);

//�õ�͸����������
bool transability(int type);

//�õ��Խ�����
bool talkability(int type);

//�õ��໭��Ԥ������
//bool previewability(int type);

#endif


