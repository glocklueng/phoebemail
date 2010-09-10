
#ifndef AFKINC_H
#define AFKINC_H


/****************************************************************************
 * ͨ������ 
 ****************************************************************************/
#define AFK_CHANNEL_TYPE_MEDIA		1		// ��ͨ��ʵʱý��ͨ��
#define AFK_CHANNEL_TYPE_SEARCH		2		// ��ѯͨ��
#define AFK_CHANNEL_TYPE_DOWNLOAD	3		// ����ͨ��
#define AFK_CHANNEL_TYPE_UPGRADE	4		// ���߸���ͨ��
#define AFK_CHANNEL_TYPE_PREVIEW	5		// Ԥ��ͨ��
#define AFK_CHANNEL_TYPE_ALARM		6		// ��������ͨ��
#define AFK_CHANNEL_TYPE_CONTROL    7       // ����ͨ��
#define AFK_CHANNEL_TYPE_CONFIG     8       // ����ͨ��
#define AFK_CHANNEL_TYPE_STATISC	9		// ͳ����Ϣͨ��
#define AFK_CHANNEL_TYPE_TRANS      10      // ͸��ͨ��
#define AFK_CHANNEL_TYPE_TALK       11      // ����ͨ��
#define AFK_CHANNEL_TYPE_USER       12      // �û�ͨ��
#define AFK_CHANNEL_TYPE_DECODE		13		// ����ͨ��
#define AFK_CHANNEL_TYPE_RENDER		14		// ��Ⱦͨ��
#define AFK_CHANNEL_TYPE_USERMSG	15		// �û�����
#define AFK_CHANNEL_TYPE_DDNS		16		// DDNS��ѯͨ��
#define AFK_CHANNEL_TYPE_CAPTURE	17		// Զ��ץͼͨ��
#define AFK_CHANNEL_TYPE_GPS        18      // GPSͨ����add by jinyx 2007/04/11
#define AFX_CHANNEL_TYPE_REQUEST	19		// ����ͨ��
#define AFX_CHANNEL_TYPE_NEWCONFIG  20		// �豸json�ַ�������ͨ��


/****************************************************************************
 * ��ѯͨ����������
 ****************************************************************************/
#define AFK_CHANNEL_SEARCH_RECORD			0		// ��ѯ¼��
#define AFK_CHANNEL_SEARCH_LOG				1		// ��ѯ�豸��־
#define AFK_CHANNEL_SEARCH_CHANNELNAME		2		// ��ѯͨ����
#define AFK_CHANNEL_SEARCH_ALARMCTRL_IN		3		// ��ѯ�������벼����
#define AFK_CHANNEL_SEARCH_ALARMCTRL_OUT	4		// ��ѯ�������������
#define AFK_CHANNEL_SEARCH_CONFIG			5		// ��ѯ�豸����
#define AFK_CHANNEL_SEARCH_RECORDSTATE		6		// ��ѯ¼��״̬
#define AFK_CHANNEL_SEARCH_DEVTIME			7		// ��ȡ�豸ʱ��
#define AFK_CHANNEL_SEARCH_COMMPROTOCOL		8		// ��ȡ����Э��
#define AFK_CHANNEL_SEARCH_DCDPROTOCOL		9		// ��ȡ������Э��
#define AFK_CHANNEL_SEARCH_SYSTEM_INFO		10		// ��ѯϵͳ��Ϣ
#define AFK_CHENNEL_SEARCH_DEVWORKSTATE		11		// ��ѯ�豸����״̬
#define AFK_CHENNEL_SEARCH_DEVSTATE			12		// ��ѯ�豸״̬����DEVWORKSTATEЭ�鲻һ��
#define AFK_CHANNEL_SEARCH_PTZ				13		// ��ѯ��̨�豸����
#define AFK_CHANNEL_SEARCH_WIRELESS_ALARMOUT 14     // ��ѯ���߱������
#define AFK_CHANNEL_SEARCH_ALARMTRRIGER_MODE 15		// ��ѯ����������ʽ
#define AFK_CHANNEL_SEARCH_TRANSCOM			 16		// ��ѯ���ڲ���

#define AFK_CHANNEL_SEARCH_DDNSIP_BYNAME	100		// ��ddns��������ѯip


/****************************************************************************
 * ����ͨ����������
 ****************************************************************************/
