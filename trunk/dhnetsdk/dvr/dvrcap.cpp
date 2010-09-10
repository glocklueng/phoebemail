///////////////////////////////////////////////////////////////////////////////////////////
// �ļ���: dvrcap.cpp
// ������: ����
// ����ʱ��: 
// ��������: dvr����
///////////////////////////////////////////////////////////////////////////////////////////
#include "dvrcap.h"
#include "def.h"

//�õ���������˿ڸ���
int alarminputCount(int type, unsigned char *buf)
{
	switch (type)
    {
	case PRODUCT_DVR_NONREALTIME_MACE:		//��ʵʱMACE
		return 8;
	case PRODUCT_DVR_NONREALTIME:			//��ʵʱ
		return 4;
		break;
	case PRODUCT_NVS_MPEG1:					//������Ƶ������
		break;
	case PRODUCT_DVR_MPEG1_2:				//MPEG1��·¼���
		return 4;
	case PRODUCT_DVR_MPEG1_8:				//MPEG1��·¼���
		return 8;
	case PRODUCT_DVR_MPEG4_8:				//MPEG4��·¼���
		return 8;
	case PRODUCT_DVR_MPEG4_16:				//MPEG4ʮ��·¼���
		return 16;
	case PRODUCT_DVR_MPEG4_SX2:			    //MPEG4����ʮ��·¼���
		return 8;
	case PRODUCT_DVR_MEPG4_ST2:				//MPEG4��ͨ¼���
		return 8;
	case PRODUCT_DVR_MEPG4_SH2:				//MPEG4�Ӻ�¼���
		return 8;
    case PRODUCT_DVR_MPEG4_GBE:              //MPEG4��ͨ������ǿ��¼���
        return 16;
    case PRODUCT_DVR_MPEG4_NVSII:            //PRODUCT_DVR_MPEG4_NVSII
        return 4;
	case PRODUCT_DVR_STD_NEW:				//�±�׼����Э��
		break;
	default:
		return 8;
	}

	return 8;
}

//�õ���������˿ڸ���
int alarmoutputCount(int type, unsigned char *buf)
{
	switch (type)
    {
	case PRODUCT_DVR_NONREALTIME_MACE:		//��ʵʱMACE
		break;
	case PRODUCT_DVR_NONREALTIME:			//��ʵʱ
		return 3;
	case PRODUCT_NVS_MPEG1:					//������Ƶ������
		break;
	case PRODUCT_DVR_MPEG1_2:				//MPEG1��·¼���
		return 3;
	case PRODUCT_DVR_MPEG1_8:				//MPEG1��·¼���
		break;
	case PRODUCT_DVR_MPEG4_8:				//MPEG4��·¼���
		break;
	case PRODUCT_DVR_MPEG4_16:				//MPEG4ʮ��·¼���
		break;
	case PRODUCT_DVR_MPEG4_SX2:			    //MPEG4����ʮ��·¼���
		return 3;
	case PRODUCT_DVR_MEPG4_ST2:				//MPEG4��ͨ¼���
		return 3;
	case PRODUCT_DVR_MEPG4_SH2:				//MPEG4�Ӻ�¼���
		return 3;
    case PRODUCT_DVR_MPEG4_GBE:              //MPEG4��ͨ������ǿ��¼���
        return 3;//20?
    case PRODUCT_DVR_MPEG4_NVSII:            //PRODUCT_DVR_MPEG4_NVSII
        return 2;
	case PRODUCT_DVR_STD_NEW:				//�±�׼����Э��
		break;
	default:
		return 3;
	}

	return 3;
}

