///////////////////////////////////////////////////////////////////////////////////////////
// �ļ���:		dvr2cfg.h
// ������:		�Ծ���
// ����ʱ��:	2006/09/18
// ��������:	����dvr�豸������Ϣ�ṹ
///////////////////////////////////////////////////////////////////////////////////////////    

#ifndef _DVR2CFG_H_
#define _DVR2CFG_H_

#include "../osIndependent.h"

#define N_SYS_CH 16
#define MAX_AUTHORITY_NUM 80


typedef enum tagProductType
{
	DVR_PRODUCT_H = 0,		//�Ӻ�
	DVR_PRODUCT_G,			//��ͨ
	DVR_PRODUCT_L,			//����
	DVR_PRODUCT_N,			//��ʵʱ
	DVR_PRODUCT_ATM,			//ATM
	NVS_PRODUCT_S,			//������Ƶ������
	NVS_PRODUCT_E,			//NVS 0404E
	DVR_PRODUCT_NB,			//������ʵʱNB
	DVR_PRODUCT_LN,			//LN ϵ��
	DVR_PRODUCT_BAV,			//BAV ϵ��
	NVS_PRODUCT_B = 10,		//NVS_B
	NVS_PRODUCT_C,			//NVS_H
	NVD_PRODUCT_SERIAL = 12,	//������
	
	SDIP_PRODUCT = 50,		//���
	IPC_PRODUCT,				//ipc
	IPC_PRODUCT_400 = 55,	//ipc4000
	IPC_PRODUCT_A6=60,		//A6
	N5_PRODUCT,				//N5
	MIX_DVR_PRODUCT,			//���dvr
	SVR_PRODUCT,				//SVR
	NVR_PRODUCT = 65,		//NVR
	DEV_NORMAL_TYPE_PRODUCT=255		//�豸����
} PRODUCTTYPE;

typedef enum _config_type_t
{
	CONFIG_TYPE_GENERAL = 0,	/*��ͨ����*/
	CONFIG_TYPE_SERIAL_COMM,	/*��������*/
	CONFIG_TYPE_NET,			/*��������*/
	CONFIG_TYPE_RECORD,			/*��ʱ¼������*/
	CONFIG_TYPE_CAPTURE,		/*ͼ������*/
	CONFIG_TYPE_PTZ,			/*��̨����*/
	CONFIG_TYPE_DETECT,			/*ͼ��������*/
	CONFIG_TYPE_ALARM,			/*��������*/
	CONFIG_TYPE_DISPLAY,		/*ͼ����ʾ����*/
								/*9 - /NULL*/
	CONFIG_TYPE_TITLE = 10,		/*ͨ�����ƣ��豸2.4�汾����֧��*/
	CONFIG_TYPE_MAIL,			/*�ʼ�����*/
	CONFIG_TYPE_PREVIEW,		/*Ԥ������*/
	CONFIG_TYPE_PPPOE,			/*PPPoE����*/
	CONFIG_TYPE_DDNS,			/*DDNS����*/
	CONFIG_TYPE_SNIFFER,		/*����ץ������*/
	CONFIG_TYPE_DSPCAP,			/*����������Ϣ*/
//	CONFIG_TYPE_FTP,			/*FTP����*/
	CONFIG_TYPE_AUTO_MT = 18,	/*�Զ�ά������*/
	CONFIG_TYPE_NTP,			/*NTP����*/
	CONFIG_TYPE_LIMIT_BR,		/*����������*/
	
	CONFIG_TYPE_WATERMAKE = 29,		/*ͼ��ˮӡ����*/
	CONFIG_TYPE_VIDEO_MATRIX = 30,	/*���ؾ����������*/
	CONFIG_TYPE_COVER = 34,			/*��Ƶ�����ڵ�*/
	CONFIG_TYPE_DHCP = 35,			/*DHCP����*/
	CONFIG_TYPE_WEB_URL = 36,		/*ץͼ����web·������*/
	CONFIG_TYPE_FTP_PRO = 37,		/*FTP����*/
	CONFIG_TYPE_CAMERA = 38,		/*����ͷ��������*/
	CONFIG_TYPE_ETHERNET = 39,		/*��������*/
	CONFIG_TYPE_DNS = 40,			/*DNS����������*/
	CONFIG_TYPE_STORSTATION = 41,   //�洢λ��
	CONFIG_TYPE_DOWNLOAD_STRATEGY = 42,	//��Ƶ����
	CONFIG_TYPE_VIDEO_OSD = 44,			//��ƵOSD��������

	CONFIG_TYPE_ALARM_CENTER_UP	= 120,  //���������ϴ����á�
	CONFIG_TYPE_RECORD_NEW	= 123,		//��¼������
	CONFIG_TYPE_TIMESHEET = 125,		//��ȡ������
	CONFIG_TYPE_COLOR = 126,			// ��ɫ����
	CONFIG_TYPE_CAPTURE_127	= 127,		//˫����ͼ������
	CONFIG_TYPE_CAPTURE_128 = 128,		//�µı�������
	CONFIG_TYPE_AUDIO_CAPTURE = 129,	//��Ƶ����
	CONFIG_TYPE_WLAN = 131,				//��ѯ��������
	CONFIG_TYPE_TRANSFER_STRATEGY = 133,//���紫���������
	CONFIG_TYPE_WIRELESS_ADDR = 134,    //���߱�������,��Ҫ�������ַ��ң������ַ
	CONFIG_TYPE_WLAN_DEVICE = 135,		//���������豸
	CONFIG_TYPE_MULTI_DDNS = 140,		//��DDNS����������
	CONFIG_TYPE_INTERVIDEO = 190,		//ƽ̨��������
	CONFIG_TYPE_OEM_INFO = 200,			//������������Ϣ
	CONFIG_TYPE_DSP_MASK = 210,
	CONFIG_TYPE_AUTO_REGISTER = 241,	// ����ע���������
	CONFIG_TYPE_POS ,					//����POS���� jfchen

	CONFIG_TYPE_ALARM_BEGIN,
	CONFIG_TYPE_ALARM_LOCALALM,
	CONFIG_TYPE_ALARM_NETALM,
	CONFIG_TYPE_ALARM_DECODER,
	CONFIG_TYPE_ALARM_MOTION,
	CONFIG_TYPE_ALARM_BLIND,
	CONFIG_TYPE_ALARM_LOSS,
	CONFIG_TYPE_ALARM_NODISK,
	CONFIG_TYPE_ALARM_DISKERR,
	CONFIG_TYPE_ALARM_DISKFULL,
	CONFIG_TYPE_ALARM_NETBROKEN,
	CONFIG_TYPE_ALARM_ENCODER,
	CONFIG_TYPE_ALARM_WIRELESS,
	CONFIG_TYPE_ALARM_AUDIODETECT,
	CONFIG_TYPE_ALARM_DISKNUM,
	CONFIG_TYPE_ALARM_PANORAMA,
	CONFIG_TYPE_ALARM_LOSTFOCUS,
	CONFIG_TYPE_ALARM_IPCOLLISION,
	CONFIG_TYPE_ALARM_END,

}CONFIG_TYPES;

/*
typedef enum _config_alarm_type_t
{
	CONFIG_ALARM_BEGIN		= 50,
	CONFIG_ALARM_LOCALALM	,
	CONFIG_ALARM_NETALM		,
	CONFIG_ALARM_DECODER		,
	CONFIG_ALARM_MOTION		,
	CONFIG_ALARM_BLIND		,
	CONFIG_ALARM_LOSS		,
	CONFIG_ALARM_NODISK		,
	CONFIG_ALARM_DISKERR		,
	CONFIG_ALARM_DISKFULL	,
	CONFIG_ALARM_NETBROKEN	,
	CONFIG_ALARM_END			,
} CONFIG_ALARM_TYPE;
*/
typedef enum _config_wsheet_typt_t
{
	WSHEET_RECORD = 1,
	WSHEET_LOCAL_ALARM = 2,
	WSHEET_NET_ALARM = 3,
	WSHEET_MOTION = 4,
	WSHEET_BLIND = 5,
	WSHEET_LOSS = 6,
	WSHEET_NO_DISK = 7,
	WSHEET_DISK_ERROR = 8,
	WSHEET_DISK_FULL = 9,
	WSHEET_NET_BROKEN = 10,
	WSHEET_DECODER_ALARM = 11,
    WSHEET_WIRELESS_ALARM = 13,
	WSHEET_PANORAMA_SWITCH = 14,
	WSHEET_LOST_FOCUS = 15,
} CONFIG_WSHEET_TYPE;

typedef enum _system_info_type_t
{
	SYSTEM_INFO_GENERAL = 0,		/* ��ͨ��Ϣ */
	SYSTEM_INFO_DEV_ATTR,			/* �豸������Ϣ */
	SYSTEM_INFO_DISK_DRIVER,		/* Ӳ����Ϣ */
	SYSTEM_INFO_FILE_SYSTEM,		/* �ļ�ϵͳ��Ϣ */
	SYSTEM_INFO_VIDEO_ATTR,			/* ��Ƶ���� */
	SYSTEM_INFO_CHARACTER_SET,		/* �ַ�����Ϣ */
	SYSTEM_INFO_OPTICS_STORAGE,		/* ��洢�豸��Ϣ */
	SYSTEM_INFO_DEV_ID,				/* �豸���к�(ID) */
	SYSTEM_INFO_DEV_VER,			/* �豸�汾���ַ�����ʽ */
	SYSTEM_INFO_LOGIN_ATTR,         /* ��½����*/
	SYSTEM_INFO_TALK_ATTR = 10,		/* �����Խ����� */
	SYSTEM_INFO_DEV_TYPE = 11,		/* �豸���� */
	SYSTEM_INFO_PLATFORM = 12,		/* ��ѯ�豸����Э��(ƽ̨����)֧����Ϣ */
	SYSTEM_INFO_SD_CARD = 13,		/* SD����Ϣ */   
	SYSTEM_INFO_MOTIONDETECT = 14,	/* �豸��Ƶ��̬���������Ϣ */
	SYSTEM_INFO_VIDEOBLIND = 15,	/* ��Ƶ�����ڵ�������Ϣ */
	SYSTEM_INFO_CAMERA = 16,		/* ����ͷ������Ϣ */
	SYSTEM_INFO_WATERMARK = 17,		/* ��ѯͼ��ˮӡ���� */
	SYSTEM_INFO_WIRELESS = 18,		/* ��ѯWireless���� */
    SYSTEM_INFO_Language = 20,		/* ��ѯ֧�ֵ������б� */
	SYSTEM_INFO_PICTURE = 25,		/* �Ƿ�֧���µ�¼��ͼƬ�б��ѯ��ʽ */
	SYSTEM_INFO_DEV_ALL = 26,		/* �豸�����б� */
	SYSTEM_INFO_INFRARED = 27,		/* ��ѯ���߱������� */
	SYSTEM_INFO_NEWLOGTYPE = 28,	/* �Ƿ�֧���µ���־��ʽ */
	SYSTEM_INFO_OEM_INFO = 29,		/* OEM��Ϣ */
	SYSTEM_INFO_NET_STATE=30,		/* ����״̬ */
	SYSTEM_INFO_DEV_SNAP =31,		/* �豸ץͼ����������ѯ */
	SYSTEM_INFO_VIDEO_CAPTURE = 32,	/* ��Ƶǰ�˲ɼ�������ѯ */
	SYSTEM_INFO_DISK_SUBAREA = 33,  /* Ӳ�̷���������ѯ*/
} SYSTEM_INFO_TYPES;

typedef enum __device_event_type
{
	EVENT_CONFIG_REBOOT = 0,
	EVENT_CONFIG_ACK,
	EVENT_TALK_START,
	EVENT_TALK_STOP,
	EVENT_CONFIG_CHANGE,
	EVENT_NVD_PLAYBACK,
	EVENT_DEVICE_DEAL,
} DEVICE_EVENT_TYPE;

typedef struct
{
    long    left;
    long    top;
    long    right;
    long    bottom;
} COVER_RECT;

typedef struct ywtime					        /*ʱ��				*/
{
	unsigned int second		:6;				    /*	��	1-60		*/
	unsigned int minute		:6;				    /*	��	1-60		*/
	unsigned int hour		:5;				    /*	ʱ	1-24		*/
	unsigned int day		:5;				    /*	��	1-31		*/
	unsigned int month		:4;				    /*	��	1-12		*/
	unsigned int year		:6;				    /*	��	2001-2064	*/
}FRAME_TIME;

