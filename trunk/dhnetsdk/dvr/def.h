
#ifndef DVR_DEF_H
#define DVR_DEF_H

#define HEADER_SIZE  32

// ��ö������䶯����netsdk.h��ҲӦ����Ӧ�䶯 linjy-2006-12-16
enum ServerType
{
	PRODUCT_NONE = 0,
    PRODUCT_DVR_NONREALTIME_MACE,	// ��ʵʱMACE
	PRODUCT_DVR_NONREALTIME,			// ��ʵʱ
	PRODUCT_NVS_MPEG1,				// ������Ƶ������
	PRODUCT_DVR_MPEG1_2,				// MPEG1��·¼���
	PRODUCT_DVR_MPEG1_8,				// MPEG1��·¼���
	PRODUCT_DVR_MPEG4_8,				// MPEG4��·¼���
	PRODUCT_DVR_MPEG4_16,			// MPEG4ʮ��·¼���
	PRODUCT_DVR_MPEG4_SX2,			// MPEG4����ʮ��·¼���
	PRODUCT_DVR_MEPG4_ST2,			// MPEG4��ͨ¼���
	PRODUCT_DVR_MEPG4_SH2,			// MPEG4�Ӻ�¼���
    PRODUCT_DVR_MPEG4_GBE,			// MPEG4��ͨ������ǿ��¼���
    PRODUCT_DVR_MPEG4_NVSII,			// MPEG4������Ƶ������II��
	PRODUCT_DVR_STD_NEW,				// �±�׼����Э��
	PRODUCT_DVR_DDNS,				// DDNS������
	PRODUCT_DVR_ATM,					// ATM��
	PRODUCT_NB_SERIAL,				// ������ʵʱNBϵ�л���
	PRODUCT_LN_SERIAL,				// LNϵ�в�Ʒ
	PRODUCT_BAV_SERIAL,				// BAVϵ�в�Ʒ
	PRODUCT_SDIP_SERIAL,				// SDIPϵ�в�Ʒ
	PRODUCT_IPC_SERIAL,				// IPCϵ�в�Ʒ
	PRODUCT_NVS_B,					// NVS Bϵ��
	PRODUCT_NVS_C,					// NVS Hϵ��
	PRODUCT_NVS_S,					// NVS Sϵ��
	PRODUCT_NVS_E,					// NVS Eϵ��
	PRODUCT_DVR_NEW_PROTOCOL,		// ��Э��
	PRODUCT_NVD_SERIAL,				// ������
	PRODUCT_DVR_N5,					// N5
	PRODUCT_DVR_MIX_DVR,				// ���DVR
	PRODUCT_SVR_SERIAL,				// SVR
	PRODUCT_SVR_BS,					// SVR-BS
	PRODUCT_NVR_SERIAL,				// NVR
};

#endif // DVR_DEF_H