#define AFK_CHANNEL_CONFIG_RECORDSTATE	AFK_CHANNEL_SEARCH_RECORDSTATE
#define AFK_CHANNEL_CONFIG_ALARMCTRL	AFK_CHANNEL_SEARCH_ALARMCTRL_IN //IN&OUT
#define AFK_CHANNEL_CONFIG_CONFIG		AFK_CHANNEL_SEARCH_CONFIG
#define AFK_CHANNEL_CONFIG_DEVTIME		AFK_CHANNEL_SEARCH_DEVTIME
#define AFK_CHANNEL_CONFIG_ALARMTRRIGER_MODE	AFK_CHANNEL_SEARCH_ALARMTRRIGER_MODE
#define AFK_CHANNEL_CONFIG_LIMIT_FLUX		99		// ����������
#define AFK_CHANNEL_CONFIG_ALARMDCD_OUT		100		// �������������
#define AFK_CHANNEL_CONFIG_CHANNEL_OSD		101		// ͨ���ַ�����
#define AFK_CHANNEL_CONFIG_FORCE_IFRAME		102		// ǿ��I֡


/****************************************************************************
 * ����ͨ����������
 ****************************************************************************/
#define AFK_CHANNEL_DOWNLOAD_RECORD			0		// ����¼���ļ�
#define AFK_CHANNEL_DOWNLOAD_CONFIGFILE		1		// ���������ļ�


/****************************************************************************
 * ����ͨ����������
 ****************************************************************************/
#define AFK_CHANNEL_UPLOAD_UPGRADE			0		// ���������ļ�
#define AFK_CHANNEL_UPLOAD_CONFIGFILE		1		// ���������ļ�


/************************************************************************
 * ��ѯ���Ͷ���
 ************************************************************************/
#define AFK_SEARCH_TYPE_MEDIA		1		// ¼���ѯ
#define AFK_SEARCH_TYPE_ALARM		2		// ������ѯ
#define AFK_SEARCH_TYPE_LOG			3		// ��־��ѯ

/************************************************************************
 * �������Ͷ���
 ***********************************************************************/
#define AFK_CONTROL_TYPE_PTZ		1		// ��̨����
#define AFK_CONTROL_TYPE_YWPTZ		2		// �����������
#define AFK_CONTROL_TYPE_RESET		3		// ��������
#define AFK_CONTROL_TYPE_DEVCONTROL	4		// �豸����


/****************************************************************************
 * ����ͨ������
 ****************************************************************************/
#define AFK_REQUEST_DECODER_CTRLTV			0x00000001		// ������������TV����
#define AFK_REQUEST_DECODER_SWITCH			0x00000002		// ���������л�TVͼ��
#define AFK_REQUEST_DEC_QUERY_TV			0x00000003		// ����������ѯTV��Ϣ
#define AFK_REQUEST_DEC_QUERY_CHANNEL		0x00000004		// ����������ѯ����ͨ����Ϣ
#define AFK_REQUEST_DEC_QUERY_SYS			0x00000005		// ����������ѯ������ϵͳ��Ϣ
#define AFK_REQUEST_DEC_QUERY_CHNNUM		0x00000006		// ����������ѯ����������ͨ������
#define AFK_REQUEST_DEC_ADD_COMBIN			0x00000007		// ������������TV�������
#define AFK_REQUEST_DEC_DEL_COMBIN			0x00000008		// ��������ɾ��TV�������
#define AFK_REQUEST_DEC_SET_COMBIN			0x00000009		// ���������޸�TV�������
#define AFK_REQUEST_DEC_QUERY_COMBIN		0x0000000A		// ����������ѯTV�������
#define AFK_REQUEST_DEC_SET_TOUR			0x0000000B		// �����������ý�������Ѳ
#define AFK_REQUEST_DEC_QUERY_TOUR			0x0000000C		// ����������ѯ��������Ѳ
#define AFK_REQUEST_DEC_SET_TV_ENABLE		0x0000000D		// �����������ý�����TVʹ��
#define AFK_REQUEST_DEC_PLAYBACKBYDEC		0x0000000E		// ���������ط�ǰ���豸
#define AFK_REQUEST_DEC_CTRLPLAYBACK		0x0000000F		// ���������طſ���
#define AFK_REQUEST_DEC_CHANNEL_STATE		0x00000010		// ����������ѯ����ͨ������Ϣ
#define AFK_REQUEST_SET_VIDEOOUT			0x00000011      // ��������������Ƶ�������
#define AFK_REQUEST_DEC_CONTROL				0x00000012      // ������������

#define AFK_REQUEST_GET_IPFILTER			0x00000101		// ��ѯIP��ַ����
#define AFK_REQUEST_SET_IPFILTER			0x00000102		// �޸�IP��ַ����
#define AFK_REQUEST_ADD_IPFILTER			0x00000103		// ����IP��ַ����
#define AFK_REQUEST_DEL_IPFILTER			0x00000104		// ɾ��IP��ַ����
#define AFK_REQUEST_GET_AMRENCODE_CFG		0x00000105      // ��ѯAMR��������
#define AFK_REQUEST_SET_AMRENCODE_CFG		0x00000106      // ����AMR��������
#define AFK_REQUEST_GET_RECORDLEN_CFG		0x00000107      // ��ѯ¼������������
#define AFK_REQUEST_SET_RECORDLEN_CFG		0x00000108      // ����¼������������
#define AFK_REQUEST_AUTOREGISTER_CONNECT	0x00000109		// ����ע���ض�������
#define AFK_REQUEST_AUTOREGISTER_GETCONID	0x0000010A		// ����ע���ض��򣺻�ȡ����ע�������������ID
#define AFK_REQUEST_AUTOREGISTER_GETSERVER	0x0000010B		// ����ע���ض��򣺻�ȡ����ע���������״̬��Ϣ
#define AFK_REQUEST_AUTOREGISTER_REGSERVER	0x0000010C		// ����ע���ض�������ע��
#define AFK_REQUEST_AUTOREGISTER_DISCONNECT	0x0000010D		// ����ע���ض��򣺶Ͽ�����
#define AFK_REQUEST_GET_VIDEOFORMAT_INFO	0x0000010E      // ��ѯ�豸֧�ֵ���Ƶ��ʽ
#define AFK_REQUEST_GET_MMS_INFO			0x0000010F		// ��ѯMMS����
#define AFK_REQUEST_SET_MMS_INFO			0x00000110		// �޸�MMS����
#define AFK_REQUEST_GET_SMSACTIVE_INFO		0x00000111	    // ��ѯSMSACTIVATION����
#define AFK_REQUEST_SET_SMSACTIVE_INFO		0x00000112		// �޸�SMSACTIVATION����
#define AFK_REQUEST_GET_DIALIN_INFO			0x00000113		// ��ѯDIALINACTIVATION����
#define AFK_REQUEST_SET_DIALIN_INFO			0x00000114		// �޸�DIALINACTIVATION����
#define AFK_REQUEST_CONNECT					0x00000115		// ��������
#define AFK_REQUEST_DISCONNECT				0x00000116		// �Ͽ�����
#define AFK_REQUEST_GET_BURNFILE_TRANS		0x00000117		// ��ѯ��¼�����ļ�����
#define AFK_REQUEST_SET_BURNFILE_TRANS		0x00000118		// ���ÿ�¼�����ļ�����
#define AFK_REQUEST_GET_BURN_ATTACH			0x00000119		// ��ѯ������¼ʹ��
#define AFK_REQUEST_SET_BURN_ATTACH			0x0000011A		// ���ø�����¼ʹ��
#define AFK_REQUEST_SET_SNIFFER				0x0000011B		// �޸���Ϣ
#define AFK_REQUEST_GET_SNIFFER				0x0000011C		// ��ѯ��Ϣ
#define AFK_REQUEST_SET_DOWNLOAD_RATE		0x0000011D		// ���������ٶ�����
#define AFK_REQUEST_GET_DOWNLOAD_RATE		0x0000011E		// ��ѯ�����ٶ�����
#define AFK_REQUEST_GET_POINT_CFG			0x0000011F		// ��ȡԤ�Ƶ�����
#define AFK_REQUEST_SET_POINT_CFG			0x00000120		// ����Ԥ�Ƶ�����
#define AFK_REQUEST_GET_OSDENABLE_CFG		0x00000121		// ����OSD����ʹ��
#define AFK_REQUEST_SET_OSDENABLE_CFG		0x00000122		// ��ȡOSD����ʹ��
#define AFK_REQUEST_LOGOUT					0x00000123		// �ǳ�֪ͨ�豸
#define AFK_REQUEST_GET_TVADJUST_CFG        0x00000124      // ��ȡTV���ڲ���
#define AFK_REQUEST_SET_TVADJUST_CFG        0x00000125      // ����TV���ڲ���
#define AFK_REQUEST_FUNCTION_MASK			0x00000126		// �����б�
#define AFK_REQUEST_GET_VEHICLE_CFG			0x00000127		// ��ȡ��������
#define AFK_REQUEST_SET_VEHICLE_CFG			0x00000128		// ���ó�������
#define AFK_REQUEST_GET_ATM_OVERLAY_ABILITY 0x00000129		// ��ȡatm��������
#define AFK_REQUEST_GET_ATM_OVERLAY_CFG		0x0000012a		// ��ȡatm��������
#define AFK_REQUEST_SET_ATM_OVERLAY_CFG		0x0000012b		// ����atm��������
#define AFK_REQUEST_QUERY_BACKUP_DEV		0x0000012c		// ��ѯ�����豸�б�
#define AFK_REQUEST_QUERY_BACKUP_DEV_INFO	0x0000012d		// ��ѯ�����豸��ϸ��Ϣ
#define AFK_REQUEST_BACKUP_START			0x0000012e		// ��ʼ����
#define AFK_REQUEST_BACKUP_STOP				0x0000012f		// ֹͣ����
#define AFK_REQUEST_BACKUP_FEEDBACK			0x00000130		// ���ݽ��ȷ���
#define AFK_REQUEST_ATM_TRADE_TYPE			0x00000131		// ATM�豸��������
#define AFK_REQUEST_GET_DECODER_TOUR_CFG	0x00000132		// ��ȡ������Ѳ����
#define AFK_REQUEST_SET_DECODER_TOUR_CFG	0x00000133		// ���ý�����Ѳ����	
#define AFK_REQUEST_GET_SIP_CFG				0x0000013c		// ��ȡSIP����
#define AFK_REQUEST_SET_SIP_CFG				0x0000013d		// ����SIP����
#define AFK_REQUEST_GET_SIP_ABILITY			0x0000013e		// ��ȡSIP����
#define AFK_REQUEST_GET_SIP_STATE			0x0000013f		// ��ȡSIP״̬