typedef struct
{
	unsigned char	CapVersion[8];  //�汾��
	unsigned char	CifMode;		//�ֱ���
	unsigned char	VideoType;		//����ģʽ��
	unsigned char	EncodeMode;		//��������
	unsigned char	ImgQlty;		//�����Ļ���
	unsigned char	Frames;			//֡��
	unsigned char	Brightness;		//����
	unsigned char	Contrast;		//�Աȶ�
	unsigned char	Saturation;		//���Ͷ�
	unsigned char	Hue;			//ɫ��
	unsigned char	AudioEn;		//��Ƶʹ��
	unsigned char	Gain;			//����
	unsigned char    CoverEnable;	//�����ڸ�ʹ��
	COVER_RECT	Cover;			//�����ڸ�
}CONFIG_CAPTURE;

#define N_COLOR_SECTION 2
#define N_ENCODE_AUX_INTER 3

char * const CAPTURE_VERSION = "0603";
char * const COLOR_VERSION = "0101";

enum rec_type_inter
{
	REC_TYP_TIM_INTER = 0,		/*��ʱ¼��*/
	REC_TYP_MTD_INTER,					
	REC_TYP_ALM_INTER,
	REC_TYP_NUM_INTER,
};

enum enc_cover_type
{
	ENC_COVER_NONE = 0,
	ENC_COVER_PREVIEW = 0x1,
	ENC_COVER_MONITOR = 0x2,
	ENC_COVER_NUM = 0x3
};

enum enc_snap_type
{
	SNAP_TYP_TIM_INTER = 0,
	SNAP_TYP_ALARM_INTER,
	SNAP_TYP_NUM_INTER,
};

//! ����ѡ��
typedef struct  
{
	BYTE	ImageSize;			/*!< �ֱ��� ����ö��capture_size_t(DVRAPI.H) */
	BYTE	BitRateControl;		/*!< �������� ����ö��capture_brc_t(DVRAPI.H) */
	BYTE	ImgQlty;			/*!< �����Ļ��� ����1-6		*/
	BYTE	Frames;				/*!< ֡�ʡ�����N��1-6,P��1-5 */	
	BYTE	AVEnable;			/*!< ����Ƶʹ�� 1λΪ��Ƶ��2λΪ��Ƶ��ONΪ�򿪣�OFFΪ�ر� */
	BYTE	IFrameInterval;		/*!< I֡���֡��������������I֮֡���P֡��������Ч��Χ0-149����֧��Ϊ255 */
	WORD	usBitRate;			/*!< DSP�޶��������� */
}ENCODE_OPTION;

//! ����ṹ
typedef struct  
{
	DWORD	TitlefgRGBA;			/*!< �����ǰ��RGB����͸���� */
	DWORD	TitlebgRGBA;		/*!< ����ĺ�RGB����͸����*/
	WORD	TitleLeft;			/*!< �������ߵľ����������ı���*8192 */
	WORD	TitleTop;			/*!< ������ϱߵľ����������ı���*8192 */
	WORD	TitleRight;			/*!< ������ұߵľ����������ı���*8192 */
	WORD	TitleBottom;			/*!< ������±ߵľ����������ı���*8192 */
	BYTE	TitleEnable;			/*!< ����ʹ�� */
	BYTE	Reserved[3];
}ENCODE_TITLE;

//! ������Ϣ�ṹ
typedef struct {
	BYTE				CapVersion[8];				/*!< �汾��			*/		
	ENCODE_OPTION		MainOption[REC_TYP_NUM_INTER];	/*!< ��������REC_TYP_NUM��ͬ¼������*/
	ENCODE_OPTION		AssiOption[N_ENCODE_AUX_INTER];	/*!< ֧��3 ·������ */
	BYTE				Compression;				/*!< ѹ��ģʽ */;	
	BYTE    			CoverEnable;				/*!< �����ڸǿ��ء�0x00��ʹ���ڸǣ�0x01���ڸ�Ԥ����0x10���ڸ�¼��0x11���ڸ�	*/
	BYTE 				alignres[2];			/*!< ���������� */
	RECT				Cover;						/*!< �����ڸǷ�Χ	*/	
	
	ENCODE_TITLE 		TimeTitle;					/*!< ʱ�����*/
	ENCODE_TITLE 		ChannelTitle;				/*!< ͨ������*/
	
	ENCODE_OPTION		SnapOption[SNAP_TYP_NUM_INTER]; /*!< 2�� ץͼ���� */   
	short				PicTimeInterval;			/*!<�Զ���ץͼʱ��������λΪs*/ 

	//delete by cqs ֮ǰ��ʱҪ�������ڲ��ԣ��������ε�ת�Ƶ�����ͷ�����Ǳ�
//	BYTE				MainScanMode[REC_TYP_NUM_INTER];	//ɨ��ģʽ ����������Ӧ	0-����ɨ�裬1-����ɨ��
//	BYTE				AssiScanMode[N_ENCODE_AUX_INTER] ;	//ɨ��ģʽ �븨������Ӧ 0-����ɨ�裬1-����ɨ��

	BYTE	Volume;								/* ���������ķ�ֵ */
	BYTE	VolumeEnable;						/* ������ֵʹ�� */									   
	BYTE	Noise;								/* �����ķ�ֵ */
	BYTE	Reserved[43];  /*!< ������ */
} NEW_CONFIG_CAPTURE;

//! �����ڵ����ýṹ��
typedef struct __video_cover_t
{
	BYTE				iChannel;		// ͨ���ţ�[1~n]
	BYTE				iCoverNum;		// ���ǵ��������
	char				reserved[30];	// ����
}CONFIG_VIDEO_COVER_T;

typedef struct __video_cover_attr_t
{
	COVER_RECT				rcBlock;		// ���ǵ���������
	int					Color;			// ���ǵ���ɫ
	BYTE				iBlockType;		// ���Ƿ�ʽ��0-�ڿ飬1-������
	BYTE				Encode;			// ���뼶�ڵ�, 1����Ч, 0��������
	BYTE				Priview;		// Ԥ���ڵ�, 1����Ч, 0������Ч
	BYTE				reserved[28];	// ����
}CONFIG_VIDEO_COVER_ATTR;

//! ��ѯ�豸��Ƶ��̬���������Ϣ
typedef struct __MOTION_DETECT_CAPS
{
	DWORD				Enabled;		// ��1��ʾ֧�ֶ�̬��⣬��0��ʾ��֧�ֶ�̬���
	DWORD				GridLines;		// ��̬����������Ҫ���ֳɵ�����
	DWORD				GridRows;		// ��̬����������Ҫ���ֳɵ�����
	BYTE				Result;			// �Ƿ��ܵõ�ÿ������ļ����
	BYTE				Hint;			// �Ƿ����ڼ��ɹ�ʱ������ʾ
}MOTION_DETECT_CAPS;

//! ��ѯ��Ƶ�����ڵ�������Ϣ
typedef struct __video_cover_caps_t
{
	unsigned char		iEnabled;		// ��1��ʾ֧�� �����ڵ���0 ��֧��
	unsigned char		iBlockNum;		// ֧�ֵ��ڵ�����
	unsigned char		iRev[62];		// ��̬����������Ҫ���ֳɵ�������
}VIDEO_COVER_CAPS_T;

//!����������Ϣ
typedef struct 
{
	int					nEnable;		// ����ʹ��
	char				szSSID[36];		// SSID
	int					nLinkMode;		// ����ģʽ 0:auto 1:adhoc 2:Infrastructure
	int					nEncryption;	// ���� 0: off 2:WEP64bit 3: WEP128bit 4:WPA-PSK-TKIP, 5: WPA-PSK-CCMP
	int					nKeyType;		// 0:Hex 1:ASCII
    int					nKeyID;			// ���
	char				szKeys[128];	// ����
	int					nKeyFlag;
	int					nReserved[3];
} CONFIG_WLAN_INFO;

//!���������豸��Ϣ
typedef struct  
{
	char				szSSID[36];
	int					nLinkMode;			// ����ģʽ 0:adhoc 1:Infrastructure
	int 				nEncryption;		// ���� 0: off  2:WEP64bit 3: WEP128bit
} CONFIG_WLAN_DEVICE;

//!����ͷ����
typedef struct 
{
	BYTE				bExposure;		// �ع�ģʽ 1-9:�ֶ��ع�ȼ�; 0:�Զ��ع�
	BYTE				bBacklight;		// ���ⲹ�� 3:ǿ��2���У�1������ 0:��
	BYTE				bAutoColor2BW;	// ��/ҹģʽ 2:����1���Զ�; 0:��
	BYTE				bMirror;		// ����  1 ���� 0��
	BYTE				bFlip;			// ��ת  1 ���� 0��
	BYTE				bLensFunction;	// ��4λ��ʾ������������4λ��ʾ���ܿ���
										// bit4 = 1:֧���Զ���Ȧ���ܣ�
										// bit0 = 0:�ر��Զ���Ȧ��bit0 = 1:�����Զ���Ȧ��
	BYTE				bWhiteBalance;  //��ƽ�� 0:Disabled,1:Auto 2:sunny 3:cloudy 4:home 5:office 6:night 
	BYTE                bSignalFormat;  //�źŸ�ʽ0-Inside(�ڲ�����) 1- BT656 2-720p 3-1080i  4-1080p  5-1080sF
	float				ExposureValue1; //�Զ��ع�ʱ�����޻����ֶ��ع��Զ���ʱ��,����Ϊ��λ��ȡֵ0.1ms~80ms
	float				ExposureValue2;	//�Զ��ع�ʱ������,����Ϊ��λ��ȡֵ0.1ms~80ms
	BYTE				bRotate90;		//0-����ת��1-˳ʱ��90�㣬2-��ʱ��90��
	char				bRev[111];		// ����
} CONFIG_CAMERA_T;

//!��������Ϣ
typedef struct  
{
	char				szEthernetName[64];
	char				szIp[32];
	char				szMask[32];
	char				szGateway[32];
} CONFIG_MULTI_ETHERNET;

//!Ĭ������
typedef struct  
{
	char				szEthernetName[64];
	int					nTranMedia;	//0������ 1������
	int					nValid;	//0����Ч 1����Ч
} CONFIG_DEFAULT_ETHERNET;

//!��Ƶ��ʽ��صĲ�������
typedef enum EnAudioBit
{
    EN_AUDIO_BIT_8  = 0,      //8bit
    EN_AUDIO_BIT_16  ,    //16bit
};
typedef enum EnAudioSamples
{
    EN_AUDIO_SAMPLE_8  = 0,    //8K
    EN_AUDIO_SAMPLE_16  ,  //16K
};
typedef enum EnAudioEncodeFmt
{
    EN_AUDIO_PCM = 0,
    EN_AUDIO_ADPCM  ,   
};

//!��Ƶ�ı���ṹ(������Ƶͨ���󶨵�)
typedef struct _audio_capture_cfg
{
	WORD 	nChannels;				//������  
    WORD 	wFormatTag;				//��������
	DWORD	dwBitsPerSample;			//�������
	DWORD	nSamplesPerSec;			//������  
	DWORD   Reserved[8];
}AUDIO_CAPTURE_CFG;