//�õ�͸����������
bool transability(int type)
{
    switch (type)
    {
	case PRODUCT_DVR_NONREALTIME_MACE:		//��ʵʱMACE
		break;
	case PRODUCT_DVR_NONREALTIME:			//��ʵʱ
		break;
	case PRODUCT_NVS_MPEG1:					//������Ƶ������
		break;
	case PRODUCT_DVR_MPEG1_2:				//MPEG1��·¼���
		break;
	case PRODUCT_DVR_MPEG1_8:				//MPEG1��·¼���
		break;
	case PRODUCT_DVR_MPEG4_8:				//MPEG4��·¼���
		break;
	case PRODUCT_DVR_MPEG4_16:				//MPEG4ʮ��·¼���
		break;
	case PRODUCT_DVR_MPEG4_SX2:			    //MPEG4����ʮ��·¼���
		return true;
	case PRODUCT_DVR_MEPG4_ST2:				//MPEG4��ͨ¼���
		return true;
	case PRODUCT_DVR_MEPG4_SH2:				//MPEG4�Ӻ�¼���
		return true;
    case PRODUCT_DVR_MPEG4_GBE:              //MPEG4��ͨ������ǿ��¼���
        return true;
    case PRODUCT_DVR_MPEG4_NVSII:            //PRODUCT_DVR_MPEG4_NVSII
        return true;
	case PRODUCT_DVR_STD_NEW:				//�±�׼����Э��
		break;
	default:
		return false;
	}

	return false;
}

//�õ��Խ�����
bool talkability(int type)
{
	return true;
	
    switch (type)
    {
	case PRODUCT_DVR_NONREALTIME_MACE:		//��ʵʱMACE
		break;
	case PRODUCT_DVR_NONREALTIME:			//��ʵʱ
		break;
	case PRODUCT_NVS_MPEG1:					//������Ƶ������
		break;
	case PRODUCT_DVR_MPEG1_2:				//MPEG1��·¼���
		break;
	case PRODUCT_DVR_MPEG1_8:				//MPEG1��·¼���
		break;
	case PRODUCT_DVR_MPEG4_8:				//MPEG4��·¼���
		break;
	case PRODUCT_DVR_MPEG4_16:				//MPEG4ʮ��·¼���
		break;
	case PRODUCT_DVR_MPEG4_SX2:			    //MPEG4����ʮ��·¼���
		return true;
	case PRODUCT_DVR_MEPG4_ST2:				//MPEG4��ͨ¼���
		return true;
	case PRODUCT_DVR_MEPG4_SH2:				//MPEG4�Ӻ�¼���
		return true;
    case PRODUCT_DVR_MPEG4_GBE:              //MPEG4��ͨ������ǿ��¼���
        return true;
    case PRODUCT_DVR_MPEG4_NVSII:            //PRODUCT_DVR_MPEG4_NVSII
        return true;
	case PRODUCT_DVR_STD_NEW:				//�±�׼����Э��
		return true;
	default:
		return false;
	}

	return false;
}

//�õ��໭��Ԥ������
/*bool previewability(int type)
{
    switch (type)
    {
	case PRODUCT_DVR_NONREALTIME_MACE:		//��ʵʱMACE
		break;
	case PRODUCT_DVR_NONREALTIME:			//��ʵʱ
		break;
	case PRODUCT_NVS_MPEG1:					//������Ƶ������
		break;
	case PRODUCT_DVR_MPEG1_2:				//MPEG1��·¼���
		break;
	case PRODUCT_DVR_MPEG1_8:				//MPEG1��·¼���
		break;
	case PRODUCT_DVR_MPEG4_8:				//MPEG4��·¼���
		break;
	case PRODUCT_DVR_MPEG4_16:				//MPEG4ʮ��·¼���
		break;
	case PRODUCT_DVR_MPEG4_SX2:			    //MPEG4����ʮ��·¼���
		return true;
	case PRODUCT_DVR_MEPG4_ST2:				//MPEG4��ͨ¼���
		return true;
	case PRODUCT_DVR_MEPG4_SH2:				//MPEG4�Ӻ�¼���
		return false;
    case PRODUCT_DVR_MPEG4_GBE:              //MPEG4��ͨ������ǿ��¼���
        return true;
    case PRODUCT_DVR_MPEG4_NVSII:            //PRODUCT_DVR_MPEG4_NVSII
        return true;
	case PRODUCT_DVR_STD_NEW:				//�±�׼����Э��
		return true;
	default:
		return false;
	}

	return false;
}*/