#define AFK_REQUEST_GET_NEWCONFIG_CFG		0x00000134		// ��ȡ�豸���ã��µ��ַ���Э�飩
#define AFK_REQUEST_SET_NEWCONFIG_CFG		0x00000135		// �����豸���ã��µ��ַ���Э�飩

#define AFK_REQUEST_GET_POS_CFG             0x00000140      // ��ȡPOS����
#define AFK_REQUEST_SET_POS_CFG             0x00000141      // ����POS����

/****************************************************************************
 * ����ͨ��������
 ****************************************************************************/
#define AFK_REQUEST_DEC_BYDECBYFILE			0x00000001		// �����������ļ��ط�ǰ���豸
#define AFK_REQUEST_DEC_BYDECBYTIME			0x00000002		// ����������ʱ��ط�ǰ���豸


/************************************************************************
 * �������
 ***********************************************************************/
typedef void * afk_handle_t;
typedef struct afk_time_s afk_time_t;
typedef struct afk_channel_param_s afk_channel_param_t;
typedef struct afk_media_channel_param_s afk_media_channel_param_t;
typedef struct afk_search_channel_param_s afk_search_channel_param_t;
typedef struct afk_download_channel_param_s afk_download_channel_param_t;
typedef struct afk_upgrade_channel_param_s afk_upgrade_channel_param_t;
typedef struct afk_preview_channel_param_s afk_preview_channel_param_t;
typedef struct afk_alarm_channel_param_s afk_alarm_channel_param_t;
typedef struct afk_control_channel_param_s afk_control_channel_param_t;
typedef struct afk_config_channel_param_s afk_config_channel_param_t;
typedef struct afk_user_channel_param_s afk_user_channel_param_t;
typedef struct afk_alarm_trriger_mode_s afk_alarm_trriger_mode_t;


/************************************************************************
 * ���ڲ�ʹ����ؽṹ�嶨��
 ***********************************************************************/