//ʹ��Э���е�0xa3��128��������Ľṹ��
typedef struct {
	BYTE	CapVersion[8];		/*!< �汾��			*/		
	BYTE	CifMode;			/*!< �ֱ��� ����ö��capture_size_t(DVRAPI.H) */
	BYTE	VideoType;			/*!< ����ģʽ ����ö��capture_comp_t(DVRAPI.H) */
	BYTE	EncodeMode;			/*!< �������� ����ö��capture_brc_t(DVRAPI.H) */
	BYTE	ImgQlty;			/*!< �����Ļ��� ����1-6		*/
	BYTE	Frames;				/*!< ֡�ʡ�����N��1-6,P��1-5 */	
	BYTE	Brightness;			/*!< ����	0-100		*/
	BYTE	Contrast;			/*!< �Աȶ�	0-100		*/
	BYTE	Saturation;			/*!< ���Ͷ�	0-100		*/
	BYTE	Hue;				/*!< ɫ��	0-100		*/
	BYTE	AudioEn;			/*!< ��Ƶʹ�� ONΪ�򿪣�OFFΪ�ر�	*/
	BYTE	Gain;				/*!< ����	0-100		*/
	BYTE    CoverEnable;		/*!< �����ڸǿ��ء�ONΪ�򿪣�OFFΪ�ر�	*/
	COVER_RECT	Cover;				/*!< �����ڸǷ�Χ	*/	

	BYTE	TimeTilteEn;		/*!< ʱ�����ʹ��  ONΪ�򿪣�OFFΪ�ر� */
	BYTE	ChTitleEn;			/*!< ͨ������ʹ��  ONΪ�򿪣�OFFΪ�ر� */
	
	BYTE	ExtFunction;		/*!< ��չ����֧�֣���Ҫ����˫���� */
	BYTE	VideoEn;			/*!< ��Ƶ������*/
	WORD	TimeTitleL;			/*!< ʱ��������ߵľ����������ı���*8192 */
	WORD	TimeTitleT;			/*!< ʱ�������ϱߵľ����������ı���*8192 */
	WORD	TimeTitleR;			/*!< ʱ�������ұߵľ����������ı���*8192 */
	WORD	TimeTitleB;			/*!< ʱ�������±ߵľ����������ı���*8192 */
	WORD	ChannelTitleL;		/*!< ͨ���������ߵľ����������ı���*8192 */
	WORD	ChannelTitleT;		/*!< ͨ��������ϱߵľ����������ı���*8192 */
	WORD	ChannelTitleR;		/*!< ͨ��������ұߵľ����������ı���*8192 */
	WORD	ChannelTitleB;		/*!< ͨ��������±ߵľ����������ı���*8192 */
	BYTE	Reserved[64];		/*!< �����ã������㣬ʡ���Ժ�ͣ�ظĽṹ֪ͨ�ͻ��� */
} CONFIG_CAPTURE_V2201;

typedef struct {    // ��ʱʱ�� 
    unsigned char    StartHour; // ��ʼʱ�� 
    unsigned char    StartMin; 
    unsigned char    StartSec; 
    unsigned char    HourEnd;   // ����ʱ�� 
    unsigned char    EndMin; 
    unsigned char    EndSec; 
    unsigned char    State; // �ڶ�λ�Ƕ�ʱ������λ�Ƕ�̬��⣬����λ�Ǳ��� 
    unsigned char    Reserve; // Reserve�Ѿ���ʹ�ã����ĵĻ���֪ͨ¼��ģ��
} TSECT;

//! ��ɫ��������
typedef struct 
{
	TSECT 	Sector;				/*!< ��Ӧ��ʱ���*/
	BYTE	Brightness;			/*!< ����	0-100		*/
	BYTE	Contrast;			/*!< �Աȶ�	0-100		*/
	BYTE	Saturation;			/*!< ���Ͷ�	0-100		*/
	BYTE	Hue;				/*!< ɫ��	0-100		*/
	BYTE	Gain;				/*!< ����	0-100		*/
	BYTE	Reserve[3];
} COLOR_PARAM;

//! ��ɫ�ṹ
typedef struct  
{
	BYTE ColorVersion[8];	
	COLOR_PARAM Color[N_COLOR_SECTION];
} CONFIG_COLOR;

#define N_WEEKS         7 
#define N_TSECT         6 

typedef struct { 
    unsigned char    RecVersion[8];               /*!< �汾�� */ 
    TSECT   Sector[N_WEEKS][N_TSECT];    /*!< ��ʱʱ�Σ�һ���������죬ÿ�� N_TSECTʱ��� */ 
    unsigned char    PreRecord;                   /*!< Ԥ¼����, 0-�ر�, 1-�� */ 
    unsigned char    Redundancy;                  /*!< ���࿪�أ�0-��Ч, 1-��Ч */ 
    unsigned char    Reserved[2];                 /*!< ���� */ 
} CONFIG_RECORD; 


typedef struct tagPTZ_ATTR
{
    unsigned long baudrate; // ����ֵ�ο���������
    unsigned char databits;
    unsigned char parity;
    unsigned char stopbits;
}PTZ_ATTR;

typedef struct
{
    unsigned char Ptz_Version[8];    /*!< �汾�� */
    PTZ_ATTR PTZAttr;       /*!< �������� */
    unsigned short DestAddr;          /*!< Ŀ�ĵ�ַ 0-255 */
    unsigned short Protocol;          /*!< Э������ ����Э����±꣬��̬�仯 */
    unsigned short MonitorAddr;       /*!< ��������ַ 0-64 */
	BYTE    CamID;					/*!����ͷID  */
	BYTE 	byMartixID;				/* �����*/
	BYTE	bPTZType;               /*!<0-���ݣ�������̨ 1-Զ��������̨>*/
    BYTE    Reserved[7];			/*! <  ����  */
} CONFIG_PTZ;

typedef struct { 
	unsigned char   Com_Version[8];       /*!< �汾�� */ 
	unsigned char    Function;           /*!< ���ڹ��� 0-��ͨ, 1-���Ƽ���, 2-͸������, 3-ATM��*/ 
	unsigned char    DataBits;           /*!< ����λ ȡֵΪ5,6,7,8 */ 
	unsigned char    StopBits;           /*!< ֹͣλ 0-1λ, 1-1.5λ, 2-2λ */ 
	unsigned char    Parity;             /*!< У��λ 0-no, 1-odd, 2-even */ 
	unsigned long   BaudBase;           /*!< {300,600,1200,2400,4800,9600,19200,38400,57600,115200}*/ 
} CONFIG_COMM;


typedef struct
{
	char    ProtocolName[12];			//Э����
	unsigned long	BaudBase;	        //������
	unsigned char	DataBits;	        //����λ
	unsigned char	StopBits;	        //ֹͣλ
	unsigned char	Parity;		        //У��λ
	unsigned char    Resove;
} DEC_PROTOCOL;

typedef struct
{
    unsigned char Version[8]; // 8�ֽڵİ汾��Ϣ
    char HostName[16]; // ������
    unsigned long HostIP; // IP ��ַ
    unsigned long Submask; // ��������
    unsigned long GateWayIP; // ���� IP
    unsigned long DNSIP; // DNS IP

    // �ⲿ�ӿ�
    unsigned long	AlarmServerIP; // ��������IP
    unsigned short  AlarmServerPort; // �������Ķ˿�
    unsigned long	SMTPServerIP; // SMTP server IP
    unsigned short  SMTPServerPort; // SMTP server port
    unsigned long	LogServerIP; // Log server IP
    unsigned short  LogServerPort; // Log server port

    // ��������˿�
    unsigned short  HttpPort; // HTTP����˿ں�
    unsigned short  HttpsPort; // HTTPS����˿ں�
    unsigned short  TCPPort; // TCP �����˿�
    unsigned short  TCPMaxConn; // TCP ���������
    unsigned short  SSLPort; // SSL �����˿�
    unsigned short  UDPPort; // UDP �����˿�
    unsigned long	McastIP; // �鲥IP
    unsigned short  McastPort; // �鲥�˿�
    
    // ����
    unsigned char  MonMode; // ����Э�� 0-TCP, 1-UDP, 2-MCAST //��ȷ��1-TCP
    unsigned char  PlayMode; // �ط�Э�� 0-TCP, 1-UDP, 2-MCAST//��ȷ��1-TCP
    unsigned char  AlmSvrStat; // ��������״̬ 0-�ر�, 1-��
}CONFIG_NET;

typedef struct
{
	int iOnTimeUpDay;   /*�����ϴ�����	"Never=0", "Everyday=1", "Sunday=2", "Monday", 
						Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"*/	
	int iOnTimeUpHour; //�����ϴ�ʱ�� [0, 23]	
}ALARM_CENTER_CFG;

/*��̫������*/
typedef struct 
{
	char	szEthernetName[64];		// ��������
	char	sDevIPAddr[16];			// DVR IP ��ַ
	char	sDevIPMask[16];			// DVR IP ��ַ����
	char	sGatewayIP[16];			// ���ص�ַ
	char	byMACAddr[40];			// MAC��ַ��ֻ��
	char	szMode[16];				// Mode:����������ģʽ, bond:��ģʽ����balance:���ؾ���ģʽ
	char	szDuplex[16];			// Full :ȫ˫�� Half :��˫�� Auto: ����Ӧ
	char	szSpeed[16];			// 10Mbps: 100Mbps: Auto: ����
	BYTE	bTranMedia;				// 0������ 1������
	BYTE	bValid;					// 0����Ч 1����Ч
	BYTE	bDefaultEth;			// 0����Ĭ�� 1��Ĭ��
	BYTE	bDHCPEnable;			// DHCPʹ��
	BYTE	bDHCPFunc;				// DHCP����
} CONFIG_ETHERNET;

/************************************************************************
 * ��̨�������Ͷ���
 ***********************************************************************/
typedef enum PTZControlType
{
	PTZ_UP =0,				//��
	PTZ_DOWN,			//��
	PTZ_LEFT,			//��
	PTZ_RIGHT,			//��
	PTZ_ZOOM_ADD,		//�䱶
	PTZ_ZOOM_DEC,		
	PTZ_FOCUS_ADD = 0x07,		//����
	PTZ_FOCUS_DEC = 0x08,		
	PTZ_APERTURE_ADD,	//��Ȧ
	PTZ_APERTURE_DEC,
    PTZ_POINT_MOVE = 0x10,     //ת��
    PTZ_POINT_SET ,      //����
    PTZ_POINT_DEL,      //ɾ��
	PTZ_LAMP = 0x0e,           //��
    PTZ_POINT_LOOP = 0x0f,     //�����ѭ
};

/*
typedef struct
{
    String  m_strServerAdd;  // �ʼ���������ַ
    String  m_strDestEmail;  //����Ŀ�ĵ�ַ
    String  m_strCCEmail;    //���䳭�͵�ַ
    String  m_strBccEmail;   //���䰵����ַ
    String  m_strUEmail;     // ����������
    String  m_strUName;  	 // ����������
    String  m_strUPwd; 	     // ����������
    String  m_strAttatch;  	 //add attatchment
    String  m_strSubject;  	 // ����
    String  m_strBody;       //����
    int m_iMaxAttatchSize;   // ������С����, -1 ������
} MAILER_CFG;
*/

enum log_t
{
	//system logs
	LOG_REBOOT = 0x0000,
	LOG_SHUT,

	//config logs
	LOG_CONFSAVE = 0x0100,
	LOG_CONFLOAD,

	//fs logs
	LOG_FSERROR = 0x0200,   //�ļ�ϵͳ����
	LOG_HDD_WERR,           //Ӳ��д����
	LOG_HDD_RERR,           //Ӳ�̶�����
	LOG_HDD_TYPE,           //����Ӳ������
	LOG_HDD_FORMAT,         //��ʽ��Ӳ��

	//alarm logs
	LOG_ALM_IN = 0x0300,

	//record
	LOG_MANUAL_RECORD_START = 0x0400,
	LOG_MANUAL_RECORD_STOP,

	//user manager
	LOG_LOGIN = 0x0500,
	LOG_LOGOUT,
	LOG_ADD_USER,
	LOG_DELETE_USER,
	LOG_MODIFY_USER,
	LOG_ADD_GROUP,
	LOG_DELETE_GROUP,
	LOG_MODIFY_GROUP,

	//clear
	LOG_CLEAR = 0x0600,

	//record operation
	LOG_SEARCH = 0x0700,    //¼���ѯ
	LOG_DOWNLOAD,           //¼������
	LOG_PLAYBACK,           //¼��ط�
	LOG_TYPE_NR = 8,
};

typedef struct _LOG_ITEM
{
    FRAME_TIME time;        //����
    unsigned short type;          //����
    unsigned char flag;          //���, 0x00 ������0x01 ��չ��0x02 ����
    unsigned char data;          //���� 0�˳� 1��½
    unsigned char context[8];    //����
}LOG_ITEM;

typedef struct
{
	unsigned char	Gen_Version[8]; //�汾��
	unsigned short	LocalNo;		// �������
	unsigned char	VideoFmt;		// ��ʽ :NTSC,PAL��
	unsigned char	Language;		// ����ѡ��
	unsigned char	OverWrite;		// ����ʱ��1������,��0��ֹͣ
	unsigned char	RecLen;			// ¼��γ���
	unsigned char	ShutPswEn;		// �ػ�����ʹ��
	unsigned char	DateFmt;		//���ڸ�ʽ
	unsigned char	DateSprtr;		//���ڷָ��
	unsigned char	TimeFmt;		//ʱ���ʽ
	unsigned char	DST;			// �Ƿ�ʵ������ʱ 1-ʵ�� 0-��ʵ��
	unsigned char	Reserved;		//δ֪
	unsigned char	ManualStart;	//�ֶ�¼������
	unsigned char	ManualStop;		//�ֶ�¼��ֹͣ
} CONFIG_GENERAL;

