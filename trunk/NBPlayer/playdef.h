#ifndef PLAYDEF_H
#define PLAYDEF_H


/************************************************************************
 * ֡����
 ************************************************************************/
#define DEC_DEMUX_TYPE_VIDEO_FRAME	1 // ��Ƶ֡
#define DEC_DEMUX_TYPE_AUDIO_FRAME	2 // ��Ƶ֡
#define DEC_DEMUX_TYPE_DATA_FRAME	3 // �Զ�������֡

// ��Ƶ֡������
#define DEC_VIDEO_I_FRAME		1 // �ؼ�֡
#define DEC_VIDEO_P_FRAME		2
#define DEC_VIDEO_B_FRAME		3

// ��������
#define DEC_ENCODE_MPEG4	1		// MPEG4����
#define DEC_ENCODE_H264		2		// ��H264����
#define DEC_ENCODE_H264_ADI	3		// ADI H264����
#define DEC_ENCODE_H264_STD	4		// ��׼H264����

/************************************************************************
 * ���ݲ�ֽ�����صĽṹ��, ����֡��ʹ�øýṹ,��
 * ��֡����Ϣ��ʱ����Ϣ������I֡��Ч
 * ͼ���С��������Ƶ��Ч
 * ���к�Ŀǰû��ʹ�� 
 ************************************************************************/
struct tagDemuxInfo {
	int type;			// ��֡���ͺ궨��
	int subtype;		// ����Ƶ֡�����ͺ궨��
	int encode;			// ���������ͺ궨��
	int sequence;		// I֡�����������
	
	// ͼ���С��Ϣ
	int width;
	int height;
	
	// ֡����Ϣ
	int rate;
	
	// time information
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
	unsigned long timestamp;
	
	int bitspersample;
	int samplespersecond;
};

#define PLAY_CMD_GetTime 1

struct TimeInfo
{
	int year;
	int month;
	int day;
	int hour;
	int minute;
	int second;
};

#endif /*DHDEC_H*/