struct afk_time_s
{
	int				year;			// ��
	int				month;			// ��
	int				day;			// ��
	int				hour;			// Сʱ
	int				minute;			// ����
	int				second;			// ��
};

/* �豸ʱ����Ϣ */
struct afk_devicetime_info_s
{
    int				year;
    int				month;
    int				day;
    int				hour;
    int				minute;
    int				second;
};

/* ��ѯ�ļ�������Ϣ */
struct afk_query_record_s
{
    unsigned int	ch;				// ͨ����
    unsigned int	type;			// 0:����¼��  1:�ⲿ���� 2:��̬��� 3:���б��� 4:����
    afk_time_s		starttime;		// ��ʼʱ��
    afk_time_s		endtime;		// ����ʱ��
    char			cardid[255];	// ����
    bool			bytime;			// ��ʱ���ѯ
};

/* ¼���ļ���Ϣ */
struct afk_record_file_info_s
{
    unsigned int	ch;				// ͨ����
    char			filename[128];	// �ļ���
    unsigned int	size;			// �ļ�����
    afk_time_s		starttime;		// ��ʼʱ��
    afk_time_s		endtime;		// ����ʱ��
    unsigned int	driveno;		// ���̺�
    unsigned int	startcluster;	// ��ʼ�غ�
	unsigned char	nRecordFileType;// ¼���ļ�����
	unsigned char	ImportantRecID;	// 0:��ͨ¼�� 1:��Ҫ¼��
	unsigned char	Hint;			// �ļ�����
	unsigned char   Reserved;		// ����
};

/* ����״̬��Ϣ */
struct afk_state_info_s
{   
	int				channelcount;
	int				alarminputcount;
	unsigned char	alarm[16];
	unsigned char	motiondection[16];
	unsigned char	videolost[16];
	unsigned char   PosTick[16];
};
    
/* �������������Ϣ */
struct afk_alarm_info_s
{
    bool			isinput;		// �Ƿ񱨾�����
    unsigned int	count;			// ����
    unsigned char*	state;			// size:count
	bool			bSupportTriggerMode;// �Ƿ�֧�ֱ���������ʽ
};

/* �������������ʽ*/
struct afk_alarm_trriger_mode_info
{
	unsigned char	mode;			// ������ʽ
};

struct afk_alarm_trriger_mode_s
{
	unsigned char	channel_count;	// Ҫ���õ�ͨ����
	afk_alarm_trriger_mode_info trriger_mode[16];// ������ʽ
};

/* ����������Ϣ */
struct afk_alarm_control_info_s
{
//	bool			isinput;		// �Ƿ񱨾�����
	unsigned char	type;			// ��������
    unsigned int	alarmid;		// ����ID
    bool			controlflag;	// �������Ʊ�־
};

struct afk_decoder_alarm_info_s
{
	int				decoderNo;		// ������������
	unsigned short	alarmChn;		// ���������
	unsigned short	alarmState;		// �������״̬
};

/* ���������Ϣ */
struct afk_config_info_s
{
    unsigned char*	configbuf;
    int				buflen;
};

/* ǿ��IA�� */
struct afk_channel_getIframe_info_s
{
	unsigned char	subchn;			// 0x00 ������1, 0x01 ��������2,0x02	��������3,0x03 ��������4,0x04 ��JPEGץͼ
};

/* ͸�����ڷ�����Ϣ */
struct afk_trans_info_s
{
    char*			data;			// ����ָ��
    int				datalen;		// ���ݳ���
};

/* �Խ�������Ϣ */ 
struct afk_talk_info_s
{
    char*			data;			// ����ָ��
    int				datalen;		// ���ݳ���
};


/* set_info, get_info types. */
#define SP_USER_REUSABLE			0x01	// �Ƿ�֧���û�����
#define SP_NEW_CHANNAME				0x02	// �Ƿ�ʹ���µ�ͨ����Э��
#define SP_NEW_RECORDPROTOCOL		0x03	// �Ƿ�֧���µ�¼��ͼƬ�б��ѯ��ʽ
#define SP_NEW_LOGPROTOCOL			0x04	// �Ƿ�֧���µ���־��ʽ��ѯ
#define SP_NEW_MULTIDDNSPRO			0x08	// �Ƿ�֧�ִ�������Ϣ�Ķ�DDNSЭ��

typedef enum 
{
	dit_special_cap_flag = 0,	// ����������־,param = DWORD*������λ��ʾ
	dit_protocol_version,		// Э��汾��
	dit_talk_encode_type,		// �Խ���������
	dit_recordprotocol_type,	// ¼���ѯ������־
	dit_logprotocol_type,		// ��־��ѯ������־
	dit_session_id,				// ���ε�¼��session id
	// ���豸��������Ϣ
	dit_ether_flag,				// ����֧�����
	dit_talk_use_mode,			// �Խ�ʹ��ģʽ(�ͻ��˺ͷ�����)
	dit_card_query,				// ���Ų�ѯ
	dit_alarmin_num,			// �����������
	dit_talk_encode_list,		// �Խ������б�
	dit_audio_alarmin_num,      // ��Ƶ��ⱨ���������
	dit_dev_type,				// �豸����
	dit_alarm_listen_use_mode,	// ����������ģʽ0-16
	dit_multiplay_flag,			// �໭��Ԥ������
	dit_heart_beat,				// ���豸����������
	dit_device_task,			// �Ƿ��������־
	dit_execute_task,			// ��������
	dit_online_flag,			// �Ƿ�����
	dit_config_authority_mode,  // ����Ȩ��
	dit_user_name,              // �û���
	dit_set_callback,			// �����첽�ص�����
	dit_asyn_timeout,			// �첽��ⳬʱ
//	dit_partition_ver,			// ����Э��汾��
//	dit_support_partition,		// ֧�ַ�������
	dit_firstqueryrecord_flag,	// ��Ҫ¼���ѯ��ʶ�ǵ�һ�β�ѯ��param(0����ͨ¼�������Ҫ¼��ĵ�һ�β�ѯ��1����Ҫ¼��ķǵ�һ�β�ѯ)
	dit_nvd_playback_flag,		// �������طŽ��Ȼص�
	dit_svr_alarm_flag,			// SVR����״̬
	dit_ether_info,             // ������Ϣ�������������Ƶļ�¼
	dit_login_device_flag,		// ���õ��뷽ʽ
	dit_quick_config,           // �Ƿ�֧�ֿ��ٶ�ȡ����
	dit_cleanres_flag,			// ����������Դ
} afk_device_info_type;

typedef struct
{
    int			type;
    int			channelcount;
    int			alarminputcount;
    int			alarmoutputcount;
    int			version;
    BOOL		ispal;
    BOOL		istrans;
    int			enctype;		// 8:mpeg4, 9:H.264
    BOOL		istalk;			// �Խ�
    BOOL		ispreview;		// �໭��Ԥ��
	char		szDevType[256]; // �豸����
	BOOL		bAutoRegister;	// �Ƿ�����ע�����
} afk_dvrdevice_info;

typedef enum
{
	EM_SEND_LOGINPACKET,
	EM_WAIT_LOGINACK,
	EM_PARSE_LOGINACK,
	EM_RECONN_SUBCONN,
	EM_WAIT_SUBCONN,
	EM_SEND_REALPACKET,
	EM_DYNAMIC_SUBCONN,
} AUTO_CONN_STATUS;

typedef enum 
{
	channel_request_param = 0,
	channel_detect_timeout,
	channel_protocoltype,
	channel_packetsequence,
} afk_channel_info_type;

typedef enum
{
	channel_connect_tcp = 0,
	channel_connect_udp,
	channel_connect_multicast,
} afk_channel_connect;

typedef struct  
{
	char		szRemoteIp[32];
	int			nRemotePort;
	int			nLoginMode;
} afk_login_device_type;



/************************************************************************
 * ��ͨ���Ĳ�������, ��ͨ������һһ��Ӧ
 ************************************************************************/
typedef int (__stdcall *afk_callback)(
	afk_handle_t object,	/* �����ṩ�� */
	unsigned char *data,	/* ������ */
	unsigned int datalen,	/* ���ݳ��� */
	void *param,			/* �ص����� */
	void *udata
);

struct afk_channel_param_s
{
	afk_callback		func;			// �ص�����
	void*				udata;			// �û�����
};

struct afk_connect_param_t 
{
	char				szSevIp[32];
	char				szLocalIp[32];
	int					nSevPort;
	int					nLocalPort;
	unsigned int		nConnectID;
	int					nConnBufSize;
	int					nConnTime;
	int					nTryTime;
	int					nConnType;
	int					nInterfaceType;
	int					nParam;
	void*				userdata;
};