typedef struct 
{ 
    unsigned long dwVersion; 
    unsigned char dbReserve[4]; 
}VER_CONFIG; 

typedef struct
{
    VER_CONFIG sVerConfig;  /*! �����ļ��汾��Ϣ */
    unsigned long MotionRecordMask; /*! ¼������ */
    unsigned long MotionAlarmMask;  /*! �������: ��λ��ʾ����ͨ�� */
    unsigned long MotionTimeDelay;  /*! ��ʱ��10��300 sec */
    unsigned long MotionRegion[18]; /*! ���� */
    unsigned long BlindAlarmMask;   /*! �������: ��λ��ʾ����ͨ�� */
    unsigned long LossAlarmMask;    /*! ��ʧ���: ��λ��ʾ����ͨ�� */
    unsigned char MotionLever;       /*! �����ȣ�1��6 */
    unsigned char dbReserved[2];     /*! �����ֶ� */
    unsigned char BlindTipEn;        /*! ���������ʾʹ�� */
    unsigned char LossTipEn;         /*! ��ʧ�����ʾʹ�� */
    unsigned char Mailer;            /*! �����ʼ����루1-8λ��ʾ���8ͨ����ͼ�� */
    unsigned char SendAlarmMsg;      /*! ���ͱ�����Ϣ���������������ȣ� */
    unsigned char adbReserved[2];    /*! �����ֶ� */
} CONFIG_DETECT;

typedef struct __sys_string_support
{
	unsigned char  Version;		// �����õİ汾��Ϣ
    unsigned long Type;       // ֧�ֵ����ͣ� �����ʾ�� �ӵ͵�������ʾ���Զ���|UTF-8
	unsigned char  iReserved_00;	// Ԥ��
	unsigned char  iReserved_01;	// Ԥ��
	unsigned char  iReserved_02;	// Ԥ��
	unsigned char  iReserved_03;	// Ԥ��
	unsigned char  iReserved_04;	// Ԥ��
	unsigned char  iReserved_05;	// Ԥ��
	unsigned char  iReserved_06;	// Ԥ��
	unsigned char  iReserved_07;	// Ԥ��
}SYS_STRING_SUPPORT;

#define ALARM_SECTS 2

typedef struct 
{
    VER_CONFIG sVerConfig;          /*! �����ļ��汾��Ϣ */
    unsigned long AlarmMask;                /*! ����������� */
    unsigned long RecordMask;               /*! ¼��ͨ������ */
    unsigned long TimeDelay;                /*! ¼����ʱ��10��300 sec */
    unsigned char SensorType;                /*! ���������ͣ����� or ���� */
    unsigned char TimePreRec;                /*! Ԥ¼ʱ�� ���� Ԥ¼���� */
    unsigned char AlarmTipEn;                /*! ������ʾ */
    TSECT sAlarmSects[ALARM_SECTS]; /*! �����������ʾ��ʱ��� */
    unsigned long dwSectMask[ALARM_SECTS];  /*! �����������ʾ��ʱ��ε����� */
    unsigned long dwInputTypeMask;          /*! ���������������� */
    unsigned char dbTourEn;                  /*! �Ƿ���������ѵ */
    unsigned char Mailer;                    /*! �����ʼ����루1-8λ��ʾ���8ͨ����ͼ�� */
    unsigned char SendAlarmMsg;              /*! ���ͱ�����Ϣ���������������ȣ� */
    unsigned char adbReserved;               /*! �����ֶ� */
}CONFIG_ALARM, *pCONFIG_ALARM;

#define NAME_LEN	32

typedef struct {
	//VER_CONFIG sVerConfig;
	unsigned char	   ChnTitle[NAME_LEN];
}CONFIG_CHNTITLE;

typedef struct __sysattr_t
{
	unsigned char iVerMaj;          // BOIS���汾��(���)
	unsigned char iVerSub;          // BOIS�ΰ汾��(���)
	unsigned char iVideoInCaps;     // ��Ƶ����ӿ�����
	unsigned char iAudioInCaps;     // ��Ƶ����ӿ�����
	unsigned char iAlarmInCaps;     // ��������ӿ���
	unsigned char iAlarmOutCaps;    // ��������ӿ���
	unsigned char iIdePortNum;      // IDE�ӿ���
	unsigned char iAetherNetPortNum;// ����ӿ���
	unsigned char iUsbPortNum;      // USB�ӿ���
	unsigned char iComPortNum;      // ������
	unsigned char iParallelPortNum; // ���ڿ���
	unsigned char iMatrixOutNum;	// ��Ƶ��������˿����� 0��ʾ��֧�־�����
	unsigned short year;            // ��������: ��
	unsigned char  month;           // ��������: ��
	unsigned char  day;             // ��������: ��
	unsigned char iVerUser;         // BOIS�û��汾��(���)
	unsigned char iVerModify;       // BOIS�޸İ汾��(���)
	unsigned char iWebVersion[4];   // WEB�汾
	unsigned char WebYear;          // Ԥ��
	unsigned char WebMonth;         // Ԥ��
	unsigned char WebDay;           // Ԥ��
	unsigned char iReserved_01;     // Ԥ��
	unsigned char iReserved_02;     // Ԥ��
	unsigned char iReserved_03;     // Ԥ��
	unsigned char iReserved_04;     // Ԥ��
	unsigned char iReserved_05;     // Ԥ��
	unsigned char iIsMutiEthIf;     // ����֧�������0�������� 1������������������֮ǰ�ɵ�Э�飬�������µ��ַ���Э�飩
	unsigned char iReserved_07;     // Ԥ��
}SYSATTR_T;

//�汾0
typedef struct { 
	int		ide_num;   //Ӳ������ 
	int		ide_port;   //IDE������ 
	unsigned long	ide_msk;    //Ӳ������ 
	unsigned long	ide_bad;    //�������� 
	unsigned long	ide_cap[32];  //Ӳ������ 
} IDE_INFO, *pIDE_INFO; 

//�汾1
/// IDE�豸��Ϣ�ṹ
typedef struct IDE_INFO64{
	/// �ѹ��ص�Ӳ�̵�����,�����������̡�Ӳ�̸���Ҳ����ide_msk����1��λ������ȥ
	/// ide_bad����1��λ����. Ӧ�ó������Ӳ��ʱ, Ӳ����Ź�������: ��һ������1
	/// ��λ��Ӧ��IDEͨ���Ϲ��ص�����Ӳ�̵�Ӳ�����Ϊ0���ڶ�������1��λ��Ӧ����
	/// Ӳ�̵�Ӳ�����Ϊ1���������ơ�
	int		ide_num;//��������
	
	///< IDEͨ������Ŀ��������չ��IDEͨ����
	int		ide_port;//ignore
	
	/// ָʾ����IDEͨ�����Ƿ����Ӳ�̣��������̡�ÿһλ��ӦIDEͨ�������̻���̣�
	/// ��λ��ʾ�Թ���Ӳ�̣�����û�С���Ӧ��ϵΪbit0��ӦIDE0�����̣�bit1��ӦIDE0
	/// �Ĵ��̣�bit2��ӦIDE1�����̣�bit3��ӦIDE1�Ĵ��̣��������ơ�
	unsigned long	ide_msk;//ignore
	
	/// ָʾ����IDEͨ�����Ƿ�����˻���Ӳ�̡�ÿһλ��ӦIDEͨ�������̻���̣���λ
	/// ��ʾ���л�Ӳ�̣�����û�С���Ӧ��ϵͬide_msk��
	unsigned long	ide_bad;//ignore
	
	/// �ѹ��ص�����Ӳ�̵�������������Ϊ��λ��������СΪIDE_SECTOR_SIZE����������
	/// 32λ����ʾ�������±�������Ӳ�̵���š�
#ifdef WIN32
	unsigned __int64			ide_cap[32];
#else	//linux
	unsigned long long			ide_cap[32];
#endif
	FRAME_TIME  start_time1;		//�ܵ�¼��ʼʱ��
	FRAME_TIME	end_time1;			//�ܵ�¼�����ʱ��
	DWORD	total_space;		//������
	DWORD	remain_space;		//ʣ������
} IDE_INFO64, *pIDE_INFO64;

 /*
 //��������Ϣ�ṹ 
 typedef struct _DRIVER_INFO{ 
 	unsigned long	driver_type;    //���������� 
 	long	is_current;   //�Ƿ�Ϊ��ǰ������ 
 	FRAME_TIME  start_time1;    //¼��ʱ���1��ʼʱ�� 
 	FRAME_TIME  end_time1;    //¼��ʱ���1����ʱ�� 
 	long	two_part;    //�Ƿ��еڶ���
 	FRAME_TIME  start_time2;    //¼��ʱ���2��ʼʱ�� 
 	FRAME_TIME  end_time2;    //¼��ʱ���2����ʱ�� 
 	unsigned long	total_space;    //������ 
 	unsigned long	remain_space;    //ʣ������ 
 	unsigned long	error_flag;   //�����־���ļ�ϵͳ��ʼ��ʱ������ 
 }DRIVER_INFO,*pDRIVER_INFO; 
 
 typedef  struct  {
 	int ide_num; //Ӳ������
 	int ide_port; //IDE������
 	DWORD ide_msk; //Ӳ������
 	DWORD ide_bad; //��������
 	DWORD ide_cap[32]; //Ӳ������
 }  IDE_INFO,  *pIDE_INFO;
 */
 
//��������Ϣ�ṹ
typedef  struct  _DRIVER_INFO{
	unsigned long driver_type; //����������
	long is_current; //�Ƿ�Ϊ��ǰ������
	unsigned long section_count; //ʱ�����
	FRAME_TIME    start_time1; //¼��ʱ���1��ʼʱ��
	FRAME_TIME end_time1; //¼��ʱ���1����ʱ��
	long two_part; //�Ƿ��еڶ���
	FRAME_TIME start_time2; //¼��ʱ���2��ʼʱ��
	FRAME_TIME end_time2; //¼��ʱ���2����ʱ��
	unsigned long total_space; //������
	unsigned long remain_space; //ʣ������
	unsigned long error_flag; //Ӳ��״̬ 0��normal 1��error
	unsigned long index; //Ψһ������ʶ��0~3�����̺ţ�4~6�������ţ�7����ʶ0Ϊ���� 1ΪԶ��
}DRIVER_INFO,*pDRIVER_INFO;

//�Ƿ�֧���µ�¼��ͼƬ�б��ѯ��ʽ
typedef struct __RecordEnable_T
{
	BYTE isSupportNewA5Query;
	BYTE supportNewA5QueryType;
	BYTE reserved[2];
}RecordEnable_T;

//�Ƿ�֧���µ���־��ѯ(XML��ʽ��������)
typedef struct tagNewLogType
{
	char isSupportNewLogType;
	char reserved[3];
}NEW_LOG_TYPE_SUPPORT_T;

//ͼ��ˮӡ����
typedef struct __WaterMake_Enable_T
{
	char isSupportWM;	//1 ֧�֣�0 ��֧��
	char supportWhat;	//0������ˮӡ��1��ͼƬˮӡ��2��ͬʱ֧������ˮӡ��ͼƬˮӡ
	char reserved[2];
}WaterMake_Enable_T;

//�Ƿ�֧�����߹���
typedef struct __Wireless_Enable_T
{
	char isWirelessEnable;
	char reserved[3];
}Wireless_Enable_T;

//! Ԥ��ͼ������
typedef struct __config_ex_capture_t
{
	BYTE		 iQuality;		// ����
	BYTE		 iReserved[31];	// ����
}CONFIG_EX_CAPTURE_T;

//��Ƶ����������
typedef struct _CONFIG_AUDIO_DETECT
{
	VER_CONFIG sVerConfig;		/*! �����ļ��汾��Ϣ */
	DWORD	AlarmMask;			/*! ��������������� */
	DWORD	RecordMask;			/*! ¼��ͨ������ */
	DWORD	TimeDelay;			/*! ¼����ʱ��10��300 sec */
	BYTE	iEnable; 			/*! [������ʾ��������ʹ��] */
	BYTE	TimePreRec;			/*! Ԥ¼ʱ�� ���� Ԥ¼���� */
	BYTE	iValve;				/*! [������ʾ��ֵ0---100] */
	BYTE	almReserved;		/*! �����ֶ� */
	TSECT	sAlarmSects[ALARM_SECTS];	/*! �����������ʾ��ʱ��� */
	DWORD	dwSectMask[ALARM_SECTS];	/*! �����������ʾ��ʱ��ε����� */
	DWORD	dwInputTypeMask;	/*! ���������������� */
	BYTE	dbTourEn;			/*! �Ƿ���������ѭ */
	BYTE	Mailer;				/*! �����ʼ�ʹ�� 1- ���� 0 - ���� */
	BYTE	SendAlarmMsg;		/*! ���ͱ�����Ϣ���������������ȣ� */	
	BYTE	adbReserved;		/*! �����ֶ� */
} CONFIG_AUDIO_DETECT, *pCONFIG_AUDIO_DETECT;

