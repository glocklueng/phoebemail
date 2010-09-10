#include "../def.h"
#include "dvrdevice.h"
#include "dvrpacket_comm.h"
#include "dvrpacket_DDNS.h"
#include "dvrpacket_dvr2.h"
#include "dvrpacket_mobile.h"


bool sendMonitor_comm(CDvrDevice* device, int channel, int subtype, bool bstart, 
					  int nConnType, int nConnectID, char* szLocalIp, int nLocalPort)
{
	return sendMonitor_dvr2(device, channel, subtype, bstart, nConnType, nConnectID, szLocalIp, nLocalPort);
}

bool sendQueryRecord_comm(CDvrDevice* device, 
                      afk_query_record_s queryrecord, int nParam)
{
    switch (device->GetDvrInfo().type)
    {
    case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendQueryRecord_dvr2(device, queryrecord, nParam);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

bool sendQueryLog_comm(CDvrDevice* device, int logtype, int nParam, char* szPacket, int nPacketLen)
{
    switch (device->GetDvrInfo().type)
    {
    case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendQueryLog_dvr2(device, logtype, nParam, szPacket, nPacketLen);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

bool sendDownload_comm(CDvrDevice* device, 
                  afk_record_file_info_s recordinfo, bool bstart, int nByTime, int nConnectID, DWORD dwParm)
{
    switch (device->GetDvrInfo().type)
    {
	case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        sendDownload_dvr2(device, recordinfo, false, nByTime, nConnectID, dwParm);
        return sendDownload_dvr2(device, recordinfo, bstart, nByTime, nConnectID, dwParm);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

bool sendExportCfgFile_comm(CDvrDevice* device, bool bStart, int nParam)
{
	switch (device->GetDvrInfo().type)
    {
	case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
		sendExportCfgFile_dvr2(device, false, nParam);
        return sendExportCfgFile_dvr2(device, bStart, nParam);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

//���ؿ���
bool sendDownload_control_comm(CDvrDevice* device, int channel,
                               int offset_time, int offset_data, int nConnectID)
{
    switch (device->GetDvrInfo().type)
    {
    case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendDownload_control_dvr2(device, channel, offset_time, offset_data, nConnectID);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

//Edited by Linjy-2006-11-2
bool sendUpgradeControl_comm(CDvrDevice* device, afk_upgrade_channel_param_s *ucparam/*, bool bstart*/)
{
    switch (device->GetDvrInfo().type)
    {
	case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendUpgradeControl_dvr2(device, ucparam/*, bstart*/);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

bool sendImportCfgFile_comm(CDvrDevice* device, afk_upgrade_channel_param_s *ucparam)
{
	switch (device->GetDvrInfo().type)
    {
	case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendImportCfgFile_dvr2(device, ucparam);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

//Edited by Linjy-2006-11-2
int sendUpgradeData_comm(CDvrDevice* device, int packetId, char *buf, int len, afk_upgrade_channel_param_s *ucparam)
{
    switch (device->GetDvrInfo().type)
    {
	case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendUpgradeData_dvr2(device, packetId, buf, len, ucparam);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return -1;
}

int sendImportCfgData_comm(CDvrDevice* device, int packetId, char *buf, int len, afk_upgrade_channel_param_s *ucparam)
{
	switch (device->GetDvrInfo().type)
    {
	case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendImportCfgData_dvr2(device, packetId, buf, len, ucparam);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return -1;
}

/*
bool sendPreview_comm(CDvrDevice* device, 
                 int type1, int type2, bool bstart)
{
    switch (device->GetDvrInfo().type)
    {
    case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendPreview_dvr2(device, type1, type2, bstart);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}
*/

bool sendAlarmQuery_comm(CDvrDevice* device, bool bRecordState, int proType)
{
    switch (device->GetDvrInfo().type)
    {
	case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendAlarmQuery_dvr2(device, bRecordState,proType);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

bool sendControl_comm(CDvrDevice* device, 
                      int ch, int type1, int type2, int parm1, int parm2, int parm3, char *pParam4)
{
    switch (device->GetDvrInfo().type)
    {
	case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendControl_dvr2(device, ch, type1, type2, parm1, parm2, parm3, pParam4);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

bool sendQueryChannelName_comm(CDvrDevice* device)
{
    switch (device->GetDvrInfo().type)
    {
	case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendQueryChannelName_dvr2(device);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

//��ѯ��������������
bool sendQueryAlarmInput_comm(CDvrDevice* device)
{
    switch (device->GetDvrInfo().type)
    {
    case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendQueryAlarmInput_dvr2(device);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

//��ѯ�������������
bool sendQueryAlarmOutput_comm(CDvrDevice* device)
{
    switch (device->GetDvrInfo().type)
    {
	case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendQueryAlarmOutput_dvr2(device);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

//��ѯ���߱������
bool sendQueryWirelessAlarmOutput_comm(CDvrDevice* device)
{
    switch (device->GetDvrInfo().type)
    {
	case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendQueryWirelessAlarmOutput_dvr2(device);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

//��ѯ����������ʽ
bool sendQueryAlarmTrrigerMode_comm(CDvrDevice* device)
{
    switch (device->GetDvrInfo().type)
    {
	case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendQueryAlarmTrrigerMode_dvr2(device);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

//���ñ���������
bool sendSettingAlarm_comm(CDvrDevice* device, afk_alarm_control_info_s alarminfo)
{
    switch (device->GetDvrInfo().type)
    {
	case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendSettingAlarm_dvr2(device, alarminfo);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

bool sendSettingAlarmTrrigerMode_comm(CDvrDevice* device, afk_alarm_trriger_mode_s trrigerinfo)
{
	switch (device->GetDvrInfo().type)
    {
	case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendSetingAlarmTrrigerMode_dvr2(device, trrigerinfo);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

bool sendSetingDecoderAlarm_comm(CDvrDevice* device, afk_decoder_alarm_info_s dainfo)
{
    switch (device->GetDvrInfo().type)
    {
	case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendSetingDecoderAlarm_dvr2(device, dainfo);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

//����͸��������Ϣ
bool sendSettingSerial_comm(CDvrDevice* device, 
                              afk_trans_channel_param_s transinfo)
{
    switch (device->GetDvrInfo().type)
    {
    case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendSettingSerial_dvr2(device, transinfo);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

//����͸��������Ϣ
bool sendTransSerialData_comm(CDvrDevice* device, int transtype, char *buffer, int buflen)
{
    switch (device->GetDvrInfo().type)
    {
    case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendTransSerialData_dvr2(device, transtype, buffer, buflen);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

//���ͶԽ�Ҫ��
bool sendTalkRequest_comm(CDvrDevice* device, int channel, bool bstart, int encodetype)
{
    switch (device->GetDvrInfo().type)
    {
    case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendTalkRequest_dvr2(device, channel, bstart, encodetype);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

//���ͶԽ���Ϣ
bool sendTalkData_comm(CDvrDevice* device, int channel, char *buffer, int buflen, int encodetype)
{
    switch (device->GetDvrInfo().type)
    {
    case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendTalkData_dvr2(device, channel, buffer, buflen, encodetype);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

//ת��֡��
int  getframerate_comm(CDvrDevice* device, unsigned char chframerate)
{
    if (chframerate > 0x30 && chframerate < 0x3F)
    {
        int framerate = chframerate - 0x30;
        switch(framerate)
		{
        case 1:
		case 2:
		case 3:
			framerate = 1;
        	break;
        case 4:
		case 5:
		case 6:
		case 7:
		case 8:
		case 9:
			framerate = (chframerate - 0x33) ? (chframerate - 0x33) : 20;
        	break;
		case 10:
			framerate = 8;
			break;
		case 11:
			framerate = 10;
			break;
		case 12:
			framerate = 12;
			break;
		case 13:
			framerate = 15;
			break;
		case 14:
			framerate = 20;
			break;
        default:
			framerate = 0;
			break;
        } 
		if (framerate > 0)
        {
            return framerate;
        }
    }
	return 0; 
}

//��ѯ����
bool  sendQueryConfig_comm(CDvrDevice* device, unsigned short configtype, int param)
{
    switch (device->GetDvrInfo().type)
    {
	case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendQueryConfig_dvr2(device, configtype, param);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

//��������
bool sendSetupConfig_comm(CDvrDevice* device, unsigned short configtype, int param, unsigned char *buffer, int buflen)
{
    switch (device->GetDvrInfo().type)
    {
    case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendSetupConfig_dvr2(device, configtype, param, buffer, buflen);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

//����¼��״̬
bool sendSetupRecordState_comm(CDvrDevice* device, unsigned char *buffer, int buflen)
{
    switch (device->GetDvrInfo().type)
    {
	case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendSetupRecordState_dvr2(device, buffer, buflen);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

bool sendQueryDeviceTime_comm(CDvrDevice* device)
{
    switch (device->GetDvrInfo().type)
    {
    case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendQueryDeviceTime_dvr2(device);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

//�����豸ʱ��
bool sendSetupDeviceTime_comm(CDvrDevice* device, int year, int month, int day,
                              int hour, int minute, int second)
{
    switch (device->GetDvrInfo().type)
    {
    case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendSetupDeviceTime_dvr2(device, year, month, day, hour, minute, second);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

//��ѯЭ��(����Э���������Э��)
bool sendQueryProtocol_comm(CDvrDevice* device, int protocoltype,DWORD dwProtocolIndex)
{
    switch (device->GetDvrInfo().type)
    {
    case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendQueryProtocol_dvr2(device, protocoltype,dwProtocolIndex);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

//��ѯϵͳ��Ϣ
bool sendQuerySystemInfo_comm(CDvrDevice* device, int type,  int param)
{
    switch (device->GetDvrInfo().type)
    {
    case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendQuerySystemInfo_dvr2(device, type, param);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

//�����û�����
bool sendUserOperate_comm(CDvrDevice* device, int type, char *buffer, int bufferlen)
{
    switch (device->GetDvrInfo().type)
    {
	case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendUserOperate_dvr2(device, type, buffer, bufferlen);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

//ǿ��I��
bool sendForceIframe_comm(CDvrDevice* device,  unsigned char mainchn, unsigned char subchn)
{
    switch (device->GetDvrInfo().type)
    {
    case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
		return sendForceIframe_dvr2(device, mainchn, subchn);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}


//������������
bool sendLimitFlux_comm(CDvrDevice* device, unsigned short limitflux)
{
    switch (device->GetDvrInfo().type)
    {
    case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
		return sendLimitFlux_dvr2(device, limitflux);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

//��ѯ�豸����״̬
bool sendQuerydevstate_comm( CDvrDevice* device, unsigned char chn, unsigned char type)
{
    switch (device->GetDvrInfo().type)
    {
    case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
		return sendQuerydevstate_dvr2(device, chn, type);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

//ͨ��������DDNS��ѯIP
bool sendQueryIPByName_comm(CDvrDevice* device, char *name, int namelen)
{
	switch (device->GetDvrInfo().type)
    {
    case PRODUCT_DVR_DDNS:					// DDNS������
        return sendQueryIPByName_DDNS(device, name, namelen);
        break;
    default:
        break;
    }
    return false;
}

bool sendQueryAlarmState_comm(CDvrDevice* device, int statetype,int deviceid)
{
	switch (device->GetDvrInfo().type)
    {
    case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
	    return sendQueryAlarmState_dvr2(device, statetype,deviceid);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

bool sendCapture_comm(CDvrDevice* device, 
					  int channel, int pipeno, bool bstart)
{
    switch (device->GetDvrInfo().type)
    {
    case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendCapture_dvr2(device, channel, pipeno, bstart);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}


bool sendSetupChannelOsdString_comm(CDvrDevice* device, int channelno, int enable, int* position, unsigned char *buf, int buflen)
{
	switch (device->GetDvrInfo().type)
    {
    case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendSetupChannelOsdString_dvr2(device, channelno, enable, position, buf, buflen);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

//ץͼ����
bool sendSnap_comm(CDvrDevice* device,void* snapParam, unsigned char type)
{
	switch(device->GetType())
	{
	case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
		return sendSnap_mobile(device,snapParam,type);
		break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
	default:
		break;
	}
	return  false;
}

//GPS����
bool sendGpsAlarm_comm(CDvrDevice* device,void* gpsParam)
{
	return sendGpsAlarm_mobile(device,gpsParam);
	/*
    switch(device->gettype())
	{
		case PRODUCT_BAV_SERIAL:
			return sendGpsAlarm_mobile(device,gpsParam);
			break;
		default:
			break;
	}
	return  false;
	*/
}

//����������
bool sendHeartBeat_comm(CDvrDevice* device)
{
	switch (device->GetDvrInfo().type)
    {
    case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendHeartBeat_dvr2(device);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

bool sendRequestPacket_comm(CDvrDevice* device, int type, int nSequence, int subtype, void *pCondition)
{
	// �������豸
	return sendRequestPacket_dvr2(device, type, nSequence, subtype, pCondition);
}

bool sendQueryTransCom_comm(CDvrDevice* device, int nTransComType)
{
	switch (device->GetDvrInfo().type)
    {
    case PRODUCT_DVR_NONREALTIME_MACE:		// ��ʵʱMAC
    case PRODUCT_DVR_NONREALTIME:			// ��ʵʱ
    case PRODUCT_NVS_MPEG1:					// ������Ƶ������
    case PRODUCT_DVR_MPEG1_2:				// MPEG1��·¼���
    case PRODUCT_DVR_MPEG1_8:				// MPEG1��·¼���
        break;
    case PRODUCT_DVR_MPEG4_8:				// RW MPEG4��·¼���
    case PRODUCT_DVR_MPEG4_16:				// RW MPEG4ʮ��·¼���
    case PRODUCT_DVR_MPEG4_SX2:				// MPEG4����ʮ��·¼���
    case PRODUCT_DVR_MEPG4_ST2:				// MPEG4��ͨ¼���
    case PRODUCT_DVR_MEPG4_SH2:				// MPEG4�Ӻ�¼���
    case PRODUCT_DVR_MPEG4_GBE:				// MPEG4��ͨ������ǿ��¼���
    case PRODUCT_DVR_MPEG4_NVSII:			// MPEG4������Ƶ������II��
	case PRODUCT_DVR_ATM:					// ATM��
	case PRODUCT_NB_SERIAL:					// ������ʵʱNBϵ�л���
	case PRODUCT_LN_SERIAL:					// LNϵ�в�Ʒ
	case PRODUCT_BAV_SERIAL:					// BAVϵ�в�Ʒ
	case PRODUCT_SDIP_SERIAL:				// SDIPϵ�в�Ʒ
	case PRODUCT_IPC_SERIAL:					// IPCϵ�в�Ʒ
	case PRODUCT_NVS_B:						// NVS Bϵ��
	case PRODUCT_NVS_C:						// NVS Hϵ��
	case PRODUCT_NVS_S:						// NVS Sϵ��
	case PRODUCT_NVS_E:						// NVS Eϵ��
	case PRODUCT_DVR_NEW_PROTOCOL:			// �豸����
	case PRODUCT_NVD_SERIAL:					// ������
	case PRODUCT_DVR_N5:						// N5
	case PRODUCT_DVR_MIX_DVR:				// ���DVR
	case PRODUCT_SVR_SERIAL:					// SVR
	case PRODUCT_SVR_BS:						// SVR-BS
	case PRODUCT_NVR_SERIAL:					// NVR
        return sendQueryTransCom_dvr2(device, nTransComType);
        break;
    case PRODUCT_DVR_STD_NEW:				// �±�׼����Э��
        break;
    default:
        break;
    }
    return false;
}

//�����÷���
bool sendNewConfigPacket_comm(CDvrDevice* device,int nSequence, void *pCondition)
{
	// 16·���ϵ��豸
	return sendNewConfigPacket_dvr2(device, nSequence, pCondition);
}