struct afk_media_channel_param_s
{
	afk_channel_param_t base;			// ��������
	afk_connect_param_t conn;			// ������Ϣ
	int					no;				// ͨ����
	int					subtype;		// ������������
};

struct afk_preview_channel_param_s
{
	afk_channel_param_t	base;			// ��������
	afk_connect_param_t conn;			// ������Ϣ
	int					parm1;			// Ԥ������1, ��ͬ��˾��Ʒ, ������һ��
	int					parm2;			// Ԥ������2, ��ͬ��˾��Ʒ, ������һ��
};

struct afk_search_channel_param_s
{
	afk_channel_param_t base;	        // ��������
	int					no;	            // ͨ����
    int					type;	        // ��ѯ����
    /* 0:��ѯ¼�� 1:��ѯ��־ 2:��ѯͨ���� 3:��ѯ�������������� 4:��ѯ�������������
		5:��ͨ���� 6:COM������ 7:�������� 8:��ʱ���� 9:ͼ������ 10:PTZ���� 11:��̬������� 12:�������� */
	/* for DDNS only: 0�������ֲ�ѯIP��1�������кŲ�ѯIP */
	int					subtype;		// ������

	int					statetype;		// ��ѯ������״̬����
	afk_query_record_s	queryrecord;	// ��ѯ¼������
	int					querydevstate;	// ��ѯ�豸״̬ 0 ��ѯ�豸״̬�� 1 ��ѯͨ��״̬
	char*				webName;
	int					webNamelen;
	int					param;
};

struct afk_download_channel_param_s
{
	afk_channel_param_t	base;			// ��������
	afk_connect_param_t conn;			// ������Ϣ
	afk_record_file_info_s info;		// ¼���ļ���Ϣ
	int					nByTime;		// ��ʱ��ط�
	int					nParam;			// ��չ������0���طţ�1������
	int					type;
	int					subtype;
};

struct afk_upgrade_channel_param_s
{
	afk_channel_param_t base;			// ��������
	char				filename[256];	// �ϴ����ļ�·��
    int					filetype;		// �ϴ����ļ�����
    int					size;			// �ϴ����ļ���С
	int					type;
	int					subtype;
};

struct afk_alarm_channel_param_s
{
    afk_channel_param_t	base;			// ��������
	int					parm;			// ���ֲ�ͬЭ��ı�������
};

struct afk_raw_channel_param_s
{
    afk_channel_param_t base;			// ��������
};

/* ͨ��������Ϣ */
struct afk_channelname_info_s
{
    char				channelname[16][16];
};

struct afk_config_channel_param_s 
{
    afk_channel_param_t	base;			// ��������
    int					no;				// ͨ����
    int					type;			// ��ѯ����
    /* 0:ͨ���� 1:���������� 2:��ͨ���� 3:COM������ 4:�������� 5:��ʱ����
		6:ͼ������ 7:PTZ���� 8:��̬������� 9:�������� */
	int					subtype;		// ������
	
	afk_channelname_info_s	chnameinfo;	// ͨ��������
    afk_alarm_control_info_s alarminfo;	// ����������
	afk_decoder_alarm_info_s decoderalarm; // �������������
    afk_config_info_s	configinfo;		// ���ò���
    afk_devicetime_info_s	devicetimeinfo; // �豸ʱ�����
	afk_channel_getIframe_info_s chngetIframe; // ǿ��I��
	unsigned short		limitflux;		// ��������
	int					param[10];
	afk_alarm_trriger_mode_t alarmtrrigermode; // �������������ʽ
};

struct afk_control_channel_param_s
{
	afk_channel_param_t	base;			// ��������
    int					no;				// ͨ����
    int					type1;			// ��������1
    int					type2;			// ��������2
    int					parm1;			// ���Ʋ���1
    int					parm2;			// ���Ʋ���2
    int					parm3;			// ���Ʋ���3
	char*				pParm4;			// ���Ʋ���4
};

struct afk_trans_channel_param_s
{
    afk_channel_param_t base;			// ��������
    unsigned char		trans_device_type; // ͸��ͨ������ 0:���� 1:485
    unsigned char		baudrate;		// ������
    unsigned char		databits;		// ����λ
    unsigned char		stopbits;		// ֹͣλ
    unsigned char		parity;			// ����λ
};