typedef struct __sys_status_t
{
	BYTE	iVer;
	BYTE	iCPUOcc;
	BYTE	iDispStatus_VGA;
	BYTE	iDispStatus_TV;
	BYTE	iRev[60];
} SYS_STATUS_T;

typedef struct __channel_info_t
{
	BYTE	iVer;
	BYTE	iChannel;
	BYTE	iSubChannel;
	BYTE	iRev;
} CHANNEL_INFO_T;

//�Զ�ά��
typedef struct __CONFIG_AUTO_NET
{
	BYTE verConfig[8]; /*! �����ļ��汾��Ϣ */
	BYTE AutoRebootDay; /*! 0-�Ӳ�, 1-ÿ��, 2-ÿ������, 3-ÿ����һ,..... */
	BYTE AutoRebootTime; /*! 0-0:00 1-1:00,........23-:23:00 */
	BYTE AutoDeleteFilesTime; /*! 0-�Ӳ�, 1-24H, 2-48H, 3-72H, 4-96H, 5-ONE WEEK, 6-ONE MONTH */
	BYTE reserved[13]; // ����λ
} CONFIG_AUTO_NET;

//Begin: new alarm, Add by yehao(10857) 2007-04-24
typedef struct tagTIMESECTION
{
	BOOL	bEnable;
	int		H1;
	int		M1;
	int		S1;
	int		H2;
	int		M2;
	int		S2;
} TIMESECTION, *LPTIMESECTION;

#define WORKSHEET_NUM 16

typedef struct tagWORKSHEET
{
	int		iName;
	TIMESECTION tsSchedule[N_WEEKS][N_TSECT];
} CONFIG_WORKSHEET;

typedef struct tagPTZ_LINK
{
	int iType;					/*! �������� */
	int iValue;					/*! ������� */
} PTZ_LINK, *LPPTZ_LINK;

typedef struct tagEVENT_HANDLER
{
	DWORD	dwRecord;
	int		iRecordLatch;
	DWORD	dwTour;
	DWORD	dwSnapShot;
	DWORD	dwAlarmOut;
	int		iAOLatch;
	PTZ_LINK	PtzLink[N_SYS_CH];

	BOOL	bRecordEn;
	BOOL	bTourEn;
	BOOL	bSnapEn;
	BOOL	bAlarmOutEn;
	BOOL	bPtzEn;
	BOOL	bTip;
	BOOL	bMail;
	BOOL	bMessage;
	BOOL	bBeep;
	BOOL	bVoice;
	BOOL	bFtp;

	DWORD	dwWorkSheet;
	
	DWORD	dwMatrix;				/*!< �������� */
	BOOL	bMatrixEn;				/*!< ����ʹ�� */
	BOOL	bLog;					/*!< ��־ʹ�ܣ�Ŀǰֻ����WTN��̬�����ʹ�� */
	int		iEventLatch;			/*!< ������ʼ��ʱʱ�䣬sΪ��λ ��Χ��0����15 Ĭ��ֵ��0*/
	BOOL	bMessagetoNet;			/*!< ��Ϣ�ϴ�������ʹ�� */
	DWORD	wiAlarmOut; 			/*!< ���߱������ */
	BYTE	bMMSEn;					/*!< ���ű���ʹ��  */
	BYTE	SnapshotTimes;          /*!< ץͼ���� */
	char	dReserved[22];			/*!< �����ֽ� */
} EVENT_HANDLER, *LPEVENT_HANDLER;

//���ر��������籨���¼���
typedef struct tagCONFIG_ALARM_X
{
	BOOL	bEnable;
	int		iSensorType;
	EVENT_HANDLER	hEvent;
} CONFIG_ALARM_X, *LPCONFIG_ALARM_X;

//��̬����¼�
#define MD_REGION_ROW	32
typedef struct tagCONFIG_MOTIONDETECT
{
	BOOL	bEnable;
	int		iLevel;
	int		iRegion[MD_REGION_ROW];	//ÿ��ʹ�ö����ƴ�
	EVENT_HANDLER	hEvent;
} CONFIG_MOTIONDETECT, *LPCONFIG_MOTIONDETECT;

//��Ƶ��ʧ�¼�
typedef struct tagCONFIG_LOSSDETECT
{
	BOOL	bEnable;
	EVENT_HANDLER	hEvent;
} CONFIG_LOSSDETECT, *LPCONFIG_LOSSDETECT;

//��Ƶ�ڵ��¼�
typedef struct tagCONFIG_BLINDDETECT
{
	BOOL	bEnable;
	int		iLevel;			//�����ȣ�1 ~ 6
	EVENT_HANDLER	hEvent;
} CONFIG_BLINDDETECT, *LPCONFIG_BLINDDETECT;

#define ALARM_MAX_NAME 64
//!(����)���ⱨ��
//����ң�������ã�
typedef struct tagCONFIG_WI_REMOTE_CONTROL
{
	BYTE  address[ALARM_MAX_NAME];// ң������ַ
	BYTE  name[ALARM_MAX_NAME];// ң��������
	BYTE  reserved[32]; //�����ֶ�
}CONFIG_ROBOT;

//���߱���������ã�
typedef struct tagCONFIG_WI_ALARM_OUT
{
	BYTE  address[ALARM_MAX_NAME];//���������ַ
	BYTE  name[ALARM_MAX_NAME];//�����������
	BYTE  reserved[32]; //�����ֶ�
}WI_ALARM_OUT;

typedef struct Infrared_Alarm_Info
{
	char				alarmInAddress[ALARM_MAX_NAME];		//����������ĵ�ַ
	int					alarmInPattern;						//���������벨��
//	char				remoteAddress[ALARM_MAX_NAME];		//ң��������Ч��ַ
//	char				alarmOutAddress[ALARM_MAX_NAME];	//��������ĵ�ַ
	char				res[ALARM_MAX_NAME*2];
	int					alarmOutPattern;					//�����������
	int					iSensorType;						//�ⲿ�豸���������ͳ��� or ����
	char				alarmName[ALARM_MAX_NAME];			//������������
	BOOL				enable;								//��������ʹ��
	int					defendEfectTime;					//��������ʱʱ�䣬�ڴ�ʱ���ñ���������Ч
	int					defendAreaType;						//��������
	int					alarmSmoothTime;					//����ƽ��ʱ�䣬���ڴ�ʱ�������ֻ��һ��������������������������Ե�����һ��
	EVENT_HANDLER		hEvent;								//��������
} CONFIG_ALARM_INFRARED;

//!��Ƶ�¼��ṹ
typedef struct tagCONFIG_AUDIODETECT_EVENT
{
	//!������
	BOOL enable;
	int  Volume_min;
	int  Volume_max;
	//!�������
	EVENT_HANDLER hEvent;
} CONFIG_ALARM_AUDIO;

//�����������¼�
#define ALARMDEC_OUT_SLOTS_NUM	8
#define ALARMDEC_IN_SLOTS_NUM	8

typedef struct tagCONFIG_ALARMDECODER
{
	int		iAddress;
	BOOL	bEnable;
	int		iOutSlots[ALARMDEC_OUT_SLOTS_NUM];//ӳ�䵽���ر��������ͨ���ţ������ص��������ܶϿ�
	CONFIG_ALARM_X	InSlots[ALARMDEC_IN_SLOTS_NUM];
} CONFIG_ALARMDECODER, *LPCONFIG_ALARMDECODER;

//Ӳ�����������¼�
typedef struct tagCONFIG_DISKNOSPACE
{
	BOOL	bEnable;
	int		iLowerLimit;	//0 ~ 99
	EVENT_HANDLER	hEvent;
} CONFIG_DISKNOSPACE, *LPCONFIG_DISKNOSPACE;

typedef struct tagCONFIG_RECORD_NEW
{
	int iPreRecord;			/*!< Ԥ¼ʱ�䣬Ϊ��ʱ��ʾ�ر� */	
	BOOL bRedundancy;		/*!< ���࿪�� */
	BOOL bSnapShot;			/*!< ���տ��� */	
	BYTE iWsName;			/*!< ѡ�еĹ������� */
	BYTE byRecordType;      /*¼������0-������ 1-������1 2-������2 3-������3*/
	BYTE byReserved[2];     //����
} CONFIG_RECORD_NEW;

//Ӳ�̳����¼�
//��Ӳ���¼�
//�����¼�
typedef struct tagCONFIG_GENERIC_EVENT
{
	BOOL	bEnable;
	EVENT_HANDLER	hEvent;
} CONFIG_GENERIC_EVENT, *LPCONFIG_GENERIC_EVENT;

typedef struct tagCONFIG_STORAGE_NUMBER_EVENT
{
	//!������
	BOOL enable;
	//!�ͻ����õ�Ӳ�̸���
	int  iHddNumber;			
	EVENT_HANDLER handler;
} CONFIG_STORAGE_NUMBER_EVENT;

// ȫ���л���������
typedef struct tagCONFIG_PANORAMA_SWITCH
{
	BOOL			bEnable;
	EVENT_HANDLER	hEvent;
} CONFIG_PANORAMA_SWITCH, *LPCONFIG_PANORAMA_SWITCH;

// ʧȥ���㱨������
typedef struct tagCONFIG_LOST_FOCUS
{
	BOOL			bEnable;
	EVENT_HANDLER	hEvent;
} CONFIG_LOST_FOCUS, *LPCONFIG_LOST_FOCUS;

//End: yehao(10857) 2007-04-24

//�����Խ�
typedef struct __dialog_caps_t
{
	// ֧�ֵ���Ƶ���ݸ���������
	BYTE iAudioTypeNum;		/*!< �Ƿ�֧�������Խ� */
	// ����λ
	BYTE iRev[31];
} DIALOG_CAPS;

typedef struct __audio_attr_t
{
	//֧�ֵı�������
	WORD iAudioType;			// 1:PCM, 2:G711a, 3:AMR ,4:G711u 5:G726
	//λ
	WORD iAudioBit;			// ��ʵ�ʵ�ֵ��ʾ�� ��8λ ����ֵΪ8
	//֧�ֵĲ�����
	DWORD dwSampleRate;			// ��ʵ�ʵ�ֵ��ʾ�� ��8k ����ֵΪ8000
	//����λ
	BYTE	iRev[64];
}AUDIO_ATTR_T;

//������Ƶ�����������
#define MATRIX_MAXOUT 4
#define TOUR_GROUP_NUM 6

typedef struct
{
	BYTE VideoOut[TOUR_GROUP_NUM]; /*!< ��Ƶ��� 0����--��g_nCapture+1����
	all*/
	int Interval; /*!< ��Ѳ��� */
	BYTE EnableTour; /*!< �Ƿ���Ѳ */
	BYTE AlarmChannel; /*!< ��������ͨ�� 0����--��g_nCapture+1��
	��1-4, g_nCapture+2����5-8*/
	BYTE Reserve[2];
}VIDEOGROUP;

typedef struct
{
	BYTE VideoMatrixVersion[8]; /*!< �����ļ��汾��Ϣ */
	VIDEOGROUP VideoGroup[MATRIX_MAXOUT]; /*!< ����������Ƶ������� */
}CONFIG_VIDEO_MATRIX;

//���洢��Ϣ�ṹ
typedef struct __card_storage_info
{
	BYTE Version; //�ṹ�汾��Ϣ
	BYTE Reserved[3];
	DWORD DevNum; //�豸����
	DWORD DevPort; //�ӿ�����
	DWORD DevBad; //�����豸����
	DWORD DevCap[32]; //������
}CARD_STORAGE_INFO, *pCARD_STORAGE_INFO;

typedef struct __card_storage_device_info
{
	BYTE Version; //�ṹ�汾��Ϣ
	BYTE Reserved[3];
	DWORD DriverType; //����������
	DWORD TotalSpace; //������(�ֽ�)
	DWORD RemainSpace; //ʣ������(�ֽ�)
	BYTE DriverName[64]; //����������
}CARD_STORAGE_DEVICE_INFO,*pCARD_STORAGE_DEVICE_INFO;

