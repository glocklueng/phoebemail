#ifndef _DECODE_H
#define _DECODE_H

#include <windows.h>
#include "..\AccurateTimer.h"


#define  AUDIOBUFLEN (8192*2)

#define DEC_YUVDATA     1//������Ƶ����
#define DEC_PCMDATA    2//������Ƶ����

#define Reset_level_RAWYUV  0  //���ԭʼ����ͽ��뻺��
#define Reset_level_YUV           1  //��ս��뻺��
#define Reset_level_FASTRETURN 2 //ʹ������ٷ���
#define Reset_level_STREAMPASER 3 //���û�������������������½�������ʶ��

#define SM_File 0
#define SM_Stream_File 1
#define SM_Stream_Stream 2

#define SAFE_DELETE(x)				{if ((x)!=NULL) {delete (x); (x)=NULL;}} 
#define SAFE_DELETEBUFF(x)			{if((x)!=NULL) {delete [] (x); (x) = NULL;}}
#define SAFE_CLOSEHANDLE(x)			{if((x)!=NULL) {CloseHandle(x); (x) = NULL;}}


typedef enum
{
	Stream_No,
	Stream_NewStream,
	Stream_OldStream,
	Stream_ShStream,
	Stream_Standard,
	Stream_DHSTD
}STREAMDATA_TYPE ;

typedef int (__stdcall *dec_callback)(
        int index,				// ������
		unsigned char *data,	// ������
		unsigned int datalen,	// ���ݳ���
		int cbtype,				// �ص�����
		int param1,			// �ص��������������Ƶ����Ϊͼ����������Ƶ����Ϊ���ݿ��
		int param2//�ص��������������Ƶ����Ϊͼ��ߣ��������Ƶ����Ϊ������
);

struct DecodeOption
{
	int decId;			// ������ID��, ����һ��Ӧ�ó��������������ͨ��
	dec_callback cb;	// ע��ص�����
	int imgBufCount;	// ͼ�񻺳����
	int transMode;		// ����ģʽ. ��ý��ģʽ�����ļ�ģʽ. ��ý��ģʽ = 1,�ļ�ģʽ = 0
	int streamType;		// �����ͣ���ʱû�õ�
	bool ifDecOnly;    //�Ƿ�������룬��ͨ����ʱ���ص�����
	HWND hwnd;
	CAccurateTimer *pACTimerObj;
};

struct tagDemuxInfo {
	int type;			// VIDEO, AUDIO, DATA
	int subtype;		// I Frame, BP Frame, PCM8, MS-ADPCM etc.
	int encode;			// MPEG4, H264, STDH264
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
	int secode;
	unsigned long timestamp;

	int channels;
	int bitspersample;
	int samplespersecond;
};

typedef struct 
{
	unsigned long 		key;			// ˮӡkeyֵ �ɸ��ݲ�ͬ��keyֵ���ж�ˮӡ�����֣�
								// ͼƬ�������ˮӡ.
	unsigned short		len;			// ˮӡ����
	unsigned short		reserved;		// �����ֶ�
	unsigned short		reallen;		// ������ʵ��ˮӡ����
	char*				buf;			// ˮӡ���ݻ���
}WATERMARK_INFO;			// ˮӡ��Ϣ�ṹ


typedef int (__stdcall*watermark_callback)(char* buf, long key, long len, long reallen, long reserved, long nUser);	//ˮӡ��Ϣ��ȡ����


//���ܷ�����begin-----------------------
#define  MAX_IVSOBJ_NUM 200
#define  MAX_TRACKPOINT_NUM 10

typedef struct _DH_IVS_POINT
{
	short 		x; 
	short 		y; 
	short		xSize;
	short		ySize;
	//�켣����������Ӿ��ε����ģ�����X��Y��XSize��YSize�������������Ӿ������꣨left��top��right��bottom����
	//RECT=(X-XSize, Y-YSize, X+XSize, Y+YSize)
	
}DH_IVS_POINT; 

typedef struct _DH_IVS_OBJ
{
	int				decode_id;
	int				obj_id;
	int				enable;//0��ɾ��
	DH_IVS_POINT 	track_point[MAX_TRACKPOINT_NUM]; 
	int				trackpt_num;
}DH_IVS_OBJ;

typedef struct _DH_IVS_PREPOS
{
	BYTE* pIVSPreposInfo;
	long  lInfoSize;
} DH_IVS_PREPOS;

//
// IVS information callback function. This function returns preset position or motion tracks informations.
// parameters: buf			information data
//             type			information type. IVSINFOTYPE_PRESETPOS or IVSINFOTYPE_MOTINTRKS
//             len			IVS information single data object size
//             reallen		IVS information data object total size
//             reserved		only for motion tracks, 1 -- normal track    2 -- lost track
//             nUser		user data
//
typedef int (__stdcall*IVS_callback)(char* buf, long type, long len, long reallen, long reserved, long nUser);

//���ܷ�����end-----------------------


#endif