struct afk_download_control_param_s
{
    unsigned int		offsettime;
    unsigned int		offsetdata;
};

struct afk_talk_channel_param_s
{
    afk_channel_param_t base;			// ��������
    int					no;				// ͨ����
	int					nEncodeType;	// �����ʽ
	int					nAudioBit;		// λ��
	unsigned int		dwSampleRate;	// ������
};

struct afk_user_channel_param_s
{
    afk_channel_param_t base;			// ��������
    int					type;			// �û���������
    char*				userbuf;		// ����ָ��
    int					buflen;			// ���ݳ���
};

struct afk_usermsg_channel_s
{
	afk_channel_param_t	base;			// ��������
	char*				msg;			// ��Ϣ
	int					msglen;			// ��Ϣ����
};

/* ץͼ���� */
struct afk_capture_channel_param_s
{
	afk_channel_param_t	base;			// ��������
	int					channo;			// ͨ����
	int					pipeno;			// ��ˮ��
	int					parm;			// �Զ������
};

struct afk_device_base_s
{
	unsigned long		type;
	afk_callback		func;			// �ص�����
	void*				udata;			// �û�����
};

struct afk_remote_control_s
{
	afk_device_base_s	base;
};

struct afk_cb_media_parm_s
{
	afk_handle_t		dev;			// �豸���
};


typedef void(__stdcall *SnapPictureRevCallback)(long lLoginID, unsigned char *pBuf, 
												unsigned int RevLen, unsigned int EncodeType,
												unsigned long CmdSerial, unsigned long dwUser);

struct afk_snap_channel_param_s
{
	afk_channel_param_t base;	        // ��������
	int					no;		        // ͨ����
	int					subtype;		// ������������
	
	SnapPictureRevCallback snapcallback;// ץͼ�ص�
	long				dwLoginID;		// �豸���,����snapcallback��dwILoginID
	unsigned long		dwuser;			// ����snapcallback��dwUser
};

typedef void (__stdcall *GPSRevCallback)(long ILongID,char strgps[],
										 long lenth,unsigned long dwuser);

struct afk_gps_channel_param_s
{
	afk_channel_param_t	base;			// ��������
	GPSRevCallback		callback;		// GPS�ص�
	long				LoginId;		// �豸���
	unsigned long		dwuser;			// �û�����
    unsigned long		keeptime;		// ����ʱ��
	unsigned long		InterlTime;		// ���ͼ��
	long				active;			// �Ƿ���
};

/* ����ͨ������ */
struct afk_request_channel_param 
{
	// ������Ϣ
	afk_channel_param_t	base;			// �ڲ��ص������ڽ�������䵽�û�������
	int					nSequence;		// �������к�
	int					nType;			// ��������
	int					nSubType;		// ����������
	void*				pCondition;		// ��������
	// ��������
	char*				pRecvBuf;		// ���ջ���
	int					nBufLen;		// ���峤��
	// �첽��Ϣ
	void*				userparam;		// �û�����
	void*				callbackFunc;	// �ⲿ�ص�����ָ��
	void*				userdata;		// �ⲿ�ص��û�����
	// ͬ����Ϣ
	void*				pRecvEvent;		// ���յ�����֪ͨ�¼�
    int*				pResultCode;	// ������
	int*				pRetLen;		// ���ճ���
};

/* ������ͨ������ */
struct afk_newconfig_channel_param 
{
	// ������Ϣ
	afk_channel_param_t	base;			// �ڲ��ص������ڽ�������䵽�û�������
	int					nSequence;		// �������к�
	int					nType;			// ��������
	int					nSubType;		// ����������
	void*				pCondition;		// ��������
	// ��������
	char*				pRecvBuf;		// ���ջ���
	int					nBufLen;		// ���峤��
	// �첽��Ϣ
	void*				userparam;		// �û�����
	void*				callbackFunc;	// �ⲿ�ص�����ָ��
	void*				userdata;		// �ⲿ�ص��û�����
	// ͬ����Ϣ
	void*				pRecvEvent;		// ���յ�����֪ͨ�¼�
    int*				pResultCode;	// ������
	int*				pDvrRestart;	// �豸������־
	int*				pRetLen;		// ���ճ���
};



#endif /* AFKINC_H */