//��¼����Ϣ
typedef struct __BACKUP_DEVICE  
{
	struct __BACKUP_DEVICE		*prev;			/* pointer to previous device */
	struct __BACKUP_DEVICE		*next;			/* pointer to next device */
	
	char		name[32];		/* device name */
	
	int			type;				/* device type, usb disk or cdrw */
	int			bus;				/* bus type, usb or ide */
	
	unsigned int	capability;	/* device capacity(KB) */
	unsigned int	remain;		/* device remain space(KB) */
	char		directory[128];	/* attached dir */
	int			flag;				/* reserved */
	
	void		*priv;			/* pointer to private data */
}BACKUP_DEVICE;

//FTP structure
#define	MAX_USERNAME_LEN	64   //10
#define	MAX_PASSWORD_LEN	64    //10
#define	MAX_CHANNEL_NUM		16
#define	DAYS_WEEK			7
#define	TIME_SECTION		2
#define FTP_MAX_PATH		240

typedef struct __MD_ALARM_FTP_Set
{
	struct
	{
		TSECT	m_tSect;
		int		m_MdEn;// ��̬���
		int		m_AlarmEn;//�ⲿ����
		int		m_TimerEn;//��ͨ¼��
		int		m_Rev[4];
	} m_Period[TIME_SECTION];
} CONFIG_MD_ALRAM_FTP_SET;

//FTP
typedef struct __General_Protocol_FTP_set
{
	int				m_isEnable;		//�Ƿ�����
	unsigned long	m_unHostIP;		//����IP
	unsigned short	m_nHostPort;		//�����˿�
	char 			m_protocol;			//0-FTP 1-SMB
	char			m_NASVer;				//����洢�������汾0=�ϵ�FTP(��������ʾʱ���),1=NAS�洢������������ʱ��Σ�
	char			m_cDirName[FTP_MAX_PATH];			//FTPĿ¼·��
	char			m_cUserName[MAX_USERNAME_LEN];	//�û���
	char			m_cPassword[MAX_PASSWORD_LEN];	//����
	int				m_iFileLen;					//�ļ�����
	int				m_iInterval;					//�����ļ�ʱ����
	CONFIG_MD_ALRAM_FTP_SET	m_stMdAlarmSet[MAX_CHANNEL_NUM][DAYS_WEEK];
	char 			m_Rev[128];
} CONFIG_FTP_PROTO_SET;

//��ý������
typedef struct __main_frame_caps
{
	DWORD Compression;
	DWORD ImageSize;
}MAIN_FRAME_CAPS;

enum capture_size_t {
	CAPTURE_D1,
	CAPTURE_HD1,	
	CAPTURE_BCIF,
	CAPTURE_CIF,
	CAPTURE__QCIF,	
	CAPTURE_VGA,	
	CAPTURE_QVGA,
	CAPTURE_SVCD,
	CAPTURE_QQVGA,
	CAPTURE_UXGA,
	CAPTURE_NR,
};

typedef struct tagCAPTURE_EXT_STREAM
{
	DWORD ExtraStream;	//��λ��ʾ�豸֧�ֵĹ��ܣ�
						//��һλ��ʾ֧��������
						//�ڶ�λ��ʾ֧�ָ�����1
						//����λ��ʾ֧�ָ�����2
						//����λ��ʾ֧��jpgץͼ
	DWORD CaptureSizeMask[64];	//��ʾ������Ϊ���ֱ���ʱ��֧�ֵĸ������ֱ������롣
}CAPTURE_EXT_STREAM, *pCAPTURE_EXT_STREAM;	

typedef struct tagCAPTURE_DSPINFO
{
	unsigned int nMaxEncodePower; /*- DSP ֧�ֵ���߱������� -*/
	unsigned short nMaxSupportChannel; /*- DSP ֧�����������Ƶͨ���� -*/
	unsigned short bChannelMaxSetSync; /*- DSP ÿͨ���������������Ƿ�ͬ�� 0-
									   ��ͬ��, 1 -ͬ�� -*/
}CAPTURE_DSPINFO, *PCAPTURE_DSPINFO;

//�汾1��2008.3.13�����˷ֱ�������CAPTURE_SIZE_QQVGA
/// ����ֱ�������
/*
enum capture_size_t {
	CAPTURE_SIZE_D1,		///< 720*576(PAL)	720*480(NTSC)
		CAPTURE_SIZE_HD1,		///< 352*576(PAL)	352*480(NTSC)
		CAPTURE_SIZE_BCIF,		///< 720*288(PAL)	720*240(NTSC)
		CAPTURE_SIZE_CIF,		///< 352*288(PAL)	352*240(NTSC)
		CAPTURE_SIZE_QCIF,		///< 176*144(PAL)	176*120(NTSC)
		CAPTURE_SIZE_VGA,		///< 640*480(PAL)	640*480(NTSC)
		CAPTURE_SIZE_QVGA,		///< 320*240(PAL)	320*240(NTSC)
		CAPTURE_SIZE_SVCD,		///< 480*480(PAL)	480*480(NTSC)
		CAPTURE_SIZE_QQVGA,		///< 160*128(PAL)	160*128(NTSC)
		CAPTURE_SIZE_NR			///< ö�ٵ�ͼ�δ�С�������Ŀ��
};
*/
/// ����������֧�����Խṹ
typedef struct _CAPTURE_EXT_STREAM_NEW
{
	DWORD ExtraStream;						///< ��channel_t��λ����ʾ֧�ֵĹ��ܡ�
	DWORD CaptureSizeMask[64];	///< ÿһ��ֵ��ʾ��Ӧ�ֱ���֧�ֵĸ���������
}CAPTURE_EXT_STREAM_NEW, *pCAPTURE_EXT_STREAM_NEW;	

//U��ͨƽ̨����
typedef struct _intervideo_ucom_chn
{
    unsigned char iChnEn;
    unsigned char iRes[3];
    unsigned char strChnId[32];
}INTERVIDEO_UCOM_CHN;

typedef struct __config_intervideo_ucom
{
	unsigned char iFuncEnable;		// ���빦��ʹ����� 0 - ʹ��
	unsigned char iAliveEnable;	// ����ʹ�����
	unsigned short iAlivePeriod;	// ��������
	unsigned long ServerIp;		// CMS��IP
	unsigned short ServerPort;// CMS��Port
	unsigned short __Res;
    unsigned char strRegPwd[16]; //ע������
	unsigned char strDeviceId[32];
    INTERVIDEO_UCOM_CHN  sChnInfo[N_SYS_CH];//ͨ��id,en
	unsigned char strUserName[32];
	unsigned char strPassWord[32];
	unsigned short __Resv[256];
}CONFIG_INTERVIDEO_UCOM;

//�Ϻ�������������ƽ̨����
typedef struct asbWEB_VSP_CONFIG
{
    unsigned short usCompanyID[2];  /* ��˾ID,��ֵ,��ͬ�ĵ���������˾,����4�ֽڶ���,Ŀǰֻ�������һ�� */
    char szDeviceNO[32];  /* ǰ���豸���кţ��ַ���, ����'\0'��������32byte */
    char szVSName[32];  /* ǰ���豸���ƣ��ַ���, ����'\0'��������16byte */
    char szVapPath[32];  /* VAP·�� */
    unsigned short usTcpPort;  /* TCP �˿�,��ֵ: ��ֵ 1~65535 */    
    unsigned short usUdpPort;  /* UDP �˿�,��ֵ: ��ֵ 1~65535 */    
    bool bCsEnable[4];  /* ���ķ�����ʹ�ܱ�־, ��ֵ: trueʹ��, false��ʹ��,����4�ֽڶ���,Ŀǰֻ�������һ�� */
    char szCsIP[16];  /* ���ķ�����IP��ַ, �ַ���, ����'\0'��������16byte */
    unsigned short usCsPort[2];  /* ���ķ������˿�,��ֵ: ��ֵ 1~65535,����4�ֽڶ���,Ŀǰֻ�������һ�� */    
    bool bHsEnable[4];  /* ����������ʹ�ܱ�־, ��ֵ: trueʹ��, false��ʹ��,����4�ֽڶ���,Ŀǰֻ�������һ�� */
    char szHsIP[16];  /* ����������IP��ַ, �ַ���, ����'\0'��������16byte */
    unsigned short usHsPort[2];  /* �����������˿�,��ֵ: ��ֵ 1~65535,����4�ֽڶ���,Ŀǰֻ�������һ�� */ 
    int iHsIntervalTime;  /* �����������������,��ֵ(��λ:��) */ 
    bool bRsEnable[4];  /* ע�������ʹ�ܱ�־, ��ֵ: trueʹ��, false��ʹ��,����4�ֽڶ���,Ŀǰֻ�������һ�� */
    char szRsIP[16];  /* ע�������IP��ַ, �ַ���, ����'\0'��������16byte */
    unsigned short usRsPort[2];  /* ע��������˿�,��ֵ: ��ֵ 1~65535,����4�ֽڶ���,Ŀǰֻ�������һ�� */
    int iRsAgedTime;  /* ע���������Чʱ��,��ֵ(��λ:Сʱ) */
    char szAuthorizeServerIp[16];  /* ��Ȩ������IP */
    unsigned short usAuthorizePort[2];  /* ��Ȩ�������˿�,����4�ֽڶ���,Ŀǰֻ�������һ�� */
    char szAuthorizeUsername[32];  /* ��Ȩ�������ʺ� */
    char szAuthorizePassword[36];  /* ��Ȩ���������� */
    
    char szIpACS[16];  /* ACS(�Զ�ע�������) IP */
    unsigned short usPortACS[2];  /* ACS Port,����4�ֽڶ���,Ŀǰֻ�������һ�� */
    char szUsernameACS[32];  /* ACS�û��� */
    char szPasswordACS[36];  /* ACS���� */
    bool bVideoMonitorEnabled[4];  /* DVS�Ƿ����ϱ�ǰ����Ƶ�źż����Ϣ, ��ֵ: trueʹ��, false��ʹ�� */
    int iVideoMonitorInterval;  /* �ϱ����ڣ����ӣ� */
    
    char szCoordinateGPS[64];  /* GPS���� */
    char szPosition[32];  /* �豸λ�� */
    char szConnPass[36];  /* �豸������ */
}WEB_VSP_CONFIG;

typedef struct tagWEB_NSS_CONFIG
{
    unsigned short server_port;               //�������˿�, ��ֵ, ��ֵ1~65535
    char server_ip[32];      //������IP��ַ, �ַ���, ����'\0'��������32byte
    char device_serial_no[32]; //ǰ���豸���кţ��ַ���,����'\0'��������32byte
    char username[32];
    char passwd[50];
}WEB_NSS_CONFIG;

//add by cqs 2008-05-09 Watchnetץ���½ṹ
#define SNIFFER_FRAMEID_NUM 6     ////6��FRAME ID ѡ��
#define SNIFFER_CONTENT_NUM 4     /////ÿ��FRAME��Ӧ��4��ץ������
#define MAX_PROTOCOL_NAME_LENGTH 20
#define SNIFFER_GROUP_NUM 4       ///4��ץ������

typedef enum __DISPLAY_POSITION
{
	DISPLAY_TOP = 0,
		DISPLAY_BOTTOM
}DISPLAY_POSITION;    //����λ�ã���Ϊ���Ϻ�����

typedef struct __SNIFFRT_CONFIG_IP
{	
	unsigned long SnifferSrcIP; //ץ��Դ��ַ
	int SnifferSrcPort;  //ץ��Դ�˿�
	unsigned long SnifferDestIP; //ץ��Ŀ���ַ
	int SnifferDestPort; //ץ��Ŀ��˿�
} SNIFFER_IP;

typedef struct __sniffer_frameid
{
	int		Offset; //��־λ��λƫ��
	int		Length; //��־λ�ĳ���
	char	Key[16]; //��־λ��ֵ
} SNIFFER_FRAMEID;

typedef struct __SNIFFER_CONTENT
{
	int  Offset;    ///��־λ��λƫ��
	int  Offset2;    //Ŀǰû��Ӧ��
	int  Length;  //��־λ�ĳ���
	int  Length2;   //Ŀǰû��Ӧ��
	char  KeyTitle[24];  //�����ֵ
} SNIFFER_CONTENT;

typedef  struct _CONFIG_ATM_NET    ////ÿ��ץ����Ӧ�����ýṹ
{
	SNIFFER_IP  snifferIp;   ////ץ��IP����
	BOOL generalProtocolEnable;  /////Э��ʹ��
	BOOL dataScopeEnable;     /////Ŀǰû��Ӧ��
	char Protocol[MAX_PROTOCOL_NAME_LENGTH];
	SNIFFER_FRAMEID  snifferFrameId[SNIFFER_FRAMEID_NUM];   ////6��FRAME ID ѡ��
	SNIFFER_CONTENT snifferContent[SNIFFER_FRAMEID_NUM][SNIFFER_CONTENT_NUM];  /////ÿ��FRAME��Ӧ��4��ץ������
	int displayPosition;       /////��ʾλ��
	int recdChannelMask;   //ͨ������
} CONFIG_ATM_SNIFFER;

typedef struct __General_Protocol_NTP_set
{
	char				Enable;					//�Ƿ�����
	char				Reserved;
	unsigned short		unHostPort; 			//NTP������Ĭ�϶˿�Ϊ123
	unsigned long		unHostIP;				//����IP
	int					nUpdateInterval;		//����ʱ��
	int					iTimeZone;				//ʱ����-12~13,����Ķ�Ϊ0-25
}CONFIG_NTP_PROTO_SET;
#define MAX_PATH_STOR 240
//add by cqs 2008-07-07 �洢λ�ýṹ
typedef struct tagCONFIG_STORAGE 
{
	DWORD dwLocalMask;      //���ش洢����							|ע:�����16λ��ʾץͼ����16λ��ʾ¼��
	DWORD dwMobileMask;     //���ƶ��洢							|	0x0001		/*!< ϵͳԤ¼�¼�	*/
	int  RemoteType;        //Զ�̴洢���� 0: Ftp  1: Smb			|	0x0002		/*!< ��ʱ¼���¼�	*/
	DWORD dwRemoteMask;     //Զ�̴洢								|	0x0004		/*!< ����¼���¼�	*/
	DWORD dwRemoteSecondSelLocal; //Զ���쳣ʱ���ش洢				|	0x0008		/*!< ����¼���¼�	*/	
	DWORD dwRemoteSecondSelMobile; //Զ���쳣ʱ���ƶ��洢			|	0x0010		/*!< ����¼���¼�	*/
	char SubRemotePath[MAX_PATH_STOR];  //Զ��Ŀ¼, ���г���Ϊ260	|	0x0020		/*!< �ֶ�¼���¼�	*/
	DWORD dwFunctionMask;        //��������λ��bit0 = 1:����ץͼ�¼������洢λ�ù���
    DWORD Res[19];
}CONFIG_STORAGE_STATION;

//��Ƶǰ�˲ɼ�����
typedef struct __prevideo_capture
{
	unsigned char iCifCaps; 	// ��С
	unsigned char iFrameCaps;	// ֡��
	unsigned char reserved[30];	// �����ֽ�
}Prevideo_Capture;

//��Ƶ������Ϣ
typedef struct __sysattr_video_caps
{
	unsigned int iCifCaps; 		// ��С
	unsigned int iTypeCaps;		// ����
	unsigned int iFrameCaps;	// ֡��
	unsigned int iQualityCaps;	// ����
	unsigned char iCifFrames;	// ÿ��оƬ������֡�� ��λ��cif/s
	unsigned char iWaterMask;	// ֧��ˮӡ�������λ��ʾ����λ���ַ�����λ��ͼƬ
	unsigned char iEncodeCap;	// ���������㷨��ʾ
	unsigned char _iRev_02;		// ����
	unsigned int iReserved_01;	// ����
	unsigned int iReserved_02;	// ����
	unsigned int iReserved_03;	// ����
	unsigned char iStandard;	// ��ʽ
	unsigned char iRev_00;		// ����
	unsigned char iRev_01;		// ����
	unsigned char iRev_02;		// ����
}SYSATTR_VIDEO_CAPS_T;


//! ���������ļ�
typedef struct 
{
	char			FileName[32];			// �����ļ�����
	unsigned long	FileTotalLen;			// �ļ��ܳ��ȣ���λ�ֽ�
	unsigned long	ThisFrameNo;			// �����ݰ������
	unsigned long	ThisFrameLen;			// �����ݰ���Ч��Ϣ�ĳ���
	unsigned char	DataBuffer[1024];		// ���ݻ��峤��1k
} CFG_FILE_INFO;

typedef struct 
{
	unsigned long	AllConfigLen;			// ������Ϣ���ܳ���
	unsigned short	TotalConfigFileNum;		// �ܵ������ļ�����
	unsigned short	CurrentFileNo;			// ��ǰ�����ļ��ı��
	CFG_FILE_INFO	ConfigFile;
} CFG_INFO;									// �ܳ���1076�ֽ�


typedef struct  
{
	int				type;					// �޸Ĳ������
	int				nResultCode;			// ������
	BOOL			bReboot;				// ������־
} CONFIG_ACK_INFO;


typedef struct  
{
	int				nEncoderNum;
	unsigned int	nTotalSize;
	unsigned int	nCurSize;
} NVD_PLAYBACK_EVENT;


//�û�������Ϣ

enum EnAuthority
{
	DVRG_AUTHORITY_SYSSET			=  0,		// �������		_01
	DVRG_AUTHORITY_SHUTDOWN			=  1,		// �ر�ϵͳ		_02
	DVRG_AUTHORITY_MONITOR			=  2,		// ����			_03
	DVRG_AUTHORITY_MONITOR_01		=  3,		// ����ͨ��_01	_04
	DVRG_AUTHORITY_MONITOR_02		=  4,		// ����ͨ��_02	_05
	DVRG_AUTHORITY_MONITOR_03		=  5,		// ����ͨ��_03	_06
	DVRG_AUTHORITY_MONITOR_04		=  6,		// ����ͨ��_04	_07
	DVRG_AUTHORITY_MONITOR_05		=  7,		// ����ͨ��_05	_08
	DVRG_AUTHORITY_MONITOR_06		=  8,		// ����ͨ��_06	_09
	DVRG_AUTHORITY_MONITOR_07		=  9,		// ����ͨ��_07	_10
	DVRG_AUTHORITY_MONITOR_08		= 10,		// ����ͨ��_08	_11
	DVRG_AUTHORITY_MONITOR_09		= 11,		// ����ͨ��_09	_12
	DVRG_AUTHORITY_MONITOR_10		= 12,		// ����ͨ��_10	_13
	DVRG_AUTHORITY_MONITOR_11		= 13,		// ����ͨ��_11	_14
	DVRG_AUTHORITY_MONITOR_12		= 14,		// ����ͨ��_12	_15
	DVRG_AUTHORITY_MONITOR_13		= 15,		// ����ͨ��_13	_16
	DVRG_AUTHORITY_MONITOR_14		= 16,		// ����ͨ��_14	_17
	DVRG_AUTHORITY_MONITOR_15		= 17,		// ����ͨ��_15	_18
	DVRG_AUTHORITY_MONITOR_16		= 18,		// ����ͨ��_16	_19
	DVRG_AUTHORITY_REPLAY			= 19,		// �ط�         _20
	DVRG_AUTHORITY_REPLAY_01		= 20,		// �ط�ͨ��_01	_21
	DVRG_AUTHORITY_REPLAY_02		= 21,		// �ط�ͨ��_02  _22
	DVRG_AUTHORITY_REPLAY_03		= 22,		// �ط�ͨ��_03  _23
	DVRG_AUTHORITY_REPLAY_04		= 23,		// �ط�ͨ��_04  _24
	DVRG_AUTHORITY_REPLAY_05		= 24,		// �ط�ͨ��_05  _25
	DVRG_AUTHORITY_REPLAY_06		= 25,		// �ط�ͨ��_06  _26
	DVRG_AUTHORITY_REPLAY_07		= 26,		// �ط�ͨ��_07  _27
	DVRG_AUTHORITY_REPLAY_08		= 27,		// �ط�ͨ��_08  _28
	DVRG_AUTHORITY_REPLAY_09		= 28,		// �ط�ͨ��_09  _29
	DVRG_AUTHORITY_REPLAY_10		= 29,		// �ط�ͨ��_10  _30
	DVRG_AUTHORITY_REPLAY_11		= 30,		// �ط�ͨ��_11  _31
	DVRG_AUTHORITY_REPLAY_12		= 31,		// �ط�ͨ��_12  _32
	DVRG_AUTHORITY_REPLAY_13		= 32,		// �ط�ͨ��_13  _33
	DVRG_AUTHORITY_REPLAY_14		= 33,		// �ط�ͨ��_14  _34
	DVRG_AUTHORITY_REPLAY_15		= 34,		// �ط�ͨ��_15  _35
	DVRG_AUTHORITY_REPLAY_16		= 35,		// �ط�ͨ��_16	_36
	DVRG_AUTHORITY_NETPREVIEW       = 36,       // NetPreview
	DVRG_AUTHORITY_NETPREVIEW_1     = 37,		// NetPreview_CH01
	DVRG_AUTHORITY_NETPREVIEW_2     = 38,		// NetPreview_CH02
	DVRG_AUTHORITY_NETPREVIEW_3     = 39,		// NetPreview_CH03
	DVRG_AUTHORITY_NETPREVIEW_4     = 40,		// NetPreview_CH04
	DVRG_AUTHORITY_NETPREVIEW_5     = 41,		// NetPreview_CH05
	DVRG_AUTHORITY_NETPREVIEW_6     = 42,		// NetPreview_CH06
	DVRG_AUTHORITY_NETPREVIEW_7     = 43,		// NetPreview_CH07
	DVRG_AUTHORITY_NETPREVIEW_8     = 44,		// NetPreview_CH08
	DVRG_AUTHORITY_NETPREVIEW_9     = 45,		// NetPreview_CH09
	DVRG_AUTHORITY_NETPREVIEW_10    = 46,		// NetPreview_CH10
	DVRG_AUTHORITY_NETPREVIEW_11    = 47,		// NetPreview_CH11
	DVRG_AUTHORITY_NETPREVIEW_12    = 48,		// NetPreview_CH12
	DVRG_AUTHORITY_NETPREVIEW_13    = 49,		// NetPreview_CH13
	DVRG_AUTHORITY_NETPREVIEW_14    = 50,		// NetPreview_CH14
	DVRG_AUTHORITY_NETPREVIEW_15    = 51,		// NetPreview_CH15
	DVRG_AUTHORITY_NETPREVIEW_16    = 52,		// NetPreview_CH16
	DVRG_AUTHORITY_RECORD			= 53,		// ¼��			
	DVRG_AUTHORITY_BACKUP			= 54,		// ����			
	DVRG_AUTHORITY_HARDISK			= 55,		// Ӳ�̹���     
	DVRG_AUTHORITY_PTZ				= 56,		// ��̨����		
	DVRG_AUTHORITY_ACCOUNT			= 57,		// �û��ʺ�		
	DVRG_AUTHORITY_SYSINFO			= 58,		// ϵͳ��Ϣ     
	DVRG_AUTHORITY_ALARM			= 59,		// ������IO/����
	DVRG_AUTHORITY_CONFIG			= 60,		// ϵͳ����     	
	DVRG_AUTHORITY_LOG_QUERY		= 61,		// ��ѯ��־     
	DVRG_AUTHORITY_LOG_DEL			= 62,		// ɾ����־		
	DVRG_AUTHORITY_UPDATE			= 63,		// ϵͳ����		
	DVRG_AUTHORITY_CONTROL			= 64,		// ����Ȩ		
	DVRG_AUTHORITY_AUTOMAINTAIN		= 65,		// �Զ�ά��		
	DVRG_AUTHORITY_GENERALCONF		= 66,		// ��ͨ����
    DVRG_AUTHORITY_ENCODECONF		= 67,		// ��������
    DVRG_AUTHORITY_RECORDCONF		= 68,		// ¼������
    DVRG_AUTHORITY_COMCONF			= 69,		// ��������
    DVRG_AUTHORITY_NETCONF			= 70,		// ��������
    DVRG_AUTHORITY_ALARMCONF		= 71,		// ��������
    DVRG_AUTHORITY_VIDEOCONF		= 72,		// ��Ƶ���
    DVRG_AUTHORITY_PTZCONF			= 73,		// ��̨����
    DVRG_AUTHORITY_OUTPUTCONF		= 74,		// ���ģʽ
    DVRG_AUTHORITY_DEFAULTCONF		= 75,		// �ָ�Ĭ��
	DVRG_AUTHORITY_FORMAT           = 76,       // ��ʽ��

	DVRG_AUTHORITY_ITEMS			,			// ����������
};

typedef struct  
{
	BYTE bAuthorityInfo[MAX_AUTHORITY_NUM];
//	DWORD dwReserved[256];
}DVR_AUTHORITY_INFO;

//��ƵOSD��������
#define VIDEO_OSD_NAME_NUM 64		// ���ӵ����Ƴ��ȣ�Ŀǰ֧��32��Ӣ�ģ�16������
#define VIDEO_CUSTOM_OSD_NUM 8		// ֧�ֵ��Զ�����ӵ���Ŀ��������ʱ���ͨ��
//��Ƶ����ṹ
typedef struct { 

	DWORD	rgbaFrontground;		/*!< �����ǰ��RGB����͸���� */	
	DWORD	rgbaBackground;			/*!< ����ĺ�RGB����͸����*/	
	RECT	rcRelativePos;			/*!< ����߾��������ı���*8191 */	
	BOOL	bPreviewBlend;			/*!< Ԥ������ */	
	BOOL	bEncodeBlend;			/*!< ������� */
} DVR_VIDEO_WIDGET;

typedef struct tagCONFIG_VIDEOITEM
{
	DVR_VIDEO_WIDGET   OSD_POS; ///< OSD���ӵ�λ�úͱ���ɫ
	char OSD_NAME[VIDEO_OSD_NAME_NUM]; ///< OSD���ӵ�����
}DVR_CONFIG_VIDEOITEM;
 
//! ÿ��ͨ����OSD��Ϣ
typedef struct tagCONFIG_VIDEOOSD
{
	DVR_CONFIG_VIDEOITEM TimeTitle;      ///< ʱ�����
	DVR_CONFIG_VIDEOITEM ChannelTitle; ///< ͨ������
	DVR_CONFIG_VIDEOITEM OSD_TITLE[VIDEO_CUSTOM_OSD_NUM]; ///< �Զ�����ӵ�OSD
}DVR_CONFIG_VIDEOOSD;

//������Ҫ¼����Ϣ
typedef struct _REC_FB						        /*1*/
{
	unsigned char usCardNo	:4;					/* ���� */
	unsigned char usAorV	:2;				    /* 01����Ƶ��10����Ƶ��00��ͼƬ */
	unsigned char usAlarm	:2;					/* 00����ͨ�ļ���01�������ļ�,10����̬��ⱨ����11��ý���ļ��ж� */
}REC_FS;

typedef struct _REC_DIRINFO
{
	REC_FS		  DirInfo;					//����Ϣ
	FRAME_TIME	      DirStartTime;				//��ʼʱ��
	FRAME_TIME	      DirEndTime;				//����ʱ��
	unsigned int  FileSize;
	unsigned int  StartCluster;
	unsigned char DriveNo;
    unsigned char HInt;
	unsigned char ImportantRecID;			//0:��ͨ¼�� 1:��Ҫ¼��				
	unsigned char Reserved;					//����
}IMPORTANT_REC_DIRINFO;


typedef struct __DEVICE_MESS_CALLBACK 
{
	void*		fun;
	void*		data;
}DEVICE_MESS_CALLBACK;

typedef struct __MESS_CALLBACK_DATA 
{
	int			nResultCode;
	char		*pBuf;
	int			nBufLen;
	LONG		lOperateHandle;
	void*		userparam;
	void*		cbMessFunc;
	void*		userdata;
	void*		pRecvEvent;
	int			*pRetLen;
	int			*pResult;
	int         nDvrRestart;
	int			*pDvrRestart;	
} MESS_CALLBACK_DATA;

// �����������TV
typedef struct __REQUEST_DEC_CTRLTV 
{
	int			nMonitorID;
	int			nSplitType;
	BYTE		*pEncoderChannel;
	int			nBufLen;
	BOOL		bEnable;
} REQUEST_DEC_CTRLTV;

// ��������л�TVͼ��
typedef struct __REQUEST_DEC_SWITCHTV 
{
	int			nEncoderID;
	char		szDevIp[64];
	WORD		wDevPort;
	WORD		wEnable;
	char		szDevUser[16];
	char		szDevPwd[16];
	int			nDevChannel;
	int			nStreamType;
	BYTE		byConnType;
	BYTE		byWorkMode;
	WORD		wListenPort;
	DWORD		dwProtoType;
	char		szDevName[128];
	BYTE		byVideoInType;
	BYTE        bySnapMode;
	BYTE        byManuFactory;
	BYTE        byDeviceType;
} REQUEST_DEC_SWITCHTV;

// ����������ӻ������
typedef struct __REQUEST_DEC_ADD_COMBIN 
{
	int			nMonitorID;
	int			nSplitType;
	BYTE		*pEncoderChannnel;
	int			nBufLen;
} REQUEST_DEC_ADD_COMBIN;

// �������ɾ���������
typedef struct __REQUEST_DEC_DEL_COMBIN 
{
	int			nMonitorID;
	int			nCombinID;
} REQUEST_DEC_DEL_COMBIN;

// ��������޸Ļ������
typedef struct __REQUEST_DEC_SET_COMBIN 
{
	int			nCombinID;
	int			nMonitorID;
	int			nSplitType;
	BYTE		*pEncoderChannnel;
	int			nBufLen;
} REQUEST_DEC_SET_COMBIN;

// ����������ý�������Ѳ
typedef struct __REQUEST_DEC_SET_TOUR
{
	int			nMonitorID;
	int			nTourTime;
	BYTE		*pTourCombin;
	BYTE		*pCombinState;
	int			nCombinCount;
} REQUEST_DEC_SET_TOUR;

// �����������TV���ʹ��
typedef struct __REQUEST_DEC_SET_TVENABLE
{
	BYTE		*pSetTVEnable;
	int			nBuflen;
} REQUEST_DEC_SET_TVENABLE;

// ����������ļ��ط�ǰ���豸
typedef struct __REQUEST_DEC_DEVBYFILE 
{
	int			nEncoderID;
	char		szDevIp[32];
	WORD		wDevPort;
	WORD		wEnable;
	char		szDevUser[16];
	char		szDevPwd[16];
	unsigned int nChannelID;
	unsigned int nFileSize;
    unsigned int driveno;
    unsigned int startcluster;
	BYTE		nRecordFileType;
	BYTE		bImportantRecID;
	BYTE		bHint;
	BYTE		bReserved;
	FRAME_TIME		startTime;
    FRAME_TIME		endTime;
} REQUEST_DEC_DEVBYFILE;

// ���������ʱ��ط�ǰ���豸
typedef struct __REQUEST_DEC_DEVBYTIME 
{
	int			nEncoderID;
	char		szDevIp[32];
	WORD		wDevPort;
	WORD		wEnable;
	char		szDevUser[16];
	char		szDevPwd[16];
	unsigned int nChannelID;
    FRAME_TIME		startTime;
    FRAME_TIME		endTime;
} REQUEST_DEC_DEVBYTIME;

// ��������������طſ���
typedef struct __REQUEST_DEC_SET_PLAYBACK
{
	int			nType;
	int			nEncoderNum;
	int			nValue;
} REQUEST_DEC_SET_PLAYBACK;

// ��������޸�IP��ַ����
typedef struct __REQUEST_SET_IPFILTER 
{
	int			nEnable;
	int			nType;
	int			nBlackIpNum;
	char		szBlackIp[200][16];
	int			nTrustIpNum;
	char		szTrustIp[200][16];
} REQUEST_SET_IPFILTER;

// �����������IP��ַ����
typedef struct __REQUEST_ADD_IPFILTER 
{
	int			nEnable;
	int			nType;
	char		szIp[16];
	char		szListStart[16];
	char		szListEnd[16];
} REQUEST_ADD_IPFILTER;

// ��������޸������Խ���������
typedef struct __REQUEST_SET_TALKENCODE 
{
	int			nCompression;//ѹ����ʽ
	int			nFrequency;  //����Ƶ��
	int			nDepth;		//�������
	int			nPacketPeriod;//�������
	int			nMode;		//����ģʽ
} REQUEST_SET_TALKENCODE;

// ��������޸�¼������������
typedef struct __REQUEST_SET_RECORDLEN 
{
	int			nType;		//��ʱ�仹�ǰ���С0:��ʱ�䣬1������С
	int			nValue;		//¼���ļ���СKB
} REQUEST_SET_RECORDLEN;

// ��������޸�MMS
typedef struct __REQUEST_SET_MMS
{
	int			nEnable;
	int			nReceiverNum;
	char		szReceiver[100][32];
	unsigned char bType;
	char		SZTitle[32*2+1];
} REQUEST_SET_MMS;

// ��������޸�SMSACTIVATION
typedef struct __REQUEST_SET_SMSACTIVATION
{

	int			nEnable;
	int			nSenderNum;
	char		szSender[100][32];
} REQUEST_SET_SMSACTIVATION;

// ��������޸�DIALINACTIVATION
typedef struct __REQUEST_SET_DIALINACTIVATION
{
	int			nEnable;
	int			nCallerNum;
	char		szCaller[100][32];
} REQUEST_SET_DIALINACTIVATION;

typedef struct __REQUEST_SET_BURNFILE
{
	DWORD		dwConID;
	char		szFileName[MAX_PATH_STOR];
	int			nFileSize;
}REQUEST_SET_BURNFILE;

// ��������޸�VideoOut����
typedef struct __REQUEST_SET_VIDEOOUT 
{
	int        nVideoStander; //��Ƶ��ʽ
	int        nImageSize;//�ֱ���
}REQUEST_SET_VIDEOOUT;

/* ��½���� */
typedef struct __login_attribute
{
	/* �Ƿ�����½�豸����ʹ�ã� 0��Ҫ��½��1�����ص�½ */
	BYTE	iShouldLogin;
	/* ֧�ֵĵ�½�û�����󳤶� */
	BYTE	iUNameMaxLen;
	/* ֧�ֵ�������󳤶� */
	BYTE	iUPwdMaxLen;
	/* ֧�ֵļ��ܷ�ʽ */
	BYTE	iEncryptType;/* �ӵ͵��ߣ���λ��ʾ���ܷ�ʽ��0-3des, */
	BYTE	iReserved[28];/* ���� */
}LOGIN_ATTRIBUTE;

// ��������޸�TV���ڲ���
typedef struct __REQUEST_SET_TVADJUST 
{
	int                 nTVID;
	int					nTop;							// �ϲ�߾ࣨ0��100��
	int					nBotton;						// �²�߾ࣨ0��100��
	int					nLeft;							// ���߾ࣨ0��100��
	int                 nRight;							// �Ҳ�߾ࣨ0��100��
}REQUEST_SET_TVADJUST;

//���ݼ�¼����
typedef struct __BACKUP_RECORDFILE_INFO
{
	unsigned int	nChannel;							//ͨ����		
	BYTE			byType;								//¼���ļ�����  0����ͨ¼��1������¼��2���ƶ���⣻3������¼��4��ͼƬ
	FRAME_TIME			DirStartTime;						//��ʼʱ��
	FRAME_TIME			DirEndTime;							//����ʱ��
	unsigned int	nFileSize;	
	unsigned int	nDriveNo;
	unsigned int	nStartCluster;
    unsigned int	nHInt;
	unsigned int	nImportantRecID;					//0:��ͨ¼�� 1:��Ҫ¼��				
} BACKUP_RECORDFILE_INFO;

//�����: ���ƿ�ʼ����
typedef struct __REQUEST_BACKUP_RECORD
{
	char					szDeviceName[32];			//�����豸����
	int						nRecordNum;					//���ݼ�¼����
	BACKUP_RECORDFILE_INFO	stuRecordInfo[1024];		//���ݼ�¼��Ϣ
} REQUEST_BACKUP_RECORD;

// �����������������
typedef struct __REQUEST_DEC_CONTROL
{
	int			nType; //��������:0-tour
	int         nAction;
	int			nMonitorID;
} REQUEST_DEC_CONTROL;


//�������POS��ز������ýṹ
typedef struct __REQUEST_POS_INFO
{
	int fontColor ; //0:default(white) 1:black 2:blue 3:red 4:white 5:green 6:brown 7:yellow 8:grey
	int fontSize ;  //0:8 1:16 2:24 3:32
	int fontX ;     //-1:aligh left -2:aligh right -3:align center >0:custom
	int fontY ;     //
	BYTE show ;     //0:hide 1:show
	int  holdTime ; //СƱOSD��ͣ����ʾʱ�� , (5-300) ��λ��
	char posAlarmHostAddr[16] ; //СƱ�ĸ澯��������ַ
	int  posAlarmHostPort ;
	BYTE reserved[64] ;
} REQUEST_POS_INFO ;



#endif  //_DVR2CFG_H_

